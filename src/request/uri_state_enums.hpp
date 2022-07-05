#ifndef URI_STATE_ENUMS_HPP
#define URI_STATE_ENUMS_HPP

enum URIPart {
	pt_Host = 0,
	pt_Path,
	pt_Query
};

enum URIState {
	u_Start = 0,
	u_Path,
	u_Query,
	u_Percent,
	u_Percent_Done,
	u_Done,
	u_Invalid
};

#endif /* URI_STATE_ENUMS_HPP */
