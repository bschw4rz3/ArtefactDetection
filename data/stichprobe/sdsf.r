install.packages("mosaic")
install.packages("psych")

library(mosaic)
library(psych)

# CSV-Datei einlesen
dataset <- read.csv2("sdsf.csv", header=TRUE, sep=";",dec=".")

#Spalten überprüfen
print("Die geladenen Spalten sind:")
print(colnames(dataset))

# ANOVA-Analyse für X0.0
anova_result <- aov(X0.0 ~ Category, data = dataset)
plotModel(anova_result)
print("0.0:")
summary(anova_result)

# ANOVA-Analyse für X0.1
anova_result <- aov(X0.1 ~ Category, data = dataset)
plotModel(anova_result)
print("0.1:")
summary(anova_result)

# ANOVA-Analyse für X0.2
anova_result <- aov(X0.2 ~ Category, data = dataset)
plotModel(anova_result)
print("0.2:")
summary(anova_result)

# ANOVA-Analyse für X0.3
anova_result <- aov(X0.3 ~ Category, data = dataset)
plotModel(anova_result)
print("0.3:")
summary(anova_result)

# ANOVA-Analyse für X0.4
anova_result <- aov(X0.4 ~ Category, data = dataset)
plotModel(anova_result)
print("0.4:")
summary(anova_result)

# ANOVA-Analyse für X0.5
anova_result <- aov(X0.5 ~ Category, data = dataset)
plotModel(anova_result)
print("0.5:")
summary(anova_result)

# ANOVA-Analyse für X0.6
anova_result <- aov(X0.6 ~ Category, data = dataset)
plotModel(anova_result)
print("0.6:")
summary(anova_result)

# ANOVA-Analyse für X0.7
anova_result <- aov(X0.7 ~ Category, data = dataset)
plotModel(anova_result)
print("0.7:")
summary(anova_result)

# ANOVA-Analyse für X0.8
anova_result <- aov(X0.8 ~ Category, data = dataset)
plotModel(anova_result)
print("0.8:")
summary(anova_result)

# ANOVA-Analyse für X0.9
anova_result <- aov(X0.9 ~ Category, data = dataset)
plotModel(anova_result)
print("0.9:")
summary(anova_result)

# ANOVA-Analyse für X1.0
anova_result <- aov(X1.0 ~ Category, data = dataset)
plotModel(anova_result)
print("1.0:")
summary(anova_result)
