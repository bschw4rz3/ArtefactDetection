#include "kNearestNeighborsService.h"

// Berechnung der euklidischen Distanz zwischen zwei Datenpunkten
double kNearestNeighborsService::euclideanDistance(const std::vector<double>& p1, const std::vector<double>& p2) 
{
    double sum = 0.0;
    for (size_t i = 0; i < p1.size(); i++) {
        sum += pow(p1[i] - p2[i], 2);
    }
    return sqrt(sum);
}

// KNN-Klassifikationsalgorithmus
int kNearestNeighborsService::classifyKNN(const std::vector<DataPoint>& trainingData, const DataPoint& testPoint, int k) 
{
    // Vektor zum Speichern der Distanzen und zugehörigen Labels
    std::vector<std::pair<double, int>> distances;

    // Berechne die euklidische Distanz zu jedem Trainingspunkt
    for (const auto& dataPoint : trainingData) {
        double dist = this->euclideanDistance(testPoint.features, dataPoint.features);
        distances.push_back(std::make_pair(dist, dataPoint.label));
    }

    // Sortiere die Distanzen in aufsteigender Reihenfolge
    std::sort(distances.begin(), distances.end());

    // Zähle die Labels der k-nächsten Nachbarn
    std::map<int, int> labelCounts;
    for (int i = 0; i < k; i++) {
        labelCounts[distances[i].second]++;
    }

    // Finde das häufigste Label unter den k-nächsten Nachbarn
    int majorityLabel = -1;
    int maxCount = 0;
    for (const auto& count : labelCounts) {
        if (count.second > maxCount) {
            maxCount = count.second;
            majorityLabel = count.first;
        }
    }

    return majorityLabel;
}

std::vector<DataPoint> kNearestNeighborsService::classify(std::vector<DataPoint> trainingData, std::vector<std::vector<double>> testData, int k)
{
    std::vector<DataPoint> data;

    for(int i = 0;i < testData.size();i++)
    {
        DataPoint testPoint;
        testPoint.features = testData[i];

        // Klassifikation des Testpunkts
        int predictedLabel = this->classifyKNN(trainingData, testPoint, k);

        DataPoint currentPoint;
        currentPoint.features = testPoint.features;
        currentPoint.label = predictedLabel;

        data.push_back(currentPoint);
    }

    return data;
}