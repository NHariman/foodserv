#ifndef URI_STATE_ENUMS_HPP
#define URI_STATE_ENUMS_HPP

enum URIPart {
	pt_Host = 1,
	pt_Path,
	pt_Query
};

enum URIState {
	st_Start = 0,
	st_Path,
	st_Percent,
	st_Percent_Done,
	st_Query,
	st_Done,
	st_Invalid
};

#endif /* URI_STATE_ENUMS_HPP */
