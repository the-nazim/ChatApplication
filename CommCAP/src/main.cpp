#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>

using namespace std;

int main() {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{"mongodb://172.19.64.1:27017/"}};
    
    auto db = conn["testdb"];
    auto collection = db["testcollection"];

    bsoncxx::builder::basic::document doc_builder{};
    doc_builder.append(bsoncxx::builder::basic::kvp("name", "John Doe"));
    doc_builder.append(bsoncxx::builder::basic::kvp("age", 30));
    
    auto result = collection.insert_one(doc_builder.view());

    cout << "Inserted document ID: " << result->inserted_id().get_oid().value.to_string() << endl;

    return 0;
}