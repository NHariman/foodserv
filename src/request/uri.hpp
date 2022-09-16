#ifndef URI_HPP
#define URI_HPP

#include <iostream>
#include "../err/exception.hpp"

using namespace std;

// Constructs a URI object composed of: host, path, query.
// Host and path portion must be parsed in 2 separate calls,
// as ParseInput only parses either as path or as host (because complete URIs are not )
// Parses during construction using RequestTargetParser, which throws
// BadRequestException if an invalid URI is passed.

class URI {
	public:
		enum class Part {
			Invalid = -1,
			Host = 0,
			Path,
			Query
		};

		// Default constructor
		URI();
		// Copy constructor
		URI(URI const& other);
		// String constructor
		explicit URI(string const& input);
		// Assignment operator
		URI&	operator=(URI const& other);
		// Overloaded assignment operator taking string
		URI&	operator=(string const& input);
		// Destructor
		~URI();

		// Getters
		string const&	Get() const;
		string const&	GetInputURI() const;
		string const&	GetParsedURI() const;
		string			GetURIDebug() const;
		string const&	GetHost() const;
		string const&	GetPort() const;
		string			GetHostWithPort() const;
		string const&	GetPath() const;
		string const&	GetQuery() const;

		// Setters
		void	SetHost(string const& host);
		void	SetPath(string const& path);
		void	SetQuery(string const& query);

		// friend class forward declaration allows parser classes to
		// access private & protected members of URI.
		friend class RequestTargetParser;
		friend class URIHostParser;

	private:
		string	_uri_input;
		string	_uri_parsed;
		string	_host;
		string	_port;
		string	_path;
		string	_query;

		void	ParseInput(Part part = Part::Invalid);
		string	ConstructParsedURI();
};

#endif /* URI_HPP */
