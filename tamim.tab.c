
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "tamim.y"

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<math.h>
    #define YYDEBUG 1
    extern FILE *yyin;
    extern FILE *yyout;
	int yylex();
	int yyerror(char *s);

    typedef struct variable{
        char *name;
        int type; 
        int *ival;
        double *dval;
        char** sval;
        int size;
    }var;

    typedef struct functionstack{
        char *fname;
        var *fptr;
        int varCnt;
    }stack;

var *vptr = NULL;  
stack *stk = NULL;  
     
 void initialize_globals() {
    vptr = (var *)malloc(8 * sizeof(var));
    if (!vptr) {
        perror("Memory allocation failed for vptr");
        exit(EXIT_FAILURE);
    }

    stk = (stack *)malloc(5 * sizeof(stack));
    if (!stk) {
        perror("Memory allocation failed for stk");
        exit(EXIT_FAILURE);
    }
}
    int varCnt = 0,funCnt=0; 
    int vartaken = 0,funtaken=0;
    int cnt = 0; 
    int conditionMatched; 
    double choiceValue;
    int currentFunction;
    int currentParam; 
    int functionRejected; 

        int checkExistance(char *varName){
            for(int i = 0 ; i<varCnt; i++){
                if(strcmp(vptr[i].name,varName)==0){
                    return 1;
                }
            }
            return 0;
        }
        int getVariableIndex(char *varName){
            for(int i = 0 ; i<varCnt; i++){
                if(strcmp(vptr[i].name,varName)==0){
                    return i;
                }
            }
            return -1;
        }
       
        void doesNotExist(char *varName){   printf("There is No Such Variable Named: %s\n\n",varName);  } 
        void outOfRange() { printf("Trying to Access index out of Range.\n\n");    }
        void alreadyExist(char *varName)  { printf("%s is already Declared.\n\n",varName);  }
        void notNumeric()  { printf("String literals not applicable.\n\n");    }
        void notInt()  {  printf("Applicable of Integer only.\n\n"); }
        
        void insertData(char *varname,void* value,int type,int id,int size){
            vptr[id].name = varname;
            vptr[id].size = size;
            if(type==0){
                int *x = ((int*)value);
                vptr[id].ival = malloc(size*sizeof(int));
                for(int i=0;i<size;i++){
                    vptr[id].ival[i] = x[i];
                }
                vptr[id].type = 0;   
            }
            else if(type==1){
                double* x = ((double*)value);
                vptr[id].dval = malloc(size*sizeof(double));
                for(int i=0;i<size;i++){
                    vptr[id].dval[i] = x[i];
                }
                vptr[id].type = 1;    
            }
            else if(type==2){
                char **s =((char**)value);
                vptr[id].sval = malloc(size*sizeof(char**));
                for(int i=0;i<size;i++){
                    vptr[id].sval[i] = s[i];
                }
                vptr[id].type = 2;
            }
        }  
        void printVariable(char *varName){
            int index = getVariableIndex(varName);
            if (index == -1)
            {
                doesNotExist(varName);
            }
            else
            {               
                    printf(" %s :",varName);
                    if (vptr[index].type == 1)
                        printf("%lf\n", vptr[index].dval[0]);
                    if (vptr[index].type == 0)
                        printf("%d\n", vptr[index].ival[0]);
                    if (vptr[index].type == 2)
                        printf("%s\n", vptr[index].sval[0]);        
            }
        }

        int getFunctionIndex(char *varName){
            for(int i = 0 ; i<funCnt; i++)
            {
                if(strcmp(stk[i].fname,varName)==0){
                    return i;
                }
            }
            return -1;
        }


/* Line 189 of yacc.c  */
#line 205 "tamim.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 131 "tamim.y"

	int integer;
	double real;
	char* string;



/* Line 214 of yacc.c  */
#line 299 "tamim.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 311 "tamim.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   867

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNRULES -- Number of states.  */
#define YYNSTATES  243

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    57,     2,     2,
      61,    62,    55,    53,    59,    54,     2,    56,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      47,    60,    48,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    58,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    49,    50,    51,    52
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    10,    13,    15,    17,    20,    23,
      26,    29,    31,    33,    35,    37,    39,    42,    45,    48,
      52,    54,    58,    60,    64,    66,    70,    72,    76,    78,
      82,    84,    88,    92,    94,    98,   100,   104,   108,   113,
     114,   116,   119,   121,   126,   129,   131,   137,   143,   145,
     148,   150,   155,   158,   160,   166,   176,   182,   190,   195,
     200,   205,   210,   215,   220,   229,   231,   235,   237,   240,
     243,   246,   252,   254,   258,   260,   262,   264,   266,   268,
     271,   274,   277,   280,   284,   288,   292,   296,   300,   304,
     308,   312,   316,   320,   324,   328,   332,   336,   340,   343,
     347,   352,   357,   362,   367,   372,   377,   382,   385,   388
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      64,     0,    -1,    44,     3,     5,    65,     4,    -1,    -1,
      65,    66,    -1,     7,    -1,    41,    -1,    67,     7,    -1,
      76,     7,    -1,    74,     7,    -1,   100,     7,    -1,    78,
      -1,    84,    -1,    90,    -1,    92,    -1,    96,    -1,    12,
      68,    -1,    13,    70,    -1,    14,    72,    -1,    68,    59,
      69,    -1,    69,    -1,     6,    60,   100,    -1,     6,    -1,
      70,    59,    71,    -1,    71,    -1,     6,    60,   100,    -1,
       6,    -1,    72,    59,    73,    -1,    73,    -1,     6,    60,
      11,    -1,     6,    -1,    15,     8,    75,    -1,    75,    59,
       6,    -1,     6,    -1,    76,    59,    77,    -1,    77,    -1,
       6,    60,   100,    -1,    28,    79,    80,    -1,   100,     5,
      66,     4,    -1,    -1,    82,    -1,    82,    81,    -1,    81,
      -1,    30,     5,    66,     4,    -1,    82,    83,    -1,    83,
      -1,    29,   100,     5,    66,     4,    -1,    31,    85,     5,
      86,     4,    -1,     6,    -1,    88,    87,    -1,    87,    -1,
      32,     5,    66,     4,    -1,    88,    89,    -1,    89,    -1,
      33,   100,     5,    66,     4,    -1,    35,   100,    36,   100,
      39,   100,     5,    66,     4,    -1,    38,    91,     5,    66,
       4,    -1,    37,     5,   100,     4,    38,    91,     7,    -1,
       6,    46,    47,   100,    -1,     6,    46,    50,   100,    -1,
       6,    46,    51,   100,    -1,     6,    45,    48,   100,    -1,
       6,    45,    49,   100,    -1,     6,    45,    51,   100,    -1,
      42,    93,    61,    94,    62,     5,    65,     4,    -1,     6,
      -1,    94,    59,    95,    -1,    95,    -1,    12,     6,    -1,
      13,     6,    -1,    14,     6,    -1,    43,    97,    61,    98,
      62,    -1,     6,    -1,    98,    59,    99,    -1,    99,    -1,
       6,    -1,     9,    -1,    10,    -1,     6,    -1,    53,   100,
      -1,    54,   100,    -1,    46,   100,    -1,    45,   100,    -1,
     100,    53,   100,    -1,   100,    54,   100,    -1,   100,    55,
     100,    -1,   100,    56,   100,    -1,   100,    58,   100,    -1,
     100,    57,   100,    -1,   100,    47,   100,    -1,   100,    48,
     100,    -1,   100,    50,   100,    -1,   100,    49,   100,    -1,
     100,    52,   100,    -1,   100,    51,   100,    -1,   100,    16,
     100,    -1,   100,    17,   100,    -1,   100,    19,   100,    -1,
      18,   100,    -1,    61,   100,    62,    -1,    23,    61,   100,
      62,    -1,    24,    61,   100,    62,    -1,    25,    61,   100,
      62,    -1,    20,    61,   100,    62,    -1,    21,    61,   100,
      62,    -1,    22,    61,   100,    62,    -1,    27,    61,   100,
      62,    -1,     6,    46,    -1,     6,    45,    -1,   100,    26,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   161,   161,   162,   163,   165,   166,   167,   168,   169,
     170,   172,   174,   175,   176,   195,   198,   199,   200,   203,
     204,   207,   219,   227,   228,   231,   243,   251,   252,   255,
     268,   276,   279,   280,   283,   284,   286,   301,   303,   314,
     314,   315,   316,   318,   333,   334,   337,   353,   357,   367,
     368,   371,   381,   382,   385,   401,   415,   422,   430,   445,
     460,   475,   490,   505,   523,   526,   540,   541,   544,   553,
     562,   573,   586,   598,   599,   602,   624,   628,   633,   643,
     644,   645,   646,   647,   648,   649,   650,   651,   652,   653,
     654,   655,   656,   657,   658,   659,   660,   661,   662,   663,
     664,   665,   666,   667,   668,   669,   670,   671,   683,   694
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BASE", "END", "START", "VARIABLE",
  "EOL", "ARROW", "INTEGER", "REAL", "STRING", "INT_TYPE", "REAL_TYPE",
  "STRING_TYPE", "SEE", "AND", "OR", "NOT", "XOR", "LOG", "LOG2", "LN",
  "SIN", "COS", "TAN", "FACTORIAL", "SQRT", "IF", "ELIF", "ELSE", "CHOICE",
  "DEFAULT", "OPTION", "FOREACH", "FROM", "TO", "DO", "WHILE", "BY", "AS",
  "COMMENT", "MODULE", "CALL", "IMPORT", "MMINUS", "PPLUS", "'<'", "'>'",
  "GEQL", "LEQL", "NEQL", "EQL", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'",
  "','", "'='", "'('", "')'", "$accept", "program", "statements",
  "statement", "declaration", "int_variables", "int_var", "real_variables",
  "real_var", "string_variables", "string_var", "show", "print_vars",
  "assigns", "assign", "if_blocks", "if_block", "else_statement",
  "single_else", "elif_statement", "single_elif", "choice_block",
  "choice_variable", "options", "default", "optionlist", "option",
  "loop_block", "while_conditions", "module_declare", "module_name",
  "module_variable", "single_var", "module_call", "user_module_name",
  "user_parameters", "single_param", "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,    60,    62,   302,
     303,   304,   305,    43,    45,    42,    47,    37,    94,    44,
      61,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    65,    65,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    67,    67,    67,    68,
      68,    69,    69,    70,    70,    71,    71,    72,    72,    73,
      73,    74,    75,    75,    76,    76,    77,    78,    79,    80,
      80,    80,    80,    81,    82,    82,    83,    84,    85,    86,
      86,    87,    88,    88,    89,    90,    90,    90,    91,    91,
      91,    91,    91,    91,    92,    93,    94,    94,    95,    95,
      95,    96,    97,    98,    98,    99,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     2,     1,     1,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     2,     2,     2,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     1,     3,     3,     4,     0,
       1,     2,     1,     4,     2,     1,     5,     5,     1,     2,
       1,     4,     2,     1,     5,     9,     5,     7,     4,     4,
       4,     4,     4,     4,     8,     1,     3,     1,     2,     2,
       2,     5,     1,     3,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       4,     4,     4,     4,     4,     4,     4,     2,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     2,    78,     5,
      76,    77,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       0,     0,     0,     0,     0,     0,     0,     4,     0,     0,
       0,    35,    11,    12,    13,    14,    15,     0,   108,   107,
       0,    22,    16,    20,    26,    17,    24,    30,    18,    28,
       0,    78,    98,     0,     0,     0,     0,     0,     0,     0,
      39,     0,    48,     0,     0,     0,     0,     0,    65,     0,
      72,     0,    82,    81,    79,    80,     0,     7,     9,     8,
       0,    10,     0,     0,     0,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,    33,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,    42,    40,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    99,
       0,    34,    95,    96,    97,    89,    90,    92,    91,    94,
      93,    83,    84,    85,    86,    88,    87,    21,    19,    25,
      23,    29,    27,     0,   103,   104,   105,   100,   101,   102,
     106,     0,     0,    41,    44,     0,     0,     0,     0,    50,
       0,    53,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    67,    75,     0,    74,    32,
       0,     0,    38,     0,     0,    47,    49,    52,     0,     0,
      61,    62,    63,    58,    59,    60,    56,    68,    69,    70,
       0,     0,     0,    71,     0,    43,     0,     0,     0,     0,
      66,     3,    73,    46,    51,     0,     0,    57,     0,    54,
       0,    64,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,    37,    38,    52,    53,    55,    56,    58,
      59,    39,   116,    40,    41,    42,    70,   126,   127,   128,
     129,    43,    73,   178,   179,   180,   181,    44,    77,    45,
      79,   194,   195,    46,    81,   197,   198,    47
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -130
static const yytype_int16 yypact[] =
{
     -21,    30,    42,    41,  -130,  -130,   105,  -130,   -33,  -130,
    -130,  -130,    54,    59,    60,    61,   265,     6,     7,     9,
      11,    12,    14,    18,   265,    86,   265,    89,    90,  -130,
      91,    93,   265,   265,   265,   265,   265,  -130,    94,    95,
      -5,  -130,  -130,  -130,  -130,  -130,  -130,   438,  -130,  -130,
     265,    40,    44,  -130,    45,    47,  -130,    50,    62,  -130,
      98,   -15,   809,   265,   265,   265,   265,   265,   265,   265,
      15,   304,  -130,   108,   721,   265,    16,   117,  -130,    63,
    -130,    70,   776,   776,     0,     0,   481,  -130,  -130,  -130,
     128,  -130,   265,   265,   265,  -130,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   776,   265,
      54,   265,    59,   124,    60,  -130,    78,   497,   541,   557,
     601,   617,   661,   677,   265,   133,  -130,  -130,    15,  -130,
     223,    31,   265,   287,   -27,   -36,   223,    -8,   135,  -130,
      79,  -130,   809,   809,   809,   -17,   -17,   -17,   -17,   -17,
     -17,     0,     0,   -23,   -23,   -23,   -23,   776,  -130,   776,
    -130,  -130,  -130,   138,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,   358,   223,  -130,  -130,   141,   144,   265,   148,  -130,
      31,  -130,   764,   115,   265,   265,   265,   265,   265,   265,
     150,   149,   151,   154,   -34,  -130,  -130,   -30,  -130,  -130,
     223,   152,  -130,   223,   371,  -130,  -130,  -130,   265,    90,
     776,   776,   776,   776,   776,   776,  -130,  -130,  -130,  -130,
      -8,   157,   135,  -130,   159,  -130,   160,   223,   425,   158,
    -130,  -130,  -130,  -130,  -130,   163,   223,  -130,   173,  -130,
     170,  -130,  -130
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,  -130,   -56,  -129,  -130,  -130,    66,  -130,    69,  -130,
      64,  -130,  -130,  -130,    99,  -130,  -130,  -130,    56,  -130,
      71,  -130,  -130,  -130,    10,  -130,    22,  -130,    -6,  -130,
    -130,  -130,   -14,  -130,  -130,  -130,   -13,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      62,   175,    89,    95,   191,   192,   193,   190,    71,    95,
      74,   187,    48,    49,   188,   189,    82,    83,    84,    85,
      86,   184,   185,     1,   186,   220,    95,    50,   221,   222,
      48,    49,   223,     3,   108,   107,   102,   103,   104,   105,
     106,   107,     4,   201,   124,   125,     5,   117,   118,   119,
     120,   121,   122,   123,    90,   104,   105,   106,   107,   133,
      51,   134,   135,   176,   177,    54,    57,    63,    64,    60,
      65,   224,    66,    67,   226,    68,   142,   143,   144,    69,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,    72,   157,    75,   159,    76,    78,   235,    80,
     109,    87,    88,   110,   115,   111,   112,   240,   171,     7,
     113,     8,     9,   131,    10,    11,   182,    12,    13,    14,
      15,   114,   136,    16,   137,    17,    18,    19,    20,    21,
      22,   138,    23,    24,   140,   161,    25,   163,   172,    50,
      26,   196,    27,    28,   199,   202,    29,    30,    31,   203,
      32,    33,   205,   209,   216,   217,   225,   218,    34,    35,
     219,   204,   231,   233,   234,   237,    36,   239,   210,   211,
     212,   213,   214,   215,   242,   238,   158,   241,   162,     8,
       9,   160,    10,    11,   173,    12,    13,    14,    15,   141,
     206,    16,   228,    17,    18,    19,    20,    21,    22,   174,
      23,    24,   207,   229,    25,     0,   230,     0,    26,   232,
      27,    28,     0,     0,    29,    30,    31,     0,    32,    33,
       0,     0,     0,     0,     0,     0,    34,    35,     0,     8,
       9,     0,    10,    11,    36,    12,    13,    14,    15,     0,
       0,    16,     0,    17,    18,    19,    20,    21,    22,     0,
      23,    24,     0,     0,    25,     0,     0,     0,    26,     0,
      27,    28,     0,     0,    29,    30,    31,     0,    32,    33,
       0,    61,     0,     0,    10,    11,    34,    35,     0,     0,
       0,     0,     0,    16,    36,    17,    18,    19,    20,    21,
      22,   183,    23,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    92,    93,     0,    94,     0,     0,   130,
      32,    33,     0,    95,     0,     0,     0,     0,    34,    35,
      92,    93,     0,    94,     0,     0,    36,     0,     0,     0,
      95,     0,     0,     0,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,     0,     0,     0,     0,
       0,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   200,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    92,    93,   227,    94,     0,     0,
       0,     0,     0,     0,    95,     0,     0,    92,    93,     0,
      94,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,     0,     0,     0,     0,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,     0,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     236,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    92,    93,     0,    94,    91,     0,     0,     0,     0,
       0,    95,     0,     0,    92,    93,     0,    94,     0,     0,
       0,     0,     0,     0,    95,     0,     0,     0,     0,     0,
       0,     0,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,     0,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,    92,    93,     0,
      94,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,     0,     0,    92,    93,     0,    94,     0,     0,     0,
       0,     0,     0,    95,     0,     0,     0,     0,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
       0,     0,     0,   139,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,     0,    92,    93,   164,
      94,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,     0,     0,    92,    93,     0,    94,     0,     0,     0,
       0,     0,     0,    95,     0,     0,     0,     0,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
       0,     0,     0,   165,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,     0,    92,    93,   166,
      94,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,     0,     0,    92,    93,     0,    94,     0,     0,     0,
       0,     0,     0,    95,     0,     0,     0,     0,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
       0,     0,     0,   167,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,     0,    92,    93,   168,
      94,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,     0,     0,    92,    93,     0,    94,     0,     0,     0,
       0,     0,     0,    95,     0,     0,     0,     0,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
       0,     0,     0,   169,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,     0,    92,    93,   170,
      94,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   132,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
      92,    93,     0,    94,     0,     0,     0,     0,     0,     0,
      95,     0,    92,    93,     0,    94,     0,     0,     0,     0,
       0,     0,    95,   208,     0,     0,     0,     0,     0,     0,
       0,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,    95,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107
};

static const yytype_int16 yycheck[] =
{
      16,   130,     7,    26,    12,    13,    14,   136,    24,    26,
      26,    47,    45,    46,    50,    51,    32,    33,    34,    35,
      36,    48,    49,    44,    51,    59,    26,    60,    62,    59,
      45,    46,    62,     3,    50,    58,    53,    54,    55,    56,
      57,    58,     0,   172,    29,    30,     5,    63,    64,    65,
      66,    67,    68,    69,    59,    55,    56,    57,    58,    75,
       6,    45,    46,    32,    33,     6,     6,    61,    61,     8,
      61,   200,    61,    61,   203,    61,    92,    93,    94,    61,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,     6,   109,     5,   111,     6,     6,   227,     6,
      60,     7,     7,    59,     6,    60,    59,   236,   124,     4,
      60,     6,     7,     5,     9,    10,   132,    12,    13,    14,
      15,    59,     5,    18,    61,    20,    21,    22,    23,    24,
      25,    61,    27,    28,     6,    11,    31,    59,     5,    60,
      35,     6,    37,    38,     6,     4,    41,    42,    43,     5,
      45,    46,     4,    38,     4,     6,     4,     6,    53,    54,
       6,   177,     5,     4,     4,     7,    61,     4,   184,   185,
     186,   187,   188,   189,     4,   231,   110,     4,   114,     6,
       7,   112,     9,    10,   128,    12,    13,    14,    15,    90,
     180,    18,   208,    20,    21,    22,    23,    24,    25,   128,
      27,    28,   180,   209,    31,    -1,   220,    -1,    35,   222,
      37,    38,    -1,    -1,    41,    42,    43,    -1,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    -1,     6,
       7,    -1,     9,    10,    61,    12,    13,    14,    15,    -1,
      -1,    18,    -1,    20,    21,    22,    23,    24,    25,    -1,
      27,    28,    -1,    -1,    31,    -1,    -1,    -1,    35,    -1,
      37,    38,    -1,    -1,    41,    42,    43,    -1,    45,    46,
      -1,     6,    -1,    -1,     9,    10,    53,    54,    -1,    -1,
      -1,    -1,    -1,    18,    61,    20,    21,    22,    23,    24,
      25,     4,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,     5,
      45,    46,    -1,    26,    -1,    -1,    -1,    -1,    53,    54,
      16,    17,    -1,    19,    -1,    -1,    61,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,     5,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    17,     5,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    -1,    -1,    16,    17,    -1,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    19,     7,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    16,    17,    -1,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    62,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    16,    17,    62,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    62,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    16,    17,    62,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    62,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    16,    17,    62,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    62,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    16,    17,    62,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      16,    17,    -1,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    16,    17,    -1,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,    64,     3,     0,     5,    65,     4,     6,     7,
       9,    10,    12,    13,    14,    15,    18,    20,    21,    22,
      23,    24,    25,    27,    28,    31,    35,    37,    38,    41,
      42,    43,    45,    46,    53,    54,    61,    66,    67,    74,
      76,    77,    78,    84,    90,    92,    96,   100,    45,    46,
      60,     6,    68,    69,     6,    70,    71,     6,    72,    73,
       8,     6,   100,    61,    61,    61,    61,    61,    61,    61,
      79,   100,     6,    85,   100,     5,     6,    91,     6,    93,
       6,    97,   100,   100,   100,   100,   100,     7,     7,     7,
      59,     7,    16,    17,    19,    26,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,   100,    60,
      59,    60,    59,    60,    59,     6,    75,   100,   100,   100,
     100,   100,   100,   100,    29,    30,    80,    81,    82,    83,
       5,     5,    36,   100,    45,    46,     5,    61,    61,    62,
       6,    77,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,    69,   100,
      71,    11,    73,    59,    62,    62,    62,    62,    62,    62,
      62,   100,     5,    81,    83,    66,    32,    33,    86,    87,
      88,    89,   100,     4,    48,    49,    51,    47,    50,    51,
      66,    12,    13,    14,    94,    95,     6,    98,    99,     6,
       5,    66,     4,     5,   100,     4,    87,    89,    39,    38,
     100,   100,   100,   100,   100,   100,     4,     6,     6,     6,
      59,    62,    59,    62,    66,     4,    66,     5,   100,    91,
      95,     5,    99,     4,     4,    66,     5,     7,    65,     4,
      66,     4,     4
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 161 "tamim.y"
    { printf("\n\n     -------Program Compiled Successfully-------\n\n\n");  ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 162 "tamim.y"
    {/*Do Nothing.*/;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 165 "tamim.y"
    {;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 166 "tamim.y"
    {   ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 167 "tamim.y"
    {;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 168 "tamim.y"
    {;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 169 "tamim.y"
    {;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 170 "tamim.y"
    { printf("%.4lf\n\n",(yyvsp[(1) - (2)].real));
                               (yyval.real) = (yyvsp[(1) - (2)].real); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 173 "tamim.y"
    {conditionMatched=0;;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 174 "tamim.y"
    {;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 175 "tamim.y"
    {;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 177 "tamim.y"
    {   
                        printf("New Module Declared-");
                        printf("Module Name: %s\n",stk[funCnt].fname);
                        printf("Parameters of the Module\n");
                        int ttl = stk[funCnt].varCnt;
                        for(int i = 0;i<ttl;i++)
                        {
                            printf("Parameter Name:%s Data Type: ",stk[funCnt].fptr[i].name);
                            if (stk[funCnt].fptr[i].type == 1)
                                printf("REAL\n");
                            if (stk[funCnt].fptr[i].type == 0)
                                printf("INT\n");
                            if (stk[funCnt].fptr[i].type == 2)
                                printf("STRING\n");
                        }
                        funCnt++;
                        
                ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 195 "tamim.y"
    {;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 203 "tamim.y"
    {;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 204 "tamim.y"
    {;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 208 "tamim.y"
    {
                    int exists = checkExistance((yyvsp[(1) - (3)].string));
                    if(exists){
                        alreadyExist((yyvsp[(1) - (3)].string));
                    }
                    else{
                        int value = (yyvsp[(3) - (3)].real);
                        insertData((yyvsp[(1) - (3)].string),&value,0,varCnt,1);
                        varCnt++;
                    }
                ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 220 "tamim.y"
    {
                    int value = rand();
                    insertData((yyvsp[(1) - (1)].string),&value,0,varCnt,1);
                    varCnt++;
                ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 227 "tamim.y"
    {;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 228 "tamim.y"
    {;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 232 "tamim.y"
    {
                    int exists = checkExistance((yyvsp[(1) - (3)].string));
                    if(exists){
                        alreadyExist((yyvsp[(1) - (3)].string));
                    }
                    else{
                        double value = (yyvsp[(3) - (3)].real);
                        insertData((yyvsp[(1) - (3)].string),&value,1,varCnt,1);
                        varCnt++;
                    }
                ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 244 "tamim.y"
    {
                double value = rand();
                insertData((yyvsp[(1) - (1)].string),&value,1,varCnt,1);
                varCnt++;
            ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 251 "tamim.y"
    {;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 252 "tamim.y"
    {;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 256 "tamim.y"
    {
                    int exists = checkExistance((yyvsp[(1) - (3)].string));
                    if(exists){
                    printf("Variable Already declared.\n\n");
                    }
                    else{
                    char *value= (yyvsp[(3) - (3)].string);
                    insertData((yyvsp[(1) - (3)].string),&value,2,varCnt,1);
                    varCnt++;
                  
                    }
                ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 269 "tamim.y"
    {
                    char* value = "";
                    insertData((yyvsp[(1) - (1)].string),&value,2,varCnt,1);
                    varCnt++;
                ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 279 "tamim.y"
    {   printVariable((yyvsp[(3) - (3)].string));  ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 280 "tamim.y"
    {  printVariable((yyvsp[(1) - (1)].string));   ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 287 "tamim.y"
    {
                    int index = getVariableIndex((yyvsp[(1) - (3)].string));
                    if (index == -1) {    printf("there is no variable named %s.\n\n", (yyvsp[(1) - (3)].string));   }
                    else
                    {
                        {
                            if (vptr[index].type == 1)
                                vptr[index].dval[0] = (yyvsp[(3) - (3)].real);
                            if (vptr[index].type == 0)
                                vptr[index].ival[0] = (yyvsp[(3) - (3)].real);
                        }
                    }
                ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 301 "tamim.y"
    {;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 304 "tamim.y"
    {
                    int isTrue = (fabs((yyvsp[(1) - (4)].real))>1e-9);
                    if(isTrue){                       
                        printf("Condition in if block is true.\n");                      
                        printf(" %.4lf\n\n",(yyvsp[(3) - (4)].real));
                        conditionMatched = 1;
                    }
                    else{    printf("Condition in if block is false.\n");     }
                ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 319 "tamim.y"
    {
                    if(conditionMatched){    printf("Condition already fulfilled.Ignoring else block.\n\n");    }
                    else{
                        double isTrue =1;
                        if(isTrue){                      
                            printf("Condition in else block is true.\n");         
                             printf(" %.4lf\n\n",(yyvsp[(4) - (4)].integer));
                            conditionMatched = 1;
                        }
                        else{  printf("Condition in else block is false.\n");    }
                    }  
                ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 338 "tamim.y"
    {
                    if(conditionMatched) { printf("Condition already fulfilled.Ignoring elif block.\n\n");}              
                    else{
                            int isTrue = (fabs((yyvsp[(2) - (5)].real))>1e-9);
                            if(isTrue){   
                                printf("Condition in elif block is true.\n");
                                printf(" %.4lf\n",(yyvsp[(4) - (5)].real));
                                conditionMatched = 1;
                            }
                            else { printf("Condition in elif block is false.\n");}
                                  
                        }
                ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 354 "tamim.y"
    {conditionMatched = 0;;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 358 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (1)].string));
                    if(id==-1) printf("No such variable");
                    else if(vptr[id].type==2) { printf("can't assign string in choices.");}
                    else if(vptr[id].type==0) choiceValue = vptr[id].ival[0];
                    else choiceValue = vptr[id].dval[0];
                ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 372 "tamim.y"
    {
                    if(conditionMatched) {    printf("Condition already fulfilled.Ignoring default option.\n");  }
                    else{
                          printf("Executing Default Option.No match found.\n");          
                        printf(" %.4lf\n\n",(yyvsp[(3) - (4)].real));
                    }
                ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 386 "tamim.y"
    {
                    if(conditionMatched) {printf("Condition already fulfilled.Ignoring current option\n");}
                        
                    else{
                        int isTrue = (fabs((yyvsp[(2) - (5)].real)-choiceValue)<1e-9);
                            if(isTrue){ 
                                printf("Option matched.\n\n");        
                                printf(" %.4lf\n\n",(yyvsp[(4) - (5)].real));
                                conditionMatched = 1;
                            }
                            else {printf("Condition of current option doesn't match.\n");}    
                    }
                ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 402 "tamim.y"
    {
                    double begin = (yyvsp[(2) - (9)].real);
                    double end = (yyvsp[(4) - (9)].real);
                    double add = (yyvsp[(6) - (9)].real);
                    double x = end-begin;
                    if(x*add < 0) {printf("Infinite  FROM loop\n\n");}
                    else{
                          printf("For will run for %d times\n", (int)(x / add+1));
                          for(double i = begin ; i<=end ; i+=add){
                                printf("%.4lf\n",(yyvsp[(8) - (9)].real));
                             }
                    }   
                ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 416 "tamim.y"
    {                  
                    printf("While will run for %d times\n",(yyvsp[(2) - (5)].integer)); 
                    for(int i = 0;i<(yyvsp[(2) - (5)].integer);i++){
                        printf(" %.4lf\n",(yyvsp[(4) - (5)].real));
                    }
                ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 423 "tamim.y"
    {    
                    printf("repeat while will run for %d times\n",(yyvsp[(6) - (7)].integer));
                    int x=(yyvsp[(6) - (7)].integer);
                    while(x--){   printf(" %.4lf\n",(yyvsp[(3) - (7)].real)); }  
                ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 431 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (4)].string));
                    if(id==-1) doesNotExist((yyvsp[(1) - (4)].string));
                    else if(vptr[id].type!=0) printf("Only applicable for Integer.\n\n");
                    else {
                        long long value = vptr[id].ival[0];
                            if(value> (yyvsp[(4) - (4)].real)){
                                (yyval.integer) = -1;
                            }
                            else{
                                (yyval.integer) = (int) (yyvsp[(4) - (4)].real) - value;
                            }
                    }
                ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 446 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (4)].string));
                    if(id==-1) doesNotExist((yyvsp[(1) - (4)].string));
                    else if(vptr[id].type!=0) printf("Only applicable for Integer.\n");
                    else {
                        long long value = vptr[id].ival[0];
                            if(value> (yyvsp[(4) - (4)].real)){
                                (yyval.integer) = -1;
                            }
                            else{
                                (yyval.integer) = (int) (yyvsp[(4) - (4)].real) - value+1;
                            }
                        }
                ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 461 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (4)].string));
                    if(id==-1) doesNotExist((yyvsp[(1) - (4)].string));
                    else if(vptr[id].type!=0) printf("Only applicable for Integer.\n\n");
                    else {
                        long long value = vptr[id].ival[0];
                            if(value> (yyvsp[(4) - (4)].real)){
                                (yyval.integer) = -1;
                            }
                            else{
                                (yyval.integer) = (int) (yyvsp[(4) - (4)].real) - value;
                            }
                    }
                ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 476 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (4)].string));
                    if(id==-1) doesNotExist((yyvsp[(1) - (4)].string));
                    else if(vptr[id].type!=0) printf("Only applicable for Integer.\n");
                    else {
                        long long value = vptr[id].ival[0];
                            if(value< (yyvsp[(4) - (4)].real)){
                                (yyval.integer) = -1;
                            }
                            else{
                                (yyval.integer) =value -(int) (yyvsp[(4) - (4)].real);
                            }
                    }
                ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 491 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (4)].string));
                    if(id==-1) doesNotExist((yyvsp[(1) - (4)].string));
                    else if(vptr[id].type!=0) printf("Only applicable for Integer.\n");
                    else {
                        long long value = vptr[id].ival[0];
                            if(value< (yyvsp[(4) - (4)].real)){
                                (yyval.integer) = -1;
                            }
                            else{
                                (yyval.integer) =value -(int) (yyvsp[(4) - (4)].real)+1;
                            }
                    }
                ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 506 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (4)].string));
                    if(id==-1) doesNotExist((yyvsp[(1) - (4)].string));
                    else if(vptr[id].type!=0) printf("Only applicable for Integer.\n");
                    else {
                        long long value = vptr[id].ival[0];
                            if(value< (yyvsp[(4) - (4)].real)){
                                (yyval.integer) = -1;
                            }
                            else{
                                (yyval.integer) =value -(int) (yyvsp[(4) - (4)].real);
                            }
                    }
                ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 527 "tamim.y"
    {
                    int id = getFunctionIndex((yyvsp[(1) - (1)].string));
                    if(id!=-1){printf("Module Already Declared\n");}
                    else{
                        printf("Declaring Module\n\n");
                        stk[funCnt].fname = malloc((strlen((yyvsp[(1) - (1)].string))+10)*sizeof(char));
                        strcpy(stk[funCnt].fname,(yyvsp[(1) - (1)].string));
                        stk[funCnt].varCnt = 0; 
                        stk[funCnt].fptr = malloc(4*sizeof(stack));
                    }
                ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 545 "tamim.y"
    {
                    int id = stk[funCnt].varCnt;
                    int value = rand();
                    insertData((yyvsp[(2) - (2)].string),&value,0,varCnt,1);
                    stk[funCnt].fptr[id] = vptr[varCnt];
                    varCnt++;
                    stk[funCnt].varCnt++;
                ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 554 "tamim.y"
    {
                    int id = stk[funCnt].varCnt;
                    double value = rand();
                    insertData((yyvsp[(2) - (2)].string),&value,1,varCnt,1);
                    stk[funCnt].fptr[id] = vptr[varCnt];
                    varCnt++;
                    stk[funCnt].varCnt++;
                ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 563 "tamim.y"
    {
                    int id = stk[funCnt].varCnt;
                    char* value = "";
                    insertData((yyvsp[(1) - (2)].string),&value,2,varCnt,1);
                    stk[funCnt].fptr[id] = vptr[varCnt];
                    varCnt++;
                    stk[funCnt].varCnt++;
                ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 574 "tamim.y"
    {
                    if(functionRejected){
                        
                        printf("Module was not called as declared\n");
                        
                    }
                    else{
                        printf("Module called Successfully.\n\n");
                    }
                ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 587 "tamim.y"
    {
                    int id = getFunctionIndex((yyvsp[(1) - (1)].string));
                    if(id==-1){printf(" No Function Exist with this name.\n");}
                    else{
                        currentFunction = id;
                        currentParam = 0;
                        functionRejected = 0;
                    }
                ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 603 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (1)].string));
                    if(currentParam>=stk[currentFunction].varCnt){
                        
                        printf("More variable than declared\n");
                        
                        functionRejected = 1;
                    }
                    else if(stk[currentFunction].fptr[currentParam].type!=vptr[id].type){
                        
                        printf("Data Type doesn't match\n");
                        functionRejected = 1;
                    }
                    else{
                        currentParam++;
                    }
                ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 625 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (1)].integer);
                ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 629 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (1)].real);
                ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 634 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (1)].string));
                    if(id==-1) doesNotExist;
                    else if(vptr[id].type==2){
                        notNumeric();
                    }
                    else if(vptr[id].type==0) (yyval.real) = vptr[id].ival[0];
                    else (yyval.real) = vptr[id].dval[0];
                ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 643 "tamim.y"
    { (yyval.real) = (yyvsp[(2) - (2)].real);;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 644 "tamim.y"
    { (yyval.real) = -(yyvsp[(2) - (2)].real);;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 645 "tamim.y"
    {(yyval.real) = (yyvsp[(2) - (2)].real);;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 646 "tamim.y"
    {(yyval.real) = (yyvsp[(2) - (2)].real);;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 647 "tamim.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) + (yyvsp[(3) - (3)].real);;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 648 "tamim.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) - (yyvsp[(3) - (3)].real);;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 649 "tamim.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) * (yyvsp[(3) - (3)].real);;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 650 "tamim.y"
    {(yyval.real) = (yyvsp[(1) - (3)].real) / (yyvsp[(3) - (3)].real);;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 651 "tamim.y"
    {(yyval.real) = pow((yyvsp[(1) - (3)].real),(yyvsp[(3) - (3)].real));;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 652 "tamim.y"
    {(yyval.real) = (int)(yyvsp[(1) - (3)].real) % (int)(yyvsp[(3) - (3)].real);;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 653 "tamim.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) < (yyvsp[(3) - (3)].real));;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 654 "tamim.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) > (yyvsp[(3) - (3)].real));;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 655 "tamim.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) <= (yyvsp[(3) - (3)].real));;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 656 "tamim.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) >= (yyvsp[(3) - (3)].real));;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 657 "tamim.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) == (yyvsp[(3) - (3)].real));;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 658 "tamim.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) != (yyvsp[(3) - (3)].real));;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 659 "tamim.y"
    {(yyval.real) = ( (yyvsp[(1) - (3)].real) && (yyvsp[(3) - (3)].real));;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 660 "tamim.y"
    {(yyval.real) = ((yyvsp[(1) - (3)].real) || (yyvsp[(3) - (3)].real));;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 661 "tamim.y"
    {(yyval.real) = ((int)(yyvsp[(1) - (3)].real) ^ (int)(yyvsp[(3) - (3)].real));;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 662 "tamim.y"
    {(yyval.real) = !(yyvsp[(2) - (2)].real);;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 663 "tamim.y"
    {(yyval.real) = (yyvsp[(2) - (3)].real);;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 664 "tamim.y"
    { (yyval.real) = sin((yyvsp[(3) - (4)].real));;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 665 "tamim.y"
    {  (yyval.real) = cos((yyvsp[(3) - (4)].real));;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 666 "tamim.y"
    {    (yyval.real) = tan((yyvsp[(3) - (4)].real));;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 667 "tamim.y"
    { (yyval.real) = log10((yyvsp[(3) - (4)].real));;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 668 "tamim.y"
    {(yyval.real) = log2((yyvsp[(3) - (4)].real));;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 669 "tamim.y"
    { (yyval.real) = log((yyvsp[(3) - (4)].real));;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 670 "tamim.y"
    { (yyval.real) = sqrt((yyvsp[(3) - (4)].real));     ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 672 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (2)].string));
                    if(id==-1) doesNotExist;
                    else if(vptr[id].type==2) notNumeric();
                    else if(vptr[id].type==1) printf("can't increment real.");
                    else {
                        vptr[id].ival[0]++;
                        (yyval.real) = vptr[id].ival[0];
                    }
                
                ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 684 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (2)].string));
                    if(id==-1) doesNotExist((yyvsp[(1) - (2)].string));
                    else if(vptr[id].type==2) notNumeric();
                    else if(vptr[id].type==1) printf("can't decrement real.");
                    else {
                        vptr[id].ival[0]--;
                        (yyval.real) = vptr[id].ival[0];
                    }
                ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 695 "tamim.y"
    {
                    int cl = ceil((yyvsp[(1) - (2)].real));int fl = floor((yyvsp[(1) - (2)].real));
                    if(cl!=fl) printf("can't find FACTORIAL of real number.\n");
                    else {
                        long long x = 1;
                        for(long long i=1;i<=(yyvsp[(1) - (2)].real);i++) x*=i;
                        (yyval.real) = x;
                    }
                ;}
    break;



/* Line 1455 of yacc.c  */
#line 2774 "tamim.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 705 "tamim.y"

int main() { 
    initialize_globals();
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        printf("Error opening input file");  
    }
    freopen("output.txt", "w", stdout);
    printf("\n-------Starting Program Execution-------\n\n\n");
    yyparse();
    return 0;
}
 
     



