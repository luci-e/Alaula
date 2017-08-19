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

Register_Class(VLCchannelMsg);

VLCchannelMsg::VLCchannelMsg(const char *name, int kind) : ::cPacket(name,kind)
{
    this->messageType_var = 0;
    this->nodeId_var = 0;
}

VLCchannelMsg::VLCchannelMsg(const VLCchannelMsg& other) : ::cPacket(other)
{
    copy(other);
}

VLCchannelMsg::~VLCchannelMsg()
{
}

VLCchannelMsg& VLCchannelMsg::operator=(const VLCchannelMsg& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void VLCchannelMsg::copy(const VLCchannelMsg& other)
{
    this->messageType_var = other.messageType_var;
    this->nodeId_var = other.nodeId_var;
}

void VLCchannelMsg::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->messageType_var);
    doPacking(b,this->nodeId_var);
}

void VLCchannelMsg::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->messageType_var);
    doUnpacking(b,this->nodeId_var);
}

int VLCchannelMsg::getMessageType() const
{
    return messageType_var;
}

void VLCchannelMsg::setMessageType(int messageType)
{
    this->messageType_var = messageType;
}

int VLCchannelMsg::getNodeId() const
{
    return nodeId_var;
}

void VLCchannelMsg::setNodeId(int nodeId)
{
    this->nodeId_var = nodeId;
}

class VLCchannelMsgDescriptor : public cClassDescriptor
{
  public:
    VLCchannelMsgDescriptor();
    virtual ~VLCchannelMsgDescriptor();

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

Register_ClassDescriptor(VLCchannelMsgDescriptor);

VLCchannelMsgDescriptor::VLCchannelMsgDescriptor() : cClassDescriptor("VLCchannelMsg", "cPacket")
{
}

VLCchannelMsgDescriptor::~VLCchannelMsgDescriptor()
{
}

bool VLCchannelMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VLCchannelMsg *>(obj)!=NULL;
}

const char *VLCchannelMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VLCchannelMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int VLCchannelMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *VLCchannelMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "messageType",
        "nodeId",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int VLCchannelMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageType")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeId")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VLCchannelMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *VLCchannelMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int VLCchannelMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VLCchannelMsg *pp = (VLCchannelMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VLCchannelMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VLCchannelMsg *pp = (VLCchannelMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMessageType());
        case 1: return long2string(pp->getNodeId());
        default: return "";
    }
}

bool VLCchannelMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VLCchannelMsg *pp = (VLCchannelMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setMessageType(string2long(value)); return true;
        case 1: pp->setNodeId(string2long(value)); return true;
        default: return false;
    }
}

const char *VLCchannelMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *VLCchannelMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VLCchannelMsg *pp = (VLCchannelMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(VLCmoveMsg);

VLCmoveMsg::VLCmoveMsg(const char *name, int kind) : ::VLCchannelMsg(name,kind)
{
}

VLCmoveMsg::VLCmoveMsg(const VLCmoveMsg& other) : ::VLCchannelMsg(other)
{
    copy(other);
}

VLCmoveMsg::~VLCmoveMsg()
{
}

VLCmoveMsg& VLCmoveMsg::operator=(const VLCmoveMsg& other)
{
    if (this==&other) return *this;
    ::VLCchannelMsg::operator=(other);
    copy(other);
    return *this;
}

void VLCmoveMsg::copy(const VLCmoveMsg& other)
{
}

void VLCmoveMsg::parsimPack(cCommBuffer *b)
{
    ::VLCchannelMsg::parsimPack(b);
}

void VLCmoveMsg::parsimUnpack(cCommBuffer *b)
{
    ::VLCchannelMsg::parsimUnpack(b);
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

VLCmoveMsgDescriptor::VLCmoveMsgDescriptor() : cClassDescriptor("VLCmoveMsg", "VLCchannelMsg")
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
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int VLCmoveMsgDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *VLCmoveMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int VLCmoveMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
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
    return NULL;
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
    return NULL;
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

VLCchannelSignalBegin::VLCchannelSignalBegin(const char *name, int kind) : ::VLCchannelMsg(name,kind)
{
}

VLCchannelSignalBegin::VLCchannelSignalBegin(const VLCchannelSignalBegin& other) : ::VLCchannelMsg(other)
{
    copy(other);
}

VLCchannelSignalBegin::~VLCchannelSignalBegin()
{
}

VLCchannelSignalBegin& VLCchannelSignalBegin::operator=(const VLCchannelSignalBegin& other)
{
    if (this==&other) return *this;
    ::VLCchannelMsg::operator=(other);
    copy(other);
    return *this;
}

void VLCchannelSignalBegin::copy(const VLCchannelSignalBegin& other)
{
}

void VLCchannelSignalBegin::parsimPack(cCommBuffer *b)
{
    ::VLCchannelMsg::parsimPack(b);
}

void VLCchannelSignalBegin::parsimUnpack(cCommBuffer *b)
{
    ::VLCchannelMsg::parsimUnpack(b);
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

VLCchannelSignalBeginDescriptor::VLCchannelSignalBeginDescriptor() : cClassDescriptor("VLCchannelSignalBegin", "VLCchannelMsg")
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
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int VLCchannelSignalBeginDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *VLCchannelSignalBeginDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int VLCchannelSignalBeginDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
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
    return NULL;
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
    return NULL;
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

VLCchannelSignalEnd::VLCchannelSignalEnd(const char *name, int kind) : ::VLCchannelMsg(name,kind)
{
}

VLCchannelSignalEnd::VLCchannelSignalEnd(const VLCchannelSignalEnd& other) : ::VLCchannelMsg(other)
{
    copy(other);
}

VLCchannelSignalEnd::~VLCchannelSignalEnd()
{
}

VLCchannelSignalEnd& VLCchannelSignalEnd::operator=(const VLCchannelSignalEnd& other)
{
    if (this==&other) return *this;
    ::VLCchannelMsg::operator=(other);
    copy(other);
    return *this;
}

void VLCchannelSignalEnd::copy(const VLCchannelSignalEnd& other)
{
}

void VLCchannelSignalEnd::parsimPack(cCommBuffer *b)
{
    ::VLCchannelMsg::parsimPack(b);
}

void VLCchannelSignalEnd::parsimUnpack(cCommBuffer *b)
{
    ::VLCchannelMsg::parsimUnpack(b);
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

VLCchannelSignalEndDescriptor::VLCchannelSignalEndDescriptor() : cClassDescriptor("VLCchannelSignalEnd", "VLCchannelMsg")
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
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int VLCchannelSignalEndDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *VLCchannelSignalEndDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int VLCchannelSignalEndDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
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
    return NULL;
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
    return NULL;
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


