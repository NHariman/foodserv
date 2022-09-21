#ifndef URI_HPP
#define URI_HPP

#include <iostream>
#include "../err/exception.hpp"

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
		explicit URI(std::string const& input);
		// Assignment operator
		URI&	operator=(URI const& other);
		// Overloaded assignment operator taking string
		URI&	operator=(std::string const& input);
		// Destructor
		~URI();

		// Getters
		std::string const&	Get() const;
		std::string const&	GetInputURI() const;
		std::string const&	GetParsedURI() const;
		std::string			GetURIDebug() const;
		std::string const&	GetHost() const;
		std::string const&	GetPort() const;
		std::string			GetHostWithPort() const;
		std::string const&	GetPath() const;
		std::string const&	GetQuery() const;

		// Setters
		void	SetHost(std::string const& host);
		void	SetPath(std::string const& path);
		void	SetQuery(std::string const& query);

		// friend class forward declaration allows parser classes to
		// access private & protected members of URI.
		friend class RequestTargetParser;
		friend class URIHostParser;

	private:
		std::string	_uri_input;
		std::string	_uri_parsed;
		std::string	_host;
		std::string	_port;
		std::string	_path;
		std::string	_query;

		void	ParseInput(Part part = Part::Invalid);
		std::string	ConstructParsedURI();
};

#endif /* URI_HPP */
