# Header Fields
### Expect:
> A server that receives an Expect field-value other than 100-continue MAY respond with a 417 (Expectation Failed) status code to indicate that the unexpected expectation cannot be met.

> A 100-continue expectation informs recipients that the client is about to send a (presumably large) message body in this request and wishes to receive a 100 (Continue) interim response if the request-line and header fields are not sufficient to cause an immediate success, redirect, or error response.

> A server MAY omit sending a 100 (Continue) response if it has already received some or all of the message body for the corresponding request, or if the framing indicates that there is no message body.

> A server that sends a 100 (Continue) response MUST ultimately send a final status code, once the message body is received and processed, unless the connection is closed prematurely.  
A server that responds with a final status code before reading the entire message body SHOULD indicate in that response whether it intends to close the connection or continue reading and discarding the request message.

> An origin server MUST, upon receiving an HTTP/1.1 (or later) request-line and a complete header section that contains a 100-continue expectation and indicates a request message body will follow, either send an immediate response with a final status code, if that status can be determined by examining just the request-line and header fields, or send an immediate 100 (Continue) response to encourage the client to send the request's message body.  The origin server MUST NOT wait for the message body before sending the 100 (Continue) response.

Source:
[Section 5.1.1](https://datatracker.ietf.org/doc/html/rfc7231#section-5.1.1)
<br/><br/>

### Content-Encoding:
>  An origin server MAY respond with a status code of 415 (Unsupported Media Type) if a representation in the request message has a content coding that is not acceptable.  

Source:
[Section 3.1.2.2](https://datatracker.ietf.org/doc/html/rfc7231#section-3.1.2.2)
<br/><br/>

# Method response codes
### DELETE:
> If a DELETE method is successfully applied, the origin server SHOULD send a 202 (Accepted) status code if the action will likely succeed but has not yet been enacted, a 204 (No Content) status code if the action has been enacted and no further information is to be supplied, or a 200 (OK) status code if the action has been enacted and the response message includes a representation describing the status. 

Source:
[Section 4.3.5](https://datatracker.ietf.org/doc/html/rfc7231#section-4.3.5)
<br/><br/>

### POST:
> If one or more resources has been created on the origin server as a result of successfully processing a POST request, the origin server SHOULD send a 201 (Created) response containing a Location header field that provides an identifier for the primary resource created (Section 7.1.2) and a representation that describes the status of the request while referring to the new resource(s).   

Source:
[Section 4.3.3](https://datatracker.ietf.org/doc/html/rfc7231#section-4.3.3)
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