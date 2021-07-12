# NOTE: dobijam greske, mrzi me da debagujem

import gym
import numpy as np
import tensorflow as tf
from tensorflow import keras

# ovo zakomentarisano je neki mali test kod koji je na pocetku casa kucao u pajton interaktivnom terminalu da bismo videli kako radi
# env = gym.make('CartPole-v1')   # pravimo okruzenje cije ime prosledimo
# obs = env.reset()               # obavezno prvo reset, to inicijalizuje okruzenje i vraca prvu opservaciju. Ta opservacija
                                # i kog je ona oblika zavisi od okruzenja u kome smo. Konkretno za cart pole je to
                                # array([f1, f2, f3, f4])  f1-pozicija postolja, f2-brzina postolja, f3-ugao sipke
                                # f4-ugaona brzina sipke, npr: array([ 0.01153075, -0.00638428, -0.02299557,  0.01545624])
# env.render()          # mozemo prikazati trenutno stanje
# env.action_space      # mozemo videti sve dostupne akcije u okruzenju. Npr on kada je pozvao obo na vezbama kao ispis 
                        # je dobio Discrete(2). Znacenje je da ima 2 moguce akcije koje su integeri. 
                        # 0 da se sipka pomeri u levo i 1 da se sipka pomeri u desno
# action = 1                                   # ovo je neka akcija koju zelimo da preduzmemo (sta je ona zavisi od konkretnog okruzenja)
# obs, reward, done, info = env.step(action)   # simuliramo tu akciju. vraca 4 parametra, sledecu opservaciju, nagradu, oznaku da li je
                                               # simulacija(epizoda) gotova, i neke dodatne informacije za debagovanje i treniranje
# u cart okruzenju, nagrada je uvek 1 dokle god sipka nije pala



# 1) za pocetak mozemo da hardcodujemo neko jednostavno pravilo na osnovu koga ce se neki potez desavati
def simple_rule_policy(obs):
    angle = obs[2]
    return 0 if angle < 0 else 1

# 2) pisemo neko malo kompleksnije pravilo, npr zelimo da istreniramo neuronsku mrezu
# tako da joj prosledimo opservaciju a onda ona za nas odluci koji potez radimo. Znamo da svaka opservacija ima 4 clana
# tako da znamo da ulaz u neuronsku mrezu ima 4 elementa. Znamo da nam potezi mogu bili 0 i 1, ali necemo da napravimo neurosnku
# sa 2 izlaza, nego sa 1 izlazom koji ce predstavljati verovatnocu (da maksimizujemo nagradu ako se pomerimo npr u levo)
# uvodimo malo nedeterminizma da bismo podstakli agenta da potencijalno koristi i neka stanja koja vec nije naucio (?)
# algoritam koji cemo koristiti:
#   (1) pusmi neurosnku mrezu da odigra igru nekoliko puta i u svakom koraku izracunaju se gradijenti koji bi ucinili odabranu akciju jos verovatnijom
#   (2) izracunati prednost svake akcije (action advantage)(objasnio je na snimku sta je ovo tacno, nisam ispratio najbolje)
#   (4) ako je prednost akcije pozitivna, primenimo gradijente iz prvog koraka kako bi akcija bila jos verovatnija u buducnosti
#      ako je prednost akcije negativna, primenimo gradijente u suprotnom smeru  
#   (5) stacuvamo srednje vrednosti svih gradijenata i iskoristimo ih da uradimo gradijentni spust


env = gym.make('CartPole-v1')  
obs = env.reset()  

# NOTE: ovu neuronsku mrezu i ove pomocne funkcije je pravio tek za drugu drugi pristup
n_inputs = env.observartion_space.shape[0]    # ne moramo ovako dinamicno, mozemo da hardcodujemo 4 jer znamo da tako sigurno izgledaju sve opservacije
n_iterations = 150          # broj iteracija koje cemo trenirati
n_episode_per_iteration = 10
n_max_steps = 100
discount_factor = 0.95
learning_rate = 0.01

opitimizer = tf.keras.optimizers.Adam(lr=learning_rate)
loss_fn = tf.keras.losses.binary_crossentropy

model = tf.keras.models.Sequential([
    tf.keras.layers.Dense(5, activation='elu', input_shape=[n_inputs]),
    tf.keras.layers.Dense(1, activation='sigmoid')
])
# imamo problem (zove se problem dodele zasluge). Kada agent dobije neku nagradu usled akcije, on tesko moze da zna da li ta nagrada
# vodi do dugorocnog uspeha. Jedini nacin da se vidi da li je uspesan je da se epizoda odradi do kraja
# jedan od nacina da se ovo resi je da se sve nagrade koje dolaze nakon neke akcije uz neki faktor slabljenja

# funkcija koja za nas odigra jedan korak za prosledjene parametre
# sta on tacno radi u ovoj funkciji nisam bas ispratio
def play_one_step(env, obs, model, loss_fn):
    with tf.GradientTape() as tape:                                     # ne bavimo se preterano sta ovo znaci, nesto je low level specificno za tensorflow, samo zapamtimo da ga koristimo
        left_probability = model(obs[np.newaxis])                       # za trenutno stanje damo modelu da proceni koja je verovatnoca da se pomerimo u levo
        action = (tf.random.uniform([1,1]) > left_probability)          # gledamo da li se zapravo pomeramo u levo na osnovu izracunate verovatnoce
        y_target = tf.constant([[1.0]]) - tf.cast(action, tf.float32)   # sta je trebalo da uradimo (ako je left_prob bilo 1, onda je ovo 0 i obrnuto)
        loss = tf.readuce_mean(loss_fn(y_target, left_probability))     # da bi izracunali loss, treba da znamo sta je trebalo da uradimo
    grads = tape.gradient(loss, model.trainable_variabls)               # gradijent funkcije nad svim promenljivima modela
    obs, reward, done, _ = env.step(int(action[0,0].numpy()))           # trazimo da okruzenje uradi jos jedan korak
    return obs, reward, done, grads

# ovde sabiramos sve nagrade i vracamos ve gradijente koje smo dobili
def play_multiple_episodes(env, n_episodes, n_max_steps, models, loss_fn):
    all_rewards = []
    all_gradients = []
    for episode in range(n_episodes):
        current_rewards = []
        current_grads = []
        obs = env.reset()
        for step in range(n_max_steps):
            obs, reward, done, grads = play_one_step(env, obs, model, loss_fn)
            current_rewards.append(reward)
            current_grads.append(grads)
            if done:
                break
        all_rewards.append(current_rewards)
        all_gradients.append(current_grads)
    # na osnovu nagrada cemo znati koja epizoda je najbolja, na osnovu gradijenata cemo znati koje vrednosti parametara su dovele do najvece nagrade
    return all_rewards, all_gradients

# slabljenje nagrada
def discount_rewards(rewards, discount_factor):
    discounted = np.array(rewards)
    for step in range(len(rewards)-2, -1, -1):
        discounted[step] += discounted[step+1] * discount_factor
    return discounted

def discount_and_normalize_rewards(all_rewards, discount_factor):
    all_discounted_rewards = [discount_rewards(rewards, discount_factor) for rewards in all_rewards]
    flat_rewards = np.concatenate(all_discounted_rewards)
    rewards_mean = flat_rewards.mean()
    rewards_std = flat_rewards.std()
    return [ ( discounted_reward - rewards_mean / rewards_std ) for discounted_reward in all_discounted_rewards ]

# neka bezveze provera, da vidimo ponasanje funkcija koje smo napisali
# print(discount_rewards([10, 0, -50], discount_factor=0.8))
# print(discount_and_normalize_rewards([[10,0,-50], [10,20]], discount_factor=0.8))

for iteration in range(n_iterations):
    all_rewards, all_grads = play_multiple_episodes(env, n_episodes_per_update, n_max_steps, models, loss_fn)
    all_final_rewards = discount_and_normalize_rewards(all_rewards, discount_factor)

    all_mean_grads = []
    for var_index in range(len(model.trainable_variables)):
        mean_grads = tf.reduce_mein(
            [final_reward * all_grads[episode_index][step][var_index] 
                for episode_index, final_rewards in enumerate(all_final_rewards) 
                for step, final_reward in enumerate(final_rewards) 
            ],   axis = 0
        )
        all_mean_grads.append(mean_grads)
    opitimizer.apply_gradients(zip(all_mean_grads, model.trainable_variables))

# ovde je na vezbama napravio neki svoj modul animate koji me mrzi da ubacujem koji plotuje ovo
# import animate
# frames = animate.render_policy_net(model) 
# animate.plot_animation(frames)


# ovo ispod je bilo dok smo koristili funkciju 1), posle za neuronsku mrezu nam nije trebalo
# totals = []
# # simuliramo odredjen broj epizoda, npr 500
# for episode in range(500):
#     episode_rewards = 0
#     obs = env.reset()           # obavezno na pcoetku svake epizode restartujemo okruzenje
#     for step in range(200):     # recimo npr da u svakoj epizodi nacinimo 200 koraka
#         action = simple_rule_policy(obs)
#         obs, reward, done, info = env.step(action)
#         episode_rewards += reward
#         if done:
#             break
#     totals.append(episode_rewards)  # npr da vidimo rewardove koje smo dobili po epizodama
#                                     # posto nam je reward uvek 1 (jer je tako propisano u samom cart okruzenju), nas reward
#                                     # po epizodi oznacava koliko smo poteza uspesno balansirali sa nasom jednostavnom politikom


# # ocenjujemo nekako ovo sto smo do sad uradili
# print(np.mean(totals))  # srednja vrednost
# print(np.std(totals))   # standardna devijacija
# print(np.min(totals))
# print(np.max(totals))