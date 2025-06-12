#pragma once

#include <iostream>
#include <map>
#include <ostream>
#include <ranges>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "consts.hpp"

namespace db {
class Database
{
public:
    using table      = std::map<int, std::string>;
    using collection = std::map<int, std::pair<std::string, std::string>>;

    Database();

    table insert(std::string table, int id, std::string name);
    table truncate(std::string table);
    collection intersection(std::string tableA, std::string tableB);
    collection symmetricDifference(std::string tableA, std::string tableB);

private:
    std::map<std::string, table> m_tables;
};

std::ostream& operator<<(std::ostream& os, const Database::collection& c);
std::ostream& operator<<(std::ostream& os, const Database::table& t);

} // namespace db
