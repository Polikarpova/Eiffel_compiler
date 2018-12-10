//включается в тело class ByteCode

ByteCode& iconst_(signed char i) {

	if ( i < -1 || i > 5) {
	
		throw 1;
	}

	this->log(QString("iconst_%1").arg(i));
	this->u1(i+3);
	this->incStack(+1);

	return *this;
}
