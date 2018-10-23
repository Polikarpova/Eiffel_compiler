#pragma once

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_underscores(char* str);

// from eiffel.flex.c
static void yyunput ( int c, char *buf_ptr  );

int parse_int(char* string_num, char char_base=0)
{
	int base;
	switch(char_base)
	{
		case 'b':
		case 'B':
			base = 2;
			break;
		case 'c':
		case 'C':
			base = 8;
			break;
		case 'x':
		case 'X':
			base = 16;
			break;
		default:
			base = 10;
	}

	if(base != 10)
	{
		int index_letter = (string_num[0] == '-')? 2 : 1;
		string_num[index_letter] = '0';
	}
	
	remove_underscores(string_num);

	int x = strtol(string_num,NULL, base);
	return x;
} 

double parse_real(char* string_num)
{
	char after_real = string_num[ strlen(string_num) - 1 ];
	string_num[ strlen(string_num) - 1 ] = 0;

	double result = atof ( remove_underscores( string_num ) );

	unput(after_real);

	return result;
}

char append_special_char_digraph(char* buf, char* escape_seq)
{
	char codes[]  = "ABCDFHLNQRSTUV%'\"()<>";
	char actual[] = "@\b^$\f\\~\n`\r#\t\0|%'\"[]{}";
	char ch;

	char* index = strchr(codes, toupper(escape_seq[1]));
	if(!index)
		//ch = escape_seq[1];
		return 0;
	else
		ch = actual[index-codes];

	int len = strlen(buf);
	buf[len] = ch;
	buf[len+1] = 0;

	return ch;
}

char append_special_char_by_code(char* buf, char* code_seq)
{
	// code_seq: "%/<3-digit-code>/"
	code_seq[ strlen(code_seq)-1 ] = 0;
	
	int c = strtol( code_seq+2 ,NULL, 10);
	char ch = c;

	int len = strlen(buf);
	buf[len] = ch;
	buf[len+1] = 0;

	return ch;
}

char* remove_underscores(char* str)
{
	char* p;
	while(p = strchr(str, '_'))
	{
		// shift remainig part left
		for(char* i = p+1; i < str+strlen(str); i++)
		{
			*(i-1) = *i;
		}
		// truncate last char
		str[strlen(str)-1] = 0;
		// or: *i = 0
	}
	
	return str;
}


void parse_char_interval(char* text, char c) {
	
	if (c == '.')
		text[strlen(text)-1] = 0;
}