//
// Generated file, do not edit! Created by nedtool 4.6 from src/VLCchannel/VLCchannelMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "VLCchannelMsg_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
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

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(VLCmoveMsg);

VLCmoveMsg::VLCmoveMsg(const char *name, int kind) : ::cMessage(name,kind)
{
    this->nodeId_var = 0;
    this->x_var = 0;
    this->y_var = 0;
    this->z_var = 0;
    this->alpha_var = 0;
    this->beta_var = 0;
}

VLCmoveMsg::VLCmoveMsg(const VLCmoveMsg& other) : ::cMessage(other)
{
    copy(other);
}

VLCmoveMsg::~VLCmoveMsg()
{
}

VLCmoveMsg& VLCmoveMsg::operator=(const VLCmoveMsg& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void VLCmoveMsg::copy(const VLCmoveMsg& other)
{
    this->nodeId_var = other.nodeId_var;
    this->x_var = other.x_var;
    this->y_var = other.y_var;
    this->z_var = other.z_var;
    this->alpha_var = other.alpha_var;
    this->beta_var = other.beta_var;
}

void VLCmoveMsg::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->nodeId_var);
    doPacking(b,this->x_var);
    doPacking(b,this->y_var);
    doPacking(b,this->z_var);
    doPacking(b,this->alpha_var);
    doPacking(b,this->beta_var);
}

void VLCmoveMsg::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->nodeId_var);
    doUnpacking(b,this->x_var);
    doUnpacking(b,this->y_var);
    doUnpacking(b,this->z_var);
    doUnpacking(b,this->alpha_var);
    doUnpacking(b,this->beta_var);
}

int VLCmoveMsg::getNodeId() const
{
    return nodeId_var;
}

void VLCmoveMsg::setNodeId(int nodeId)
{
    this->nodeId_var = nodeId;
}

double VLCmoveMsg::getX() const
{
    return x_var;
}

void VLCmoveMsg::setX(double x)
{
    this->x_var = x;
}

double VLCmoveMsg::getY() const
{
    return y_var;
}

void VLCmoveMsg::setY(double y)
{
    this->y_var = y;
}

double VLCmoveMsg::getZ() const
{
    return z_var;
}

void VLCmoveMsg::setZ(double z)
{
    this->z_var = z;
}

double VLCmoveMsg::getAlpha() const
{
    return alpha_var;
}

void VLCmoveMsg::setAlpha(double alpha)
{
    this->alpha_var = alpha;
}

double VLCmoveMsg::getBeta() const
{
    return beta_var;
}

void VLCmoveMsg::setBeta(double beta)
{
    this->beta_var = beta;
}

class VLCmoveMsgDescriptor : public cClassDescriptor
{
  public:
    VLCmoveMsgDescriptor();
    virtual ~VLCmoveMsgDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(VLCmoveMsgDescriptor);

VLCmoveMsgDescriptor::VLCmoveMsgDescriptor() : cClassDescriptor("VLCmoveMsg", "cMessage")
{
}

VLCmoveMsgDescriptor::~VLCmoveMsgDescriptor()
{
}

bool VLCmoveMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VLCmoveMsg *>(obj)!=NULL;
}

const char *VLCmoveMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VLCmoveMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int VLCmoveMsgDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
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

const char *VLCmoveMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "nodeId",
        "x",
        "y",
        "z",
        "alpha",
        "beta",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int VLCmoveMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeId")==0) return base+0;
    if (fieldName[0]=='x' && strcmp(fieldName, "x")==0) return base+1;
    if (fieldName[0]=='y' && strcmp(fieldName, "y")==0) return base+2;
    if (fieldName[0]=='z' && strcmp(fieldName, "z")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "alpha")==0) return base+4;
    if (fieldName[0]=='b' && strcmp(fieldName, "beta")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VLCmoveMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
        "double",
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *VLCmoveMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int VLCmoveMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VLCmoveMsg *pp = (VLCmoveMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VLCmoveMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VLCmoveMsg *pp = (VLCmoveMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNodeId());
        case 1: return double2string(pp->getX());
        case 2: return double2string(pp->getY());
        case 3: return double2string(pp->getZ());
        case 4: return double2string(pp->getAlpha());
        case 5: return double2string(pp->getBeta());
        default: return "";
    }
}

bool VLCmoveMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VLCmoveMsg *pp = (VLCmoveMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setNodeId(string2long(value)); return true;
        case 1: pp->setX(string2double(value)); return true;
        case 2: pp->setY(string2double(value)); return true;
        case 3: pp->setZ(string2double(value)); return true;
        case 4: pp->setAlpha(string2double(value)); return true;
        case 5: pp->setBeta(string2double(value)); return true;
        default: return false;
    }
}

const char *VLCmoveMsgDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *VLCmoveMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VLCmoveMsg *pp = (VLCmoveMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(VLCchannelSignalBegin);

VLCchannelSignalBegin::VLCchannelSignalBegin(const char *name, int kind) : ::cMessage(name,kind)
{
    this->nodeId_var = 0;
    this->power_var = 0;
    this->carrierFreq_var = 0;
    this->modulationType_var = 0;
}

VLCchannelSignalBegin::VLCchannelSignalBegin(const VLCchannelSignalBegin& other) : ::cMessage(other)
{
    copy(other);
}

VLCchannelSignalBegin::~VLCchannelSignalBegin()
{
}

VLCchannelSignalBegin& VLCchannelSignalBegin::operator=(const VLCchannelSignalBegin& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void VLCchannelSignalBegin::copy(const VLCchannelSignalBegin& other)
{
    this->nodeId_var = other.nodeId_var;
    this->power_var = other.power_var;
    this->carrierFreq_var = other.carrierFreq_var;
    this->modulationType_var = other.modulationType_var;
}

void VLCchannelSignalBegin::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->nodeId_var);
    doPacking(b,this->power_var);
    doPacking(b,this->carrierFreq_var);
    doPacking(b,this->modulationType_var);
}

void VLCchannelSignalBegin::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->nodeId_var);
    doUnpacking(b,this->power_var);
    doUnpacking(b,this->carrierFreq_var);
    doUnpacking(b,this->modulationType_var);
}

int VLCchannelSignalBegin::getNodeId() const
{
    return nodeId_var;
}

void VLCchannelSignalBegin::setNodeId(int nodeId)
{
    this->nodeId_var = nodeId;
}

double VLCchannelSignalBegin::getPower() const
{
    return power_var;
}

void VLCchannelSignalBegin::setPower(double power)
{
    this->power_var = power;
}

double VLCchannelSignalBegin::getCarrierFreq() const
{
    return carrierFreq_var;
}

void VLCchannelSignalBegin::setCarrierFreq(double carrierFreq)
{
    this->carrierFreq_var = carrierFreq;
}

int VLCchannelSignalBegin::getModulationType() const
{
    return modulationType_var;
}

void VLCchannelSignalBegin::setModulationType(int modulationType)
{
    this->modulationType_var = modulationType;
}

class VLCchannelSignalBeginDescriptor : public cClassDescriptor
{
  public:
    VLCchannelSignalBeginDescriptor();
    virtual ~VLCchannelSignalBeginDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(VLCchannelSignalBeginDescriptor);

VLCchannelSignalBeginDescriptor::VLCchannelSignalBeginDescriptor() : cClassDescriptor("VLCchannelSignalBegin", "cMessage")
{
}

VLCchannelSignalBeginDescriptor::~VLCchannelSignalBeginDescriptor()
{
}

bool VLCchannelSignalBeginDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VLCchannelSignalBegin *>(obj)!=NULL;
}

const char *VLCchannelSignalBeginDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VLCchannelSignalBeginDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int VLCchannelSignalBeginDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *VLCchannelSignalBeginDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "nodeId",
        "power",
        "carrierFreq",
        "modulationType",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int VLCchannelSignalBeginDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeId")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "power")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "carrierFreq")==0) return base+2;
    if (fieldName[0]=='m' && strcmp(fieldName, "modulationType")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VLCchannelSignalBeginDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
        "double",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *VLCchannelSignalBeginDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int VLCchannelSignalBeginDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VLCchannelSignalBegin *pp = (VLCchannelSignalBegin *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VLCchannelSignalBeginDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VLCchannelSignalBegin *pp = (VLCchannelSignalBegin *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNodeId());
        case 1: return double2string(pp->getPower());
        case 2: return double2string(pp->getCarrierFreq());
        case 3: return long2string(pp->getModulationType());
        default: return "";
    }
}

bool VLCchannelSignalBeginDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VLCchannelSignalBegin *pp = (VLCchannelSignalBegin *)object; (void)pp;
    switch (field) {
        case 0: pp->setNodeId(string2long(value)); return true;
        case 1: pp->setPower(string2double(value)); return true;
        case 2: pp->setCarrierFreq(string2double(value)); return true;
        case 3: pp->setModulationType(string2long(value)); return true;
        default: return false;
    }
}

const char *VLCchannelSignalBeginDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *VLCchannelSignalBeginDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VLCchannelSignalBegin *pp = (VLCchannelSignalBegin *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(VLCchannelSignalEnd);

VLCchannelSignalEnd::VLCchannelSignalEnd(const char *name, int kind) : ::cMessage(name,kind)
{
    this->nodeId_var = 0;
}

VLCchannelSignalEnd::VLCchannelSignalEnd(const VLCchannelSignalEnd& other) : ::cMessage(other)
{
    copy(other);
}

VLCchannelSignalEnd::~VLCchannelSignalEnd()
{
}

VLCchannelSignalEnd& VLCchannelSignalEnd::operator=(const VLCchannelSignalEnd& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void VLCchannelSignalEnd::copy(const VLCchannelSignalEnd& other)
{
    this->nodeId_var = other.nodeId_var;
}

void VLCchannelSignalEnd::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->nodeId_var);
}

void VLCchannelSignalEnd::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->nodeId_var);
}

int VLCchannelSignalEnd::getNodeId() const
{
    return nodeId_var;
}

void VLCchannelSignalEnd::setNodeId(int nodeId)
{
    this->nodeId_var = nodeId;
}

class VLCchannelSignalEndDescriptor : public cClassDescriptor
{
  public:
    VLCchannelSignalEndDescriptor();
    virtual ~VLCchannelSignalEndDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(VLCchannelSignalEndDescriptor);

VLCchannelSignalEndDescriptor::VLCchannelSignalEndDescriptor() : cClassDescriptor("VLCchannelSignalEnd", "cMessage")
{
}

VLCchannelSignalEndDescriptor::~VLCchannelSignalEndDescriptor()
{
}

bool VLCchannelSignalEndDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VLCchannelSignalEnd *>(obj)!=NULL;
}

const char *VLCchannelSignalEndDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VLCchannelSignalEndDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int VLCchannelSignalEndDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *VLCchannelSignalEndDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "nodeId",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int VLCchannelSignalEndDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeId")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VLCchannelSignalEndDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *VLCchannelSignalEndDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int VLCchannelSignalEndDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VLCchannelSignalEnd *pp = (VLCchannelSignalEnd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VLCchannelSignalEndDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VLCchannelSignalEnd *pp = (VLCchannelSignalEnd *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNodeId());
        default: return "";
    }
}

bool VLCchannelSignalEndDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VLCchannelSignalEnd *pp = (VLCchannelSignalEnd *)object; (void)pp;
    switch (field) {
        case 0: pp->setNodeId(string2long(value)); return true;
        default: return false;
    }
}

const char *VLCchannelSignalEndDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *VLCchannelSignalEndDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VLCchannelSignalEnd *pp = (VLCchannelSignalEnd *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


