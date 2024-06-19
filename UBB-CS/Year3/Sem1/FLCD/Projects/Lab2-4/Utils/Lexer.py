from ply import lex


class MyLexer:
    def __init__(self):
        # List of token names. This is always required
        self.tokens = [
            'DOLLAR_NUMBER',
            'DOLLAR',
            'ID',
            'NUMBER',
            'PLUS',
            'MINUS',
            'TIMES',
            'DIVIDE',
            'LT',
            'GT',
            'EQ',
            'NEQ',
            'GTEQ',
            'LTEQ',
            'LBRACKET',
            'RBRACKET',
            'LBRACE',
            'RBRACE',
            'COMMA',
            'SEMICOLON',
            'COLON',
            'SPACE',
            'NEWLINE',
            'CHARACTER',
            'STRING',
            'UNDERSCORE',
            'SPECIALCHAR',
            'RESERVEDWORD',
        ] + ['RESERVED_' + r.upper() for r in
             ['MORE', 'char', 'const', 'perform', 'otherwise', 'when', 'then', 'choose', 'nr', 'scan',
              'write', 'while', 'var']]

        # Regular expression rules for simple tokens
        self.t_PLUS = r'\+'
        self.t_MINUS = r'-'
        self.t_TIMES = r'\*'
        self.t_DIVIDE = r'/'
        self.t_LT = r'<'
        self.t_GT = r'>'
        self.t_EQ = r'='
        self.t_NEQ = r'<>'
        self.t_GTEQ = r'>='
        self.t_LTEQ = r'<='
        self.t_LBRACKET = r'\['
        self.t_RBRACKET = r'\]'
        self.t_LBRACE = r'\{'
        self.t_RBRACE = r'\}'
        self.t_COMMA = r','
        self.t_SEMICOLON = r';'
        self.t_COLON = r':'
        self.t_SPACE = r'[\ ]'
        self.t_NEWLINE = r'\n'
        self.t_CHARACTER = r'\'[A-Za-z0-9]\''
        self.t_STRING = r'\"(?:[^\"\\]|\\.)*\"'
        self.t_UNDERSCORE = r'_'

        # Reserved words
        self.reserved_words = {'MORE', 'char', 'const', 'perform', 'otherwise', 'when', 'then', 'choose', 'nr', 'scan',
                               'write', 'while', 'var'}

        # Build the lexer
        self.lexer = lex.lex(module=self)

    # Define a rule for identifiers
    def t_ID(self, t):
        r'(\$?[A-Za-z_][A-Za-z0-9_]*)'
        if t.value.upper() in self.reserved_words:
            t.type = 'RESERVED_' + t.value.upper()
        return t

    # Define a rule for numbers
    def t_NUMBER(self, t):
        r'\d+(\.\d*)?([eE][-+]?\d+)?'
        t.value = float(t.value) if '.' in t.value or 'e' in t.value or 'E' in t.value else int(t.value)

        # Check if the number is immediately followed by an identifier
        lookahead = self.lexer.lexdata[self.lexer.lexpos:self.lexer.lexpos + 1]
        if lookahead.isalpha() or lookahead == '_':
            print(f"Lexical error: Invalid constant '{t.value}' followed by '{lookahead}'")
            self.lexer.skip(1)

        return t

    def t_DOLLAR_NUMBER(self, t):
        r'\$\d+'
        print(f"Lexical error: Invalid sequence '$' followed by a number: '{t.value}'")
        self.lexer.skip(1)

    # Define a rule to track line numbers
    def t_newline(self, t):
        r'\n+'
        t.lexer.lineno += len(t.value)

    # Define a rule to ignore whitespace
    t_ignore = ' \t'

    def t_SPECIALCHAR(self, t):
        r'[~.()]'
        return t

    def t_RESERVEDWORD(self, t):
        r'[A-Za-z]+'
        t.type = 'RESERVED_' + t.value.upper()
        return t

    # Define a rule for DOLLAR
    def t_DOLLAR(self, t):
        r'\$?[A-Za-z_][A-Za-z0-9_]*\d*'
        if t.value.upper() in self.reserved_words:
            t.type = 'RESERVED_' + t.value.upper()
        return t

    # Define a rule for errors
    def t_error(self, t):
        if isinstance(t, str):
            print(f"Illegal character '{t}'")
        else:
            print(f"Illegal character '{t.value[0]}' at line {t.lineno}, position {t.lexpos}")
        t.lexer.skip(1)

    def tokenize(self, input_code):
        self.lexer.input(input_code)
        tokens = []
        for token in self.lexer:
            tokens.append(token)
        return tokens
