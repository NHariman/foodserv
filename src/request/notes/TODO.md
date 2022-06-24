- [ ] Look into reserved characters use in URIs for RequestParser::ParseTarget
[ref](https://datatracker.ietf.org/doc/html/rfc3986#section-2.2)

- [x] Figure out if we only have to handle origin-form URIs for request-target (no scheme)
    - Yes. Only have to handle origin-form.

- [x] Ask someone about "If the target URI's path component is empty, the client MUST send "/" as the path within the origin-form of request-target."
    - If there's no path component after the authority/host, i.e. "www.google.com", then client must use a "/" after the method. E.g. "GET / HTTP/1.1
    Host: www.google.com"