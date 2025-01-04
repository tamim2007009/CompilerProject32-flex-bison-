
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


        /* Printing an Array Index */
        int printArrayIndex(char *varName, int position){
            int index = getVariableIndex(varName);
            if (index == -1)
            {
               doesNotExist(varName);
            }
            else if (vptr[index].isArray == 0)
            {
                notArray(varName);
            }
            else if (position >= vptr[index].size)
            {
                printf("index out of range\n");
            }
            else
            {
                printf("Value of Array %s at Index %d is: ", varName, position);
                if (vptr[index].type == 1)
                    printf("%lf\n", vptr[index].dval[position]);
                if (vptr[index].type == 0)
                    printf("%d\n", vptr[index].ival[position]);
                if (vptr[index].type == 2)
                    printf("%s\n", vptr[index].sval[position]);
            }
        }

        /* Taking Input From User */
         int takeInput(char *varName, int id ){
             
             printf("Enter Value of %s: ",varName);
             
            int index = getVariableIndex(varName);
            if (index == -1)
            {
                doesNotExist(varName);
            }
            else
            {
                if(id>=vptr[index].size){
                    outOfRange();
                }
                else
                {
                    if (vptr[index].type == 1)
                        scanf("%lf", &vptr[index].dval[id]);
                    if (vptr[index].type == 0)
                        scanf("%d", &vptr[index].ival[id]);
                    if (vptr[index].type == 2){
                        char str [100000];
                        scanf("%s",str);
                        vptr[index].sval[id]=str;
                    }
                       
                }
            }
        }

        /* ---------Array Helper Functions-------- */

        /* Push new element at the end of array. */
        void appendData(int index,void *value){
            int curSize = vptr[index].size;
            double x = *(double*) value;
            if(vptr[index].type==0){
                vptr[index].ival = realloc(vptr[index].ival,(curSize+1)*sizeof(int));
                vptr[index].ival[curSize] = (int)x;
                vptr[index].size++;
            }
            else{
                vptr[index].dval = realloc(vptr[index].dval,(curSize+1)*sizeof(double));
                vptr[index].dval[curSize] = x;
                vptr[index].size++;
            }
        }

        /* pop last element from the array. */
        void popLast(int index){
            int curSize = vptr[index].size;
            if(curSize==0){
                emptyArray();
                return ;
            }
            if(vptr[index].type==0){
                vptr[index].ival = realloc(vptr[index].ival,(curSize-1)*sizeof(int));
                vptr[index].size--;
            }
            else if (vptr[index].type==1){
                vptr[index].dval = realloc(vptr[index].dval,(curSize-1)*sizeof(double));
                vptr[index].size--;
            }
            else if (vptr[index].type==1){
                vptr[index].sval = realloc(vptr[index].sval,(curSize-1)*sizeof(char**));
                vptr[index].size--;
            }
        }
        /* functions for quicksort */
        int cmpfunInt (const void * a, const void * b) {
            return ( *(int*)a - *(int*)b );
        }

        int cmpfunDouble ( const void *a , const void *b){
            return ( *(double*)a - *(double*)b );
        }

        int cmpfunString(const void *a, const void *b) { 
            const char **str_a = (const char **)a;
            const char **str_b = (const char **)b;
            return strcmp(*str_a, *str_b);
        } 

        void sort(int id){
            if(vptr[id].type==0){
                qsort (vptr[id].ival, vptr[id].size, sizeof(int), cmpfunInt);
            }
            else if(vptr[id].type==1){
                qsort (vptr[id].dval, vptr[id].size, sizeof(double), cmpfunDouble);
            }
            else{
                qsort (vptr[id].sval, vptr[id].size, sizeof(char*), cmpfunString);
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
#line 413 "tamim.tab.c"

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
     RARROW = 265,
     INTEGER = 266,
     REAL = 267,
     STRING = 268,
     INT_TYPE = 269,
     REAL_TYPE = 270,
     STRING_TYPE = 271,
     SEE = 272,
     AND = 273,
     OR = 274,
     NOT = 275,
     XOR = 276,
     LOG = 277,
     LOG2 = 278,
     LN = 279,
     SIN = 280,
     COS = 281,
     TAN = 282,
     FACTORIAL = 283,
     SQRT = 284,
     IF = 285,
     ELIF = 286,
     ELSE = 287,
     CHOICE = 288,
     DEFAULT = 289,
     OPTION = 290,
     FOREACH = 291,
     FROM = 292,
     TO = 293,
     DO = 294,
     WHILE = 295,
     BY = 296,
     AS = 297,
     COMMENT = 298,
     MODULE = 299,
     CALL = 300,
     PUSH = 301,
     POP = 302,
     SORT = 303,
     IMPORT = 304,
     MMINUS = 305,
     PPLUS = 306,
     GEQL = 307,
     LEQL = 308,
     NEQL = 309,
     EQL = 310
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 342 "tamim.y"

	int integer;
	double real;
	char* string;



/* Line 214 of yacc.c  */
#line 512 "tamim.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 524 "tamim.tab.c"

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
#define YYLAST   990

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNRULES -- Number of states.  */
#define YYNSTATES  292

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    62,     2,     2,
      70,    71,    60,    58,    64,    59,    72,    61,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,    65,    53,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    68,     2,    69,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,     2,    67,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    54,    55,    56,
      57
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    10,    13,    15,    17,    20,    23,
      26,    29,    31,    33,    35,    37,    39,    41,    44,    47,
      50,    54,    56,    60,    62,    64,    70,    74,    76,    80,
      82,    86,    88,    90,    96,   100,   102,   106,   108,   112,
     114,   116,   122,   126,   128,   132,   136,   140,   147,   149,
     151,   156,   160,   162,   166,   173,   177,   182,   183,   185,
     188,   190,   195,   198,   200,   206,   212,   214,   217,   219,
     224,   227,   229,   235,   245,   251,   259,   264,   269,   274,
     279,   284,   289,   298,   300,   304,   306,   309,   312,   315,
     321,   323,   327,   329,   331,   338,   344,   348,   350,   352,
     354,   357,   360,   363,   366,   370,   374,   378,   382,   386,
     390,   394,   398,   402,   406,   410,   414,   418,   422,   426,
     429,   433,   438,   443,   448,   453,   458,   463,   468,   471,
     474
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      74,     0,    -1,    49,     3,     5,    75,     4,    -1,    -1,
      75,    76,    -1,     8,    -1,    43,    -1,    77,     8,    -1,
      89,     8,    -1,    87,     8,    -1,   114,     8,    -1,    91,
      -1,    97,    -1,   103,    -1,   105,    -1,   109,    -1,   113,
      -1,    14,    78,    -1,    15,    81,    -1,    16,    84,    -1,
      78,    64,    79,    -1,    79,    -1,     6,    65,   114,    -1,
       6,    -1,     7,    -1,     7,    65,    66,    80,    67,    -1,
      80,    64,   114,    -1,   114,    -1,    81,    64,    82,    -1,
      82,    -1,     6,    65,   114,    -1,     6,    -1,     7,    -1,
       7,    65,    66,    83,    67,    -1,    83,    64,   114,    -1,
     114,    -1,    84,    64,    85,    -1,    85,    -1,     6,    65,
      13,    -1,     6,    -1,     7,    -1,     7,    65,    66,    86,
      67,    -1,    86,    64,    13,    -1,    13,    -1,    17,     9,
      88,    -1,    88,    64,     6,    -1,    88,    64,     7,    -1,
      88,    64,     7,    68,   114,    69,    -1,     6,    -1,     7,
      -1,     7,    68,   114,    69,    -1,    89,    64,    90,    -1,
      90,    -1,     6,    65,   114,    -1,     7,    68,    11,    69,
      65,   114,    -1,    30,    92,    93,    -1,   114,     5,    76,
       4,    -1,    -1,    95,    -1,    95,    94,    -1,    94,    -1,
      32,     5,    76,     4,    -1,    95,    96,    -1,    96,    -1,
      31,   114,     5,    76,     4,    -1,    33,    98,     5,    99,
       4,    -1,     6,    -1,   101,   100,    -1,   100,    -1,    34,
       5,    76,     4,    -1,   101,   102,    -1,   102,    -1,    35,
     114,     5,    76,     4,    -1,    37,   114,    38,   114,    41,
     114,     5,    76,     4,    -1,    40,   104,     5,    76,     4,
      -1,    39,     5,   114,     4,    40,   104,     8,    -1,     6,
      51,    52,   114,    -1,     6,    51,    55,   114,    -1,     6,
      51,    56,   114,    -1,     6,    50,    53,   114,    -1,     6,
      50,    54,   114,    -1,     6,    50,    56,   114,    -1,    44,
     106,    70,   107,    71,     5,    75,     4,    -1,     6,    -1,
     107,    64,   108,    -1,   108,    -1,    14,     6,    -1,    15,
       6,    -1,    16,     6,    -1,    45,   110,    70,   111,    71,
      -1,     6,    -1,   111,    64,   112,    -1,   112,    -1,     6,
      -1,     7,    72,    46,    70,   114,    71,    -1,     7,    72,
      47,    70,    71,    -1,     7,    72,    48,    -1,    11,    -1,
      12,    -1,     6,    -1,    58,   114,    -1,    59,   114,    -1,
      51,   114,    -1,    50,   114,    -1,   114,    58,   114,    -1,
     114,    59,   114,    -1,   114,    60,   114,    -1,   114,    61,
     114,    -1,   114,    63,   114,    -1,   114,    62,   114,    -1,
     114,    52,   114,    -1,   114,    53,   114,    -1,   114,    55,
     114,    -1,   114,    54,   114,    -1,   114,    57,   114,    -1,
     114,    56,   114,    -1,   114,    18,   114,    -1,   114,    19,
     114,    -1,   114,    21,   114,    -1,    20,   114,    -1,    70,
     114,    71,    -1,    25,    70,   114,    71,    -1,    26,    70,
     114,    71,    -1,    27,    70,   114,    71,    -1,    22,    70,
     114,    71,    -1,    23,    70,   114,    71,    -1,    24,    70,
     114,    71,    -1,    29,    70,   114,    71,    -1,     6,    51,
      -1,     6,    50,    -1,   114,    28,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   374,   374,   381,   382,   385,   386,   392,   393,   394,
     395,   402,   404,   405,   406,   426,   427,   430,   431,   432,
     435,   436,   439,   451,   457,   462,   471,   477,   485,   486,
     489,   501,   507,   513,   522,   528,   536,   537,   540,   553,
     559,   565,   575,   581,   589,   592,   596,   600,   604,   608,
     612,   619,   620,   624,   641,   665,   668,   685,   686,   687,
     688,   690,   715,   716,   719,   746,   750,   765,   766,   769,
     785,   786,   789,   815,   832,   841,   849,   864,   879,   894,
     909,   924,   942,   945,   959,   960,   963,   972,   981,   992,
    1005,  1017,  1018,  1021,  1042,  1059,  1067,  1080,  1084,  1089,
    1099,  1103,  1107,  1111,  1115,  1119,  1123,  1127,  1131,  1135,
    1140,  1144,  1148,  1152,  1156,  1160,  1164,  1168,  1172,  1176,
    1180,  1184,  1189,  1193,  1197,  1201,  1205,  1209,  1213,  1225,
    1236
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ROOT", "END", "START", "VARIABLE",
  "ARRAY_VAR", "EOL", "ARROW", "RARROW", "INTEGER", "REAL", "STRING",
  "INT_TYPE", "REAL_TYPE", "STRING_TYPE", "SEE", "AND", "OR", "NOT", "XOR",
  "LOG", "LOG2", "LN", "SIN", "COS", "TAN", "FACTORIAL", "SQRT", "IF",
  "ELIF", "ELSE", "CHOICE", "DEFAULT", "OPTION", "FOREACH", "FROM", "TO",
  "DO", "WHILE", "BY", "AS", "COMMENT", "MODULE", "CALL", "PUSH", "POP",
  "SORT", "IMPORT", "MMINUS", "PPLUS", "'<'", "'>'", "GEQL", "LEQL",
  "NEQL", "EQL", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "','", "'='",
  "'{'", "'}'", "'['", "']'", "'('", "')'", "'.'", "$accept", "program",
  "statements", "statement", "declaration", "int_variables", "int_var",
  "ints", "real_variables", "real_var", "reals", "string_variables",
  "string_var", "strings", "show", "print_vars", "assigns", "assign",
  "if_blocks", "if_block", "else_statement", "single_else",
  "elif_statement", "single_elif", "choice_block", "choice_variable",
  "options", "default", "optionlist", "option", "loop_block",
  "while_conditions", "module_declare", "module_name", "module_variable",
  "single_var", "module_call", "user_module_name", "user_parameters",
  "single_param", "array_operations", "expr", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,    60,    62,   307,   308,   309,   310,    43,    45,
      42,    47,    37,    94,    44,    61,   123,   125,    91,    93,
      40,    41,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    75,    75,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    77,    77,    77,
      78,    78,    79,    79,    79,    79,    80,    80,    81,    81,
      82,    82,    82,    82,    83,    83,    84,    84,    85,    85,
      85,    85,    86,    86,    87,    88,    88,    88,    88,    88,
      88,    89,    89,    90,    90,    91,    92,    93,    93,    93,
      93,    94,    95,    95,    96,    97,    98,    99,    99,   100,
     101,   101,   102,   103,   103,   103,   104,   104,   104,   104,
     104,   104,   105,   106,   107,   107,   108,   108,   108,   109,
     110,   111,   111,   112,   113,   113,   113,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     2,     1,     1,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       3,     1,     3,     1,     1,     5,     3,     1,     3,     1,
       3,     1,     1,     5,     3,     1,     3,     1,     3,     1,
       1,     5,     3,     1,     3,     3,     3,     6,     1,     1,
       4,     3,     1,     3,     6,     3,     4,     0,     1,     2,
       1,     4,     2,     1,     5,     5,     1,     2,     1,     4,
       2,     1,     5,     9,     5,     7,     4,     4,     4,     4,
       4,     4,     8,     1,     3,     1,     2,     2,     2,     5,
       1,     3,     1,     1,     6,     5,     3,     1,     1,     1,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     4,     4,     4,     4,     4,     4,     4,     2,     2,
       2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     2,    99,     0,
       5,    97,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     0,     0,     0,     0,     0,     0,     0,     4,     0,
       0,     0,    52,    11,    12,    13,    14,    15,    16,     0,
     129,   128,     0,     0,     0,    23,    24,    17,    21,    31,
      32,    18,    29,    39,    40,    19,    37,     0,    99,   119,
       0,     0,     0,     0,     0,     0,     0,    57,     0,    66,
       0,     0,     0,     0,     0,    83,     0,    90,     0,   103,
     102,   100,   101,     0,     7,     9,     8,     0,    10,     0,
       0,     0,   130,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    53,     0,     0,     0,    96,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    44,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    55,    60,    58,    63,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   120,     0,     0,    51,   116,   117,
     118,   110,   111,   113,   112,   115,   114,   104,   105,   106,
     107,   109,   108,     0,     0,     0,    22,     0,    20,    30,
       0,    28,    38,     0,    36,     0,     0,   124,   125,   126,
     121,   122,   123,   127,     0,     0,    59,    62,     0,     0,
       0,     0,    68,     0,    71,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    85,    93,
       0,    92,     0,     0,    95,     0,    27,     0,    35,    43,
       0,     0,    45,    46,     0,     0,    56,     0,     0,    65,
      67,    70,     0,     0,    79,    80,    81,    76,    77,    78,
      74,    86,    87,    88,     0,     0,     0,    89,    54,    94,
       0,    25,     0,    33,     0,    41,    50,     0,     0,    61,
       0,     0,     0,     0,    84,     3,    91,    26,    34,    42,
       0,    64,    69,     0,     0,    75,     0,    47,    72,     0,
      82,    73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,    38,    39,    57,    58,   225,    61,    62,
     227,    65,    66,   230,    40,   131,    41,    42,    43,    77,
     141,   142,   143,   144,    44,    80,   201,   202,   203,   204,
      45,    84,    46,    86,   217,   218,    47,    88,   220,   221,
      48,    49
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -124
static const yytype_int16 yypact[] =
{
     -48,     6,    52,     9,  -124,  -124,   240,  -124,   -44,   -57,
    -124,  -124,  -124,    92,    94,    98,    58,   114,    15,    32,
      51,    57,    59,    61,    63,   114,    73,   114,    76,   122,
    -124,   126,   129,   114,   114,   114,   114,   114,  -124,   134,
     136,    -4,  -124,  -124,  -124,  -124,  -124,  -124,  -124,   179,
    -124,  -124,   114,   135,   -14,    80,    82,    95,  -124,    90,
      93,   102,  -124,   104,   105,   103,  -124,   101,   -24,   927,
     114,   114,   114,   114,   114,   114,   114,    78,   374,  -124,
     151,   879,   114,    62,   166,  -124,   108,  -124,   110,   891,
     891,     1,     1,   503,  -124,  -124,  -124,   109,  -124,   114,
     114,   114,  -124,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   891,   106,   111,   112,  -124,
     114,   119,    92,   114,   123,    94,   161,   130,    98,  -124,
     120,   137,   523,   569,   589,   635,   655,   701,   721,   114,
     194,  -124,  -124,    78,  -124,   338,    83,   114,   158,    20,
      14,   338,    35,   196,  -124,   138,   140,  -124,   927,   927,
     927,    91,    91,    91,    91,    91,    91,     1,     1,   -15,
     -15,   -15,   -15,   139,   114,   152,   891,   114,  -124,   891,
     114,  -124,  -124,   193,  -124,   114,   117,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,   386,   338,  -124,  -124,   205,   217,
     114,   220,  -124,    83,  -124,   -16,   186,   114,   114,   114,
     114,   114,   114,   223,   222,   224,   243,   -41,  -124,  -124,
     -40,  -124,   114,   767,  -124,     4,   891,    11,   891,  -124,
      13,   787,  -124,   185,   338,   225,  -124,   338,   445,  -124,
    -124,  -124,   114,   122,   891,   891,   891,   891,   891,   891,
    -124,  -124,  -124,  -124,    35,   253,   196,  -124,   891,  -124,
     114,  -124,   114,  -124,   246,  -124,  -124,   114,   257,  -124,
     264,   338,   457,   263,  -124,  -124,  -124,   891,   891,  -124,
     833,  -124,  -124,   268,   338,  -124,   289,  -124,  -124,   270,
    -124,  -124
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -124,  -124,     0,  -123,  -124,  -124,   154,  -124,  -124,   153,
    -124,  -124,   159,  -124,  -124,  -124,  -124,   184,  -124,  -124,
    -124,   143,  -124,   145,  -124,  -124,  -124,    79,  -124,    86,
    -124,    49,  -124,  -124,  -124,    40,  -124,  -124,  -124,    46,
    -124,   -17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      69,     1,    99,   100,    96,   101,    50,    51,    78,     3,
      81,    53,   102,   102,     5,    54,    89,    90,    91,    92,
      93,    52,   198,   254,   256,   242,    50,    51,   213,   102,
     255,   257,   117,   118,   119,   115,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   114,   214,
     215,   216,     4,   132,   133,   134,   135,   136,   137,   138,
      97,   111,   112,   113,   114,   148,   210,    67,   260,   211,
     212,   261,   235,   207,   208,   262,   209,   264,   263,    79,
     265,    82,   158,   159,   160,    70,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,    55,    56,
      59,    60,    71,   176,    63,    64,   179,   129,   130,   139,
     140,   268,   149,   150,   270,   155,   156,   199,   200,   102,
      68,    72,   194,   232,   233,    11,    12,    73,    83,    74,
     205,    75,    85,    76,    17,    87,    18,    19,    20,    21,
      22,    23,    94,    24,    95,   120,   116,   121,   283,   109,
     110,   111,   112,   113,   114,   123,   146,   223,   124,   122,
     226,   289,   206,   228,    33,    34,   125,   128,   231,   126,
     127,   151,    35,    36,   182,   173,    99,   100,   152,   101,
     153,   174,   175,   238,    37,   177,   102,    98,   185,   180,
     244,   245,   246,   247,   248,   249,   183,    99,   100,   195,
     101,   186,   219,    52,   222,   258,   229,   102,    53,   236,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   237,   224,   239,   272,   243,   250,   251,   269,
     252,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   277,     7,   278,     8,     9,    10,   253,
     280,    11,    12,   267,    13,    14,    15,    16,   275,   279,
      17,   281,    18,    19,    20,    21,    22,    23,   282,    24,
      25,   285,   288,    26,   291,   286,   178,    27,   181,    28,
      29,   157,   240,    30,    31,    32,   196,   184,   197,   241,
      33,    34,   273,   290,   274,     8,     9,    10,    35,    36,
      11,    12,   276,    13,    14,    15,    16,     0,     0,    17,
      37,    18,    19,    20,    21,    22,    23,     0,    24,    25,
       0,     0,    26,     0,     0,     0,    27,     0,    28,    29,
       0,     0,    30,    31,    32,     0,     0,     0,     0,    33,
      34,     0,     0,     0,     8,     9,    10,    35,    36,    11,
      12,     0,    13,    14,    15,    16,     0,     0,    17,    37,
      18,    19,    20,    21,    22,    23,     0,    24,    25,     0,
       0,    26,     0,     0,     0,    27,     0,    28,    29,   145,
       0,    30,    31,    32,     0,     0,     0,     0,    33,    34,
       0,   234,    99,   100,     0,   101,    35,    36,     0,     0,
       0,     0,   102,     0,    99,   100,     0,   101,    37,     0,
       0,     0,     0,     0,   102,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     271,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   284,    99,   100,     0,   101,     0,     0,     0,
       0,     0,     0,   102,     0,    99,   100,     0,   101,     0,
       0,     0,     0,     0,     0,   102,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    99,   100,     0,   101,     0,     0,     0,     0,     0,
       0,   102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    99,   100,     0,   101,     0,     0,     0,     0,     0,
       0,   102,     0,     0,     0,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,   154,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,    99,   100,     0,
     101,     0,     0,     0,   187,     0,     0,   102,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    99,   100,     0,
     101,     0,     0,     0,     0,     0,     0,   102,     0,     0,
       0,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,     0,     0,     0,     0,
     188,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,    99,   100,     0,   101,     0,     0,     0,
     189,     0,     0,   102,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,   100,     0,   101,     0,     0,     0,
       0,     0,     0,   102,     0,     0,     0,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,     0,
       0,     0,     0,     0,     0,     0,   190,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,    99,
     100,     0,   101,     0,     0,     0,   191,     0,     0,   102,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    99,
     100,     0,   101,     0,     0,     0,     0,     0,     0,   102,
       0,     0,     0,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,     0,     0,     0,     0,     0,
       0,     0,   192,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,    99,   100,     0,   101,     0,
       0,     0,   193,     0,     0,   102,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,   100,     0,   101,     0,
       0,     0,     0,     0,     0,   102,     0,     0,     0,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,     0,     0,     0,     0,     0,     0,     0,   259,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    99,   100,     0,   101,     0,   266,     0,     0,     0,
       0,   102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,    99,   100,     0,
     101,     0,   287,     0,     0,     0,     0,   102,     0,    99,
     100,     0,   101,     0,     0,     0,     0,   147,     0,   102,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   102,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114
};

static const yytype_int16 yycheck[] =
{
      17,    49,    18,    19,     8,    21,    50,    51,    25,     3,
      27,    68,    28,    28,     5,    72,    33,    34,    35,    36,
      37,    65,   145,    64,    64,    41,    50,    51,   151,    28,
      71,    71,    46,    47,    48,    52,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    63,    14,
      15,    16,     0,    70,    71,    72,    73,    74,    75,    76,
      64,    60,    61,    62,    63,    82,    52,     9,    64,    55,
      56,    67,   195,    53,    54,    64,    56,    64,    67,     6,
      67,     5,    99,   100,   101,    70,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,     6,     7,
       6,     7,    70,   120,     6,     7,   123,     6,     7,    31,
      32,   234,    50,    51,   237,     6,     7,    34,    35,    28,
       6,    70,   139,     6,     7,    11,    12,    70,     6,    70,
     147,    70,     6,    70,    20,     6,    22,    23,    24,    25,
      26,    27,     8,    29,     8,    65,    11,    65,   271,    58,
      59,    60,    61,    62,    63,    65,     5,   174,    65,    64,
     177,   284,     4,   180,    50,    51,    64,    64,   185,    65,
      65,     5,    58,    59,    13,    69,    18,    19,    70,    21,
      70,    70,    70,   200,    70,    66,    28,     8,    68,    66,
     207,   208,   209,   210,   211,   212,    66,    18,    19,     5,
      21,    64,     6,    65,    65,   222,    13,    28,    68,     4,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,     5,    71,     4,   242,    40,     4,     6,     4,
       6,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,   260,     4,   262,     6,     7,     8,     6,
     267,    11,    12,    68,    14,    15,    16,    17,     5,    13,
      20,     4,    22,    23,    24,    25,    26,    27,     4,    29,
      30,     8,     4,    33,     4,   275,   122,    37,   125,    39,
      40,    97,   203,    43,    44,    45,   143,   128,   143,   203,
      50,    51,   243,     4,   254,     6,     7,     8,    58,    59,
      11,    12,   256,    14,    15,    16,    17,    -1,    -1,    20,
      70,    22,    23,    24,    25,    26,    27,    -1,    29,    30,
      -1,    -1,    33,    -1,    -1,    -1,    37,    -1,    39,    40,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    50,
      51,    -1,    -1,    -1,     6,     7,     8,    58,    59,    11,
      12,    -1,    14,    15,    16,    17,    -1,    -1,    20,    70,
      22,    23,    24,    25,    26,    27,    -1,    29,    30,    -1,
      -1,    33,    -1,    -1,    -1,    37,    -1,    39,    40,     5,
      -1,    43,    44,    45,    -1,    -1,    -1,    -1,    50,    51,
      -1,     5,    18,    19,    -1,    21,    58,    59,    -1,    -1,
      -1,    -1,    28,    -1,    18,    19,    -1,    21,    70,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,    18,    19,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    18,    19,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    18,    19,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    18,    19,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    18,    19,    -1,
      21,    -1,    -1,    -1,    71,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    19,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    18,    19,    -1,    21,    -1,    -1,    -1,
      71,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    19,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    18,
      19,    -1,    21,    -1,    -1,    -1,    71,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      19,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    18,    19,    -1,    21,    -1,
      -1,    -1,    71,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    18,    19,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    18,    19,    -1,    21,    -1,    69,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    18,    19,    -1,
      21,    -1,    69,    -1,    -1,    -1,    -1,    28,    -1,    18,
      19,    -1,    21,    -1,    -1,    -1,    -1,    38,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    49,    74,     3,     0,     5,    75,     4,     6,     7,
       8,    11,    12,    14,    15,    16,    17,    20,    22,    23,
      24,    25,    26,    27,    29,    30,    33,    37,    39,    40,
      43,    44,    45,    50,    51,    58,    59,    70,    76,    77,
      87,    89,    90,    91,    97,   103,   105,   109,   113,   114,
      50,    51,    65,    68,    72,     6,     7,    78,    79,     6,
       7,    81,    82,     6,     7,    84,    85,     9,     6,   114,
      70,    70,    70,    70,    70,    70,    70,    92,   114,     6,
      98,   114,     5,     6,   104,     6,   106,     6,   110,   114,
     114,   114,   114,   114,     8,     8,     8,    64,     8,    18,
      19,    21,    28,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,   114,    11,    46,    47,    48,
      65,    65,    64,    65,    65,    64,    65,    65,    64,     6,
       7,    88,   114,   114,   114,   114,   114,   114,   114,    31,
      32,    93,    94,    95,    96,     5,     5,    38,   114,    50,
      51,     5,    70,    70,    71,     6,     7,    90,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,    69,    70,    70,   114,    66,    79,   114,
      66,    82,    13,    66,    85,    68,    64,    71,    71,    71,
      71,    71,    71,    71,   114,     5,    94,    96,    76,    34,
      35,    99,   100,   101,   102,   114,     4,    53,    54,    56,
      52,    55,    56,    76,    14,    15,    16,   107,   108,     6,
     111,   112,    65,   114,    71,    80,   114,    83,   114,    13,
      86,   114,     6,     7,     5,    76,     4,     5,   114,     4,
     100,   102,    41,    40,   114,   114,   114,   114,   114,   114,
       4,     6,     6,     6,    64,    71,    64,    71,   114,    71,
      64,    67,    64,    67,    64,    67,    69,    68,    76,     4,
      76,     5,   114,   104,   108,     5,   112,   114,   114,    13,
     114,     4,     4,    76,     5,     8,    75,    69,     4,    76,
       4,     4
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
#line 375 "tamim.y"
    {
                printf("\n\n     -------Program Compiled Successfully-------\n\n\n");
            ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 381 "tamim.y"
    {/*Do Nothing.*/;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 385 "tamim.y"
    {;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 387 "tamim.y"
    {
                   
                    printf("  %s\n",(yyvsp[(1) - (1)].string));
                    
                ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 392 "tamim.y"
    {;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 393 "tamim.y"
    {;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 394 "tamim.y"
    {;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 396 "tamim.y"
    {
                    
                    printf("Value of the expression:%.4lf\n",(yyvsp[(1) - (2)].real));
                    (yyval.real) = (yyvsp[(1) - (2)].real);
                    
                ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 403 "tamim.y"
    {conditionMatched=0;;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 404 "tamim.y"
    {;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 405 "tamim.y"
    {;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 407 "tamim.y"
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
#line 426 "tamim.y"
    {;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 427 "tamim.y"
    {;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 435 "tamim.y"
    {;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 436 "tamim.y"
    {;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 440 "tamim.y"
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

  case 23:

/* Line 1455 of yacc.c  */
#line 452 "tamim.y"
    {
                    int value = rand();
                    insertData((yyvsp[(1) - (1)].string),&value,0,varCnt,1,0);
                    varCnt++;
                ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 458 "tamim.y"
    {
                    insertData((yyvsp[(1) - (1)].string),itmp,0,varCnt,cnt,1);
                    varCnt++;
                ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 463 "tamim.y"
    {
                    insertData((yyvsp[(1) - (5)].string),itmp,0,varCnt,cnt,1);
                    varCnt++;
                    cnt = 0;
                    free(itmp);
                ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 472 "tamim.y"
    {
                    cnt++;
                    itmp = realloc(itmp,cnt*sizeof(int));;
                    itmp[cnt-1]=(yyvsp[(3) - (3)].real);
                ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 478 "tamim.y"
    {
                    cnt++;
                    itmp = realloc(itmp,cnt*sizeof(int));;
                    itmp[cnt-1]=(int)(yyvsp[(1) - (1)].real);
                ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 485 "tamim.y"
    {;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 486 "tamim.y"
    {;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 490 "tamim.y"
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

  case 31:

/* Line 1455 of yacc.c  */
#line 502 "tamim.y"
    {
                double value = rand();
                insertData((yyvsp[(1) - (1)].string),&value,1,varCnt,1,0);
                varCnt++;
            ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 508 "tamim.y"
    {
                    printf("Real Array Declaration.\n");
                    insertData((yyvsp[(1) - (1)].string),dtmp,1,varCnt,cnt,1);
                    varCnt++;
                ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 514 "tamim.y"
    {
                    insertData((yyvsp[(1) - (5)].string),dtmp,1,varCnt,cnt,1);
                    varCnt++;
                    cnt = 0;
                    free(dtmp);
                ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 523 "tamim.y"
    {
                    cnt++;
                    dtmp = realloc(dtmp,cnt*sizeof(double));;
                    dtmp[cnt-1]=(yyvsp[(3) - (3)].real);
                ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 529 "tamim.y"
    {
                    cnt++;
                    dtmp = realloc(dtmp,cnt*sizeof(double));;
                    dtmp[cnt-1]=(yyvsp[(1) - (1)].real);
                ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 536 "tamim.y"
    {;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 537 "tamim.y"
    {;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 541 "tamim.y"
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

  case 39:

/* Line 1455 of yacc.c  */
#line 554 "tamim.y"
    {
                    char* value = "";
                    insertData((yyvsp[(1) - (1)].string),&value,2,varCnt,1,0);
                    varCnt++;
                ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 560 "tamim.y"
    {
                    printf("Integer Array Declaration.\n");
                    insertData((yyvsp[(1) - (1)].string),stmp,2,varCnt,cnt,1);
                    varCnt++;
                ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 566 "tamim.y"
    {
                    printf("String Array of size:%d\n",cnt);
                    insertData((yyvsp[(1) - (5)].string),stmp,2,varCnt,cnt,1);
                    varCnt++;
                    cnt = 0;
                    free(stmp);
                ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 576 "tamim.y"
    {
                    cnt++;
                    stmp = realloc(stmp,cnt*sizeof(char*));;
                    stmp[cnt-1]=(yyvsp[(3) - (3)].string);
                ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 582 "tamim.y"
    {
                    cnt++;
                    stmp = realloc(stmp,cnt*sizeof(char*));;
                    stmp[cnt-1]=(yyvsp[(1) - (1)].string);
                ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 593 "tamim.y"
    {
                    printVariable((yyvsp[(3) - (3)].string));
                ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 597 "tamim.y"
    {
                    printVariable((yyvsp[(3) - (3)].string));
                ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 601 "tamim.y"
    {
                    printArrayIndex((yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].real));
                ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 605 "tamim.y"
    {
                    printVariable((yyvsp[(1) - (1)].string));
                ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 609 "tamim.y"
    {
                    printVariable((yyvsp[(1) - (1)].string));
                ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 613 "tamim.y"
    {
                    printArrayIndex((yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].real));
                ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 625 "tamim.y"
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

  case 54:

/* Line 1455 of yacc.c  */
#line 642 "tamim.y"
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

  case 55:

/* Line 1455 of yacc.c  */
#line 665 "tamim.y"
    {;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 669 "tamim.y"
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

  case 61:

/* Line 1455 of yacc.c  */
#line 691 "tamim.y"
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

  case 64:

/* Line 1455 of yacc.c  */
#line 720 "tamim.y"
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

  case 65:

/* Line 1455 of yacc.c  */
#line 747 "tamim.y"
    {conditionMatched = 0;;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 751 "tamim.y"
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

  case 69:

/* Line 1455 of yacc.c  */
#line 770 "tamim.y"
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

  case 72:

/* Line 1455 of yacc.c  */
#line 790 "tamim.y"
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

  case 73:

/* Line 1455 of yacc.c  */
#line 816 "tamim.y"
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

  case 74:

/* Line 1455 of yacc.c  */
#line 833 "tamim.y"
    {
                    
                    printf("While will run for %d times\n",(yyvsp[(2) - (5)].integer));
                    
                    for(int i = 0;i<(yyvsp[(2) - (5)].integer);i++){
                        printf("Value of Statement %.4lf\n",(yyvsp[(4) - (5)].real));
                    }
                ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 842 "tamim.y"
    {
                    
                    printf("repeat while will run for %d times\n",(yyvsp[(6) - (7)].integer));
                    
                ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 850 "tamim.y"
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

  case 77:

/* Line 1455 of yacc.c  */
#line 865 "tamim.y"
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

  case 78:

/* Line 1455 of yacc.c  */
#line 880 "tamim.y"
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

  case 79:

/* Line 1455 of yacc.c  */
#line 895 "tamim.y"
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

  case 80:

/* Line 1455 of yacc.c  */
#line 910 "tamim.y"
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

  case 81:

/* Line 1455 of yacc.c  */
#line 925 "tamim.y"
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

  case 83:

/* Line 1455 of yacc.c  */
#line 946 "tamim.y"
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

  case 86:

/* Line 1455 of yacc.c  */
#line 964 "tamim.y"
    {
                    int id = stk[funCnt].varCnt;
                    int value = rand();
                    insertData((yyvsp[(2) - (2)].string),&value,0,varCnt,1,0);
                    stk[funCnt].fptr[id] = vptr[varCnt];
                    varCnt++;
                    stk[funCnt].varCnt++;
                ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 973 "tamim.y"
    {
                    int id = stk[funCnt].varCnt;
                    double value = rand();
                    insertData((yyvsp[(2) - (2)].string),&value,1,varCnt,1,0);
                    stk[funCnt].fptr[id] = vptr[varCnt];
                    varCnt++;
                    stk[funCnt].varCnt++;
                ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 982 "tamim.y"
    {
                    int id = stk[funCnt].varCnt;
                    char* value = "";
                    insertData((yyvsp[(1) - (2)].string),&value,2,varCnt,1,0);
                    stk[funCnt].fptr[id] = vptr[varCnt];
                    varCnt++;
                    stk[funCnt].varCnt++;
                ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 993 "tamim.y"
    {
                    if(functionRejected){
                        
                        printf("Module was not called as declared\n");
                        
                    }
                    else{
                        printf("Module called Successfully.\n");
                    }
                ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1006 "tamim.y"
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

  case 93:

/* Line 1455 of yacc.c  */
#line 1022 "tamim.y"
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

  case 94:

/* Line 1455 of yacc.c  */
#line 1043 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (6)].string));
                    if(id==-1) doesNotExist((yyvsp[(1) - (6)].string));
                    else if(vptr[id].isArray==0)
                        notArray((yyvsp[(1) - (6)].string));
                    else{
                            if(vptr[id].type== 2){
                                notNumeric();
                            }
                            else{
                                double x = (yyvsp[(5) - (6)].real);
                               appendData(id,&x);
                            }
                        }
                    
                ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1060 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (5)].string));
                    if(id==-1) doesNotExist((yyvsp[(1) - (5)].string));
                    else{
                        popLast(id);
                    }
                ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1068 "tamim.y"
    {
                    int id = getVariableIndex((yyvsp[(1) - (3)].string));
                    if(id==-1) doesNotExist((yyvsp[(1) - (3)].string));
                    else if(vptr[id].isArray==0)
                        notArray((yyvsp[(1) - (3)].string));
                    else{
                            sort(id);
                        }
                
                ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1081 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (1)].integer);
                ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1085 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (1)].real);
                ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1090 "tamim.y"
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

  case 100:

/* Line 1455 of yacc.c  */
#line 1100 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(2) - (2)].real);
                ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1104 "tamim.y"
    {
                    (yyval.real) = -(yyvsp[(2) - (2)].real);
                ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1108 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(2) - (2)].real);
                ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1112 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(2) - (2)].real);
                ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1116 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (3)].real) + (yyvsp[(3) - (3)].real);
                ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1120 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (3)].real) - (yyvsp[(3) - (3)].real);
                ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1124 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (3)].real) * (yyvsp[(3) - (3)].real);
                ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1128 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(1) - (3)].real) / (yyvsp[(3) - (3)].real);
                ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1132 "tamim.y"
    {
                    (yyval.real) = pow((yyvsp[(1) - (3)].real),(yyvsp[(3) - (3)].real));
                ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1136 "tamim.y"
    {

                    (yyval.real) = (int)(yyvsp[(1) - (3)].real) % (int)(yyvsp[(3) - (3)].real);
                ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1141 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) < (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1145 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) > (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1149 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) <= (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1153 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) >= (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1157 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) == (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1161 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) != (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1165 "tamim.y"
    {
                    (yyval.real) = ( (yyvsp[(1) - (3)].real) && (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1169 "tamim.y"
    {
                    (yyval.real) = ((yyvsp[(1) - (3)].real) || (yyvsp[(3) - (3)].real));
                ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1173 "tamim.y"
    {
                    (yyval.real) = ((int)(yyvsp[(1) - (3)].real) ^ (int)(yyvsp[(3) - (3)].real));
                ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1177 "tamim.y"
    {
                    (yyval.real) = !(yyvsp[(2) - (2)].real);
                ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1181 "tamim.y"
    {
                    (yyval.real) = (yyvsp[(2) - (3)].real);
                ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1185 "tamim.y"
    {
                    (yyval.real) = sin((yyvsp[(3) - (4)].real));

                ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1190 "tamim.y"
    {
                    (yyval.real) = cos((yyvsp[(3) - (4)].real));
                ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1194 "tamim.y"
    {
                    (yyval.real) = tan((yyvsp[(3) - (4)].real));
                ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1198 "tamim.y"
    {
                    (yyval.real) = log10((yyvsp[(3) - (4)].real));
                ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1202 "tamim.y"
    {
                    (yyval.real) = log2((yyvsp[(3) - (4)].real));
                ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1206 "tamim.y"
    {
                    (yyval.real) = log((yyvsp[(3) - (4)].real));
                ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1210 "tamim.y"
    {
                    (yyval.real) = sqrt((yyvsp[(3) - (4)].real));
                ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1214 "tamim.y"
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

  case 129:

/* Line 1455 of yacc.c  */
#line 1226 "tamim.y"
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

  case 130:

/* Line 1455 of yacc.c  */
#line 1237 "tamim.y"
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
#line 3435 "tamim.tab.c"
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
#line 1248 "tamim.y"



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
 
     



