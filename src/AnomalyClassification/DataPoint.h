#ifndef DataPointFeature_H
#define DataPointFeature_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include "../TinyXML2/XMLSerialization.h"

class DataPointFeature : public xmls::Serializable
{
public:
    DataPointFeature() : xmls::Serializable()
    {
        setClassName("DataPointFeature");
        Register("Feature", &feature);
        setVersion("1.0");
    }

    DataPointFeature(DataPointFeature const & dataPointFeature) : xmls::Serializable()
    {
        this->feature = dataPointFeature.feature;

        setClassName("DataPointFeature");
        Register("Feature", &feature);
        setVersion("1.0");
    }

    xmls::xDouble feature;
};

class DataPoint : public xmls::Serializable
{
public:
    DataPoint();
    DataPoint(DataPoint const & dataPoint);

    ~DataPoint();

    xmls::Collection<DataPointFeature> features; 
    xmls::xInt label;

    void addFeature(double value);
    void addFeature(std::vector<double> values);
    std::vector<double> getFeatures();

    int const getLabel();
};

class DataFile : public xmls::Serializable
{
public:
    DataFile() : xmls::Serializable() { 
        setClassName("DataFile");
        Register("DataPoints", &this->dataPoints);
        setVersion("1.0");
    }
    
    DataFile(DataFile const & dataFile) : xmls::Serializable()
    {
        this->dataPoints = dataFile.dataPoints;

        setClassName("DataFile");
        Register("DataPoints", &this->dataPoints);
        setVersion("1.0");
    }
    
    ~DataFile() { }

    xmls::Collection<DataPoint> dataPoints;

    void addDataPoint(std::vector<DataPoint> values)
    {
        for(DataPoint value : values)
        {
            this->addDataPoint(value);
        }
    }

    void addDataPoint(DataPoint value)
    {
        this->dataPoints.addItem(&value);
    }
};

#endif