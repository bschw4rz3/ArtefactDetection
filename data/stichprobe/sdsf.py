import numpy as np
import pandas as pd
from sklearn.linear_model import Lasso
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from var_dump import var_dump

df = pd.read_csv('sdsf.csv', sep = ';')

categoryArray = []
for name, values in df[["Category"]].items():
    for i in range(values.count()):
        if values[i] == "Artefact":
            categoryArray.append(1)
        else:
            categoryArray.append(0)

# Daten generieren
X = df[["0.0", "0.1", "0.2", "0.3", "0.4", "0.5", "0.6", "0.7", "0.8", "0.9", "1.0"]]
y = categoryArray

# Daten aufteilen
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Daten skalieren
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# Lasso-Regression mit L1-Regularisierung
lasso = Lasso(alpha=0.0025)  # Regularisierungsstärke anpassen
lasso.fit(X_train_scaled, y_train)

var_dump(lasso.coef_)

# Wichtige Features auswählen
selected_features = X.columns[lasso.coef_ != 0]
print("Ausgewählte Features:", list(selected_features))
