#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "../database.h"

int main()
{
    Database database;

    // 新数据库应当没有记录
    assert(database.count() == 0);

    int aliceId = database.insert("Alice", 18);
    int bobId = database.insert("Bob", 25);

    assert(aliceId == 1);
    assert(bobId == 2);
    assert(database.count() == 2);

    const Person *alice = database.findById(aliceId);

    assert(alice != nullptr);
    assert(alice->name == "Alice");
    assert(alice->age == 18);
    assert(database.findById(999) == nullptr);

    bool updated = database.update(bobId, "Robert Smith", 26);

    assert(updated);

    const Person *robert = database.findById(bobId);

    assert(robert != nullptr);


    assert(robert->name == "Robert Smith");
    assert(robert->age == 26);
    assert(!database.update(999, "Nobody", 30));

    std::vector<Person> searchResults = database.searchByName("Smith");

    assert(searchResults.size() == 1);
    assert(searchResults[0].id == bobId);
    assert(searchResults[0].name == "Robert Smith");

    std::vector<Person> noResults = database.searchByName("Nobody");

    assert(noResults.empty());


    //测试获取全部记录
    const std::vector<Person> &people = database.getAll();

    assert(people.size() == 2);

    //测试删除
    assert(database.removeById(aliceId));
    assert(database.count() == 1);
    assert(database.findById(aliceId) == nullptr);

    //同一个ID不能删除两次
    assert(!database.removeById(aliceId));

    const std::string testFilename = "database_test_data.txt";

    assert(database.saveToFile(testFilename));

    Database loadedDatabase;

    assert(loadedDatabase.loadFromFile(testFilename));
    assert(loadedDatabase.count() == 1);

    const Person *loadedRobert = loadedDatabase.findById(bobId);

    assert(loadedRobert != nullptr);
    assert(loadedRobert->name == "Robert Smith");
    assert(loadedRobert->age == 26);

    int charlieId = loadedDatabase.insert("Charlie", 30);

    assert(charlieId == 3);

    assert(std::remove(testFilename.c_str()) == 0);

    const std::string missingFilename = "database_test_missing.txt";
    std::remove(missingFilename.c_str());

    Database missingFileDatabase;
    assert(!missingFileDatabase.loadFromFile(missingFilename));

    const std::string invalidFilename = "database_test_invalid.txt";

    {
        std::ofstream invalidOutput(invalidFilename);
        assert(invalidOutput);
        invalidOutput << "invalid data\n";
    }

    Database unchangedDatabase;
    int keepId = unchangedDatabase.insert("Keep", 40);

    assert(!unchangedDatabase.loadFromFile(invalidFilename));
    assert(unchangedDatabase.count() == 1);

    const Person *keptPerson = unchangedDatabase.findById(keepId);

    assert(keptPerson != nullptr);
    assert(keptPerson->name == "Keep");
    assert(keptPerson->age == 40);
    assert(std::remove(invalidFilename.c_str()) == 0);

    std::cout << "ALL database tests passed.\n";
    return 0;
}
