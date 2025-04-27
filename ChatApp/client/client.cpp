#include <bits/stdc++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>

using namespace std;

int main()
{
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // sending connection request
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // sending data
    // const char* message = "Hello, server!";
    string message;
    cout<<"Enter the message: ";
    cin>>message;
    const char* to_send = message.c_str();

    send(clientSocket, to_send, strlen(to_send), 0);

    // closing socket
    close(clientSocket);

    return 0;
}