#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/config/directive_validation/directive_validation.hpp"
# include <map>
#include <string>

// Test syntax
/*
		TEST(TestSuiteName, TestName) {
		... test body ...
		}
*/



//////////////////////////////
//**MODULE ALLOWED METHODS**//
//////////////////////////////
TEST(AllowedMethodsTest, ValidInput) {
	EXPECT_NO_THROW({
		AllowedMethods test("GET");
	});
	EXPECT_NO_THROW({
		AllowedMethods test("POST");
	});
	EXPECT_NO_THROW({
		AllowedMethods test("DELETE");
	});
	EXPECT_NO_THROW({
		AllowedMethods test("GET DELETE");
	});
	EXPECT_NO_THROW({
		AllowedMethods test("GET POST DELETE");
	});
	{
		AllowedMethods test("GET POST DELETE");
		EXPECT_TRUE(test.GetPOST());
	}
	{
		AllowedMethods test("GET POST DELETE");
		EXPECT_TRUE(test.GetGET());
	}
	{
		AllowedMethods test("GET POST DELETE");
		EXPECT_TRUE(test.GetGET());
	}
	{
		AllowedMethods test("GET POST DELETE");
		EXPECT_TRUE(test.GetDELETE());
	}
}

TEST(AllowedMethodsTest, InvalidInput) {
	EXPECT_THROW({
		AllowedMethods test("GETP");
	}, AllowedMethods::BadMethodException);
	EXPECT_THROW({
		AllowedMethods test("POSTS");
	}, AllowedMethods::BadMethodException);
	EXPECT_THROW({
		AllowedMethods test("DELETEE");
	}, AllowedMethods::BadMethodException);
	EXPECT_THROW({
		AllowedMethods test("GET DFD DELETE");
	}, AllowedMethods::BadMethodException);
	EXPECT_THROW({
		AllowedMethods test("GET POST DELETE BB");
	}, AllowedMethods::TooManyArgumentsException);
	EXPECT_THROW({
		AllowedMethods test("GETPOST DELETE BB");
	}, AllowedMethods::BadMethodException);
	EXPECT_THROW({
		AllowedMethods test("");
	}, AllowedMethods::MissingArgumentsException);
}

//////////////////////////////
//**  MODULE AUTOINDEX    **//
//////////////////////////////

TEST(AutoIndexTest, ValidInput) {
	EXPECT_NO_THROW({
		SetAutoindex("on");
	});
	EXPECT_NO_THROW({
		SetAutoindex("off");
	});
	EXPECT_TRUE(SetAutoindex("on"));
	EXPECT_FALSE(SetAutoindex("off"));
}

TEST(AutoIndexTest, invalidInput) {
	EXPECT_THROW({
		SetAutoindex("onf");
	}, Autoindex::InvalidAutoindexException);
	EXPECT_THROW({
		SetAutoindex("offe");
	}, Autoindex::InvalidAutoindexException);
	EXPECT_THROW({
		SetAutoindex("1");
	}, Autoindex::InvalidAutoindexException);
	EXPECT_THROW({
		SetAutoindex("off e");
	}, Autoindex::TooManyArgumentsException);
	EXPECT_THROW({
		SetAutoindex("on e");
	}, Autoindex::TooManyArgumentsException);
	EXPECT_THROW({
		SetAutoindex("k on");
	}, Autoindex::TooManyArgumentsException);
	EXPECT_THROW({
		SetAutoindex("oh off");
	}, Autoindex::TooManyArgumentsException);
	EXPECT_THROW({
		SetAutoindex("");
	}, Autoindex::MissingArgumentsException);
}

//////////////////////////////
//**   MODULE ERROR_PAGE  **//
//////////////////////////////

TEST(ErrorPageTest, ValidInput) {
	{
		std::map<int, std::string> map;
		EXPECT_NO_THROW({
		AddToErrorPageMap(&map, "500 502 503 504 /50x.html");
	});}
	{
		std::map<int, std::string> map;
		EXPECT_NO_THROW({
		AddToErrorPageMap(&map, "404             /404.html");
	});}
	{
		std::map<int, std::string> map;
		EXPECT_NO_THROW({
		AddToErrorPageMap(&map, "404 /404.html");
	});}
	{
		std::map<int, std::string> map;
		EXPECT_NO_THROW({
		AddToErrorPageMap(&map, "500 502 503 504 404 403 402 405 /50x.html");
	});}
	{
		std::map<int, std::string> map;
		EXPECT_NO_THROW({
		AddToErrorPageMap(&map, "500 502 503 504 /50x.html");
		AddToErrorPageMap(&map, "404 /404.html");
	});}
}

TEST(ErrorPageTest, InvalidInput) {
	{
		std::map<int, std::string> map;
		EXPECT_THROW({
		AddToErrorPageMap(&map, "500 502 503 404 /50x.html");
		AddToErrorPageMap(&map, "404 /404.html");	
		}, ErrorPage::DuplicateErrorCodeException);
	}
	{
		std::map<int, std::string> map;
		EXPECT_THROW({
			AddToErrorPageMap(&map, "404 /404.html 404");
			}, ErrorPage::BadErrorURIException);
	}
	{
		std::map<int, std::string> map;
		EXPECT_THROW({
			AddToErrorPageMap(&map, "404 /404.html 404");
			}, ErrorPage::BadErrorURIException);
	}
	{
		std::map<int, std::string> map;
		EXPECT_THROW({
			AddToErrorPageMap(&map, "404 404.html /stuff.html");
			}, ErrorPage::InvalidCodeInputException);
	}
	{
		std::map<int, std::string> map;
		EXPECT_THROW({
			AddToErrorPageMap(&map, "404 abc /404.html");
			}, ErrorPage::InvalidCodeInputException);
	}
	{
		std::map<int, std::string> map;
		EXPECT_THROW({
			AddToErrorPageMap(&map, "404d 404 /404.html");
			}, ErrorPage::InvalidCodeInputException);
	}
	{
		std::map<int, std::string> map;
		EXPECT_THROW({
			AddToErrorPageMap(&map, "404 404.html");
			}, ErrorPage::BadErrorURIException);
	}
	{
		std::map<int, std::string> map;
		EXPECT_THROW({
			AddToErrorPageMap(&map, "404 /404.html /404.html");
			}, ErrorPage::InvalidCodeInputException);
	}
	{
		std::map<int, std::string> map;
		EXPECT_THROW({
			AddToErrorPageMap(&map, "");
		}, ErrorPage::MissingArgumentsException);
	}
	
	
	
}

//////////////////////////////
//**      MODULE INDEX    **//
//////////////////////////////


TEST(IndexTest, InvalidInput) {
	EXPECT_THROW({
		Index test("");
	}, Index::MissingArgumentsException);
}

TEST(IndexTest, ValidInput){
	EXPECT_NO_THROW({
		Index test("index.php");
	});
		EXPECT_NO_THROW({
		Index test("index.php index.html");
	});
}

//////////////////////////////
//**      MODULE ROOT     **//
//////////////////////////////

TEST(RootTest, InvalidInput) {
	EXPECT_THROW({
		Root test("");
	}, Root::MissingArgumentsException);
	 EXPECT_THROW({
		Root test("root/here new/root/here");
	}, Root::TooManyArgumentsException); 

}

TEST(RootTest, ValidInput){
	EXPECT_NO_THROW({
		Root test("root/here");
	});
}

//////////////////////////////
//**      MODULE CMBS     **//
//////////////////////////////


TEST(CMBSTest, ValidInputTests) {
	EXPECT_NO_THROW({
		ClientMaxBodySize test("123");
	});
	EXPECT_NO_THROW({
		ClientMaxBodySize test("123m");
	});
	EXPECT_NO_THROW({
		ClientMaxBodySize test("123M");
	});
	EXPECT_NO_THROW({
		ClientMaxBodySize test("2147483647");
	});
	EXPECT_NO_THROW({
		ClientMaxBodySize test("2147483647m");
	});
	EXPECT_NO_THROW({
		ClientMaxBodySize test("2147483647M");
	});
}

TEST(CMBSTest, InvalidInputTests) {
	EXPECT_THROW({
		ClientMaxBodySize test("-123");
	}, ClientMaxBodySize::InvalidClientMaxBodySizeException);
	EXPECT_THROW({
		ClientMaxBodySize test("123b");
	}, ClientMaxBodySize::InvalidClientMaxBodySizeException);
	EXPECT_THROW({
		ClientMaxBodySize test("a123");
	}, ClientMaxBodySize::InvalidClientMaxBodySizeException);
	EXPECT_THROW({
		ClientMaxBodySize test("123mb");
	}, ClientMaxBodySize::InvalidClientMaxBodySizeException);
	EXPECT_THROW({
		ClientMaxBodySize test("123MB");
	}, ClientMaxBodySize::InvalidClientMaxBodySizeException);
	EXPECT_THROW({
		ClientMaxBodySize test("123 1");
	}, ClientMaxBodySize::InvalidClientMaxBodySizeException);
	EXPECT_THROW({
		ClientMaxBodySize test("123 m");
	}, ClientMaxBodySize::InvalidClientMaxBodySizeException);
	EXPECT_THROW({
		ClientMaxBodySize test("123m1");
	}, ClientMaxBodySize::InvalidClientMaxBodySizeException);
	EXPECT_THROW({
		ClientMaxBodySize test("123Me");
	}, ClientMaxBodySize::InvalidClientMaxBodySizeException);
	EXPECT_THROW({
		ClientMaxBodySize test("asbsd");
	}, ClientMaxBodySize::InvalidClientMaxBodySizeException);
	EXPECT_THROW({
		ClientMaxBodySize test("2147483648");
	}, ClientMaxBodySize::TooLargeClientMaxBodySizeException);
	EXPECT_THROW({
		ClientMaxBodySize test("2147483648m");
	}, ClientMaxBodySize::TooLargeClientMaxBodySizeException);
	EXPECT_THROW({
		ClientMaxBodySize test("2147483648M");
	}, ClientMaxBodySize::TooLargeClientMaxBodySizeException);
		EXPECT_THROW({
		ClientMaxBodySize test("");
	}, ClientMaxBodySize::MissingArgumentsException);

}

TEST(CMBSTest, ReturnInputTests) {
	EXPECT_EQ(PrintValue("123"), 123);
	EXPECT_EQ(PrintValue("123m"), 123);
	EXPECT_EQ(PrintValue("123M"), 123);
	EXPECT_EQ(PrintValue("2147483647"), 2147483647);
	EXPECT_EQ(PrintValue("2147483647M"), 2147483647);
	EXPECT_EQ(PrintValue("2147483647m"), 2147483647);
}

//////////////////////////////
//**   MODULE CGIPASS **//
//////////////////////////////

TEST(cgipassTest, InvalidInput) {
	EXPECT_THROW({
		CGIPass test("");
	}, CGIPass::MissingArgumentsException);
	EXPECT_THROW({
		CGIPass test("dadfadf dafdfsafadsf dafdadfaf");
	}, CGIPass::TooManyArgumentsException);
}

TEST(cgipassTest, ValidInput){
	EXPECT_NO_THROW({
		CGIPass test(".py link_here");
	});
	EXPECT_NO_THROW({
		CGIPass test("./py");
	});
	EXPECT_NO_THROW({
		CGIPass test("path/to/executable");
	});	
}

//////////////////////////////
//**   MODULE LocationUri **//
//////////////////////////////

TEST(LocationURITest, InvalidInput) {
	EXPECT_THROW({
		LocationUri test("test");}, LocationUri::BadUriException);
	EXPECT_THROW({
		LocationUri test("");}, BadRequestException);
}

TEST(LocationURITest, ValidInput){
	EXPECT_NO_THROW({
		LocationUri test("/test");
	});
	EXPECT_NO_THROW({
		LocationUri test("/test/");
	});
	{
		LocationUri test("/test/");
		EXPECT_TRUE(test.IsDir());
	}
	{
		LocationUri test("/test");
		EXPECT_FALSE(test.IsDir());
	}
}

//////////////////////////////
//**   MODULE Return      **//
//////////////////////////////

TEST(ReturnTest, InvalidInput) {
	EXPECT_THROW({
		ReturnDir test("");}, ReturnDir::MissingArgumentsException);
	EXPECT_THROW({
		ReturnDir test("a1 redirection_link");}, ReturnDir::InvalidReturnCodeException);
	EXPECT_THROW({
		ReturnDir test("301 redirection_link ddddd");}, ReturnDir::InvalidAmountOfArgumentsException);
EXPECT_THROW({
		ReturnDir test(" redirection_link");}, ReturnDir::InvalidReturnCodeException);
	EXPECT_THROW({
		ReturnDir test("-1 redirection_link");}, ReturnDir::InvalidReturnCodeException);
	EXPECT_THROW({
		ReturnDir test("1000 redirection_link");}, ReturnDir::InvalidReturnCodeException);
	}


TEST(ReturnTest, ValidInput){
	EXPECT_NO_THROW({
		ReturnDir test("301 url");
	});
	EXPECT_NO_THROW({
		ReturnDir test("999 url");
	});
	EXPECT_NO_THROW({
		ReturnDir test("0 url");
	});
	EXPECT_NO_THROW({
		ReturnDir test("1 url");
	});
	EXPECT_NO_THROW({
		ReturnDir test("42 url");
	});

}

//////////////////////////////
//**MODULE NGINX PARSING  **//
//////////////////////////////
TEST(NginxConfigTest, valid) {
	EXPECT_NO_THROW({
		NginxConfig test("../../../config_files/default.conf");
	});	
	EXPECT_NO_THROW({
		NginxConfig test("../../../config_files/multiple_servers.conf");
	});
	EXPECT_NO_THROW({
		NginxConfig test("../../../config_files/simple.conf");
	});	
}

TEST(NginxConfigTest, invalid) {
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/open_brackets.conf");}, NginxConfig::OpenBracketsException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/outside_server.conf");}, NginxConfig::BadServerContextException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/misspelled_server.conf");}, NginxConfig::BadServerContextException);
	EXPECT_THROW({
		NginxConfig test("../../config_files/bad_config_files/dfhdkfh.conf");}, NginxConfig::InvalidFileLocationException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/empty.conf");}, NginxConfig::NoServerContextsException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/double_listen");}, ServerContext::MultipleListensException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/double_Server_name");}, ServerContext::MultipleServerNameException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/bad_input");}, ConfigValues::InvalidDirectiveException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/double_location");}, ServerContext::DuplicateLocationUriException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/double_CMBS");}, ConfigValues::MultipleClientMaxBodySizeException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/location_error_cmbs");}, ConfigValues::MultipleClientMaxBodySizeException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/double_autoindex");}, ConfigValues::MultipleAutoindexException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/location_error_autoindex");}, ConfigValues::MultipleAutoindexException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/double_root");}, ConfigValues::MultipleRootException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/location_error_root");}, ConfigValues::MultipleRootException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/double_return");}, ConfigValues::MultipleReturnException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/location_error_return");}, ConfigValues::MultipleReturnException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/double_index");}, ConfigValues::MultipleIndexException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/location_error_index");}, ConfigValues::MultipleIndexException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/location_error_misspelling");}, ConfigValues::InvalidDirectiveException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/location_error_index");}, ConfigValues::MultipleIndexException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/double_allowed_methods.conf");}, LocationContext::MultipleAllowedMethodsException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/double_alias.conf");}, LocationContext::MultipleAliasException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/double_cgi.conf");}, LocationContext::MultipleCGIPassException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/root_alias.conf");}, LocationContext::RootAndAliasException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/misspelled_error.conf");}, ConfigValues::InvalidDirectiveException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/misspelled_listen.conf");}, ConfigValues::InvalidDirectiveException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/misspelled_index.conf");}, ConfigValues::InvalidDirectiveException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/misspelled_client_max_body_size.conf");}, ConfigValues::InvalidDirectiveException);
	EXPECT_THROW({
		NginxConfig test("../../../config_files/bad_config_files/misspelled_server.conf");}, NginxConfig::BadServerContextException);
	
}

//////////////////////////////
//** MODULE TargetConfig  **//
//////////////////////////////

