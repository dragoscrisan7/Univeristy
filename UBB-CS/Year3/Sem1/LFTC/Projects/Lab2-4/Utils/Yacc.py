import ply.yacc as yacc
from Lexer import MyLexer

class YaccParser:
    tokens = MyLexer().tokens

    def p_program(self, p):
        """program : COD decllist TILDA cmpdstmt DOT"""
        # Define the action when parsing a program
        pass

    def p_decllist(self, p):
        """decllist : declaration
                    | declaration TILDA decllist"""
        # Define the action when parsing a declaration list
        pass

    def p_declaration(self, p):
        """declaration : IDENTIFIER DOLLAR type"""
        # Define the action when parsing a declaration
        pass

    def p_type(self, p):
        """type : type1
                | arraydecl"""
        # Define the action when parsing a type
        pass

    def p_type1(self, p):
        """type1 : ALBA_NEAGRA
                 | VORBE
                 | DINAIA
                 | DITOATE"""
        # Define the action when parsing type1
        pass

    def p_arraydecl(self, p):
        """arraydecl : MORE LBRACKET nr RBRACKET OF type1"""
        # Define the action when parsing an array declaration
        pass

    def p_cmpdstmt(self, p):
        """cmpdstmt : ONWARD stmtlist AT_EASE"""
        # Define the action when parsing a compound statement
        pass

    def p_stmtlist(self, p):
        """stmtlist : stmt
                    | stmt TILDA stmtlist"""
        # Define the action when parsing a statement list
        pass

    def p_stmt(self, p):
        """stmt : simplstmt
                | structstmt"""
        # Define the action when parsing a statement
        pass

    def p_simplstmt(self, p):
        """simplstmt : assignstmt
                     | iostmt"""
        # Define the action when parsing a simple statement
        pass

    def p_assignstmt(self, p):
        """assignstmt : IDENTIFIER ARROW expression"""
        # Define the action when parsing an assignment statement
        pass

    def p_expression(self, p):
        """expression : expression PLUS term
                      | term"""
        # Define the action when parsing an expression
        pass

    def p_term(self, p):
        """term : term TIMES factor
                | factor"""
        # Define the action when parsing a term
        pass

    def p_factor(self, p):
        """factor : LPAREN expression RPAREN
                  | IDENTIFIER"""
        # Define the action when parsing a factor
        pass

    def p_iostmt(self, p):
        """iostmt : SCAN
                  | WRITE LPAREN IDENTIFIER RPAREN"""
        # Define the action when parsing an I/O statement
        pass

    def p_structstmt(self, p):
        """structstmt : cmpdstmt
                      | ifstmt
                      | whilestmt
                      | choosestmt"""
        # Define the action when parsing a structured statement
        pass

    def p_ifstmt(self, p):
        """ifstmt : WHEN condition THEN LBRACE stmt RBRACE
                  | WHEN condition THEN LBRACE stmt RBRACE OTHERWISE LBRACE stmt RBRACE"""
        # Define the action when parsing an if statement
        pass

    def p_whilestmt(self, p):
        """whilestmt : WHILE condition PERFORM LBRACE stmt RBRACE"""
        # Define the action when parsing a while statement
        pass

    def p_choosestmt(self, p):
        """choosestmt : CHOOSE LPAREN expression RPAREN LBRACE caselist RBRACE"""
        # Define the action when parsing a choose statement
        pass

    def p_caselist(self, p):
        """caselist : case caselist
                    | defaultstmt"""
        # Define the action when parsing a case list
        pass

    def p_case(self, p):
        """case : CASE constant COLON LBRACE stmtlist RBRACE"""
        # Define the action when parsing a case
        pass

    def p_defaultstmt(self, p):
        """defaultstmt : DEFAULT COLON LBRACE stmtlist RBRACE"""
        # Define the action when parsing a default statement
        pass
    #
    # def p_error(self, p):
    #     print(f"Syntax error at line {p.lineno}, position {find_column(p.lexer.lexdata, p)}: Unexpected token '{p.value}'")
    #     yacc.errok()

