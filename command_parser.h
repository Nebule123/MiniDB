#pragma once

#include <string> // 提供 std::string，用于保存姓名和错误信息

enum class CommandType
{
    Empty,
    Exit,
    Help,
    Insert,
    Find,
    Search,
    Update,
    Delete,
    Count,
    List,
    Invalid
};

struct Command
{
    CommandType type = CommandType::Invalid;
    int id = 0;
    std::string name;
    int age = 0;
    std::string error;
};

Command parseCommand(const std::string &line);