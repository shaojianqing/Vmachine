#include <stdio.h>
#include "../common/constants.h"
#include "../common/commonType.h"
#include "../resolver/resolver.h"

int main(int argc, char **argv) {
	
	if (argc<2) {
		printf("Parameter number not correct!!!\n");
		return 0;	
	}
	
	char *filename = argv[1];
	ClassType *classType = loadClassData(filename);
	printf("Class Magic:					%X\n", classType->magic);
	printf("Class MinorVersion:				%d\n", classType->minorVersion);
	printf("Class majorVersion:				%d\n", classType->majorVersion);
	printf("Class constPoolCount:				%d\n", classType->constPoolCount);
	printf("Class accessFlags:				%d\n", classType->accessFlags);
	printf("Class thisClass:				%d\n", classType->thisClass);
	printf("Class superClass:				%d\n", classType->superClass);
	printf("Class interfaceCount:				%d\n", classType->interfaceCount);
	printf("Class fieldCount:				%d\n", classType->fieldCount);
	printf("Class methodCount:				%d\n", classType->methodCount);
	printf("Class attributeCount:				%d\n", classType->attributeCount);
	printf("Start to print UTF-8 String Value!\n\n");

	u16 constPoolCount = classType->constPoolCount;
	u16 i = 0;
	for (i=1;i<constPoolCount;++i) {
		ConstPool constPool = classType->constPool[i];
		if (constPool.type == CONSTANT_Utf8) {
			ConstUtf8Info *constUtf8Info = (ConstUtf8Info *)constPool.value;
			printf("%i-> UTF-8Info Value:%s\n", i, constUtf8Info->bytes);	
		} else if (constPool.type == CONSTANT_Fieldref) {
			ConstFieldRefInfo *constFieldRefInfo = (ConstFieldRefInfo *)constPool.value;
			printf("%i-> FieldRef classIndex:%i\n", i, constFieldRefInfo->classIndex);
			printf("%i-> FieldRef nameAndTypeIndex:%i\n", i, constFieldRefInfo->nameAndTypeIndex);
		} else if (constPool.type == CONSTANT_Methodref) {
			ConstMethodRefInfo *constMethodRefInfo = (ConstMethodRefInfo *)constPool.value;
			printf("%i-> MethodRef classIndex:%i\n", i, constMethodRefInfo->classIndex);
			printf("%i-> MethodRef nameAndTypeIndex:%i\n", i, constMethodRefInfo->nameAndTypeIndex);
		} else if (constPool.type == CONSTANT_String) {
			ConstStringInfo *constStringInfo = (ConstStringInfo *)constPool.value;
			printf("%i-> StringInfo stringIndex:%i\n", i, constStringInfo->stringIndex);	
		} else if (constPool.type == CONSTANT_NameAndType) {
			ConstNameAndTypeInfo *constNameAndTypeInfo = (ConstNameAndTypeInfo *)constPool.value;
			printf("%i-> NameAndTypeInfo nameIndex:%i\n", i, constNameAndTypeInfo->nameIndex);
			printf("%i-> NameAndTypeInfo descriptorIndex:%i\n", i, 
			constNameAndTypeInfo->descriptorIndex);	
		} else if (constPool.type == CONSTANT_MethodType) {
			ConstMethodTypeInfo *constMethodTypeInfo = (ConstMethodTypeInfo *)constPool.value;
			printf("%i-> MethodTypeInfo descriptorIndex:%i\n", i, 
					constMethodTypeInfo->descriptorIndex);	
		} else if (constPool.type == CONSTANT_Class) {
			ConstClassInfo *constClassInfo = (ConstClassInfo *)constPool.value;
			printf("%i-> ClassInfo nameIndex:%i\n", i, constClassInfo->nameIndex);	
		} else if (constPool.type == CONSTANT_Class) {
			ConstIntegerInfo *constIntegerInfo = (ConstIntegerInfo *)constPool.value;
			printf("%i-> IntegerInfo bytes:%i\n", i, constIntegerInfo->bytes);	
		}
	}

	printf("\nStart to print field info~~\n");
	u16 fieldCount = classType->fieldCount;
	for (i=0;i<fieldCount;++i) {
		FieldInfo field = classType->fieldList[i];
		printf("The Field NameIndex:%i\n", field.nameIndex);
		printf("The Field descriptorIndex:%i\n", field.descriptorIndex);	
		printf("The Field attributeCount:%i\n", field.attributeCount);
		printf("\r\n");			
	}
	
	printf("Start to print method info~~\n");
	u16 methodCount = classType->methodCount;
	for (i=0;i<methodCount;++i) {
		MethodInfo method = classType->methodList[i];
		printf("The Mehtod NameIndex:%i\n", method.nameIndex);
		printf("The Mehtod descriptorIndex:%i\n", method.descriptorIndex);
		printf("The Mehtod attributeCount:%i\n", method.attributeCount);
		u16 k = 0;
		for (k=0;k<method.attributeCount;++k) {
			AttributeInfo attributeInfo = method.attributeList[k];
			printf("The Mehtod AttributeInfo nameIndex:%i\n", attributeInfo.nameIndex);
			printf("The Mehtod AttributeInfo attrLength:%i\n", attributeInfo.attrLength);
			printf("The Mehtod AttributeInfo data:%s\n", attributeInfo.data);
		}
		printf("\r\n");			
	}
}











