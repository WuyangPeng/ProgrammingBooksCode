#ifndef INC_NoViableAltForCharException_hpp__
# define INC_NoViableAltForCharException_hpp__

/* ANTLR Translator Generator
 * Project led by Terence Parr at http://www.jGuru.com
 * Software rights: http://www.antlr.org/license.html
 *
 * $Id: //depot/code/org.antlr/release/antlr-2.7.4/lib/cpp/antlr/NoViableAltForCharException.hpp#1 $
 */

# include <config.hpp>
# include <RecognitionException.hpp>
# include <CharScanner.hpp>

# ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr
{
# endif

class ANTLR_API NoViableAltForCharException : public RecognitionException
{
public:
	NoViableAltForCharException(int c, CharScanner* scanner);
	NoViableAltForCharException(int c, const ANTLR_USE_NAMESPACE(std)string& fileName_,
										 int line_, int column_);

	virtual ~NoViableAltForCharException() throw()
	{
	}

	/// Returns a clean error message (no line number/column information)
	ANTLR_USE_NAMESPACE(std)string getMessage() const;
protected:
	int foundChar;
};

# ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
# endif

#endif //INC_NoViableAltForCharException_hpp__
