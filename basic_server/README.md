# network-programming

## OSI model: Open Systems Interconnection model

The Open Systems Interconnection model is a conceptual model that describes seven layers
that computer systems use to communiccate over a network. 

<img src="https://www.imperva.com/learn/wp-content/uploads/sites/13/2020/02/OSI-7-layers.jpg" width="400px">

### OSI vs TCP/IP model

The Transfer Control Protocol / Internet Protocol defines how information moves from sender to receiver.
A key difference between the models is that TCP/IP is simpler, collapsing several OSI layers into one.

<img src="https://www.imperva.com/learn/wp-content/uploads/sites/13/2020/02/OSI-vs.-TCPIP-models.jpg" width="500px">

<br>

> ## To implement HTTP we only care about the **4th layer: Transport Layer**


### Transport Layer
The Transport layer is mainly responsible for ensuring that data is transferred from one point to
another reliably and without erros. It makes sure data is sent and received in the correct sequence.
This layer provides flow control and error handling. Common examples of Transport layer protocols are
Transmission Control Protocol (TCP) and User Datagram Protocol (UDP).

> ## We use TCP to implement HTTP as it is more reliable.

HTTP communication takes place over TCP/IP connections with as default port TCP 80. HTTP only presumes
a reliable transport, any protocol that provides such gurantees can be used.

> ## **STEP 1** implement the Transport Layer of HTTP, which is TCP, by learning TCP socket programming.

## TCP Socket Programming

A socket is a mechanism that gives programs access to the network. It allows messages to be sent and
received between applications. The steps involved in using sockes:
1. Create the socket.
2. Identify the socket.
3. On the server, wait for an incoming connection.
4. Send and reveice messages.
5. Close the socket.

### 1. Creating the socket

A socket is created with the socket system call.
```C++
int server_fd = socket(domain, type, protocol);
``` 

**`domain/address family`** -- there are 2 possible address domains, the unix domain for two processes which
share a common file system `AF_UNIX` , and the Internet domain for any two hosts on the internet `AF_INET`. <br>
**`type`** -- the type of socket, the 2 possibilities are a stream socket `SOCK_STREAM` in which characters are read 
in a contiguous stream as if from a file or pipe, and a datagram socket `SOCK_DGRAM` in which messages are read
in chuncks. <br>
**`protocol`** -- if this argument is zero (which is nearly always should be), the OS will choose the appropraite
protocol. It will choose TCP for stream sockets and UDP for datagram sockets. <br>
**return** -- the socket system call returns an entry into the FD, which is used for all references to this socket.
If socket call failes -1 will be returned.


> ### For TCP sockets we want to specify the IP address family as AF_INET and the type as SOCK_STREAM. Since there is only one form of virtual circuit server, there is no variation possible on the protocol, so its set to 0.

<br>
Code for creating the TCP socket:

```C++
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
  perror("cannot creat socket");
  return (0);
}
```

### 2. Identify/naming a socket

When we talk about naming a socket, we mean assigning a transport address to the socket (a port number in IP networking).
This operationg is called binding an address and the bind system call is used for this. The transport address is 
definied in a socket address structure. The sockaddr's structures format is determined on the address family you are using.

System call for bind: 

```C++
int bind(int socket, const struct sockaddr *address, socklen_t address_len);
```

`socket` -- the socket that was created with the socket system call, socket_fd. <br>
`sockaddr` -- a generic container that allows the OS to read the first couple of bytes that identify the address family.
The address family detemines what variant of the sockaddr struct to use that contains elements that make sense for that
specific communication type. For IP networking we use `struct sockaddr_in`, which is definde in `netinet/in.h`. 
This struct needs to be filled before calling bind. <br>
`address_len` -- the address structure may differ based on type of transport used, this third parameter specifies the
length of this structure, wich is simply `sizeof(struct sockaddr_in)`.<br> 

``` C++
struct sockaddr_in {
    __unit8_t       sin_len;
    sa_family_t     sin_family;
    in_port_t       sin_port;
    struct in_addr  sin_addr;
    char            sin_zero[8];
};
```

`sin_family` -- the address family we used when we set up the socket, `AF_INET` in our case. <br>
`sin_port` -- the port number (transport address). You can specify one or let the OS assign one. If you're a server 
you'll generally pick a specific port number, as the client will need to know which port to connect to. <br>
`sin_addr` -- The address for this socket, which is your machine's IP address. It is a structure of type `struct in_addr`, 
which only contains a single field `unsigned long s_addr`, which contains the IP address of the host. Most of the time we
don't care to specify a specific interface als let the OS choose. The special address for this is 0.0.0.0 defined by 
`INADDR_ANY`. <br>

<br>

Code for binding a socket: 
```C++
struct sockaddr_in  address;
const int port = 8080; // this is where the client can reach at

memset((char*)&address, 0, sizeof(address));

address.sin_family = AF_INET;
address.sin_addr.s_addr = htonl(INADDR_ANY); // htonl converts a long integer (address) to a network representation
address.sin_port = htons(PORT); // converts a short integer (port) to a network representation

if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
  perror("bind failed");
  return (0);
}
```

### 3. On the server, wait for an incoming connection

Before a client can connect to a server, the server should have a socket prepared to accept connections. The listen
system call tells a socket that it should be capable of accepting incoming connections:

```C++
int listen(int socket, int backlog);
```

`socket` -- the socket file descriptor. <br>
`backlog` -- the size of the backlog queue, the number of connections that can be waiting while the process is handling
a particular connection. <br>

The accept system call grabs the first connection request on the queue of the pending connections and creates a new socket
for that connection. 

The original socket set up for listening is used only for accepting connection, not for exchanging data.

```C++
int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
```

`socket` -- the socket that was set up for accepting connections with listen.
`address` -- the address structure that gets filled in with the address of the client that is connecting. 
`address_len` -- the lenght of the address structure

The code to listen and accept:

```C++
if (listen(server_fd, 3) < 0) {
  perror("In listen");
  exit (EXIT_FAILURE);
}

if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
  perror("In accept");
  exit(EXIT_FAILURE);
}
```

### 4. Send and receive messages

We have now connected sockets between a client and a server (when you visit IP address of your server from a web browser).

Communication between these is the easy part.
```C++
char buffer[1024] = {0};
int valread = read( new_socket , buffer, 1024); 
printf(“%s\n”,buffer );
if(valread < 0) { 
    printf("No bytes are there to read");
}
char *hello = "Hello from the server";
write(new_socket , hello , strlen(hello));
```

### 5. Close the socket

When done communicating we should close the socket.
```C++
close(new_socket);
```

> ## first execute the server-side code, then client or webbrowser
<br>

## HTTP

The HTTP client (web browser) sends a HTTP request to the HTTP server.<br>
The server processes the request received and sends HTTP response to the HTTP client.

<img src="https://miro.medium.com/max/393/1*JSnJtHpU7cWUnWIgGupu7w.png" width="300"> <br>

### HTTP CLIENT

The client is always the one that initiates the connection. <br>
**We want to connect to the server -> we type in a URL/address into the browser.**

`http://www.example.com:80/index.html`

The browser fetches the file `index.html` from a web server. When typing in: `www.example.com` the browser reconstructs it to: `http://www.example.com:80`, and sends it to the server. 

If the server has certain default pages, its decided by the name of the file. Some server have `public.html` and some have `index.html`.

**EXAMPLE**: consider index.html as default page

<img src="https://miro.medium.com/max/1400/1*Yqq-60D9mD4NVuhFd4IoFg.png" width="400">
<br> <br>

> ### 1. Run the TCP server-side code<br>2. open your web-browser and enter localhost:8080/index.html in the address bar.<br>3. Check terminal output.

<br>

### HTTP Methods

HTTP works as a request-response protocol bewteen client and server. A client (browser) sends a request to the server; then the server returns a response to the client. This response contains information about the request. 

* #### `GET` method
GET requests a representation of the specified resource. Requests using GET should only be used to request data, they shouldn't include data.<br>
```
GET /index.html
```

* #### `POST` method
POST sends data to the server. The type of the body of the request is indicated by the Content-Type header. A POST request is typically sent via an HTML form and results in a change on the server.<br>
```
POST /test
```

* #### `DELETE`
DELETE delets the specified resource.
```
DELETE /file.html HTTP/1.1
```

### HTTP server
The client sent us some headers and expects the same from the server in return.
The borwser is expecting the same format response in which it sent us the request. The format the web browser is expecting:

<img src="https://miro.medium.com/max/1400/1*5QCrgA5LoA8AKR30ce6x5A.png" width=400>

If we want to send a messgae, we first need to construct the header. Then insert a blank line, followed by our data, or the body.

A minimal HTTP header would be: `"HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!"`

These 3 headers are minimum required:
* `HTTP/1.1 200 OK` - mentions the version of HTTP, Status code and Status message.
* `Content-Type: text/plane` - This says the server is sending plain text.
* `Content-Length: 12` - It mentions how many bytes the server is sending to the client, the client will only read the amount that we mention here.

The body part is where we send our data. We calculate how many bytes we are sending with the body,
mention that in Content-Length and set the Content-Type appropriately.

### Status Code and Status Messages

Status codes are issued by a server in response to a client's request made to the server. It includes codes form IETF RFCs, other specifications and some additional code used in common applications of the HTTP.

The first digit of the status code specified one of five standard classes of response. 

* 1xx informational response – the request was received, continuing process
* 2xx successful – the request was successfully received, understood, and accepted
* 3xx redirection – further action needs to be taken in order to complete the request
* 4xx client error – the request contains bad syntax or cannot be fulfilled
* 5xx server error – the server failed to fulfil an apparently valid request

[Detailed information about status codes.](https://en.wikipedia.org/wiki/List_of_HTTP_status_codes)

> ### Type in localhost:8080 in the browser


So know we are able to send a string.
How do we send a requested web page to a client?

Suppose we enter `localhost:8080/info.html` in the address bar, this sends the following request to the server:

```
GET /info.html HTTP/1.1
Host: localhost:8080
Connection: keep-alive
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.162 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
DNT: 1
Accept-Encoding: gzip, deflate, br
Accept-Language: en-US,en;q=0.9
```

This means we need to search for the `info.html` file in the root directory of the server. The cases that can happen:
* the file (web page) is present
* the file (web page) is absent
* the client does not have permission to acces the file (webpage)

Select the status code approriate. <br>
If the file is present and the client has permissions to access it, select the approrpiate `Content-Type` : [link to content types.](https://docs.microsoft.com/en-us/previous-versions/exchange-server/exchange-10/ms526508(v=exchg.10)?redirectedfrom=MSDN).

Open that file and read the data into a variable. Count the number of bytes read from the file. When you read a simple text file, we can count while reading the file or from the return value of the read function. Finally set the `Content-Length` and construct the response header.

Now add a newline at the end of the response header and append the data to it which we have read from the file. And send the response header to the client.



## Resources
https://www.youtube.com/watch?v=bdIiTxtMaKA&list=PL9IEJIKnBJjH_zM5LnovnoaKlXML5qh17

https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa
https://www.ietf.org/rfc/rfc2616.txt
https://www.linuxhowtos.org/C_C++/socket.htm

https://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf
https://www.youtube.com/watch?v=gntyAFoZp-E

still read: https://ruslanspivak.com/lsbaws-part1/

nice slides: https://www.cs.cmu.edu/~srini/15-441/S10/lectures/r01-sockets.pdf