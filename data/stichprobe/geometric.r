install.packages("mosaic")
install.packages("psych")

library(mosaic)
library(psych)

# CSV-Datei einlesen
dataset <- read.csv2("geometricFeature.csv", header=TRUE, sep=";",dec=".")

#Spalten überprüfen
print("Die geladenen Spalten sind:")
print(colnames(dataset))

# ANOVA-Analyse für RoiX
anova_result <- aov(RoiX ~ Class, data = dataset)
plotModel(anova_result)
print("RoiX:")
summary(anova_result)

# ANOVA-Analyse für RoiY
anova_result <- aov(RoiY ~ Class, data = dataset)
plotModel(anova_result)
print("RoiY:")
summary(anova_result)

# ANOVA-Analyse für Area
anova_result <- aov(Area ~ Class, data = dataset)
plotModel(anova_result)
print("Area:")
summary(anova_result)

# ANOVA-Analyse für RatioOfAreaAndROI
anova_result <- aov(RatioOfAreaAndROI ~ Class, data = dataset)
plotModel(anova_result)
print("RatioOfAreaAndROI:")
summary(anova_result)

# ANOVA-Analyse für Slimness
anova_result <- aov(Slimness ~ Class, data = dataset)
plotModel(anova_result)
print("Slimness:")
summary(anova_result)

# ANOVA-Analyse für ScopeOfAnomaly
anova_result <- aov(ScopeOfAnomaly ~ Class, data = dataset)
plotModel(anova_result)
print("ScopeOfAnomaly:")
summary(anova_result)

# ANOVA-Analyse für FocusOfTheAnomalyX
anova_result <- aov(FocusOfTheAnomalyX ~ Class, data = dataset)
plotModel(anova_result)
print("FocusOfTheAnomalyX:")
summary(anova_result)

# ANOVA-Analyse für FocusOfTheAnomalyY
anova_result <- aov(FocusOfTheAnomalyY ~ Class, data = dataset)
plotModel(anova_result)
print("FocusOfTheAnomalyY:")
summary(anova_result)

# ANOVA-Analyse für Rectangularity
anova_result <- aov(Rectangularity ~ Class, data = dataset)
plotModel(anova_result)
print("Rectangularity:")
summary(anova_result)

# ANOVA-Analyse für AnomalyWidth
anova_result <- aov(AnomalyWidth ~ Class, data = dataset)
plotModel(anova_result)
print("AnomalyWidth:")
summary(anova_result)

# ANOVA-Analyse für AnomalyHeight
anova_result <- aov(AnomalyHeight ~ Class, data = dataset)
plotModel(anova_result)
print("AnomalyHeight:")
summary(anova_result)

# ANOVA-Analyse für AnomalyAngle
anova_result <- aov(AnomalyAngle ~ Class, data = dataset)
plotModel(anova_result)
print("AnomalyAngle:")
summary(anova_result)

