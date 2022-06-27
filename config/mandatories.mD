# Mandatory parts of a config file for our webserver

## HTTP block
Each config file MUST start with an HTTP block in order to specify global variables such as:
    - Client_max_body_size (default 1mb)
    - access_log (default logs/access.log), works a little different from the og access_log, as it puts everything in there
It will also contain any server blocks that need to be configured. A server block outside of an http block will be ignored.

### Description
http blocks contain directives for handling web traffic. These directives are often universal as they are passed on to all website configurations NGINX serves. A list of available directives for http blocks are available on official NGINX http block documentation.

**only a SINGLE http block will be configured, extra http blocks will be ignored.**

## Server Block
Each config file MUST contain server blocks inside the http block. Server blocks outside the http block will be ignored.

### Description
Contains the server configuration files for a server block for a website.

### Contains:
    - listen (default: 80), tells NGINX the hostname/IP and the TCP port where it should listen for HTTP connections
        - if multiple listens to the same port occur the file will fail
    - server_name (default: localhost), allows multiple domains to be served from a single IP address. Ideally, it should be created per domain or site. based on the request header it receives, the server decides which domain to serve.
    - root (default: html/)
    - index (default: index.html)
    - try_files (default: $uri index.html): Checks the existence of files in the specified order and uses the first found file for request processing; the processing is performed in the current context. [...] If none of the files were found, an internal redirect to the uri specified in the last parameter is made.
    - Location Blocks

## Location Block
A Location block covers requests for specific files and folders. It also allows NGINX to respond to requests for resources within the server.
The locations are literal string matches.

Multiple location blocks can be found inside a server block.

### Contains
    - root, indicates which folder to start looking for files in
    - index, indicates which index files to select
    - fastcgi_pass (OPTIONAL)
    - fastcgi_index (OPTIONAL)
    - fastcgi_param (OPTIONAL)
        - fastcgi tells nginx to forward requests from clients to a backend server. [(more info here)](https://www.digitalocean.com/community/tutorials/understanding-and-implementing-fastcgi-proxying-in-nginx)

# Variables to implement ($var)
`$uri` - the URI that nginx is currently processing. Contains the normalised URI (Uniform resource identifier).
For example, the URL http://example.org/wiki/Main_Page refers to a resource identified as /wiki/Main_Page (the URI).


# Information on NGINX config files:
[how to configure nginx](https://www.linode.com/docs/guides/how-to-configure-nginx/)
[Understanding and implementing fastcgi proxy in nginx](https://www.digitalocean.com/community/tutorials/understanding-and-implementing-fastcgi-proxying-in-nginx)
[Nginx location directive](https://www.keycdn.com/support/nginx-location-directive)