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
				break;
			case CLASS_N:
				bc.u2(jc.value.class_const);
				bc.log( QString("type=CONSTANT_Class,  Num CONSTANT_Utf8 =")+bc.CombinedPrint(jc.value.class_const, 2) );
				break;
			case STRING_N:
				break;
			case FIELD_REF:
				break;
			case METHOD_REF:
				break;
			case NAME_AND_TYPE:
				break;
		}
	}

return bc;
}