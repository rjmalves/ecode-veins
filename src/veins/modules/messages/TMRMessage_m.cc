//
// Generated file, do not edit! Created by nedtool 5.7 from veins/modules/messages/TMRMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "TMRMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace veins {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(TMRMessage)

TMRMessage::TMRMessage(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
    this->senderID = 0;
    this->edgeAverageSpeed = 0;
    this->edgeDensity = 0;
    this->edgeTravelTime = 0;
    this->time = 0;
}

TMRMessage::TMRMessage(const TMRMessage& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

TMRMessage::~TMRMessage()
{
}

TMRMessage& TMRMessage::operator=(const TMRMessage& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void TMRMessage::copy(const TMRMessage& other)
{
    this->senderID = other.senderID;
    this->senderEdge = other.senderEdge;
    this->edgeAverageSpeed = other.edgeAverageSpeed;
    this->edgeDensity = other.edgeDensity;
    this->edgeTravelTime = other.edgeTravelTime;
    this->time = other.time;
}

void TMRMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->senderID);
    doParsimPacking(b,this->senderEdge);
    doParsimPacking(b,this->edgeAverageSpeed);
    doParsimPacking(b,this->edgeDensity);
    doParsimPacking(b,this->edgeTravelTime);
    doParsimPacking(b,this->time);
}

void TMRMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->senderID);
    doParsimUnpacking(b,this->senderEdge);
    doParsimUnpacking(b,this->edgeAverageSpeed);
    doParsimUnpacking(b,this->edgeDensity);
    doParsimUnpacking(b,this->edgeTravelTime);
    doParsimUnpacking(b,this->time);
}

int TMRMessage::getSenderID() const
{
    return this->senderID;
}

void TMRMessage::setSenderID(int senderID)
{
    this->senderID = senderID;
}

const char * TMRMessage::getSenderEdge() const
{
    return this->senderEdge.c_str();
}

void TMRMessage::setSenderEdge(const char * senderEdge)
{
    this->senderEdge = senderEdge;
}

double TMRMessage::getEdgeAverageSpeed() const
{
    return this->edgeAverageSpeed;
}

void TMRMessage::setEdgeAverageSpeed(double edgeAverageSpeed)
{
    this->edgeAverageSpeed = edgeAverageSpeed;
}

double TMRMessage::getEdgeDensity() const
{
    return this->edgeDensity;
}

void TMRMessage::setEdgeDensity(double edgeDensity)
{
    this->edgeDensity = edgeDensity;
}

double TMRMessage::getEdgeTravelTime() const
{
    return this->edgeTravelTime;
}

void TMRMessage::setEdgeTravelTime(double edgeTravelTime)
{
    this->edgeTravelTime = edgeTravelTime;
}

::omnetpp::simtime_t TMRMessage::getTime() const
{
    return this->time;
}

void TMRMessage::setTime(::omnetpp::simtime_t time)
{
    this->time = time;
}

class TMRMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TMRMessageDescriptor();
    virtual ~TMRMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(TMRMessageDescriptor)

TMRMessageDescriptor::TMRMessageDescriptor() : omnetpp::cClassDescriptor("veins::TMRMessage", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

TMRMessageDescriptor::~TMRMessageDescriptor()
{
    delete[] propertynames;
}

bool TMRMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TMRMessage *>(obj)!=nullptr;
}

const char **TMRMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TMRMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TMRMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int TMRMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *TMRMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderID",
        "senderEdge",
        "edgeAverageSpeed",
        "edgeDensity",
        "edgeTravelTime",
        "time",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int TMRMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderID")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderEdge")==0) return base+1;
    if (fieldName[0]=='e' && strcmp(fieldName, "edgeAverageSpeed")==0) return base+2;
    if (fieldName[0]=='e' && strcmp(fieldName, "edgeDensity")==0) return base+3;
    if (fieldName[0]=='e' && strcmp(fieldName, "edgeTravelTime")==0) return base+4;
    if (fieldName[0]=='t' && strcmp(fieldName, "time")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TMRMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
        "double",
        "double",
        "double",
        "simtime_t",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **TMRMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TMRMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TMRMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TMRMessage *pp = (TMRMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *TMRMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TMRMessage *pp = (TMRMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TMRMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TMRMessage *pp = (TMRMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSenderID());
        case 1: return oppstring2string(pp->getSenderEdge());
        case 2: return double2string(pp->getEdgeAverageSpeed());
        case 3: return double2string(pp->getEdgeDensity());
        case 4: return double2string(pp->getEdgeTravelTime());
        case 5: return simtime2string(pp->getTime());
        default: return "";
    }
}

bool TMRMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TMRMessage *pp = (TMRMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setSenderID(string2long(value)); return true;
        case 1: pp->setSenderEdge((value)); return true;
        case 2: pp->setEdgeAverageSpeed(string2double(value)); return true;
        case 3: pp->setEdgeDensity(string2double(value)); return true;
        case 4: pp->setEdgeTravelTime(string2double(value)); return true;
        case 5: pp->setTime(string2simtime(value)); return true;
        default: return false;
    }
}

const char *TMRMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *TMRMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TMRMessage *pp = (TMRMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace veins

