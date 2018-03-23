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

	#include <stdio.h>
	#include <iostream>
	#include <string>
	int yyerror(const char* yaccProvidedMessage);
	int yylex(void);

	extern int yylineno;
	extern char* yytext;
	extern FILE* yyin;
 

#line 79 "parser.cpp" /* yacc.c:339  */

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
#line 21 "parser.y" /* yacc.c:355  */

	int intVal;
	char* strVal;
	double realVal;

#line 185 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 202 "parser.cpp" /* yacc.c:358  */

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
#define YYFINAL  71
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   674

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  175

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
static const yytype_uint8 yyrline[] =
{
       0,    42,    42,    43,    46,    47,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    62,    63,    64,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    82,    83,    84,    85,    86,    87,    88,    89,
      92,    95,    96,    97,    98,    99,   102,   103,   104,   105,
     108,   109,   110,   111,   114,   115,   116,   119,   120,   124,
     127,   130,   131,   134,   137,   138,   141,   142,   146,   147,
     150,   154,   157,   158,   161,   162,   165,   166,   167,   168,
     169,   170,   173,   174,   175,   178,   181,   182,   185,   188,
     191,   192
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
  "objectdefs", "indexed", "indexeds", "indexedelem", "block", "funcdef",
  "const", "idlist", "idlists", "ifstmt", "whilestmt", "forstmt",
  "returnstmt", YY_NULLPTR
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

#define YYPACT_NINF -101

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-101)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     196,  -101,  -101,  -101,  -101,   -34,   -31,   -23,     0,   284,
      -1,    14,  -101,    76,   366,  -101,  -101,    79,    38,   366,
      38,   240,   326,  -101,    11,    83,   196,  -101,   410,  -101,
    -101,  -101,    96,  -101,   -33,  -101,  -101,  -101,  -101,    81,
    -101,  -101,  -101,   366,   366,   366,    59,   102,  -101,   432,
    -101,  -101,  -101,  -101,  -101,   108,    53,   -33,  -101,    53,
    -101,   366,   579,    86,    85,    97,  -101,   476,    98,  -101,
     150,  -101,  -101,   366,   366,   366,   366,   366,   366,   366,
     366,   366,   366,   366,   366,   366,  -101,  -101,   142,  -101,
     366,  -101,   143,   366,   366,  -101,  -101,  -101,   144,   366,
     366,   196,   497,   518,    18,   102,  -101,   -15,  -101,   105,
     388,   366,  -101,  -101,   104,  -101,  -101,   109,  -101,   613,
     599,   627,   627,   638,   638,   638,   638,    52,    52,  -101,
    -101,  -101,   110,   579,  -101,   539,    -5,  -101,   559,     4,
    -101,   196,   196,   366,    51,   121,   166,  -101,   109,   366,
     579,  -101,   366,   366,  -101,  -101,  -101,  -101,  -101,  -101,
     454,   121,  -101,  -101,    80,    55,    77,   366,  -101,  -101,
    -101,  -101,    84,   196,  -101
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    46,    76,    78,    77,     0,     0,     0,     0,     0,
       0,     0,    79,     0,     0,    80,    81,     0,     0,     0,
       0,     0,     0,    15,     0,     0,     2,     5,     0,    18,
      16,    39,    41,    49,    42,    43,    13,    14,    45,     7,
       8,     9,    10,     0,     0,     0,     0,    84,    91,     0,
      11,    12,    47,    34,    48,     0,    37,     0,    33,    35,
      65,     0,    62,    66,     0,    67,    69,     0,     0,    73,
       0,     1,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,    17,     0,    38,
       0,    36,     0,     0,     0,    55,    57,    58,     0,     0,
       0,     0,     0,     0,     0,    84,    83,     0,    90,     0,
       0,     0,    61,    64,     0,    68,    32,    44,    72,    29,
      30,    28,    31,    25,    27,    24,    26,    19,    20,    21,
      22,    23,     0,    40,    50,     0,     0,    52,     0,     0,
      86,     0,     0,     0,     0,     0,     0,    82,     0,     0,
      63,    70,     0,     0,    51,    59,    53,    54,    87,    88,
       0,     0,    75,    85,     0,     0,     0,     0,    74,    71,
      56,    60,     0,     0,    89
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -101,  -101,   149,   -24,    -9,  -101,  -101,  -101,  -101,   112,
    -101,   119,  -101,  -101,  -101,   -44,  -101,  -101,  -101,  -101,
    -101,    60,  -100,   -18,  -101,    70,  -101,  -101,  -101,  -101,
    -101
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    87,    29,    30,    31,    32,
      33,    34,    95,    96,    97,    63,   112,    35,    64,    65,
     115,    66,    36,    37,    38,   107,   147,    39,    40,    41,
      42
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,   104,    72,    46,    68,    53,    98,    99,    43,   100,
      58,    44,    62,    67,     1,     2,     3,     4,     5,    45,
       6,     7,     8,     9,    10,    11,    12,    13,   145,    14,
     146,    15,    16,    17,   102,   103,    62,   109,   155,    18,
     111,     1,    47,    50,    19,   162,    72,   157,    20,   111,
     136,    21,   110,    22,    13,    23,   139,    24,    51,    69,
      17,   168,   143,   111,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   140,    88,    52,
      55,   133,    54,    71,   135,    62,    83,    84,    85,   101,
     138,    62,    92,    93,   161,    94,   146,    73,   170,    74,
     111,   105,   150,    75,    76,   106,    77,    78,   165,   166,
      79,    80,    81,    82,    83,    84,    85,   158,   159,     8,
     171,    88,   111,   172,    89,    90,   113,   173,   169,   111,
      56,   111,    59,    91,   160,    92,    93,    57,    94,    57,
     164,   117,   114,    62,    62,   132,   134,   137,   148,   174,
      61,   152,   153,     1,     2,     3,     4,     5,    62,     6,
       7,     8,     9,    10,    11,    12,    13,    24,    14,   163,
      15,    16,    17,    70,   151,   144,     0,     0,    18,     0,
       0,     0,     0,    19,     0,     0,     0,    20,     0,     0,
      21,     0,    22,     0,    23,     0,    24,     0,   118,     1,
       2,     3,     4,     5,     0,     6,     7,     8,     9,    10,
      11,    12,    13,     0,    14,     0,    15,    16,    17,     0,
       0,     0,     0,     0,    18,     0,     0,     0,     0,    19,
       0,     0,     0,    20,     0,     0,    21,     0,    22,     0,
      23,     0,    24,     1,     2,     3,     4,     0,     0,     0,
       0,     0,     0,     0,     0,    12,    13,     0,    14,     0,
      15,    16,    17,     0,     0,     0,     0,     0,    18,     0,
       0,     0,     0,    19,     0,     0,     0,    20,     0,     0,
      21,    60,    22,     0,     0,     0,    61,     1,     2,     3,
       4,     0,     0,     0,     0,     0,     0,     0,     0,    12,
      13,     0,    14,     0,    15,    16,    17,     0,     0,     0,
       0,     0,    18,     0,     0,     0,     0,    19,     0,     0,
       0,    20,     0,     0,    21,     0,    22,     0,    48,     1,
       2,     3,     4,     0,     0,     0,     0,     8,     0,     0,
       0,    12,    13,     0,    14,     0,    15,    16,    17,     0,
       0,     0,     0,     0,    18,     0,     0,     0,     0,    19,
       0,     0,     0,    20,     0,     0,    21,     0,    22,     1,
       2,     3,     4,     0,     0,     0,     0,     0,     0,     0,
       0,    12,    13,     0,    14,     0,    15,    16,    17,     0,
       0,     0,     0,     0,    18,     0,     0,     0,     0,    19,
       0,     0,     0,    20,     0,    73,    21,    74,    22,     0,
       0,    75,    76,     0,    77,    78,     0,     0,    79,    80,
      81,    82,    83,    84,    85,     0,     0,    73,     0,    74,
       0,     0,     0,    75,    76,   149,    77,    78,     0,     0,
      79,    80,    81,    82,    83,    84,    85,     0,     0,    73,
       0,    74,     0,     0,    86,    75,    76,     0,    77,    78,
       0,     0,    79,    80,    81,    82,    83,    84,    85,     0,
       0,    73,     0,    74,     0,     0,   108,    75,    76,     0,
      77,    78,     0,     0,    79,    80,    81,    82,    83,    84,
      85,     0,     0,    73,     0,    74,     0,     0,   167,    75,
      76,     0,    77,    78,     0,     0,    79,    80,    81,    82,
      83,    84,    85,     0,    73,     0,    74,     0,     0,   116,
      75,    76,     0,    77,    78,     0,     0,    79,    80,    81,
      82,    83,    84,    85,     0,    73,     0,    74,     0,     0,
     141,    75,    76,     0,    77,    78,     0,     0,    79,    80,
      81,    82,    83,    84,    85,     0,    73,     0,    74,     0,
       0,   142,    75,    76,     0,    77,    78,     0,     0,    79,
      80,    81,    82,    83,    84,    85,    73,     0,    74,     0,
     154,     0,    75,    76,     0,    77,    78,     0,     0,    79,
      80,    81,    82,    83,    84,    85,    73,     0,    74,     0,
     156,     0,    75,    76,     0,    77,    78,     0,     0,    79,
      80,    81,    82,    83,    84,    85,    73,     0,     0,     0,
       0,     0,    75,    76,     0,    77,    78,     0,     0,    79,
      80,    81,    82,    83,    84,    85,    75,    76,     0,    77,
      78,     0,     0,    79,    80,    81,    82,    83,    84,    85,
      -1,    -1,     0,    77,    78,     0,     0,    79,    80,    81,
      82,    83,    84,    85,    -1,    -1,     0,     0,    -1,    -1,
      81,    82,    83,    84,    85
};

static const yytype_int16 yycheck[] =
{
       9,    45,    26,     3,    22,    14,    39,    40,    42,    42,
      19,    42,    21,    22,     3,     4,     5,     6,     7,    42,
       9,    10,    11,    12,    13,    14,    15,    16,    43,    18,
      45,    20,    21,    22,    43,    44,    45,    55,    43,    28,
      45,     3,    42,    44,    33,   145,    70,    43,    37,    45,
      94,    40,    61,    42,    16,    44,   100,    46,    44,    48,
      22,   161,    44,    45,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,   101,    25,     3,
      42,    90,     3,     0,    93,    94,    34,    35,    36,     8,
      99,   100,    39,    40,    43,    42,    45,    17,    43,    19,
      45,    42,   111,    23,    24,     3,    26,    27,   152,   153,
      30,    31,    32,    33,    34,    35,    36,   141,   142,    11,
      43,    25,    45,   167,    28,    29,    41,    43,    48,    45,
      18,    45,    20,    37,   143,    39,    40,    18,    42,    20,
     149,    43,    45,   152,   153,     3,     3,     3,    43,   173,
      46,    42,    42,     3,     4,     5,     6,     7,   167,     9,
      10,    11,    12,    13,    14,    15,    16,    46,    18,     3,
      20,    21,    22,    24,   114,   105,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    -1,    37,    -1,    -1,
      40,    -1,    42,    -1,    44,    -1,    46,    -1,    48,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    18,    -1,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    37,    -1,    -1,    40,    -1,    42,    -1,
      44,    -1,    46,     3,     4,     5,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    16,    -1,    18,    -1,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    -1,    37,    -1,    -1,
      40,    41,    42,    -1,    -1,    -1,    46,     3,     4,     5,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    -1,    18,    -1,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    33,    -1,    -1,
      -1,    37,    -1,    -1,    40,    -1,    42,    -1,    44,     3,
       4,     5,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    15,    16,    -1,    18,    -1,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    37,    -1,    -1,    40,    -1,    42,     3,
       4,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    16,    -1,    18,    -1,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    37,    -1,    17,    40,    19,    42,    -1,
      -1,    23,    24,    -1,    26,    27,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    17,    -1,    19,
      -1,    -1,    -1,    23,    24,    47,    26,    27,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    17,
      -1,    19,    -1,    -1,    44,    23,    24,    -1,    26,    27,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    17,    -1,    19,    -1,    -1,    44,    23,    24,    -1,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    17,    -1,    19,    -1,    -1,    44,    23,
      24,    -1,    26,    27,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    17,    -1,    19,    -1,    -1,    43,
      23,    24,    -1,    26,    27,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    17,    -1,    19,    -1,    -1,
      43,    23,    24,    -1,    26,    27,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    17,    -1,    19,    -1,
      -1,    43,    23,    24,    -1,    26,    27,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    17,    -1,    19,    -1,
      41,    -1,    23,    24,    -1,    26,    27,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    17,    -1,    19,    -1,
      41,    -1,    23,    24,    -1,    26,    27,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    17,    -1,    -1,    -1,
      -1,    -1,    23,    24,    -1,    26,    27,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    23,    24,    -1,    26,
      27,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      23,    24,    -1,    26,    27,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    26,    27,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      13,    14,    15,    16,    18,    20,    21,    22,    28,    33,
      37,    40,    42,    44,    46,    50,    51,    52,    53,    55,
      56,    57,    58,    59,    60,    66,    71,    72,    73,    76,
      77,    78,    79,    42,    42,    42,     3,    42,    44,    53,
      44,    44,     3,    53,     3,    42,    58,    60,    53,    58,
      41,    46,    53,    64,    67,    68,    70,    53,    72,    48,
      51,     0,    52,    17,    19,    23,    24,    26,    27,    30,
      31,    32,    33,    34,    35,    36,    44,    54,    25,    28,
      29,    37,    39,    40,    42,    61,    62,    63,    39,    40,
      42,     8,    53,    53,    64,    42,     3,    74,    44,    72,
      53,    45,    65,    41,    45,    69,    43,    43,    48,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,     3,    53,     3,    53,    64,     3,    53,    64,
      52,    43,    43,    44,    74,    43,    45,    75,    43,    47,
      53,    70,    42,    42,    41,    43,    41,    43,    52,    52,
      53,    43,    71,     3,    53,    64,    64,    44,    71,    48,
      43,    43,    64,    43,    52
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
      63,    64,    64,    65,    66,    66,    67,    67,    68,    68,
      69,    70,    71,    71,    72,    72,    73,    73,    73,    73,
      73,    73,    74,    74,    74,    75,    76,    76,    77,    78,
      79,    79
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
       5,     2,     1,     2,     3,     2,     1,     1,     2,     1,
       2,     5,     3,     2,     6,     5,     1,     1,     1,     1,
       1,     1,     2,     1,     0,     2,     3,     5,     5,     9,
       3,     2
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
#line 42 "parser.y" /* yacc.c:1646  */
    {std::cout<<"Program <- stmts"<<std::endl;}
#line 1502 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 43 "parser.y" /* yacc.c:1646  */
    {std::cout<<"Program <- (empty)"<<std::endl;}
#line 1508 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 46 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmts <- stmts stmt"<<std::endl;}
#line 1514 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 47 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmts <- stmt"<<std::endl;}
#line 1520 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 50 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- expr(;)"<<std::endl;}
#line 1526 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 51 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- ifstmt"<<std::endl;}
#line 1532 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 52 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- whilestmt"<<std::endl;}
#line 1538 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 53 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- forstmt"<<std::endl;}
#line 1544 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 54 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- returnstmt"<<std::endl;}
#line 1550 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 55 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- break(;)"<<std::endl;}
#line 1556 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 56 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- continue(;)"<<std::endl;}
#line 1562 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 57 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- block"<<std::endl;}
#line 1568 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 58 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- funcdef"<<std::endl;}
#line 1574 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 59 "parser.y" /* yacc.c:1646  */
    {std::cout<<"stmt <- semicolon(;)"<<std::endl;}
#line 1580 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 62 "parser.y" /* yacc.c:1646  */
    {std::cout<<"expr <- assignexpr"<<std::endl;}
#line 1586 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 63 "parser.y" /* yacc.c:1646  */
    {std::cout<<"expr <- expr op"<<std::endl;}
#line 1592 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 64 "parser.y" /* yacc.c:1646  */
    {std::cout<<"expr <- term"<<std::endl;}
#line 1598 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 67 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- + expr"<<std::endl;}
#line 1604 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 68 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- - expr"<<std::endl;}
#line 1610 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 69 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- * expr"<<std::endl;}
#line 1616 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 70 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- / expr"<<std::endl;}
#line 1622 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 71 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- % expr"<<std::endl;}
#line 1628 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 72 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- > expr"<<std::endl;}
#line 1634 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 73 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- >= expr"<<std::endl;}
#line 1640 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 74 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- < expr"<<std::endl;}
#line 1646 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 75 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- <= expr"<<std::endl;}
#line 1652 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 76 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- != expr"<<std::endl;}
#line 1658 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 77 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- && expr"<<std::endl;}
#line 1664 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 78 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- || expr"<<std::endl;}
#line 1670 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 79 "parser.y" /* yacc.c:1646  */
    {std::cout<<"op <- == expr"<<std::endl;}
#line 1676 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 82 "parser.y" /* yacc.c:1646  */
    {std::cout<<"term <- ( expr )"<<std::endl;}
#line 1682 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 83 "parser.y" /* yacc.c:1646  */
    {std::cout<<"term <- - expr (UMINUS)"<<std::endl;}
#line 1688 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 84 "parser.y" /* yacc.c:1646  */
    {std::cout<<"term <- ! expr"<<std::endl;}
#line 1694 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 85 "parser.y" /* yacc.c:1646  */
    {std::cout<<"term <- ++ lvalue"<<std::endl;}
#line 1700 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 86 "parser.y" /* yacc.c:1646  */
    {std::cout<<"term <- lvalue ++"<<std::endl;}
#line 1706 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 87 "parser.y" /* yacc.c:1646  */
    {std::cout<<"term <- -- lvalue"<<std::endl;}
#line 1712 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 88 "parser.y" /* yacc.c:1646  */
    {std::cout<<"term <- lvalue --"<<std::endl;}
#line 1718 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 89 "parser.y" /* yacc.c:1646  */
    {std::cout<<"term <- primary"<<std::endl;}
#line 1724 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 92 "parser.y" /* yacc.c:1646  */
    {std::cout<<"assignexpr <- lvalue = expr"<<std::endl;}
#line 1730 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 95 "parser.y" /* yacc.c:1646  */
    {std::cout<<"primary <- lvalue"<<std::endl;}
#line 1736 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 96 "parser.y" /* yacc.c:1646  */
    {std::cout<<"primary <- call"<<std::endl;}
#line 1742 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 97 "parser.y" /* yacc.c:1646  */
    {std::cout<<"primary <- objectdef"<<std::endl;}
#line 1748 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 98 "parser.y" /* yacc.c:1646  */
    {std::cout<<"primary <- ( funcdef )"<<std::endl;}
#line 1754 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 99 "parser.y" /* yacc.c:1646  */
    {std::cout<<"primary <- const"<<std::endl;}
#line 1760 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 102 "parser.y" /* yacc.c:1646  */
    {std::cout<<"lvalue <- ID"<<std::endl;}
#line 1766 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 103 "parser.y" /* yacc.c:1646  */
    {std::cout<<"lvalue <- LOCAL ID"<<std::endl;}
#line 1772 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 104 "parser.y" /* yacc.c:1646  */
    {std::cout<<"lvalue <- SCOPE ID"<<std::endl;}
#line 1778 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 105 "parser.y" /* yacc.c:1646  */
    {std::cout<<"lvalue <- member"<<std::endl;}
#line 1784 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 108 "parser.y" /* yacc.c:1646  */
    {std::cout<<"member <- lvalue.ID"<<std::endl;}
#line 1790 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 109 "parser.y" /* yacc.c:1646  */
    {std::cout<<"member <- lvalue [expr]"<<std::endl;}
#line 1796 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 110 "parser.y" /* yacc.c:1646  */
    {std::cout<<"member <- call.ID"<<std::endl;}
#line 1802 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 111 "parser.y" /* yacc.c:1646  */
    {std::cout<<"member <- call[ID]"<<std::endl;}
#line 1808 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 114 "parser.y" /* yacc.c:1646  */
    {std::cout<<"call <- call ( elist )"<<std::endl;}
#line 1814 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 115 "parser.y" /* yacc.c:1646  */
    {std::cout<<"call <- lvalue callsuffix"<<std::endl;}
#line 1820 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 116 "parser.y" /* yacc.c:1646  */
    {std::cout<<"call <- (funcdef) (elist)"<<std::endl;}
#line 1826 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 119 "parser.y" /* yacc.c:1646  */
    {std::cout<<"callsuffix <- normcall"<<std::endl;}
#line 1832 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 120 "parser.y" /* yacc.c:1646  */
    {std::cout<<"callsuffix <- methodcall"<<std::endl;}
#line 1838 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 124 "parser.y" /* yacc.c:1646  */
    {std::cout<<"normcall <- ( elist )"<<std::endl;}
#line 1844 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 127 "parser.y" /* yacc.c:1646  */
    {std::cout<<"methodcall <- ..ID(elist)"<<std::endl;}
#line 1850 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 130 "parser.y" /* yacc.c:1646  */
    {std::cout<<"elist <- elist exprs"<<std::endl;}
#line 1856 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 131 "parser.y" /* yacc.c:1646  */
    {std::cout<<"elist <- expr"<<std::endl;}
#line 1862 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 134 "parser.y" /* yacc.c:1646  */
    {std::cout<<"exprs <- , expr"<<std::endl;}
#line 1868 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 137 "parser.y" /* yacc.c:1646  */
    {std::cout<<"objectdef <- [ objectdefs ]"<<std::endl;}
#line 1874 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 138 "parser.y" /* yacc.c:1646  */
    {std::cout<<"objectdef <- [ ]"<<std::endl;}
#line 1880 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 141 "parser.y" /* yacc.c:1646  */
    {std::cout<<"objectdefs <- elist"<<std::endl;}
#line 1886 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 142 "parser.y" /* yacc.c:1646  */
    {std::cout<<"objectdefs <- indexed"<<std::endl;}
#line 1892 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 146 "parser.y" /* yacc.c:1646  */
    {std::cout<<"indexed <- indexed indexeds"<<std::endl;}
#line 1898 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 147 "parser.y" /* yacc.c:1646  */
    {std::cout<<"indexed <- indexedelem"<<std::endl;}
#line 1904 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 150 "parser.y" /* yacc.c:1646  */
    {std::cout<<"indexeds <- , indexedelem"<<std::endl;}
#line 1910 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 154 "parser.y" /* yacc.c:1646  */
    {std::cout<<"indexedelem <- { expr : expr }"<<std::endl;}
#line 1916 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 157 "parser.y" /* yacc.c:1646  */
    {std::cout<<"block <- { stmts }"<<std::endl;}
#line 1922 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 158 "parser.y" /* yacc.c:1646  */
    {std::cout<<"block <- { }"<<std::endl;}
#line 1928 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 161 "parser.y" /* yacc.c:1646  */
    {std::cout<<"funcdef <- FUNCTION ID (idlist) block"<<std::endl;}
#line 1934 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 162 "parser.y" /* yacc.c:1646  */
    {std::cout<<"funcdef <- FUNCTION (idlist) block"<<std::endl;}
#line 1940 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 165 "parser.y" /* yacc.c:1646  */
    {std::cout<<"const <- INTCONST"<<std::endl;}
#line 1946 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 166 "parser.y" /* yacc.c:1646  */
    {std::cout<<"const <- REALCONST"<<std::endl;}
#line 1952 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 167 "parser.y" /* yacc.c:1646  */
    {std::cout<<"const <- STRING"<<std::endl;}
#line 1958 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 168 "parser.y" /* yacc.c:1646  */
    {std::cout<<"const <- NIL"<<std::endl;}
#line 1964 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 169 "parser.y" /* yacc.c:1646  */
    {std::cout<<"const <- TRUE"<<std::endl;}
#line 1970 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 170 "parser.y" /* yacc.c:1646  */
    {std::cout<<"const <- FALSE"<<std::endl;}
#line 1976 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 173 "parser.y" /* yacc.c:1646  */
    {std::cout<<"idlist <- idlist idlists"<<std::endl;}
#line 1982 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 174 "parser.y" /* yacc.c:1646  */
    {std::cout<<"idlist <- (empty)"<<std::endl;}
#line 1988 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 178 "parser.y" /* yacc.c:1646  */
    {std::cout<<"idlists <- , ID"<<std::endl;}
#line 1994 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 181 "parser.y" /* yacc.c:1646  */
    {std::cout<<"ifstmt <- ifstmt ELSE stmt"<<std::endl;}
#line 2000 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 182 "parser.y" /* yacc.c:1646  */
    {std::cout<<"ifstmt <- IF ( expr ) stmt"<<std::endl;}
#line 2006 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 185 "parser.y" /* yacc.c:1646  */
    {std::cout<<"whilestmt <- WHILE ( expr ) stmt"<<std::endl;}
#line 2012 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 188 "parser.y" /* yacc.c:1646  */
    {std::cout<<"forstmt <- FOR ( elist ; expr ; elist ) stmt"<<std::endl;}
#line 2018 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 191 "parser.y" /* yacc.c:1646  */
    {std::cout<<"returnstmt <- RETURN expr ;"<<std::endl;}
#line 2024 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 192 "parser.y" /* yacc.c:1646  */
    {std::cout<<"returnstmt <- RETURN ;"<<std::endl;}
#line 2030 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2034 "parser.cpp" /* yacc.c:1646  */
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
#line 194 "parser.y" /* yacc.c:1906  */


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



yyparse();
return 0;
}
