# foodserv
webserv is a [42](https://www.42network.org/)/[Codam](https://www.codam.nl/) project about writing our own HTTP server in C++  
This is a collaborative project between [nhariman](https://github.com/nhariman), [salbregh](https://github.com/salbregh), and [mjiam](https://github.com/MichelleJiam).  
## Content
- [Project Description](#description)
- [Usage](#usage)
- [Documentation](#documentation)
- [Resources](#resources)
- [About Us](#about-us)

## Description
This is a simple HTTP/1.1 web server that can handle GET, POST, and DELETE requests.  

Our webserver uses the same non-blocking, event-driven architecture [that nginx does](https://www.nginx.com/blog/inside-nginx-how-we-designed-for-performance-scale/). This allows the server to handle a high amount of requests with speed.  
We use [`kqueue`](https://www.freebsd.org/cgi/man.cgi?query=kqueue&sektion=2) to handle the multiplexing, which means the server can only run on **Mac** machines.  

Detailed project specifications can be found [here](docs/webserv.en.subject.pdf).

## Usage
### Configuration
The server settings are configured through a `.conf` configuration file based on Nginx. The list of accepted directives can be found [here](https://github.com/NHariman/foodserv/wiki/Configuration-file).  

### Build
From the root of the repo, run `make && ./webserv` to build and start the web server.  
The `webserv` executable takes an optional configuration file argument:  
```console
$ ./webserv [your_config_file.conf]
```
Otherwise the web server defaults to using the settings in `config_files/default.conf`.

### Use
The web server can be interfaced with through any browser or tools like curl and telnet.  
If using the default configuration, navigating to `localhost` on port 80 (default), 4242, and 8080 showcases 3 different websites with different configuration settings.   

> http://localhost/
- Standard functionality  

> http://localhost:4242/
- Internal and external redirects  

> http://localhost:8080/
- Custom error pages
- Autoindexing


## Documentation
We made a [wiki](https://github.com/NHariman/foodserv/wiki) containing information about:
- project requirements
- server specs
- implementation and research notes
- code documentation

## Non-Goals
- Persistent connections
- Accepting POST file uploads other than text files

## Resources
### General info on programming web servers
- [Intro to network programming](https://beej.us/guide/bgnet/html/#intro)
- [Simple, clear introduction to writing a basic HTTP server](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)
- [Easy-to-read explanation of HTTP workings by Mozilla](https://developer.mozilla.org/en-US/docs/Web/HTTP)

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

### Requests
- [HTTP Request Parsing using a Finite State Machine](https://ieeexplore.ieee.org/document/6957302)
- [HTTP header line breaks](https://stackoverflow.com/questions/5757290/http-header-line-break-style)
- [Chunked transfer-encoding](https://en.wikipedia.org/wiki/Chunked_transfer_encoding)
- [Boundary strings in POST file uploads](https://stackoverflow.com/questions/8659808/how-does-http-file-upload-work) (not handled by our server)

### CGI
- [Common Gateway Interface (CGI) – How it Works, Features & Applications](https://electricalfundablog.com/common-gateway-interface-cgi/)
- [How the web works: HTTP and CGI explained](https://www.garshol.priv.no/download/text/http-tut.html)

### RFC
- [7230: Message Syntax and Routing](https://datatracker.ietf.org/doc/html/rfc7230)
- [7231: Semantics and Content (requests, headers, response codes)](https://www.rfc-editor.org/rfc/rfc7231.html)
- [3986: URI Generic Syntax](https://datatracker.ietf.org/doc/html/rfc3986)


## About Us
Michelle Jiam - [LinkedIn](https://www.linkedin.com/in/mljiam/) / [Github](https://github.com/MichelleJiam)  
Sanne Albreghs - [LinkedIn](https://www.linkedin.com/in/sanne-albreghs-ba09141a3/) / [Github](https://github.com/salbregh)  
Niks Hariman - [LinkedIn](https://www.linkedin.com/in/niks-hariman-msc-aaa74b152/) / [Github](https://github.com/nhariman)
