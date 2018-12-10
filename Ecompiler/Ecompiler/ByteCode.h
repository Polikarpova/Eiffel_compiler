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
	//* байт-код
	QByteArray code;
	int size() {return code.size();};

	/** “екуща€ позици€ записи в байт-код.
		¬ обычном режиме (дозапись) равна code.size().
		¬ режиме перезаписи указывает на некоторую позицию в середине массива записанных байтов
	*/
	int currentOffset;

	ByteCode& gotoEnd() {currentOffset = size(); return *this;}


	// ==================================================================== //
	// подсчЄт размера стека
	int stackSize, maxStackSize;
	bool assertOnNegativeStack;

	// ==================================================================== //
	/** добавить сообщение в лог.
		ѕри логировании добавл€емых инструкций
		следует вызывать log() до записи инструкции к код,
		чтобы в лог попала позици€ первого байта инструкции (а не следующего после неЄ)
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


	//*  запись в байт-кода в файл
	bool toFile(const QString& fname);

	#include "instructions.h"

private:
	//* лог
	QList<LogLine> _log;

	void incStack(int sizeDiff);
	void appendLog(const QList<LogLine>& other_log);
};

