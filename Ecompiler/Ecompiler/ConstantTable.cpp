#include "JvmConstant.h"

#include "ByteCode.h"

//Таблица констант -> в ByteCode
ByteCode ConstantTable::to_ByteCode(ByteCode & bc) {

	short int constant_pool_count, len;
	JvmConstant jc;

 // формат - ClassFile
	bc.u4(0xCAFEBABE); //magic Java-signature
	bc.u2(0x0000); //minor_version;
	bc.u2(0x0034); //major_version;

	bc.log(QString("Writing Constant_pool ..."));
	constant_pool_count = constants.size() + 1;
 	bc.u2(constant_pool_count); //длина Таблицы констант
	bc.log(QString("constant_pool_count")+bc.CombinedPrint(constant_pool_count, 2));

 //   cp_info constant_pool[constant_pool_count-1];
	for(short int i = 1; i < constant_pool_count;  i++)
	{
		jc = get(i);
		bc.log(QString("Constant N %1").arg(i));
		if(jc.isInvalid) {bc.log(QString("Constant is invalid")); continue;};

		bc.u1(jc.type);
		switch(jc.type)
		{
			case UTF8_VALUE:
				len = jc.value.utf8->length();
				bc.u2(len);
				bc.log( (QString("type=CONSTANT_Utf8,  length=%2  \"").arg(len)) + *(jc.value.utf8)+"\"" );
				bc.appendHere(jc.value.utf8->toLocal8Bit());
				break;
			case INT4_VALUE:
				bc.u4(jc.value.int4);
				bc.log( QString("type=CONSTANT_Integer,  value =")+bc.CombinedPrint(jc.value.int4, 4) );
				break;
			case FLOAT_VALUE:
				bc.u4(jc.value.real);
				bc.log( QString("type=CONSTANT_Float,  value =")+bc.CombinedPrint(jc.value.real, 4) );
				break;
			case CLASS_N:
				bc.u2(jc.value.class_const);
				bc.log( QString("type=CONSTANT_Class,  Num CONSTANT_Utf8 =")+bc.CombinedPrint(jc.value.class_const, 2) );
				break;
			case STRING_N:
				bc.u2(jc.value.string_const);
				bc.log( QString("type=CONSTANT_String,  value =")+bc.CombinedPrint(jc.value.string_const, 2) );
				break;
			case FIELD_REF:
				bc.u2(jc.value.field_ref[CONST_CLASS]);
				bc.u2(jc.value.field_ref[CONST_NAMEnTYPE]);
				bc.log( QString("type=CONSTANT_Fieldref,  Num CONSTANT_Class =")+bc.CombinedPrint(jc.value.field_ref[CONST_CLASS], 2)
					+ QString(",  Num CONSTANT_NameAndType =")+bc.CombinedPrint(jc.value.field_ref[CONST_NAMEnTYPE], 2) );
				break;
			case METHOD_REF:
				bc.u2(jc.value.method_ref[CONST_CLASS]);
				bc.u2(jc.value.method_ref[CONST_NAMEnTYPE]);
				bc.log( QString("type=CONSTANT_Methodref,  Num CONSTANT_Class =")+bc.CombinedPrint(jc.value.method_ref[CONST_CLASS], 2)
					+ QString(",  Num CONSTANT_NameAndType =")+bc.CombinedPrint(jc.value.method_ref[CONST_NAMEnTYPE], 2) );
				break;
			case NAME_AND_TYPE:
				bc.u2(jc.value.name_and_type[UTF8_NAME]);
				bc.u2(jc.value.name_and_type[UTF8_DESCR]);
				bc.log( QString("type=CONSTANT_NameAndType,  Name_CONSTANT_Utf8 =")+bc.CombinedPrint(jc.value.name_and_type[UTF8_NAME], 2)
					+ QString(",  Descriptor_CONSTANT_Utf8 =")+bc.CombinedPrint(jc.value.name_and_type[UTF8_DESCR], 2) );
				break;
		}
	}

return bc;
}