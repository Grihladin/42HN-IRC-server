# 42HN IRC Server

A IRC server written in modern C++ (C++17). It handles multiple clients and a subset of core IRC commands to join channels, exchange messages, and manage basic modes.

## Features
> Fast, simple, and compatible with common IRC clients
>
> - Modern C++17
> - Non-blocking sockets (no TLS)
> - Multi-client support
> - Works perfectly with KVIrc client
> - Implemented IRC commands:
>   - Registration/identity: PASS, NICK, USER
>   - Connection/health: PING, PONG, QUIT
>   - Channels: JOIN, PART, TOPIC, LIST, INVITE, KICK, MODE, WHO
>   - Messaging: PRIVMSG
>   - Operator: OPER

Note: Behavior follows a simplified subset of typical IRC servers and may not be fully RFC-complete.

## Requirements
- macOS/Linux
- g++ with C++17 support

## Build
Use the provided Makefile.

```fish
make        # build ircserv
make clean  # remove object files
make fclean # remove objects and binary
make re     # full rebuild
```

## Run
The server expects a TCP port and a server password.

```fish
./ircserv <port> <password>
# example
./ircserv 6667 secret
```

## Quick test
You can connect with a terminal client (netcat) or a GUI/TTY IRC client.

- Minimal handshake over netcat:

```text
PASS secret
NICK alice
USER alice alice alice alice
```

- With irssi (example):

Once connected, try basic commands like joining and messaging:

```text
JOIN #Channel1
PRIVMSG #Channel1 :Hello everyone!
LIST
WHO #Channel1
TOPIC #Channel1 :A new topic
QUIT :bye
```

## Project layout
- `inc/` — public headers (Channel.hpp, Command.hpp, Definitions.hpp, IrcServer.hpp, User.hpp)
- `src/` — sources
  - core files: `main.cpp`, `IrcServer.cpp`, `User.cpp`, `Channel.cpp`, `Command.cpp`, `Parser.cpp`, `IrcServerParser.cpp`, `IrcServerCommandExecutor.cpp`
  - commands: `src/Commands/*.cpp` (IRC command handlers)
  - server helpers: `src/IrcServer/*.cpp` (I/O helpers, utilities)
- `Makefile` — build rules for `ircserv`

## Notes
- Non-blocking sockets are used; no TLS.
- No persistence across restarts.
- Tested on Linux and macOS.
