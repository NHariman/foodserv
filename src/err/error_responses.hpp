#ifndef ERROR_RESPONSES_HPP
# define ERROR_RESPONSES_HPP

#define CRLF "\r\n"
#define STYLE_START "<style>"
#define IMG_CSS "img {\r\nwidth: 35%;\r\n height: auto;\r\n}\r\nbody{color:white;background-color:black;font-family:\'Trebuchet MS\';}"
#define KEYFRAME_SPIN "@keyframes spin {from {transform:rotate(0deg); }to {transform:rotate(360deg);}}"
#define SPIN_DIV ".spin {width: 5%;\r\nanimation-name: spin;animation-duration: 4000ms;animation-iteration-count: infinite;animation-timing-function: linear;}"
#define STYLE_END "</style>"
#define footer "<hr><center>foodserv 1.0<br><img src=\"www/img/beans_flip_gif.gif\" class=\"spin\"><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</center>\r\n</html>"

char*	GetServerErrorPage(int status_code);

#endif