install.packages("mosaic")
install.packages("psych")

library(mosaic)
library(psych)

# CSV-Datei einlesen
dataset <- read.csv2("huFeature.csv", header=TRUE, sep=";",dec=".")
bla <- dataset$Category

#Spalten überprüfen
print("Die geladenen Spalten sind:")
print(colnames(dataset))

# ANOVA-Analyse für Hu.1
anova_result <- aov(Hu.1 ~ Category, data = dataset)
plotModel(anova_result)
print("Hu.1:")
summary(anova_result)

# ANOVA-Analyse für Hu.2
anova_result <- aov(Hu.2 ~ Category, data = dataset)
plotModel(anova_result)
print("Hu.2:")
summary(anova_result)

# ANOVA-Analyse für Hu.3
anova_result <- aov(Hu.3 ~ Category, data = dataset)
plotModel(anova_result)
print("Hu.3:")
summary(anova_result)

# ANOVA-Analyse für Hu.4
anova_result <- aov(Hu.4 ~ Category, data = dataset)
plotModel(anova_result)
print("Hu.4:")
summary(anova_result)

# ANOVA-Analyse für Hu.5
anova_result <- aov(Hu.5 ~ Category, data = dataset)
plotModel(anova_result)
print("Hu.5:")
summary(anova_result)

# ANOVA-Analyse für Hu.6
anova_result <- aov(Hu.6 ~ Category, data = dataset)
plotModel(anova_result)
print("Hu.6:")
summary(anova_result)

# ANOVA-Analyse für Hu.7
anova_result <- aov(Hu.7 ~ Category, data = dataset)
plotModel(anova_result)
print("Hu.7:")
summary(anova_result)

