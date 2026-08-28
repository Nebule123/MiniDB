#include <cassert>  // 提供 assert，用于检查测试条件
#include <iostream> // 提供 std::cout

#include "../command_parser.h" // 提供 Command 和 parseCommand

int main()
{
    Command command = parseCommand("   ");
    assert(command.type == CommandType::Empty);

    command = parseCommand("exit");
    assert(command.type == CommandType::Exit);

    command = parseCommand("help");
    assert(command.type == CommandType::Help);

    command = parseCommand("help extra");
    assert(command.type == CommandType::Invalid);

    command = parseCommand("insert Alice 20");
    assert(command.type == CommandType::Insert);
    assert(command.name == "Alice");
    assert(command.age == 20);

    command = parseCommand("insert \"Alice Smith\" 20");
    assert(command.type == CommandType::Insert);
    assert(command.name == "Alice Smith");
    assert(command.age == 20);

    command = parseCommand("insert Alice");
    assert(command.type == CommandType::Invalid);

    command = parseCommand("insert Alice 200");
    assert(command.type == CommandType::Invalid);
    assert(command.error == "Invalid age.");

    command = parseCommand("insert Alice 20 extra");
    assert(command.type == CommandType::Invalid);

    command = parseCommand("find 7");
    assert(command.type == CommandType::Find);
    assert(command.id == 7);
    command = parseCommand("search Smith");
    assert(command.type == CommandType::Search);
    assert(command.name == "Smith");

    command = parseCommand("search \"Robert Smith\"");
    assert(command.type == CommandType::Search);
    assert(command.name == "Robert Smith");

    command = parseCommand("search");
    assert(command.type == CommandType::Invalid);

    command = parseCommand("update 7 Bob 30");
    assert(command.type == CommandType::Update);
    assert(command.id == 7);
    assert(command.name == "Bob");
    assert(command.age == 30);

    command = parseCommand("update 7 \"Bob Lee\" 30");
    assert(command.type == CommandType::Update);
    assert(command.id == 7);
    assert(command.name == "Bob Lee");
    assert(command.age == 30);

    command = parseCommand("delete 7");
    assert(command.type == CommandType::Delete);
    assert(command.id == 7);

    command = parseCommand("count");
    assert(command.type == CommandType::Count);

    command = parseCommand("list");
    assert(command.type == CommandType::List);

    command = parseCommand("list extra");
    assert(command.type == CommandType::Invalid);

    command = parseCommand("hello");
    assert(command.type == CommandType::Invalid);
    assert(command.error == "Unknown command: hello");

    std::cout << "ALL command parser tests passed.\n";
    return 0;
}
