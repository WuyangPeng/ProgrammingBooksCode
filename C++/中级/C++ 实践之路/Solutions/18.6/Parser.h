#if !defined (PARSER_H)
#define PARSER_H
// (c) Bartosz Milewski 2000
#include <memory>

class Node;
class Scanner;
class Calculator;

class Parser
{
public:
	Parser (Scanner & scanner, Calculator & calc);
	~Parser ();
	void Parse ();
	double Calculate () const;
private:
	std::auto_ptr<Node> Expr();
	std::auto_ptr<Node> Term();
	std::auto_ptr<Node> Factor();

	Scanner			  & _scanner;
	std::auto_ptr<Node>	_pTree;
	Calculator		  & _calc;
};

#endif
