install.packages("mosaic")
install.packages("psych")

library(mosaic)
library(psych)

# CSV-Datei einlesen
dataset <- read.csv2("morlet.csv", header=TRUE, sep=";",dec=".")

#Spalten überprüfen
print("Die geladenen Spalten sind:")
print(colnames(dataset))

# ANOVA-Analyse für minFrequence
anova_result <- aov(minFrequence ~ Category, data = dataset)
plotModel(anova_result)
print("minFrequence")
summary(anova_result)

# ANOVA-Analyse für maxFrequence
anova_result <- aov(maxFrequence ~ Category, data = dataset)
plotModel(anova_result)
print("maxFrequence")
summary(anova_result)

# ANOVA-Analyse für avgFrequence
anova_result <- aov(avgFrequence ~ Category, data = dataset)
plotModel(anova_result)
print("avgFrequence")
summary(anova_result)

# ANOVA-Analyse für skewnessFrequence
anova_result <- aov(skewnessFrequence ~ Category, data = dataset)
plotModel(anova_result)
print("skewnessFrequence:")
summary(anova_result)

# ANOVA-Analyse für varianceFrequence
anova_result <- aov(varianceFrequence ~ Category, data = dataset)
plotModel(anova_result)
print("varianceFrequence:")
summary(anova_result)

# ANOVA-Analyse für energyFrequence
anova_result <- aov(energyFrequence ~ Category, data = dataset)
plotModel(anova_result)
print("energyFrequence")
summary(anova_result)

# ANOVA-Analyse für kurtosisFrequence
anova_result <- aov(kurtosisFrequence ~ Category, data = dataset)
plotModel(anova_result)
print("kurtosisFrequence")
summary(anova_result)


# ANOVA-Analyse für minAmplitude
anova_result <- aov(minAmplitude ~ Category, data = dataset)
plotModel(anova_result)
print("minAmplitude")
summary(anova_result)

# ANOVA-Analyse für maxAmplitude
anova_result <- aov(maxAmplitude ~ Category, data = dataset)
plotModel(anova_result)
print("maxAmplitude")
summary(anova_result)

# ANOVA-Analyse für avgAmplitude
anova_result <- aov(avgAmplitude ~ Category, data = dataset)
plotModel(anova_result)
print("avgAmplitude")
summary(anova_result)

# ANOVA-Analyse für skewnessAmplitude
anova_result <- aov(skewnessAmplitude ~ Category, data = dataset)
plotModel(anova_result)
print("skewnessAmplitude")
summary(anova_result)

# ANOVA-Analyse für varianceAmplitude
anova_result <- aov(varianceAmplitude ~ Category, data = dataset)
plotModel(anova_result)
print("varianceAmplitude:")
summary(anova_result)

# ANOVA-Analyse für energyAmplitude
anova_result <- aov(energyAmplitude ~ Category, data = dataset)
plotModel(anova_result)
print("energyAmplitude:")
summary(anova_result)

# ANOVA-Analyse für kurtosisAmplitude
anova_result <- aov(kurtosisAmplitude ~ Category, data = dataset)
plotModel(anova_result)
print("kurtosisAmplitude")
summary(anova_result)
