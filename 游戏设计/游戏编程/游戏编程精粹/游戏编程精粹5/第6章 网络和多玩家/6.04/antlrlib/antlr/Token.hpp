#ifndef INC_Token_hpp__
#define INC_Token_hpp__

/* ANTLR Translator Generator
 * Project led by Terence Parr at http://www.jGuru.com
 * Software rights: http://www.antlr.org/license.html
 *
 * $Id: //depot/code/org.antlr/release/antlr-2.7.4/lib/cpp/antlr/Token.hpp#1 $
 */

#include <config.hpp>
#include <RefCount.hpp>
#include <string>

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr {
#endif

/** A token is minimally a token type.  Subclasses can add the text matched
 *  for the token and line info.
 */

class ANTLR_API Token;
typedef RefCount<Token> RefToken;

class ANTLR_API Token {
public:
	// constants
#ifndef NO_STATIC_CONSTS
	static const int MIN_USER_TYPE = 4;
	static const int NULL_TREE_LOOKAHEAD = 3;
	static const int INVALID_TYPE = 0;
	static const int EOF_TYPE = 1;
	static const int SKIP = -1;
#else
	enum {
		MIN_USER_TYPE = 4,
		NULL_TREE_LOOKAHEAD = 3,
		INVALID_TYPE = 0,
		EOF_TYPE = 1,
		SKIP = -1
	};
#endif

	// each Token has at least a token type
	int type; //=INVALID_TYPE;

public:
	// the illegal token object
	static RefToken badToken; // = new Token(INVALID_TYPE, "<no text>");

	Token();
	Token(int t);
	Token(int t, const ANTLR_USE_NAMESPACE(std)string& txt);

	virtual int getColumn() const;
	virtual int getLine() const;
	virtual ANTLR_USE_NAMESPACE(std)string getText() const;
	virtual int getType() const;

	virtual void setColumn(int c);

	virtual void setLine(int l);
	virtual void setText(const ANTLR_USE_NAMESPACE(std)string& t);
	virtual void setType(int t);

	virtual ANTLR_USE_NAMESPACE(std)string toString() const;

	virtual ~Token();
private:
	Token(const Token&);
	const Token& operator=(const Token&);
};

extern ANTLR_API RefToken nullToken;

#ifdef NEEDS_OPERATOR_LESS_THAN
// RK: Added after 2.7.2 previously it was undefined.
// AL: what to return if l and/or r point to nullToken???
inline bool operator<( RefToken l, RefToken r )
{
	return nullToken == l ? ( nullToken == r ? false : true ) : l->getType() < r->getType();
}
#endif

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
#endif

#endif //INC_Token_hpp__
