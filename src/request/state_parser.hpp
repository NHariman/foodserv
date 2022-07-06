#ifndef STATE_PARSER_HPP
#define STATE_PARSER_HPP

template <typename State>
class StateParser {
	public:		
		void	Parse(string const& input_string) {
			size_t i = 0;

			PreParseCheck();
			cur_state = SetStartState();
			while (NotDone(i)) {
				cur_state = GetNextState(input_string[i]);
				InvalidStateCheck();
				if (DoneStateCheck())
					break;
				UpdateBuffer(input_string[i]);
				IncrementCounter(i);
			}
			AfterParseCheck(i);
		}

	protected:
		// State	table[](char uri_char);
		State	cur_state;
		string	buffer;
		string	input;

		virtual State	SetStartState() const = 0;
		virtual State	GetNextState(char c) = 0;
		virtual void	InvalidStateCheck() const = 0;
		virtual bool	DoneStateCheck() = 0;
		virtual void	UpdateBuffer(char c) {
			buffer += c;
		}
		// Hooks are optional extensions points where subclasses can add actions.
		// They can be overriden by subclasses, but it's not mandatory since
		// the hooks already have default (but empty) implementation.
		// This hook is for if subclasses want to use a different stopping point.
		bool			NotDone(size_t pos) const {
			return (pos <= input.size());
		}
		// Hook for if subclasses want custom incrementation steps.
		void			IncrementCounter(size_t& pos) {
			pos += 1;
		}
		// Hook for checks before entering parsing loop, e.g. if input string exceeds max allowed size.
		virtual void	PreParseCheck() const {};
		// Hook for checks after parsing, e.g. if there are characters after end state has been reached.
		virtual void	AfterParseCheck(size_t pos) const { (void)pos; };
};

#endif /* STATE_PARSER_HPP */
