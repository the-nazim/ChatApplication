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

string regClient()
{
    string username;
    cout<<"Enter username: ";
    cin>>username;

    return username;
}   

string logClient()
{
    string username;
    cout<<"Enter username: ";
    cin>>username;

    return username;
}

int main(int argc, char *argv[]) 
{
    dbClient client;
    string username;
    // client.registerClient();
    // client.loginClient();

    if(argc == 1)
    {
        int ch;
        cout<<"Enter your choice: \n1. Register\n2. Login\n";
        cin>>ch;
        switch(ch)
        {
            case 1:
                username = regClient();
                break;
            case 2:
                username = logClient();
                break;
            default:
                cout<<"Invalid choice"<<endl;
                return 0;
        }
    }

    else if(argc>1)
    {
        if(argv[1].c_str()=="--register" || argv[1].c_str()=="-r")
        {
            username = regClient();
        }
        else if(argv[1].c_str()=="--login" || argv[1].c_str()=="-l")
        {
            username = logClient();
        }
        else
        {
            cout<<"Invalid choice"<<endl;
            return 0;
        }
    }
    
    return 0;
}