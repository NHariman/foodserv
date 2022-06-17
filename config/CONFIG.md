# Train of thought on Configuration parsing

### Must haves
- `http` - context holds directives for handling HTTP and HTTPS traffic
    - `server` - context which has directives wwhich tell how to process requests, associated with a domain/IP address 
        - `listen` for choosing port numbers and host of each server
        - `server_name` default name to local host if not found
        - `root` - location of html files etc -> front end shizzle
        - `location` - contexts are used to define directives to handle client request. When a request for resource arrives at NGINX, it will try to match the URI to one of the locations and handle it accordingly.
    - `client_max_body_size` - defines upload size

### NOTES
- tree like structure - parse treelike
- SERVER CONTEXT - should be able to handle multiple server blocks
- ERROR PAGES - in location context
- 

### RESOURCES
- https://www.journaldev.com/26618/nginx-configuration-file
