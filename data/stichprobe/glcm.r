install.packages("mosaic")
install.packages("psych")

library(mosaic)
library(psych)

# CSV-Datei einlesen
dataset <- read.csv2("glcm.csv", header=TRUE, sep=";",dec=".")

#Spalten überprüfen
print("Die geladenen Spalten sind:")
print(colnames(dataset))

# ANOVA-Analyse für Energy
anova_result <- aov(Energy ~ Category, data = dataset)
plotModel(anova_result)
print("Energy:")
summary(anova_result)

# ANOVA-Analyse für Contrast
anova_result <- aov(Contrast ~ Category, data = dataset)
plotModel(anova_result)
print("Contrast")
summary(anova_result)

# ANOVA-Analyse für Homogenity
anova_result <- aov(Homogenity ~ Category, data = dataset)
plotModel(anova_result)
print("Homogenity:")
summary(anova_result)

# ANOVA-Analyse für IDM
anova_result <- aov(IDM ~ Category, data = dataset)
plotModel(anova_result)
print("IDM:")
summary(anova_result)

# ANOVA-Analyse für Entropy
anova_result <- aov(Entropy ~ Category, data = dataset)
plotModel(anova_result)
print("Entropy:")
summary(anova_result)

# ANOVA-Analyse für Mean1
anova_result <- aov(Mean1 ~ Category, data = dataset)
plotModel(anova_result)
print("Mean1:")
summary(anova_result)
