
#ifndef LOCATION_CONTEXT_HPP
# define LOCATION_CONTEXT_HPP

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "../utils/config_utils.hpp"
#include "config_interface.hpp"
#include "directive_validation/directive_validation.hpp"

class LocationContext : virtual public ConfigValues {
	protected:
		bool						bool_uri;
		bool						bool_cgi_pass;
		bool						bool_allowed_methods;
		bool						bool_alias;
		LocationUri					_location_uri;
		CGIPass						_cgi_pass;
		AllowedMethods				_allowed_methods;
		std::string					_alias;

		void						GetDirectiveValuePairs(std::string data);
		virtual int							IsDirective(std::string directive) override;
		virtual void						SetValue(int directive, std::string input) override;

		int							GetDirective(std::string directive);

		// setters
		size_t				FindValue(int directive, std::string data, size_t key_start, size_t key_end);
		void				SetAllowedMethods(std::string value);
		void				SetAlias(std::string value);
		void				SetCGI(std::string value);
		void				SetURI(std::string value);

		void				CopyValues(LocationContext const& location_context);

	public:
		LocationContext();
		LocationContext(std::string data);
		LocationContext& operator= (LocationContext const &location_context);
		virtual ~LocationContext(){};

		// location context specific getters
		virtual bool						IsSet(std::string directive) override;
		// getters
		LocationUri					GetLocationUri() const;
		CGIPass						GetCGIPass() const;
		AllowedMethods				GetAllowedMethods() const;
		std::string					GetAlias() const;
};

#endif