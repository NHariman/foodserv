#ifndef CONFIG_INTERFACE_HPP
# define CONFIG_INTERFACE_HPP

#include "directive_validation/directive_validation.hpp"
#include <map>
#include <iostream>

class ConfigValues {
    protected:
        bool	bool_root;
	    bool	bool_index;
	    bool	bool_client_max_body_size;
	    bool	bool_error_page;
	    bool	bool_autoindex;
	    bool	bool_return_dir;

        std::string						_root;
		std::vector<std::string>		_index;
		size_t							_client_max_body_size;
		std::map<int, std::string>		_error_page;
		bool							_autoindex;
		ReturnDir						_return_dir;
    
	protected:
       virtual int                      IsDirective(std::string directive) = 0;
	   virtual void                     SetValue(int directive, std::string value) = 0;

	   	// setters
		void							SetRoot(std::string trimmed_value);
		void							SetIndex(std::string trimmed_value);
		void							SetCMBS(std::string trimmed_value);
		void							SetErrorPage(std::string trimmed_value);
		void							SetAutoindexDir(std::string trimmed_value);
		void							SetReturn(std::string trimmed_value);

	   ConfigValues();
	   ConfigValues(const ConfigValues& obj);
	   ConfigValues&	operator=(const ConfigValues& obj);
	   virtual ~ConfigValues(){};

    public:
	   	void								AddToErrorPageMap(std::map<int, std::string> *map, std::string input);
       //getters
       virtual std::string					GetRoot() const;
       virtual std::vector<std::string>	    GetIndex() const;
       virtual size_t						GetClientMaxBodySize() const;
       virtual std::map<int, std::string>	GetErrorPage() const;
       virtual bool						    GetAutoindex() const;
       virtual ReturnDir                    GetReturn() const;
       virtual bool							HasErrorPage() const;
	   void									PrintErrorPage() const;

	   // checks if a directive has been set
       virtual bool							IsSet(std::string directive) = 0;
};

#endif