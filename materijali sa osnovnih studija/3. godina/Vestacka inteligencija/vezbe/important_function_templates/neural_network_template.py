import tensorflow as tf
from tensorflow import keras

# ucitamo neke podatke (npr neki ugradjeni dataset iz kerasa) (cifar10, na primer)
# (skup_za_treniranje, tacna_resenja_za_taj_skup), (skup_za_testiranje, tacna_resenja_za_taj_skup)
(X_train, X_labels), (y_test, y_labels) = keras.datasets.cifar10.load_data()

# treba da razumemo podatke, npr tako sto vidimo shapove i slicno
print(X_train.shape)

# normalizujemo podatke u interval [0,1] ako mozemo
X_train_processed = X_train / X_train.max()
y_test_processed = y_test / y_test.max()

# a ciljnu kolonu pretvaramo u vektor kategorije ako radimo klasifikaciju
X_labels_categorical = tf.keras.utils.to_categorical(X_labels, n)       # n broj kategorija
y_labels_categorical = tf.keras.utils.to_categorical(y_labels, n)

# pravimo model
model = tf.keras.models.Sequential()
model.add( tf.keras.layers.Conv2D(c, (i,j), activation='relu', input_shape=(...)) )    # c filtera, (i,j) dimenzija filtera     # sloj za konvolutivne  (ima i opcija padding='same')
model.add( tf.keras.layers.MaxPooling2D(l,k) )                                         # l,k dimenzija agregacije               # sloj za konvolutivne
model.add( tf.keras.layers.Flatten( input_shape=(x,y)) )  # ako je potreban 
model.add( tf.ekras.layers.Dropout(0.2))                  # ako je potreban  
model.add( tf.keras.layers.Dense(num, activation='relu') )  # num broj cvorova 
# za poslednji sloj ako imamo tacno 2 kategorije mozemo da ima 1 cvor i  activation='sigmoid'
model.add( tf.keras.layers.Dense(n, activation='softmax') )  # izlazni, ima n kategorija pa je to broj cvorova

# kompajliramo model pre fitovanja
# ako imamo 2 krajnje kategorije mozemo da korsitimo BinaryCrossentropy()
# jos neke metrike: 'mae', 'mse'
model.compile(optimizer='adam', loss=tf.keras.losses.CategoricalCrossentropy(), metrics=['accuracy'])   # npr: metrics = ['accuracy, 'mae', 'mse']

# model.summary()

# treniranje
history = model.fit(X_train_processed, X_labels_categorical, epocs=epocs, batch_size=batch_size
                    , validation_data = (y_test_processed, y_labels_categorical))
# plot   history.history['accuracy']        # zaone druge metrike je slicno, npr:   'mae'  i  'val_mae'
# plot   history.history['val_accuracy']


# evaluacija (ko smo naveli jos neke metrike i one ce biti vracene: npr bilo bi:  test_loss, test_acc, test_mae, test_mse)
test_loss, test_acc = model.evaluate(X_train_processed, X_labels_categorical, verbose=2)
print(test_loss)
print(test_acc)

# koriscenje modela
predictions = model.predict(y_test_processed)   # dobijamo vektor duzine n sa verovatnocama da pripada nekoj od n kategorija
max_index = np.argmax(predictions[0])           # indeks najvece verovatnoce