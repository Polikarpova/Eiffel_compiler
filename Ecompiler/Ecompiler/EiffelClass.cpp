#include "EiffelClass.h"
#include "MetaClass.h"

#include "IntegerType.h"
#include "REAL.h"
#include "CHARACTER.h"
#include "EiffelSTRING.h"
#include "BOOLEAN.h"

EiffelClass::EiffelClass(void)
{
	this->metaClass = 0;
}
EiffelClass::EiffelClass(MetaClass* metaClass) {
	this->tree_node = NULL;
	this->metaClass = metaClass;
}


EiffelClass::~EiffelClass(void)
{
}

/*virtual*/ bool EiffelClass::canCastTo(const EiffelType* otherType, EiffelType* *convertTo /*= 0*/) const
{
	if( ! EiffelType::canCastTo(otherType, convertTo) ) // ������ �� �����
	{
		return false;
	}

	// ��� ���� - ������
	const EiffelClass* otherClass = (EiffelClass*) otherType;

	// ��������� �� ��������...
	
	if( this->metaClass->name() == otherClass->metaClass->name() )
	{
		// ����� ������� ���������
		return true;
	}
	else if( this->metaClass->parent != NULL )
	{
		// chain up
		return this->metaClass->parent->getType() -> canCastTo(otherClass);
	}
	else
	{
		// no common parent can be found.
		return false;
	}

}


const QString& EiffelClass::className() const
{
	return metaClass->name();
}

// ���������� ������ � ������ �������������: `L�����.�����;`
QString EiffelClass::descriptor()
{
	return QString("L%1;").arg(metaClass->fullJavaName());
}


/*static*/ EiffelClass* EiffelClass::create(struct NType* node) {

	EiffelProgram* program = EiffelProgram::currentProgram;

	MetaClass* mc = 0;

	switch(node->type) {
	
		case ClassV:
			mc = program->findClass( QString(node->className).toUpper() );
			if(mc == NULL)
			{
				program->logError(
					QString("semantic"), 
					QString("Using undefined class %1 as type")
					.arg(node->className),
					node->loc.first_line);
			}
		case IntegerV:
			//mc = new IntegerType();
			break;
		case RealV:
			//mc = new REAL();
			break;
		case CharacterV:
			//����� ������
			break;
		case StringV:
			mc = program->findClass("STRING");
			break;
		case BooleanV:
			break;
	}

	if( !mc )
		return NULL;

	return (EiffelClass*) mc->getType();
}