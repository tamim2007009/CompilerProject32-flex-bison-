
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ROOT = 258,
     END = 259,
     START = 260,
     VARIABLE = 261,
     ARRAY_VAR = 262,
     EOL = 263,
     ARROW = 264,
     INTEGER = 265,
     REAL = 266,
     STRING = 267,
     INT_TYPE = 268,
     REAL_TYPE = 269,
     STRING_TYPE = 270,
     SEE = 271,
     AND = 272,
     OR = 273,
     NOT = 274,
     XOR = 275,
     LOG = 276,
     LOG2 = 277,
     LN = 278,
     SIN = 279,
     COS = 280,
     TAN = 281,
     FACTORIAL = 282,
     SQRT = 283,
     IF = 284,
     ELIF = 285,
     ELSE = 286,
     CHOICE = 287,
     DEFAULT = 288,
     OPTION = 289,
     FOREACH = 290,
     FROM = 291,
     TO = 292,
     DO = 293,
     WHILE = 294,
     BY = 295,
     AS = 296,
     COMMENT = 297,
     MODULE = 298,
     CALL = 299,
     IMPORT = 300,
     MMINUS = 301,
     PPLUS = 302,
     GEQL = 303,
     LEQL = 304,
     NEQL = 305,
     EQL = 306
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 194 "tamim.y"

	int integer;
	double real;
	char* string;



/* Line 1676 of yacc.c  */
#line 111 "tamim.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


