//
// Generated file, do not edit! Created by nedtool 4.6 from src/VLCpacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "VLCpacket_m.h"

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

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("VLCmsgType");
    if (!e) enums.getInstance()->add(e = new cEnum("VLCmsgType"));
    e->insert(VLC_MOVE_MSG, "VLC_MOVE_MSG");
    e->insert(VLC_SIG_BEGIN_MSG, "VLC_SIG_BEGIN_MSG");
    e->insert(VLC_SIG_END_MSG, "VLC_SIG_END_MSG");
    e->insert(VLC_CTRL_MSG, "VLC_CTRL_MSG");
    e->insert(VLC_DATA_MSG, "VLC_DATA_MSG");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("VLCctrlCode");
    if (!e) enums.getInstance()->add(e = new cEnum("VLCctrlCode"));
    e->insert(TRANSMISSION_DONE, "TRANSMISSION_DONE");
    e->insert(TRANSMISSION_ABORTED, "TRANSMISSION_ABORTED");
    e->insert(DEVICE_BUSY, "DEVICE_BUSY");
    e->insert(ABORT_TRANSMISSION, "ABORT_TRANSMISSION");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("VLCmodulationType");
    if (!e) enums.getInstance()->add(e = new cEnum("VLCmodulationType"));
    e->insert(PAM, "PAM");
    e->insert(VPPM, "VPPM");
);

Register_Class(VLCpacket);

VLCpacket::VLCpacket(const char *name, int kind) : ::cPacket(name,kind)
{
    this->messageType_var = 0;
}

VLCpacket::VLCpacket(const VLCpacket& other) : ::cPacket(other)
{
    copy(other);
}

VLCpacket::~VLCpacket()
{
}

VLCpacket& VLCpacket::operator=(const VLCpacket& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void VLCpacket::copy(const VLCpacket& other)
{
    this->messageType_var = other.messageType_var;
}

void VLCpacket::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->messageType_var);
}

void VLCpacket::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->messageType_var);
}

int VLCpacket::getMessageType() const
{
    return messageType_var;
}

void VLCpacket::setMessageType(int messageType)
{
    this->messageType_var = messageType;
}

class VLCpacketDescriptor : public cClassDescriptor
{
  public:
    VLCpacketDescriptor();
    virtual ~VLCpacketDescriptor();

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

Register_ClassDescriptor(VLCpacketDescriptor);

VLCpacketDescriptor::VLCpacketDescriptor() : cClassDescriptor("VLCpacket", "cPacket")
{
}

VLCpacketDescriptor::~VLCpacketDescriptor()
{
}

bool VLCpacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VLCpacket *>(obj)!=NULL;
}

const char *VLCpacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VLCpacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int VLCpacketDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *VLCpacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "messageType",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int VLCpacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageType")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VLCpacketDescriptor::getFieldTypeString(void *object, int field) const
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

const char *VLCpacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "VLCmsgType";
            return NULL;
        default: return NULL;
    }
}

int VLCpacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VLCpacket *pp = (VLCpacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VLCpacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VLCpacket *pp = (VLCpacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMessageType());
        default: return "";
    }
}

bool VLCpacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VLCpacket *pp = (VLCpacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setMessageType(string2long(value)); return true;
        default: return false;
    }
}

const char *VLCpacketDescriptor::getFieldStructName(void *object, int field) const
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

void *VLCpacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VLCpacket *pp = (VLCpacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(VLCmoveMsg);

VLCmoveMsg::VLCmoveMsg(const char *name, int kind) : ::VLCpacket(name,kind)
{
    this->nodeId_var = 0;
}

VLCmoveMsg::VLCmoveMsg(const VLCmoveMsg& other) : ::VLCpacket(other)
{
    copy(other);
}

VLCmoveMsg::~VLCmoveMsg()
{
}

VLCmoveMsg& VLCmoveMsg::operator=(const VLCmoveMsg& other)
{
    if (this==&other) return *this;
    ::VLCpacket::operator=(other);
    copy(other);
    return *this;
}

void VLCmoveMsg::copy(const VLCmoveMsg& other)
{
    this->nodeId_var = other.nodeId_var;
}

void VLCmoveMsg::parsimPack(cCommBuffer *b)
{
    ::VLCpacket::parsimPack(b);
    doPacking(b,this->nodeId_var);
}

void VLCmoveMsg::parsimUnpack(cCommBuffer *b)
{
    ::VLCpacket::parsimUnpack(b);
    doUnpacking(b,this->nodeId_var);
}

int VLCmoveMsg::getNodeId() const
{
    return nodeId_var;
}

void VLCmoveMsg::setNodeId(int nodeId)
{
    this->nodeId_var = nodeId;
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

VLCmoveMsgDescriptor::VLCmoveMsgDescriptor() : cClassDescriptor("VLCmoveMsg", "VLCpacket")
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
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
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
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
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
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int VLCmoveMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeId")==0) return base+0;
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
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
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

VLCchannelSignalBegin::VLCchannelSignalBegin(const char *name, int kind) : ::VLCpacket(name,kind)
{
    this->nodeId_var = 0;
}

VLCchannelSignalBegin::VLCchannelSignalBegin(const VLCchannelSignalBegin& other) : ::VLCpacket(other)
{
    copy(other);
}

VLCchannelSignalBegin::~VLCchannelSignalBegin()
{
}

VLCchannelSignalBegin& VLCchannelSignalBegin::operator=(const VLCchannelSignalBegin& other)
{
    if (this==&other) return *this;
    ::VLCpacket::operator=(other);
    copy(other);
    return *this;
}

void VLCchannelSignalBegin::copy(const VLCchannelSignalBegin& other)
{
    this->nodeId_var = other.nodeId_var;
}

void VLCchannelSignalBegin::parsimPack(cCommBuffer *b)
{
    ::VLCpacket::parsimPack(b);
    doPacking(b,this->nodeId_var);
}

void VLCchannelSignalBegin::parsimUnpack(cCommBuffer *b)
{
    ::VLCpacket::parsimUnpack(b);
    doUnpacking(b,this->nodeId_var);
}

int VLCchannelSignalBegin::getNodeId() const
{
    return nodeId_var;
}

void VLCchannelSignalBegin::setNodeId(int nodeId)
{
    this->nodeId_var = nodeId;
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

VLCchannelSignalBeginDescriptor::VLCchannelSignalBeginDescriptor() : cClassDescriptor("VLCchannelSignalBegin", "VLCpacket")
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
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
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
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
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
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int VLCchannelSignalBeginDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeId")==0) return base+0;
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
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
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

VLCchannelSignalEnd::VLCchannelSignalEnd(const char *name, int kind) : ::VLCpacket(name,kind)
{
    this->nodeId_var = 0;
}

VLCchannelSignalEnd::VLCchannelSignalEnd(const VLCchannelSignalEnd& other) : ::VLCpacket(other)
{
    copy(other);
}

VLCchannelSignalEnd::~VLCchannelSignalEnd()
{
}

VLCchannelSignalEnd& VLCchannelSignalEnd::operator=(const VLCchannelSignalEnd& other)
{
    if (this==&other) return *this;
    ::VLCpacket::operator=(other);
    copy(other);
    return *this;
}

void VLCchannelSignalEnd::copy(const VLCchannelSignalEnd& other)
{
    this->nodeId_var = other.nodeId_var;
}

void VLCchannelSignalEnd::parsimPack(cCommBuffer *b)
{
    ::VLCpacket::parsimPack(b);
    doPacking(b,this->nodeId_var);
}

void VLCchannelSignalEnd::parsimUnpack(cCommBuffer *b)
{
    ::VLCpacket::parsimUnpack(b);
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

VLCchannelSignalEndDescriptor::VLCchannelSignalEndDescriptor() : cClassDescriptor("VLCchannelSignalEnd", "VLCpacket")
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

Register_Class(VLCctrlMsg);

VLCctrlMsg::VLCctrlMsg(const char *name, int kind) : ::VLCpacket(name,kind)
{
    this->ctrlCode_var = 0;
}

VLCctrlMsg::VLCctrlMsg(const VLCctrlMsg& other) : ::VLCpacket(other)
{
    copy(other);
}

VLCctrlMsg::~VLCctrlMsg()
{
}

VLCctrlMsg& VLCctrlMsg::operator=(const VLCctrlMsg& other)
{
    if (this==&other) return *this;
    ::VLCpacket::operator=(other);
    copy(other);
    return *this;
}

void VLCctrlMsg::copy(const VLCctrlMsg& other)
{
    this->ctrlCode_var = other.ctrlCode_var;
}

void VLCctrlMsg::parsimPack(cCommBuffer *b)
{
    ::VLCpacket::parsimPack(b);
    doPacking(b,this->ctrlCode_var);
}

void VLCctrlMsg::parsimUnpack(cCommBuffer *b)
{
    ::VLCpacket::parsimUnpack(b);
    doUnpacking(b,this->ctrlCode_var);
}

int VLCctrlMsg::getCtrlCode() const
{
    return ctrlCode_var;
}

void VLCctrlMsg::setCtrlCode(int ctrlCode)
{
    this->ctrlCode_var = ctrlCode;
}

class VLCctrlMsgDescriptor : public cClassDescriptor
{
  public:
    VLCctrlMsgDescriptor();
    virtual ~VLCctrlMsgDescriptor();

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

Register_ClassDescriptor(VLCctrlMsgDescriptor);

VLCctrlMsgDescriptor::VLCctrlMsgDescriptor() : cClassDescriptor("VLCctrlMsg", "VLCpacket")
{
}

VLCctrlMsgDescriptor::~VLCctrlMsgDescriptor()
{
}

bool VLCctrlMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VLCctrlMsg *>(obj)!=NULL;
}

const char *VLCctrlMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VLCctrlMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int VLCctrlMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *VLCctrlMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "ctrlCode",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int VLCctrlMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "ctrlCode")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VLCctrlMsgDescriptor::getFieldTypeString(void *object, int field) const
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

const char *VLCctrlMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "VLCctrlCode";
            return NULL;
        default: return NULL;
    }
}

int VLCctrlMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VLCctrlMsg *pp = (VLCctrlMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VLCctrlMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VLCctrlMsg *pp = (VLCctrlMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCtrlCode());
        default: return "";
    }
}

bool VLCctrlMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VLCctrlMsg *pp = (VLCctrlMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setCtrlCode(string2long(value)); return true;
        default: return false;
    }
}

const char *VLCctrlMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *VLCctrlMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VLCctrlMsg *pp = (VLCctrlMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(dataPacket);

dataPacket::dataPacket(const char *name, int kind) : ::VLCpacket(name,kind)
{
    this->modulationType_var = 0;
    this->transmissionPower_var = 0;
    this->modulationOrder_var = 0;
    this->dutyCycle_var = 0;
    this->content_var = 0;
    this->transmissionStartTime_var = 0;
}

dataPacket::dataPacket(const dataPacket& other) : ::VLCpacket(other)
{
    copy(other);
}

dataPacket::~dataPacket()
{
}

dataPacket& dataPacket::operator=(const dataPacket& other)
{
    if (this==&other) return *this;
    ::VLCpacket::operator=(other);
    copy(other);
    return *this;
}

void dataPacket::copy(const dataPacket& other)
{
    this->modulationType_var = other.modulationType_var;
    this->transmissionPower_var = other.transmissionPower_var;
    this->modulationOrder_var = other.modulationOrder_var;
    this->dutyCycle_var = other.dutyCycle_var;
    this->content_var = other.content_var;
    this->transmissionStartTime_var = other.transmissionStartTime_var;
}

void dataPacket::parsimPack(cCommBuffer *b)
{
    ::VLCpacket::parsimPack(b);
    doPacking(b,this->modulationType_var);
    doPacking(b,this->transmissionPower_var);
    doPacking(b,this->modulationOrder_var);
    doPacking(b,this->dutyCycle_var);
    doPacking(b,this->content_var);
    doPacking(b,this->transmissionStartTime_var);
}

void dataPacket::parsimUnpack(cCommBuffer *b)
{
    ::VLCpacket::parsimUnpack(b);
    doUnpacking(b,this->modulationType_var);
    doUnpacking(b,this->transmissionPower_var);
    doUnpacking(b,this->modulationOrder_var);
    doUnpacking(b,this->dutyCycle_var);
    doUnpacking(b,this->content_var);
    doUnpacking(b,this->transmissionStartTime_var);
}

int dataPacket::getModulationType() const
{
    return modulationType_var;
}

void dataPacket::setModulationType(int modulationType)
{
    this->modulationType_var = modulationType;
}

double dataPacket::getTransmissionPower() const
{
    return transmissionPower_var;
}

void dataPacket::setTransmissionPower(double transmissionPower)
{
    this->transmissionPower_var = transmissionPower;
}

int dataPacket::getModulationOrder() const
{
    return modulationOrder_var;
}

void dataPacket::setModulationOrder(int modulationOrder)
{
    this->modulationOrder_var = modulationOrder;
}

double dataPacket::getDutyCycle() const
{
    return dutyCycle_var;
}

void dataPacket::setDutyCycle(double dutyCycle)
{
    this->dutyCycle_var = dutyCycle;
}

const char * dataPacket::getContent() const
{
    return content_var.c_str();
}

void dataPacket::setContent(const char * content)
{
    this->content_var = content;
}

double dataPacket::getTransmissionStartTime() const
{
    return transmissionStartTime_var;
}

void dataPacket::setTransmissionStartTime(double transmissionStartTime)
{
    this->transmissionStartTime_var = transmissionStartTime;
}

class dataPacketDescriptor : public cClassDescriptor
{
  public:
    dataPacketDescriptor();
    virtual ~dataPacketDescriptor();

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

Register_ClassDescriptor(dataPacketDescriptor);

dataPacketDescriptor::dataPacketDescriptor() : cClassDescriptor("dataPacket", "VLCpacket")
{
}

dataPacketDescriptor::~dataPacketDescriptor()
{
}

bool dataPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<dataPacket *>(obj)!=NULL;
}

const char *dataPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int dataPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int dataPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *dataPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "modulationType",
        "transmissionPower",
        "modulationOrder",
        "dutyCycle",
        "content",
        "transmissionStartTime",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int dataPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "modulationType")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "transmissionPower")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "modulationOrder")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "dutyCycle")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "content")==0) return base+4;
    if (fieldName[0]=='t' && strcmp(fieldName, "transmissionStartTime")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *dataPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
        "double",
        "string",
        "double",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *dataPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "VLCmodulationType";
            return NULL;
        default: return NULL;
    }
}

int dataPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    dataPacket *pp = (dataPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string dataPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    dataPacket *pp = (dataPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getModulationType());
        case 1: return double2string(pp->getTransmissionPower());
        case 2: return long2string(pp->getModulationOrder());
        case 3: return double2string(pp->getDutyCycle());
        case 4: return oppstring2string(pp->getContent());
        case 5: return double2string(pp->getTransmissionStartTime());
        default: return "";
    }
}

bool dataPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    dataPacket *pp = (dataPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setModulationType(string2long(value)); return true;
        case 1: pp->setTransmissionPower(string2double(value)); return true;
        case 2: pp->setModulationOrder(string2long(value)); return true;
        case 3: pp->setDutyCycle(string2double(value)); return true;
        case 4: pp->setContent((value)); return true;
        case 5: pp->setTransmissionStartTime(string2double(value)); return true;
        default: return false;
    }
}

const char *dataPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *dataPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    dataPacket *pp = (dataPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


