//
// Generated file, do not edit! Created by nedtool 5.7 from veins/modules/messages/NRMessage.msg.
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
#include "NRMessage_m.h"

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

Register_Class(NRMessage)

NRMessage::NRMessage(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
    this->numElements = 0;
    for (unsigned int i=0; i<50; i++)
        this->ids[i] = 0;
    for (unsigned int i=0; i<50; i++)
        this->speeds[i] = 0;
    for (unsigned int i=0; i<50; i++)
        this->lanePositions[i] = 0;
    for (unsigned int i=0; i<50; i++)
        this->times[i] = 0;
}

NRMessage::NRMessage(const NRMessage& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

NRMessage::~NRMessage()
{
}

NRMessage& NRMessage::operator=(const NRMessage& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void NRMessage::copy(const NRMessage& other)
{
    this->numElements = other.numElements;
    for (unsigned int i=0; i<50; i++)
        this->ids[i] = other.ids[i];
    for (unsigned int i=0; i<50; i++)
        this->speeds[i] = other.speeds[i];
    for (unsigned int i=0; i<50; i++)
        this->edges[i] = other.edges[i];
    for (unsigned int i=0; i<50; i++)
        this->lanes[i] = other.lanes[i];
    for (unsigned int i=0; i<50; i++)
        this->lanePositions[i] = other.lanePositions[i];
    for (unsigned int i=0; i<50; i++)
        this->destinations[i] = other.destinations[i];
    for (unsigned int i=0; i<50; i++)
        this->times[i] = other.times[i];
}

void NRMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->numElements);
    doParsimArrayPacking(b,this->ids,50);
    doParsimArrayPacking(b,this->speeds,50);
    doParsimArrayPacking(b,this->edges,50);
    doParsimArrayPacking(b,this->lanes,50);
    doParsimArrayPacking(b,this->lanePositions,50);
    doParsimArrayPacking(b,this->destinations,50);
    doParsimArrayPacking(b,this->times,50);
}

void NRMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->numElements);
    doParsimArrayUnpacking(b,this->ids,50);
    doParsimArrayUnpacking(b,this->speeds,50);
    doParsimArrayUnpacking(b,this->edges,50);
    doParsimArrayUnpacking(b,this->lanes,50);
    doParsimArrayUnpacking(b,this->lanePositions,50);
    doParsimArrayUnpacking(b,this->destinations,50);
    doParsimArrayUnpacking(b,this->times,50);
}

int NRMessage::getNumElements() const
{
    return this->numElements;
}

void NRMessage::setNumElements(int numElements)
{
    this->numElements = numElements;
}

unsigned int NRMessage::getIdsArraySize() const
{
    return 50;
}

int NRMessage::getIds(unsigned int k) const
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    return this->ids[k];
}

void NRMessage::setIds(unsigned int k, int ids)
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    this->ids[k] = ids;
}

unsigned int NRMessage::getSpeedsArraySize() const
{
    return 50;
}

double NRMessage::getSpeeds(unsigned int k) const
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    return this->speeds[k];
}

void NRMessage::setSpeeds(unsigned int k, double speeds)
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    this->speeds[k] = speeds;
}

unsigned int NRMessage::getEdgesArraySize() const
{
    return 50;
}

const char * NRMessage::getEdges(unsigned int k) const
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    return this->edges[k].c_str();
}

void NRMessage::setEdges(unsigned int k, const char * edges)
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    this->edges[k] = edges;
}

unsigned int NRMessage::getLanesArraySize() const
{
    return 50;
}

const char * NRMessage::getLanes(unsigned int k) const
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    return this->lanes[k].c_str();
}

void NRMessage::setLanes(unsigned int k, const char * lanes)
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    this->lanes[k] = lanes;
}

unsigned int NRMessage::getLanePositionsArraySize() const
{
    return 50;
}

double NRMessage::getLanePositions(unsigned int k) const
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    return this->lanePositions[k];
}

void NRMessage::setLanePositions(unsigned int k, double lanePositions)
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    this->lanePositions[k] = lanePositions;
}

unsigned int NRMessage::getDestinationsArraySize() const
{
    return 50;
}

const char * NRMessage::getDestinations(unsigned int k) const
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    return this->destinations[k].c_str();
}

void NRMessage::setDestinations(unsigned int k, const char * destinations)
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    this->destinations[k] = destinations;
}

unsigned int NRMessage::getTimesArraySize() const
{
    return 50;
}

::omnetpp::simtime_t NRMessage::getTimes(unsigned int k) const
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    return this->times[k];
}

void NRMessage::setTimes(unsigned int k, ::omnetpp::simtime_t times)
{
    if (k>=50) throw omnetpp::cRuntimeError("Array of size 50 indexed by %lu", (unsigned long)k);
    this->times[k] = times;
}

class NRMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NRMessageDescriptor();
    virtual ~NRMessageDescriptor();

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

Register_ClassDescriptor(NRMessageDescriptor)

NRMessageDescriptor::NRMessageDescriptor() : omnetpp::cClassDescriptor("veins::NRMessage", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

NRMessageDescriptor::~NRMessageDescriptor()
{
    delete[] propertynames;
}

bool NRMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NRMessage *>(obj)!=nullptr;
}

const char **NRMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NRMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NRMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int NRMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *NRMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "numElements",
        "ids",
        "speeds",
        "edges",
        "lanes",
        "lanePositions",
        "destinations",
        "times",
    };
    return (field>=0 && field<8) ? fieldNames[field] : nullptr;
}

int NRMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "numElements")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "ids")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "speeds")==0) return base+2;
    if (fieldName[0]=='e' && strcmp(fieldName, "edges")==0) return base+3;
    if (fieldName[0]=='l' && strcmp(fieldName, "lanes")==0) return base+4;
    if (fieldName[0]=='l' && strcmp(fieldName, "lanePositions")==0) return base+5;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinations")==0) return base+6;
    if (fieldName[0]=='t' && strcmp(fieldName, "times")==0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NRMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "double",
        "string",
        "string",
        "double",
        "string",
        "simtime_t",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : nullptr;
}

const char **NRMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *NRMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NRMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NRMessage *pp = (NRMessage *)object; (void)pp;
    switch (field) {
        case 1: return 50;
        case 2: return 50;
        case 3: return 50;
        case 4: return 50;
        case 5: return 50;
        case 6: return 50;
        case 7: return 50;
        default: return 0;
    }
}

const char *NRMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NRMessage *pp = (NRMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NRMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NRMessage *pp = (NRMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNumElements());
        case 1: return long2string(pp->getIds(i));
        case 2: return double2string(pp->getSpeeds(i));
        case 3: return oppstring2string(pp->getEdges(i));
        case 4: return oppstring2string(pp->getLanes(i));
        case 5: return double2string(pp->getLanePositions(i));
        case 6: return oppstring2string(pp->getDestinations(i));
        case 7: return simtime2string(pp->getTimes(i));
        default: return "";
    }
}

bool NRMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NRMessage *pp = (NRMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setNumElements(string2long(value)); return true;
        case 1: pp->setIds(i,string2long(value)); return true;
        case 2: pp->setSpeeds(i,string2double(value)); return true;
        case 3: pp->setEdges(i,(value)); return true;
        case 4: pp->setLanes(i,(value)); return true;
        case 5: pp->setLanePositions(i,string2double(value)); return true;
        case 6: pp->setDestinations(i,(value)); return true;
        case 7: pp->setTimes(i,string2simtime(value)); return true;
        default: return false;
    }
}

const char *NRMessageDescriptor::getFieldStructName(int field) const
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

void *NRMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NRMessage *pp = (NRMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace veins

