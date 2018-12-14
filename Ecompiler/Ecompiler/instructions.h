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

