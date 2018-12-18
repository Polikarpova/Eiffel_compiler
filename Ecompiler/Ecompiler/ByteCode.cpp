#include "ByteCode.h"
#include <QFile>
#include <QStringList>

//* convert to string
QString LogLine::toString() const {
	QString formatted;
	if(this->pos > -1)
	{
		formatted = QString("%1 | ").arg(QString::number(this->pos));
	}
	if(this->global_pos > -1 && this->global_pos != this->pos)
	{
		formatted = QString("%1:%2").arg(QString::number(this->global_pos), formatted);
	}
	QString& trimmed = this->msg.trimmed();
	formatted += trimmed;
	 int indents = this->msg.size() - trimmed.size();
	 if(indents > 0)
		 formatted.prepend(QString(indents, ' ' ));
	return formatted;
}


ByteCode::ByteCode(void)
{
	this->currentOffset = 0;
	this->stackSize = this->maxStackSize = 0;
	this->assertOnNegativeStack = true;
}

ByteCode::~ByteCode(void)
{
	this->codeStream.clear();
	this->_log.clear();
}

ByteCode& ByteCode::log(const QString& s)
{
	this->_log.append(
		LogLine(this->currentOffset, this->currentOffset, s)
		);
	return *this;
}
void ByteCode::printLog()
{
	qDebug(LogToPrint());
}

QByteArray ByteCode::LogToPrint(bool forFile /* = false */)
{
	QStringList l;
	foreach(const LogLine& line, this->_log)
	{
		l << line.toString();
	}
	return (l.join(forFile ? "\r\n":"\n").toLocal8Bit());
}

//сохраняем Лог в текстовый файл
bool ByteCode::LogToFile(const QString& fname)
{
	qDebug("Writing Log to file: `%s`", fname.toLocal8Bit().data());

    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly))
        return false;

	file.write( this-> LogToPrint(true) );

	if( !file.flush() )
        return false;

	file.close();
    return true;
}

bool ByteCode::toFile(const QString& fname)
{
	qDebug("Writing ByteCode to file: `%s`", fname.toLocal8Bit().data());

    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly))
        return false;

	file.write( this->codeStream );

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
		this->log( QString("/!\\ Negative stack size == %1").arg(this->stackSize) );
		if( false )
		{
			qWarning("/!\\ ByteCode : negative stack size == %d\n Max 5 last log messages on ByteCode:", this->stackSize);
			QStringList l;
			int limit = qMin(5, _log.size()-1);
			for(int i=1; i<=limit; ++i)
			{
				l.prepend( this->_log[_log.size()-i] . toString() );
			}
			qWarning(l.join("\n").toLocal8Bit());
		}
	}
}


void ByteCode::appendLog(const QList<LogLine>& other_log)
{
	QString indent(" ");

	LogLine brace("{");
	this->_log.append(brace);

	foreach(const LogLine& line, other_log)
	{
		this->_log.append(
			LogLine(line.global_pos + this->size(), line.pos, indent + line.msg)
			);
	}

	brace.msg = "}";
	this->_log.append(brace);
}

ByteCode& ByteCode::append(const ByteCode& other)
{
	this->codeStream.append(other.codeStream);
	this->gotoEnd();

	this->appendLog(other._log);

	// append stackSize & maxStackSize
	this->incStack(+ other.maxStackSize);
	this->incStack(- other.maxStackSize);
	this->incStack(+ other.stackSize);
	
	return *this;
}


/*inline*/ ByteCode& ByteCode::s1(signed char v)
{
	return this->u1(v);
}
ByteCode& ByteCode::u1(unsigned char v)
{
	//this->codeStream.append(v);
	this->codeStream[this->currentOffset] = v;
	this->currentOffset += 1;
	return *this;
}

ByteCode& ByteCode::u2(unsigned short int v)
{
#ifdef INVERT_INTS
	v = Endian_Word_Conversion(v);
#endif
	
	union {
		unsigned short int u2;
		char b[2];
	} data;

	data.u2 = v;
	this->u1(data.b[0]);
	this->u1(data.b[1]);
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
	this->u1(data.b[0]);
	this->u1(data.b[1]);
	this->u1(data.b[2]);
	this->u1(data.b[3]);
	return *this;
}

ByteCode& ByteCode::appendHere(QByteArray ba)
{
	this->codeStream.append(ba);
	this->gotoEnd();

	return *this;
}

ByteCode& ByteCode::f4(float v)
{
	union {
		float f4;
		char b[4];
	} data;

	data.f4 = v;
	this->u1(data.b[0]);	//в float порядок байт не инвертируем
	this->u1(data.b[1]);
	this->u1(data.b[2]);
	this->u1(data.b[3]);
	return *this;
}

