#if !defined (EXCEPTION_H)
#define EXCEPTION_H
// (c) Bartosz Milewski 2000
#include <string>

namespace Win
{
	class Exception
	{
	public:
		Exception (std::string const & msg,
				   std::string const & objName = std::string (),
				   unsigned long err = 0);
		Exception (std::string const & msg, Exception const & e);
		Exception ()
			: _err (0)
		{}

		unsigned long GetError () const { return _err; }
		std::string const & GetMessage () const { return _msg; }
		std::string const & GetObjectName () const { return _objName; }

	protected:
		unsigned long	_err;
		std::string		_msg;
		std::string		_objName;
	};

	class ExitException
	{
	};
}

#endif
