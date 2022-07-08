# Highlights from RFC 7230

# Request

## Structure

### Structure of a request:
> A client sends an HTTP request to a server in the form of a request  message, beginning with a request-line that includes a method, URI, and protocol version (Section 3.1.1), followed by header fields containing request modifiers, client information, and representation metadata (Section 3.2), an empty line to indicate the end of the header section, and finally a message body containing the payload body (if any, Section 3.3).  

Source:
[Section 2.1](https://datatracker.ietf.org/doc/html/rfc7230#section-2.1)
<br/><br/>

> The following example illustrates a typical message exchange for a GET request (Section 4.3.1 of [RFC7231]) on the URI "http://www.example.com/hello.txt":

   Client request:

     GET /hello.txt HTTP/1.1
     User-Agent: curl/7.16.3 libcurl/7.16.3 OpenSSL/0.9.7l zlib/1.2.3
     Host: www.example.com
     Accept-Language: en, mi


   Server response:

     HTTP/1.1 200 OK
     Date: Mon, 27 Jul 2009 12:28:53 GMT
     Server: Apache
     Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT
     ETag: "34aa387-d-1568eb00"
     Accept-Ranges: bytes
     Content-Length: 51
     Vary: Accept-Encoding
     Content-Type: text/plain

     Hello World! My payload includes a trailing CRLF.

Example request message for sending the result of a form:  

    POST /contact_form.php HTTP/1.1
    Host: developer.mozilla.org
    Content-Length: 64
    Content-Type: application/x-www-form-urlencoded

    name=Joe%20User&request=Send%20me%20one%20of%20your%20catalogue
<br/><br/>

### Field order:
>  it is good practice to send header fields that contain control data first, such as Host on requests and Date on responses, so that implementations can decide when not to handle a message as early as possible.  
A server MUST NOT apply a request to the target resource until the entire request header section is received, since later header fields might include conditionals, authentication credentials, or deliberately misleading duplicate header fields that would impact request processing.  

Source:
[Section 3.2.2](https://datatracker.ietf.org/doc/html/rfc7230#section-3.2.2)
<br/><br/>


## Parsing

### Method of parsing request message:
> The normal procedure for parsing an HTTP message is to read the start-line into a structure, read each header field into a hash table by field name until the empty line, and then use the parsed data to determine if a message body is expected.  
If a message body has been indicated, then it is read as a stream until an amount of octets equal to the message body length is read or the connection is closed. 

Source: [Section 3](https://www.rfc-editor.org/rfc/rfc7230#section-3)
<br/><br/>

### Field Parsing:
>  Messages are parsed using a generic algorithm, independent of the individual header field names.  The contents within a given field value are not parsed until a later stage of message interpretation (usually after the message's entire header section has been processed).  

Source:
[Section 3.2.4](https://datatracker.ietf.org/doc/html/rfc7230#section-3.2.4)
<br/><br/>


## Formatting

### Request-line formatting:
> A request-line begins with a method token, followed by a single space (SP), the request-target, another single space (SP), the protocol version, and ends with CRLF.  

Source:
[Section 3.1.1](https://datatracker.ietf.org/doc/html/rfc7230#section-3.1.1)

> request-line and status-line grammar rules require that each of the component elements be separated by a single SP octet  

Source:
[Section 3.5](https://datatracker.ietf.org/doc/html/rfc7230#section-3.5)
<br/><br/>

### Request Target formatting:
>  When making a request directly to an origin server [...] a client MUST send only the absolute path and query components of the target URI as the request-target.  
If the target URI's path component is empty, the client MUST send "/" as the path within the origin-form of request-target.  A Host header field is also sent, as defined in Section 5.4.  

    origin-form = absolute-path [ "?" query ]
    |_ absolute-path = 1*( "/" *pchar )
    |_ query = *( pchar / "/" / "?" )

> For example, a client wishing to retrieve a representation of the resource identified as  
http://www.example.org/where?q=now  
directly from the origin server would open (or reuse) a TCP connection to port 80 of the host "www.example.org" and send the lines:

    GET /where?q=now HTTP/1.1  
    Host: www.example.org  


Source:
[Section 5.3.1](https://datatracker.ietf.org/doc/html/rfc7230#section-5.3.1)
<br/><br/>

### Header field formatting:
>  Each header field consists of a case-insensitive field name followed by a colon (":"), optional leading whitespace, the field value, and optional trailing whitespace.  

Source:
[Section 3.2](https://datatracker.ietf.org/doc/html/rfc7230#section-3.2)
<br/><br/>

### Header line breaks:  
[HTTP header line break style](https://stackoverflow.com/questions/5757290/http-header-line-break-style)
> The line terminator for message-header fields is the sequence CRLF. However, we recommend that applications, when parsing such headers, recognize a single LF as a line terminator and ignore the leading CR.  

Source: [RFC 2616 Section 19.3](https://www.rfc-editor.org/rfc/rfc2616#section-19.3)  

> An HTTP/1.1 user agent MUST NOT preface or follow a request with an extra CRLF.  
If terminating the request message body with a line-ending is desired, then the user agent MUST count the terminating CRLF octets as part of the message body length.  
In the interest of robustness, a server that is expecting to receive and parse a request-line SHOULD ignore at least one empty line (CRLF) received prior to the request-line.  

Source: [Section 3.5](https://www.rfc-editor.org/rfc/rfc7230#section-3.5)  
<br/><br/>


## Length limitations

### Request-line length:
> It is RECOMMENDED that all HTTP senders and recipients support, at a minimum, request-line lengths of 8000 octets.  
HTTP does not place a predefined limit on the length of a request-line, as described in Section 2.5.  A server that receives a method longer than any that it implements SHOULD respond with a 501 (Not Implemented) status code.  

> A server that receives a request-target longer than any URI it wishes to parse MUST respond with a 414 (URI Too Long) status code (see Section 6.5.12 of [RFC7231]).  

Source:
[Section 3.1.1](https://datatracker.ietf.org/doc/html/rfc7230#section-3.1.1)
<br/><br/>

### Field limits:
>  A server that receives a request header field, or set of fields, larger than it wishes to process MUST respond with an appropriate 4xx (Client Error) status code.  Ignoring such header fields would increase the server's vulnerability to request smuggling attacks.  

Source:
[Section 3.2.5](https://datatracker.ietf.org/doc/html/rfc7230#section-3.2.5)
<br/><br/>


## Errors

### Invalid requests & how to respond:
> When a server listening only for HTTP request messages [...] receives a sequence of octets that does not match the HTTP-message grammar aside from the robustness exceptions listed above, the server SHOULD respond with a 400 (Bad Request) response.

Source:
[Section 3.5](https://datatracker.ietf.org/doc/html/rfc7230#section-3.5)

> Recipients of an invalid request-line SHOULD respond with either a 400 (Bad Request) error or a 301 (Moved Permanently) redirect with the request-target properly encoded.  
A recipient SHOULD NOT attempt to autocorrect and then process the request without a redirect, since the invalid request-line might be deliberately crafted to bypass security filters along the request chain.  

Source:
[Section 3.1.1](https://datatracker.ietf.org/doc/html/rfc7230#section-3.1.1)

> A sender MUST NOT generate an "http" URI with an empty host identifier. A recipient that processes such a URI reference MUST reject it as invalid.

Source:
[Section 2.7.1](https://datatracker.ietf.org/doc/html/rfc7230#section-2.7.1)
<br/><br/>

### Field formatting:
> No whitespace is allowed between the header field-name and colon. [...] A server MUST reject any received request message that contains whitespace between a header field-name and colon with a response code of 400 (Bad Request).  

Source:
[Section 3.2.4](https://datatracker.ietf.org/doc/html/rfc7230#section-3.2.4)
<br/><br/>

### Transfer-Encoding:
>  If a Transfer-Encoding header field is present in a request and the chunked transfer coding is not the final encoding, the message body length cannot be determined reliably; the server MUST respond with the 400 (Bad Request) status code and then close the connection..  

>  If a message is received without Transfer-Encoding and with either multiple Content-Length header fields having differing field-values or a single Content-Length header field having an invalid value, then the message framing is invalid and the recipient MUST treat it as an unrecoverable error.  If this is a request message, the server MUST respond with a 400 (Bad Request) status code and then close the connection.

Source:
[3.3.3](https://datatracker.ietf.org/doc/html/rfc7230#section-3.3.3)
<br/><br/>


# Response

### Structure of a response:
> A server responds to a client's request by sending one or more HTTP response messages, each beginning with a status line that includes the protocol version, a success or error code, and textual reason phrase (Section 3.1.2), possibly followed by header fields containing server information, resource metadata, and representation metadata (Section 3.2), an empty line to indicate the end of the header section, and finally a message body containing the payload body (if any, Section 3.3).

Source:
[Section 2.1](https://datatracker.ietf.org/doc/html/rfc7230#section-2.1)
<br/><br/>

### Response status-line formatting:
>  The first line of a response message is the status-line, consisting of the protocol version, a space (SP), the status code, another space, a possibly empty textual phrase describing the status code, and ending with CRLF.  

Source:
[Section 3.1.2](https://datatracker.ietf.org/doc/html/rfc7230#section-3.1.2)
<br/><br/>


### :
>  .  

Source:
[]()
<br/><br/>

### :
>  .  

Source:
[]()
<br/><br/>

### :
>  .  

Source:
[]()
<br/><br/>

### :
>  .  

Source:
[]()
<br/><br/>

### :
>  .  

Source:
[]()
<br/><br/>

### :
>  .  

Source:
[]()
<br/><br/>