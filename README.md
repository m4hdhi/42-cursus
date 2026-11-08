*This project has been created as part of the 42 curriculum by mamuzamm, mknbar, ccastro.*

# ft_irc

## Description

**ft_irc** is a small IRC (Internet Relay Chat) server written in C++98.
Real IRC clients (irssi, WeeChat, HexChat, `nc`...) can connect to it, authenticate with a
password, choose a nickname, join channels, and talk in channels or in private.

The goal of the project is to understand how a network server works: TCP sockets,
non-blocking I/O, handling many clients at the same time with a single `poll()`, and
following a real text protocol (RFC 1459 / RFC 2812).

### Features

- Authentication with a connection password: `PASS`, `NICK`, `USER`
- Channels: `JOIN`, `PART`, `TOPIC`, `WHO`
- Messages: `PRIVMSG` (to a channel or a user), `NOTICE`
- Channel operators (the creator of a channel is its first operator, shown as `@nick`):
  - `KICK` – eject a client from the channel
  - `INVITE` – invite a client to a channel
  - `TOPIC` – change or view the channel topic
  - `MODE` – change the channel modes:
    - `i` invite-only channel
    - `t` only operators can change the topic
    - `k` channel key (password)
    - `o` give / take operator rights
    - `l` user limit
- `PING` / `PONG`, `QUIT`

## Instructions

### Build

```bash
make          # builds ./ircserv
make clean    # removes object files
make fclean   # removes object files and binaries
make re       # rebuilds everything
```

Requirements: a C++ compiler (`c++`) and `make`. The code compiles with
`-Wall -Wextra -Werror -std=c++98` on Linux and macOS.

### Run the server

```bash
./ircserv <port> <password>
# example
./ircserv 6667 secret
```

Stop it with `ctrl+C`: every socket is closed cleanly.

### Connect with an IRC client

Reference client: **irssi**

```text
irssi
/connect 127.0.0.1 6667 secret mynick
/join #42
/msg #42 hello everyone
```

### Connect with nc

```bash
nc -C 127.0.0.1 6667
PASS secret
NICK alice
USER alice 0 * :Alice
JOIN #42
PRIVMSG #42 :hello everyone
```

A command can be sent in several pieces (type `com`, `ctrl+D`, `man`, `ctrl+D`, `d` and Enter):
the server keeps the pieces until the line is complete.

## Technical choices

- **One `poll()` for everything.** Every loop builds the list of sockets to watch: the
  listening socket and every client. `accept()`, `recv()` and `send()` are only called
  after `poll()` said the socket is ready. Every socket is non-blocking (`fcntl(fd, F_SETFL, O_NONBLOCK)`).
- **Output buffers.** Replies are never sent directly: they are added to the client's
  `outBuffer`, and the server asks `poll()` for `POLLOUT` only when that buffer is not empty.
  A slow client can never block the server.
- **Input buffers.** Received bytes are added to the client's `inBuffer`. Only complete lines
  (ending with `\n` or `\r\n`) are executed; the rest waits for the next `recv()`.
  A line longer than 512 bytes (the IRC limit) is refused with `417 Input line was too long`.
- **`errno` is never used** after `recv()`/`send()`: `0` or `-1` simply closes the connection.
- **Data structures.** `std::map<int, Client>` (key: socket fd) and
  `std::map<std::string, Channel>` (key: channel name). A channel stores its members,
  operators and invited users as sets of fds, so changing a nickname updates nothing else.

### Code layout

| Path | Content |
| --- | --- |
| `main.cpp` | argument checks, signals, starts the server |
| `src/Server.cpp` | sockets, the `poll()` loop, reading, writing, disconnecting |
| `src/Messages.cpp` | command dispatch, sending replies, finding users and channels |
| `src/Client.cpp`, `src/Channel.cpp` | the two data classes |
| `src/Utils.cpp` | splitting IRC lines, checking nicknames and channel names |
| `cmd/*.cpp` | one file per IRC command |
| `inc/Replies.hpp` | numeric reply codes (`461`, `482`...) |

## Resources

- [RFC 1459 – Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2812 – IRC: Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
- [Modern IRC Client Protocol](https://modern.ircdocs.horse/) – clear list of commands and numeric replies
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/) – sockets, `poll()`
- `man 2 poll`, `man 2 socket`, `man 2 recv`, `man 2 send`
- [irssi documentation](https://irssi.org/documentation/)
- [Small IRC Server – ft_irc (Medium)](https://medium.com/@afatir.ahmedfatir/small-irc-server-ft-irc-42-network-7cee848de6f9)

### Use of AI

Claude (Anthropic's AI assistant) was used to:

- check the project against the subject (single `poll()`, non-blocking I/O, no `send()`
  without `POLLOUT`, no use of `errno`, Makefile relinking, README requirements);
- find bugs (two crashes, lost partial lines, wrong `MODE` parameter parsing, `KICK`
  deleting the wrong channel, missing `PING`);
- refactor the server into simpler code (output buffers sent on `POLLOUT`,
  one shared line parser, channels storing fds instead of copies of clients);
- write test scripts (not submitted) and this README.

All generated code was reviewed, run and tested with `nc`, Python test clients and valgrind.
