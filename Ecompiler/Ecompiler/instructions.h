//включается в тело class ByteCode

//Функции команд работы со стеком
ByteCode& iconst_(signed char i) {
	if ( i < -1 || i > 5) {	
		throw "Недопустимый параметр iconst_()";
	}
	this->log(QString("iconst_%1").arg(i));
	this->u1(i+3);
	this->incStack(+1);

	return *this;
}
ByteCode& bipush(char s1) {
//	this->log(QString("bipush %1 (0x%2)").arg( (int) s1)  .arg( QString::number(s1,16).right(2).toUpper()) );
	this->log(QString("bipush")+CombinedPrint(s1, 1));
	this->u1(0x10);
	this->u1(s1);
	this->incStack(+1); //размером Единицы Стека_операндов считаем 4 байта

	return *this;
}
ByteCode& sipush(short int s2) {
//	this->log(QString("sipush %1 (0x%2)").arg(s2) .arg(QString::number(s2,16).right(4).toUpper() ));
	this->log(QString("sipush")+CombinedPrint(s2, 2));
	this->u1(0x11);
	this->u2(s2);
	this->incStack(+1);

	return *this;
}
ByteCode& ldc(char u1) {
	this->log(QString("ldc")+CombinedPrint(u1, 1));
	this->u1(0x12);
	this->u1(u1);
	this->incStack(+1);

	return *this;
}
ByteCode& ldc_w(short int u2) {
	this->log(QString("ldc_w")+CombinedPrint(u2, 2));
	this->u1(0x13);
	this->u2(u2);
	this->incStack(+1);

	return *this;
}
ByteCode& iload(char u1) {
	this->log(QString("iload")+CombinedPrint(u1, 1));
	this->u1(0x15);
	this->u1(u1);
	this->incStack(+1);

	return *this;
}
ByteCode& aload(char u1) {
	this->log(QString("aload")+CombinedPrint(u1, 1));
	this->u1(0x19);
	this->u1(u1);
	this->incStack(+1);

	return *this;
}
ByteCode& aload_0 () {
	this->log(QString("aload_0 "));
	this->u1(0x2A);
	this->incStack(+1);

	return *this;
}
ByteCode& aload_1 () {
	this->log(QString("aload_1 "));
	this->u1(0x2B);
	this->incStack(+1);

	return *this;
}
ByteCode& aload_2 () {
	this->log(QString("aload_2 "));
	this->u1(0x2C);
	this->incStack(+1);

	return *this;
}
ByteCode& aload_3 () {
	this->log(QString("aload_3 "));
	this->u1(0x2D);
	this->incStack(+1);

	return *this;
}
ByteCode& istore(char u1) {
	this->log(QString("istore")+CombinedPrint(u1, 1));
	this->u1(0x36);
	this->u1(u1);
	this->incStack(-1);

	return *this;
}
ByteCode& astore(char u1) {
	this->log(QString("astore")+CombinedPrint(u1, 1));
	this->u1(0x3A);
	this->u1(u1);
	this->incStack(-1);

	return *this;
}
ByteCode& astore_0 () {
	this->log(QString("astore_0 "));
	this->u1(0x4B);
	this->incStack(-1);

	return *this;
}
ByteCode& astore_1 () {
	this->log(QString("astore_1 "));
	this->u1(0x4C);
	this->incStack(-1);

	return *this;
}
ByteCode& astore_2 () {
	this->log(QString("astore_2 "));
	this->u1(0x4D);
	this->incStack(-1);

	return *this;
}
ByteCode& astore_3 () {
	this->log(QString("astore_3 "));
	this->u1(0x4E);
	this->incStack(-1);

	return *this;
}
ByteCode& pop() {
	this->log(QString("pop"));
	this->u1(0x57);
	this->incStack(-1);

	return *this;
}
ByteCode& dup() {
	this->log(QString("dup"));
	this->u1(0x59);
	this->incStack(+1);

	return *this;
}
ByteCode& dup2() {
	this->log(QString("dup2"));
	this->u1(0x5C);
	this->incStack(+2);

	return *this;
}

//Функции команд, выполняющих арифметические операции
ByteCode& iadd() {
	this->log(QString("iadd"));
	this->u1(0x60);
	this->incStack(-1);

	return *this;
}
ByteCode& imul() {
	this->log(QString("imul"));
	this->u1(0x68);
	this->incStack(-1);

	return *this;
}
ByteCode& isub() {
	this->log(QString("isub"));
	this->u1(0x64);
	this->incStack(-1);

	return *this;
}
ByteCode& idiv() {
	this->log(QString("idiv"));
	this->u1(0x6C);
	this->incStack(-1);

	return *this;
}
ByteCode& iinc(char u1, signed char i) {
	this->log(QString("iinc")+CombinedPrint(u1, 1)+CombinedPrint(i, 1));
	this->u1(0x84);
	this->u1(u1);
	this->u1(i);

	return *this;
}

//* Функции команд передачи управления
 //** Условный переход если сравнение целых чисел дает истину.
ByteCode& if_icmpeq(short int s2) {
	this->log(QString("if_icmpeq")+CombinedPrint(s2, 2));
	this->u1(0x9F);
	this->u2(s2);
	this->incStack(-2);

	return *this;
}
ByteCode& if_icmpne(short int s2) {
	this->log(QString("if_icmpne")+CombinedPrint(s2, 2));
	this->u1(0xA0);
	this->u2(s2);
	this->incStack(-2);

	return *this;
}
ByteCode& if_icmplt(short int s2) {
	this->log(QString("if_icmplt")+CombinedPrint(s2, 2));
	this->u1(0xA1);
	this->u2(s2);
	this->incStack(-2);

	return *this;
}
ByteCode& if_icmpge(short int s2) {
	this->log(QString("if_icmpge")+CombinedPrint(s2, 2));
	this->u1(0xA2);
	this->u2(s2);
	this->incStack(-2);

	return *this;
}
ByteCode& if_icmpgt(short int s2) {
	this->log(QString("if_icmpgt")+CombinedPrint(s2, 2));
	this->u1(0xA3);
	this->u2(s2);
	this->incStack(-2);

	return *this;
}
ByteCode& if_icmple(short int s2) {
	this->log(QString("if_icmple")+CombinedPrint(s2, 2));
	this->u1(0xA4);
	this->u2(s2);
	this->incStack(-2);

	return *this;
}

 //** Перейти, если сравнение целого числа с нулем дает истину
ByteCode& ifeq(short int s2) {
	this->log(QString("ifeq")+CombinedPrint(s2, 2));
	this->u1(0x99);
	this->u2(s2);
	this->incStack(-1);

	return *this;
}
ByteCode& ifne(short int s2) {
	this->log(QString("ifne")+CombinedPrint(s2, 2));
	this->u1(0x9A);
	this->u2(s2);
	this->incStack(-1);

	return *this;
}
ByteCode& iflt(short int s2) {
	this->log(QString("iflt")+CombinedPrint(s2, 2));
	this->u1(0x55);
	this->u2(s2);
	this->incStack(-1);

	return *this;
}
ByteCode& ifle(short int s2) {
	this->log(QString("ifle")+CombinedPrint(s2, 2));
	this->u1(0x9E);
	this->u2(s2);
	this->incStack(-1);

	return *this;
}
ByteCode& ifgt(short int s2) {
	this->log(QString("ifgt")+CombinedPrint(s2, 2));
	this->u1(0x9D);
	this->u2(s2);
	this->incStack(-1);

	return *this;
}
ByteCode& ifge(short int s2) {
	this->log(QString("ifge")+CombinedPrint(s2, 2));
	this->u1(0x9C);
	this->u2(s2);
	this->incStack(-1);

	return *this;
}
 //** Перейти, если сравнение ссылок верно
ByteCode& if_acmpeq(short int s2) {
	this->log(QString("if_acmpeq")+CombinedPrint(s2, 2));
	this->u1(0xA5);
	this->u2(s2);
	this->incStack(-2);

	return *this;
}
ByteCode& if_acmpne(short int s2) {
	this->log(QString("if_acmpne")+CombinedPrint(s2, 2));
	this->u1(0xA6);
	this->u2(s2);
	this->incStack(-2);

	return *this;
}
 //** Безусловный  переход
ByteCode& goto_(short int s2) {
	this->log(QString("goto_")+CombinedPrint(s2, 2));
	this->u1(0xA7);
	this->u2(s2);

	return *this;
}

//Функции команд работы с массивами
ByteCode& newarray(char u1) {
	this->log(QString("newarray")+CombinedPrint(u1, 1));
	this->u1(0xBC);
	this->u1(u1);

	return *this;
}
ByteCode& anewarray(short int u2) {
	this->log(QString("anewarray")+CombinedPrint(u2, 2));
	this->u1(0xBD);
	this->u2(u2);

	return *this;
}
ByteCode& arraylength() {
	this->log(QString("arraylength"));
	this->u1(0xBE);

	return *this;
}
ByteCode& iaload() {
	this->log(QString("iaload"));
	this->u1(0x2E);
	this->incStack(-1);

	return *this;
}
ByteCode& aaload() {
	this->log(QString("aaload"));
	this->u1(0x32);
	this->incStack(-1);

	return *this;
}
ByteCode& iastore() {
	this->log(QString("iastore"));
	this->u1(0x4F);
	this->incStack(-3);

	return *this;
}
ByteCode& aastore() {
	this->log(QString("aastore"));
	this->u1(0x53);
	this->incStack(-3);

	return *this;
}

//Функции команд работы с объектами
ByteCode& new_(short int u2) {
	this->log(QString("new_")+CombinedPrint(u2, 2));
	this->u1(0xBB);
	this->u2(u2);
	this->incStack(+1);

	return *this;
}
ByteCode& getfield(short int u2) {
	this->log(QString("getfield")+CombinedPrint(u2, 2));
	this->u1(0xB4);
	this->u2(u2);

	return *this;
}
ByteCode& putfield(short int u2) {
	this->log(QString("putfield")+CombinedPrint(u2, 2));
	this->u1(0xB5);
	this->u2(u2);
	this->incStack(-2);

	return *this;
}

//Функции команд работы с методами
ByteCode& invokevirtual(short int u2, short int argCount, bool isVoid) {
	//argCount - кол-во ТОЛЬКО аргументов (this - не входит)
	this->log(QString("invokevirtual")+CombinedPrint(u2, 2));
	this->u1(0xB6);
	this->u2(u2);
	this->incStack(-argCount - (isVoid ? 1 : 0) );

	return *this;
}
ByteCode& invokespecial(short int u2, short int argCount, bool isVoid) {
	//argCount - кол-во ТОЛЬКО аргументов (this - не входит)
	this->log(QString("invokespecial")+CombinedPrint(u2, 2));
	this->u1(0xB7);
	this->u2(u2);
	this->incStack(-argCount - (isVoid ? 1 : 0) );

	return *this;
}
ByteCode& invokestatic(short int u2, short int argCount, bool isVoid) {
	//argCount - кол-во ТОЛЬКО аргументов (this - вообще отсутствует)
	this->log(QString("invokestatic")+CombinedPrint(u2, 2));
	this->u1(0xB8);
	this->u2(u2);
	this->incStack(-(argCount-1) - (isVoid ? 1 : 0) );

	return *this;
}
ByteCode& ireturn() {
	this->log(QString("ireturn"));
	this->u1(0xAC);
	this->incStack(-1);

	return *this;
}
ByteCode& areturn() {
	this->log(QString("areturn"));
	this->u1(0xB0);
	this->incStack(-1);

	return *this;
}
ByteCode& return_() {
	this->log(QString("return_"));
	this->u1(0xB1);

	return *this;
}
