#if !defined (CMD_H)
#define CMD_H
// Bartosz Milewski (c) 2000
#include "Util.h"
#include <map>

namespace Cmd
{
	enum Status
	{
		Disabled,		// Command not available
		Enabled,		// Command available
		Checked			// Command available and checkmarked
	};

	//-------------------
	// Vector of commands
	//-------------------

	class Vector
	{
	public:
		virtual ~Vector () {}
		int CmdToId (char const * cmdName) const;
		virtual void Execute (int cmdId) const = 0;
		virtual Status Test (char const * cmdName) const = 0;
	protected:

		typedef std::map<char const *, int, CstrCmp> CmdMap;

		CmdMap	_cmdMap;
	};

	template <class T>
	class Item
	{
	public:
		char const * _name;            // official name
		void (T::*_exec)();            // execute command
		Status (T::*_test)() const;    // test command status
		char const * _help;            // help string
	};

	template <class T>
	class VectorExec: public Vector
	{
	public:
		VectorExec (Cmd::Item<T> const * cmdTable, T * commander);
		void Execute (int cmdId) const;
		Status Test (char const * cmdName) const;
		char const * GetHelp (int cmdId) const;
	protected:
		T *						_commander;
		Cmd::Item<T> const *	_cmd;
	};


	template <class T>
	VectorExec<T>::VectorExec (Cmd::Item<T> const * cmdTable, T * commander)
		: _cmd (cmdTable), _commander (commander)
	{
		//Add command names to the map
		for (int j = 0; _cmd [j]._exec != 0; j++)
		{
			_cmdMap.insert (CmdMap::value_type (_cmd [j]._name, j));
		}
	}

	template <class T>
	void VectorExec<T>::Execute (int cmdId) const
	{
		assert (cmdId != -1);
		assert (_commander != 0);
		assert (_cmd [cmdId]._exec != 0);
		(_commander->*_cmd [cmdId]._exec)();
	}

	template <class T>
	Cmd::Status VectorExec<T>::Test (char const * cmd) const
	{
		assert (_commander != 0);
		int cmdId = CmdToId (cmd);
		assert (cmdId != -1);
		assert (_cmd [cmdId]._test != 0);
		return (_commander->*_cmd [cmdId]._test)();
	}

	template <class T>
	char const * VectorExec<T>::GetHelp (int cmdId) const
	{
		assert (cmdId != -1);
		return _cmd [cmdId]._help;
	}
}

#endif
