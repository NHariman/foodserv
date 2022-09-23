#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/config/directive_validation/directive_validation.hpp"
#include "../../src/resolved_target/server_selection.hpp"

using namespace std;

// function to compare get the chosen server context
void    compareChosenServer(string expect_port, string chosen_port, vector<string> expect_servername, vector<string> chosen_servername) {
    EXPECT_EQ(expect_port, chosen_port);
    EXPECT_EQ(expect_servername.size(), chosen_servername.size());
    if (expect_servername.size() != 0) {
        for (vector<string>::iterator it = expect_servername.begin(); it != expect_servername.end(); it++) {
            for (vector<string>::iterator it2 = chosen_servername.begin(); it2 != chosen_servername.end(); it2++)
                EXPECT_EQ(*it, *it2);
        }
    }
}

TEST(ServerSelectionTest, TestConfig1) {
    NginxConfig	test1("/Users/sannealbreghs/Desktop/foodserv/config_files/test_config/conf1.conf");

    {
        ServerSelection	select("localhost", "80", test1.GetServers());

        string			chosen_port = select.GetChosenServerContext().GetPortNumber();
        vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

    	string expect_port = "80";
     	vector<string> expect_servername; // empty

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
    }

    {
        ServerSelection	select("", "80", test1.GetServers());

        string			chosen_port = select.GetChosenServerContext().GetPortNumber();
        vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

    	string expect_port = "80";
     	vector<string> expect_servername; // empty

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
    }

    {
        ServerSelection select("localhost", "8080", test1.GetServers());

        string			chosen_port = select.GetChosenServerContext().GetPortNumber();
        vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

    	string expect_port = "8080";
     	vector<string> expect_servername; // empty

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
    }

    {
        ServerSelection select("", "8080", test1.GetServers());

        string			chosen_port = select.GetChosenServerContext().GetPortNumber();
        vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

    	string expect_port = "8080";
     	vector<string> expect_servername; // empty

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
    }

    {
        ServerSelection select("localhost", "666", test1.GetServers());

        string			chosen_port = select.GetChosenServerContext().GetPortNumber();
        vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

    	string expect_port = "80";
     	vector<string> expect_servername; // empty

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
    }

    {
        ServerSelection select("", "666", test1.GetServers());

        string			chosen_port = select.GetChosenServerContext().GetPortNumber();
        vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

    	string expect_port = "80";
     	vector<string> expect_servername; // empty

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
    }
}

TEST(ServerSelectionTest, TestConfig2) {
    NginxConfig	test2("/Users/sannealbreghs/Desktop/foodserv/config_files/test_config/conf2.conf");
    {
        ServerSelection	select("localhost.com", "80", test2.GetServers());

        string			chosen_port = select.GetChosenServerContext().GetPortNumber();
        vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

    	string expect_port = "80";
     	vector<string> expect_servername; // empty

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
    }	
    {
        ServerSelection	select("", "80", test2.GetServers());

        string			chosen_port = select.GetChosenServerContext().GetPortNumber();
        vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

    	string expect_port = "80";
     	vector<string> expect_servername; // empty

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
    }

    {
        ServerSelection	select("localhost.com", "8080", test2.GetServers());

        string			chosen_port = select.GetChosenServerContext().GetPortNumber();
        vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

    	string expect_port = "8080";
     	vector<string> expect_servername = {"localhost.com"};

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
    }	
    {
        ServerSelection	select("haha not matching", "8080", test2.GetServers());

        string			chosen_port = select.GetChosenServerContext().GetPortNumber();
        vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

    	string expect_port = "8080";
     	vector<string> expect_servername = {"localhost.com"};

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
    }

    {
        ServerSelection	select("localhost.com", "777", test2.GetServers());

        string			chosen_port = select.GetChosenServerContext().GetPortNumber();
        vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

    	string expect_port = "8080";
     	vector<string> expect_servername = {"localhost.com"};

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
    }	
    {
        ServerSelection	select("crapperdiecrap", "777", test2.GetServers());

        string			chosen_port = select.GetChosenServerContext().GetPortNumber();
        vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

    	string expect_port = "80";
     	vector<string> expect_servername;

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
    }
}

TEST(ServerSelectionTest, TestConfig3) {
    NginxConfig	test3("/Users/sannealbreghs/Desktop/foodserv/config_files/test_config/conf3.conf");

	{
		ServerSelection	select("bad example", "80", test3.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "80";
		vector<string>	expect_servername; // empty

		compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
	}

	{
		ServerSelection	select("example.com", "80", test3.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "80";
		vector<string>	expect_servername = {"example.com"};

		compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
	}

	{
		ServerSelection	select("take_first", "10101", test3.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "80";
		vector<string>	expect_servername;

		compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
	}

	{
		ServerSelection	select("example.com", "10101", test3.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "80";
		vector<string>	expect_servername = {"example.com"};

		compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
	}
}

TEST(ServerSelectionTest, TestConfig4) {
	NginxConfig	test4("/Users/sannealbreghs/Desktop/foodserv/config_files/test_config/conf4.conf");

	{
		ServerSelection	select("", "", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "80";
		vector<string>	expect_servername;
	}

	{
		ServerSelection	select("", "80", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "80";
		vector<string>	expect_servername;
	}

	{
		ServerSelection	select("very random shit", "", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "80";
		vector<string>	expect_servername;
	}

	{
		ServerSelection	select("test.com", "77777", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "80";
		vector<string>	expect_servername{"test.com", "test.nl", "test"};
	}
	{
		ServerSelection	select("test.nl", "", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "80";
		vector<string>	expect_servername{"test.com", "test.nl", "test"};
	}
	{
		ServerSelection	select("test", "80", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "80";
		vector<string>	expect_servername{"test.com", "test.nl", "test"};
	}

	{
		ServerSelection	select("test", "808", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "808";
		vector<string>	expect_servername{"test3.com", "test3.nl", "test3"};
	}

	{
		ServerSelection	select("test3", "80", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "808";
		vector<string>	expect_servername{"test3.com", "test3.nl", "test3"};
	}
	{
		ServerSelection	select("hell_yeah", "80", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "80";
		vector<string>	expect_servername{"hell_yeah"};
	}

	{
		ServerSelection	select("", "808", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "808";
		vector<string>	expect_servername{"test3.com", "test3.nl", "test3"};
	}
	{
		ServerSelection	select("test_this_one", "808", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "808";
		vector<string>	expect_servername{"test3.com", "test3.nl", "test3", "test_this_one"};
	}
	{
		ServerSelection	select("test_this_one", "80", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "808";
		vector<string>	expect_servername{"test3.com", "test3.nl", "test3", "test_this_one"};
	}
		{
		ServerSelection	select("nothing_matches", "80", test4.GetServers());

		string			chosen_port = select.GetChosenServerContext().GetPortNumber();
		vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

		string			expect_port = "80";
		vector<string>	expect_servername;;
	}

}

// TEST SYNTAX
// {
// 	ServerSelection	select("nothing", "80", test3.GetServers());

// 	string			chosen_port = select.GetChosenServerContext().GetPortNumber();
// 	vector<string>	chosen_servername = select.GetChosenServerContext().GetServerNameVector();

// 	string			expect_port = 
// 	vector<string>	expect_servername =

// 	compareChosenServer(expect_port, chosen_port. expect_servername, chosen_servername);
// }
