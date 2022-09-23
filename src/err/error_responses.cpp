#include "error_responses.hpp"

// https://github.com/nginx/nginx/blob/release-1.15.8/src/http/ngx_http_special_response.c

static char foodserv_http_error_301_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>301 Moved Permanently</title></head>" CRLF
"<body>" CRLF
"<center><h1>301 Moved Permanently</h1></center>" CRLF
"<center><img src=\"https://http.cat/301\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_302_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>302 Found</title></head>" CRLF
"<body>" CRLF
"<center><h1>302 Found</h1></center>" CRLF
"<center><img src=\"https://http.cat/302\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_303_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>303 See Other</title></head>" CRLF
"<body>" CRLF
"<center><h1>303 See Other</h1></center>" CRLF
"<center><img src=\"https://http.cat/303\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_307_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>307 Temporary Redirect</title></head>" CRLF
"<body>" CRLF
"<center><h1>307 Temporary Redirect</h1></center>" CRLF
"<center><img src=\"https://http.cat/307\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_308_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>308 Permanent Redirect</title></head>" CRLF
"<body>" CRLF
"<center><h1>308 Permanent Redirect</h1></center>" CRLF
"<center><img src=\"https://http.cat/308\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_400_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>400 Bad Request</title></head>" CRLF
"<body>" CRLF
"<center><h1>400 Bad Request</h1></center>" CRLF
"<center><img src=\"https://http.cat/309\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_401_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>401 Authorization Required</title></head>" CRLF
"<body>" CRLF
"<center><h1>401 Authorization Required</h1></center>" CRLF
"<center><img src=\"https://http.cat/401\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_402_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>402 Payment Required</title></head>" CRLF
"<body>" CRLF
"<center><h1>402 Payment Required</h1></center>" CRLF
"<center><img src=\"https://http.cat/402\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_403_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>403 Forbidden</title></head>" CRLF
"<body>" CRLF
"<center><h1>403 Forbidden</h1></center>" CRLF
"<center><img src=\"https://http.cat/403\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_404_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>404 Not Found</title></head>" CRLF
"<body>" CRLF
"<center><h1>404 Not Found</h1></center>" CRLF
"<center><img src=\"https://http.cat/404\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_405_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>405 Not Allowed</title></head>" CRLF
"<body>" CRLF
"<center><h1>405 Not Allowed</h1></center>" CRLF
"<center><img src=\"https://http.cat/405\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_406_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>406 Not Acceptable</title></head>" CRLF
"<body>" CRLF
"<center><h1>406 Not Acceptable</h1></center>" CRLF
"<center><img src=\"https://http.cat/406\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_408_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>408 Request Timeout</title></head>" CRLF
"<body>" CRLF
"<center><h1>408 Request Timeout</h1></center>" CRLF
"<center><img src=\"https://http.cat/408\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_409_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>409 Conflict</title></head>" CRLF
"<body>" CRLF
"<center><h1>409 Conflict</h1></center>" CRLF
"<center><img src=\"https://http.cat/409\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_410_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>410 Gone</title></head>" CRLF
"<body>" CRLF
"<center><h1>410 Gone</h1></center>" CRLF
"<center><img src=\"https://http.cat/410\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_411_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>411 Length Required</title></head>" CRLF
"<body>" CRLF
"<center><h1>411 Length Required</h1></center>" CRLF
"<center><img src=\"https://http.cat/411\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_412_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>412 Precondition Failed</title></head>" CRLF
"<body>" CRLF
"<center><h1>412 Precondition Failed</h1></center>" CRLF
"<center><img src=\"https://http.cat/412\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_413_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>413 Payload Too Large</title></head>" CRLF
"<body>" CRLF
"<center><h1>413 Payload Too Large</h1></center>" CRLF
"<center><img src=\"https://http.cat/413\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_414_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>414 URI Too Long</title></head>" CRLF
"<body>" CRLF
"<center><h1>414 URI Too Long</h1></center>" CRLF
"<center><img src=\"https://http.cat/414\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_415_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>415 Unsupported Media Type</title></head>" CRLF
"<body>" CRLF
"<center><h1>415 Unsupported Media Type</h1></center>" CRLF
"<center><img src=\"https://http.cat/415\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_416_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>416 Requested Range Not Satisfiable</title></head>" CRLF
"<body>" CRLF
"<center><h1>416 Requested Range Not Satisfiable</h1></center>" CRLF
"<center><img src=\"https://http.cat/416\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_417_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>417 Expectation Failed</title></head>" CRLF
"<body>" CRLF
"<center><h1>417 Expectation Failed</h1></center>" CRLF
"<center><img src=\"https://http.cat/417\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_421_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>421 Misdirected Request</title></head>" CRLF
"<body>" CRLF
"<center><h1>421 Misdirected Request</h1></center>" CRLF
"<center><img src=\"https://http.cat/421\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_429_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>429 Too Many Requests</title></head>" CRLF
"<body>" CRLF
"<center><h1>429 Too Many Requests</h1></center>" CRLF
"<center><img src=\"https://http.cat/429\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_431_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>431 Request Header Fields Too Large</title></head>" CRLF
"<body>" CRLF
"<center><h1>431 Request Header Fields Too Large</h1></center>" CRLF
"<center><img src=\"https://http.cat/431\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_500_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>500 Internal Server Error</title></head>" CRLF
"<body>" CRLF
"<center><h1>500 Internal Server Error</h1></center>" CRLF
"<center><img src=\"https://http.cat/500\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_501_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>501 Not Implemented</title></head>" CRLF
"<body>" CRLF
"<center><h1>501 Not Implemented</h1></center>" CRLF
"<center><img src=\"https://http.cat/501\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_502_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>502 Bad Gateway</title></head>" CRLF
"<body>" CRLF
"<center><h1>502 Bad Gateway</h1></center>" CRLF
"<center><img src=\"https://http.cat/502\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_503_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>503 Service Temporarily Unavailable</title></head>" CRLF
"<body>" CRLF
"<center><h1>503 Service Temporarily Unavailable</h1></center>" CRLF
"<center><img src=\"https://http.cat/503\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_504_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>504 Gateway Timeout</title></head>" CRLF
"<body>" CRLF
"<center><h1>504 Gateway Timeout</h1></center>" CRLF
"<center><img src=\"https://http.cat/504\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_505_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>505 HTTP Version Not Supported</title></head>" CRLF
"<body>" CRLF
"<center><h1>505 HTTP Version Not Supported</h1></center>" CRLF
"<center><img src=\"https://http.cat/505\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_507_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>507 Insufficient Storage</title></head>" CRLF
"<body>" CRLF
"<center><h1>507 Insufficient Storage</h1></center>" CRLF
"<center><img src=\"https://http.cat/507\"></center>" CRLF
footer CRLF
;


static char foodserv_http_error_unknown_page[] =
STYLE_START CRLF
IMG_CSS CRLF
STYLE_END CRLF
"<html>" CRLF
"<head><title>Unknown Status Code</title></head>" CRLF
"<body>" CRLF
"<center><h1>Unknown Status Code</h1></center>" CRLF
"<center><img src=\"img/cat_thonk.jpg\"></center>" CRLF
footer CRLF
;


char*	GetServerErrorPage(int status_code) {
	switch (status_code) {
		case 301: return foodserv_http_error_301_page;
		case 302: return foodserv_http_error_302_page;
		case 303: return foodserv_http_error_303_page;
		case 307: return foodserv_http_error_307_page;
		case 308: return foodserv_http_error_308_page;
		case 400: return foodserv_http_error_400_page;
		case 401: return foodserv_http_error_401_page;
		case 402: return foodserv_http_error_402_page;
		case 403: return foodserv_http_error_403_page;
		case 404: return foodserv_http_error_404_page;
		case 405: return foodserv_http_error_405_page;
		case 406: return foodserv_http_error_406_page;
		case 408: return foodserv_http_error_408_page;
		case 409: return foodserv_http_error_409_page;
		case 410: return foodserv_http_error_410_page;
		case 411: return foodserv_http_error_411_page;
		case 412: return foodserv_http_error_412_page;
		case 413: return foodserv_http_error_413_page;
		case 414: return foodserv_http_error_414_page;
		case 415: return foodserv_http_error_415_page;
		case 416: return foodserv_http_error_416_page;
		case 417: return foodserv_http_error_417_page;
		case 421: return foodserv_http_error_421_page;
		case 429: return foodserv_http_error_429_page;
		case 431: return foodserv_http_error_431_page;
		case 500: return foodserv_http_error_500_page;
		case 501: return foodserv_http_error_501_page;
		case 502: return foodserv_http_error_502_page;
		case 503: return foodserv_http_error_503_page;
		case 504: return foodserv_http_error_504_page;
		case 505: return foodserv_http_error_505_page;
		case 507: return foodserv_http_error_507_page;
		default: return foodserv_http_error_unknown_page;
	}
}
