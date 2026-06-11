install.packages("mosaic")
install.packages("psych")

library(mosaic)
library(psych)

# CSV-Datei einlesen
dataset <- read.csv2("dft.csv", header=TRUE, sep=";",dec=".")

#Spalten überprüfen
print("Die geladenen Spalten sind:")
print(colnames(dataset))

# ANOVA-Analyse für min
anova_result <- aov(min ~ Category, data = dataset)
plotModel(anova_result)
print("min")
summary(anova_result)

# ANOVA-Analyse für max
anova_result <- aov(max ~ Category, data = dataset)
plotModel(anova_result)
print("max")
summary(anova_result)

# ANOVA-Analyse für avg
anova_result <- aov(avg ~ Category, data = dataset)
plotModel(anova_result)
print("avg")
summary(anova_result)

# ANOVA-Analyse für skewness
anova_result <- aov(skewness ~ Category, data = dataset)
plotModel(anova_result)
print("skewness")
summary(anova_result)

# ANOVA-Analyse für variance
anova_result <- aov(variance ~ Category, data = dataset)
plotModel(anova_result)
print("variance:")
summary(anova_result)

# ANOVA-Analyse für energy
anova_result <- aov(energy ~ Category, data = dataset)
plotModel(anova_result)
print("energy:")
summary(anova_result)

# ANOVA-Analyse für kurtosis
anova_result <- aov(kurtosis ~ Category, data = dataset)
plotModel(anova_result)
print("kurtosis")
summary(anova_result)
