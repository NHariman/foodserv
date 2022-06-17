# Train of thought on Configuration parsing

### Must haves
- `http` - context holds directives for handling HTTP and HTTPS traffic
    - `server` - context which has directives wwhich tell how to process requests, associated with a domain/IP address 
        - `listen` for choosing port numbers and host of each server
        - `server_name` default name to local host if not found
        - `root` - location of html files etc -> front end shizzle
        - `index index.php...` - default to file if request is a directory
        - `location` - contexts are used to define directives to handle client request. When a request for resource arrives at NGINX, it will try to match the URI to one of the locations and handle it accordingly.
        - `location ~\.php$ {}` - location block for fastcgi/python
    - `client_max_body_size` - defines upload size

### DEFAULTS
- http : should always be there. if not error.
- server: should always be there. if not error.
- listen: if non: default to 80
- server_name: if non: default to localhost
- root: if non: will start in root dir of computer: `/`
- index: if non: have a default html page to display
- location: default error pages:
- autoindex: if non: default: on
- client-max-body-size: if non: default 2mb

### NOTES
- tree like structure - parse treelike
- SERVER CONTEXT - should be able to handle multiple server blocks
- ERROR PAGES - in location context
- AUTO INDEX - in location

### HOW TO READ


### RESOURCES
- https://www.journaldev.com/26618/nginx-configuration-file
