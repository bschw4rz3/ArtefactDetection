install.packages("mosaic")
install.packages("psych")

library(mosaic)
library(psych)

# CSV-Datei einlesen
dataset <- read.csv2("grayFeature.csv", header=TRUE, sep=";",dec=".")

#Spalten überprüfen
print("Die geladenen Spalten sind:")
print(colnames(dataset))

# ANOVA-Analyse für Mean
anova_result <- aov(Mean ~ Class, data = dataset)
plotModel(anova_result)
print("Mean:")
summary(anova_result)

# ANOVA-Analyse für Variance
anova_result <- aov(Variance ~ Class, data = dataset)
plotModel(anova_result)
print("Variance:")
summary(anova_result)

# ANOVA-Analyse für Skewness
anova_result <- aov(Skewness ~ Class, data = dataset)
plotModel(anova_result)
print("Skewness:")
summary(anova_result)

# ANOVA-Analyse für Kurtosis
anova_result <- aov(Kurtosis ~ Class, data = dataset)
plotModel(anova_result)
print("Kurtosis:")
summary(anova_result)

# ANOVA-Analyse für Power
anova_result <- aov(Power ~ Class, data = dataset)
plotModel(anova_result)
print("Power:")
summary(anova_result)

# ANOVA-Analyse für Entropy
anova_result <- aov(Entropy ~ Class, data = dataset)
plotModel(anova_result)
print("Entropy:")
summary(anova_result)

