# Simple Chat Application

A basic client-server chat application implemented in C using TCP sockets.

## Features
- Single client-server communication
- Real-time message exchange
- Simple command-line interface
- Cross-platform compatibility (Unix-based systems)

## Prerequisites
- GCC Compiler
- POSIX-compliant operating system
- Basic understanding of terminal/command line

## Project Structure
```
simple-chat/
├── src/
│   ├── server.c
│   └── client.c
├── Makefile
└── README.md
```

## Installation

1. Clone the repository:
```bash
git clone https://github.com/stephenombuya/Simple-Chat-Application
cd simple-chat
```

2. Compile the applications:
```bash
gcc -o server src/server.c
gcc -o client src/client.c
```

Or use the provided Makefile:
```bash
make all
```

## Usage

1. Start the server:
```bash
./server
```

2. In a separate terminal, start the client:
```bash
./client
```

3. Begin chatting:
   - Type messages in either window and press Enter to send
   - The server displays "Client connected" when a client joins
   - The client displays "Connected to server" upon successful connection

## Configuration

Default settings in both programs:
- Port: 8080
- Server IP: 127.0.0.1 (localhost)
- Buffer Size: 1024 bytes

To modify these settings, update the corresponding #define directives in the source files.

## Technical Details

### Server (server.c)
- Creates TCP socket
- Binds to specified port
- Listens for incoming connections
- Accepts single client connection
- Handles bidirectional communication

### Client (client.c)
- Creates TCP socket
- Connects to server IP/port
- Manages user input/output
- Handles bidirectional communication

## Error Handling
The application handles common errors including:
- Socket creation failures
- Connection errors
- Send/receive failures
- Invalid address errors

## Limitations
- Supports only one client at a time
- No message encryption
- Basic error handling
- No persistent message history

## Future Improvements
- Multi-client support
- Message encryption
- GUI interface
- File transfer capabilities
- Persistent chat history
- Username support

## Contributing
1. Fork the repository
2. Create feature branch
3. Commit changes
4. Push to branch
5. Open pull request

## License
This project is licensed under the GNU License - see `LICENSE` file for details.


## Acknowledgments
- POSIX Socket Programming Documentation
- Unix Network Programming by W. Richard Stevens
