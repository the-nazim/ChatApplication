#include "server.h"

void Server::start()
{
    while(true)
    {
        int clientSocket = accept(serverSocket, nullptr,nullptr);
        if(clientSocket == -1)
        {
            cout << "Error in accepting connection" << endl;
            continue;
        }

        thread clientThread(handl_client, clientSocket);
        clientThread.detach();
    }
}

void handl_client(int clientSocket)
{
    char buffer[1024] = {0};
    while(true)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        
        if (bytesReceived <= 0) // Client disconnected or error occurred
            break;
            
        cout << "Message from client: " << buffer << endl;
    }
    close(clientSocket);
    exit(0);   
}


int main()
{
    Server server("127.0.0.1", 8080);
    server.start();

    return 0;
}



