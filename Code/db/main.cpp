#include <iostream>
#include "sqlite_orm.h"

using namespace std;
using namespace sqlite_orm;

struct User
{
    int id;
    string firstName;
    string lastName;
    int age;
};

struct Room
{
    int id;
    int seatsCount;
};

auto setup()
{
    auto storage = make_storage("db.sqlite",
                                make_table("users",
                                           make_column("id", &User::id, primary_key().autoincrement()),
                                           make_column("first_name", &User::firstName),
                                           make_column("last_name", &User::lastName),
                                           make_column("age", &User::age)),
                                make_table("rooms",
                                           make_column("id", &Room::id, primary_key().autoincrement()),
                                           make_column("seats_count", &Room::seatsCount)));
    return storage;
}

int main()
{
    auto storage = setup();

    User user{-1, "Bob", "Bolly", 15};
    auto insertedId = storage.insert(user);
    user.id = insertedId;
    cout << insertedId << endl;

    Room room{-1, 5};
    insertedId = storage.insert(room);
    room.id = insertedId;
    cout << insertedId << endl;

    auto allUsers = storage.get_all<User>();
    cout << "allUsers (" << allUsers.size() << "):" << endl;
    for (auto &user : allUsers)
    {
        cout << storage.dump(user) << endl;
    }
}
