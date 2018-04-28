/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

	#include "quad.h"

	struct forPrefix{
		int test;
		int enter;
	};

	unsigned tempcounter=0;
	quad*    quads = (quad*) 0;
	unsigned total=0;
	unsigned currQuad = 0;

	unsigned programVarOffset=0;
	unsigned functionLocalOffset=0;
	unsigned formalArgOffset=0;

	unsigned suffixNum=0;
	unsigned currScope=0;
	unsigned currRange=1;
	unsigned currOffset=0;
	HashTable SymTable;
	std::fstream buffer;
	std::stack<unsigned> offsetStack,labelStack;


#line 93 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTCONST = 259,
    STRING = 260,
    REALCONST = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    FOR = 265,
    FUNCTION = 266,
    RETURN = 267,
    BREAK = 268,
    CONTINUE = 269,
    NIL = 270,
    LOCAL = 271,
    AND = 272,
    NOT = 273,
    OR = 274,
    TRUE = 275,
    FALSE = 276,
    SCOPE = 277,
    NOT_EQUAL = 278,
    EQUAL_EQUAL = 279,
    DOT_DOT = 280,
    GREATER_EQUAL = 281,
    LESS_EQUAL = 282,
    MINUS_MINUS = 283,
    PLUS_PLUS = 284,
    UMINUS = 285
  };
#endif
/* Tokens.  */
#define ID 258
#define INTCONST 259
#define STRING 260
#define REALCONST 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define FOR 265
#define FUNCTION 266
#define RETURN 267
#define BREAK 268
#define CONTINUE 269
#define NIL 270
#define LOCAL 271
#define AND 272
#define NOT 273
#define OR 274
#define TRUE 275
#define FALSE 276
#define SCOPE 277
#define NOT_EQUAL 278
#define EQUAL_EQUAL 279
#define DOT_DOT 280
#define GREATER_EQUAL 281
#define LESS_EQUAL 282
#define MINUS_MINUS 283
#define PLUS_PLUS 284
#define UMINUS 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 35 "parser.y" /* yacc.c:355  */

	int intVal;
	char* strVal;
	double realVal;
	struct Symbol* sym;
	struct expr *node;
	struct forPrefix *prefix;

#line 202 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 219 "parser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  72
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   655

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  181

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    36,     2,     2,
      42,    43,    34,    32,    45,    33,    39,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    44,
      31,    29,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    48,     2,     2,     2,     2,
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
      25,    26,    27,    28,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    67,    67,    68,    71,    75,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    93,    94,   106,   109,
     114,   119,   124,   129,   134,   145,   156,   167,   178,   189,
     195,   200,   213,   214,   220,   221,   236,   251,   266,   281,
     284,   303,   304,   305,   306,   307,   310,   329,   351,   363,
     366,   367,   368,   369,   372,   373,   374,   377,   378,   382,
     385,   388,   389,   390,   393,   396,   399,   400,   404,   405,
     408,   412,   415,   415,   422,   422,   432,   433,   440,   477,
     480,   486,   502,   509,   516,   517,   518,   519,   522,   523,
     547,   550,   574,   575,   578,   581,   586,   589,   598,   609,
     610
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTCONST", "STRING", "REALCONST",
  "IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE",
  "NIL", "LOCAL", "AND", "NOT", "OR", "TRUE", "FALSE", "SCOPE",
  "NOT_EQUAL", "EQUAL_EQUAL", "DOT_DOT", "GREATER_EQUAL", "LESS_EQUAL",
  "MINUS_MINUS", "'='", "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "PLUS_PLUS", "UMINUS", "'.'", "'['", "']'", "'('", "')'", "';'", "','",
  "'{'", "':'", "'}'", "$accept", "program", "stmts", "stmt", "expr", "op",
  "term", "assignexpr", "primary", "lvalue", "member", "call",
  "callsuffix", "normcall", "methodcall", "elist", "exprs", "objectdef",
  "objectdefs", "indexed", "indexeds", "indexedelem", "block", "$@1",
  "$@2", "funcname", "funcprefix", "funcargs", "funcbody", "funcdef",
  "const", "idlist", "idlists", "ifstmt", "whilestmt", "N", "M",
  "forprefix", "for", "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    61,
      62,    60,    43,    45,    42,    47,    37,   284,   285,    46,
      91,    93,    40,    41,    59,    44,   123,    58,   125
};
# endif

#define YYPACT_NINF -160

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-160)))

#define YYTABLE_NINF -75

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-75)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     197,  -160,  -160,  -160,  -160,   -19,   -10,    -2,    30,   285,
      -3,    16,  -160,    41,   367,  -160,  -160,    47,     0,   367,
       0,   241,   327,  -160,     9,    63,   197,  -160,   411,  -160,
    -160,  -160,     6,  -160,    12,  -160,  -160,    42,  -160,  -160,
      70,  -160,  -160,  -160,  -160,   367,   367,   367,  -160,  -160,
    -160,   433,  -160,  -160,  -160,  -160,  -160,    72,    22,    12,
    -160,    22,   367,   580,    48,    53,    56,  -160,   477,    65,
     197,    58,  -160,  -160,   367,   367,   367,   367,   367,   367,
     367,   367,   367,   367,   367,   367,   367,  -160,  -160,   107,
    -160,   367,  -160,   109,   367,   367,  -160,  -160,  -160,   111,
     367,   367,   113,    71,   197,   367,   498,   519,   -30,  -160,
      75,   389,   367,  -160,  -160,    88,  -160,  -160,    79,   151,
    -160,   594,    -6,   608,   608,   619,   619,   619,   619,   -27,
     -27,  -160,  -160,  -160,    91,   580,  -160,   540,    13,  -160,
     560,    36,  -160,    44,  -160,  -160,  -160,    45,   197,   197,
    -160,    79,   367,   580,  -160,   367,  -160,   367,  -160,  -160,
    -160,  -160,  -160,   132,  -160,  -160,  -160,  -160,   367,    96,
      54,    55,  -160,   197,   455,  -160,  -160,  -160,  -160,  -160,
    -160
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    46,    82,    84,    83,     0,     0,     0,    77,     0,
       0,     0,    85,     0,     0,    86,    87,     0,     0,     0,
       0,    63,     0,    15,    72,     0,     2,     5,     0,    18,
      16,    39,    41,    49,    42,    43,    13,     0,    14,    45,
       7,     8,    95,     9,    10,     0,     0,    63,    76,    78,
     100,     0,    11,    12,    47,    34,    48,     0,    37,     0,
      33,    35,     0,    62,    66,     0,    67,    69,     0,     0,
       0,     0,     1,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,    17,     0,
      38,     0,    36,     0,     0,    63,    55,    57,    58,     0,
       0,    63,    90,     0,     0,    63,     0,     0,     0,    99,
       0,     0,     0,    61,    65,     0,    68,    32,    44,     0,
      75,    29,    30,    28,    31,    25,    27,    24,    26,    19,
      20,    21,    22,    23,     0,    40,    50,     0,     0,    52,
       0,     0,    89,     0,    80,    81,    92,     0,     0,     0,
      96,     0,     0,    64,    70,    63,    73,    63,    51,    59,
      53,    54,    79,     0,    88,    95,    93,    94,     0,     0,
       0,     0,    91,     0,     0,    71,    56,    60,    95,    97,
      98
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -160,  -160,    66,   -24,    -9,  -160,  -160,  -160,  -160,    84,
    -160,    87,  -160,  -160,  -160,   -46,  -160,  -160,  -160,  -160,
    -160,    23,    34,  -160,  -160,  -160,  -160,  -160,  -160,   -18,
    -160,  -160,  -160,  -160,  -160,  -159,  -160,  -160,  -160,  -160
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    88,    29,    30,    31,    32,
      33,    34,    96,    97,    98,    64,   113,    35,    65,    66,
     116,    67,    36,    70,    71,    49,    37,   103,   145,    38,
      39,   143,   164,    40,    41,   105,   168,    42,    43,    44
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,   108,    73,     1,    69,    55,   173,    84,    85,    86,
      60,    74,    63,    68,   150,   112,    13,    76,    77,   180,
      78,    79,    17,    45,    80,    81,    82,    83,    84,    85,
      86,    89,    46,    48,    90,    91,   106,   107,    63,   110,
      47,    52,    57,    92,    54,    93,    94,    89,    95,   138,
      56,    99,   100,   111,   101,   141,   159,   -74,   112,   147,
      53,    93,    94,    72,    95,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   104,   161,
     146,   112,   135,     8,   102,   137,    63,   162,   165,   163,
     112,   140,    63,   112,   114,    73,    63,   176,   177,   112,
     112,   115,    58,   153,    61,    59,   120,    59,   118,   170,
     134,   171,   136,    74,   139,    75,   142,    24,   151,    76,
      77,   155,    78,    79,   166,   167,    80,    81,    82,    83,
      84,    85,    86,   157,    62,   172,   119,   144,   154,     0,
       0,     0,     0,   169,   175,     0,    63,     0,    63,   178,
       0,     0,     0,     0,     1,     2,     3,     4,     5,   174,
       6,     7,     8,     9,    10,    11,    12,    13,     0,    14,
       0,    15,    16,    17,     0,     0,     0,     0,     0,    18,
       0,     0,     0,     0,    19,     0,     0,     0,    20,     0,
       0,    21,     0,    22,     0,    23,     0,    24,     0,   156,
       1,     2,     3,     4,     5,     0,     6,     7,     8,     9,
      10,    11,    12,    13,     0,    14,     0,    15,    16,    17,
       0,     0,     0,     0,     0,    18,     0,     0,     0,     0,
      19,     0,     0,     0,    20,     0,     0,    21,     0,    22,
       0,    23,     0,    24,     1,     2,     3,     4,     0,     0,
       0,     0,     0,     0,     0,     0,    12,    13,     0,    14,
       0,    15,    16,    17,     0,     0,     0,     0,     0,    18,
       0,     0,     0,     0,    19,     0,     0,     0,    20,     0,
       0,    21,     0,    22,     0,     0,     0,    62,     1,     2,
       3,     4,     0,     0,     0,     0,     0,     0,     0,     0,
      12,    13,     0,    14,     0,    15,    16,    17,     0,     0,
       0,     0,     0,    18,     0,     0,     0,     0,    19,     0,
       0,     0,    20,     0,     0,    21,     0,    22,     0,    50,
       1,     2,     3,     4,     0,     0,     0,     0,     8,     0,
       0,     0,    12,    13,     0,    14,     0,    15,    16,    17,
       0,     0,     0,     0,     0,    18,     0,     0,     0,     0,
      19,     0,     0,     0,    20,     0,     0,    21,     0,    22,
       1,     2,     3,     4,     0,     0,     0,     0,     0,     0,
       0,     0,    12,    13,     0,    14,     0,    15,    16,    17,
       0,     0,     0,     0,     0,    18,     0,     0,     0,     0,
      19,     0,     0,     0,    20,     0,    74,    21,    75,    22,
       0,     0,    76,    77,     0,    78,    79,     0,     0,    80,
      81,    82,    83,    84,    85,    86,     0,     0,    74,     0,
      75,     0,     0,     0,    76,    77,   152,    78,    79,     0,
       0,    80,    81,    82,    83,    84,    85,    86,     0,     0,
      74,     0,    75,     0,     0,    87,    76,    77,     0,    78,
      79,     0,     0,    80,    81,    82,    83,    84,    85,    86,
       0,     0,    74,     0,    75,     0,     0,   109,    76,    77,
       0,    78,    79,     0,     0,    80,    81,    82,    83,    84,
      85,    86,     0,     0,    74,     0,    75,     0,     0,   179,
      76,    77,     0,    78,    79,     0,     0,    80,    81,    82,
      83,    84,    85,    86,     0,    74,     0,    75,     0,     0,
     117,    76,    77,     0,    78,    79,     0,     0,    80,    81,
      82,    83,    84,    85,    86,     0,    74,     0,    75,     0,
       0,   148,    76,    77,     0,    78,    79,     0,     0,    80,
      81,    82,    83,    84,    85,    86,     0,    74,     0,    75,
       0,     0,   149,    76,    77,     0,    78,    79,     0,     0,
      80,    81,    82,    83,    84,    85,    86,    74,     0,    75,
       0,   158,     0,    76,    77,     0,    78,    79,     0,     0,
      80,    81,    82,    83,    84,    85,    86,    74,     0,    75,
       0,   160,     0,    76,    77,     0,    78,    79,     0,     0,
      80,    81,    82,    83,    84,    85,    86,    76,    77,     0,
      78,    79,     0,     0,    80,    81,    82,    83,    84,    85,
      86,   -75,   -75,     0,    78,    79,     0,     0,    80,    81,
      82,    83,    84,    85,    86,   -75,   -75,     0,     0,   -75,
     -75,    82,    83,    84,    85,    86
};

static const yytype_int16 yycheck[] =
{
       9,    47,    26,     3,    22,    14,   165,    34,    35,    36,
      19,    17,    21,    22,    44,    45,    16,    23,    24,   178,
      26,    27,    22,    42,    30,    31,    32,    33,    34,    35,
      36,    25,    42,     3,    28,    29,    45,    46,    47,    57,
      42,    44,    42,    37,     3,    39,    40,    25,    42,    95,
       3,    39,    40,    62,    42,   101,    43,    48,    45,   105,
      44,    39,    40,     0,    42,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,     8,    43,
     104,    45,    91,    11,    42,    94,    95,    43,    43,    45,
      45,   100,   101,    45,    41,   119,   105,    43,    43,    45,
      45,    45,    18,   112,    20,    18,    48,    20,    43,   155,
       3,   157,     3,    17,     3,    19,     3,    46,    43,    23,
      24,    42,    26,    27,   148,   149,    30,    31,    32,    33,
      34,    35,    36,    42,    46,     3,    70,   103,   115,    -1,
      -1,    -1,    -1,   152,    48,    -1,   155,    -1,   157,   173,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,   168,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    18,
      -1,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    37,    -1,
      -1,    40,    -1,    42,    -1,    44,    -1,    46,    -1,    48,
       3,     4,     5,     6,     7,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    18,    -1,    20,    21,    22,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    -1,    37,    -1,    -1,    40,    -1,    42,
      -1,    44,    -1,    46,     3,     4,     5,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    -1,    18,
      -1,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    37,    -1,
      -1,    40,    -1,    42,    -1,    -1,    -1,    46,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    16,    -1,    18,    -1,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    33,    -1,
      -1,    -1,    37,    -1,    -1,    40,    -1,    42,    -1,    44,
       3,     4,     5,     6,    -1,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    15,    16,    -1,    18,    -1,    20,    21,    22,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    -1,    37,    -1,    -1,    40,    -1,    42,
       3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    15,    16,    -1,    18,    -1,    20,    21,    22,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    -1,    37,    -1,    17,    40,    19,    42,
      -1,    -1,    23,    24,    -1,    26,    27,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    17,    -1,
      19,    -1,    -1,    -1,    23,    24,    47,    26,    27,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      17,    -1,    19,    -1,    -1,    44,    23,    24,    -1,    26,
      27,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    17,    -1,    19,    -1,    -1,    44,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    17,    -1,    19,    -1,    -1,    44,
      23,    24,    -1,    26,    27,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    17,    -1,    19,    -1,    -1,
      43,    23,    24,    -1,    26,    27,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    17,    -1,    19,    -1,
      -1,    43,    23,    24,    -1,    26,    27,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    17,    -1,    19,
      -1,    -1,    43,    23,    24,    -1,    26,    27,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    17,    -1,    19,
      -1,    41,    -1,    23,    24,    -1,    26,    27,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    17,    -1,    19,
      -1,    41,    -1,    23,    24,    -1,    26,    27,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    23,    24,    -1,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    23,    24,    -1,    26,    27,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    26,    27,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      13,    14,    15,    16,    18,    20,    21,    22,    28,    33,
      37,    40,    42,    44,    46,    50,    51,    52,    53,    55,
      56,    57,    58,    59,    60,    66,    71,    75,    78,    79,
      82,    83,    86,    87,    88,    42,    42,    42,     3,    74,
      44,    53,    44,    44,     3,    53,     3,    42,    58,    60,
      53,    58,    46,    53,    64,    67,    68,    70,    53,    78,
      72,    73,     0,    52,    17,    19,    23,    24,    26,    27,
      30,    31,    32,    33,    34,    35,    36,    44,    54,    25,
      28,    29,    37,    39,    40,    42,    61,    62,    63,    39,
      40,    42,    42,    76,     8,    84,    53,    53,    64,    44,
      78,    53,    45,    65,    41,    45,    69,    43,    43,    51,
      48,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,     3,    53,     3,    53,    64,     3,
      53,    64,     3,    80,    71,    77,    52,    64,    43,    43,
      44,    43,    47,    53,    70,    42,    48,    42,    41,    43,
      41,    43,    43,    45,    81,    43,    52,    52,    85,    53,
      64,    64,     3,    84,    53,    48,    43,    43,    52,    44,
      84
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    53,    53,    53,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    57,    57,    57,    57,    57,    58,    58,    58,    58,
      59,    59,    59,    59,    60,    60,    60,    61,    61,    62,
      63,    64,    64,    64,    65,    66,    67,    67,    68,    68,
      69,    70,    72,    71,    73,    71,    74,    74,    75,    76,
      77,    78,    79,    79,    79,    79,    79,    79,    80,    80,
      80,    81,    82,    82,    83,    84,    85,    86,    87,    88,
      88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     2,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     2,     2,     2,     2,     2,     2,     1,
       3,     1,     1,     1,     3,     1,     1,     2,     2,     1,
       3,     4,     3,     4,     4,     2,     6,     1,     1,     3,
       5,     2,     1,     0,     2,     3,     1,     1,     2,     1,
       2,     5,     0,     4,     0,     3,     1,     0,     2,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     2,     1,
       0,     2,     3,     5,     5,     0,     0,     7,     7,     3,
       2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 67 "parser.y" /* yacc.c:1646  */
    {std::cout<<"Program <- stmts"<<std::endl;}
#line 1522 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 68 "parser.y" /* yacc.c:1646  */
    {std::cout<<"Program <- (empty)"<<std::endl;}
#line 1528 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 71 "parser.y" /* yacc.c:1646  */
    {
					//tempcounter=0;
					std::cout<<"stmts <- stmts stmt"<<std::endl;
				}
#line 1537 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 75 "parser.y" /* yacc.c:1646  */
    {
					//tempcounter=0;
					std::cout<<"stmts <- stmt"<<std::endl;
				}
#line 1546 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 81 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- expr(;)"<<std::endl;}
#line 1552 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 82 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- ifstmt"<<std::endl;}
#line 1558 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 83 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- whilestmt"<<std::endl;}
#line 1564 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 84 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- forstmt"<<std::endl;}
#line 1570 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 85 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- returnstmt"<<std::endl;}
#line 1576 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 86 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- break(;)"<<std::endl;}
#line 1582 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 87 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- continue(;)"<<std::endl;}
#line 1588 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 88 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- block"<<std::endl;}
#line 1594 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 89 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- funcdef"<<std::endl;}
#line 1600 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 90 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- semicolon(;)"<<std::endl;}
#line 1606 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 93 "parser.y" /* yacc.c:1646  */
    {std::cout<<"expr <- assignexpr"<<std::endl;}
#line 1612 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 94 "parser.y" /* yacc.c:1646  */
    {
					if(quads[currQuad-(yyvsp[0].intVal)].arg1==NULL){
						quads[currQuad-(yyvsp[0].intVal)].result=newexpr(arithexpr_e);
						quads[currQuad-(yyvsp[0].intVal)].result->sym=newtemp();

						quads[currQuad-(yyvsp[0].intVal)].arg1 = (yyvsp[-1].node);
						(yyval.node)=quads[currQuad-(yyvsp[0].intVal)].result;
					}else{
						quads[currQuad-(yyvsp[0].intVal)].result=(yyvsp[-1].node);
					}
					std::cout<<"expr <- expr op"<<std::endl;
				}
#line 1629 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 106 "parser.y" /* yacc.c:1646  */
    {std::cout<<"expr <- term"<<std::endl;}
#line 1635 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 109 "parser.y" /* yacc.c:1646  */
    {
						emit(add,(expr*)0,(yyvsp[0].node),(expr*)0,0,yylineno);
						(yyval.intVal)=1;
						std::cout<<"op <- + expr"<<std::endl;
					}
#line 1645 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 114 "parser.y" /* yacc.c:1646  */
    {
						emit(sub,(expr*)0,(yyvsp[0].node),(expr*)0,0,yylineno);
						(yyval.intVal)=1;
						std::cout<<"op <- - expr"<<std::endl;
					}
#line 1655 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 119 "parser.y" /* yacc.c:1646  */
    {
						emit(mul,(expr*)0,(yyvsp[0].node),(expr*)0,0,yylineno);
						(yyval.intVal)=1;
						std::cout<<"op <- * expr"<<std::endl;
					}
#line 1665 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 124 "parser.y" /* yacc.c:1646  */
    {
						emit(Div,(expr*)0,(yyvsp[0].node),(expr*)0,0,yylineno);
						(yyval.intVal)=1;
						std::cout<<"op <- / expr"<<std::endl;
					}
#line 1675 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 129 "parser.y" /* yacc.c:1646  */
    {
						emit(mod,(expr*)0,(yyvsp[0].node),(expr*)0,0,yylineno);
						(yyval.intVal)=1;
						std::cout<<"op <- % expr"<<std::endl;
					}
#line 1685 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 134 "parser.y" /* yacc.c:1646  */
    {
						emit(if_greater,(yyvsp[0].node),newexpr_constnum_e(currQuad+2),(expr*)0,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+3,yylineno);
						expr *e=newexpr(assignexpr_e);
						e->sym=newtemp();
						emit(assign,newexpr_constbool_e(true),(expr*)0,e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
						emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
						(yyval.intVal) = 5;
						std::cout<<"op <- > expr"<<std::endl;
					}
#line 1701 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 145 "parser.y" /* yacc.c:1646  */
    {
						emit(if_greatereq,(yyvsp[0].node),newexpr_constnum_e(currQuad+2),(expr*)0,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+3,yylineno);
						expr *e=newexpr(assignexpr_e);
						e->sym=newtemp();
						emit(assign,newexpr_constbool_e(true),(expr*)0,e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
						emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
						(yyval.intVal) = 5;
						std::cout<<"op <- >= expr"<<std::endl;
					}
#line 1717 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 156 "parser.y" /* yacc.c:1646  */
    {
						emit(if_less,(yyvsp[0].node),newexpr_constnum_e(currQuad+2),(expr*)0,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+3,yylineno);
						expr *e=newexpr(assignexpr_e);
						e->sym=newtemp();
						emit(assign,newexpr_constbool_e(true),(expr*)0,e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
						emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
						(yyval.intVal) = 5;
						std::cout<<"op <- < expr"<<std::endl;
					}
#line 1733 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 167 "parser.y" /* yacc.c:1646  */
    {
						emit(if_lesseq,(yyvsp[0].node),newexpr_constnum_e(currQuad+2),(expr*)0,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+3,yylineno);
						expr *e=newexpr(assignexpr_e);
						e->sym=newtemp();
						emit(assign,newexpr_constbool_e(true),(expr*)0,e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
						emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
						(yyval.intVal) = 5;
						std::cout<<"op <- <= expr"<<std::endl;
					}
#line 1749 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 178 "parser.y" /* yacc.c:1646  */
    {
						emit(if_noteq,(yyvsp[0].node),newexpr_constnum_e(currQuad+2),(expr*)0,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+3,yylineno);
						expr *e=newexpr(assignexpr_e);
						e->sym=newtemp();
						emit(assign,newexpr_constbool_e(true),(expr*)0,e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
						emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
						(yyval.intVal) = 5;
						std::cout<<"op <- != expr"<<std::endl;
					}
#line 1765 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 189 "parser.y" /* yacc.c:1646  */
    {
						emit(And,(expr*)0,(yyvsp[0].node),(expr*)0,0,yylineno);
						(yyval.intVal) = 1;

						std::cout<<"op <- && expr"<<std::endl;
					}
#line 1776 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 195 "parser.y" /* yacc.c:1646  */
    {
						emit(Or,(expr*)0,(yyvsp[0].node),(expr*)0,0,yylineno);
						(yyval.intVal) = 1;
						std::cout<<"op <- || expr"<<std::endl;
					}
#line 1786 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 200 "parser.y" /* yacc.c:1646  */
    {
						emit(if_eq,(yyvsp[0].node),newexpr_constnum_e(currQuad+2),(expr*)0,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+3,yylineno);
						expr *e=newexpr(assignexpr_e);
						e->sym=newtemp();
						emit(assign,newexpr_constbool_e(true),(expr*)0,e,0,yylineno);
						emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
						emit(assign,newexpr_constbool_e(false),(expr*)0,e,0,yylineno);
						(yyval.intVal) = 5;
						std::cout<<"op <- == expr"<<std::endl;
					}
#line 1802 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 213 "parser.y" /* yacc.c:1646  */
    {std::cout<<"term <- ( expr )"<<std::endl;}
#line 1808 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 214 "parser.y" /* yacc.c:1646  */
    {
						expr* e = newexpr(arithexpr_e);
						e->sym = newtemp();
						emit(uminus,(yyvsp[0].node),(expr*)0,e,0,yylineno);
						std::cout<<"term <- - expr (UMINUS)"<<std::endl;
					}
#line 1819 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 220 "parser.y" /* yacc.c:1646  */
    {std::cout<<"term <- ! expr"<<std::endl;}
#line 1825 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 221 "parser.y" /* yacc.c:1646  */
    {
						if(((yyvsp[0].node)->sym!=NULL) && ((yyvsp[0].node)->sym->type == LIBRARY_FUNC || (yyvsp[0].node)->sym->type == PROGRAM_FUNC)){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Invalid use of prefix operator ++ : " << (yyvsp[0].node)->sym->name << " refers to a function type."<<std::endl;
						}else if((yyvsp[0].node)->sym==NULL){
                                                        buffer<<"Line: " <<yylineno<< ":";
                                                        buffer<<" undeclared variable."<<std::endl;
                                                }
						emit(add,(yyvsp[0].node),newexpr_constnum_e(1),(yyvsp[0].node),0,yylineno);
						expr* e = newexpr(arithexpr_e);
						e->sym = newtemp();
						emit(assign,(yyvsp[0].node),(expr*)0,e,0,yylineno);
						(yyval.node)=(yyvsp[0].node);
						std::cout<<"term <- ++ lvalue"<<std::endl;
					}
#line 1845 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 236 "parser.y" /* yacc.c:1646  */
    {
						if(((yyvsp[-1].node)->sym!=NULL)&& ((yyvsp[-1].node)->sym->type == LIBRARY_FUNC || (yyvsp[-1].node)->sym->type == PROGRAM_FUNC)){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Invalid use of suffix operator ++ : " << (yyvsp[-1].node)->sym->name << " refers to a function type."<<std::endl;
						}else if((yyvsp[-1].node)->sym==NULL){
							buffer<<"Line: " <<yylineno<< ":\n\t";
							buffer<<"undeclared variable."<<std::endl;
						}
						expr* e = newexpr(arithexpr_e);
						e->sym = newtemp();
						emit(assign,(yyvsp[-1].node),(expr*)0,e,0,yylineno);
						emit(add,(yyvsp[-1].node),newexpr_constnum_e(1),(yyvsp[-1].node),0,yylineno);
						(yyval.node) = e;
						std::cout<<"term <- lvalue ++"<<std::endl;
					}
#line 1865 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 251 "parser.y" /* yacc.c:1646  */
    {
						if(((yyvsp[0].node)->sym!=NULL) && ((yyvsp[0].node)->sym->type == LIBRARY_FUNC || (yyvsp[0].node)->sym->type == PROGRAM_FUNC)){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Invalid use of prefix operator -- : " << (yyvsp[0].node)->sym->name << " refers to a function type.\n";
						}else if((yyvsp[0].node)->sym==NULL){
                                                        buffer<<"Line: " <<yylineno<< ":\n\t";
                                                        buffer<<"undeclared variable."<<std::endl;
                                                }
						emit(sub,(yyvsp[0].node),newexpr_constnum_e(1),(yyvsp[0].node),0,yylineno);
						expr* e = newexpr(arithexpr_e);
						e->sym = newtemp();
						emit(assign,(yyvsp[0].node),(expr*)0,e,0,yylineno);
						(yyval.node)=(yyvsp[0].node);
						std::cout<<"term <- -- lvalue"<<std::endl;
					}
#line 1885 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 266 "parser.y" /* yacc.c:1646  */
    {
						if(((yyvsp[-1].node)->sym!=NULL) && ((yyvsp[-1].node)->sym->type == LIBRARY_FUNC || (yyvsp[-1].node)->sym->type == PROGRAM_FUNC)){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Invalid use of suffix operator -- : " << (yyvsp[-1].node)->sym->name << " refers to a function type.\n";
						}else if((yyvsp[-1].node)->sym==NULL){
                                                        buffer<<"Line: " <<yylineno<< ":\n\t";
                                                        buffer<<"undeclared variable."<<std::endl;
                                                }
						expr* e = newexpr(arithexpr_e);
						e->sym = newtemp();
						emit(assign,(yyvsp[-1].node),(expr*)0,e,0,yylineno);
						emit(sub,(yyvsp[-1].node),newexpr_constnum_e(1),(yyvsp[-1].node),0,yylineno);
						(yyval.node) = e;
						std::cout<<"term <- lvalue --"<<std::endl;
					}
#line 1905 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 281 "parser.y" /* yacc.c:1646  */
    {std::cout<<"term <- primary"<<std::endl;}
#line 1911 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 284 "parser.y" /* yacc.c:1646  */
    {
						if(((yyvsp[-2].node)->sym!=NULL) && ((yyvsp[-2].node)->sym->type == LIBRARY_FUNC || (yyvsp[-2].node)->sym->type == PROGRAM_FUNC)){
								buffer << "Line: "<< yylineno <<"\n\t";
								buffer<<"Invalid use of assignment operator = : " << (yyvsp[-2].node)->sym->name << " refers to a function type and cannot be assigned a value.\n";
						}else if((yyvsp[-2].node)->sym==NULL){
								buffer<<"Line: " <<yylineno<< ":\n\t";
								buffer<<"undeclared variable."<<std::endl;
						}

						emit(assign,(yyvsp[0].node),(expr*)0,(yyvsp[-2].node),0,yylineno);

						(yyval.node) = newexpr(assignexpr_e);
						(yyval.node)->sym = newtemp();
						emit(assign,(yyvsp[-2].node),(expr*)0,(yyval.node),0,yylineno);

						std::cout<<"assignexpr <- lvalue = expr"<<std::endl;
					}
#line 1933 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 303 "parser.y" /* yacc.c:1646  */
    {std::cout<<"primary <- lvalue"<<std::endl;}
#line 1939 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 304 "parser.y" /* yacc.c:1646  */
    {std::cout<<"primary <- call"<<std::endl;}
#line 1945 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 305 "parser.y" /* yacc.c:1646  */
    {std::cout<<"primary <- objectdef"<<std::endl;}
#line 1951 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 306 "parser.y" /* yacc.c:1646  */
    {std::cout<<"primary <- ( funcdef )"<<std::endl;}
#line 1957 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 307 "parser.y" /* yacc.c:1646  */
    {std::cout<<"primary <- const"<<std::endl;}
#line 1963 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 310 "parser.y" /* yacc.c:1646  */
    {
					Symbol* tmp;
					Symbol* newSym=construct_Symbol((yyvsp[0].strVal),((currScope) ? 1 : 0),yylineno,currScope,currRange,currScopeSpace(),currScopeOffset());

					tmp = SymTable.lookup((yyvsp[0].strVal),currScope,1);
					if(tmp==NULL || (tmp->hidden && tmp->scope==currScope)){
						tmp=SymTable.insert(newSym);
						incCurrScopeOffset();
					}else{
						if(!((tmp->range==currRange || tmp->range==currRange-1) || tmp->scope==0
							|| tmp->type==LIBRARY_FUNC || tmp->type==PROGRAM_FUNC)){
								buffer << "Line: "<< yylineno <<"\t"<<tmp->range<<"\t"<<currRange<<" \n\t";
								buffer<<"ID:Cannot access "<<(yyvsp[0].strVal)<<" already defined here: "<< tmp->lineno <<std::endl;
						}
					}

					(yyval.node)=lvalue_expr(tmp);
					std::cout<<"lvalue <- ID"<<std::endl;
				}
#line 1987 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 329 "parser.y" /* yacc.c:1646  */
    {
					Symbol* tmp;
					Symbol* newSym=construct_Symbol((yyvsp[0].strVal),(currScope) ? 1 : 0,yylineno,currScope,currRange,currScopeSpace(),currScopeOffset());
					tmp = SymTable.lookup((yyvsp[0].strVal),currScope,1);

					if(tmp==NULL){
						tmp=SymTable.insert(newSym);
						incCurrScopeOffset();
					}else{
						if((tmp->scope!=currScope || tmp->hidden)  && (tmp->type!=LIBRARY_FUNC)){
							tmp=SymTable.insert(newSym);
							incCurrScopeOffset();
						}else if(tmp->type==LIBRARY_FUNC){
							buffer << "Line " << yylineno << ":\n\t"<<(yyvsp[0].strVal)<<" is a Library Function.\n\t";
							buffer<<"Library functions cannot be shadowed:"<<(yyvsp[0].strVal)<<" already defined here:" << tmp->lineno<<std::endl;
						}
					}

					(yyval.node)=lvalue_expr(tmp);

					std::cout<<"lvalue <- LOCAL ID"<<std::endl;
				}
#line 2014 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 351 "parser.y" /* yacc.c:1646  */
    {
					Symbol* tmp;
					tmp=SymTable.lookup((yyvsp[0].strVal),0);

					if(tmp==NULL){
						buffer << "Line: "<< yylineno <<" \n\t";
						buffer<<"Could not find Global variable:  \""<<(yyvsp[0].strVal)<<"\" ,is not defined"<<std::endl;
					}

					(yyval.node)=lvalue_expr(tmp);
					std::cout<<"lvalue <- SCOPE ID"<<std::endl;
				}
#line 2031 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 363 "parser.y" /* yacc.c:1646  */
    {(yyval.node)->sym->type=LOCAL_VAR;std::cout<<"lvalue <- member"<<std::endl;}
#line 2037 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 366 "parser.y" /* yacc.c:1646  */
    {std::cout<<"member <- lvalue.ID"<<std::endl;}
#line 2043 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 367 "parser.y" /* yacc.c:1646  */
    {std::cout<<"member <- lvalue [expr]"<<std::endl;}
#line 2049 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 368 "parser.y" /* yacc.c:1646  */
    {std::cout<<"member <- call.ID"<<std::endl;}
#line 2055 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 369 "parser.y" /* yacc.c:1646  */
    {std::cout<<"member <- call[expr]"<<std::endl;}
#line 2061 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 372 "parser.y" /* yacc.c:1646  */
    {std::cout<<"call <- call ( elist )"<<std::endl;}
#line 2067 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 373 "parser.y" /* yacc.c:1646  */
    {std::cout<<"call <- lvalue callsuffix"<<std::endl;}
#line 2073 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 374 "parser.y" /* yacc.c:1646  */
    {std::cout<<"call <- (funcdef) (elist)"<<std::endl;}
#line 2079 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 377 "parser.y" /* yacc.c:1646  */
    {std::cout<<"callsuffix <- normcall"<<std::endl;}
#line 2085 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 378 "parser.y" /* yacc.c:1646  */
    {std::cout<<"callsuffix <- methodcall"<<std::endl;}
#line 2091 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 382 "parser.y" /* yacc.c:1646  */
    {std::cout<<"normcall <- ( elist )"<<std::endl;}
#line 2097 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 385 "parser.y" /* yacc.c:1646  */
    {std::cout<<"methodcall <- ..ID(elist)"<<std::endl;}
#line 2103 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 388 "parser.y" /* yacc.c:1646  */
    {std::cout<<"elist <- elist exprs"<<std::endl;}
#line 2109 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 389 "parser.y" /* yacc.c:1646  */
    {std::cout<<"elist <- expr"<<std::endl;}
#line 2115 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 393 "parser.y" /* yacc.c:1646  */
    {std::cout<<"exprs <- , expr"<<std::endl;}
#line 2121 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 396 "parser.y" /* yacc.c:1646  */
    {std::cout<<"objectdef <- [ objectdefs ]"<<std::endl;}
#line 2127 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 399 "parser.y" /* yacc.c:1646  */
    {std::cout<<"objectdefs <- elist"<<std::endl;}
#line 2133 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 400 "parser.y" /* yacc.c:1646  */
    {std::cout<<"objectdefs <- indexed"<<std::endl;}
#line 2139 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 404 "parser.y" /* yacc.c:1646  */
    {std::cout<<"indexed <- indexed indexeds"<<std::endl;}
#line 2145 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 405 "parser.y" /* yacc.c:1646  */
    {std::cout<<"indexed <- indexedelem"<<std::endl;}
#line 2151 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 408 "parser.y" /* yacc.c:1646  */
    {std::cout<<"indexeds <- , indexedelem"<<std::endl;}
#line 2157 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 412 "parser.y" /* yacc.c:1646  */
    {std::cout<<"indexedelem <- { expr : expr }"<<std::endl;}
#line 2163 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 415 "parser.y" /* yacc.c:1646  */
    {currScope++;}
#line 2169 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 417 "parser.y" /* yacc.c:1646  */
    {
				SymTable.hideScope(currScope);
				currScope--;
				std::cout<<"block <- { stmts }"<<std::endl;
			}
#line 2179 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 422 "parser.y" /* yacc.c:1646  */
    {currScope++;}
#line 2185 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 423 "parser.y" /* yacc.c:1646  */
    {
				SymTable.hideScope(currScope);
				currScope--;
				std::cout<<"block <- { }"<<std::endl;
			}
#line 2195 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 432 "parser.y" /* yacc.c:1646  */
    {(yyval.strVal)=(yyvsp[0].strVal);}
#line 2201 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 433 "parser.y" /* yacc.c:1646  */
    {
					std::string funcName = "$f";
					funcName += std::to_string(suffixNum++);
					(yyval.strVal)=const_cast<char*>(funcName.c_str());
				}
#line 2211 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 440 "parser.y" /* yacc.c:1646  */
    {
								Symbol* tmp;
								Symbol* newSym=construct_Symbol((yyvsp[0].strVal),4,yylineno,currScope,currRange,currScopeSpace(),currOffset);
								tmp = SymTable.lookup((yyvsp[0].strVal),currScope);

								if(tmp==NULL){
									if((tmp = SymTable.lookup((yyvsp[0].strVal),0))!=NULL && tmp->type == LIBRARY_FUNC){
										buffer << "Line: "<< yylineno <<" \n\t";
										buffer<<"Invalid Name:  \""<<(yyvsp[0].strVal)<<"\". Reserved keyword for a library function"<<std::endl;
									}else{
										tmp=SymTable.insert(newSym);
									}
								}
								else{
									buffer << "Line: "<< yylineno <<" \n\t";
									if(tmp->type == LIBRARY_FUNC){
										buffer<<"Invalid Name:  \""<<(yyvsp[0].strVal)<<"\". Reserved keyword for a library function"<<std::endl;
									}else if(tmp->type == PROGRAM_FUNC){
										buffer<<"Function redefinition. "<<(yyvsp[0].strVal)<<". already defined here: "<< tmp->lineno<<std::endl;
									}else{
										buffer<<"Cannot access "<<(yyvsp[0].strVal)<<". already defined here: "<< tmp->lineno<<std::endl;
									}
								}


								(yyval.sym)=tmp;
								labelStack.push(currQuad);
								emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
								(yyval.sym)->function.iaddress = nextquadlabel();
								emit(funcstart,(expr*)0,(expr*)0,lvalue_expr((yyval.sym)),0,yylineno);
								currScope++;
								currRange++;
								offsetStack.push(formalArgOffset);
								offsetStack.push(functionLocalOffset);
								formalArgOffset = 0;
							}
#line 2252 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 477 "parser.y" /* yacc.c:1646  */
    {currScope--;currRange++;functionLocalOffset=0;}
#line 2258 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 480 "parser.y" /* yacc.c:1646  */
    {
						currRange-=2;

					}
#line 2267 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 486 "parser.y" /* yacc.c:1646  */
    {
								(yyvsp[-2].sym)->function.totallocals = functionLocalOffset;
								(yyvsp[-2].sym)->function.totalformals = formalArgOffset;
								functionLocalOffset = offsetStack.top();
								offsetStack.pop();
								formalArgOffset = offsetStack.top();
								offsetStack.pop();

								emit(funcend,(expr*)0,(expr*)0,lvalue_expr((yyvsp[-2].sym)),0,yylineno);
								unsigned labels=labelStack.top();
								labelStack.pop();
								patchlabel(labels,currQuad);
								std::cout<<"funcdef <- FUNCTION (idlist) block"<<std::endl;
							}
#line 2286 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 502 "parser.y" /* yacc.c:1646  */
    {
					expr* e =new expr();
					e->type=constnum_e;
					e->numConst=(yyvsp[0].intVal);
					(yyval.node)=e;
					std::cout<<"const <- INTCONST"<<std::endl;
				}
#line 2298 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 509 "parser.y" /* yacc.c:1646  */
    {
							expr* e =new expr();
							e->type=constnum_e;
							e->numConst=(yyvsp[0].realVal);
							(yyval.node)=e;
							std::cout<<"const <- REALCONST"<<std::endl;
				}
#line 2310 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 516 "parser.y" /* yacc.c:1646  */
    {std::cout<<"const <- STRING"<<std::endl;}
#line 2316 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 517 "parser.y" /* yacc.c:1646  */
    {std::cout<<"const <- NIL"<<std::endl;}
#line 2322 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 518 "parser.y" /* yacc.c:1646  */
    {std::cout<<"const <- TRUE"<<std::endl;}
#line 2328 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 519 "parser.y" /* yacc.c:1646  */
    {std::cout<<"const <- FALSE"<<std::endl;}
#line 2334 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 522 "parser.y" /* yacc.c:1646  */
    {std::cout<<"idlist <- idlist idlists"<<std::endl;}
#line 2340 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 523 "parser.y" /* yacc.c:1646  */
    {
					Symbol* tmp;
					Symbol* newSym=construct_Symbol((yyvsp[0].strVal),2,yylineno,currScope,currRange,currScopeSpace(),currScopeOffset());

					tmp = SymTable.lookup((yyvsp[0].strVal),currScope,1);

					if(tmp==NULL){
						tmp=SymTable.insert(newSym);
						incCurrScopeOffset();
					}else{
						if(tmp->type == LIBRARY_FUNC){
							buffer << "Line " << yylineno << ":\n\t"<<(yyvsp[0].strVal)<< " is a Library Function.\n";
						}else if(!tmp->hidden && tmp->scope==currScope){
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Variable: "<<(yyvsp[0].strVal)<<" is already defined at line: "<< tmp->lineno <<std::endl;
						}else{
							tmp=SymTable.insert(newSym);
							incCurrScopeOffset();
						}

                    			}

					std::cout<<"idlist <- ID "<<std::endl;
				}
#line 2369 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 547 "parser.y" /* yacc.c:1646  */
    {std::cout<<"idlist <- (empty)"<<std::endl;}
#line 2375 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 550 "parser.y" /* yacc.c:1646  */
    {
					Symbol* tmp;
					Symbol* newSym=construct_Symbol((yyvsp[0].strVal),2,yylineno,currScope,currRange,currScopeSpace(),currScopeOffset());
					tmp = SymTable.lookup((yyvsp[0].strVal),currScope,1);

					if(tmp==NULL){
						tmp=SymTable.insert(newSym);
						incCurrScopeOffset();
					}else{
						if(tmp->type == LIBRARY_FUNC){
							buffer << "Line " << yylineno << ":\n\t"<<(yyvsp[0].strVal)<< " is a Library Function.\n";
						}else if(tmp->hidden){
							tmp=SymTable.insert(newSym);
							incCurrScopeOffset();
						}else{
							buffer << "Line: "<< yylineno <<" \n\t";
							buffer<<"Variable: "<<(yyvsp[0].strVal)<<" is already defined at line: "<< tmp->lineno <<std::endl;
						}
					}

					std::cout<<"idlists <- , ID"<<std::endl;
				}
#line 2402 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 574 "parser.y" /* yacc.c:1646  */
    {std::cout<<"ifstmt <- ifstmt ELSE stmt"<<std::endl;}
#line 2408 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 575 "parser.y" /* yacc.c:1646  */
    {std::cout<<"ifstmt <- IF ( expr ) stmt"<<std::endl;}
#line 2414 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 578 "parser.y" /* yacc.c:1646  */
    {std::cout<<"whilestmt <- WHILE ( expr ) stmt"<<std::endl;}
#line 2420 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 581 "parser.y" /* yacc.c:1646  */
    {(yyval.intVal)=currQuad;
	emit(jump,(expr*)0,(expr*)0,(expr*)0,0,yylineno);
	}
#line 2428 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 586 "parser.y" /* yacc.c:1646  */
    {(yyval.intVal)=currQuad;}
#line 2434 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 589 "parser.y" /* yacc.c:1646  */
    {
			struct forPrefix* e = (struct forPrefix*)malloc(sizeof(struct forPrefix));
			e->test = (yyvsp[-2].intVal);
			e->enter = nextquadlabel();
			(yyval.prefix) = e;
			emit(if_eq,(yyvsp[-1].node),newexpr_constbool_e(true),(expr*)0,0,yylineno);
			}
#line 2446 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 598 "parser.y" /* yacc.c:1646  */
    {
		patchlabel((yyvsp[-6].prefix)->enter ,(yyvsp[-2].intVal)+1);
		patchlabel((yyvsp[-5].intVal),nextquadlabel());
		patchlabel((yyvsp[-2].intVal),(yyvsp[-6].prefix)->test);
		patchlabel((yyvsp[0].intVal),(yyvsp[-5].intVal)+1);

		std::cout<<"forstmt <- FOR ( elist ; expr ; elist ) stmt"<<std::endl;
	}
#line 2459 "parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 609 "parser.y" /* yacc.c:1646  */
    {std::cout<<"returnstmt <- RETURN expr ;"<<std::endl;}
#line 2465 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 610 "parser.y" /* yacc.c:1646  */
    {std::cout<<"returnstmt <- RETURN ;"<<std::endl;}
#line 2471 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2475 "parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 612 "parser.y" /* yacc.c:1906  */


int yyerror(const char* yaccProvidedMessage){
	fprintf(stderr,"%s: at line %d,before token: %s\n",yaccProvidedMessage,yylineno,yytext);
	fprintf(stderr,"INPUT NOT VALID\n");
}

int main(int argc,char** argv){
	if(argc > 1){
		if(!(yyin = fopen(argv[1],"r"))){
			fprintf(stderr,"Cannot read file: %s\n",argv[1]);
			return 1;
		}
	}else
		yyin = stdin;

	buffer.open("alpha_compiler_Errors.txt",std::ios::out);

	SymTable.insert(construct_Symbol("print",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("input",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("objectmemberkeys",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("objecttotalmembers",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("objectcopy",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("totalarguments",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("argument",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("typeof",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("strtonum",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("sqrt",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("cos",3,0,0,0,programVar,0));
	SymTable.insert(construct_Symbol("sin",3,0,0,0,programVar,0));

	yyparse();
	buffer.close();

	std::cout<<SymTable.allscopestoString()<<std::endl;

	std::ifstream errors("alpha_compiler_Errors.txt");
	std::string line;
	if(errors.is_open()){
		while(getline(errors,line)){
			std::cout<<line<<std::endl;
		}
	}
	remove("alpha_compiler_Errors.txt");


	std::cout<<quads_toString()<<std::endl;
return 0;
}
