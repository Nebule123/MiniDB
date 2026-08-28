# MiniDB

MiniDB is a C++17 command-line database project. It supports inserting, finding,
searching, updating, deleting, listing, and persistently storing person records.

## Build

Run these commands from the project root:

```powershell
cmake -S . -B build
cmake --build build
```

## Run

```powershell
.\build\minidb.exe
```

Available commands:

```text
insert "<name>" <age>
find <id>
search "<keyword>"
update <id> "<new_name>" <new_age>
delete <id>
list
count
help
exit
```

Example:

```text
insert "Alice Smith" 20
search Smith
update 1 "Alice Brown" 21
find 1
```

Records are saved to `minidb_data.txt` and loaded again when the program starts.

## Test

```powershell
ctest --test-dir build --output-on-failure
```

The test suite covers database operations, persistence, invalid data handling,
and command parsing.

## Project Structure

```text
main.cpp                       Command-line interface
person.h                       Person data model
database.h / database.cpp      Database operations and persistence
command_parser.h / .cpp        Command parsing and validation
tests/                         Automated tests
CMakeLists.txt                 Build configuration
```
