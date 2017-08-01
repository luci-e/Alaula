//
// Generated file, do not edit! Created by nedtool 4.6 from src/VLCnode/VLCmobilityManager/VLCmobilityMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "VLCmobilityMsg_m.h"

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

Register_Class(VLCupdateMovMsg);

VLCupdateMovMsg::VLCupdateMovMsg(const char *name, int kind) : ::cMessage(name,kind)
{
    this->type_var = 0;
}

VLCupdateMovMsg::VLCupdateMovMsg(const VLCupdateMovMsg& other) : ::cMessage(other)
{
    copy(other);
}

VLCupdateMovMsg::~VLCupdateMovMsg()
{
}

VLCupdateMovMsg& VLCupdateMovMsg::operator=(const VLCupdateMovMsg& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void VLCupdateMovMsg::copy(const VLCupdateMovMsg& other)
{
    this->type_var = other.type_var;
}

void VLCupdateMovMsg::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->type_var);
}

void VLCupdateMovMsg::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->type_var);
}

int VLCupdateMovMsg::getType() const
{
    return type_var;
}

void VLCupdateMovMsg::setType(int type)
{
    this->type_var = type;
}

class VLCupdateMovMsgDescriptor : public cClassDescriptor
{
  public:
    VLCupdateMovMsgDescriptor();
    virtual ~VLCupdateMovMsgDescriptor();

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

Register_ClassDescriptor(VLCupdateMovMsgDescriptor);

VLCupdateMovMsgDescriptor::VLCupdateMovMsgDescriptor() : cClassDescriptor("VLCupdateMovMsg", "cMessage")
{
}

VLCupdateMovMsgDescriptor::~VLCupdateMovMsgDescriptor()
{
}

bool VLCupdateMovMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VLCupdateMovMsg *>(obj)!=NULL;
}

const char *VLCupdateMovMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VLCupdateMovMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int VLCupdateMovMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *VLCupdateMovMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int VLCupdateMovMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VLCupdateMovMsgDescriptor::getFieldTypeString(void *object, int field) const
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

const char *VLCupdateMovMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int VLCupdateMovMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VLCupdateMovMsg *pp = (VLCupdateMovMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VLCupdateMovMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VLCupdateMovMsg *pp = (VLCupdateMovMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        default: return "";
    }
}

bool VLCupdateMovMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VLCupdateMovMsg *pp = (VLCupdateMovMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        default: return false;
    }
}

const char *VLCupdateMovMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *VLCupdateMovMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VLCupdateMovMsg *pp = (VLCupdateMovMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(VLCmoveTargetMsg);

VLCmoveTargetMsg::VLCmoveTargetMsg(const char *name, int kind) : ::cMessage(name,kind)
{
    this->x_var = 0;
    this->y_var = 0;
    this->z_var = 0;
    this->speed_var = 0;
}

VLCmoveTargetMsg::VLCmoveTargetMsg(const VLCmoveTargetMsg& other) : ::cMessage(other)
{
    copy(other);
}

VLCmoveTargetMsg::~VLCmoveTargetMsg()
{
}

VLCmoveTargetMsg& VLCmoveTargetMsg::operator=(const VLCmoveTargetMsg& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void VLCmoveTargetMsg::copy(const VLCmoveTargetMsg& other)
{
    this->x_var = other.x_var;
    this->y_var = other.y_var;
    this->z_var = other.z_var;
    this->speed_var = other.speed_var;
}

void VLCmoveTargetMsg::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->x_var);
    doPacking(b,this->y_var);
    doPacking(b,this->z_var);
    doPacking(b,this->speed_var);
}

void VLCmoveTargetMsg::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->x_var);
    doUnpacking(b,this->y_var);
    doUnpacking(b,this->z_var);
    doUnpacking(b,this->speed_var);
}

double VLCmoveTargetMsg::getX() const
{
    return x_var;
}

void VLCmoveTargetMsg::setX(double x)
{
    this->x_var = x;
}

double VLCmoveTargetMsg::getY() const
{
    return y_var;
}

void VLCmoveTargetMsg::setY(double y)
{
    this->y_var = y;
}

double VLCmoveTargetMsg::getZ() const
{
    return z_var;
}

void VLCmoveTargetMsg::setZ(double z)
{
    this->z_var = z;
}

double VLCmoveTargetMsg::getSpeed() const
{
    return speed_var;
}

void VLCmoveTargetMsg::setSpeed(double speed)
{
    this->speed_var = speed;
}

class VLCmoveTargetMsgDescriptor : public cClassDescriptor
{
  public:
    VLCmoveTargetMsgDescriptor();
    virtual ~VLCmoveTargetMsgDescriptor();

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

Register_ClassDescriptor(VLCmoveTargetMsgDescriptor);

VLCmoveTargetMsgDescriptor::VLCmoveTargetMsgDescriptor() : cClassDescriptor("VLCmoveTargetMsg", "cMessage")
{
}

VLCmoveTargetMsgDescriptor::~VLCmoveTargetMsgDescriptor()
{
}

bool VLCmoveTargetMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VLCmoveTargetMsg *>(obj)!=NULL;
}

const char *VLCmoveTargetMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VLCmoveTargetMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int VLCmoveTargetMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *VLCmoveTargetMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "x",
        "y",
        "z",
        "speed",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int VLCmoveTargetMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='x' && strcmp(fieldName, "x")==0) return base+0;
    if (fieldName[0]=='y' && strcmp(fieldName, "y")==0) return base+1;
    if (fieldName[0]=='z' && strcmp(fieldName, "z")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "speed")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VLCmoveTargetMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *VLCmoveTargetMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int VLCmoveTargetMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VLCmoveTargetMsg *pp = (VLCmoveTargetMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VLCmoveTargetMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VLCmoveTargetMsg *pp = (VLCmoveTargetMsg *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getX());
        case 1: return double2string(pp->getY());
        case 2: return double2string(pp->getZ());
        case 3: return double2string(pp->getSpeed());
        default: return "";
    }
}

bool VLCmoveTargetMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VLCmoveTargetMsg *pp = (VLCmoveTargetMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setX(string2double(value)); return true;
        case 1: pp->setY(string2double(value)); return true;
        case 2: pp->setZ(string2double(value)); return true;
        case 3: pp->setSpeed(string2double(value)); return true;
        default: return false;
    }
}

const char *VLCmoveTargetMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *VLCmoveTargetMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VLCmoveTargetMsg *pp = (VLCmoveTargetMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(VLCrotateTargetMsg);

VLCrotateTargetMsg::VLCrotateTargetMsg(const char *name, int kind) : ::cMessage(name,kind)
{
    this->alpha_var = 0;
    this->beta_var = 0;
    this->speed_var = 0;
}

VLCrotateTargetMsg::VLCrotateTargetMsg(const VLCrotateTargetMsg& other) : ::cMessage(other)
{
    copy(other);
}

VLCrotateTargetMsg::~VLCrotateTargetMsg()
{
}

VLCrotateTargetMsg& VLCrotateTargetMsg::operator=(const VLCrotateTargetMsg& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void VLCrotateTargetMsg::copy(const VLCrotateTargetMsg& other)
{
    this->alpha_var = other.alpha_var;
    this->beta_var = other.beta_var;
    this->speed_var = other.speed_var;
}

void VLCrotateTargetMsg::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->alpha_var);
    doPacking(b,this->beta_var);
    doPacking(b,this->speed_var);
}

void VLCrotateTargetMsg::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->alpha_var);
    doUnpacking(b,this->beta_var);
    doUnpacking(b,this->speed_var);
}

double VLCrotateTargetMsg::getAlpha() const
{
    return alpha_var;
}

void VLCrotateTargetMsg::setAlpha(double alpha)
{
    this->alpha_var = alpha;
}

double VLCrotateTargetMsg::getBeta() const
{
    return beta_var;
}

void VLCrotateTargetMsg::setBeta(double beta)
{
    this->beta_var = beta;
}

double VLCrotateTargetMsg::getSpeed() const
{
    return speed_var;
}

void VLCrotateTargetMsg::setSpeed(double speed)
{
    this->speed_var = speed;
}

class VLCrotateTargetMsgDescriptor : public cClassDescriptor
{
  public:
    VLCrotateTargetMsgDescriptor();
    virtual ~VLCrotateTargetMsgDescriptor();

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

Register_ClassDescriptor(VLCrotateTargetMsgDescriptor);

VLCrotateTargetMsgDescriptor::VLCrotateTargetMsgDescriptor() : cClassDescriptor("VLCrotateTargetMsg", "cMessage")
{
}

VLCrotateTargetMsgDescriptor::~VLCrotateTargetMsgDescriptor()
{
}

bool VLCrotateTargetMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VLCrotateTargetMsg *>(obj)!=NULL;
}

const char *VLCrotateTargetMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VLCrotateTargetMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int VLCrotateTargetMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *VLCrotateTargetMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "alpha",
        "beta",
        "speed",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int VLCrotateTargetMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "alpha")==0) return base+0;
    if (fieldName[0]=='b' && strcmp(fieldName, "beta")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "speed")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VLCrotateTargetMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *VLCrotateTargetMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int VLCrotateTargetMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VLCrotateTargetMsg *pp = (VLCrotateTargetMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VLCrotateTargetMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VLCrotateTargetMsg *pp = (VLCrotateTargetMsg *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getAlpha());
        case 1: return double2string(pp->getBeta());
        case 2: return double2string(pp->getSpeed());
        default: return "";
    }
}

bool VLCrotateTargetMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VLCrotateTargetMsg *pp = (VLCrotateTargetMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setAlpha(string2double(value)); return true;
        case 1: pp->setBeta(string2double(value)); return true;
        case 2: pp->setSpeed(string2double(value)); return true;
        default: return false;
    }
}

const char *VLCrotateTargetMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *VLCrotateTargetMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VLCrotateTargetMsg *pp = (VLCrotateTargetMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


