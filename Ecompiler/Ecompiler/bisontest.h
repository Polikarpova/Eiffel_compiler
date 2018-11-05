#ifndef BISONTEST_H
#define BISONTEST_H

#include <QObject>
#include <QTest>
#include <QtTest/QtTest>

class BisonTest : public QObject
{
	Q_OBJECT

public:
	BisonTest(QObject *parent);
	~BisonTest();

private:

private slots:
	//void init();
	//void cleanup();

	void emptyClass();
	
};

#endif // BISONTEST_H
