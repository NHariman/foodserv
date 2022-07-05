### Request ABNF rules:
	HTTP-message = request-line *( header-field CRLF ) CRLF [ message-body ]
	|_ request-lin = method SP request-target SP HTTP-version CRLF
		|_ method =	token
		|_ request-target =	1*( "/" *pchar ) [ "?" query ] OR
							scheme ":" hier-part [ "?" query ] OR (only for proxy servers)
							[ userinfo "@" ] host [ ":" port ] OR (only for CONNECT requests)
							"*"" (only for OPTIONS requests)
			|_ pchar = unreserved / pct-encoded / sub-delims / ":" / "@" (see URI ABNF)
			|_ scheme =	ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
		|_ HTTP-version = HTTP-name "/" DIGIT "." DIGIT
			|_ HTTP-name = %x48.54.54.50 ; HTTP
		
	|_ header-field = field-name ":" OWS field-value OWS
		|_ field-name =		token
		|_ field-value =	*( field-content )

	|_ message-body = *OCTET


### Request target URI ABNF:
For origin servers:  

	request-target = 1*( "/" *pchar ) [ "?" query ]
	|_ pchar = unreserved / pct-encoded / sub-delims / ":" / "@"
				|_ unreserved =	ALPHA / DIGIT / "-" / "." / "_" / "~"
				|_ pct-encoded = "%" HEXDIG HEXDIG
					|_ HEXDIG = DIGIT / "A" / "B" / "C" / "D" / "E" / "F"
				|_ sub-delims =	"!" / "$" / "&" / "'" / "(" / ")"
								/ "*" / "+" / "," / ";" / "="
	|_ query = *( pchar / "/" / "?" )

Source: [unreserved](https://datatracker.ietf.org/doc/html/rfc3986#section-2.3),
[percent-encoding](https://datatracker.ietf.org/doc/html/rfc3986#section-2.1),
[subdelims](https://datatracker.ietf.org/doc/html/rfc3986#section-2.2),
[query](https://datatracker.ietf.org/doc/html/rfc3986#section-3.4)


### Query string in URI vs request body
> The form content is only encoded in the URL's query string when the form submission method is GET. The same encoding is used by default when the submission method is POST, but the result is submitted as the HTTP request body rather than being included in a modified URL.  

Source: [Query string wiki](https://en.wikipedia.org/wiki/Query_string)