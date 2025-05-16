#include "../include/client.h"

string dbClient::registerClient()
{
    string username, password;
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;

    bsoncxx::builder::basic::document doc_builder{};
    doc_builder.append(bsoncxx::builder::basic::kvp("username", username));
    doc_builder.append(bsoncxx::builder::basic::kvp("password", password));
    doc_builder.append(bsoncxx::builder::basic::kvp("timestamp", bsoncxx::types::b_date{std::chrono::system_clock::now()}));

    auto result = collection.insert_one(doc_builder.view());
    cout<< "Inserted document ID: " << result->inserted_id().get_oid().value.to_string() << endl;
    cout << "Registered client: " << username << endl;

    return username;
}

string dbClient::loginClient()
{
    string username, password;
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;

    auto cursor = collection.find(bsoncxx::builder::basic::make_document(
        bsoncxx::builder::basic::kvp("username", username),
        bsoncxx::builder::basic::kvp("password", password)
    ));

    if (cursor.begin() != cursor.end())
    {
        cout << "Login successful for user: " << username << endl;
    }
    else
    {
        cout << "Login failed for user: " << username << endl;
    }

    return username;
}

void broadcastMessage(int socket)
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

void Client::sendMessage()
{
    string message;

    thread broadThread(broadcastMessage, clientSocket);

    while (true) 
    {
        cout << "Enter the message: ";
        getline(cin, message);

        if (message == "exit") 
            break;

        send(clientSocket, message.c_str(), message.length(), 0);
    }
    broadThread.join(); // Wait for receive thread
}


int main(int argc, char *argv[])
{
    if (argc != 3) 
    {
        cout << "Usage: " << argv[0] << " <IP Address> <Port>" << endl;
        return 1;
    }

    string ipAddress = argv[1];
    int port = atoi(argv[2]);

    Client client(ipAddress, port);
    client.sendMessage();

    return 0;
}
