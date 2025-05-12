#include <bits/stdc++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <thread>

using namespace std;

void recieveMessage(int socket)
{
    char buffer[1024];
    while (true) 
    {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(socket, buffer, sizeof(buffer), 0);
        if (bytes <= 0) {
            cout << "Disconnected from server.\n";
            break;
        }
        cout << "\nMessage from server: " << buffer << endl;
    }
}

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        cerr << "Connection Failed." << endl;
        return 1;
    }

    thread recvThread(recieveMessage, clientSocket);

    string message;
    while (true) {
        cout << "Enter the message: ";
        getline(cin, message);
        if (message == "exit") {
            close(clientSocket);
            break;
        }
        send(clientSocket, message.c_str(), message.size(), 0);
    }

    recvThread.join(); // Wait for receive thread
    return 0;
}






// int main()
// {
//     // creating socket
//     int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

//     // specifying address
//     sockaddr_in serverAddress;
//     serverAddress.sin_family = AF_INET;
//     serverAddress.sin_port = htons(8080);
//     serverAddress.sin_addr.s_addr = INADDR_ANY;

//     // sending connection request
//     connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

//     string message;
    
//     thread recvThread(recieveMessage, clientSocket);

//     while(1)
//     {
//         cout<<"Enter the message: ";
//         getline(cin,message);
//         const char* to_send = message.c_str();
//         send(clientSocket, to_send, strlen(to_send), 0);
//     }


//     // closing socket
//     close(clientSocket);
//     recvThread.join();
//     return 0;
// }