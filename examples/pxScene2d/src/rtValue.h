// rtCore CopyRight 2007-2015 John Robinson
// rtValue.h

#ifndef RT_VALUE_H
#define RT_VALUE_H

#include <stdio.h>

#include "rtDefs.h"
#include "rtString.h"

class rtIObject;
class rtIFunction;
class rtObject;
class rtObjectRef;
class rtFunctionRef;

typedef void* voidPtr;

union rtValue_ {
  bool        boolValue;
  int8_t      int8Value;
  uint8_t     uint8Value;
  int32_t     int32Value;
  uint32_t    uint32Value;
  float       floatValue;
  double      doubleValue;
  rtString    *stringValue;
  rtIObject   *objectValue;
  rtIFunction *functionValue;
  voidPtr     voidPtrValue;  // For creating mischief
};

typedef char rtType;

class rtValue {
 public:
  rtValue();
  rtValue(bool v);
  rtValue(int8_t v);
  rtValue(uint8_t v);
  rtValue(int32_t v);
  rtValue(uint32_t v);
  rtValue(float v);
  rtValue(double v);
  rtValue(const char* v);
  rtValue(const rtString& v);
  rtValue(const rtIObject* v);
  rtValue(const rtObjectRef& v);
  rtValue(const rtValue& v);
  rtValue(voidPtr v);

  finline rtValue& operator=(bool v)                { setBool(v);     }
  finline rtValue& operator=(int8_t v)              { setInt8(v);     }
  finline rtValue& operator=(uint8_t v)             { setUInt8(v);    }
  finline rtValue& operator=(int32_t v)             { setInt32(v);    }
  finline rtValue& operator=(uint32_t v)            { setUInt32(v);   }
  finline rtValue& operator=(float v)               { setFloat(v);    }
  finline rtValue& operator=(double v)              { setDouble(v);   }  
  finline rtValue& operator=(rtIObject* v)          { setObject(v);   }
  finline rtValue& operator=(const rtObjectRef& v)  { setObject(v);   }
  finline rtValue& operator=(rtIFunction* v)        { setFunction(v); }
  finline rtValue& operator=(const rtFunctionRef& v){ setFunction(v); }
  finline rtValue& operator=(const rtValue& v)      { setValue(v);    }
  finline rtValue& operator=(voidPtr v)             { setVoidPtr(v);  }

  bool operator!=(const rtValue& rhs) const { return !(*this == rhs); }
  bool operator==(const rtValue& rhs) const;

  void cvt(rtValue& v)                const { getValue(v);    }
  void cvt(bool& v)                   const { getBool(v);     }
  void cvt(int8_t& v)                 const { getInt8(v);     }
  void cvt(uint8_t& v)                const { getUInt8(v);    }
  void cvt(int32_t& v)                const { getInt32(v);    }
  void cvt(uint32_t& v)               const { getUInt32(v);   }
  void cvt(float& v)                  const { getFloat(v);    }
  void cvt(double& v)                 const { getDouble(v);   }
  void cvt(rtString& v)               const { getString(v);   }
  void cvt(rtObjectRef& v)            const { getObject(v);   }
  void cvt(rtFunctionRef& v)          const { getFunction(v); }
  void cvt(voidPtr& v)                const { getVoidPtr(v);  }

  void asn(const rtValue& v)                { setValue(v);    }
  void asn(bool v)                          { setBool(v);     }
  void asn(int8_t v)                        { setInt8(v);     }
  void asn(uint8_t v)                       { setUInt8(v);    }
  void asn(int32_t v)                       { setInt32(v);    }
  void asn(uint32_t v)                      { setUInt32(v);   }
  void asn(float v)                         { setFloat(v);   }
  void asn(double v)                        { setDouble(v);   }
  void asn(const char* v)                   { setString(v);   }
  void asn(const rtString& v)               { setString(v);   }
  void asn(const rtIObject* v)              { setObject(v);   }
  void asn(const rtObjectRef& v)            { setObject(v);   }
  void asn(const rtIFunction* v)            { setFunction(v); }
  void asn(const rtFunctionRef& v)          { setFunction(v); }
  void asn(voidPtr v)                       { setVoidPtr(v);  }

  finline bool       toBool()   const { bool v;        getBool(v);   return v; }
  finline int8_t     toInt8()   const { int8_t v;      getInt8(v);   return v; }
  finline uint8_t    toUInt8()  const { uint8_t v;     getUInt8(v);  return v; }
  finline int32_t    toInt32()  const { int32_t v;     getInt32(v);  return v; }
  finline uint32_t   toUInt32() const { int32_t v;     getInt32(v);  return v; }
  finline float      toFloat() const  { float v;       getFloat(v);  return v; }
  finline double     toDouble() const { double v;      getDouble(v); return v; }
  finline rtString   toString() const { rtString v;    getString(v); return v; }
  //finline rtObjectRef toObject() const { rtObjectRef v; getObject(v); return v; }
  rtObjectRef toObject() const;
  rtFunctionRef toFunction() const;
  voidPtr toVoidPtr() const;

  // TODO rework this so we avoid a copy if the type matches
  template <typename T> 
    T convert() const { T t; cvt(t); return t; }

  template <typename T> 
    void assign(T t) { asn(t); }

  // JRXXX
  rtType getType() const { return mType; }

 public:
  // explicit setters
  void setEmpty();
  void setValue(const rtValue& v);
  void setBool(bool v);
  void setInt8(int8_t v);
  void setUInt8(uint8_t v);
  void setInt32(int32_t v);
  void setUInt32(uint32_t v);
  void setFloat(float v);
  void setDouble(double v);
  void setString(const rtString& v);
  void setObject(const rtIObject* v);
  void setObject(const rtObjectRef& v);
  void setFunction(const rtIFunction* v);
  void setFunction(const rtFunctionRef& v);
  void setVoidPtr(voidPtr v);

  rtError getValue(rtValue& v)          const;
  rtError getBool(bool& v)              const;
  rtError getInt8(int8_t& v)            const;
  rtError getUInt8(uint8_t& v)          const;
  rtError getInt32(int32_t& v)          const;
  rtError getUInt32(uint32_t& v)        const;
  rtError getFloat(float& v)            const;
  rtError getDouble(double& v)          const;
  rtError getString(rtString& v)        const;
  rtError getObject(rtObjectRef& v)     const;
  rtError getFunction(rtFunctionRef& v) const;
  rtError getVoidPtr(voidPtr& v)        const;

  rtError coerceType(rtType newType);

 protected:
  rtType mType;
  rtValue_ mValue;
};

#endif