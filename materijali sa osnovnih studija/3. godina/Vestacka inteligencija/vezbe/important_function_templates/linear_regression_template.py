# pipeline koji je vrlo cest kod problema masinskog ucenja:
# 1) Priprema i obrada podataka
# 2) Treniranje modela
# 3) Evaulacija modela
# 4) Koriscenje modela 

import pandas as pd
import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score, mean_squared_error

# 1) -------------------- priprema i obrada -------------------- 
df = pd.read_csv('some_data.csv')

df = df.replace('?', np.nan)    # ako su nepostojece vrednosti obelezene sa '?' u podacina i ako zelimo da ih izbacimo
df = df.dropna()

X = df.drop('kolona_koju_predvidjamo', axis=1)
y = df[['kolona_koju_predvidjamo']]

# dodatno: ako nam treba da neke kaegoricke kolone prebacimo u neke brojne vrednosti, korisna transformacija za ovo je:
# dataset['Origin'] = dataset['Origin'].map({1: 'USA', 2: 'Europe', 3: 'Japan'})   <- tj ovo je samo primer koriscenja
# imamo i   df = pd.get_dummies(df)    ali ovo dummy enkodiranje daje dodatne kolone, pa treba da razmislimo da li zelimo to ili ovo iznad

# primer standardizacije iz nekog od ispitnih zadataka (trebalo je da se predvidi MEDV kolona):
# X_train_standardized = (X_train - df.drop(['MEDV'], axis=1).mean()) / df.drop(['MEDV'], axis=1).std()
# y_train_standardized = (y_train - df[['MEDV']].mean()) / df[['MEDV']].std()
# X_test_standardized = (X_test - df.drop(['MEDV'], axis=1).mean()) / df.drop(['MEDV'], axis=1).std()
# y_test_standardized = (y_test - df[['MEDV']].mean()) / df[['MEDV']].std()

# test size i random state biramo kako nam odgovara
# y_train su klasifikacije podataka iz X_train
# y_test su klasifikacije podataka iz X_test
# NOTE: semantika ovoga se razlikuje u odnosu na ono sto vidimo na primerima iz neuronskih mreza,
# tamo ono sto se vraca je bi bilo:   (X_train, y_train), (X_test, y_test)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=123)

# 2) -------------------- treniranje -------------------- 
reg = LinearRegression()
reg.fit(X_train, y_train)

# primeri sta sve mozemo da vidimo posle fitovanja

# mozemo npr da vidimo slobodnog clana iz modela linearne regresije
print(reg.intercept_[0])

# nnpr da vidimo vrednosti modela dodeljene svakoj koloni ( reg.coef_ nam daje niz svih koeficijenata)
for idx, col_name in enumerate(X_train.columns):
    print(f'coef za {col_name} = {reg.coef_[0][idx]}')

# 3) -------------------- evaliacija --------------------     (pored ovih imamo i reg.score(x, y))
# npr r2 metrika    ( imamo u sklearn.metrics)
r2_test = r2_score(Y_test, reg.predict(X_test))            
r2_train = r2_score(Y_train, reg.predict(X_train))
print(f'r2 test {r2_test}')
print(f'r2 train {r2_train}')

# npr srednje kvadratna greska ( imamo u sklearn.metrics)
mse_test = mean_squared_error(Y_test, reg.predict(X_test))
mse_train = mean_squared_error(Y_train, reg.predict(X_train))
print(f'mse test {mse_test}')
print(f'mse train {mse_train}')

# 4)  -------------------- koriscenje modela -------------------- 
# zavisi od problema
# npr najjednostavnije moguce:
result = reg.predict([some_data])