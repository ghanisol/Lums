import ply.lex as lex
import ply.yacc as yacc

# Reserved words
reserved = (
	'if',
	'elseif',
	'else',
	'do',
	'while',
	'array',
	'echo',
	'function'
)

# Token names
tokens = (
	'ID',			#'identifiers'
	'NUMBER',		#'numbers'
	'STRING',		#'string'
	'PLUS',			#'+'
	'MINUS',		#'-'
	'PLUSPLUS',		#'++'
	'MINUSMINUS',	#'--'
	'MULT',			#'*'
	'DIV',			#'/'
	'MOD',			#'%'	
	'GT',			#'>'
	'LT',			#'<'
	'GE',			#'>='
	'LE',			#'<='
	'EEQ',			#'=='
	'NEQ',			#'!='
	'LPAREN',		#'('
	'RPAREN',		#')'
	'LBRACE',		#'{'
	'RBRACE',		#'}'
	'LBRACKET',		#'['
	'RBRACKET',		#']'
	'EQ',			#'='
	'COMMA',		#','
	'SEMICOLON',	#';'
	'IF',			#'if'
	'ELSEIF',		#'elseif'
	'ELSE',			#'else'
	'DO',			#'do'
	'WHILE',		#'while'
	'ENDLINE',		#'\n'
	'ARRAY',		#'array'
	'ECHO',			#'echo'
	'FUNCTION',		#'function'
	'FUNCNAME'		#'function names'
)

# Regular Expressions 
t_ignore = ' \t\r\v'
t_PLUS = r'\+'
t_MINUS = r'\-'
t_PLUSPLUS = r'\+\+'
t_MINUSMINUS = r'\-\-'
t_MULT = r'\*'
t_DIV = r'/'
t_MOD = r'%'
t_GT = r'>'
t_LT = r'<'
t_GE = r'>='
t_LE = r'<='
t_EEQ = r'=='
t_NEQ = r'!='
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_LBRACE = r'{'
t_RBRACE = r'}'
t_LBRACKET = r'\['
t_RBRACKET = r'\]'
t_EQ = r'='
t_COMMA = r','
t_SEMICOLON = r';'
t_IF = r'if'
t_ELSEIF = r'elseif'
t_ELSE = r'else'
t_DO = r'do'
t_WHILE = r'while'
t_ARRAY = r'array'
t_ECHO = r'echo'
t_FUNCTION = r'function'

def t_ID(t):
	r'\$[a-zA-Z_][a-zA-Z0-9_]*'
	if t.value in reserved:
		t.type = t.value.upper()
	return t

def t_NUMBER(t):
	r'-?[0-9]*\.?[0-9]+'
	if '.' in t.value:
		t.value = float(t.value)
	else:
		t.value = int(t.value)
	return t

def t_STRING(t):
	r'"[^"]*"'
	t.value = t.value[1:-1]
	return t

def t_FUNCNAME(t):
	r'[a-z][a-zA-Z0-9]*'
	if t.value in reserved:
		t.type = t.value.upper()
	return t

def t_ENDLINE(t):
	r'\n'
	t.lexer.lineno += 1
	pass

def t_error(t):
	print "Invalid syntax '%s' at line no. : '%d'" % (t.value[0], t.lexer.lineno)
	t.lexer.skip(1)


# Production Rules
def p_php_0(p):
	'php : element php'
	p[0] = [p[1]] + p[2]

def p_php_1(p):
	'php : '
	p[0] = [ ]

def p_element_0(p):
	'element : stmt'
	p[0] = ('stmt', p[1])

def p_stmt_0(p):
	'stmt : IF LPAREN exp RPAREN LBRACE stmts RBRACE'
	p[0] = ('if', p[3], p[6])

def p_stmt_1(p):
	'stmt : IF LPAREN exp RPAREN LBRACE stmts RBRACE ELSEIF LPAREN exp RPAREN LBRACE stmts RBRACE ELSE LBRACE stmts RBRACE'
	p[0] = ('ifelseif', p[3], p[6], p[10], p[13], p[17])

def p_stmt_2(p):
	'stmt : IF LPAREN exp RPAREN LBRACE stmts RBRACE ELSE LBRACE stmts RBRACE'
	p[0] = ('ifelse', p[3], p[6], p[10])

def p_stmt_3(p):
	'stmt : DO LBRACE stmts RBRACE WHILE LPAREN exp RPAREN'
	p[0] = ('dowhile', p[3], p[7])

def p_stmt_4(p):
	'stmt : ID EQ exp SEMICOLON'
	p[0] = ('var_assign', p[1], p[3])

def p_stmt_5(p):
	'stmt : ID PLUSPLUS SEMICOLON'
	p[0] = ('inc_op', p[1])

def p_stmt_6(p):
	'stmt : ID MINUSMINUS SEMICOLON'
	p[0] = ('dec_op', p[1])

def p_stmt_7(p):
	'stmt : ID EQ ARRAY LPAREN optparams RPAREN SEMICOLON'
	p[0] = ('arr_dec', p[1], p[5])

def p_stmt_8(p):
	'stmt : ID LBRACKET NUMBER RBRACKET EQ exp SEMICOLON'
	p[0] = ('arr_assign', p[1], p[3], p[6])

def p_stmt_9(p):
	'stmt : arr_access SEMICOLON'
	p[0] = p[1]
	
def p_stmt_10(p):
	'stmt : ECHO printable SEMICOLON'
	p[0] = ('echo', p[2])

def p_stmt_11(p):
	'stmt : FUNCTION FUNCNAME LPAREN optparams RPAREN LBRACE stmts RBRACE'
	p[0] = ('fun_def', p[2], p[4], p[7])

def p_stmt_12(p):
	'stmt : FUNCNAME LPAREN optparams RPAREN SEMICOLON'
	p[0] = ('fun_call', p[1], p[3])

def p_printable_0(p):
	'printable : exp'
	p[0] = p[1]

def p_arr_access_0(p):
	'arr_access : ID LBRACKET NUMBER RBRACKET'
	p[0] = ('arr_access', p[1], p[3])

def p_optparams_0(p):
	'optparams : params'
	p[0] = p[1]

def p_optparams_1(p):
	'optparams : '
	p[0] = []

def p_params_0(p):
	'params : exp COMMA params'
	p[0] = [p[1]] + p[3]	

def p_params_1(p):
	'params : exp'
	p[0] = [p[1]]

def p_stmts_0(p):
	'stmts : stmt stmts'
	p[0] = [p[1]] + p[2]

def p_stmts_1(p):
	'stmts : '
	p[0] = []

def p_exp_0(p):
	'exp : exp binop exp'
	p[0] = ('binop', p[1], p[2], p[3])

def p_exp_1(p):
	'exp : LPAREN exp binop exp RPAREN'
	p[0] = ('binop', p[2], p[3], p[4])

def p_exp_2(p):
	'exp : exp comop exp'
	p[0] = ('comop', p[1], p[2], p[3])

def p_exp_3(p):
	'exp : LPAREN exp comop exp RPAREN'
	p[0] = ('comop', p[2], p[3], p[4])	

def p_exp_4(p):
	'exp : ID'
	p[0] = ('id', p[1])

def p_exp_5(p):
	'exp : NUMBER'
	p[0] = ('number', p[1])

def p_exp_6(p):
	'exp : STRING'
	p[0] = ('string', p[1])

def p_exp_7(p):
	'exp : arr_access'
	p[0] = p[1]

def p_binop_0(p):
	'''binop : PLUS
		| MINUS
		| MULT
		| DIV
		| MOD
		| GT
		| LT
		| GE
		| LE '''
	p[0] = p[1]

def p_comop_0(p):
	'''comop : EEQ
		| NEQ '''
	p[0] = p[1]

def p_error(p):
	print 'Syntax error at lineno : %d' % p.lineno


# Interpretation

def eval_exp(tree, environment):
	nodetype = tree[0]
	if nodetype == 'number':
		return tree[1]
	elif nodetype == 'string':
		return tree[1]
	elif nodetype == 'id':
		value = env_lookup(tree[1], environment)
		if (value != None):
			return value
		else:
			print "Variable %s not defined!" % tree[1]
			exit(1)
	elif nodetype == 'arr_access':
		arr_id = env_lookup(tree[1], environment)
		if (arr_id != None and isinstance(arr_id, list)):
			return arr_id[tree[2]]
		else:
			print 'Error : %s is not defined as array.' % tree[1]
			exit(1)
		
	elif nodetype == 'binop':
		left_child = tree[1]
		op = tree[2]
		right_child = tree[3]

		left_val = eval_exp(left_child, environment)
		right_val = eval_exp(right_child, environment)

		if isinstance(left_val, str) or isinstance(right_val, str):
				print "Logical Error : Binary operations not allowed on strings"
				return
		# create a dict
		if op == '+':
			return left_val + right_val
		elif op == '-':
			return left_val - right_val
		elif op == '*':
			return left_val * right_val
		elif op == '/':
			return left_val / right_val
		elif op == '%':
			return left_val % right_val
		elif op == '>':
			return left_val > right_val
		elif op == '<':
			return left_val < right_val
		elif op == '>=':
			return left_val >= right_val
		elif op == '<=':
			return left_val <= right_val

	elif nodetype == 'comop':
		left_child = tree[1]
		op = tree[2]
		right_child = tree[3]

		left_val = eval_exp(left_child, environment)
		right_val = eval_exp(right_child, environment)
		
		if op == '==':
			if isinstance(left_val, str) and isinstance(right_val, str):
				return left_val == right_val
			elif isinstance(left_val, str) or isinstance(right_val, str):
				print "Logical Error : String is not comparable with other data types."
				exit(1)
			else:
				return left_val == right_val
		elif op == '!=':
			if isinstance(left_val, str) and isinstance(right_val, str):
				return left_val != right_val
			elif isinstance(left_val, str) or isinstance(right_val, str):
				print "Logical Error : String is not comparable with other data types."
				exit(1)
			else:
				return left_val != right_val

		
def eval_stmt(tree, environment):
	stmttype = tree[0]
	if stmttype == 'var_assign':
		value = eval_exp(tree[2], environment)
		isUpdate = env_update(tree[1], value, environment)
		if (not isUpdate):
			env_create(tree[1], value, environment)

	elif stmttype == 'inc_op':
		value = env_lookup(tree[1], environment)
		if (value != None):
			env_update(tree[1], value+1, environment)
		else:
			print "Variable %s not defined!" % tree[1]
			exit(1)
	elif stmttype == 'dec_op':
		value = env_lookup(tree[1], environment)
		if (value != None):
			env_update(tree[1], value-1, environment)
		else:
			print "Variable %s not defined!" % tree[1]
			exit(1)
	elif stmttype == 'arr_dec':
		value = []
		for v in tree[2]:
			value.append(eval_exp(v, environment))
		isUpdate = env_update(tree[1], value, environment)
		if (not isUpdate):
			env_create(tree[1], value, environment)
	elif stmttype == 'arr_assign':
		value = eval_exp(tree[3], environment)
		arr_id = env_lookup(tree[1], environment)
		if (arr_id != None and isinstance(arr_id, list)):
			arr_id[tree[2]] = value
		else:
			print "Variable %s not defined!" % tree[1]
			exit(1)
	elif stmttype == 'echo':
		print eval_exp(tree[1], environment)

	elif stmttype == 'if':
		env_child = (environment, {})
		cond_exp = tree[1]
		if (eval_exp(cond_exp, env_child)):
			then_stmts = tree[2]
			for s in then_stmts:
				eval_stmt(s, env_child)
		
	elif stmttype == 'ifelseif':
		if_cond_exp = tree[1]
		elif_cond_exp = tree[3]
		if (eval_exp(if_cond_exp, environment)):
			env_child = (environment, {})
			then_stmts = tree[2]
			for s in then_stmts:
				eval_stmt(s, env_child)
		elif (eval_exp(elif_cond_exp, environment)):
			env_child = (environment, {})
			then_stmts = tree[4]
			for s in then_stmts:
				eval_stmt(s, env_child)
		else:
			env_child = (environment, {})
			then_stmts = tree[5]
			for s in then_stmts:
				eval_stmt(s, env_child)

	elif stmttype == 'ifelse':
		cond_exp = tree[1]
		if (eval_exp(cond_exp, environment)):
			env_child = (environment, {})
			then_stmts = tree[2]
			for s in then_stmts:
				eval_stmt(s, env_child)
		else:
			env_child = (environment, {})
			then_stmts = tree[3]
			for s in then_stmts:
				eval_stmt(s, env_child)

	elif stmttype == 'dowhile':
		env_child = (environment, {})
		cond_exp = tree[2]
		then_stmts = tree[1]
		for s in then_stmts:
			eval_stmt(s, env_child)
		while eval_exp(cond_exp, environment):
			for s in then_stmts:
				eval_stmt(s, env_child)

	elif stmttype == 'fun_def':
		parameters = tree[2]
		for p in parameters:
			if (p[0] != 'id'):
				print 'Syntax error : function definition expects variables.'
				exit(1)
		statements = tree[3]
		value = ('fun_def', parameters, statements)
		env_create(tree[1], value, environment)

	elif stmttype == 'fun_call':
		call_params = tree[2]
		fun_def = env_lookup(tree[1], environment)
		if (fun_def == None):
			print 'Error : Function %s not defined' % tree[1]
			exit(1)
		elif (not isinstance(fun_def, tuple) or fun_def[0] != 'fun_def'):
			print 'Error : %s is not a function.' % tree[1]
			exit(1)


		fun_params = fun_def[1]
		fun_stmts = fun_def[2]

		if (len(fun_params) != len(call_params)):
			print 'Error in number of parameters given to the function %s.' % tree[1]
			exit(1)

		env_child = (environment, {})
		for i in range(len(fun_params)):
			env_create(fun_params[i][1], eval_exp(call_params[i], environment), env_child)

		for s in fun_stmts:
			eval_stmt(s, env_child)

def eval_php(tree, environment):
	for s in tree:
		if (s[0] == 'stmt'):
			eval_stmt(s[1], environment)
			
def env_lookup(vname, env):
	if vname in env[1]:
		return env[1][vname]
	elif env[0] == None:
		return None
	else:
		return env_lookup(vname, env[0])

def env_update(vname, value, env):
	if vname in env[1]:
		env[1][vname] = value
		return True
	elif not env[0] == None:
		return env_update(vname, value, env[0])
	else:
		return False


def env_create(vname, value, env):
	env[1][vname] = value

environment = (None, {})
phplexer = lex.lex()
phpparser = yacc.yacc()


test_string = ''
with open('test1.txt') as f:
	test_string = f.read()

eval_php(phpparser.parse(test_string, lexer=phplexer), environment)
