#include "Command.hpp"
#include <iostream>
#include <vector>

// Helper function to print a parsed message for verification.
void print_message(const std::string &raw_line, const Command &cmd) {
  std::cout << "--> " << raw_line << std::endl;
  std::cout << "  Command: " << cmd.getCommand() << std::endl;
  if (!cmd.getParams().empty()) {
    std::cout << "  Params (" << cmd.getParams().size() << "):" << std::endl;
    for (size_t i = 0; i < cmd.getParams().size(); ++i) {
      std::cout << "    " << cmd.getParams()[i].name << ": "
                << cmd.getParams()[i].value << std::endl;
    }
  }
  std::cout << "----------------------------------------" << std::endl;
}
int main() {
  std::vector<std::string> test_cases = {
      // Common cases
      ":Nick!user@host JOIN #channel",
      ":irc.server.net 001 MyNick :Welcome to the Internet Relay Network "
      "MyNick",
      "PRIVMSG #chat :Hello everyone! This is a test.", "PING :123456789",

      // Cases with multiple middle params
      "MODE #channel +o user1", ":server.name MODE #channel +v user2",

      // Edge cases
      "QUIT",          // Command with no params
      "NICK new_nick", // Command with one param
      ":server.name NOTICE Auth :*** Looking up your hostname...", // Server
                                                                   // notice
      ":some_user!~user@host PRIVMSG #another_channel :This is a message with "
      "a : colon inside."};

  for (const auto &line : test_cases) {
    try {
      Command msg = Command::parse(line);
      print_message(line, msg);
    } catch (const std::runtime_error &e) {
      std::cerr << "Failed to parse '" << line << "': " << e.what()
                << std::endl;
      std::cerr << "----------------------------------------" << std::endl;
    }
  }

  return 0;
}
