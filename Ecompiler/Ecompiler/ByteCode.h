#pragma once
#include <QByteArray>
#include <QList>
#include <QString>

//typedef char byte;


#define INVERT_INTS //*< short int & int values are to be reversed is this macros id defined (no matter which value it is set to)

class LogLine
{
public:

	LogLine()
	{
		this->global_pos = this->pos = -1;
	}
	LogLine(const QString& msg)
	{
		this->global_pos = this->pos = -1;
		this->msg = msg;
	}
	LogLine(int global_pos, int pos, const QString& msg)
	{
		this->global_pos = global_pos;
		this->pos = pos;
		this->msg = msg;
	}
	~LogLine()
	{
		this->msg.clear();
	}

	int global_pos, pos; // -1 value: don`t show positions
	QString msg;

	//* convert to string
	QString toString() const; // see ByteCode.cpp
};


class ByteCode
{
public:

	ByteCode(void);
	~ByteCode(void);

	// ==================================================================== //
	//* поток байт-кода
	QByteArray codeStream;
	int size() {return codeStream.size();};

	/** Текущая позиция записи в байт-код.
		В обычном режиме (дозапись) равна codeStream.size().
		В режиме перезаписи указывает на некоторую позицию в середине массива записанных байтов
	*/
	int currentOffset;

	ByteCode& gotoEnd() {currentOffset = size(); return *this;}

	ByteCode& gotoPos(int pos) {currentOffset = pos; return *this;}


	// ==================================================================== //
	// подсчёт размера стека
	int stackSize, maxStackSize;
	bool assertOnNegativeStack;

	// ==================================================================== //
	/** добавить сообщение в лог.
		При логировании добавляемых инструкций
		следует вызывать log() до записи инструкции к код,
		чтобы в лог попала позиция первого байта инструкции (а не следующего после неё)
	*/
	ByteCode& log(const QString& s);
	void printLog();


	// ==================================================================== //
	// запись в байт-код
	ByteCode& ByteCode::append(const ByteCode& other);
	ByteCode& s1(signed char v);
	ByteCode& u1(unsigned char v);
	ByteCode& u2(unsigned short int v);
	ByteCode& u4(unsigned long int v);
	ByteCode& appendHere(QByteArray ba);
	ByteCode& f4(float v);

	QString CombinedPrint(int pArg, short int bytes){
		return QString(" %1 (0x%2)").arg(pArg) .arg( QString::number(pArg,16).right(bytes*2).toUpper().rightJustified(bytes*2,'0'));
	}

	QString CombinedPrint(float pArg){
		union {
			float f4;
			char b[4];
		} data;
		data.f4 = pArg;
		QByteArray s ;
		short int dg;
		for(short int i=0; i<=3; i++)
		{
			dg = data.b[i];
			s += QString::number(dg,16).right(2).toUpper().rightJustified(2,'0');
		}
		return QString(" %1 [").arg(pArg) +QString(s) +"]";
	}


	#include "instructions.h"


	//*  запись в байт-кода в файл
	bool toFile(const QString& fname);

	//* сохраняем Лог в текстовый файл
	bool LogToFile(const QString& fname);

	QByteArray ByteCode::LogToPrint(bool forFile = false);


private:
	//* лог
	QList<LogLine> _log;

	void incStack(int sizeDiff);
	void appendLog(const QList<LogLine>& other_log);
};

