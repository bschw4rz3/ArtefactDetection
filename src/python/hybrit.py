import tensorflow as tf
import numpy as np
import pandas as pd
import os
os.system('set TF_ENABLE_ONEDNN_OPTS=0')

from var_dump import var_dump
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

# Modell-Speicherpfad
MODEL_PATH = "binary_classifier_model.h5"
columnCount=3

def compare_arrays(arr1, arr2):
    arr1, arr2 = np.array(arr1), np.array(arr2)
    
    if arr1.shape != arr2.shape:
        raise ValueError("Arrays müssen die gleiche Größe haben")
    
    matching_elements = np.sum(arr1 == arr2)
    total_elements = arr1.size
    similarity_percentage = (matching_elements / total_elements) * 100
    
    return similarity_percentage

def load_data(csv_file):
    df = pd.read_csv(csv_file, sep=";")
    
    # Erste Spalte als Zielvariable, nächste drei als Features
    X = df.iloc[:, 1:columnCount+1].values
    y = df.iloc[:, 0].values
    
    # Aufteilen in Trainings- und Testdaten
    train_mask = df.iloc[:, columnCount+1] == "training"
    test_mask = df.iloc[:, columnCount+1] == "test"
    
    x_train, y_train = X[train_mask], y[train_mask]
    x_test, y_test = X[test_mask], y[test_mask]
    
    # Normalisierung der Daten
    scaler = StandardScaler()
    x_train = scaler.fit_transform(x_train)
    x_test = scaler.transform(x_test)
    
    return x_train, y_train, x_test, y_test

def mapClass(y_classes):
    y_train = []
    for c in y_classes:
        A=0
        B=0
        if c == 0:
            A=1
        if c == 1:
            B=1
    
        y_train.append(np.array([A, B]))
    y_train = np.array(y_train)
    return y_train

def train(csv_file):
    x_train, y_classes, _, _ = load_data(csv_file)
    
    y_train = mapClass(y_classes)
    x_train, x_test, y_train, y_test = train_test_split(x_train, y_train, test_size=0.2)
    
    # Neuronales Netz erstellen
    model = tf.keras.Sequential([
        tf.keras.layers.Dense(16, activation='relu', input_shape=(columnCount,)),
        #tf.keras.layers.Dense(32, activation='relu'),
        #tf.keras.layers.Dense(64, activation='relu'),
        #tf.keras.layers.Dense(32, activation='relu'),
        #tf.keras.layers.Dense(16, activation='relu'),
        tf.keras.layers.Dense(8, activation='relu'),
        #tf.keras.layers.Dense(4, activation='relu'),
        tf.keras.layers.Dense(2, activation='softmax')
    ])
    
    # Kompilieren des Modells
    #optimizer = tf.keras.optimizers.Adam(learning_rate=0.0001)
    #model.compile(optimizer=optimizer, loss='binary_crossentropy', metrics=['accuracy'])
    #model.compile(optimizer=optimizer, loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    model.compile(optimizer='adam', loss='mean_squared_error', metrics=['accuracy'])
    
    model_file = "temp.keras"
    
    # Callbacks für frühes Stoppen und bestes Modell speichern
    early_stop = tf.keras.callbacks.EarlyStopping(monitor='val_loss', mode="auto", patience = 100, restore_best_weights = False)
    checkpoint = tf.keras.callbacks.ModelCheckpoint(model_file, monitor="val_loss", mode="min", save_best_only=True, verbose=1)
    
    # Training des Modells # , callbacks=[early_stopping]
    model.fit(x_train, y_train, epochs=1000, batch_size=32, validation_data=(x_test, y_test), callbacks=[early_stop, checkpoint])
    
    # Bestes Modell laden
    model.load_weights(model_file)
    
    # Speichern des Modells
    model.save(MODEL_PATH)
    print(f"Modell gespeichert unter {MODEL_PATH}")

def run(csv_file):
    if not os.path.exists(MODEL_PATH):
        print("Kein trainiertes Modell gefunden. Bitte zuerst trainieren.")
        return
    
    # Laden des gespeicherten Modells
    model = tf.keras.models.load_model(MODEL_PATH)
    print("Modell geladen.")
    
    _, _, x_test, y_test = load_data(csv_file)
    
    # Vorhersagen treffen
    predictions = model.predict(x_test)
    
    result = []
    for i in range(len(predictions)):
            if predictions[i][0] > predictions[i][1]:
                result.append(0)
            else:
                result.append(1)
    
    #predictions = (predictions > 0.5).astype(int)  # Rundung auf 0 oder 1
    
    print("Vorhersagen:", result)
    print("Erwartungen:", y_test)
    print(f"Übereinstimmung: {compare_arrays(result, y_test):.2f}%")

if __name__ == "__main__":
    import sys
    if len(sys.argv) > 2 and sys.argv[1] == "train":
        train(sys.argv[2])
    elif len(sys.argv) > 2 and sys.argv[1] == "run":
        run(sys.argv[2])
    else:
        print("Bitte einen gültigen Modus ('train' oder 'run') und eine CSV-Datei angeben.")