#include <iostream>
#include <vector>
#include "IRCMessage.h"

// Helper function to print a parsed message for verification.
void print_message(const std::string& raw_line, const IRCMessage& msg) {
    std::cout << "--> " << raw_line << std::endl;
    if (msg.prefix) {
        std::cout << "  Prefix: " << *msg.prefix << std::endl;
    }
    std::cout << "  Command: " << msg.command << std::endl;
    if (!msg.params.empty()) {
        std::cout << "  Params (" << msg.params.size() << "):" << std::endl;
        for (size_t i = 0; i < msg.params.size(); ++i) {
            std::cout << "    " << i << ": " << msg.params[i] << std::endl;
        }
    }
    std::cout << "----------------------------------------" << std::endl;
}

int main() {
    std::vector<std::string> test_cases = {
        // Common cases
        ":Nick!user@host JOIN #channel",
        ":irc.server.net 001 MyNick :Welcome to the Internet Relay Network MyNick",
        "PRIVMSG #chat :Hello everyone! This is a test.",
        "PING :123456789",

        // Cases with multiple middle params
        "MODE #channel +o user1",
        ":server.name MODE #channel +v user2",

        // Edge cases
        "QUIT", // Command with no params
        "NICK new_nick", // Command with one param
        ":server.name NOTICE Auth :*** Looking up your hostname...", // Server notice
        ":some_user!~user@host PRIVMSG #another_channel :This is a message with a : colon inside."
    };

    for (const auto& line : test_cases) {
        try {
            IRCMessage msg = parse(line);
            print_message(line, msg);
        } catch (const std::runtime_error& e) {
            std::cerr << "Failed to parse '" << line << "': " << e.what() << std::endl;
            std::cerr << "----------------------------------------" << std::endl;
        }
    }

    return 0;
}
