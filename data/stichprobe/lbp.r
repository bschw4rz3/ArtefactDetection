install.packages("mosaic")
install.packages("psych")

library(mosaic)
library(psych)

# CSV-Datei einlesen
dataset <- read.csv2("lbp.csv", header=TRUE, sep=";",dec=".")

#Spalten überprüfen
print("Die geladenen Spalten sind:")
print(colnames(dataset))

# ANOVA-Analyse für 0
anova_result <- aov(X0 ~ Category, data = dataset)
plotModel(anova_result)
print("0:")
summary(anova_result)

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

# ANOVA-Analyse für P+1
anova_result <- aov(P.1 ~ Category, data = dataset)
plotModel(anova_result)
print("P+1:")
summary(anova_result)
