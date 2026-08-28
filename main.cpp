#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "command_parser.h"
#include "database.h"
#include "person.h"

int main()
{
    Database database;
    const std::string dataFilename = "minidb_data.txt";

    if (std::filesystem::exists(dataFilename))
    {
        if (!database.loadFromFile(dataFilename))
        {
            std::cerr << "Failed to load database file: "
                      << dataFilename << '\n';
            return 1;
        }
    }

    std::string command;

    std::cout << "MiniDB started. Type 'help' for commands.\n";

    while (true)
    {
        std::cout << "db > ";
        if (!std::getline(std::cin, command))
        {
            std::cout << '\n';
            break;
        }

        Command parsedCommand = parseCommand(command);

        if (parsedCommand.type == CommandType::Empty)
        {
            continue;
        }

        if (parsedCommand.type == CommandType::Invalid)
        {
            std::cout << parsedCommand.error << '\n';
            continue;
        }

        if (parsedCommand.type == CommandType::Exit)
        {
            break;
        }

        bool dataChanged = false;

        if (parsedCommand.type == CommandType::Help)
        {
            std::cout << "Commands:\n"
                      << "  insert \"<name>\" <age>\n"
                      << "  find <id>\n"
                      << "  search \"<keyword>\"\n"
                      << "  update <id> \"<new_name>\" <new_age>\n"
                      << "  delete <id>\n"
                      << "  list\n"
                      << "  count\n"
                      << "  help\n"
                      << "  exit\n";
        }
        else if (parsedCommand.type == CommandType::Insert)
        {
            int id = database.insert(
                parsedCommand.name,
                parsedCommand.age);

            dataChanged = true;

            std::cout << "Inserted successfully. ID: "
                      << id << '\n';
        }
        else if (parsedCommand.type == CommandType::Find)
        {
            const Person *person =
                database.findById(parsedCommand.id);

            if (person != nullptr)
            {
                std::cout << "ID: " << person->id
                          << ", Name: " << person->name
                          << ", Age: " << person->age << '\n';
            }
            else
            {
                std::cout << "Person not found.\n";
            }
        }
        else if (parsedCommand.type == CommandType::Search)
        {
            std::vector<Person> results =
                database.searchByName(parsedCommand.name);

            if (results.empty())
            {
                std::cout << "No matching records.\n";
            }

            for (const Person &person : results)
            {
                std::cout << "ID: " << person.id
                          << ", Name: " << person.name
                          << ", Age: " << person.age << '\n';
            }
        }
        else if (parsedCommand.type == CommandType::Update)
        {
            bool updated = database.update(
                parsedCommand.id,
                parsedCommand.name,
                parsedCommand.age);

            if (updated)
            {
                dataChanged = true;
                std::cout << "Updated successfully.\n";
            }
            else
            {
                std::cout << "Person not found.\n";
            }
        }
        else if (parsedCommand.type == CommandType::Delete)
        {
            bool deleted =
                database.removeById(parsedCommand.id);

            if (deleted)
            {
                dataChanged = true;
                std::cout << "Deleted successfully.\n";
            }
            else
            {
                std::cout << "Person not found.\n";
            }
        }
        else if (parsedCommand.type == CommandType::Count)
        {
            std::cout << "Total records: "
                      << database.count() << '\n';
        }
        else if (parsedCommand.type == CommandType::List)
        {
            const std::vector<Person> &records =
                database.getAll();

            if (records.empty())
            {
                std::cout << "No records.\n";
            }

            for (const Person &person : records)
            {
                std::cout << "ID: " << person.id
                          << ", Name: " << person.name
                          << ", Age: " << person.age << '\n';
            }
        }

        if (dataChanged && !database.saveToFile(dataFilename))
        {
            std::cerr << "Failed to save database file: "
                      << dataFilename << '\n';
            return 1;
        }
    }

    if (!database.saveToFile(dataFilename))
    {
        std::cerr << "Failed to save database file: "
                  << dataFilename << '\n';
        return 1;
    }

    std::cout << "Bye!\n";
    return 0;
}
