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
from sklearn.tree import plot_tree

taringsArray = readInputNpMultiple(sys.argv[1], False)
testArray = readInputNpMultiple(sys.argv[2], False)
targetArray = readInputNpMultiple(sys.argv[3], False, True)

var_dump(targetArray);
exit

#Aufteilung der Daten in Trainings- und Testsets
#X_train, X_test, y_train, y_test = train_test_split(inputArray, targetArray, test_size=0.0, random_state=42)

X_train = taringsArray
X_test = testArray
y_train = targetArray

#Erstellen des Entscheidungsbaum-Klassifikators
clf = DecisionTreeClassifier(criterion='gini', max_depth=None, random_state=42)

#Trainieren des Modells
clf.fit(X_train, y_train[0])

#plt.figure(figsize=(12, 8))
#plot_tree(clf, class_names=["defect", "artefact"], filled=True, rounded=True)
#plt.show()

#Vorhersagen auf dem Testset
y_pred = clf.predict(X_test)

#Bewertung der Modellleistung
#accuracy = accuracy_score(y_test, y_pred)

#writeOutput(sys.argv[4], y_pred)

print(y_pred)