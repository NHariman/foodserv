#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/config/directive_validation/directive_validation.hpp"
#include "../../src/config/server_selection.hpp"

// function to compare get the chosen server context
void    compareChosenServer(std::string expect_port, std::string chosen_port, std::vector<std::string> expect_servername, std::vector<std::string> chosen_servername) {
    EXPECT_EQ(expect_port, chosen_port);
    EXPECT_EQ(expect_servername.size(), chosen_servername.size());
    if (expect_servername.size() != 0) {
        for (std::vector<std::string>::iterator it = expect_servername.begin(); it != expect_servername.end(); it++) {
            for (std::vector<std::string>::iterator it2 = chosen_servername.begin(); it2 != chosen_servername.end(); it2++)
                EXPECT_EQ(*it, *it2);
        }
    }
}

TEST(ServerSelectionTest, TestConfig1) {
    NginxConfig	test1("/Users/sannealbreghs/Desktop/foodserv/test_config/conf1.conf");

    {
        ServerSelection	select("localhost", "80", test1.GetServers());

        std::string chosen_port = select.GetChosenServerContext().GetPortNumber();
        std::vector<std::string> chosen_servername = select.GetChosenServerContext().GetServerNameVector();

        std::string expect_port = "80";
        std::vector<std::string> expect_servername; // empty

        compareChosenServer(expect_port, chosen_port, expect_servername, chosen_servername);
        // EXPECT_EQ(server_context_selection.GetHost(), "80");
        // EXPECT_EQ(server_context_selection.Get)
    }

    {
        ServerSelection server_context_selection("localhost", "8080", test1.GetServers());
    }
}

// ASSERT_STREQ(str1, str2);	use the assert string equal to check config input
