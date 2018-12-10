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
	//* ����-���
	QByteArray code;
	int size() {return code.size();};

	/** ������� ������� ������ � ����-���.
		� ������� ������ (��������) ����� code.size().
		� ������ ���������� ��������� �� ��������� ������� � �������� ������� ���������� ������
	*/
	int currentOffset;

	ByteCode& gotoEnd() {currentOffset = size(); return *this;}


	// ==================================================================== //
	// ������� ������� �����
	int stackSize, maxStackSize;
	bool assertOnNegativeStack;

	// ==================================================================== //
	/** �������� ��������� � ���.
		��� ����������� ����������� ����������
		������� �������� log() �� ������ ���������� � ���,
		����� � ��� ������ ������� ������� ����� ���������� (� �� ���������� ����� ��)
	*/
	ByteCode& log(const QString& s);
	void printLog();


	// ==================================================================== //
	// ������ � ����-���
	ByteCode& ByteCode::append(const ByteCode& other);
	ByteCode& s1(signed char v);
	ByteCode& u1(unsigned char v);
	ByteCode& u2(unsigned short int v);
	ByteCode& u4(unsigned long int v);


	//*  ������ � ����-���� � ����
	bool toFile(const QString& fname);

	#include "instructions.h"

private:
	//* ���
	QList<LogLine> _log;

	void incStack(int sizeDiff);
	void appendLog(const QList<LogLine>& other_log);
};

