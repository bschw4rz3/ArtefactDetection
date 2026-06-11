import numpy as np
import pandas as pd
from sklearn.linear_model import Lasso
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from var_dump import var_dump

# Beispiel-Datensatz erstellen
def generate_data(n_samples=100, n_features=10, random_state=42):
    np.random.seed(random_state)
    X = np.random.randn(n_samples, n_features)
    coef = np.random.randn(n_features)
    coef[coef < 0.5] = 0  # Einige Koeffizienten auf 0 setzen (irrelevante Features)
    y = X @ coef + np.random.randn(n_samples) * 0.1
    return pd.DataFrame(X, columns=[f'Feature_{i}' for i in range(n_features)]), y

df = pd.read_csv('ft.csv', sep = ';')

categoryArray = []
for name, values in df[["Category"]].items():
    for i in range(values.count()):
        if values[i] == "Artefact":
            categoryArray.append(1)
        else:
            categoryArray.append(0)

# Daten generieren
X = df[["min", "max", "avg", "skewness", "variance", "energy", "kurtosis" ]]
y = categoryArray

# Daten aufteilen
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Daten skalieren
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# Lasso-Regression mit L1-Regularisierung
lasso = Lasso(alpha=0.1)  # Regularisierungsstärke anpassen
lasso.fit(X_train_scaled, y_train)

var_dump(lasso.coef_)

# Wichtige Features auswählen
selected_features = X.columns[lasso.coef_ != 0]
print("Ausgewählte Features:", list(selected_features))
