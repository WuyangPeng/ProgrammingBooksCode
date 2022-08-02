// (c) Bartosz Milewski 2000
#include <iostream>

class IStack {};

class StackSeq
{
public:
	StackSeq (IStack const & stack) : _stack (stack), _done (false)
	{
		std::cout << "Stack sequencer created\n";
	}
	bool AtEnd () const { return _done; }
	void Advance () { _done = true; }
	int GetNum () const { return 13; }
private:
	IStack const &  _stack;
	bool            _done;
};

class Input
{
public:
	Input ()
	{
		std::cout << "Input created\n";
	}
};

class Calculator
{
public:
	Calculator () : _done (false)
	{
		std::cout << "Calculator created\n";
	}
	bool Execute (Input& input)
	{
		std::cout << "Calculator::Execute\n";
		return !_done;
	}
	IStack const & GetStack () //const
	{
		_done = true;
		return _stack;
	}
private:
	IStack  _stack;
	bool    _done;
};

int main ()
{
	Calculator TheCalculator;
	bool status;
	do
	{
		// Prompt for input
		std::cout << "> ";
		Input input;
		status = TheCalculator.Execute (input);
		if (status)
		{
			for (StackSeq seq (TheCalculator.GetStack ());
				 !seq.AtEnd ();
				 seq.Advance () )
			{
				std::cout << "    " << seq.GetNum () << std::endl;
			}
		}
	} while (status);
}
