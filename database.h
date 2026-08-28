#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "person.h"

class Database
{
public:
    int insert(const std::string &name, int age);
    const Person *findById(int id) const;
    std::vector<Person> searchByName(const std::string &keyword) const;
    bool update(int id, const std::string &name, int age);
    bool removeById(int id);

    bool saveToFile(const std::string &filename) const;
    bool loadFromFile(const std::string &filename);

    const std::vector<Person> &getAll() const;
    std::size_t count() const;

private:
    std::vector<Person> people;
    int nextId = 1;
};
