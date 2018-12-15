#include "EiffelClass.h"
#include "MetaClass.h"

#include "INTEGER.h"
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

/*virtual*/ bool EiffelClass::canCastTo(const EiffelType* otherType) const
{
	// ���������, ���� ��������� ������� ... -> ��� �������� ��������� � MetaArray::canCastTo()

	if( ! EiffelType::canCastTo(otherType) ) // ������ �� �����
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


const QString& EiffelClass::className()
{
	return metaClass->name();
}

// ���������� ������ � ������ �������������: `L�����.�����;`
QString EiffelClass::descriptor()
{
	return QString("Leiffel/%1;").arg(metaClass->name());
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
			//mc = new INTEGER();
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

	return mc->getType();
}