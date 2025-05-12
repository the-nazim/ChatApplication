#include "../include/main.h"

void Database::insertMessage(string message)
{
    bsoncxx::builder::basic::document doc_builder{};
    doc_builder.append(bsoncxx::builder::basic::kvp("username", "client1"));
    doc_builder.append(bsoncxx::builder::basic::kvp("message", message));
    doc_builder.append(bsoncxx::builder::basic::kvp("timestamp", bsoncxx::types::b_date{std::chrono::system_clock::now()}));
    
    auto result = collection.insert_one(doc_builder.view());

    cout<< "Inserted document ID: " << result->inserted_id().get_oid().value.to_string() << endl;
    cout << "Inserted message: " << message << endl;
}

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

        {
            lock_guard<mutex> lock(mtx);
            clients.push_back(clientSocket);
        }

        thread clientThread(handle_client, clientSocket);
        clientThread.detach();
    }
}

void handle_client(int clientSocket)
{
    char buffer[1024] = {0};
    // Database db;
    while(true)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        
        if (bytesReceived <= 0) // Client disconnected or error occurred
            break;
            
        cout << "Message from client: " << buffer << endl;

        // db.insertMessage(string(buffer));

        //Broadcast message
        lock_guard<mutex> lock(mtx);
        for(int client : clients)
        {
            if(client != clientSocket) // Don't send the message back to the sender
                send(client, buffer, bytesReceived, 0);
        }
    }

    lock_guard<mutex> lock(mtx);
    clients.erase(remove(clients.begin(), clients.end(), clientSocket), clients.end());
    close(clientSocket);   
}

int main() 
{
    Server server("127.0.0.1", 8080);
    server.start();

    return 0;
}