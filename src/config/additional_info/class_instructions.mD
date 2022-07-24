# How to use NginxConfig class to get the configuration data.

All classes are entirely written in coplien form in order for easy copying into other variables.

## NginxConfig

**Available getters**
- `std::string GetConfigFile() const;` Gets the string containing the entire config file, without comments.
- `size_t GetServerContextAmount() const;` gets the amount of server contexts found
- `std::vector<ServerContext> GetServers() const;` gets the vector of server contexts for use. (See ServerContext class header for available getters within this context)

## ServerContext

**Available getters**
- `std::vector<LocationContext>	GetLocationContexts() const;` - Gets available location contexts (See LocationContext class header for available getters within this context)
- `std::pair<in_addr_t, int>	GetListen() const;` - Gets listen directive
- `in_addr_t					GetIPAddress() const;` - Gets IP address
- `int							GetPortNumber() const;` - Gets Port number
- `std::vector<std::string>	GetServerNameVector() const;` - Gets vector of server_name
- `std::string					GetRoot() const;` - gets root directive within server context
- `std::vector<std::string>	GetIndex() const;` - Get vector of indexes in `std::string` format.
- `int							GetClientMaxBodySize() const;` - Gets client_max_body_size in int form.
- `std::vector<ErrorPage>		GetErrorPage() const;` - gets vector of error_page entries in format `ErrorPage`. (See ErrorPage header for getters)
- `bool						IsErrorPageSet() const;` - checks if error_page has been set or not
- `t_flags_server				GetFlags() const;` - gets flags for server context to check which directives have been set.

## ListenContext

**Available getters**
- `bool						IsSet(std::string key);` - can be used to check if a certain directive is set by passing a string of the directive in question (available directives: "autoindex", "root", "index", "client_max_body_size", "error_page", "fastcgi_pass", "allowed_methods", "return"), returns true if set, false if not set
- `t_flags_location			GetFlags() const;` - gets the flags of the location context to check which directives have been set.
- `LocationUri					GetLocationUri() const;` - Gets the uri of the location context in format LocationUri (see LocationUri header for more available getters.)
- `bool						GetAutoindex() const;` - returns true of autoindex is on, false if autoindex is off.
- `std::string					GetRoot() const;` - returns the root of the location context
- `std::vector<std::string>	GetIndex() const;` - returns available indexes for the location context as a vector of strings.
- `int							GetClientMaxBodySize() const;` - returns client_max_body_size in int.
- `std::string					GetFastCGIPass() const;` - returns a string of fastcgi_pass.
- `std::vector<ErrorPage>		GetErrorPage() const;` - returns a vector of type ErrorPage (see ErrorPage header for information about getters)
- `AllowedMethods				GetAllowedMethods() const;` - returns AllowedMethods in type AllowedMethods. (Check AllowedMethods for getters)

### Available directive classes

#### ErrorPage
- `std::string			GetUri() const;` - Gets error_page uri
- `std::vector<int>	GetCodes() const;` - Gets the error codes that belong to a certain uri in a vector of ints.
- `void				PrintCodes() const;` - just prints codes and the uri.

#### LocationUri
- `std::string	GetUri() const;` - Gets the uri of the location context in string form
- `bool		IsDirectory() const;` - returns true if uri is a directory, false if it's not a directive.
- `bool        IsEmpty() const;` - checks if is empty.

#### AllowedMethods
- `std::vector<std::string>	GetAllowedMethods() const;` - Gets allowed methods in a vector of strings
- `void		PrintMethods();` - prints methods
- `bool		IsSet() const;` - checks if AllowedMethods has been set or not. Returns true if it has been set, returns false if it hasn't. In the event it's false it means no methods are allowed.