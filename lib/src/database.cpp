#include "database.hpp"

namespace db {
Database::Database()
{
    for (const auto& name : g_tableNames)
        m_tables.insert({name, table()});
}

Database::table Database::insert(std::string table, int id, std::string name)
{
    if (!m_tables.contains(table))
        throw std::invalid_argument("Unknown table name");

    m_tables[table].insert({id, name});
    return m_tables[table];
}

Database::table Database::truncate(std::string table)
{
    if (!m_tables.contains(table))
        throw std::invalid_argument("Unknown table name");

    m_tables[table].clear();
    return m_tables[table];
}

Database::collection Database::intersection(std::string tableA, std::string tableB)
{
    if (!m_tables.contains(tableA) || !m_tables.contains(tableB))
        throw std::invalid_argument("Unknown table name");

    collection result;

    for (const auto& [id, name] : m_tables[tableA])
        if (m_tables[tableB].contains(id))
            result.insert({id, {name, m_tables[tableB][id]}});

    return result;
}

Database::collection Database::symmetricDifference(std::string tableA, std::string tableB)
{
    if (!m_tables.contains(tableA) || !m_tables.contains(tableB))
        throw std::invalid_argument("Unknown table name");

    collection result;

    for (const auto& [id, name] : m_tables[tableA]) {
        if (m_tables[tableB].find(id) == m_tables[tableB].end())
            result.insert({id, {name, ""}});

        for (const auto& [id, name] : m_tables[tableB])
            if (m_tables[tableA].find(id) == m_tables[tableA].end())
                result.insert({id, {"", name}});
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const Database::collection& c)
{
    for (const auto& [key, value] : c)
        os << key << " | " << value.first << " | " << value.second << std::endl;

    return os;
}

std::ostream& operator<<(std::ostream& os, const Database::table& t)
{
    for (const auto& [key, value] : t)
        os << key << " | " << value << std::endl;

    return os;
}

} // namespace db
