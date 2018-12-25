#include <locale.h>
#include <string>
#include "print2dot.h"

#include <QProcess>

extern FILE *yyin;
extern int yyparse();
extern struct NClassList* root;

/* < Error handling > */
#define MAX_SYNTAX_ERRORS 20 /* copy of define in bison file */
extern char* syntax_errors[MAX_SYNTAX_ERRORS];
extern int syntax_errors_logged;
/* </ Error handling > */

#include "EiffelProgram.h"
#include "ByteCode.h"
#include "MetaClass.h"
#include "Field.h"
#include "Method.h"


/**
arg[0]: -
arg[1]: input file name (no extension): fnm
	fnm.e
	fnm.dot
	fnm.png

*/

//#include "Expression.h"
#include "JvmConstant.h"	//для Отладки Заполнения таблицы Констант

int main(int argc, char *argv[])
{
	if(false)
	{
		printf("Running a test for ByteCode...\n");

		ByteCode bc;
		bc.log("Begin writing Java-signature \\o/");
		bc.s1(0xCA).s1(0xFE).u1(0xBA).u1(0xBE);
		/*
		bc.iconst_(-1).iconst_(5);
		 ByteCode bc_1;
		 bc_1.log("Begin Of Nested ByteCode block")
			 .u2(0x0000).u4(0xCAFEBABE)
			 .log("End Of Nested ByteCode block");
		bc.append(bc_1)
			.u1(0x00).u1(-2)
			.u1(0x00).u2(-2)
			.u1(0x00).u4(-2);
		bc.currentOffset = 2; // move to some place in existing code
		bc.u1(0x77).u2(0x2BAD) // overwrite some consequent bytes
			.gotoEnd().log("End Of Whole ByteCode"); 
		*/

		//bc.pop()
		//  .dup()
		//  .dup2()
		//  .invokestatic(0x1B3D, 2, false) .ireturn().areturn().return_();

//		bc.log("Writed istore (0xAB);  ldc_w (0x008D); /o\\");

//Отладка Записи в ByteCode таблицы Констант
		ConstantTable ConstTable;
		JvmConstant jc = { UTF8_VALUE, 0, false };

		// имя класса
		jc.type = UTF8_VALUE;
		jc.value.utf8 = new QString("Constant_1");
		ConstTable.put(jc);
		
		// FLOAT Constant
		jc.type = FLOAT_VALUE;
		jc.value.real = 2.5;
		ConstTable.put(jc);

		// NAME_AND_TYPE Constant
		jc.type = NAME_AND_TYPE;
		jc.value.name_and_type[UTF8_NAME] = 7;
		jc.value.name_and_type[UTF8_DESCR] = 12;
		ConstTable.put(jc);

		// INT4 Constant
		jc.type = INT4_VALUE;
		jc.value.int4 = 0x404;
		ConstTable.put(jc);

		ConstTable.to_ByteCode(bc);

//Отладка Записи в ByteCode таблицы Методов
		MetaClass MetaClassD;
		Method Method1, Method2;

		Method1.name_constN = 0x1111;
		Method1.descr_constN = 0x8888;
		MetaClassD.methods["Method_1"] = &Method1;

		Method2.name_constN = 0x2222;
		Method2.descr_constN = 0x9999;
		MetaClassD.methods["Method_2"] = &Method2;

		MetaClassD.methods_to_ByteCode(bc);



		bc.toFile("bytecode-test.bc");

		bc.printLog();
		bc.LogToFile( "bytecode-test.log");

		return 0;
	}

	// запуск компилятора ...

	char in_fnm[100];
	char file_name[100];

	if(argc > 1)
	{
		strcpy(in_fnm, argv[1]);
	}
	else
	{
		//char[] infile = "test.e";
		//char infile[] = "../../samples/sample.e";
		//char infile[] = "../../samples/class_creation.e";
		//char infile[] = "../../samples/array_test.e";
		////char infile[] = "../../samples/testclass.e";
		//char infile[] = "../../samples/chain.e";

		//char infile[] = "../../samples/syntax/class_copy";
		char infile[] = "../../samples/bytecode/polymorph";
		//char infile[] = "../../samples/bytecode/hello_world";
		//char infile[] = "../../samples/bytecode/sort";
		strcpy(in_fnm, infile);
	}
		
	strcpy(file_name, in_fnm);
	strcat(file_name, ".e");
	
	printf("Processing file %s...\n", file_name);

	yyin = fopen(file_name, "r");
	int parse_result = yyparse();
	fclose(yyin);

	printf("yyparse() returned %i\n", parse_result);
	printf("ROOT: %p\n", root);

	if(root)
	{
		//printf("first_line: %d, last_line: %d \n",root->loc.first_line, root->loc.last_line);
		strcpy(file_name, in_fnm);
		strcat(file_name, ".dot");
	
		print2dot(file_name, root);
		printf("check out tree in %s\n",file_name);

		// run dot
		/// для отладки /// QProcess::startDetached(QString("cmd /C run_dot.bat %1 ../../samples/test").arg(in_fnm));


		// make semantic classes
		EiffelProgram* program = EiffelProgram::create(root, syntax_errors, syntax_errors_logged);
		
		if(program->errors.size() > 0) {
			printf("\n ====== Error List: ======\n");
			program->printErrors();
		} else {
			printf("\nCompilation completed successfully. Class files saved.\n");
		}
	}
	else
	{
		printf("tree was not exported to dot.\n");
	}

	if(argc <= 1) // debug mode
	{
		// `hit any key ...`
//		system("pause");
	}
}

/* TODO
	- Делать очистку out/eiffel/*.class перед записью туда скомпилированных классов
*/

