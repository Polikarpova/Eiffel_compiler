#include "Method.h"
#include "EiffelClass.h"
#include "EiffelArray.h"

Method::Method(void)
	: Feature()
{
	this->isCreator = false;
}
Method::Method(MetaClass* mc, EiffelType* type, const QString& name, QList<LocalVariable> argList /*= QList<>()*/ )
	: Feature(mc, type, name)
{
	this->isCreator = false;

	// local vars
	int loc_i = 0;

	// 1 (Current)
	LocalVariable* lvr = new LocalVariable("current", loc_i, mc->getType() );
	this->localVariables[lvr->name] = lvr;
	++loc_i;

	// + ���������� ���������
	if( ! argList.isEmpty() )
	{
		foreach(LocalVariable lvar, argList ) {
			// add var
			this->localVariables[lvar.name] = new LocalVariable(lvar.name, loc_i, lvar.type );
			++loc_i;
		}
	}

	// ������������� ���������� ����������
	this->paramCount = loc_i;
}


Method::~Method(void)
{
}

/*static*/ Method* Method::create(MetaClass* mc, struct NFeature* node)
{
	QString name(node->name);
	name = name.toLower();

	Method* mtd = new Method();
	// add to class
	mc->methods[name] = mtd;

	mtd->name = name;
	mtd->metaClass = mc;

	mtd->tree_node = node;
	mtd->type = EiffelType::create(node->type);
	if( ! mtd->type )
	{
		qDebug("Method does not declared with a type! where: Method::create()");
		delete mtd;
		return false;
	}

	// local vars
	int loc_i = 0;

	// 1 (Current)
	LocalVariable* lvr = new LocalVariable("current", loc_i, mc->getType() );
	mtd->localVariables[lvr->name] = lvr;
	++loc_i;

	// + ���������� ���������
	struct NNameAndTypeList* List;
	List = node->params;
	if(List) {
		for(struct NNameAndType* i = List->first; ; i = i->next) {
			// add var
			LocalVariable* lvr = LocalVariable::create(i, loc_i);
			mtd->localVariables[lvr->name] = lvr;
			++loc_i;

			if(i == List->last) break;
		}
	}

	// ������������� ���������� ����������
	mtd->paramCount = loc_i;

	// + ��������� ����������

	List = node->localVars;
	if(List) {
		for(struct NNameAndType* i = List->first; ; i = i->next) {
			// add var
			LocalVariable* lvr = LocalVariable::create(i, loc_i);
			mtd->localVariables[lvr->name] = lvr;
			++loc_i;

			if(i == List->last) break;
		}
	}

	// ���������� Result: ��� �������� ��������
	if( ! mtd->type->isVoid() )
	{
		// 1 (Result)
		LocalVariable* lvr = new LocalVariable("result", loc_i, mtd->type );
		mtd->localVariables[lvr->name] = lvr;
		++loc_i;
	}

	mtd->initJavaName();

	mtd->descriptor = mtd->createDescriptor();

	// ������� ��������� � ������: ��� � ����������
	mtd->initConstants();


	// report creation
	qDebug("created Method: %s. Descriptor: %s", node->name, mtd->getDescriptor().toLocal8Bit().data());

	return mtd;
}

bool Method::createBody()
{
	this->body.currentMethod = this;
	return 
		this->body.createBody(this->tree_node->routineBody);
}

LocalVariable* Method::findLocalVar(const QString& lowerName)
{
	return this->localVariables.value(lowerName, NULL);
}

LocalVariable* Method::findLocalVar(int n)
{
	foreach(LocalVariable* lvar , this->localVariables)
	{
		if(lvar->n == n)
			return lvar;
	}
	return NULL;
}


QString Method::createDescriptor() {

	QString result = "(";

	//�������� �� ���� ����������
	for(int i=1 ; i<this->paramCount ; ++i )
	{
		result += this->findLocalVar(i)->type->descriptor();
	}

	result += ")";

	//�������� ���������� ������������� ��������
	result += this->type->descriptor();

	return result;
}


ByteCode& Method::generateCodeAttribute(ByteCode &bc) {

	int attribute_size_u4_pos, attribute_start, attribute_length;

	bc.log("").log(QString("Start of atribute `Code` of method `%1` ...").arg(this->name));

	// `Code`
	bc.u2(this->metaClass->code_constN);

	// ����� ��������
	attribute_size_u4_pos = bc.currentOffset;
	bc.u4(0xDEADBEEF); // ���� ���������� ��������, ����� �������������

	attribute_start = bc.currentOffset; // ������ �������� (�� ����������� ������ 6 ����)

	// ����-��� ���������� ���� ������ (���������� ����������)
	ByteCode body_bc;
	this->generateCode4Body(body_bc);

	// ������ ����� ���������
	bc.u2( body_bc.maxStackSize + 0 ); // ��������� �� ������ ������ ?

	// ���-�� ��������� ����������
	bc.u2( this->localVariables.size() );

	// ����� ���������� ����-����
	bc.log( QString("Length of ByteCode = ")+bc.CombinedPrint(body_bc.size(), 4) );
	bc.u4(body_bc.size()); // ���� ���������� ��������, ����� �������������

	// ����-���
	bc.append(body_bc);

	// ����� ������ ���������� � ���������
	bc.u2(0x0000).u2(0x0000);


	attribute_length = bc.currentOffset - attribute_start;

	// ����� ��������:
	// ����������
	bc.gotoPos(attribute_size_u4_pos)
		.u4( attribute_length )
		.gotoEnd();
	bc.log( QString("Length of written attribute `Code` = ")+bc.CombinedPrint(attribute_length, 4) );

	return bc;
}

ByteCode& Method::generateCode4Body(ByteCode &bc)
{
	bc.log( QString("ByteCode of method starts here ...") );

	if(this->isCreator)
	{
         //0: aload_0
         //1: invokespecial #1                  // Method rtl/ANY."<init>":()V
	}

	
	body.toByteCode(bc);


	// ������� �� ������

	LocalVariable* result_var = findLocalVar("result");
	QString type_descr = this->type->descriptor();
	
	if(this->isVoid())
	{
		bc.return_();
	}
	else if( type_descr.startsWith("L") || type_descr.startsWith("[") ) // class or array
	{
		bc.aload( result_var->n );
		bc.areturn();
	}
	else if( type_descr == "I" )
	{
		bc.iload( result_var->n );
		bc.ireturn();
	}
	else
	{
		bc.log( QString("/!\\ Unknown return type: `%1`").arg(type_descr) );
	}
	// ...

	return bc;
}

//������� ������ -> � ByteCode
ByteCode& Method::to_ByteCode(ByteCode & bc) {
//����� � ByteCode ������ �� ����� ������
	bc.u2(ACC_PUBLIC | addFlags); //�����
	bc.u2(name_constN); //���
	bc.log( QString("Method_name, num CONSTANT_Utf8 =")+bc.CombinedPrint(name_constN, 2) );
	bc.u2(descr_constN); //����������
	bc.log( QString("Method_descriptor, num CONSTANT_Utf8 =")+bc.CombinedPrint(descr_constN, 2) );
	bc.u2(0x0001); //���-�� ���������

	generateCodeAttribute(bc); //������� "Code"
	return bc;
}