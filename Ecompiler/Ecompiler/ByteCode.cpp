#include "ByteCode.h"
#include <QFile>


ByteCode::ByteCode(void)
{
	this->stackSize = this->maxStackSize = 0;
	this->assertOnNegativeStack = true;

}

ByteCode& ByteCode::log(const QString& s)
{
	this->_log.append(
		LogLine(this->currentOffset, this->currentOffset, s)
		);
	return *this;
}


ByteCode::~ByteCode(void)
{
	this->code.clear();
	this->_log.clear();
}

bool ByteCode::toFile(const QString& fname)
{
    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly))
        return false;

	file.write( this->code );

	if( !file.flush() )
        return false;

	file.close();
    return true;
}


// инверсия байт //

//* переворот четырёх байт
inline unsigned long int Endian_DWord_Conversion(unsigned long int dword)
{
   return ((dword>>24)&0x000000FF) | ((dword>>8)&0x0000FF00) | ((dword<<8)&0x00FF0000) | ((dword<<24)&0xFF000000);
}

//* переворот двух байт
inline unsigned short int Endian_Word_Conversion(unsigned short int word)
{
   return ((word>>8)&0x00FF) | ((word<<8)&0xFF00);
}


void ByteCode::incStack(int sizeDiff)
{
	this->stackSize += sizeDiff;
	if(this->stackSize > this->maxStackSize)
		this->maxStackSize = this->stackSize;

	if(assertOnNegativeStack && this->stackSize < 0)
	{
		qWarning("/!\\ ByteCode : negative stack size == %d\n 5 last log messages on ByteCode:\n", this->stackSize);
		QStringList l;
		for(int i=1; i<=5; ++i)
		{
			l << this->_log[_log.size()-i] . toString();
		}
		qWarning(l.join("\n").toLocal8Bit());
	}
}


void ByteCode::appendLog(const QList<LogLine>& other_log)
{
	//currentOffset
	QString indent(" ");

	LogLine brace("{");
	this->_log.append(brace);

	foreach(const LogLine& line, other_log)
	{
		this->_log.append(
			LogLine(line.global_pos, line.pos, indent + line.msg)
			);
	}

	brace.msg = "}";
	this->_log.append(brace);
}

ByteCode& ByteCode::append(const ByteCode& other)
{
	this->code.append(other.code);
	this->appendLog(other._log);
	this->incStack(other.stackSize);
	this->gotoEnd();

	return *this;
}


/*inline*/ ByteCode& ByteCode::s1(signed char v)
{
	return this->u1(v);
}
ByteCode& ByteCode::u1(unsigned char v)
{
	this->code.append(v);
	this->currentOffset += 1;
	return *this;
}

ByteCode& ByteCode::u2(unsigned short int v)
{
#ifdef INVERT_INTS
	v = Endian_Word_Conversion(v);
#endif
	
	union {
		unsigned long int u2;
		char b[2];
	} data;

	data.u2 = v;
	this->code.append(data.b[0]);
	this->code.append(data.b[1]);
	this->currentOffset += 2;
	return *this;
}

ByteCode& ByteCode::u4(unsigned long int v)
{
#ifdef INVERT_INTS
	v = Endian_DWord_Conversion(v);
#endif
	
	union {
		unsigned long int u4;
		char b[4];
	} data;

	data.u4 = v;
	this->code.append(data.b[0]);
	this->code.append(data.b[1]);
	this->code.append(data.b[2]);
	this->code.append(data.b[3]);
	this->currentOffset += 4;
	return *this;
}
