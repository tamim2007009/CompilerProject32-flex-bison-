
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
     BASE = 258,
     END = 259,
     START = 260,
     VARIABLE = 261,
     EOL = 262,
     ARROW = 263,
     INTEGER = 264,
     REAL = 265,
     STRING = 266,
     INT_TYPE = 267,
     REAL_TYPE = 268,
     STRING_TYPE = 269,
     SEE = 270,
     AND = 271,
     OR = 272,
     NOT = 273,
     XOR = 274,
     LOG = 275,
     LOG2 = 276,
     LN = 277,
     SIN = 278,
     COS = 279,
     TAN = 280,
     FACTORIAL = 281,
     SQRT = 282,
     IF = 283,
     ELIF = 284,
     ELSE = 285,
     CHOICE = 286,
     DEFAULT = 287,
     OPTION = 288,
     FOREACH = 289,
     FROM = 290,
     TO = 291,
     DO = 292,
     WHILE = 293,
     BY = 294,
     AS = 295,
     COMMENT = 296,
     MODULE = 297,
     CALL = 298,
     IMPORT = 299,
     MMINUS = 300,
     PPLUS = 301,
     GEQL = 302,
     LEQL = 303,
     NEQL = 304,
     EQL = 305
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 131 "tamim.y"

	int integer;
	double real;
	char* string;



/* Line 1676 of yacc.c  */
#line 110 "tamim.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


