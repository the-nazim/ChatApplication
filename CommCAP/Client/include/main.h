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
    
}