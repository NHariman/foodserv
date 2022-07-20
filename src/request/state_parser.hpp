#ifndef STATE_PARSER_HPP
#define STATE_PARSER_HPP

#include <iostream>

using namespace std;

template <typename State>
class StateParser {
	public:
		// State parsing algorithm defined as a template method.
		// Takes string to parse (byte-by-byte) and returns bytes read.
		size_t	ParseString(string const& input_string) {
			size_t i = 0;

			input = input_string;
			PreParseCheck();
			cur_state = SetStartState();
			while (NotDone(i)) {
				cur_state = GetNextState(i);
				InvalidStateCheck();
				if (DoneStateCheck())
					break;
				UpdateBuffer(i);
				IncrementCounter(i);
			}
			AfterParseCheck(i);
			return i;
		}

	protected:
		State	cur_state;
		string	buffer;
		string	input;

		virtual State	SetStartState() const = 0;
		virtual State	GetNextState(size_t pos) = 0;
		virtual void	InvalidStateCheck() const = 0;
		virtual bool	DoneStateCheck() = 0;
		virtual void	UpdateBuffer(size_t pos) {
			buffer += input[pos];
		}
		// Hooks are optional extensions points where subclasses can add actions.
		// They can be overriden by subclasses, but it's not mandatory since
		// the hooks already have default (but empty) implementation.
		// This hook is for if subclasses want to use a different stopping point.
		virtual bool			NotDone(size_t pos) const {
			return (pos <= input.size());
		}
		// Hook for if subclasses want custom incrementation steps.
		virtual void			IncrementCounter(size_t& pos) {
			pos += 1;
		}
		// Hook for checks before entering parsing loop, e.g. if input string exceeds max allowed size.
		virtual void	PreParseCheck() {};
		// Hook for checks after parsing, e.g. if there are characters after end state has been reached.
		virtual void	AfterParseCheck(size_t pos) { (void)pos; };
};

#endif /* STATE_PARSER_HPP */
