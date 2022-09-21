#ifndef AHTTP_MESSAGE_HPP
#define AHTTP_MESSAGE_HPP

#include <iostream>
#include <map>
#include "../utils/request_utils.hpp"

// returned by GetField when no field by the passed name is found.
#define NO_VAL "NO SUCH HEADER FIELD"

// Abstract class inherited by Request & Response classes.
class AHTTPMessage {
	public:
		typedef std::map<std::string, std::string>	FieldsMap;

		AHTTPMessage() : _status_code(0), _content_length(0) {}
		virtual	~AHTTPMessage() {}

		// Getters
		virtual	std::string const&	GetHTTPVersion() const {
			return _http_version;
		}

		virtual	std::string const&	GetMessageBody() const {
			return _message_body;
		}

		// Retrieves header field value associated with `field_name` parameter.
		// If no header field with that name is found, returns macro NO_VAL, which
		// expands to string "NO SUCH HEADER FIELD" (defined above).
		// Example use:
		//		[ChildClass].GetField("host")
		virtual	std::string	GetField(std::string field_name) const {
			// Normalizes field name to lowercase for case-insensitive searching
			NormalizeString(tolower, field_name, 0);

			FieldsMap::const_iterator	found = _header_fields.find(field_name);
			if (found == _header_fields.end())
				return NO_VAL;
			return found->second;
		}

		virtual	FieldsMap const&	GetFields() const {
			return _header_fields;
		}

		virtual	int	GetStatusCode() const {
			return _status_code;
		}

		virtual size_t	GetContentLength() const {
			return _content_length;
		}

		// Setters
		virtual	void	SetHTTPVersion(std::string const& version) {
			_http_version = version;
		}

		virtual	void	SetStatusCode(int code) {
			_status_code = code;
		}

		virtual	void	SetMessageBody(std::string const& message) {
			_message_body = message;
		}

		// Inserts new field name + value pair into map or appends new value to
		// existing field value if field already exists in map.
		virtual	void	SetHeaderField(std::string field_name, std::string field_val) {
			// Normalize field name to lowercase for easy lookup later
			NormalizeString(tolower, field_name, 0);

			if (_header_fields.find(field_name) != _header_fields.end()) { // if header field exists
				field_val = _header_fields[field_name] + ", " + field_val;
			}
			std::pair<std::string, std::string>	new_field(field_name, field_val);
			_header_fields.insert(new_field);
		}
		
		virtual void	SetContentLength(size_t content_length) {
			_content_length = content_length;
		}
		
		virtual	void	RemoveField(std::string const& field_name) {
			_header_fields.erase(field_name);
		}

	protected:
		std::string			_http_version;
		int					_status_code; // for error codes
		std::string			_message_body;
		FieldsMap			_header_fields;
		size_t				_content_length; // bytes of payload body
};

#endif /* AHTTP_MESSAGE_HPP */
