#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/config/directive_validation/directive_validation.hpp"

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
		Autoindex test("on");
	});
	EXPECT_NO_THROW({
		Autoindex test("off");
	});
}

TEST(AutoIndexTest, invalidInput) {
	EXPECT_THROW({
		Autoindex test("onf");
	}, Autoindex::InvalidAutoindexException);
	EXPECT_THROW({
		Autoindex test("offe");
	}, Autoindex::InvalidAutoindexException);
	EXPECT_THROW({
		Autoindex test("1");
	}, Autoindex::InvalidAutoindexException);
	EXPECT_THROW({
		Autoindex test("off e");
	}, Autoindex::InvalidAutoindexException);
	EXPECT_THROW({
		Autoindex test("on e");
	}, Autoindex::InvalidAutoindexException);
	EXPECT_THROW({
		Autoindex test("k on");
	}, Autoindex::InvalidAutoindexException);
	EXPECT_THROW({
		Autoindex test("oh off");
	}, Autoindex::InvalidAutoindexException);
	EXPECT_THROW({
		Autoindex test("");
	}, Autoindex::MissingArgumentsException);
}

//////////////////////////////
//**   MODULE ERROR PAGE  **//
//////////////////////////////

TEST(ErrorPageTest, ValidInput) {
	EXPECT_NO_THROW({
		ErrorPage test("500 502 503 504 /50x.html");
	});
	EXPECT_NO_THROW({
		ErrorPage test("404             /404.html");
	});
	EXPECT_NO_THROW({
		ErrorPage test("404 /404.html");
	});
	EXPECT_NO_THROW({
		ErrorPage test("500 502 503 504 404 403 402 405 /50x.html");
	});
}

TEST(ErrorPageTest, InvalidInput) {
	EXPECT_THROW({
		ErrorPage test("404 /404.html 404");
	}, ErrorPage::InvalidInputException);
	EXPECT_THROW({
		ErrorPage test("404 404.html /stuff.html");
	}, ErrorPage::InvalidInputException);
	EXPECT_THROW({
		ErrorPage test("404 abc /404.html");
	}, ErrorPage::InvalidInputException);
	EXPECT_THROW({
		ErrorPage test("404d 404 /404.html");
	}, ErrorPage::InvalidInputException);
	EXPECT_THROW({
		ErrorPage test("404 404.html");
	}, ErrorPage::InvalidInputException);
	EXPECT_THROW({
		ErrorPage test("404 /404.html /404.html");
	}, ErrorPage::DuplicateUriException);
	EXPECT_THROW({
		ErrorPage test("");
	}, ErrorPage::MissingArgumentsException);
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
//**   MODULE FASTCGIPASS **//
//////////////////////////////

TEST(FastcgipassTest, InvalidInput) {
	EXPECT_THROW({
		FastCGIPass test("");
	}, FastCGIPass::MissingArgumentsException);
	EXPECT_THROW({
		FastCGIPass test("dadfadf dafdfsafadsf");
	}, FastCGIPass::TooManyArgumentsException);
}

TEST(FastcgipassTest, ValidInput){
	EXPECT_NO_THROW({
		FastCGIPass test("link_here");
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
		EXPECT_TRUE(test.IsDirectory());
	}
	{
		LocationUri test("/test");
		EXPECT_FALSE(test.IsDirectory());
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