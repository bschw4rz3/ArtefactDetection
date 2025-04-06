import matplotlib.pyplot as plt
import numpy as np
import sys
import scipy.fft
import numbers
from decimal import Decimal
from waveletMethods import *

from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix

import matplotlib.pyplot as plt
from sklearn import svm

import pickle

taringsArray = readInputNpMultiple(sys.argv[1], False)
testArray = readInputNpMultiple(sys.argv[2], False)
targetArray = readInputNpMultiple(sys.argv[3], False, True)

X_train=taringsArray
X_test = testArray
y_train = targetArray[0]

#Erstellen des Entscheidungsbaum-Klassifikators und Trainieren des Modells
#clf = svm.SVC(kernel="linear", C=1).fit(X_train, y_train)
clf = svm.SVC(kernel="linear", probability=False).fit(X_train, y_train)
#clf = pickle.load('model.pkl');

pickle.dump(clf,'model2.pkl');

#Vorhersagen auf dem Testset
y_pred = clf.predict(X_test)

print(y_pred)