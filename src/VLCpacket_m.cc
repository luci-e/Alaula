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
    e->insert(VLC_CTRL_MSG, "VLC_CTRL_MSG");
    e->insert(VLC_DATA_MSG, "VLC_DATA_MSG");
    e->insert(VLC_MAC_MSG, "VLC_MAC_MSG");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("VLCctrlCode");
    if (!e) enums.getInstance()->add(e = new cEnum("VLCctrlCode"));
    e->insert(TRANSMISSION_BEGIN, "TRANSMISSION_BEGIN");
    e->insert(TRANSMISSION_END, "TRANSMISSION_END");
    e->insert(TRANSMISSION_ABORT, "TRANSMISSION_ABORT");
    e->insert(DEVICE_BUSY, "DEVICE_BUSY");
    e->insert(DEVICE_MOVED, "DEVICE_MOVED");
    e->insert(NOISE_DEVICE_CHANGED, "NOISE_DEVICE_CHANGED");
    e->insert(ABORT_TRANSMISSION, "ABORT_TRANSMISSION");
    e->insert(VPPM_CYCLE_DOWN, "VPPM_CYCLE_DOWN");
    e->insert(NEW_PACKET, "NEW_PACKET");
    e->insert(CHECK_BEACON, "CHECK_BEACON");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("VLCMACCode");
    if (!e) enums.getInstance()->add(e = new cEnum("VLCMACCode"));
    e->insert(BEACON_MSG, "BEACON_MSG");
    e->insert(SUBSCRIBE_MSG, "SUBSCRIBE_MSG");
    e->insert(UNSUBSCRIBE_MSG, "UNSUBSCRIBE_MSG");
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

Register_Class(VLCctrlMsg);

VLCctrlMsg::VLCctrlMsg(const char *name, int kind) : ::VLCpacket(name,kind)
{
    this->nodeId_var = 0;
    this->nodeAddress_var = 0;
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
    this->nodeId_var = other.nodeId_var;
    this->nodeAddress_var = other.nodeAddress_var;
    this->ctrlCode_var = other.ctrlCode_var;
}

void VLCctrlMsg::parsimPack(cCommBuffer *b)
{
    ::VLCpacket::parsimPack(b);
    doPacking(b,this->nodeId_var);
    doPacking(b,this->nodeAddress_var);
    doPacking(b,this->ctrlCode_var);
}

void VLCctrlMsg::parsimUnpack(cCommBuffer *b)
{
    ::VLCpacket::parsimUnpack(b);
    doUnpacking(b,this->nodeId_var);
    doUnpacking(b,this->nodeAddress_var);
    doUnpacking(b,this->ctrlCode_var);
}

int VLCctrlMsg::getNodeId() const
{
    return nodeId_var;
}

void VLCctrlMsg::setNodeId(int nodeId)
{
    this->nodeId_var = nodeId;
}

int VLCctrlMsg::getNodeAddress() const
{
    return nodeAddress_var;
}

void VLCctrlMsg::setNodeAddress(int nodeAddress)
{
    this->nodeAddress_var = nodeAddress;
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
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
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
        "nodeId",
        "nodeAddress",
        "ctrlCode",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int VLCctrlMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeId")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeAddress")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "ctrlCode")==0) return base+2;
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
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
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
        case 2:
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
        case 0: return long2string(pp->getNodeId());
        case 1: return long2string(pp->getNodeAddress());
        case 2: return long2string(pp->getCtrlCode());
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
        case 0: pp->setNodeId(string2long(value)); return true;
        case 1: pp->setNodeAddress(string2long(value)); return true;
        case 2: pp->setCtrlCode(string2long(value)); return true;
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

Register_Class(VLCnoiseControlMsg);

VLCnoiseControlMsg::VLCnoiseControlMsg(const char *name, int kind) : ::VLCctrlMsg(name,kind)
{
    this->noisePower_var = 0;
}

VLCnoiseControlMsg::VLCnoiseControlMsg(const VLCnoiseControlMsg& other) : ::VLCctrlMsg(other)
{
    copy(other);
}

VLCnoiseControlMsg::~VLCnoiseControlMsg()
{
}

VLCnoiseControlMsg& VLCnoiseControlMsg::operator=(const VLCnoiseControlMsg& other)
{
    if (this==&other) return *this;
    ::VLCctrlMsg::operator=(other);
    copy(other);
    return *this;
}

void VLCnoiseControlMsg::copy(const VLCnoiseControlMsg& other)
{
    this->noisePower_var = other.noisePower_var;
}

void VLCnoiseControlMsg::parsimPack(cCommBuffer *b)
{
    ::VLCctrlMsg::parsimPack(b);
    doPacking(b,this->noisePower_var);
}

void VLCnoiseControlMsg::parsimUnpack(cCommBuffer *b)
{
    ::VLCctrlMsg::parsimUnpack(b);
    doUnpacking(b,this->noisePower_var);
}

double VLCnoiseControlMsg::getNoisePower() const
{
    return noisePower_var;
}

void VLCnoiseControlMsg::setNoisePower(double noisePower)
{
    this->noisePower_var = noisePower;
}

class VLCnoiseControlMsgDescriptor : public cClassDescriptor
{
  public:
    VLCnoiseControlMsgDescriptor();
    virtual ~VLCnoiseControlMsgDescriptor();

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

Register_ClassDescriptor(VLCnoiseControlMsgDescriptor);

VLCnoiseControlMsgDescriptor::VLCnoiseControlMsgDescriptor() : cClassDescriptor("VLCnoiseControlMsg", "VLCctrlMsg")
{
}

VLCnoiseControlMsgDescriptor::~VLCnoiseControlMsgDescriptor()
{
}

bool VLCnoiseControlMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VLCnoiseControlMsg *>(obj)!=NULL;
}

const char *VLCnoiseControlMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VLCnoiseControlMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int VLCnoiseControlMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *VLCnoiseControlMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "noisePower",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int VLCnoiseControlMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "noisePower")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VLCnoiseControlMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "double",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *VLCnoiseControlMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int VLCnoiseControlMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VLCnoiseControlMsg *pp = (VLCnoiseControlMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VLCnoiseControlMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VLCnoiseControlMsg *pp = (VLCnoiseControlMsg *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getNoisePower());
        default: return "";
    }
}

bool VLCnoiseControlMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VLCnoiseControlMsg *pp = (VLCnoiseControlMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setNoisePower(string2double(value)); return true;
        default: return false;
    }
}

const char *VLCnoiseControlMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *VLCnoiseControlMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VLCnoiseControlMsg *pp = (VLCnoiseControlMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(VLCMACMsg);

VLCMACMsg::VLCMACMsg(const char *name, int kind) : ::VLCpacket(name,kind)
{
    this->MACCode_var = 0;
    this->transmitterNodeId_var = 0;
    this->transmitterNodeAddress_var = 0;
    this->receiverNodeIde_var = 0;
    this->receiverNodeAddress_var = 0;
}

VLCMACMsg::VLCMACMsg(const VLCMACMsg& other) : ::VLCpacket(other)
{
    copy(other);
}

VLCMACMsg::~VLCMACMsg()
{
}

VLCMACMsg& VLCMACMsg::operator=(const VLCMACMsg& other)
{
    if (this==&other) return *this;
    ::VLCpacket::operator=(other);
    copy(other);
    return *this;
}

void VLCMACMsg::copy(const VLCMACMsg& other)
{
    this->MACCode_var = other.MACCode_var;
    this->transmitterNodeId_var = other.transmitterNodeId_var;
    this->transmitterNodeAddress_var = other.transmitterNodeAddress_var;
    this->receiverNodeIde_var = other.receiverNodeIde_var;
    this->receiverNodeAddress_var = other.receiverNodeAddress_var;
}

void VLCMACMsg::parsimPack(cCommBuffer *b)
{
    ::VLCpacket::parsimPack(b);
    doPacking(b,this->MACCode_var);
    doPacking(b,this->transmitterNodeId_var);
    doPacking(b,this->transmitterNodeAddress_var);
    doPacking(b,this->receiverNodeIde_var);
    doPacking(b,this->receiverNodeAddress_var);
}

void VLCMACMsg::parsimUnpack(cCommBuffer *b)
{
    ::VLCpacket::parsimUnpack(b);
    doUnpacking(b,this->MACCode_var);
    doUnpacking(b,this->transmitterNodeId_var);
    doUnpacking(b,this->transmitterNodeAddress_var);
    doUnpacking(b,this->receiverNodeIde_var);
    doUnpacking(b,this->receiverNodeAddress_var);
}

int VLCMACMsg::getMACCode() const
{
    return MACCode_var;
}

void VLCMACMsg::setMACCode(int MACCode)
{
    this->MACCode_var = MACCode;
}

int VLCMACMsg::getTransmitterNodeId() const
{
    return transmitterNodeId_var;
}

void VLCMACMsg::setTransmitterNodeId(int transmitterNodeId)
{
    this->transmitterNodeId_var = transmitterNodeId;
}

int VLCMACMsg::getTransmitterNodeAddress() const
{
    return transmitterNodeAddress_var;
}

void VLCMACMsg::setTransmitterNodeAddress(int transmitterNodeAddress)
{
    this->transmitterNodeAddress_var = transmitterNodeAddress;
}

int VLCMACMsg::getReceiverNodeIde() const
{
    return receiverNodeIde_var;
}

void VLCMACMsg::setReceiverNodeIde(int receiverNodeIde)
{
    this->receiverNodeIde_var = receiverNodeIde;
}

int VLCMACMsg::getReceiverNodeAddress() const
{
    return receiverNodeAddress_var;
}

void VLCMACMsg::setReceiverNodeAddress(int receiverNodeAddress)
{
    this->receiverNodeAddress_var = receiverNodeAddress;
}

class VLCMACMsgDescriptor : public cClassDescriptor
{
  public:
    VLCMACMsgDescriptor();
    virtual ~VLCMACMsgDescriptor();

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

Register_ClassDescriptor(VLCMACMsgDescriptor);

VLCMACMsgDescriptor::VLCMACMsgDescriptor() : cClassDescriptor("VLCMACMsg", "VLCpacket")
{
}

VLCMACMsgDescriptor::~VLCMACMsgDescriptor()
{
}

bool VLCMACMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VLCMACMsg *>(obj)!=NULL;
}

const char *VLCMACMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VLCMACMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int VLCMACMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *VLCMACMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "MACCode",
        "transmitterNodeId",
        "transmitterNodeAddress",
        "receiverNodeIde",
        "receiverNodeAddress",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int VLCMACMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='M' && strcmp(fieldName, "MACCode")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "transmitterNodeId")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "transmitterNodeAddress")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "receiverNodeIde")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "receiverNodeAddress")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VLCMACMsgDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *VLCMACMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "VLCMACCode";
            return NULL;
        default: return NULL;
    }
}

int VLCMACMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VLCMACMsg *pp = (VLCMACMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VLCMACMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VLCMACMsg *pp = (VLCMACMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMACCode());
        case 1: return long2string(pp->getTransmitterNodeId());
        case 2: return long2string(pp->getTransmitterNodeAddress());
        case 3: return long2string(pp->getReceiverNodeIde());
        case 4: return long2string(pp->getReceiverNodeAddress());
        default: return "";
    }
}

bool VLCMACMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VLCMACMsg *pp = (VLCMACMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setMACCode(string2long(value)); return true;
        case 1: pp->setTransmitterNodeId(string2long(value)); return true;
        case 2: pp->setTransmitterNodeAddress(string2long(value)); return true;
        case 3: pp->setReceiverNodeIde(string2long(value)); return true;
        case 4: pp->setReceiverNodeAddress(string2long(value)); return true;
        default: return false;
    }
}

const char *VLCMACMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *VLCMACMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VLCMACMsg *pp = (VLCMACMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(VLCBeaconMsg);

VLCBeaconMsg::VLCBeaconMsg(const char *name, int kind) : ::VLCMACMsg(name,kind)
{
    this->modulationType_var = 0;
    this->transmissionPower_var = 0;
    this->modulationOrder_var = 0;
    this->dutyCycle_var = 0;
}

VLCBeaconMsg::VLCBeaconMsg(const VLCBeaconMsg& other) : ::VLCMACMsg(other)
{
    copy(other);
}

VLCBeaconMsg::~VLCBeaconMsg()
{
}

VLCBeaconMsg& VLCBeaconMsg::operator=(const VLCBeaconMsg& other)
{
    if (this==&other) return *this;
    ::VLCMACMsg::operator=(other);
    copy(other);
    return *this;
}

void VLCBeaconMsg::copy(const VLCBeaconMsg& other)
{
    this->modulationType_var = other.modulationType_var;
    this->transmissionPower_var = other.transmissionPower_var;
    this->modulationOrder_var = other.modulationOrder_var;
    this->dutyCycle_var = other.dutyCycle_var;
}

void VLCBeaconMsg::parsimPack(cCommBuffer *b)
{
    ::VLCMACMsg::parsimPack(b);
    doPacking(b,this->modulationType_var);
    doPacking(b,this->transmissionPower_var);
    doPacking(b,this->modulationOrder_var);
    doPacking(b,this->dutyCycle_var);
}

void VLCBeaconMsg::parsimUnpack(cCommBuffer *b)
{
    ::VLCMACMsg::parsimUnpack(b);
    doUnpacking(b,this->modulationType_var);
    doUnpacking(b,this->transmissionPower_var);
    doUnpacking(b,this->modulationOrder_var);
    doUnpacking(b,this->dutyCycle_var);
}

int VLCBeaconMsg::getModulationType() const
{
    return modulationType_var;
}

void VLCBeaconMsg::setModulationType(int modulationType)
{
    this->modulationType_var = modulationType;
}

double VLCBeaconMsg::getTransmissionPower() const
{
    return transmissionPower_var;
}

void VLCBeaconMsg::setTransmissionPower(double transmissionPower)
{
    this->transmissionPower_var = transmissionPower;
}

int VLCBeaconMsg::getModulationOrder() const
{
    return modulationOrder_var;
}

void VLCBeaconMsg::setModulationOrder(int modulationOrder)
{
    this->modulationOrder_var = modulationOrder;
}

double VLCBeaconMsg::getDutyCycle() const
{
    return dutyCycle_var;
}

void VLCBeaconMsg::setDutyCycle(double dutyCycle)
{
    this->dutyCycle_var = dutyCycle;
}

class VLCBeaconMsgDescriptor : public cClassDescriptor
{
  public:
    VLCBeaconMsgDescriptor();
    virtual ~VLCBeaconMsgDescriptor();

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

Register_ClassDescriptor(VLCBeaconMsgDescriptor);

VLCBeaconMsgDescriptor::VLCBeaconMsgDescriptor() : cClassDescriptor("VLCBeaconMsg", "VLCMACMsg")
{
}

VLCBeaconMsgDescriptor::~VLCBeaconMsgDescriptor()
{
}

bool VLCBeaconMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VLCBeaconMsg *>(obj)!=NULL;
}

const char *VLCBeaconMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VLCBeaconMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int VLCBeaconMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *VLCBeaconMsgDescriptor::getFieldName(void *object, int field) const
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
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int VLCBeaconMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "modulationType")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "transmissionPower")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "modulationOrder")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "dutyCycle")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VLCBeaconMsgDescriptor::getFieldTypeString(void *object, int field) const
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
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *VLCBeaconMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int VLCBeaconMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VLCBeaconMsg *pp = (VLCBeaconMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VLCBeaconMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VLCBeaconMsg *pp = (VLCBeaconMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getModulationType());
        case 1: return double2string(pp->getTransmissionPower());
        case 2: return long2string(pp->getModulationOrder());
        case 3: return double2string(pp->getDutyCycle());
        default: return "";
    }
}

bool VLCBeaconMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VLCBeaconMsg *pp = (VLCBeaconMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setModulationType(string2long(value)); return true;
        case 1: pp->setTransmissionPower(string2double(value)); return true;
        case 2: pp->setModulationOrder(string2long(value)); return true;
        case 3: pp->setDutyCycle(string2double(value)); return true;
        default: return false;
    }
}

const char *VLCBeaconMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *VLCBeaconMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VLCBeaconMsg *pp = (VLCBeaconMsg *)object; (void)pp;
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
    this->sourceAddress_var = 0;
    this->destinationAddress_var = 0;
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
    this->sourceAddress_var = other.sourceAddress_var;
    this->destinationAddress_var = other.destinationAddress_var;
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
    doPacking(b,this->sourceAddress_var);
    doPacking(b,this->destinationAddress_var);
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
    doUnpacking(b,this->sourceAddress_var);
    doUnpacking(b,this->destinationAddress_var);
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

int dataPacket::getSourceAddress() const
{
    return sourceAddress_var;
}

void dataPacket::setSourceAddress(int sourceAddress)
{
    this->sourceAddress_var = sourceAddress;
}

int dataPacket::getDestinationAddress() const
{
    return destinationAddress_var;
}

void dataPacket::setDestinationAddress(int destinationAddress)
{
    this->destinationAddress_var = destinationAddress;
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
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
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
        "sourceAddress",
        "destinationAddress",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
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
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceAddress")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationAddress")==0) return base+7;
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
        "int",
        "int",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
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
        case 6: return long2string(pp->getSourceAddress());
        case 7: return long2string(pp->getDestinationAddress());
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
        case 6: pp->setSourceAddress(string2long(value)); return true;
        case 7: pp->setDestinationAddress(string2long(value)); return true;
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


