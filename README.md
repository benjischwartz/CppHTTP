# CppHTTP

## Idea
Personal project to build an HTTP web server from scratch in C++, using only the standard library

## Concepts
### HTTP Server
Hypertext Transfer Protocol. Protocol for sending/receiving data over the internet.
Server is a computer that serves data over a network via HTTP.
![image info](./pictures/webserver.png)

### Web Client
A wider term that encompasses both web browsers and web applications.

### HTTP Request/Response
Web server is powered by HTTP server :
1) receives request and process it
2) determines response after checking
3) sends response to web  client (may include data, e.g. HTML stored on webserver)

### TCP (Transmission Control Protocol)
- Operates at "transport layer" of internet model - this sits above the "network layer" which is IP.
- Connection-based protocol used for HTTP servers. It guarantees the integrity of the data being communicated over a network (compared to UDP which is connectionless).
- TCP ensure packet delivery by assigning a sequence number to each byte sent, and receiver acknowledges it, specifying the expected sequence number for the next packet.
- TCP detects lost, duplicated or out of order packets, and requests re-transmission of lost data, or rearranges data. Can incur long delays (optimises accuracy over timely delivery).
- Positive acknowledgement with re-transmission: receiver required to respond with acknowledgement message it received the data. Sender keeps a record of each sent packet and maintains a timer from when the packet was sent. Sender re-transmits a packet if timer expires before receiving the acknowledgement.
- TCP divides data into "segments" which IP then handles the delivery of. TCP layer on client side re-assembles packets and ensures correct and error-free ordering for the receiving application.


### Ports & Sockets
- TCP Socket is an endpoint *instance* defined by *IP address* and a *port*. Used in context of a TCP connection or a listening state. Ports differentiate multiple endpoints on a given network address.
- TCP *connection* is defined by two endpoints aka sockets.
- Port is a virtualisation identifier defining a service endpoint (vs a service instance endpoint which is a session identifier). Makes multiple concurrent connections on a single network interface possible.
- TCP socket is not a connection, but endpoint of a specific connection.
- Can be concurrent connections to a service endpoint, but *only one* listener socket for a given address/port combination.

#### TLDR: 

A **socket** (e.g. 10.1.1.2, tcp, port1030) consists of
  1) An IP address
  2) A transport protocol
  3) A port number

A **port** (e.g. 1030) is between 1 and 65535 inclusive, and is a logical gate in a device. Every connnection between client/server requires a unique socket.

## Implementation

### Libraries
This project will be using the POSIX sockets API (a standardized interface for networking communication). It's available on a wide range of Unix-like systems, and for our purposes (using MacOS) this works. The sockets API supports both TCP and UDP. The API can be used with C++.
We will use the "Sys/socket" and "Arpa/inet" libraries.

### Creating a socket
The ```socket``` API takes three parameters:
```int socket(int domain, int type, int protocol)```
1) domain: is the communication domain - we will use ```AF_INET``` for IPv4 Protocols.
2) type: type of communication structure socket will allow - we will use ```SOCK_STREAM``` which allows reliable, full-duplex (both readable and writable) byte streams.
3) protocol: specifies protocol socket will use - there is only one that supports ```SOCK_STREAM``` so we set this to ```0```.


