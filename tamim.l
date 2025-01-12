%{
                                /*Definition Section*/
	#include "tamim.tab.h"
	#include<string.h>
	extern int yydebug;
	//int yyparse();	
%}

%%
        /*---Rules Section--*/

"import<tamim.h>"      {
	fprintf(yyout, "-----------Importing tamim.h-------------\n");
    return IMPORT; }
	
	
"base"											{return ROOT;}
":"												{return START;}
";"                                             {return EOL;}
"end"											{return END;}

"num"											{return INT_TYPE;}
"frac" 										    {return REAL_TYPE;}
"alpha"										{return STRING_TYPE;}

"++"											{return PPLUS;}
"--"											{return MMINUS;}
"=="											{return EQL;}
"!="											{return NEQL;}	
"<="											{return LEQL;}
">="											{return GEQL;}
">>>"											{return ARROW;}



"inspect"											{return SEE;}

"XOR"											{return XOR;}
"AND"											{return AND;}
"OR"											{return OR;}
"~"												{return NOT;}
"SIN"											{return SIN;}
"COS"											{return COS;}
"TAN"											{return TAN;}
"SQRT"											{return SQRT;}
"log"											{return LOG;}
"log2"											{return LOG2;}
"ln"											{return LN;}
"!"												{return FACTORIAL;}

"if"											{return IF;}
"elif"											{return ELIF;}
"else"											{return ELSE;}
"choices for"									{return CHOICE;}
"none"											{return DEFAULT;}
"option"										{return OPTION;}

"repeat"										{return DO;}
"while"											{return WHILE;}
"from"											{return FROM;}
"to"											{return TO;}
"by"											{return BY;}

"module"										{return MODULE;}
"call"											{return CALL;}




[0-9]+  										{yylval.integer = atoi(yytext); return INTEGER;}
[0-9]*[.][0-9]+([eE][+-]?[0-9]+)?				{yylval.real = atof(yytext);return REAL;}

[A-Za-z0-9]+ 									{yylval.string = strdup(yytext);return VARIABLE;}



\"(\\.|[^"\\])*\"								{
													char* tmp = strdup(yytext);
													int n = strlen(tmp);
													yylval.string = malloc(n*sizeof(char));
  													memcpy(yylval.string,&tmp[1],n-2);
													  yylval.string[n-2]='\0';
													return STRING;
												}

"."												{return yytext[0];}
[-+/*<>=,();%^{}\]\[] 							{return yytext[0];}
[#][^#]*[#]										{
													char* tmp = strdup(yytext);
													int n = strlen(tmp);
													yylval.string = malloc(n*sizeof(char));
  													memcpy(yylval.string,&tmp[1],n-2);
													   yylval.string[n-2]='\0';
													return COMMENT;
												
												}
[ \t\n]											{}
.												{printf("Unknown character.");}
%%
 /*User Code Section*/
int yywrap(){
	return 1;
}

int yyerror(char *s){
	fprintf(stderr,"error: %s\n", s);
}