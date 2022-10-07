# Mandatory parts of a config file for our webserver

## When is something a valid nginx config file
Because our server is based on nginx config files, we use the nginx command to check if a config file is valid or not.
To do that, nginx must be installed on the system and then one can do:
`nginx -c {Path_to_config_file_starting_from_root} -t`

## Server Block
Each config file MUST contain server blocks inside the http block. Server blocks outside the http block will be ignored.
The block contains the server configuration files for a server block for a website.

### Contains:
- listen (default: 80), tells NGINX the hostname/IP and the TCP port where it should listen for HTTP connections
    - if multiple listens to the same port occur the file will fail
- server_name (default: localhost), allows multiple domains to be served from a single IP address. Ideally, it should be created per domain or site. based on the request header it receives, the server decides which domain to serve.
- root (default: /var/www/html)
- index (default: index.html)
- Location Blocks

## Location Block
A Location block covers requests for specific files and folders. It also allows NGINX to respond to requests for resources within the server.
The locations are literal string matches.

Multiple location blocks can be found inside a server block. However, in the event of duplicate uri names, an error is thrown.

### Contains
- uri, literal string before the {} part [(more info here)](https://www.plesk.com/blog/various/nginx-configuration-guide/), unlike nginx which accepts uri's without the leading slash, this webserv project _requires_ the loading slash before a uri definition.
example:
```
location /uri {} // GOOD

location uri {} // BAD
```
Depending on the uri style a directory or a file can be indicated
```
location /uri {} // an exact url

location /uri/ {} // a directory, in this case, one must find an index file within that directory.
```
- root, indicates which folder to start looking for files in
- index, indicates which index files to select
- allowed_methods, a custom keyword for webserver that allows a user to specify what methods are allowed within said location block. On default, no methods are allowed and the string will be empty. Only the methods GET, POST and DELETE are implemented.
example:
```
allowed_methods GET POST DELETE ;
```
- fastcgi_pass (OPTIONAL)
    - fastcgi tells nginx to forward requests from clients to a backend server. [(more info here)](https://www.digitalocean.com/community/tutorials/understanding-and-implementing-fastcgi-proxying-in-nginx)
 examples:
 ```
                location / {
                       autoindex on;
                       # First attempt to serve request as file, then
                       # as directory, then fall back to displaying a 404.
                       try_files $uri $uri/ =404;
               }
              location /test/ {
                       autoindex on;
                       # First attempt to serve request as file, then
                       # as directory, then fall back to displaying a 404.
               }

               location /cgi-bin {
                     fastcgi_pass http://127.0.0.1:8080;
              }
```
- return, takes a return code and an url
example:
```
return 301 $scheme://www.new-name.com$request_uri;
```

# Variables to implement ($var)
`$uri` - the URI that nginx is currently processing. Contains the normalised URI (Uniform resource identifier).
For example, the URL http://example.org/wiki/Main_Page refers to a resource identified as /wiki/Main_Page (the URI).

# Comments
Comments are defined with a `#`, anything after the `#` and before a newline will be ignored.
ie.
```
this won't be ignored # but this will be
```
# TREE
<img src="https://cdn.discordapp.com/attachments/856460136758771726/990966854396821564/image_1.png">

# Information on NGINX config files:
[how to configure nginx](https://www.linode.com/docs/guides/how-to-configure-nginx/)

[NGINX http configuration](https://www.digitalocean.com/community/tutorials/understanding-the-nginx-configuration-file-structure-and-configuration-contexts#the-http-context)

[Understanding and implementing fastcgi proxy in nginx](https://www.digitalocean.com/community/tutorials/understanding-and-implementing-fastcgi-proxying-in-nginx)

[Nginx location directive](https://www.keycdn.com/support/nginx-location-directive)

[NGINX Error Codes](https://www.nginx.com/resources/wiki/extending/api/http/)

[All http status codes](https://developer.mozilla.org/en-US/docs/Web/HTTP/Status)