#include <gtest/gtest.h>
#include "../../src/config/listen.hpp"

/*
    Test syntax
    
    TEST(TestSuiteName, TestName) {
    ... test body ...
    }
*/

/*

LISTEN: sets the address and port for IP, both address and port, or only address or only port can be specified.
		an address may also be a hostname.

all possibilities to check for: 

syntax: 
listen address[:port];

default:
listen *:80;
or
listen *:8000;

good ones:

listen 127.0.0.1:8000;
listen 127.0.0.1;
listen 8000;
listen *:8000;
listen localhost:8000;
listen [::]:8000;
listen [::1];

*/

TEST(ListenTests, ValidInput) {
    EXPECT_NO_THROW( {

    });
}

TEST(ListenTests) {
	EXPECT_THROW({

	});
}