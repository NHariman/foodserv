#ifndef ASTATE_PARSER_HPP
#define ASTATE_PARSER_HPP

#include <iostream>

using namespace std;

// An abstract class template that defines the state parsing algorithm
// as a template method, complete with hooks and abstract methods to be
// implemented by the subclasses.
// `State` template parameter refers to type of states, e.g. an enum.
// The state parsing algorithm itself is made for parsing strings byte-by-byte.

template <typename State>
class AStateParser {
	public:
		// Constructor taking starting state for initialization.
		// Child classes should call it in constructor like so:
		//		ChildClassParser::ChildClassParser() : AStateParser(c_StartEnum)
		AStateParser(State starting_state, State ending_state)
			:	start_state(starting_state),
				end_state(ending_state),
				cur_state(starting_state),
				skip_char(false) {}

		// Template method
		// Takes string to parse and returns bytes read.
		size_t	ParseString(string const& input_string) {
			InitParser(input_string); // reset counters for repeat calls
			PreParseCheck();
			while (NotDone(pos)) {
				cur_state = GetNextState(pos);
				UpdateBuffer(pos);
				CheckInvalidState();
				if (CheckDoneState())
					break;
				IncrementCounter();
			}
			AfterParseCheck();
			return pos;
		}

		// For external classes to check if parsing has been completed.
		bool	IsDone() { return CheckDoneState(); }

	protected:
		State	start_state;
		State	end_state;
		State	cur_state;
		string	buffer; // for keeping track of parsed input
		string	input; // saving original input
		size_t	pos; // n. of bytes read
		bool	skip_char; // for skipping pushing whitespace/EOL to buffer

		// Abstract methods that must be implemented by subclass.
		virtual State	GetNextState(size_t pos) = 0;
		virtual void	CheckInvalidState() const = 0;

		// Concrete methods that can be overridden if custom looping behaviour
		// is needed.
		virtual void	InitParser(string const& input_string) {
			input = input_string;
			skip_char = false;
			pos = 0;
		}
		virtual bool	NotDone(size_t pos) const {
			return (pos <= input.size() && cur_state != end_state);
		}
		virtual void	UpdateBuffer(size_t pos) {
			if (!skip_char)
				buffer += input[pos];
		}
		virtual bool	CheckDoneState() { return (cur_state == end_state); }
		virtual void	IncrementCounter() { pos += 1; }

		// Hooks. Optional extensions points where subclasses can add actions.
		// They can be overriden by subclasses, but it's not mandatory since
		// the hooks already have default (but empty) implementation.
		// This hook is for if subclasses want to use a different stopping point.
		// This is for checks before entering parsing loop, e.g. if input string
		// exceeds max allowed size.
		virtual void	PreParseCheck() {};
		// This is for checks after parsing, e.g. if there are characters after
		// end state has been reached.
		virtual void	AfterParseCheck() {};
};

#endif /* ASTATE_PARSER_HPP */
