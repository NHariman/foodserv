#ifndef ERROR_RESPONSES_HPP
# define ERROR_RESPONSES_HPP

#define CRLF "\r\n"
#define footer "<hr><center>foodserv 1.0</center>\r\n</html>"

char*	GetServerErrorPage(int status_code);

#endif