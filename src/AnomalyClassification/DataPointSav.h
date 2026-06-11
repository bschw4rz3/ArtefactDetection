#ifndef DataPointFeature_H
#define DataPointFeature_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include "DataPoint.h"
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

class DataPointSav : public xmls::Serializable
{
public:
    DataPointSav();
    DataPointSav(DataPoint dp);
    DataPointSav(DataPointSav const & dataPoint);

    ~DataPointSav();

    bool deleteMembers;

    xmls::Collection<DataPointFeature> features; 
    xmls::xInt label;

    void addFeature(double value);
    void addFeature(xmls::Collection<DataPointFeature> list);
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

        this->deleteMembers = false;
    }
    
    DataFile(DataFile const & dataFile) : xmls::Serializable()
    {
        this->dataPoints = dataFile.dataPoints;

        setClassName("DataFile");
        Register("DataPoints", &this->dataPoints);
        setVersion("1.0");
        this->deleteMembers = true;
    }
    
    ~DataFile() 
    {
        if(!this->deleteMembers)
        {
            return;
        }

        std::vector<DataPointSav*> deleteVector;

        for(int i = 0;i < this->dataPoints.size();i++)
        {
            deleteVector.push_back(this->dataPoints.getItem(i));
        }

        this->dataPoints.Clear();

        for(int i = 0;i < deleteVector.size();i++)
        {
            delete deleteVector[i];
        }
    }

    bool deleteMembers;

    xmls::Collection<DataPointSav> dataPoints;

    void addDataPoint(std::vector<DataPointSav> values)
    {
        for(DataPointSav value : values)
        {
            this->addDataPoint(value);
        }
    }

    void addDataPoint(DataPointSav value)
    {
        this->dataPoints.addItem(&value);
    }

    void addDataPoint(std::vector<DataPoint> values)
    {
        for(DataPoint value : values)
        {
            DataPointSav* dp = new DataPointSav(value);
            this->dataPoints.addItem(dp);
        }
    }

    std::vector<DataPoint> toDataPoints()
    {
        std::vector<DataPoint> result;

        for(int i = 0;i < this->dataPoints.size();i++)
        {
            DataPoint dataPoint;
            dataPoint.features = std::vector<double>();
            
            DataPointSav* dataPointSav = this->dataPoints.getItem(i);

            for(int j = 0;j < dataPointSav->features.size();j++)
            {
                DataPointFeature* feature = dataPointSav->features.getItem(j);
                dataPoint.features.push_back(feature->feature.value());
                dataPoint.label = dataPointSav->label.value();
            }

            result.push_back(dataPoint);
        }

        return result;
    }
};

#endif