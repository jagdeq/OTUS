#define BOOST_TEST_MODULE test_db_library

#include "database.hpp"

#include <boost/test/unit_test.hpp>

////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(database)

BOOST_AUTO_TEST_CASE(insert)
{
    db::Database db;
    BOOST_REQUIRE_THROW(db.insert("C", 1, "asd"), std::invalid_argument);

    db::Database::table tmpA{{1, "qwerty"}};
    db::Database::table tmpB{{0, "ytrewq"}};

    BOOST_REQUIRE(db.insert("A", 1, "qwerty") == tmpA);
    BOOST_REQUIRE(db.insert("B", 0, "ytrewq") == tmpB);
}

BOOST_AUTO_TEST_CASE(truncate)
{
    db::Database db;
    BOOST_REQUIRE_THROW(db.truncate("a"), std::invalid_argument);

    db.insert("A", 4, "4");
    db.insert("B", 3, "a");

    BOOST_REQUIRE(db.truncate("A").empty());
    BOOST_REQUIRE(db.truncate("B").empty());
}

BOOST_AUTO_TEST_CASE(intersection)
{
    db::Database db;
    BOOST_REQUIRE_THROW(db.intersection("a", "B"), std::invalid_argument);
    BOOST_REQUIRE_THROW(db.intersection("A", "b"), std::invalid_argument);
    db.insert("A", 1, "1");
    db.insert("A", 2, "2");
    db.insert("A", 3, "3");
    db.insert("A", 4, "4");
    db.insert("B", 3, "a");
    db.insert("B", 4, "b");

    auto res = db.intersection("A", "B");
    db::Database::collection tmp{{3, {"3", "a"}}, {4, {"4", "b"}}};

    BOOST_CHECK(res == tmp);
}

BOOST_AUTO_TEST_CASE(symmetric_difference)
{
    db::Database db;
    BOOST_REQUIRE_THROW(db.symmetricDifference("a", "B"), std::invalid_argument);
    BOOST_REQUIRE_THROW(db.symmetricDifference("A", "b"), std::invalid_argument);
    db.insert("A", 1, "1");
    db.insert("A", 2, "2");
    db.insert("A", 3, "3");
    db.insert("A", 4, "4");
    db.insert("B", 0, "a");
    db.insert("B", 6, "b");

    auto res = db.symmetricDifference("A", "B");
    db::Database::collection tmp{{0, {"", "a"}}, {1, {"1", ""}}, {2, {"2", ""}},
                                 {3, {"3", ""}}, {4, {"4", ""}}, {6, {"", "b"}}};

    BOOST_CHECK(res == tmp);
}

BOOST_AUTO_TEST_SUITE_END()
