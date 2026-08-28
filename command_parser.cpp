#include "command_parser.h" // 提供 Command、CommandType 和 parseCommand 声明
#include <iomanip> // 提供 std::quoted，用于读取带空格的引号字符串
#include <sstream> // 提供 std::istringstream，用于拆分命令文本

namespace
{
Command invalidCommand(const std::string &message)
{
    Command command;
    command.type = CommandType::Invalid;
    command.error = message;
    return command;
}

bool hasExtraArgument(std::istringstream &input)
{
    std::string extra;
    return static_cast<bool>(input >> extra);
}
}

Command parseCommand(const std::string &line)
{
    std::istringstream input(line);
    std::string action;
    Command command;

    if (!(input >> action))
    {
        command.type = CommandType::Empty;
        return command;
    }

    if (action == "exit")
    {
        if (hasExtraArgument(input))
        {
            return invalidCommand("Usage: exit");
        }

        command.type = CommandType::Exit;
    }
    else if (action == "help")
    {
        if (hasExtraArgument(input))
        {
            return invalidCommand("Usage: help");
        }

        command.type = CommandType::Help;
    }
    else if (action == "insert")
    {
        if (!(input >> std::quoted(command.name) >> command.age) ||
            hasExtraArgument(input))
        {
            return invalidCommand("Usage: insert <name> <age>");
        }

        if (command.age < 0 || command.age > 150)
        {
            return invalidCommand("Invalid age.");
        }

        command.type = CommandType::Insert;
    }
    else if (action == "find")
    {
        if (!(input >> command.id) || hasExtraArgument(input))
        {
            return invalidCommand("Usage: find <id>");
        }

        command.type = CommandType::Find;
    }
    else if (action == "search")
    {
        if (!(input >> std::quoted(command.name)) ||
            hasExtraArgument(input))
        {
            return invalidCommand("Usage: search <keyword>");
        }

        command.type = CommandType::Search;
    }
    else if (action == "update")
    {
        if (!(input >> command.id >> std::quoted(command.name) >> command.age) ||
            hasExtraArgument(input))
        {
            return invalidCommand(
                "Usage: update <id> <new_name> <new_age>");
        }

        if (command.age < 0 || command.age > 150)
        {
            return invalidCommand("Invalid age.");
        }

        command.type = CommandType::Update;
    }
    else if (action == "delete")
    {
        if (!(input >> command.id) || hasExtraArgument(input))
        {
            return invalidCommand("Usage: delete <id>");
        }

        command.type = CommandType::Delete;
    }
    else if (action == "count")
    {
        if (hasExtraArgument(input))
        {
            return invalidCommand("Usage: count");
        }

        command.type = CommandType::Count;
    }
    else if (action == "list")
    {
        if (hasExtraArgument(input))
        {
            return invalidCommand("Usage: list");
        }

        command.type = CommandType::List;
    }
    else
    {
        return invalidCommand("Unknown command: " + action);
    }

    return command;
}
