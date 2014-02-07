//
//  ieObject.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieObject__
#define __ieCore__ieObject__

#include "ieCommon.h"
#include "ieEnums.h"

class ieValue
{
private:
    
protected:
    
    E_VALUE_TYPE m_type;
    union
    {
        bool        m_BOOL;
        i8          m_I8;
        ui8         m_UI8;
        i16         m_I16;
        ui16        m_UI16;
        i32         m_I32;
        ui32        m_UI32;
        f32         m_F32;
    } m_data;
    std::string m_STRING;
    
public:
    
    ieValue(bool value) { m_data.m_BOOL = value; m_type = E_VALUE_TYPE_BOOL; };
    ieValue(i8 value) { m_data.m_I8 = value; m_type = E_VALUE_TYPE_I8; };
    ieValue(ui8 value) { m_data.m_UI8 = value; m_type = E_VALUE_TYPE_UI8; };
    ieValue(i16 value) { m_data.m_I16 = value; m_type = E_VALUE_TYPE_I16; };
    ieValue(ui16 value) { m_data.m_UI16 = value; m_type = E_VALUE_TYPE_UI16; };
    ieValue(i32 value) { m_data.m_I32 = value; m_type = E_VALUE_TYPE_I32; };
    ieValue(ui32 value) { m_data.m_UI32 = value; m_type = E_VALUE_TYPE_UI32; };
    ieValue(f32 value) { m_data.m_F32 = value; m_type = E_VALUE_TYPE_F32; };
    ieValue(const char* value) { m_STRING = value; m_type = E_VALUE_TYPE_STRING; };
    
    E_VALUE_TYPE getType(void);
    bool getBool(void);
    i8 getI8(void);
    ui8 getUI8(void);
    i16 getI16(void);
    ui16 getUI16(void);
    i32 getI32(void);
    ui32 getUI32(void);
    f32 getF32(void);
    std::string getString(void);
};


class ieObject : public std::enable_shared_from_this<ieObject>
{
private:
    
protected:
    
    std::string m_description;
    std::map<std::string, std::shared_ptr<ieObject>> m_objects;
    std::map<std::string, ieValue> m_values;
    
public:
    
    std::string getDescription(void) const;
    
    ieObject(void);
    virtual ~ieObject(void);
    
    void addObjectWithKey(const std::shared_ptr<ieObject>& object, const std::string& key);
    void removeObjectWithKey(const std::string& key);
    void setObjectWithKey(const std::shared_ptr<ieObject>& object, const std::string& key);
    std::shared_ptr<ieObject> getObjectWithKey(const std::string& key);
    
    void addValueWithKey(const ieValue& value, const std::string& key);
    void removeValueWithKey(const std::string& key);
    void setValueWithKey(const ieValue& value, const std::string& key);
    ieValue getValueWithKey(const std::string& key);
};

#endif 
