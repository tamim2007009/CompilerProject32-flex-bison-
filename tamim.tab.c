
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
	#include<conio.h>
	#include<string.h>
	#include<math.h>
    #include <windows.h>
    #include <io.h>
    #include <direct.h>
    #define YYDEBUG 1
    extern FILE *yyin;
    extern FILE *yyout;
	int yylex();
	int yyparse();
	int yyerror(char *s);

    /* structure for storing variables.*/
    typedef struct variable{
        char *name;
        int type; /* indicates data type- 0:int,1:double,2:char* */
        int *ival;
        double *dval;
        char** sval;
        int size;
        int isArray;
    }var;

    /*structure for storing user-defined modules(functions).*/
    typedef struct functionstack{
        char *fname;
        var *fptr;
        int varCnt;
    }stack;

    /*Initial Pointers to store variable and modules.*/
   /* Declare and initialize pointers globally */
var *vptr = NULL;   // Pointer to variable storage
stack *stk = NULL;  // Pointer to function stack
//int vartaken = 100; // Example of other global variables
     
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



    /* Helper variables.*/
    int varCnt = 0,funCnt=0; /* variable and functions taken so far.*/
    int vartaken = 0,funtaken=0; /* memory assigned for them so far.*/
    int cnt = 0; /* counts array element during declaration. */
    int *itmp;
    double *dtmp;  /* Stores array value temporarily to insert later*/
    char **stmp;
    int conditionMatched; /* 1 if condition is matched in conditional statements(if-else,choice) */
    double choiceValue; /* stores the value of choice to check in options. */
    int currentFunction; /* module index that is being called currently. */
    int currentParam; /* paramaters that have been processed of the calling function so far. */
    int functionRejected; /* 1 if calling module structure doesn't match. */

    /* ------------------- Helper Functions------------------- */
        /* Checks if a variable is already declared. */
        int checkExistance(char *varName){
            for(int i = 0 ; i<varCnt; i++){
                if(strcmp(vptr[i].name,varName)==0){
                    return 1;
                }
            }
            return 0;
        }

        /* Get the index of variable that is called. If not found return -1. */
        int getVariableIndex(char *varName){
            for(int i = 0 ; i<varCnt; i++){
                if(strcmp(vptr[i].name,varName)==0){
                    return i;
                }
            }
            return -1;
        }
        /* Error Handling Function: No variable */
        void doesNotExist(char *varName){
            
            printf("There is No Such Variable Named: %s\n",varName);
           
        } 
        /* Error Handling Function: Not an array */ 
        void notArray(char *varName){
           
            printf("%s is not an Array.\n",varName);
        
        }
        /* Error Handling Function: out of bound */ 
        void outOfRange(){
           
            printf("Trying to Access index out of Range.\n");
           
        }
        /* Error Handling Function: empty Array. */ 
        void emptyArray(){
          
            printf("Array is already empty.\n");
            
        }
        /* Error Handling Function: Already Declared. */
        void alreadyExist(char *varName){
            
            printf("%s is already Declared.\n",varName);

        }
        /* Error Handling Function: Applying arithmetic on string. */
        void notNumeric(){
         
            printf("String literals not applicable.\n");
             
        }
        /* Error Handling Function: Applying arithmetic on double. */
        void notInt(){
             
            printf("Applicable of Integer only.\n");
             
        }
        /* Insert New variable in array. */
        /* void pointer is used so that I can typecast it to the type defined by type variable. */
        void insertData(char *varname,void* value,int type,int id,int size,int isArray){
            vptr[id].name = varname;
            vptr[id].size = size;
            vptr[id].isArray = isArray;
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

        /* Printing a variable (including array)*/
        void printVariable(char *varName){
            int index = getVariableIndex(varName);
            if (index == -1)
            {
                doesNotExist(varName);
            }
            else
            {
                if (vptr[index].isArray)
                {
                    printf("%s is an array with %d elements.Elements are:\n", varName, vptr[index].size);
                    for (int i = 0; i < vptr[index].size; i++)
                    {
                        if (vptr[index].type == 1)
                            printf("%lf ", vptr[index].dval[i]);
                        if (vptr[index].type == 0)
                            printf("%d ", vptr[index].ival[i]);
                        if (vptr[index].type == 2)
                            printf("%s ", vptr[index].sval[i]);
                        if (i % 10 == 9)
                            puts("");
                    }
                    puts("");
                }
                else
                {
                    printf("Value of %s is:",varName);
                    if (vptr[index].type == 1)
                        printf("%lf\n", vptr[index].dval[0]);
                    if (vptr[index].type == 0)
                        printf("%d\n", vptr[index].ival[0]);
                    if (vptr[index].type == 2)
                        printf("%s\n", vptr[index].sval[0]);
                }
            }
        }



       

        /* --- Helper Function for Modules. ---*/
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
#line 293 "tamim.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
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

/* Line 214 of yacc.c  */
#line 222 "tamim.y"

	int integer;
	double real;
	char* string;



/* Line 214 of yacc.c  */
#line 388 "tamim.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 400 "tamim.tab.c"

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
#define YYLAST   875

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  123
/* YYNRULES -- Number of states.  */
#define YYNSTATES  274

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    58,     2,     2,
      66,    67,    56,    54,    60,    55,     2,    57,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      48,    61,    49,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    64,     2,    65,    59,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,     2,    63,     2,     2,     2,     2,
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
      45,    46,    47,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    10,    13,    15,    17,    20,    23,
      26,    29,    31,    33,    35,    37,    39,    42,    45,    48,
      52,    54,    58,    60,    62,    68,    72,    74,    78,    80,
      84,    86,    88,    94,    98,   100,   104,   106,   110,   112,
     114,   120,   124,   126,   130,   134,   138,   140,   144,   146,
     150,   157,   161,   166,   167,   169,   172,   174,   179,   182,
     184,   190,   196,   198,   201,   203,   208,   211,   213,   219,
     229,   235,   243,   248,   253,   258,   263,   268,   273,   282,
     284,   288,   290,   293,   296,   299,   305,   307,   311,   313,
     315,   317,   319,   321,   324,   327,   330,   333,   337,   341,
     345,   349,   353,   357,   361,   365,   369,   373,   377,   381,
     385,   389,   393,   396,   400,   405,   410,   415,   420,   425,
     430,   435,   438,   441
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      69,     0,    -1,    45,     3,     5,    70,     4,    -1,    -1,
      70,    71,    -1,     8,    -1,    42,    -1,    72,     8,    -1,
      84,     8,    -1,    82,     8,    -1,   108,     8,    -1,    86,
      -1,    92,    -1,    98,    -1,   100,    -1,   104,    -1,    13,
      73,    -1,    14,    76,    -1,    15,    79,    -1,    73,    60,
      74,    -1,    74,    -1,     6,    61,   108,    -1,     6,    -1,
       7,    -1,     7,    61,    62,    75,    63,    -1,    75,    60,
     108,    -1,   108,    -1,    76,    60,    77,    -1,    77,    -1,
       6,    61,   108,    -1,     6,    -1,     7,    -1,     7,    61,
      62,    78,    63,    -1,    78,    60,   108,    -1,   108,    -1,
      79,    60,    80,    -1,    80,    -1,     6,    61,    12,    -1,
       6,    -1,     7,    -1,     7,    61,    62,    81,    63,    -1,
      81,    60,    12,    -1,    12,    -1,    16,     9,    83,    -1,
      83,    60,     6,    -1,    83,    60,     7,    -1,     6,    -1,
      84,    60,    85,    -1,    85,    -1,     6,    61,   108,    -1,
       7,    64,    10,    65,    61,   108,    -1,    29,    87,    88,
      -1,   108,     5,    71,     4,    -1,    -1,    90,    -1,    90,
      89,    -1,    89,    -1,    31,     5,    71,     4,    -1,    90,
      91,    -1,    91,    -1,    30,   108,     5,    71,     4,    -1,
      32,    93,     5,    94,     4,    -1,     6,    -1,    96,    95,
      -1,    95,    -1,    33,     5,    71,     4,    -1,    96,    97,
      -1,    97,    -1,    34,   108,     5,    71,     4,    -1,    36,
     108,    37,   108,    40,   108,     5,    71,     4,    -1,    39,
      99,     5,    71,     4,    -1,    38,     5,   108,     4,    39,
      99,     8,    -1,     6,    47,    48,   108,    -1,     6,    47,
      51,   108,    -1,     6,    47,    52,   108,    -1,     6,    46,
      49,   108,    -1,     6,    46,    50,   108,    -1,     6,    46,
      52,   108,    -1,    43,   101,    66,   102,    67,     5,    70,
       4,    -1,     6,    -1,   102,    60,   103,    -1,   103,    -1,
      13,     6,    -1,    14,     6,    -1,    15,     6,    -1,    44,
     105,    66,   106,    67,    -1,     6,    -1,   106,    60,   107,
      -1,   107,    -1,     6,    -1,    10,    -1,    11,    -1,     6,
      -1,    54,   108,    -1,    55,   108,    -1,    47,   108,    -1,
      46,   108,    -1,   108,    54,   108,    -1,   108,    55,   108,
      -1,   108,    56,   108,    -1,   108,    57,   108,    -1,   108,
      59,   108,    -1,   108,    58,   108,    -1,   108,    48,   108,
      -1,   108,    49,   108,    -1,   108,    51,   108,    -1,   108,
      50,   108,    -1,   108,    53,   108,    -1,   108,    52,   108,
      -1,   108,    17,   108,    -1,   108,    18,   108,    -1,   108,
      20,   108,    -1,    19,   108,    -1,    66,   108,    67,    -1,
      24,    66,   108,    67,    -1,    25,    66,   108,    67,    -1,
      26,    66,   108,    67,    -1,    21,    66,   108,    67,    -1,
      22,    66,   108,    67,    -1,    23,    66,   108,    67,    -1,
      28,    66,   108,    67,    -1,     6,    47,    -1,     6,    46,
      -1,   108,    27,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   254,   254,   261,   262,   265,   266,   272,   273,   274,
     275,   282,   284,   285,   286,   306,   310,   311,   312,   315,
     316,   319,   331,   337,   342,   351,   357,   365,   366,   369,
     381,   387,   393,   402,   408,   416,   417,   420,   433,   439,
     445,   455,   461,   469,   472,   476,   481,   489,   490,   494,
     511,   535,   538,   555,   556,   557,   558,   560,   585,   586,
     589,   616,   620,   635,   636,   639,   655,   656,   659,   685,
     702,   711,   719,   734,   749,   764,   779,   794,   812,   815,
     829,   830,   833,   842,   851,   862,   875,   887,   888,   891,
     913,   917,   922,   932,   936,   940,   944,   948,   952,   956,
     960,   964,   968,   973,   977,   981,   985,   989,   993,   997,
    1001,  1005,  1009,  1013,  1017,  1022,  1026,  1030,  1034,  1038,
    1042,  1046,  1058,  1069
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ROOT", "END", "START", "VARIABLE",
  "ARRAY_VAR", "EOL", "ARROW", "INTEGER", "REAL", "STRING", "INT_TYPE",
  "REAL_TYPE", "STRING_TYPE", "SEE", "AND", "OR", "NOT", "XOR", "LOG",
  "LOG2", "LN", "SIN", "COS", "TAN", "FACTORIAL", "SQRT", "IF", "ELIF",
  "ELSE", "CHOICE", "DEFAULT", "OPTION", "FOREACH", "FROM", "TO", "DO",
  "WHILE", "BY", "AS", "COMMENT", "MODULE", "CALL", "IMPORT", "MMINUS",
  "PPLUS", "'<'", "'>'", "GEQL", "LEQL", "NEQL", "EQL", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'^'", "','", "'='", "'{'", "'}'", "'['", "']'",
  "'('", "')'", "$accept", "program", "statements", "statement",
  "declaration", "int_variables", "int_var", "ints", "real_variables",
  "real_var", "reals", "string_variables", "string_var", "strings", "show",
  "print_vars", "assigns", "assign", "if_blocks", "if_block",
  "else_statement", "single_else", "elif_statement", "single_elif",
  "choice_block", "choice_variable", "options", "default", "optionlist",
  "option", "loop_block", "while_conditions", "module_declare",
  "module_name", "module_variable", "single_var", "module_call",
  "user_module_name", "user_parameters", "single_param", "expr", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,    60,    62,
     303,   304,   305,   306,    43,    45,    42,    47,    37,    94,
      44,    61,   123,   125,    91,    93,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    69,    70,    70,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    72,    72,    72,    73,
      73,    74,    74,    74,    74,    75,    75,    76,    76,    77,
      77,    77,    77,    78,    78,    79,    79,    80,    80,    80,
      80,    81,    81,    82,    83,    83,    83,    84,    84,    85,
      85,    86,    87,    88,    88,    88,    88,    89,    90,    90,
      91,    92,    93,    94,    94,    95,    96,    96,    97,    98,
      98,    98,    99,    99,    99,    99,    99,    99,   100,   101,
     102,   102,   103,   103,   103,   104,   105,   106,   106,   107,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     2,     1,     1,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     2,     2,     2,     3,
       1,     3,     1,     1,     5,     3,     1,     3,     1,     3,
       1,     1,     5,     3,     1,     3,     1,     3,     1,     1,
       5,     3,     1,     3,     3,     3,     1,     3,     1,     3,
       6,     3,     4,     0,     1,     2,     1,     4,     2,     1,
       5,     5,     1,     2,     1,     4,     2,     1,     5,     9,
       5,     7,     4,     4,     4,     4,     4,     4,     8,     1,
       3,     1,     2,     2,     2,     5,     1,     3,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     4,     4,     4,     4,     4,     4,
       4,     2,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     2,    92,     0,
       5,    90,    91,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     0,     0,     0,     0,     0,     0,     0,     4,     0,
       0,     0,    48,    11,    12,    13,    14,    15,     0,   122,
     121,     0,     0,    22,    23,    16,    20,    30,    31,    17,
      28,    38,    39,    18,    36,     0,    92,   112,     0,     0,
       0,     0,     0,     0,     0,    53,     0,    62,     0,     0,
       0,     0,     0,    79,     0,    86,     0,    96,    95,    93,
      94,     0,     7,     9,     8,     0,    10,     0,     0,     0,
     123,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,    56,    54,    59,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,     0,
      47,   109,   110,   111,   103,   104,   106,   105,   108,   107,
      97,    98,    99,   100,   102,   101,     0,    21,     0,    19,
      29,     0,    27,    37,     0,    35,     0,   117,   118,   119,
     114,   115,   116,   120,     0,     0,    55,    58,     0,     0,
       0,     0,    64,     0,    67,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    81,    89,
       0,    88,     0,     0,    26,     0,    34,    42,     0,    44,
      45,     0,     0,    52,     0,     0,    61,    63,    66,     0,
       0,    75,    76,    77,    72,    73,    74,    70,    82,    83,
      84,     0,     0,     0,    85,    50,     0,    24,     0,    32,
       0,    40,     0,    57,     0,     0,     0,     0,    80,     3,
      87,    25,    33,    41,    60,    65,     0,     0,    71,     0,
      68,     0,    78,    69
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,    38,    39,    55,    56,   213,    59,    60,
     215,    63,    64,   218,    40,   125,    41,    42,    43,    75,
     135,   136,   137,   138,    44,    78,   191,   192,   193,   194,
      45,    82,    46,    84,   207,   208,    47,    86,   210,   211,
      48
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -125
static const yytype_int16 yypact[] =
{
       5,   120,    39,   124,  -125,  -125,   194,  -125,   -34,    74,
    -125,  -125,  -125,    -3,    58,    72,   133,   111,    80,    82,
      83,    84,    86,    87,    89,   111,   141,   111,   151,   153,
    -125,   154,   155,   111,   111,   111,   111,   111,  -125,   156,
     159,    -2,  -125,  -125,  -125,  -125,  -125,  -125,   474,  -125,
    -125,   111,   152,   102,   108,   110,  -125,   113,   114,   112,
    -125,   115,   117,   119,  -125,   162,    79,    56,   111,   111,
     111,   111,   111,   111,   111,    -6,   334,  -125,   166,   761,
     111,    81,   181,  -125,   121,  -125,   122,   816,   816,   -16,
     -16,   486,  -125,  -125,  -125,    96,  -125,   111,   111,   111,
    -125,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   816,   125,   111,   127,    -3,   111,   129,
      58,   180,   131,    72,  -125,   134,   529,   549,   592,   612,
     655,   675,   718,   111,   191,  -125,  -125,    -6,  -125,   302,
     107,   111,    18,    10,    -4,   302,   105,   193,  -125,   136,
    -125,    56,    56,    56,   -26,   -26,   -26,   -26,   -26,   -26,
     -16,   -16,   -22,   -22,   -22,   -22,   142,   816,   111,  -125,
     816,   111,  -125,  -125,   199,  -125,   138,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,   353,   302,  -125,  -125,   202,   209,
     111,   217,  -125,   107,  -125,   804,   185,   111,   111,   111,
     111,   111,   111,   221,   222,   228,   229,   -58,  -125,  -125,
     -53,  -125,   111,   -37,   816,   -14,   816,  -125,    36,  -125,
    -125,   302,   223,  -125,   302,   408,  -125,  -125,  -125,   111,
     153,   816,   816,   816,   816,   816,   816,  -125,  -125,  -125,
    -125,   105,   234,   193,  -125,   816,   111,  -125,   111,  -125,
     230,  -125,   239,  -125,   240,   302,   422,   237,  -125,  -125,
    -125,   816,   816,  -125,  -125,  -125,   242,   302,  -125,   248,
    -125,   243,  -125,  -125
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -125,  -125,    -9,  -124,  -125,  -125,   140,  -125,  -125,   145,
    -125,  -125,   128,  -125,  -125,  -125,  -125,   158,  -125,  -125,
    -125,   144,  -125,   146,  -125,  -125,  -125,    73,  -125,    75,
    -125,    45,  -125,  -125,  -125,    37,  -125,  -125,  -125,    42,
     -17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      67,   100,   241,    53,    54,   100,    94,   243,    76,   242,
      79,   100,    49,    50,   244,   188,    87,    88,    89,    90,
      91,   203,   196,   246,   133,   134,   247,    51,   107,   108,
     109,   110,   111,   112,   113,    97,    98,   112,    99,     4,
     109,   110,   111,   112,   200,   100,   248,   201,   202,   249,
       1,   126,   127,   128,   129,   130,   131,   132,    95,   197,
     198,   222,   199,   142,    57,    58,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,    61,    62,
     151,   152,   153,   100,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   250,   252,   167,   251,
     254,   170,   149,     9,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   184,    66,   204,   205,
     206,    11,    12,     3,   195,    49,    50,   143,   144,     5,
      17,   266,    18,    19,    20,    21,    22,    23,    52,    24,
     189,   190,    65,   271,   219,   220,    68,    77,    69,    70,
      71,   214,    72,    73,   216,    74,    80,    33,    34,    81,
      83,    85,   114,   115,    92,    35,    36,    93,   124,   116,
     117,   140,   120,   225,   118,   119,   121,    37,   122,   123,
     231,   232,   233,   234,   235,   236,   145,   146,   147,   168,
     166,   171,   173,   174,   176,   245,   185,    51,     7,   209,
       8,     9,    10,   212,    11,    12,   223,    13,    14,    15,
      16,   217,   256,    17,   224,    18,    19,    20,    21,    22,
      23,   226,    24,    25,   230,   237,    26,   253,   238,   261,
      27,   262,    28,    29,   239,   240,    30,    31,    32,   259,
      33,    34,   263,   264,   265,   268,   270,   273,    35,    36,
     269,   175,   272,   150,     8,     9,    10,   169,    11,    12,
      37,    13,    14,    15,    16,   172,   227,    17,   228,    18,
      19,    20,    21,    22,    23,   257,    24,    25,   258,     0,
      26,   186,     0,   187,    27,   260,    28,    29,     0,     0,
      30,    31,    32,     0,    33,    34,     0,     0,     0,     0,
       0,     0,    35,    36,     0,     0,     0,     0,     8,     9,
      10,     0,    11,    12,    37,    13,    14,    15,    16,     0,
       0,    17,     0,    18,    19,    20,    21,    22,    23,     0,
      24,    25,     0,     0,    26,     0,     0,     0,    27,   139,
      28,    29,     0,     0,    30,    31,    32,     0,    33,    34,
       0,    97,    98,     0,    99,     0,    35,    36,   221,     0,
       0,   100,     0,     0,     0,     0,     0,     0,    37,     0,
      97,    98,     0,    99,     0,     0,     0,     0,     0,     0,
     100,     0,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,     0,     0,     0,     0,     0,     0,
       0,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   255,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    97,    98,   267,    99,     0,
       0,     0,     0,     0,     0,   100,     0,     0,     0,    97,
      98,     0,    99,     0,     0,     0,     0,     0,     0,   100,
       0,     0,     0,     0,     0,     0,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,     0,     0,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,    96,     0,     0,     0,     0,     0,     0,     0,
       0,    97,    98,     0,    99,     0,     0,     0,     0,     0,
       0,   100,     0,    97,    98,     0,    99,     0,     0,     0,
       0,     0,     0,   100,     0,     0,     0,     0,     0,     0,
       0,     0,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,    97,    98,     0,    99,
       0,     0,     0,   148,     0,     0,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    97,    98,     0,    99,
       0,     0,     0,     0,     0,     0,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,   177,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,    97,
      98,     0,    99,     0,     0,     0,   178,     0,     0,   100,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    97,
      98,     0,    99,     0,     0,     0,     0,     0,     0,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,     0,     0,     0,     0,     0,     0,     0,   179,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,    97,    98,     0,    99,     0,     0,     0,   180,
       0,     0,   100,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    97,    98,     0,    99,     0,     0,     0,     0,
       0,     0,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,     0,     0,     0,     0,     0,
       0,     0,   181,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,    97,    98,     0,    99,     0,
       0,     0,   182,     0,     0,   100,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,    97,    98,
       0,    99,     0,     0,     0,   183,     0,     0,   100,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   141,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,    97,    98,     0,    99,     0,     0,     0,     0,     0,
       0,   100,     0,    97,    98,     0,    99,     0,     0,     0,
       0,     0,     0,   100,   229,     0,     0,     0,     0,     0,
       0,     0,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112
};

static const yytype_int16 yycheck[] =
{
      17,    27,    60,     6,     7,    27,     8,    60,    25,    67,
      27,    27,    46,    47,    67,   139,    33,    34,    35,    36,
      37,   145,     4,    60,    30,    31,    63,    61,    54,    55,
      56,    57,    58,    59,    51,    17,    18,    59,    20,     0,
      56,    57,    58,    59,    48,    27,    60,    51,    52,    63,
      45,    68,    69,    70,    71,    72,    73,    74,    60,    49,
      50,   185,    52,    80,     6,     7,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,     6,     7,
      97,    98,    99,    27,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,    60,   221,   115,    63,
     224,   118,     6,     7,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,   133,     6,    13,    14,
      15,    10,    11,     3,   141,    46,    47,    46,    47,     5,
      19,   255,    21,    22,    23,    24,    25,    26,    64,    28,
      33,    34,     9,   267,     6,     7,    66,     6,    66,    66,
      66,   168,    66,    66,   171,    66,     5,    46,    47,     6,
       6,     6,    10,    61,     8,    54,    55,     8,     6,    61,
      60,     5,    60,   190,    61,    61,    61,    66,    61,    60,
     197,   198,   199,   200,   201,   202,     5,    66,    66,    62,
      65,    62,    12,    62,    60,   212,     5,    61,     4,     6,
       6,     7,     8,    61,    10,    11,     4,    13,    14,    15,
      16,    12,   229,    19,     5,    21,    22,    23,    24,    25,
      26,     4,    28,    29,    39,     4,    32,     4,     6,   246,
      36,   248,    38,    39,     6,     6,    42,    43,    44,     5,
      46,    47,    12,     4,     4,     8,     4,     4,    54,    55,
     259,   123,     4,    95,     6,     7,     8,   117,    10,    11,
      66,    13,    14,    15,    16,   120,   193,    19,   193,    21,
      22,    23,    24,    25,    26,   230,    28,    29,   241,    -1,
      32,   137,    -1,   137,    36,   243,    38,    39,    -1,    -1,
      42,    43,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    -1,    -1,    -1,    -1,     6,     7,
       8,    -1,    10,    11,    66,    13,    14,    15,    16,    -1,
      -1,    19,    -1,    21,    22,    23,    24,    25,    26,    -1,
      28,    29,    -1,    -1,    32,    -1,    -1,    -1,    36,     5,
      38,    39,    -1,    -1,    42,    43,    44,    -1,    46,    47,
      -1,    17,    18,    -1,    20,    -1,    54,    55,     5,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      17,    18,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,     5,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,     5,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,    17,
      18,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    17,    18,    -1,    20,
      -1,    -1,    -1,    67,    -1,    -1,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    27,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    17,
      18,    -1,    20,    -1,    -1,    -1,    67,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    17,    18,    -1,    20,    -1,    -1,    -1,    67,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    17,    18,    -1,    20,    -1,
      -1,    -1,    67,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    17,    18,
      -1,    20,    -1,    -1,    -1,    67,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    45,    69,     3,     0,     5,    70,     4,     6,     7,
       8,    10,    11,    13,    14,    15,    16,    19,    21,    22,
      23,    24,    25,    26,    28,    29,    32,    36,    38,    39,
      42,    43,    44,    46,    47,    54,    55,    66,    71,    72,
      82,    84,    85,    86,    92,    98,   100,   104,   108,    46,
      47,    61,    64,     6,     7,    73,    74,     6,     7,    76,
      77,     6,     7,    79,    80,     9,     6,   108,    66,    66,
      66,    66,    66,    66,    66,    87,   108,     6,    93,   108,
       5,     6,    99,     6,   101,     6,   105,   108,   108,   108,
     108,   108,     8,     8,     8,    60,     8,    17,    18,    20,
      27,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,   108,    10,    61,    61,    60,    61,    61,
      60,    61,    61,    60,     6,    83,   108,   108,   108,   108,
     108,   108,   108,    30,    31,    88,    89,    90,    91,     5,
       5,    37,   108,    46,    47,     5,    66,    66,    67,     6,
      85,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,    65,   108,    62,    74,
     108,    62,    77,    12,    62,    80,    60,    67,    67,    67,
      67,    67,    67,    67,   108,     5,    89,    91,    71,    33,
      34,    94,    95,    96,    97,   108,     4,    49,    50,    52,
      48,    51,    52,    71,    13,    14,    15,   102,   103,     6,
     106,   107,    61,    75,   108,    78,   108,    12,    81,     6,
       7,     5,    71,     4,     5,   108,     4,    95,    97,    40,
      39,   108,   108,   108,   108,   108,   108,     4,     6,     6,
       6,    60,    67,    60,    67,   108,    60,    63,    60,    63,
      60,    63,    71,     4,    71,     5,   108,    99,   103,     5,
     107,   108,   108,    12,     4,     4,    71,     5,     8,    70,
       4,    71,     4,     4
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
#line 255 "tamim.y"
    {
                printf("\n\n     -------Program Compiled Successfully-------\n\n\n");
            ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 261 "tamim.y"
    {/*Do Nothing.*/;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 265 "tamim.y"
    {;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 267 "tamim.y"
    {
                   
                    printf("  %s\n",(yyvsp[(1) - (1)].string));
                    
                ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 272 "tamim.y"
    {;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 273 "tamim.y"
    {;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 274 "tamim.y"
    {;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 276 "tamim.y"
    {
                    
                    printf("Value of the expression:%.4lf\n",(yyvsp[(1) - (2)].real));
                    (yyval.real) = (yyvsp[(1) - (2)].real);
                    
                ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 283 "tamim.y"
    {conditionMatched=0;;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 284 "tamim.y"
    {;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 285 "tamim.y"
    {;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 287 "tamim.y"
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
#line 306 "tamim.y"
    {;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 315 "tamim.y"
    {;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 316 "tamim.y"
    {;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 320 "tamim.y"
    {
                    int exists = checkExistance((yyvsp[(1) - (3)].string));
                    if(exists){
                        alreadyExist((yyvsp[(1) - (3)].string));
                    }
                    else{
                        int value = (yyvsp[(3) - (3)].real);
                        insertData((yyvsp[(1) - (3)].string),&value,0,varCnt,1,0);
                        varCnt++;
                    }
                ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 332 "tamim.y"
    {
                    int value = rand();
                    insertData((yyvsp[(1) - (1)].string),&value,0,varCnt,1,0);
                    varCnt++;
                ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 338 "tamim.y"
    {
                    insertData((yyvsp[(1) - (1)].string),itmp,0,varCnt,cnt,1);
                    varCnt++;
                ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 343 "tamim.y"
    {
                    insertData((yyvsp[(1) - (5)].string),itmp,0,varCnt,cnt,1);
                    varCnt++;
                    cnt = 0;
                    free(itmp);
                ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 352 "tamim.y"
    {
                    cnt++;
                    itmp = realloc(itmp,cnt*sizeof(int));;
                    itmp[cnt-1]=(yyvsp[(3) - (3)].real);
                ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 358 "tamim.y"
    {
                    cnt++;
                    itmp = realloc(itmp,cnt*sizeof(int));;
                    itmp[cnt-1]=(int)(yyvsp[(1) - (1)].real);
                ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 365 "tamim.y"
    {;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 366 "tamim.y"
    {;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 370 "tamim.y"
    {
                    int exists = checkExistance((yyvsp[(1) - (3)].string));
                    if(exists){
                        alreadyExist((yyvsp[(1) - (3)].string));
                    }
                    else{
                        double value = (yyvsp[(3) - (3)].real);
                        insertData((yyvsp[(1) - (3)].string),&value,1,varCnt,1,0);
                        varCnt++;
                    }
                ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 382 "tamim.y"
    {
                double value = rand();
                insertData((yyvsp[(1) - (1)].string),&value,1,varCnt,1,0);
                varCnt++;
            ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 388 "tamim.y"
    {
                    printf("Real Array Declaration.\n");
                    insertData((yyvsp[(1) - (1)].string),dtmp,1,varCnt,cnt,1);
                    varCnt++;
                ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 394 "tamim.y"
    {
                    insertData((yyvsp[(1) - (5)].string),dtmp,1,varCnt,cnt,1);
                    varCnt++;
                    cnt = 0;
                    free(dtmp);
                ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 403 "tamim.y"
    {
                    cnt++;
                    dtmp = realloc(dtmp,cnt*sizeof(double));;
                    dtmp[cnt-1]=(yyvsp[(3) - (3)].real);
                ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 409 "tamim.y"
    {
                    cnt++;
                    dtmp = realloc(dtmp,cnt*sizeof(double));;
                    dtmp[cnt-1]=(yyvsp[(1) - (1)].real);
                ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 416 "tamim.y"
    {;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 417 "tamim.y"
    {;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 421 "tamim.y"
    {
                    int exists = checkExistance((yyvsp[(1) - (3)].string));
                    if(exists){
                    printf("Variable Already declared.\n");
                    }
                    else{
                    char *value= (yyvsp[(3) - (3)].string);
                    insertData((yyvsp[(1) - (3)].string),&value,2,varCnt,1,0);
                    varCnt++;
                    printf("New variable initialized.\n");
                    }
                ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 434 "tamim.y"
    {
                    char* value = "";
                    insertData((yyvsp[(1) - (1)].string),&value,2,varCnt,1,0);
                    varCnt++;
                ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 440 "tamim.y"
    {
                    printf("Integer Array Declaration.\n");
                    insertData((yyvsp[(1) - (1)].string),stmp,2,varCnt,cnt,1);
                    varCnt++;
                ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 446 "tamim.y"
    {
                    printf("String Array of size:%d\n",cnt);
                    insertData((yyvsp[(1) - (5)].string),stmp,2,varCnt,cnt,1);
                    varCnt++;
                    cnt = 0;
                    free(stmp);
                ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 456 "tamim.y"
    {
                    cnt++;
                    stmp = realloc(stmp,cnt*sizeof(char*));;
                    stmp[cnt-1]=(yyvsp[(3) - (3)].string);
                ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 462 "tamim.y"
    {
                    cnt++;
                    stmp = realloc(stmp,cnt*sizeof(char*));;
                    stmp[cnt-1]=(yyvsp[(1) - (1)].string);
                ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 473 "tamim.y"
    {
                    printVariable((yyvsp[(3) - (3)].string));
                ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 477 "tamim.y"
    {
                    printVariable((yyvsp[(3) - (3)].string));
                ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 482 "tamim.y"
    {
                    printVariable((yyvsp[(1) - (1)].string));
                ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 495 "tamim.y"
    {
                    int index = getVariableIndex((yyvsp[(1) - (3)].string));
                    if (index == -1)
                    {
                        printf("there is no variable named %s.\n", (yyvsp[(1) - (3)].string));
                    }
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

  case 50:

/* Line 1455 of yacc.c  */
#line 512 "tamim.y"
    {
                    int id = (yyvsp[(3) - (6)].integer);
                    int index = getVariableIndex((yyvsp[(1) - (6)].string));
                    if (index == -1)
                    {
                        doesNotExist((yyvsp[(1) - (6)].string));
                    }
                    else
                    {
                        if(id>=vptr[index].size){
                            outOfRange();
                        }
                        else
                        {
                            if (vptr[index].type == 1)
                                vptr[index].dval[id] = (yyvsp[(6) - (6)].real);
                            if (vptr[index].type == 0)
                                vptr[index].ival[id] =  (yyvsp[(6) - (6)].real);
                        }
                    }
                ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 535 "tamim.y"
    {;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 539 "tamim.y"
    {
                    int isTrue = (fabs((yyvsp[(1) - (4)].real))>1e-9);
                    if(isTrue){
                        
                        printf("Condition in if block is true.\n");
                        
                        printf("Value of expression in if block is %.4lf\n",(yyvsp[(3) - (4)].real));
                        conditionMatched = 1;
                    }
                    else{
                        
                        printf("Condition in if block is false.\n");
                        
                    }
                ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 561 "tamim.y"
    {
                    if(conditionMatched){
                        
                        printf("Condition already fulfilled.Ignoring else block.\n");
                        
                    }
                    else{
                        double isTrue =1;
                        if(isTrue){
                            
                            printf("Condition in else block is true.\n");
                            
                            printf("Value of expression in else block is %.4lf\n",(yyvsp[(4) - (4)].integer));
                            conditionMatched = 1;
                        }
                        else{
                            
                            printf("Condition in else block is false.\n");
                            
                        }
                    }  
                ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 590 "tamim.y"
    {
                    if(conditionMatched){
                        
                        printf("Condition already fulfilled.Ignoring elif block.\n");
                        
                    }
                    else{
                            int isTrue = (fabs((yyvsp[(2) - (5)].real))>1e-9);
                            if(isTrue){
                                
                                printf("Condition in elif block is true.\n");
                                
                                printf("Value of expression in elif block is %.4lf\n",(yyvsp[(4) - (5)].real));
                                conditionMatched = 1;
                            }
                            else{
                                
                                printf("Condition in elif block is false.\n");
                                
                            }
                        }
                ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 617 "tamim.y"
    {conditionMatched = 0;;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 621 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (1)].string));
                    if(id==-1) printf("No such variable");
                    else if(vptr[id].type==2){
                        
                        printf("can't assign string in choices.");
                        
                    }
                    else if(vptr[id].type==0) choiceValue = vptr[id].ival[0];
                    else choiceValue = vptr[id].dval[0];
                ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 640 "tamim.y"
    {
                    if(conditionMatched){
                        
                        printf("Condition already fulfilled.Ignoring default option.\n");
                        
                        }
                    else{
                        
                        printf("Executing Default Option.No match found.\n");
                        
                        printf("Value of expression: %.4lf\n",(yyvsp[(3) - (4)].real));
                    }
                ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 660 "tamim.y"
    {
                    if(conditionMatched){
                        
                        printf("Condition already fulfilled.Ignoring current option\n");
                        
                        }
                    else{
                        int isTrue = (fabs((yyvsp[(2) - (5)].real)-choiceValue)<1e-9);
                            if(isTrue){
                                
                                printf("Option matched.\n");
                                
                                printf("Value of expression in current option %.4lf\n",(yyvsp[(4) - (5)].real));
                                conditionMatched = 1;
                            }
                            else{
                                
                                printf("Condition of current option doesn't match.\n");
                                
                            }
                    }
                ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 686 "tamim.y"
    {
                    double begin = (yyvsp[(2) - (9)].real);
                    double end = (yyvsp[(4) - (9)].real);
                    double add = (yyvsp[(6) - (9)].real);
                    double x = end-begin;
                    if(x*add < 0){
                        
                        printf("Infinite  FROM loop\n");
                        
                    }
                    else{
                          for(double i = begin ; i<=end ; i+=add){
                                printf("Runnning Inside From Loop and value of expression is:%.4lf\n",(yyvsp[(8) - (9)].real));
                             }
                    }   
                ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 703 "tamim.y"
    {
                    
                    printf("While will run for %d times\n",(yyvsp[(2) - (5)].integer));
                    
                    for(int i = 0;i<(yyvsp[(2) - (5)].integer);i++){
                        printf("Value of Statement %.4lf\n",(yyvsp[(4) - (5)].real));
                    }
                ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 712 "tamim.y"
    {
                    
                    printf("repeat while will run for %d times\n",(yyvsp[(6) - (7)].integer));
                    
                ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 720 "tamim.y"
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
                                (yyval.integer) = (int) (yyvsp[(4) - (4)].real) - value;
                            }
                    }
                ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 735 "tamim.y"
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

  case 74:

/* Line 1455 of yacc.c  */
#line 750 "tamim.y"
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
                                (yyval.integer) = (int) (yyvsp[(4) - (4)].real) - value;
                            }
                    }
                ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 765 "tamim.y"
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

  case 76:

/* Line 1455 of yacc.c  */
#line 780 "tamim.y"
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

  case 77:

/* Line 1455 of yacc.c  */
#line 795 "tamim.y"
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

  case 79:

/* Line 1455 of yacc.c  */
#line 816 "tamim.y"
    {
                    int id = getFunctionIndex((yyvsp[(1) - (1)].string));
                    if(id!=-1){printf("Module Already Declared");}
                    else{
                        printf("Declaring Module\n");
                        stk[funCnt].fname = malloc((strlen((yyvsp[(1) - (1)].string))+10)*sizeof(char));
                        strcpy(stk[funCnt].fname,(yyvsp[(1) - (1)].string));
                        stk[funCnt].varCnt = 0; 
                        stk[funCnt].fptr = malloc(4*sizeof(stack));
                    }
                ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 834 "tamim.y"
    {
                    int id = stk[funCnt].varCnt;
                    int value = rand();
                    insertData((yyvsp[(2) - (2)].string),&value,0,varCnt,1,0);
                    stk[funCnt].fptr[id] = vptr[varCnt];
                    varCnt++;
                    stk[funCnt].varCnt++;
                ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 843 "tamim.y"
    {
                    int id = stk[funCnt].varCnt;
                    double value = rand();
                    insertData((yyvsp[(2) - (2)].string),&value,1,varCnt,1,0);
                    stk[funCnt].fptr[id] = vptr[varCnt];
                    varCnt++;
                    stk[funCnt].varCnt++;
                ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 852 "tamim.y"
    {
                    int id = stk[funCnt].varCnt;
                    char* value = "";
                    insertData((yyvsp[(1) - (2)].string),&value,2,varCnt,1,0);
                    stk[funCnt].fptr[id] = vptr[varCnt];
                    varCnt++;
                    stk[funCnt].varCnt++;
                ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 863 "tamim.y"
    {
                    if(functionRejected){
                        
                        printf("Module was not called as declared\n");
                        
                    }
                    else{
                        printf("Module called Successfully.\n");
                    }
                ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 876 "tamim.y"
    {
                    int id = getFunctionIndex((yyvsp[(1) - (1)].string));
                    if(id==-1){printf(" No Function Exist with this name.");}
                    else{
                        currentFunction = id;
                        currentParam = 0;
                        functionRejected = 0;
                    }
                ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 892 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (1)].string));
                    if(currentParam>=stk[currentFunction].varCnt){
                        
                        printf("More variable than declared");
                        
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

  case 90:

/* Line 1455 of yacc.c  */
#line 914 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (1)].integer);
                ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 918 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (1)].real);
                ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 923 "tamim.y"
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

  case 93:

/* Line 1455 of yacc.c  */
#line 933 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(2) - (2)].real);
                ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 937 "tamim.y"
    {
                    (yyval.real) = -(yyvsp[(2) - (2)].real);
                ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 941 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(2) - (2)].real);
                ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 945 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(2) - (2)].real);
                ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 949 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (3)].real) + (yyvsp[(3) - (3)].real);
                ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 953 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (3)].real) - (yyvsp[(3) - (3)].real);
                ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 957 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (3)].real) * (yyvsp[(3) - (3)].real);
                ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 961 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (3)].real) / (yyvsp[(3) - (3)].real);
                ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 965 "tamim.y"
    {
                    (yyval.real) = pow((yyvsp[(1) - (3)].real),(yyvsp[(3) - (3)].real));
                ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 969 "tamim.y"
    {

                    (yyval.real) = (int)(yyvsp[(1) - (3)].real) % (int)(yyvsp[(3) - (3)].real);
                ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 974 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) < (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 978 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) > (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 982 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) <= (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 986 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) >= (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 990 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) == (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 994 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) != (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 998 "tamim.y"
    {
                    (yyval.real) = ( (yyvsp[(1) - (3)].real) && (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1002 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) || (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1006 "tamim.y"
    {
                    (yyval.real) = ((int)(yyvsp[(1) - (3)].real) ^ (int)(yyvsp[(3) - (3)].real));
                ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1010 "tamim.y"
    {
                    (yyval.real) = !(yyvsp[(2) - (2)].real);
                ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1014 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(2) - (3)].real);
                ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1018 "tamim.y"
    {
                    (yyval.real) = sin((yyvsp[(3) - (4)].real));

                ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1023 "tamim.y"
    {
                    (yyval.real) = cos((yyvsp[(3) - (4)].real));
                ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1027 "tamim.y"
    {
                    (yyval.real) = tan((yyvsp[(3) - (4)].real));
                ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1031 "tamim.y"
    {
                    (yyval.real) = log10((yyvsp[(3) - (4)].real));
                ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1035 "tamim.y"
    {
                    (yyval.real) = log2((yyvsp[(3) - (4)].real));
                ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1039 "tamim.y"
    {
                    (yyval.real) = log((yyvsp[(3) - (4)].real));
                ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1043 "tamim.y"
    {
                    (yyval.real) = sqrt((yyvsp[(3) - (4)].real));
                ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1047 "tamim.y"
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

  case 122:

/* Line 1455 of yacc.c  */
#line 1059 "tamim.y"
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

  case 123:

/* Line 1455 of yacc.c  */
#line 1070 "tamim.y"
    {
                    int cl = ceil((yyvsp[(1) - (2)].real));int fl = floor((yyvsp[(1) - (2)].real));
                    if(cl!=fl) printf("can't find FACTORIAL of real number.");
                    else {
                        long long x = 1;
                        for(long long i=1;i<=(yyvsp[(1) - (2)].real);i++) x*=i;
                        (yyval.real) = x;
                    }
                ;}
    break;



/* Line 1455 of yacc.c  */
#line 3186 "tamim.tab.c"
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
#line 1081 "tamim.y"



int main() {
   
    initialize_globals();

    yyin = fopen("input.txt", "r");
    if (!yyin) {
        printf("Error opening input file");  
    }

    freopen("output.txt", "w", stdout);

    printf("\n\n     -------Starting Program Execution-------\n\n\n");

    yyparse();
    return 0;
}
 
     



