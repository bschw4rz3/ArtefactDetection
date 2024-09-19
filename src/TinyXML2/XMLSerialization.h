/**
 * XML Serialization
 * Simple and lightweight xml serialization class
 * 
 * Original code by Lothar Perr
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely
 */

#ifndef _XML_Serialization_H
#define _XML_Serialization_H

#include <string>
#include <vector>
#include <map>
#include "tinyxml2.h"

using namespace std;

#define RootClassName "SerializableClass"
#define XMLClassEndTag string("</")+RootClassName+">"
#define Empty_String string("")

/**
	XML Serialization
 */
namespace xmls
{
    class Serializable;

    /**
	serializable members base class
     */
    class MemberBase
    {
        protected:
            std::string m_sValue;
        public:
            virtual ~MemberBase() {};
            std::string toString(){return m_sValue;};
            const char* c_str() {return m_sValue.c_str();};
            std::string *getStringPtr() {return &m_sValue;};
    };

    /**
	serializable string
     */
    class xString: public MemberBase
    {
        private:
            void AssignValue(const std::string value){m_sValue=value;};
        public:
            xString(){};
            xString(std::string value) {AssignValue(value);};
            std::string value(){return m_sValue;};
            xString operator=(const std::string value) {AssignValue(value);return *this;};
            xString operator=(const char* value) {AssignValue(value);return *this;};
    };

    /**
    serializable double
     */
    class xDouble: public MemberBase
    {
        private:
            void AssignValue(const double value);
        public:
            xDouble() {AssignValue(0);};
            xDouble(double value) {AssignValue(value);};
            double value();
            xDouble operator=(const double value) {AssignValue(value);return *this;};
    };

    /**
    serializable int
     */
    class xInt: public MemberBase
    {
        private:
            void AssignValue(const int value);
        public:
            xInt() {AssignValue(0);};
            xInt(int value) {AssignValue(value);};
            int value();
            xInt operator=(const int value) {AssignValue(value);return *this;};
    };

    /**
	serializable bool
     */
    class xBool: public MemberBase
    {
        private:
            void AssignValue(const bool value){m_sValue = value ? "true":"false";};
        public:
            xBool() {AssignValue(false);};
            xBool(bool value) {AssignValue(value);};
            bool value();
            xBool operator=(const bool value) {AssignValue(value);return *this;};
    };

    /**
	serializable time_t
     */
    class xTime_t: public MemberBase
    {
        private:
            void AssignValue(const time_t value);
        public:
            xTime_t() {AssignValue(0);};
            xTime_t(time_t value) {AssignValue(value);};
            time_t value();
            xTime_t operator=(const time_t value) {AssignValue(value);return *this;};
    };

    /**
	Member-Field mapping
     */
    class FieldMapping;
    typedef vector<FieldMapping*>::iterator FieldMappingIterator;
    class FieldMapping
    {
        public:
            std::string m_sFieldName;
            std::string *m_sField;
            FieldMapping(std::string FieldName, std::string *Field) {m_sFieldName=FieldName; m_sField=Field;};
            std::string getFieldName(){return m_sFieldName;};
            std::string *getField(){return m_sField;};
    };

    /**
	Member-Class mapping
     */
    class ClassMapping;
    typedef vector<ClassMapping*>::iterator ClassMappingIterator;
    class ClassMapping
    {
        public:
            std::string m_sMemberName;
            Serializable *m_cSubclass;
            ClassMapping(std::string MemberName, Serializable *subclass) {m_sMemberName=MemberName; m_cSubclass=subclass;};
            std::string getName(){return m_sMemberName;};
            Serializable *getSubclass(){return m_cSubclass;};
    };

    /**
	Class-collection base
     */
    class CollectionBase;
    typedef vector<CollectionBase*>::iterator CollectionIterator;
    class CollectionBase
    {
            friend class Serializable;
        private:
            std::string m_sCollectionName;
            std::string m_sCollectionClassType;
        protected:
            CollectionBase() {};
            vector<Serializable*> m_vCollection;
            std::map<Serializable*, bool> m_mOwner;
            void setCollectionName(std::string value) {m_sCollectionName=value;};
            void setCollectionClassType(std::string value) {m_sCollectionClassType=value;};
            std::string getCollectionName(){return m_sCollectionName;};
            virtual Serializable *newElement()=0;
        public:
            virtual ~CollectionBase() {};
            size_t size() {return m_vCollection.size();};
            Serializable *getItem(int itemID) { return m_vCollection.at(itemID);};
            void Clear();
    };

    /**
	Class-collection template
     */
    template <typename T>
    class Collection: public CollectionBase
    {
            friend class Serializable;
        public:
            ~Collection() {Clear();	};
            T *newElement();
            void addItem(T *item) { m_vCollection.push_back(item); m_mOwner[item]=false;};
            T *getItem(int itemID) { return (T*)m_vCollection.at(itemID); };
    };

    /**
	create new element of type T
	@return empty object of type T
     */
    template <typename T>
    T* Collection<T>::newElement()
    {
        T* newItem = new T();
        m_vCollection.push_back(newItem);
        m_mOwner[newItem]=true;
        return newItem;
    };

    /**
	Serializeable base class
	derive your serializable class from Serializable
     */
    typedef vector<Serializable*>::iterator SerializableIterator;
    class Serializable
    {
            friend class CollectionBase;
        private:
            Serializable(Serializable const&) { }
            Serializable operator=(Serializable const&) {return *this;};
            static std::string strReplaceAll(std::string source, const std::string from, const std::string to);
        protected:
            std::string m_sXML;
            std::string m_sClassName;
            std::string m_sVersion;
            vector<FieldMapping*> m_FieldMappings;
            vector<ClassMapping*> m_SubclassMappings;
            vector<CollectionBase*> m_SubclassCollections;
            Serializable();
            virtual ~Serializable();
            void setClassName(std::string ClassName){m_sClassName=ClassName;};
            void Register(std::string MemberName, MemberBase *Member, std::string DefaultValue="");
            void Register(std::string MemberName, Serializable *Member);
            void Register(std::string CollectionName, CollectionBase *SubclassCollection);
            void Serialize(tinyxml2::XMLDocument *classDoc, tinyxml2::XMLElement *rootNode);
            static void Deserialize(Serializable *classItem, tinyxml2::XMLDocument *classDoc, tinyxml2::XMLElement *rootNode);
        public:
            static bool fromXML(std::string XMLSource, Serializable *classObject);
            static std::string IdentifyClass(std::string XMLSource);
            static std::string IdentifyClassVersion(std::string XMLSource);
            std::string getClassName(){return m_sClassName;};
            void setVersion(std::string value) {m_sVersion=value;};
            std::string getVersion() {return m_sVersion;};
            std::string toXML();
            bool Compare(Serializable *messageToCompare);
            static bool Clone(Serializable *source, Serializable *destination);
            bool Copy(Serializable *source);
            void Replace(std::string searchFor, std::string replaceWith, bool recursive=true);
            void Clear();
    };
}

#endif // _XML_Serialization_H


