#include "../include/main.h"

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

void dbClient::loginClient()
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
}

void Client::sendMessage()
{
    string message;
    while (true) 
    {
        cout << "Enter the message: ";
        getline(cin, message);

        if (message == "exit") 
            break;

        send(clientSocket, message.c_str(), message.length(), 0);
    }
}

int main() 
{
    dbClient client;
    
    // client.registerClient();
    // client.loginClient();
    return 0;
}