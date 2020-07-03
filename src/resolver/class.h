
#define ACC_PUBLIC      	0x0001
#define ACC_PRIVATE     	0x0002
#define ACC_PROTECTED   	0x0004
#define ACC_STATIC      	0x0008
#define ACC_FINAL       	0x0010
#define ACC_SUPER       	0x0020
#define ACC_SYNCHRONIZED	0x0020 
#define ACC_VOLATILE    	0x0040
#define ACC_BRIDGE      	0x0040
#define ACC_TRANSLENT   	0x0080
#define ACC_VARARGS			0x0080 
#define ACC_NATIVE      	0x0100 
#define ACC_INTERFACE   	0x0200
#define ACC_ABSTRACT    	0x0400
#define ACC_STRICT      	0x0800
#define ACC_SYNTHETIC   	0x1000
#define ACC_ANNOTATION  	0x2000
#define ACC_ENUM        	0x4000

typedef struct Class Class;

typedef struct Field Field;

typedef struct Method Method;

typedef struct Exception Exception;

typedef struct Attribute Attribute;

typedef struct ConstUtf8Info {

    u8 tag;

    u16 length;

    byte* bytes;

} ConstUtf8Info;

typedef struct ConstIntegerInfo {

    u8 tag;

    u32 bytes;

} ConstIntegerInfo;

typedef struct ConstFloatInfo {

    u8 tag;

    u32 bytes;

} ConstFloatInfo;

typedef struct ConstLongInfo {

    u8 tag;

    u32 highBytes;

    u32 lowBytes;

} ConstLongInfo;

typedef struct ConstDoubleInfo {

    u8 tag;

    u32 highBytes;

    u32 lowBytes;

} ConstDoubleInfo;

typedef struct ConstClassInfo {

    u8 tag;

    u16 nameIndex;

} ConstClassInfo;

typedef struct ConstStringInfo {

    u8 tag;

    u16 stringIndex;

} ConstStringInfo;

typedef struct ConstFieldRefInfo {

    u8 tag;

    u16 classIndex;

    u16 nameAndTypeIndex;

} ConstFieldRefInfo;

typedef struct ConstMethodRefInfo {

    u8 tag;

    u16 classIndex;

    u16 nameAndTypeIndex;

} ConstMethodRefInfo;

typedef struct ConstInterfaceMethodRefInfo {

    u8 tag;

    u16 classIndex;

    u16 nameAndTypeIndex;

} ConstInterfaceMethodRefInfo;

typedef struct ConstNameAndTypeInfo {

    u8 tag;

    u16 nameIndex;

    u16 descriptorIndex;

} ConstNameAndTypeInfo;

typedef struct ConstMethodHandleInfo {

    u8 tag;

    u8 referenceKind;

    u16 referenceIndex;

} ConstMethodHandleInfo;

typedef struct ConstMethodTypeInfo {

    u8 tag;

    u16 descriptorIndex;

} ConstMethodTypeInfo;

typedef struct ConstInvokeDynamicInfo {

    u8 tag;

    u16 bootstrapMethodAttrIndex;

    u16 nameAndTypeIndex;

} ConstInvokeDynamicInfo;

typedef struct ConstPool {

	u8 type;

	void *value;

} ConstPool;

typedef struct Attribute {
	
	char* attributeName;

	u32	attributeLength;

	byte *data;

} Attribute;

struct Exception {

	u16 startPc;

    u16 endPc;

    u16 handlerPc;

    u16 catchType;
};

struct Field {

	Class *class;

	u16 accessFlags;

	char *fieldName;

	char *descriptor;

	u16 attributeCount;

	Attribute *attributeList;

	u32 constValueIdx;

	u32 slotId;
};

struct Method {

	Class *class;

	u16 accessFlags;

	char *methodName;

	char *descriptor;

	u16 attributeCount;

	Attribute *attributeList;
	
	u32 maxStackSize;

	u32 maxLocalSize;

	u32 codeLength;

	byte *codeData;

	u16 exceptionTableLength;

	Exception *exceptionList;
};

struct Class {

	u32 magic;

	u16 minorVersion;

	u16 majorVersion;

	u16 accessFlags;

	u16 constPoolCount;

	ConstPool *constPool;

	char *className;

	char *superClassName;

	u16 interfaceCount;

	char **interfaceNames;

	u16 fieldCount;

	Field *fieldList;

	u16 methodCount;

	Method *methodList;

	u16 attributeCount;

	Attribute *attributeList;
	
	Class *superClass;

	Class *interfaces;

	bool (*isPublic)(Class *this);

	bool (*isFinal)(Class *this);

	bool (*isSuper)(Class *this);

	bool (*isInterface)(Class *this);

	bool (*isAbstract)(Class *this);

	bool (*isSynthetic)(Class *this);

	bool (*isAnnotation)(Class *this);

	bool (*isEnum)(Class *this);

	ConstPool* (*getConstant)(Class *this, u32 index);

	Field* (*findField)(Class *this, char *fieldName);

	Method* (*findMethod)(Class *this, char *methodName, char *descriptor);

	Method* (*findMainMethod)(Class *this);
};

Class* defineClass(char *classFilename);