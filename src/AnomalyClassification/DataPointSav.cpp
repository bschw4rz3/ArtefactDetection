#include "DataPointSav.h"

DataPointSav::DataPointSav() : xmls::Serializable()
{
    setClassName("DataPoint");
    Register("Label", &this->label);
    Register("Features", &this->features);
    setVersion("1.0");

    this->deleteMembers = false;
}

DataPointSav::DataPointSav(DataPoint dataPoint)
{
    setClassName("DataPoint");
    Register("Label", &this->label);
    Register("Features", &this->features);
    setVersion("1.0");

    this->label = dataPoint.label;
    this->addFeature(dataPoint.features);

    this->deleteMembers = true;
}

DataPointSav::DataPointSav(DataPointSav const& dataPoint)
{
    setClassName("DataPoint");
    Register("Label", &this->label);
    Register("Features", &this->features);
    setVersion("1.0");

    this->label = dataPoint.label;
    this->addFeature(dataPoint.features);

    this->deleteMembers = true;
}

DataPointSav::~DataPointSav()
{
    if(!this->deleteMembers)
    {
        return;
    }

    std::vector<DataPointFeature*> deleteVector;

    for(int i = 0;i < this->features.size();i++)
    {
        deleteVector.push_back(this->features.getItem(i));
    }

    this->features.Clear();

    for(int i = 0;i < deleteVector.size();i++)
    {
        delete deleteVector[i];
    }
}

void DataPointSav::addFeature(std::vector<double> values)
{
    for(double value : values)
    {
        this->addFeature(value);
    }
}

void DataPointSav::addFeature(xmls::Collection<DataPointFeature> list)
{
    for(int i = 0;i < list.size();i++)
    {
        DataPointFeature* value = list.getItem(i);
        this->addFeature(value->feature.value());
    }
}

void DataPointSav::addFeature(double value)
{
    DataPointFeature* feature = new DataPointFeature();
    feature->feature = value;
    this->features.addItem(feature);
}

std::vector<double> DataPointSav::getFeatures()
{
    std::vector<double> result;

    for(int i = 0;i < this->features.size();i++)
    {
        DataPointFeature* feature = this->features.getItem(i);
        result.push_back(feature->feature.value());
    }

    return result;
}

int const DataPointSav::getLabel()
{
    return this->label.value();
}