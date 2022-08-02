#include "Parser.h"
// (c) Bartosz Milewski 2000
#include "Scanner.h"
#include "Nodes.h"
#include "Calc.h"
#include "Output.h"
#include "SyntaxErr.h"
#include <sstream>

Parser::Parser (Scanner & scanner, Calculator & calc)
  : _scanner (scanner), 
	_calc (calc)
{}

Parser::~Parser ()
{}

void Parser::Parse ()
{
	// Everything is an expression
	_pTree = Expr ();
	if (!_scanner.IsDone ())
		throw Syntax ();
}

double Parser::Calculate () const
{
	assert (_pTree.get () != 0);
	return _pTree->Calc ();
}

std::auto_ptr<Node> Parser::Expr ()
{
	std::auto_ptr<Node> pNode = Term ();

	EToken token = _scanner.Token ();
	if (token == tPlus || token == tMinus)
	{
		// Expr := Term { ('+' | '-') Term }
		std::auto_ptr<MultiNode> pMultiNode (
					new SumNode (pNode));
		do
		{
			_scanner.Accept ();
			std::auto_ptr<Node> pRight = Term ();
			pMultiNode->AddChild (pRight, (token == tPlus));
			token = _scanner.Token ();
		} while (token == tPlus || token == tMinus);
		// with member template support
		pNode = pMultiNode; // <- Up-casting!
	}
	else if (token == tAssign)
	{
		// Expr := Term = Expr
		_scanner.Accept ();
		std::auto_ptr<Node> pRight = Expr ();
		// provided the Term is an lvalue
		if (pNode->IsLvalue ())
		{
			pNode = std::auto_ptr<Node> (
							new AssignNode (pNode, pRight));
		}
		else
		{
			throw Syntax ("The left-hand side of an assignment must be a variable.");
		}
	}
	return pNode;
}

std::auto_ptr<Node> Parser::Term ()
{
	std::auto_ptr<Node> pNode = Factor ();
	EToken token = _scanner.Token ();
	if (token == tMult || token == tDivide)
	{
		// Term := Factor { ('*' | '/') Factor }
		std::auto_ptr<MultiNode> pMultiNode (new ProductNode (pNode));
		do
		{
			_scanner.Accept ();
			std::auto_ptr<Node> pRight = Factor ();
			pMultiNode->AddChild (pRight, (token == tMult));
			token = _scanner.Token ();
		} while (token == tMult || token == tDivide);
		pNode = pMultiNode;
	}
	return pNode;
}

std::auto_ptr<Node> Parser::Factor ()
{
	std::auto_ptr<Node> pNode;
	EToken token = _scanner.Token ();

	if (token == tLParen)
	{
		_scanner.Accept (); // accept '('
		pNode = Expr ();
		if (_scanner.Token() == tRParen)
			_scanner.Accept (); // accept ')'
		else
			throw Syntax ("Missing parenthesis.");
	}
	else if (token == tNumber)
	{
		pNode = std::auto_ptr<Node> (new NumNode (_scanner.Number ()));
		_scanner.Accept ();
	}
	else if (token == tIdent)
	{
		std::string strSymbol = _scanner.GetSymbolName (); 
		std::size_t id = _calc.FindSymbol (strSymbol);
		_scanner.Accept ();
		if (_scanner.Token () == tLParen) // function call
		{
			_scanner.Accept (); // accept '('
			pNode = Expr ();
			assert (pNode.get () != 0);
			if (_scanner.Token () == tRParen)
				_scanner.Accept (); // accept ')'
			else
				throw Syntax ("Missing parentesis in a function call.");
			if (id != SymbolTable::idNotFound && _calc.IsFunction (id))
			{
				pNode = std::auto_ptr<Node> (
					new FunNode (_calc.GetFun (id), pNode));
			}
			else
			{
				std::ostringstream out;
				out << "Unknown function \"";
				out << strSymbol << "\"";
				throw Syntax (out.str ());
			}
		}
		else
		{
			// Factor := Ident
			if (id == SymbolTable::idNotFound)
			{
				id = _calc.AddSymbol (strSymbol);
			}
			pNode = std::auto_ptr<Node> (new VarNode (id, _calc.GetStore ()));
		}
	}
	else if (token == tMinus) // unary minus
	{
		_scanner.Accept (); // accept minus
		pNode = Factor ();
		pNode = std::auto_ptr<Node> (new UMinusNode (pNode));
	}
	else
	{
		throw Syntax ("Not a valid expression.");
	}
	return pNode;
}
