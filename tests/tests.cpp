#define BOOST_TEST_MODULE test_filter_library

#include <vector>

#include "ip_filter.hpp"

#include <boost/test/unit_test.hpp>

////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(empty)

BOOST_AUTO_TEST_CASE(convert)
{
    std::string addr;
    BOOST_CHECK_THROW(ip::convertAddrToBytes(addr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(sort)
{
    std::vector<std::string> pool;
    auto result = ip::reverseSort(pool);
    BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(one_byte)
{
    std::vector<std::string> pool;
    auto result = ip::filterByFirstByte(pool, 0);
    BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(two_bytes)
{
    std::vector<std::string> pool;
    auto result = ip::filterByFirstTwoBytes(pool, 0, 0);
    BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(any_byte)
{
    std::vector<std::string> pool;
    auto result = ip::filterByAnyByte(pool, 0);
    BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_SUITE_END()
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(invalid_input)

BOOST_AUTO_TEST_CASE(addr2bytes)
{
    try {
        ip::convertAddrToBytes("123");
    } catch (std::exception& ex) {
        BOOST_CHECK_EQUAL(ex.what(), "Invalid dots count in address");
    }

    try {
        ip::convertAddrToBytes("0.0.0.");
    } catch (std::exception& ex) {
        BOOST_CHECK_EQUAL(ex.what(), "Empty byte");
    }

    try {
        ip::convertAddrToBytes("0.0.0");
    } catch (std::exception& ex) {
        BOOST_CHECK_EQUAL(ex.what(), "Invalid dots count in address");
    }

    try {
        ip::convertAddrToBytes("481.516.2342.10800");
    } catch (std::exception& ex) {
        BOOST_CHECK_EQUAL(ex.what(), "Byte overflow");
    }

    try {
        ip::convertAddrToBytes("0.0.0.0.0");
    } catch (std::exception& ex) {
        BOOST_CHECK_EQUAL(ex.what(), "Invalid dots count in address");
    }

    try {
        ip::convertAddrToBytes("-1.-1.-1.-1");
    } catch (std::exception& ex) {
        BOOST_CHECK_EQUAL(ex.what(), "Bytes must be positive");
    }
}

BOOST_AUTO_TEST_SUITE_END()
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(use_lib)

BOOST_AUTO_TEST_CASE(sort)
{
    std::vector<std::string> ip_pool = {"192.168.1.1", "224.234.1.4", "46.87.2.5", "46.87.2.5",
                                        "46.87.2.5",   "46.87.2.5",   "46.87.2.6", "255.255.255.255"};

    std::vector<std::string> sortedPool = {"255.255.255.255", "224.234.1.4", "192.168.1.1", "46.87.2.6",
                                           "46.87.2.5",       "46.87.2.5",   "46.87.2.5",   "46.87.2.5"};

    auto sortedPool_check = ip::reverseSort(ip_pool);

    BOOST_CHECK_EQUAL_COLLECTIONS(sortedPool.begin(), sortedPool.end(), sortedPool_check.begin(),
                                  sortedPool_check.end());
}

BOOST_AUTO_TEST_CASE(already_sort)
{
    std::vector<std::string> ip_pool;
    ip_pool.push_back("224.200.1.0");
    ip_pool.push_back("224.100.1.0");
    ip_pool.push_back("192.168.1.0");
    ip_pool.push_back("43.20.1.0");

    auto sortedPool = ip::reverseSort(ip_pool);

    BOOST_CHECK_EQUAL_COLLECTIONS(ip_pool.begin(), ip_pool.end(), sortedPool.begin(), sortedPool.end());
}

BOOST_AUTO_TEST_CASE(fbyte)
{
    std::vector<std::string> ip_pool = {"192.168.1.1", "224.234.1.4", "42.87.2.5", "42.87.2.5",      "42.87.2.5",
                                        "42.87.2.5",   "42.87.2.6",   "42.87.2.5", "255.255.255.255"};

    std::vector<std::string> filteredPool = {"42.87.2.5", "42.87.2.5", "42.87.2.5",
                                             "42.87.2.5", "42.87.2.6", "42.87.2.5"};

    auto filteredPool_check = ip::filterByFirstByte(ip_pool, 42);

    BOOST_CHECK_EQUAL_COLLECTIONS(filteredPool.begin(), filteredPool.end(), filteredPool_check.begin(),
                                  filteredPool_check.end());
}

BOOST_AUTO_TEST_CASE(fbyte_nobyte)
{
    std::vector<std::string> ip_pool = {"192.168.1.1", "224.234.1.4", "42.87.2.5", "42.87.2.5",      "42.87.2.5",
                                        "42.87.2.5",   "42.87.2.6",   "42.87.2.5", "255.255.255.255"};

    auto filteredPool = ip::filterByFirstByte(ip_pool, 43);

    BOOST_CHECK(filteredPool.empty());
}

BOOST_AUTO_TEST_CASE(fsbyte)
{
    std::vector<std::string> ip_pool = {"192.168.1.1", "224.234.1.4", "42.87.2.5", "38.87.45.1",     "42.42.2.5",
                                        "42.87.2.5",   "42.83.2.6",   "42.87.2.6", "255.255.255.255"};

    std::vector<std::string> filteredPool = {"42.87.2.5", "42.87.2.5", "42.87.2.6"};

    auto filteredPool_check = ip::filterByFirstTwoBytes(ip_pool, 42, 87);

    BOOST_CHECK_EQUAL_COLLECTIONS(filteredPool.begin(), filteredPool.end(), filteredPool_check.begin(),
                                  filteredPool_check.end());
}

BOOST_AUTO_TEST_CASE(fsbyte_nobyte)
{
    std::vector<std::string> ip_pool = {"192.168.1.1", "224.234.1.4", "42.87.2.5", "42.87.2.5",      "42.87.2.5",
                                        "42.87.2.5",   "42.87.2.6",   "42.87.2.5", "255.255.255.255"};

    auto filteredPool = ip::filterByFirstTwoBytes(ip_pool, 42, 88);

    BOOST_CHECK(filteredPool.empty());
}

BOOST_AUTO_TEST_CASE(anybyte)
{
    std::vector<std::string> ip_pool = {"192.168.1.1", "224.234.1.4", "42.87.2.5", "38.87.45.1",     "42.42.2.5",
                                        "42.87.2.5",   "42.83.2.6",   "42.87.2.6", "255.255.255.255"};

    std::vector<std::string> filteredPool = {"42.87.2.5", "42.42.2.5", "42.87.2.5"};

    auto filteredPool_check = ip::filterByAnyByte(ip_pool, 5);

    BOOST_CHECK_EQUAL_COLLECTIONS(filteredPool.begin(), filteredPool.end(), filteredPool_check.begin(),
                                  filteredPool_check.end());
}

BOOST_AUTO_TEST_CASE(anybyte_nobyte)
{
    std::vector<std::string> ip_pool = {"192.168.1.1", "224.234.1.4", "42.87.2.5", "42.87.2.5",      "42.87.2.5",
                                        "42.87.2.5",   "42.87.2.6",   "42.87.2.5", "255.255.255.255"};

    auto filteredPool = ip::filterByAnyByte(ip_pool, 66);

    BOOST_CHECK(filteredPool.empty());
}

BOOST_AUTO_TEST_SUITE_END()
////////////////////////////////////////////////////////////////
