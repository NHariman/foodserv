# foodserv
A 42/Codam project about writing an HTTP/1.1 server in C++.  
A collaborative project between [nhariman](https://github.com/nhariman), [salbregh](https://github.com/salbregh), and [mjiam](https://github.com/MichelleJiam).  

## Description


Our webserver uses the same non-blocking, event-driven architecture that nginx does. This allows the server to handle a high amount of requests with speed. We use [`kqueue`](https://www.freebsd.org/cgi/man.cgi?query=kqueue&sektion=2) for this, which means the server can only run on Mac machines.

## Documentation
We made a [wiki](https://github.com/NHariman/foodserv/wiki) containing information about:
- project requirements
- server specs
- implementation and research notes
- code documentation

## Resources
### General info on programming web servers
- [Intro to network programming](https://beej.us/guide/bgnet/html/#intro)
- [Simple, clear introduction to writing an HTTP server](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)
- [Easy to read Mozilla explanations of HTTP workings](https://developer.mozilla.org/en-US/docs/Web/HTTP)

### Sockets
- [Socket Programming in C/C++](https://www.geeksforgeeks.org/socket-programming-cc/)
- [Network-related system calls](https://beej.us/guide/bgnet/html/#system-calls-or-bust)
- [Video series: network programming](https://www.youtube.com/playlist?list=PL9IEJIKnBJjH_zM5LnovnoaKlXML5qh17)
- [Video: Socket Programming Tutorial In C For Beginners](https://youtu.be/LtXEMwSG5-8)

### Kqueue
- [IO Multiplexing: select vs poll vs kqueue](https://nima101.github.io/io_multiplexing)
- [Using kqueue to implement a streaming server](https://nima101.github.io/kqueue_server)
- [Kqueue tutorial](https://wiki.netbsd.org/tutorials/kqueue_tutorial/)

### Nginx
- [Non-blocking event-driven architecture behind nginx](https://www.nginx.com/blog/inside-nginx-how-we-designed-for-performance-scale/)
- [How nginx processes requests](http://nginx.org/en/docs/http/request_processing.html)
- [Server and location block selection algorithms](https://www.digitalocean.com/community/tutorials/understanding-nginx-server-and-location-block-selection-algorithms)
- [How nginx config files work](https://www.plesk.com/blog/various/nginx-configuration-guide/)
- [How the return directive works](https://www.digitalocean.com/community/tutorials/nginx-rewrite-url-rules)
- [Redirections](https://developer.mozilla.org/en-US/docs/Web/HTTP/Redirections)
- [Auto-index](https://www.keycdn.com/support/nginx-directory-index)
- [Full config example](https://www.nginx.com/resources/wiki/start/topics/examples/full/)
- [fastCGI config example](https://www.nginx.com/resources/wiki/start/topics/examples/fastcgiexample/)

### Request
- [HTTP Request Parsing using a Finite State Machine](https://ieeexplore.ieee.org/document/6957302)
- [HTTP header line breaks](https://stackoverflow.com/questions/5757290/http-header-line-break-style)
- [Chunked transfer-encoding](https://en.wikipedia.org/wiki/Chunked_transfer_encoding)
- [Boundary strings in POST file uploads](https://stackoverflow.com/questions/8659808/how-does-http-file-upload-work) (not handled by our server)

### RFC
- [7230: Message Syntax and Routing](https://datatracker.ietf.org/doc/html/rfc7230)
- [7231: Semantics and Content (requests, headers, response codes)](https://www.rfc-editor.org/rfc/rfc7231.html)
- [3986: URI Generic Syntax](https://datatracker.ietf.org/doc/html/rfc3986)


## About Us
Michelle Jiam - [LinkedIn](https://www.linkedin.com/in/mljiam/) / [Github](https://github.com/MichelleJiam)  
Sanne Albreghs - [LinkedIn](https://www.linkedin.com/in/sanne-albreghs-ba09141a3/) / [Github](https://github.com/salbregh)  
Niks Hariman - [LinkedIn](https://www.linkedin.com/in/niks-hariman-msc-aaa74b152/) / [Github](https://github.com/nhariman)
