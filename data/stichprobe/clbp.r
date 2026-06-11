install.packages("mosaic")
install.packages("psych")

library(mosaic)
library(psych)

# CSV-Datei einlesen
dataset <- read.csv2("clbp.csv", header=TRUE, sep=";",dec=".")

#Spalten überprüfen
print("Die geladenen Spalten sind:")
print(colnames(dataset))

# ANOVA-Analyse für 1
anova_result <- aov(X1 ~ Category, data = dataset)
plotModel(anova_result)
print("1:")
summary(anova_result)

# ANOVA-Analyse für 2
anova_result <- aov(X2 ~ Category, data = dataset)
plotModel(anova_result)
print("2:")
summary(anova_result)

# ANOVA-Analyse für p+1
anova_result <- aov(P.1 ~ Category, data = dataset)
plotModel(anova_result)
print("p+1:")
summary(anova_result)
