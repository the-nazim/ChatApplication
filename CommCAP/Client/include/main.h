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

class dbClient
{
    private:
        mongocxx::instance inst;
        mongocxx::database db;
        mongocxx::client conn;
        mongocxx::collection collection;

        string db_name = "testdb";
        string collection_name = "test_clients";

        public:
            dbClient(): inst(), conn{mongocxx::uri{"mongodb://172.19.64.1:27017/"}}, db_name("testdb"), collection_name("test_clients")
            {
                db = conn[db_name];
                collection = db[collection_name];
            }

            void registerClient();
            void loginClient();
};

class Client
{
    private:
        int clientSocket;
        sockaddr_in serverAddress;

    public:
        Client(string ipAddress, int port)
        {
            clientSocket = socket(AF_INET, SOCK_STREAM, 0);

            memset(&serverAddress, 0, sizeof(serverAddress));

            serverAddress.sin_family = AF_INET;
            serverAddress.sin_port = htons(port);
            inet_pton(AF_INET, ipAddress.c_str(), &serverAddress.sin_addr);

            if (clientSocket == -1)
            {
                cout << "Error in creating socket" << endl;
                exit(1);
            }

            if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
            {
                cout << "Error in connecting to server" << endl;
                exit(1);
            }
        }

        void sendMessage();

        ~Client()
        {
            close(clientSocket);
        }
};