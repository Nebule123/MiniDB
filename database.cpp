#include "database.h"

#include <fstream> // 提供 std::ifstream 和 std::ofstream，用于文件读写
#include <iomanip> // 提供 std::quoted，用于保存和加载带空格姓名

int Database::insert(const std::string &name, int age)
{
    Person person;

    person.id = nextId;
    person.name = name;
    person.age = age;

    ++nextId;
    people.push_back(person);

    return person.id;
}

const Person *Database::findById(int id) const
{
    for (const Person &person : people)
    {
        if (person.id == id)
        {
            return &person;
        }
    }

    return nullptr;
}

std::vector<Person> Database::searchByName(
    const std::string &keyword) const
{
    std::vector<Person> matches;

    for (const Person &person : people)
    {
        if (person.name.find(keyword) != std::string::npos)
        {
            matches.push_back(person);
        }
    }

    return matches;
}

bool Database::update(int id, const std::string &name, int age)
{
    for (Person &person : people)
    {
        if (person.id == id)
        {
            person.name = name;
            person.age = age;

            return true;
        }
    }

    return false;
}

bool Database::removeById(int id)
{
    for (auto it = people.begin(); it != people.end(); ++it)
    {
        if (it->id == id)
        {
            people.erase(it);
            return true;
        }
    }

    return false;
}

const std::vector<Person> &Database::getAll() const
{
    return people;
}

std::size_t Database::count() const
{
    return people.size();
}

bool Database::saveToFile(const std::string &filename) const
{
    std::ofstream output(filename);

    if (!output)
    {
        return false;
    }

    for (const Person &person : people)
    {
        output << person.id << ' '
               << std::quoted(person.name) << ' '
               << person.age << '\n';
    }

    return output.good();
}

bool Database::loadFromFile(const std::string &filename)
{
    std::ifstream input(filename);

    if (!input)
    {
        return false;
    }

    std::vector<Person> loadedPeople;

    int loadedNextId = 1;
    Person person;

    while (input >> person.id >> std::quoted(person.name) >> person.age)
    {
        if (person.id <= 0 || person.age < 0 || person.age > 150)
        {
            return false;
        }

        loadedPeople.push_back(person);

        if (person.id >= loadedNextId)
        {
            loadedNextId = person.id + 1;
        }
    }

    if (!input.eof())
    {
        return false;
    }

    people = loadedPeople;
    nextId = loadedNextId;

    return true;
}
