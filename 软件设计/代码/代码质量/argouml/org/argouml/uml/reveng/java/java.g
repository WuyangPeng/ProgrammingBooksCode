header {
package org.argouml.uml.reveng.java;

import java.util.*;
}  

/** Java 1.2 Recognizer
 *
 * Run 'java Main <directory full of java files>'
 *
 * Contributing authors:
 *		John Mitchell		johnm@non.net
 *		Terence Parr		parrt@magelang.com
 *		John Lilley			jlilley@empathy.com
 *		Scott Stanchfield	thetick@magelang.com
 *		Markus Mohnen       mohnen@informatik.rwth-aachen.de
 *		Peter Williams		pwilliams@netdynamics.com
 *
 * Version 1.00 December 9, 1997 -- initial release
 * Version 1.01 December 10, 1997
 *		fixed bug in octal def (0..7 not 0..8)
 * Version 1.10 August 1998 (parrt)
 *		added tree construction
 *		fixed definition of WS,comments for mac,pc,unix newlines
 *		added unary plus
 * Version 1.11 (Nov 20, 1998)
 *		Added "shutup" option to turn off last ambig warning.
 *		Fixed inner class def to allow named class defs as statements
 *		synchronized requires compound not simple statement
 *		add [] after builtInType DOT class in primaryExpression
 *		"const" is reserved but not valid..removed from modifiers
 * Version 1.12 (Feb 2, 1999)
 *		Changed LITERAL_xxx to xxx in tree grammar.
 *		Updated java.g to use tokens {...} now for 2.6.0 (new feature).
 *
 * Version 1.13 (Apr 23, 1999)
 *		Didn't have (stat)? for else clause in tree parser.
 *		Didn't gen ASTs for interface extends.  Updated tree parser too.
 *		Updated to 2.6.0.
 * Version 1.14 (Jun 20, 1999)
 *		Allowed final/abstract on local classes.
 *		Removed local interfaces from methods
 *		Put instanceof precedence where it belongs...in relationalExpr
 *			It also had expr not type as arg; fixed it.
 *		Missing ! on SEMI in classBlock
 *		fixed: (expr) + "string" was parsed incorrectly (+ as unary plus).
 *		fixed: didn't like Object[].class in parser or tree parser
 * Version 1.15 (Jun 26, 1999)
 *		Screwed up rule with instanceof in it. :(  Fixed.
 *		Tree parser didn't like (expr).something; fixed.
 *		Allowed multiple inheritance in tree grammar. oops.
 * Version 1.16 (August 22, 1999)
 *		Extending an interface built a wacky tree: had extra EXTENDS.
 *		Tree grammar didn't allow multiple superinterfaces.
 *		Tree grammar didn't allow empty var initializer: {}
 * Version 1.17 (October 12, 1999)
 *		ESC lexer rule allowed 399 max not 377 max.
 *		java.tree.g didn't handle the expression of synchronized
 *			statements.
 *
 * Version tracking now done with following ID:
 *
 * $Id: java.g,v 1.10 2001/04/29 22:11:29 marcus Exp $
 *
 * BUG:
 * 		Doesn't like boolean.class!
 *
 * class Test {
 *   public static void main( String args[] ) {
 *     if (boolean.class.equals(boolean.class)) {
 *       System.out.println("works");
 *     }
 *   }
 * }
 *
 * This grammar is in the PUBLIC DOMAIN
 */
class JavaRecognizer extends Parser;

options {
	k = 2;                           // two token lookahead
	exportVocab=Java;                // Call its vocabulary "Java"
	codeGenMakeSwitchThreshold = 2;  // Some optimizations
	codeGenBitsetTestThreshold = 3;
	defaultErrorHandler = false;     // Don't generate parser error handlers
	buildAST = false;
}

tokens {
	BLOCK; MODIFIERS; OBJBLOCK; SLIST; CTOR_DEF; METHOD_DEF; VARIABLE_DEF; 
	INSTANCE_INIT; STATIC_INIT; TYPE; CLASS_DEF; INTERFACE_DEF; 
	PACKAGE_DEF; ARRAY_DECLARATOR; EXTENDS_CLAUSE; IMPLEMENTS_CLAUSE;
	PARAMETERS; PARAMETER_DEF; LABELED_STAT; TYPECAST; INDEX_OP; 
	POST_INC; POST_DEC; METHOD_CALL; EXPR; ARRAY_INIT; 
	IMPORT; UNARY_MINUS; UNARY_PLUS; CASE_GROUP; ELIST; FOR_INIT; FOR_CONDITION; 
	FOR_ITERATOR; EMPTY_STAT; FINAL="final"; ABSTRACT="abstract";
}
	
{
	// Constants for access modifiers according to the JVM specs chapter 4
   	public static final short ACC_PUBLIC    = 0x0001;
        public static final short ACC_PRIVATE   = 0x0002;
        public static final short ACC_PROTECTED = 0x0004;
        public static final short ACC_STATIC    = 0x0008;
        public static final short ACC_FINAL     = 0x0010;
        public static final short ACC_SUPER     = 0x0020;
        public static final short ACC_VOLATILE  = 0x0040;
        public static final short ACC_TRANSIENT = 0x0080;
        public static final short ACC_NATIVE    = 0x0100;
        public static final short ACC_INTERFACE = 0x0200;
        public static final short ACC_ABSTRACT  = 0x0400;                     

	// This one is not(!) in the JVM specs, but required
	public static final short ACC_SYNCHRONIZED  = 0x0800;

	/**
         * To get direct access to the lexer (for the javadoc
	 * comments), we store a reference to it.
         */
	private JavaLexer _lexer = null;

	/**
	 * Set the lexer for this parser.
	 * 
	 * @param lexer The lexer for this parser.
	 */
	private void setLexer(JavaLexer lexer) {
	    _lexer = lexer;
	}
	
	/**
	 * Get the last parsed javadoc comment from the lexer.
         */
	private String getJavadocComment() {
	    return _lexer.getJavadocComment();
	}
	
        private Modeller _modeller;

	Modeller getModeller() {
	    return _modeller;
	}

	void setModeller(Modeller modeller) {
	    _modeller = modeller;
        }
	
        // A reference to the last added MOperation (here: method)
        private Object _currentMethod = null;

	/**
	 * get reference to the last added MOperation (here: method)
	 */
	Object getMethod() {
	    return _currentMethod;
	}

	/**
	 * set reference to the last added MOperation (here: method)
	 */
	void setMethod(Object method) {
	    _currentMethod = method;
        }

        // A method body
        private String _methodBody = null;

	/**
	 * get last method body
	 */
	String getBody() {
	    return _methodBody;
	}

	/**
	 * set last method body
	 */
	void setBody(String body) {
	    _methodBody = body;
        }

	// A flag to indicate if we track the tokens for a expression.
	private boolean      _trackExpression  = false;	

	// A flag to indicate if we are inside a compoundStatement
	private boolean      _inCompoundStatement  = false;	

	// A string buffer for the current expression.
    	private StringBuffer _expressionBuffer = new StringBuffer();   

	/**
	 * set if we are inside a compoundStatement
	 */
	void setIsInCompoundStatement(boolean flag) {
	    _inCompoundStatement = flag;
	}

	/**
	 * check if we are inside a compoundStatement
	 */
	boolean isInCompoundStatement() {
	    return _inCompoundStatement;
	}

	/**
	 * Activate the tracking of expressions.
	 */
	void activateExpressionTracking() {
	    _trackExpression = true;
	}

	/**
         * Deactivate the tracking of expressions.
	 */
	void deactivateExpressionTracking() {
	    _trackExpression = false;
        }

	/**
     	 * Get a tracked expression.
     	 *
     	 * @return the tracked expression.
     	 */
    	public String getExpression() {
            String result = _expressionBuffer.toString();

            _expressionBuffer = new StringBuffer();

            return result;
        }      

	/**
     	 * Appends to a tracked expression. (used to restore it)
     	 */
    	public void appendExpression(String expr) {
            _expressionBuffer.append(expr);
        }      

	public void match(int t) throws MismatchedTokenException, TokenStreamException {
            String text = ((ArgoToken)LT(1)).getWhitespace() + LT(1).getText();

            super.match(t);

            // '== 0' to avoid the following when backtracking
            if(_trackExpression && inputState.guessing==0)
                appendExpression(text);
    	}     
}

// Compilation Unit: In Java, this is a single file.  This is the start
//   rule for this parser
compilationUnit[ Modeller modeller, JavaLexer lexer]
{ setModeller(modeller);
  setLexer(lexer); }
	:	// A compilation unit starts with an optional package definition
		(	packageDefinition
		|	/* nothing */
		)

		// Next we have a series of zero or more import statements
		( importDefinition )*

		// Wrapping things up with any number of class or interface
		//    definitions
		( typeDefinition )*

		EOF
	;


// Package statement: "package" followed by an identifier.
packageDefinition
	options {defaultErrorHandler = true;} // let ANTLR handle errors
{String packageName = null;}
	:	"package" packageName=identifier SEMI
		{getModeller().addPackage(packageName);}     	
	;


// Import statement: import followed by a package or class name
importDefinition
	options {defaultErrorHandler = true;}
{String name=null;}
	:	"import" name=identifierStar SEMI
 		{getModeller().addImport(name);}    
	;

// A type definition in a file is either a class or interface definition.
typeDefinition
	options {defaultErrorHandler = true;}
{short m = 0;}
	:	m=modifiers
		( classDefinition[getJavadocComment(), m]
		| interfaceDefinition[getJavadocComment(), m]
		)
	|	SEMI
	;

/** A declaration is the creation of a reference or primitive-type variable
 *  Create a separate Type/Var tree for each var in the var list.
 */
declaration
{short m = 0; String t=null;}
	:	m=modifiers t=typeSpec v:variableDefinitions["", m, t]
	;

// A list of zero or more modifiers.  We could have used (modifier)* in
//   place of a call to modifiers, but I thought it was a good idea to keep
//   this rule separate so they can easily be collected in a Vector if
//   someone so desires
modifiers returns [ short mod_flags]
{ mod_flags = 0;
  short cur_flag; }
	:	( cur_flag=modifier { mod_flags |= cur_flag; })*
	;


// A type specification is a type name with possible brackets afterwards
//   (which would make it an array type).
typeSpec returns [String type=null]
	{String c=null, b=null;}
	: c=classTypeSpec {type=c;}
	| b=builtInTypeSpec {type=b;}
	;

// A class type specification is a class type with possible brackets afterwards
//   (which would make it an array type).
classTypeSpec returns [String type=null]
	:	type=identifier (LBRACK RBRACK {type +="[]";})*
	;

// A builtin type specification is a builtin type with possible brackets
// afterwards (which would make it an array type).
builtInTypeSpec returns [String type=null]
	:	type=builtInType (LBRACK RBRACK {type += "[]";})*
	;

// A type name. which is either a (possibly qualified) class name or
//   a primitive (builtin) type
type returns [String type=null]
	:	type=identifier
	|	type=builtInType
	;

// The primitive types.
builtInType returns [String type=null]
	:	"void"     {type="void";}
	|	"boolean"  {type="boolean";}
	|	"byte"     {type="byte";}
	|	"char"	   {type="char";}
	|	"short"	   {type="short";}
	|	"int"      {type="int";}
	|	"float"    {type="float";}
	|	"long"     {type="long";}
	|	"double"   {type="double";}
	;

// A (possibly-qualified) java identifier.  We start with the first IDENT
//   and expand its name by adding dots and following IDENTS
identifier returns [String name=null]
        :       t1:IDENT {name = t1.getText();}
                (DOT t2:IDENT {name += "." + t2.getText();})*
        ;    

identifierStar returns [String name=null]
	:	t1:IDENT {name = t1.getText();}
		( DOT t2:IDENT {name = name + "." + t2.getText();} )*
		( DOT STAR {name = name + "." + "*";} )?
	;


// modifiers for Java classes, interfaces, class/instance vars and methods
modifier returns [short mod_flag = 0]
	:	"private"      { mod_flag = ACC_PRIVATE; }
	|	"public"       { mod_flag = ACC_PUBLIC; }
	|	"protected"    { mod_flag = ACC_PROTECTED; }
	|	"static"       { mod_flag = ACC_STATIC; }
	|	"transient"    { mod_flag = ACC_TRANSIENT; }
	|	"final"        { mod_flag = ACC_FINAL; }
	|	"abstract"     { mod_flag = ACC_ABSTRACT; }
	|	"native"       { mod_flag = ACC_NATIVE; }
	|	"threadsafe"
	|	"synchronized" { mod_flag = ACC_SYNCHRONIZED; }
//	|	"const"			// reserved word; leave out
	|	"volatile"     { mod_flag = ACC_VOLATILE; }
	;


// Definition of a Java class
classDefinition[String javadoc, short modifiers]
{String superClassName = null; Vector ic = null;}
	:	"class" className:IDENT
		// it _might_ have a superclass...
		superClassName=superClassClause
		// it might implement some interfaces...
		ic=implementsClause
		{getModeller().addClass(className.getText(), modifiers, superClassName, ic, javadoc);}  
		// now parse the body of the class
		classBlock
		{getModeller().popClassifier();}
	;

superClassClause returns [String superClassName = null]
	:	( "extends" superClassName=identifier )?
	;

// Definition of a Java Interface
interfaceDefinition[String javadoc, short modifiers]
{Vector ie=null;}
        :       "interface" interfaceName:IDENT
                // it might extend some other interfaces
                ie=interfaceExtends
                {getModeller().addInterface(interfaceName.getText(), modifiers,
ie, javadoc);}
                // now parse the body of the interface (looks like a class...)
                classBlock
                {getModeller().popClassifier();}
        ;


// This is the body of a class.  You can have fields and extra semicolons,
// That's about it (until you see what a field is...)
classBlock
	:	LCURLY
			( field | SEMI )*
		RCURLY
	;

// An interface can extend several other interfaces...
interfaceExtends returns [Vector names=new Vector()]
	{String n=null;}
	:	(
			e:"extends"
			n=identifier {names.addElement(n);}
			(COMMA n=identifier {names.addElement(n);})*
		)?
	;

// A class can implement several interfaces...
implementsClause returns [Vector names=new Vector()]
	{String n=null;}
	:	(
			i:"implements"
			n=identifier {names.addElement(n);}
			(COMMA n=identifier {names.addElement(n);})*
		)?
	;

// Now the various things that can be defined inside a class or interface...
// Note that not all of these are really valid in an interface (constructors,
//   for example), and if this grammar were used for a compiler there would
//   need to be some semantic checks to make sure we're doing the right thing...
field
{short mods=0; String t=null; Vector param=null; String a=null;}
	:	// method, constructor, or variable declaration
		mods=modifiers
		(	ctorHead[mods] compoundStatement // constructor
			{getModeller().addBodyToOperation(getMethod(),getBody());
			 setMethod(null);
			 setBody(null);}
		|	classDefinition["", mods]       // inner class
		|	interfaceDefinition["", mods]   // inner interface
		|	t=typeSpec         // method or variable declaration(s)
			(	( name:IDENT  // the name of the method

				  // parse the formal parameter declarations.
				  LPAREN param=parameterDeclarationList RPAREN

				  (a=returnTypeBrackersOnEndOfMethodHead
				   {t += a;})

				  // get the list of exceptions that this method is declared to throw
				  (throwsClause)?

				  (compoundStatement | SEMI)
				) {setMethod(getModeller().addOperation(mods, t, name.getText(), param, getJavadocComment()));
				   getModeller().addBodyToOperation(getMethod(),getBody());
				   setMethod(null);
				   setBody(null);}
			|	classVariableDefinitions[getJavadocComment(), mods, t] SEMI
			)
		)

    // "static { ... }" class initializer
	|	"static" s3:compoundStatement
    // "{ ... }" instance initializer
	|	s4:compoundStatement
	;

classVariableDefinitions[String javadoc, short modifiers, String returnType]
	:	classVariableDeclarator[javadoc, modifiers, returnType]
		(	COMMA
			classVariableDeclarator[javadoc, modifiers, returnType]
		)*
	;

/** Declaration of a class variable.
 * It can also include possible initialization.
 */
classVariableDeclarator[String javadoc, short modifiers, String varType]
{String initializer=null; String b=null;}
	:	(id:IDENT b=declaratorBrackets initializer=varInitializer)
		{getModeller().addAttribute(modifiers, varType+b, id.getText(), initializer, javadoc);}
	;

variableDefinitions[String javadoc, short modifiers, String returnType]
	:	variableDeclarator[javadoc, modifiers, returnType]
		(	COMMA
			variableDeclarator[javadoc, modifiers, returnType]
		)*
	;

/** Declaration of a variable.  This can be a class/instance variable,
 *   or a local variable in a method
 * It can also include possible initialization.
 */
variableDeclarator[String javadoc, short modifiers, String varType]
{String initializer=null;}
	:	(IDENT declaratorBrackets initializer=varInitializer)
	;

declaratorBrackets returns [String b=""]
	:	(LBRACK RBRACK {b += "[]";} )*
	;

varInitializer returns [String expression=null]
{String trackedSoFar = null;}
	:	( ASSIGN
		  {trackedSoFar=getExpression();
		   if (!isInCompoundStatement())
		     activateExpressionTracking();}
		  initializer
		  {expression=getExpression();
		   if (isInCompoundStatement()) {
		     activateExpressionTracking();
		     appendExpression(trackedSoFar);
		     appendExpression(expression);
		   } else
		     deactivateExpressionTracking();})?
	;

// This is an initializer used to set up an array.
arrayInitializer
	:	LCURLY
			(	initializer
				(
					// CONFLICT: does a COMMA after an initializer start a new
					//           initializer or start the option ',' at end?
					//           ANTLR generates proper code by matching
					//			 the comma as soon as possible.
					options {
						warnWhenFollowAmbig = false;
					}
				:
					COMMA initializer
				)*
				(COMMA)?
			)?
		RCURLY
	;


// The two "things" that can initialize an array element are an expression
//   and another (nested) array initializer.
initializer
	:	expression
	|	arrayInitializer
	;

// This is the header of a method.  It includes the name and parameters
//   for the method.
//   This also watches for a list of exception classes in a "throws" clause.
ctorHead[ short mods]
	{Vector param = null;}
	:	name:IDENT  // the name of the method

		// parse the formal parameter declarations.
		LPAREN param=parameterDeclarationList RPAREN

		{ setMethod(getModeller().addOperation(mods, null, 
			name.getText(), param, getJavadocComment())); }

		// get the list of exceptions that this method is
		// declared to throw
		(throwsClause)?
	;

// This is a list of exception classes that the method is declared to throw
throwsClause
	:	"throws" identifier ( COMMA identifier )*
	;


returnTypeBrackersOnEndOfMethodHead returns [String a=""]
	:	(LBRACK RBRACK {a += "[]";})*
	;

// A list of formal parameters
parameterDeclarationList returns [Vector paramList=new Vector()]
{Vector currentParameter=null;}
	:	( 
		  currentParameter=parameterDeclaration { paramList.add(currentParameter); } 
		  ( COMMA currentParameter=parameterDeclaration { paramList.add(currentParameter); } )* 
		)?
	;

// A formal parameter.
parameterDeclaration returns [Vector pd=new Vector()]
{short pm=0; String ts=null; String pdb=null;}
	:	(pm=parameterModifier ts=typeSpec id:IDENT) 
		pdb=parameterDeclaratorBrackets
		{ pd.add(new Short(pm));
		  pd.add(ts + pdb);
		  pd.add(id.getText());}
	;

parameterDeclaratorBrackets returns [String pdb=""]
	:	(LBRACK RBRACK {pdb += "[]";} )*
	;

parameterModifier returns [short mods=0;]
	:	("final" {mods |= ACC_FINAL;})?
	;

// Compound statement.  This is used in many contexts:
//   Inside a class definition prefixed with "static":
//      it is a class initializer
//   Inside a class definition without "static":
//      it is an instance initializer
//   As the body of a method
//   As a completely indepdent braced block of code inside a method
//      it starts a new scope for variable definitions

compoundStatement
{boolean isOutestCompStat = !isInCompoundStatement();}
	:	LCURLY
		{if (isOutestCompStat) {
		   setIsInCompoundStatement(true);
		   activateExpressionTracking();}}
		// include the (possibly-empty) list of statements
		(statement)*
		{if (isOutestCompStat) {
		   setBody(getExpression());
		   deactivateExpressionTracking();
		   setIsInCompoundStatement(false);}}
		RCURLY
	;


statement
	// A list of statements in curly braces -- start a new scope!
	:	compoundStatement

	// class definition
	|	classDefinition["",(short)0]

	// final class definition
	|	"final" classDefinition["",ACC_FINAL]

	// abstract class definition
	|	"abstract" classDefinition["",ACC_ABSTRACT]

	// declarations are ambiguous with "ID DOT" relative to expression
	// statements.  Must backtrack to be sure.  Could use a semantic
	// predicate to test symbol table to see what the type was coming
	// up, but that's pretty hard without a symbol table ;)
	|	(declaration)=> declaration SEMI

	// An expression statement.  This could be a method call,
	// assignment statement, or any other expression evaluated for
	// side-effects.
	|	expression SEMI

	// Attach a label to the front of a statement
	|	IDENT COLON statement

	// If-else statement
	|	"if" LPAREN expression RPAREN statement
		(
			// CONFLICT: the old "dangling-else" problem...
			//           ANTLR generates proper code matching
			//			 as soon as possible.  Hush warning.
			options {
				warnWhenFollowAmbig = false;
			}
		:
			"else" statement
		)?

	// For statement
	|	"for"
			LPAREN
				forInit SEMI   // initializer
				forCond	SEMI   // condition test
				forIter         // updater
			RPAREN
			statement                     // statement to loop over

	// While statement
	|	"while" LPAREN expression RPAREN statement

	// do-while statement
	|	"do" statement "while" LPAREN expression RPAREN SEMI

	// get out of a loop (or switch)
	|	"break" (IDENT)? SEMI

	// do next iteration of a loop
	|	"continue" (IDENT)? SEMI

	// Return an expression
	|	"return" (expression)? SEMI

	// switch/case statement
	|	"switch" LPAREN expression RPAREN LCURLY
			( casesGroup )*
		RCURLY

	// exception try-catch block
	|	tryBlock

	// throw an exception
	|	"throw" expression SEMI

	// synchronize a statement
	|	"synchronized" LPAREN expression RPAREN compoundStatement

	// empty statement
	|	SEMI 
	;


casesGroup
	:	(	// CONFLICT: to which case group do the statements bind?
			//           ANTLR generates proper code: it groups the
			//           many "case"/"default" labels together then
			//           follows them with the statements
			options {
				warnWhenFollowAmbig = false;
			}
			:
			aCase
		)+
		caseSList
	;

aCase
	:	("case" expression | "default") COLON
	;

caseSList
	:	(statement)*
	;

// The initializer for a for loop
forInit
		// if it looks like a declaration, it is
	:	(	(declaration)=> declaration
		// otherwise it could be an expression list...
		|	expressionList
		)?
	;

forCond
	:	(expression)?
	;

forIter
	:	(expressionList)?
	;

// an exception handler try/catch block
tryBlock
	:	"try" compoundStatement
		(handler)*
		( "finally" compoundStatement )?
	;


// an exception handler
handler
	:	"catch" LPAREN parameterDeclaration RPAREN compoundStatement
	;


// expressions
// Note that most of these expressions follow the pattern
//   thisLevelExpression :
//       nextHigherPrecedenceExpression
//           (OPERATOR nextHigherPrecedenceExpression)*
// which is a standard recursive definition for a parsing an expression.
// The operators in java have the following precedences:
//    lowest  (13)  = *= /= %= += -= <<= >>= >>>= &= ^= |=
//            (12)  ?:
//            (11)  ||
//            (10)  &&
//            ( 9)  |
//            ( 8)  ^
//            ( 7)  &
//            ( 6)  == !=
//            ( 5)  < <= > >=
//            ( 4)  << >>
//            ( 3)  +(binary) -(binary)
//            ( 2)  * / %
//            ( 1)  ++ -- +(unary) -(unary)  ~  !  (type)
//                  []   () (method call)  . (dot -- identifier qualification)
//                  new   ()  (explicit parenthesis)
//
// the last two are not usually on a precedence chart; I put them in
// to point out that new has a higher precedence than '.', so you
// can validy use
//     new Frame().show()
// 
// Note that the above precedence levels map to the rules below...
// Once you have a precedence chart, writing the appropriate rules as below
//   is usually very straightfoward



// the mother of all expressions
expression
	:	assignmentExpression
	;


// This is a list of expressions.
expressionList
	:	expression (COMMA expression)*
	;


// assignment expression (level 13)
assignmentExpression
	:	conditionalExpression
		(	(	ASSIGN
            |   PLUS_ASSIGN
            |   MINUS_ASSIGN
            |   STAR_ASSIGN
            |   DIV_ASSIGN
            |   MOD_ASSIGN
            |   SR_ASSIGN
            |   BSR_ASSIGN
            |   SL_ASSIGN
            |   BAND_ASSIGN
            |   BXOR_ASSIGN
            |   BOR_ASSIGN
            )
			assignmentExpression
		)?
	;


// conditional test (level 12)
conditionalExpression
	:	logicalOrExpression
		( QUESTION assignmentExpression COLON conditionalExpression )?
	;


// logical or (||)  (level 11)
logicalOrExpression
	:	logicalAndExpression (LOR logicalAndExpression)*
	;


// logical and (&&)  (level 10)
logicalAndExpression
	:	inclusiveOrExpression (LAND inclusiveOrExpression)*
	;


// bitwise or non-short-circuiting or (|)  (level 9)
inclusiveOrExpression
	:	exclusiveOrExpression (BOR exclusiveOrExpression)*
	;


// exclusive or (^)  (level 8)
exclusiveOrExpression
	:	andExpression (BXOR andExpression)*
	;


// bitwise or non-short-circuiting and (&)  (level 7)
andExpression
	:	equalityExpression (BAND equalityExpression)*
	;


// equality/inequality (==/!=) (level 6)
equalityExpression
	:	relationalExpression ((NOT_EQUAL | EQUAL) relationalExpression)*
	;


// boolean relational expressions (level 5)
relationalExpression
	:	shiftExpression
		(	(	(	LT
				|	GT
				|	LE
				|	GE
				)
				shiftExpression
			)*
		|	"instanceof" typeSpec
		)
	;


// bit shift expressions (level 4)
shiftExpression
	:	additiveExpression ((SL | SR | BSR) additiveExpression)*
	;


// binary addition/subtraction (level 3)
additiveExpression
	:	multiplicativeExpression ((PLUS | MINUS) multiplicativeExpression)*
	;


// multiplication/division/modulo (level 2)
multiplicativeExpression
	:	unaryExpression ((STAR | DIV | MOD ) unaryExpression)*
	;

unaryExpression
	:	INC unaryExpression
	|	DEC unaryExpression
	|	MINUS unaryExpression
	|	PLUS unaryExpression
	|	unaryExpressionNotPlusMinus
	;

unaryExpressionNotPlusMinus
	:	BNOT unaryExpression
	|	LNOT unaryExpression

	|	(	// subrule allows option to shut off warnings
			options {
				// "(int" ambig with postfixExpr due to lack of sequence
				// info in linear approximate LL(k).  It's ok.  Shut up.
				generateAmbigWarnings=false;
			}
		:	// If typecast is built in type, must be numeric operand
			// Also, no reason to backtrack if type keyword like int, float...
			LPAREN builtInTypeSpec RPAREN
			unaryExpression

			// Have to backtrack to see if operator follows.  If no operator
			// follows, it's a typecast.  No semantic checking needed to parse.
			// if it _looks_ like a cast, it _is_ a cast; else it's a "(expr)"
		|	(LPAREN classTypeSpec RPAREN unaryExpressionNotPlusMinus)=>
			LPAREN classTypeSpec RPAREN
			unaryExpressionNotPlusMinus

		|	postfixExpression
		)
	;

// qualified names, array expressions, method invocation, post inc/dec
postfixExpression
	:	primaryExpression // start with a primary

		(	// qualified id (id.id.id.id...) -- build the name
			DOT ( IDENT
				| "this"
				| "class"
				| newExpression
				| "super" LPAREN ( expressionList )? RPAREN
				)
			// the above line needs a semantic check to make sure "class"
			//   is the _last_ qualifier.

			// allow ClassName[].class
		|	( LBRACK RBRACK )+
			DOT "class"

			// an array indexing operation
		|	LBRACK expression RBRACK

			// method invocation
			// The next line is not strictly proper; it allows x(3)(4) or
			//  x[2](4) which are not valid in Java.  If this grammar were used
			//  to validate a Java program a semantic check would be needed, or
			//   this rule would get really ugly...
		|	LPAREN
				argList
			RPAREN
		)*

		// possibly add on a post-increment or post-decrement.
		// allows INC/DEC on too much, but semantics can check
		(	INC
	 	|	DEC
		|	// nothing
		)

		// look for int.class and int[].class
	|	builtInType 
		(LBRACK RBRACK)*
		DOT "class"
	;

// the basic element of an expression
primaryExpression
	:	IDENT
	|	newExpression
	|	constant
	|	"super"
	|	"true"
	|	"false"
	|	"this"
	|	"null"
	|	LPAREN assignmentExpression RPAREN
	;

/** object instantiation.
 *  Trees are built as illustrated by the following input/tree pairs:
 *  
 *  new T()
 *  
 *  new
 *   |
 *   T --  ELIST
 *           |
 *          arg1 -- arg2 -- .. -- argn
 *  
 *  new int[]
 *
 *  new
 *   |
 *  int -- ARRAY_DECLARATOR
 *  
 *  new int[] {1,2}
 *
 *  new
 *   |
 *  int -- ARRAY_DECLARATOR -- ARRAY_INIT
 *                                  |
 *                                EXPR -- EXPR
 *                                  |      |
 *                                  1      2
 *  
 *  new int[3]
 *  new
 *   |
 *  int -- ARRAY_DECLARATOR
 *                |
 *              EXPR
 *                |
 *                3
 *  
 *  new int[1][2]
 *  
 *  new
 *   |
 *  int -- ARRAY_DECLARATOR
 *               |
 *         ARRAY_DECLARATOR -- EXPR
 *               |              |
 *             EXPR             1
 *               |
 *               2
 *  
 */
newExpression
	{String t = null;}
	:	"new" t=type
		(	LPAREN argList RPAREN
			(	{ getModeller().addAnonymousClass(t); }
				classBlock
				{ getModeller().popClassifier(); }
			)?

			//java 1.1
			// Note: This will allow bad constructs like
			//    new int[4][][3] {exp,exp}.
			//    There needs to be a semantic check here...
			// to make sure:
			//   a) [ expr ] and [ ] are not mixed
			//   b) [ expr ] and an init are not used together

		|	newArrayDeclarator (arrayInitializer)?
		)
	;

argList
	:	(	expressionList
		|	/*nothing*/
		)
	;

newArrayDeclarator
	:	(
			// CONFLICT:
			// newExpression is a primaryExpression which can be
			// followed by an array index reference.  This is ok,
			// as the generated code will stay in this loop as
			// long as it sees an LBRACK (proper behavior)
			options {
				warnWhenFollowAmbig = false;
			}
		:
			LBRACK
				(expression)?
			RBRACK
		)+
	;

constant
	:	NUM_INT
	|	CHAR_LITERAL
	|	STRING_LITERAL
	|	NUM_FLOAT
	;


//----------------------------------------------------------------------------
// The Java scanner
//----------------------------------------------------------------------------
class JavaLexer extends Lexer;

options {
	exportVocab=Java;      // call the vocabulary "Java"
	testLiterals=false;    // don't automatically test for literals
	k=4;                   // four characters of lookahead
//	charVocabulary='\u0003'..'\uFFFF';
}

{
    private StringBuffer whitespaceBuffer = new StringBuffer();

    /**
     * This method adds a whitespace string to the whitespace buffer
     *
     * @param ws The whitespace to add to the buffer
     */
    public void addWhitespace( String ws) {
        whitespaceBuffer.append( ws);
    }

    /**
     * This method returns the current whitespace buffer as a string
     * and reinitializes it.
     *
     * @return the current whitespace buffer as a string.
     */
    public String getWhitespaceBuffer() {
        String result = whitespaceBuffer.toString();

        whitespaceBuffer = new StringBuffer();
        return result;
    }

    /**
     * Override makeToken to store the whitespaces in the
     * special Argo tokens.
     */
    public Token makeToken(int t) {
        Token tok = super.makeToken(t);

        ((ArgoToken)tok).setWhitespace( getWhitespaceBuffer());

        return tok;
    }

    /**
     * A buffer to hold the last parsed javadoc comment.
     */
    String _javadocComment = null;

    /**
     * Store a parsed javadoc comment.
     *
     * @param comment The parsed javadoc comment.
     */
    protected void setJavadocComment(String comment) {
	_javadocComment = comment;
    }

    /**
     * Return (and consume) the last available Javadoc Comment.
     *
     * @return The last parsed javadoc comment.
     */
    protected String getJavadocComment() {
	String result = _javadocComment;

	_javadocComment = null;  // Since we consume the comment, the buffer is reset.

	return result;
    }
}     

// OPERATORS
QUESTION		:	'?'		;
LPAREN			:	'('		;
RPAREN			:	')'		;
LBRACK			:	'['		;
RBRACK			:	']'		;
LCURLY			:	'{'		;
RCURLY			:	'}'		;
COLON			:	':'		;
COMMA			:	','		;
//DOT			:	'.'		;
ASSIGN			:	'='		;
EQUAL			:	"=="	;
LNOT			:	'!'		;
BNOT			:	'~'		;
NOT_EQUAL		:	"!="	;
DIV				:	'/'		;
DIV_ASSIGN		:	"/="	;
PLUS			:	'+'		;
PLUS_ASSIGN		:	"+="	;
INC				:	"++"	;
MINUS			:	'-'		;
MINUS_ASSIGN	:	"-="	;
DEC				:	"--"	;
STAR			:	'*'		;
STAR_ASSIGN		:	"*="	;
MOD				:	'%'		;
MOD_ASSIGN		:	"%="	;
SR				:	">>"	;
SR_ASSIGN		:	">>="	;
BSR				:	">>>"	;
BSR_ASSIGN		:	">>>="	;
GE				:	">="	;
GT				:	">"		;
SL				:	"<<"	;
SL_ASSIGN		:	"<<="	;
LE				:	"<="	;
LT				:	'<'		;
BXOR			:	'^'		;
BXOR_ASSIGN		:	"^="	;
BOR				:	'|'		;
BOR_ASSIGN		:	"|="	;
LOR				:	"||"	;
BAND			:	'&'		;
BAND_ASSIGN		:	"&="	;
LAND			:	"&&"	;
SEMI			:	';'		;


// Whitespace -- ignored
WS	:	(	' '
		|	'\t'
		|	'\f'
		// handle newlines
		|	(	"\r\n"  // Evil DOS
			|	'\r'    // Macintosh
			|	'\n'    // Unix (the right way)
			)
			{ newline(); }
		)
		{ addWhitespace($getText);
		  $setType(Token.SKIP); }
	;

// Single-line comments
SL_COMMENT
	:	"//"
		(~('\n'|'\r'))* ('\n' | '\r'('\n')?)?
		{ addWhitespace($getText);
		  $setType(Token.SKIP);
		  newline(); }
	;

// javadoc comments
JAVADOC
	:	"/**"
		(	/*	'\r' '\n' can be matched in one alternative or by matching
				'\r' in one iteration and '\n' in another.  I am trying to
				handle any flavor of newline that comes in, but the language
				that allows both "\r\n" and "\r" and "\n" to all be valid
				newline is ambiguous.  Consequently, the resulting grammar
				must be ambiguous.  I'm shutting this warning off.
			 */
			options {
				generateAmbigWarnings=false;
			}
		:
			{ LA(2)!='/' }? '*'
		|	'\r' '\n'		{newline();}
		|	'\r'			{newline();}
		|	'\n'			{newline();}
		|	~('*'|'\n'|'\r')
		)*
		"*/"
		{ setJavadocComment($getText);
		  $setType(Token.SKIP); }
	;

// multiple-line comments
ML_COMMENT
	:	"/*"
		( /* Do not allow /** at start */
			options {
				generateAmbigWarnings=false;
			}
		:
			'\r' '\n'		{newline();}
		|	'\r'			{newline();}
		|	'\n'			{newline();}
		|	~('*'|'\n'|'\r')
		)		
		(	/*	'\r' '\n' can be matched in one alternative or by matching
				'\r' in one iteration and '\n' in another.  I am trying to
				handle any flavor of newline that comes in, but the language
				that allows both "\r\n" and "\r" and "\n" to all be valid
				newline is ambiguous.  Consequently, the resulting grammar
				must be ambiguous.  I'm shutting this warning off.
			 */
			options {
				generateAmbigWarnings=false;
			}
		:
			{ LA(2)!='/' }? '*'
		|	'\r' '\n'		{newline();}
		|	'\r'			{newline();}
		|	'\n'			{newline();}
		|	~('*'|'\n'|'\r')
		)*
		"*/"
		{ addWhitespace($getText);
		  $setType(Token.SKIP); }
	;

// character literals
CHAR_LITERAL
	:	'\'' ( ESC | ~'\'' ) '\''
	;

// string literals
STRING_LITERAL
	:	'"' (ESC|~('"'|'\\'))* '"'
	;


// escape sequence -- note that this is protected; it can only be called
//   from another lexer rule -- it will not ever directly return a token to
//   the parser
// There are various ambiguities hushed in this rule.  The optional
// '0'...'9' digit matches should be matched here rather than letting
// them go back to STRING_LITERAL to be matched.  ANTLR does the
// right thing by matching immediately; hence, it's ok to shut off
// the FOLLOW ambig warnings.
protected
ESC
	:	'\\'
		(	'n'
		|	'r'
		|	't'
		|	'b'
		|	'f'
		|	'"'
		|	'\''
		|	'\\'
		|	('u')+ HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT 
		|	('0'..'3')
			(
				options {
					warnWhenFollowAmbig = false;
				}
			:	('0'..'7')
				(	
					options {
						warnWhenFollowAmbig = false;
					}
				:	'0'..'7'
				)?
			)?
		|	('4'..'7')
			(
				options {
					warnWhenFollowAmbig = false;
				}
			:	('0'..'9')
			)?
		)
	;


// hexadecimal digit (again, note it's protected!)
protected
HEX_DIGIT
	:	('0'..'9'|'A'..'F'|'a'..'f')
	;


// a dummy rule to force vocabulary to be all characters (except special
//   ones that ANTLR uses internally (0 to 2)
protected
VOCAB
	:	'\3'..'\377'
	;


// an identifier.  Note that testLiterals is set to true!  This means
// that after we match the rule, we look in the literals table to see
// if it's a literal or really an identifer
IDENT
	options {testLiterals=true;}
	:	('a'..'z'|'A'..'Z'|'_'|'$') ('a'..'z'|'A'..'Z'|'_'|'0'..'9'|'$')*
	;


// a numeric literal
NUM_INT
	{boolean isDecimal=false;}
	:	'.' {_ttype = DOT;}
			(('0'..'9')+ (EXPONENT)? (FLOAT_SUFFIX)? { _ttype = NUM_FLOAT; })?
	|	(	'0' {isDecimal = true;} // special case for just '0'
			(	('x'|'X')
				(											// hex
					// the 'e'|'E' and float suffix stuff look
					// like hex digits, hence the (...)+ doesn't
					// know when to stop: ambig.  ANTLR resolves
					// it correctly by matching immediately.  It
					// is therefor ok to hush warning.
					options {
						warnWhenFollowAmbig=false;
					}
				:	HEX_DIGIT
				)+
			|	('0'..'7')+									// octal
			)?
		|	('1'..'9') ('0'..'9')*  {isDecimal=true;}		// non-zero decimal
		)
		(	('l'|'L')
		
		// only check to see if it's a float if looks like decimal so far
		|	{isDecimal}?
			(	'.' ('0'..'9')* (EXPONENT)? (FLOAT_SUFFIX)?
			|	EXPONENT (FLOAT_SUFFIX)?
			|	FLOAT_SUFFIX
			)
			{ _ttype = NUM_FLOAT; }
		)?
	;


// a couple protected methods to assist in matching floating point numbers
protected
EXPONENT
	:	('e'|'E') ('+'|'-')? ('0'..'9')+
	;


protected
FLOAT_SUFFIX
	:	'f'|'F'|'d'|'D'
	;





