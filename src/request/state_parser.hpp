#ifndef STATE_PARSER_HPP
#define STATE_PARSER_HPP

template <typename State>
class StateParser {
	public:		
		void	Parse(string const& input_string) {
			size_t i;

			PreParseCheck();
			cur_state = SetStartState();
			for (i = 0; i <= input_string.size(); i++) {
				cur_state = GetNextState(input_string[i]);
				InvalidStateCheck();
				if (DoneStateCheck())
					break;
				UpdateBuffer(input_string[i]);
			}
			AfterParseCheck(i);
		}

	protected:
		// State	table[](char uri_char);
		State	cur_state;
		string	buffer;

		virtual State	SetStartState() const = 0;
		virtual State	GetNextState(char c) = 0;
		virtual void	InvalidStateCheck() const = 0;
		virtual bool	DoneStateCheck() = 0;
		virtual void	UpdateBuffer(char c) {
			buffer += c;
		}
		// Hooks may be overriden by subclasses, but it's not mandatory since
		// the hooks already have default (but empty) implementation.
		// This hook is for checks before entering parsing loop, e.g. if input string exceeds max allowed size.
		virtual void	PreParseCheck() const {};
		// This hook is for checks after parsing, e.g. if there are characters after end state has been reached.
		virtual void	AfterParseCheck(size_t pos) const { (void)pos; };
};

#endif /* STATE_PARSER_HPP */
