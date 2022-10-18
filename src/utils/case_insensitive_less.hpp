#include <cctype>
#include <string>

// Used by HTTPMessage class for header fields map as 3rd template parameter.
// Allows for case-insensitive searching of header fields.
struct	case_insensitive_less {
	struct	ci_compare_less {
		bool	operator() (unsigned char const& c1, unsigned char const& c2) const {
			return tolower(c1) < tolower(c2);
		}
	};
	bool	operator()(std::string const& s1, std::string const& s2) const {
		return std::lexicographical_compare(s1.begin(), s1.end(),
											s2.begin(), s2.end(),
											ci_compare_less());
	}
};
