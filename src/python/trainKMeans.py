import matplotlib.pyplot as plt
import numpy as np
import sys
import scipy.fft
import numbers
from decimal import Decimal
from waveletMethods import *

from sklearn.model_selection import train_test_split
from sklearn.cluster import KMeans
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix

import matplotlib.pyplot as plt
from sklearn import svm

taringsArray = readInputNpMultiple(sys.argv[1], False)
testArray = readInputNpMultiple(sys.argv[2], False)
targetArray = readInputNpMultiple(sys.argv[3], False, True)

X_train=taringsArray
X_test = testArray
y_train = targetArray[0]

#Erstellen des Entscheidungsbaum-Klassifikators und Trainieren des Modells
kmeans = KMeans(n_clusters=2, random_state=42)
kmeans.fit(X_train)

y_pred = kmeans.predict([X_train[0]])

inverse=False
if y_pred[0] != int(y_train[0]):
    inverse=True

#Vorhersagen auf dem Testset
y_pred = kmeans.predict(X_test)

if inverse == True:
    if y_pred[0] == 0:
        y_pred[0] = 1
    else:
        y_pred[0] = 0

print(y_pred)