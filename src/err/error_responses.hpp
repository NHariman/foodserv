#ifndef ERROR_RESPONSES_HPP
# define ERROR_RESPONSES_HPP

#define CRLF "\r\n"
#define footer "<hr><center>foodserv 1.0</center>\r\n</html>"
#define STYLE_START "<style>"
#define STYLE_END "</style>"
#define IMG_CSS "img {\r\nwidth: 80%;\r\n height: auto;\r\n}"


char*	GetServerErrorPage(int status_code);

#endif