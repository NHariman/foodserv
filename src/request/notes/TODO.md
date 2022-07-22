- [ ] Look into reserved characters use in URIs for RequestParser::ParseTarget
[ref](https://datatracker.ietf.org/doc/html/rfc3986#section-2.2)

- [x] Figure out if we only have to handle origin-form URIs for request-target (no scheme)
    - Yes. Only have to handle origin-form.

- [x] Ask someone about "If the target URI's path component is empty, the client MUST send "/" as the path within the origin-form of request-target."
    - If there's no path component after the authority/host, i.e. "www.google.com", then client must use a "/" after the method. E.g. "GET / HTTP/1.1
    Host: www.google.com"

/*
	Transition table for request parser
	MT = Method, URI, VR = Version, FN = FieldName, FS = FieldStart, FV = FieldValue

	// TCh       VCh       SP       WHTSP    URI       HTTP     ht       :       \n       \0
	{  MT,       x,        x,       x,       x,        x,       x,       x,       x,       x     }, // Start
	{  MT,       x,        URI,     x,       x,        x,       x,       x,       x,       x     }, // Method
	{  x,        x,        VR,      x,       URI,      x,       x,       URI,     x,       x     }, // URI
	{  x,        x,        x,       x,       x,        VR,      x,       x,       FS,      DONE  }, // Version
	{  FN,       x,        x,       x,       x,        x,       x,       x,       DONE,    x     }, // FieldStart
	{  FN,       x,        x,       x,       x,        x,       x,       FV,      x,       x     }, // FieldName
	{  x,        FV,       FV,      DONE,    x,        x,       FV,      x,       FS,      DONE  }, // FieldValue
*/

/*

HandleRequest
|_ ParseRequest
	|_ ParseRequestLine (into struct)
		|_ ParseMethod
		|_ ParseTarget
		|_ ParseHTTP
	|_ ParseHeaderField (into hash table)
		|_ ParseFieldName
		|_ ParseFieldValue
	|_ ParseReceivedforContentIndication
	if expecting message body
		|_ ParseHeaderMessage
	|_ ValidateRequest
CreateResponse
|_ 

*/