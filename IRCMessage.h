#ifndef IRC_MESSAGE_H
#define IRC_MESSAGE_H

#include <string>
#include <vector>
#include <optional>

// Represents a single, parsed IRC message.
// Using a struct to signal that this is primarily a plain data container.
struct IRCMessage {
    // The prefix, indicating the message's origin (e.g., ":nickname!user@host").
    // Optional because not all messages have a prefix.
    std::optional<std::string> prefix;

    // The main command (e.g., "PRIVMSG", "JOIN", "001").
    std::string command;

    // The list of parameters for the command.
    // The final parameter might be a "trailing" parameter, which can contain spaces.
    std::vector<std::string> params;
};

// Parses a raw IRC message line into an IRCMessage object.
IRCMessage parse(const std::string& line);

#endif // IRC_MESSAGE_H
