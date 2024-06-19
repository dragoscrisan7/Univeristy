%start program
%token IDENTIFIER MORE ALBA_NEAGRA VORBE DINAIA DITOATE
%token SCAN WRITE WHILE VAR WHEN THEN CHOOSE NR COD ONWARD AT_EASE
%token '<' '{' '}' '~' ':' CASE TRUE FALSE OTHERWISE DEFAULT
%token '+' '-' '*' '%' '/' '->' '<' '>' '<=' '=' '>=' '!=' '$'
%token '(' ')' '.' SPACE
%token LETTER DIGIT UNDERSCORE
%token STRING CHAR

%%

program : COD decllist '~' cmpdstmt '.' AT_EASE

decllist : declaration
         | declaration '~' decllist

declaration : IDENTIFIER '$' type

type : type1
     | arraydecl

type1 : ALBA_NEAGRA
      | VORBE
      | DINAIA
      | DITOATE

arraydecl : MORE '[' NR ']' 'OF' type1

cmpdstmt : ONWARD stmtlist AT_EASE

stmtlist : stmt
         | stmt '~' stmtlist

stmt : simplstmt
     | structstmt

simplstmt : assignstmt
          | iostmt

assignstmt : IDENTIFIER '->' expression

expression : expression '+' term
           | term

term : term '*' factor
     | factor

factor : '(' expression ')'
       | IDENTIFIER

iostmt : SCAN '(' IDENTIFIER ')'
       | WRITE '(' IDENTIFIER ')'

structstmt : cmpdstmt
           | ifstmt
           | whilestmt
           | choosestmt

ifstmt : WHEN condition THEN '<{' stmt '}>' OTHERWISE '<{' stmt '}>' %prec OTHERWISE
       | WHEN condition THEN '<{' stmt '}>'

whilestmt : WHILE condition PERFORM '<{' stmt '}>'

choosestmt : CHOOSE '(' expression ')' '<{' caselist '}>'

caselist : case caselist
         | defaultstmt

case : CASE constant ':' stmtlist

defaultstmt : DEFAULT ':' stmtlist

condition : expression '<' expression
          | expression '<=' expression
          | expression '=' expression
          | expression '<>' expression
          | expression '>=' expression
          | expression '>' expression

constant : STRING
         | CHAR
         | NR

%%

%token <sval> IDENTIFIER STRING CHAR NR

%%
