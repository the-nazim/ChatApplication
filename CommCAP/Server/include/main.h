#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <bits/stdc++.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <cstring>
#include <cstdlib>

using namespace std;
void handle_client(int clientSocket);

class Database 
{
    private:
        mongocxx::instance inst;
        mongocxx::database db;
        mongocxx::client conn;
        mongocxx::collection collection;
        string db_uri = "mongodb://172.19.64.1:27017/";
        string db_name = "testdb";
        string collection_name = "test_messages";
    public:
        Database(): inst(), conn{mongocxx::uri{"mongodb://172.19.64.1:27017/"}}, db_name("testdb"), collection_name("test_messages") 
        {
            db = conn[db_name];
            collection = db[collection_name];
        }

        void insertMessage(string message);
};

class Server
{
    private:
        int serverSocket;
        sockaddr_in serverAddress;
    
    public:
        Server(string ipAddress, int port)
        {
            serverSocket = socket(AF_INET, SOCK_STREAM,0);
            
            memset(&serverAddress, 0, sizeof(serverAddress));

            serverAddress.sin_family = AF_INET;
            serverAddress.sin_port = htons(port);
            serverAddress.sin_addr.s_addr = ipAddress.empty() ? INADDR_ANY : inet_addr(ipAddress.c_str());


            if(serverSocket == -1)
            {
                cout << "Error in creating socket" << endl;
                exit(1);
            }

            bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
            listen(serverSocket, 5);

            cout<<"Server started !!!"<<endl;
        }        

        void start();
        void reciveMessage();

        ~Server()
        {
            close(serverSocket);
        }
};