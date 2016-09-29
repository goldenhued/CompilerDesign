#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAXLEN 31
#define INLEN 50

char input[INLEN];

int position = 0;

typedef enum 
{
	START,INNUM,INID,INEQ,INLTE,INGTE,INNOT,COM1,COM2,COM3,DONE
}StateType;

typedef enum
{
	ELSE,IF,INT,RETURN,VOID,WHILE,NUM,ID,PLUS,MINUS,MUL,DIV,SEMICOLON,COMMA,LPAREN,RPAREN,LBRAC,RBRAC,LCURLY,RCURLY,LTE,LESSER,GTE,GREATER,NOT,NOTEQUAL,ASSIGN,EQUAL,ERROR
}TokenType;

char getNextchar()
{
	return input[position++];
}

void ungetNextchar()
{
	position--;
}

struct 
{
	char keywords[10];
	TokenType t;
}
reservedwords[]={{"if",IF},{"else",ELSE},{"int",INT},{"return",RETURN},{"void",VOID},{"while",WHILE}};

TokenType reservedLookup(char a[])
{
	int i;
	for(i=0;i<=6;i++)
		if(strcmp(a,reservedwords[i].keywords)==0)
			return reservedwords[i].t;
	return ID;
}

TokenType getToken ()
{
	char c;
	StateType state=START;
	int save,index=0;
	TokenType currentToken;
	char TokenString[MAXLEN+1];
	while(state!=DONE)
	{
		save=1;
		c=getNextchar();
		switch(state)
		{
			case START:
				if(isdigit(c))
					state=INNUM;
				else if(isalpha(c))
					state=INID;
				else if((c == ' ')||(c == '\n')||(c == '\t'))
					save=0;
				else if(c == '/')
					state=COM1;
				else if(c == '=')
					state=INEQ;
				else if(c == '<')
					state=INLTE;
				else if(c == '>')
					state=INGTE;
				else if(c == '!')
					state=INNOT;
				else
				{
					state=DONE;
					if(c == '+')
					currentToken = PLUS;
					else if(c == '-')
					currentToken = MINUS;
					else if(c == '*')
					currentToken = MUL;
					else if(c == ';')
					currentToken = SEMICOLON;
					else if(c == ',')
					currentToken = COMMA;
					else if(c == '(')
					currentToken = LPAREN;
					else if(c == ')')
					currentToken = RPAREN;
					else if(c == '[')
					currentToken = LBRAC;
					else if(c == ']')
					currentToken = RBRAC;
					else if(c == '{')
					currentToken = LCURLY;
					else if(c == '}')
					currentToken = RCURLY;
					else
					currentToken = ERROR;
				}
				break;
				
			case INNUM:
				if(!isdigit(c))
				{
					state=DONE;
					save=0;
					ungetNextchar();
					currentToken=NUM;
				}
				break;
				
			case INID:
				if(!isalpha(c))
				{
					state=DONE;
					save=0;
					ungetNextchar();
					currentToken=ID;
				}
				break;
			
			case INEQ:
				state=DONE;
				if(c == '=')
					currentToken=EQUAL;
				else
				{
					save=0;
					currentToken=ASSIGN;
					ungetNextchar();
				}
				break;
			
			case INLTE:
				state=DONE;
				if(c == '=')
					currentToken=LTE;
				else
				{
					save=0;
					currentToken=LESSER;
					ungetNextchar();
				}
				break;
			
			case INGTE:
				state=DONE;
				if(c == '=')
					currentToken=GTE;
				else
				{
					save=0;
					currentToken=GREATER;
					ungetNextchar();
				}
				break;
			
			case INNOT:
				state=DONE;
				if(c == '=')
					currentToken=NOTEQUAL;
				else
				{
					save=0;
					currentToken=NOT;
					ungetNextchar();
				}
				break;
				
			case COM1:
				if(c == '*')
				{
					state=COM2;
					save=0;
				}
				else
				{
					state=DONE;
					currentToken=DIV;
					ungetNextchar();
				}
				break;
				
			case COM2:
				save=0;
				if(c == '*')
					state=COM3;
				break;
			
			case COM3:
				save=0;
				if(c == '*')
					state=COM3;
				else if(c == '/')
					state=START;
				else
					state=COM2;
				break;
		}
	if(save==1 && strlen(TokenString)<MAXLEN)
		TokenString[index++]=c;
	}
	
	TokenString[index]='\0';
	
	if(currentToken == ID)
		currentToken=reservedLookup(TokenString);
	
	return currentToken;
}

main()
{
	TokenType x;
	printf("Enter string\n");
	//scanf("%s",input);
	gets(input);
	x=getToken();
	printf("%d",x);
}
