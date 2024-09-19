#include "DataPoint.h"

DataPoint::DataPoint() : xmls::Serializable()
{
    setClassName("DataPoint");
    Register("Label", &this->label);
    Register("Features", &this->features);
    setVersion("1.0");
}

DataPoint::DataPoint(DataPoint const& dataPoint)
{
    this->label = dataPoint.label;
    this->features = dataPoint.features;

    setClassName("DataPoint");
    Register("Label", &this->label);
    Register("Features", &this->features);
    setVersion("1.0");
}

DataPoint::~DataPoint()
{
    for(int i = 0;i < this->features.size();i++)
    {
        delete this->features.getItem(i);
    }
}

void DataPoint::addFeature(std::vector<double> values)
{
    for(double value : values)
    {
        this->addFeature(value);
    }
}

void DataPoint::addFeature(double value)
{
    DataPointFeature* feature = new DataPointFeature();
    feature->feature = value;
    this->features.addItem(feature);
}

std::vector<double> DataPoint::getFeatures()
{
    std::vector<double> result;

    for(int i = 0;i < this->features.size();i++)
    {
        DataPointFeature* feature = this->features.getItem(i);
        result.push_back(feature->feature.value());
    }

    return result;
}

int const DataPoint::getLabel()
{
    return this->label.value();
}