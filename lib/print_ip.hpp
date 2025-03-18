#ifndef PRINT_IP_HPP
#define PRINT_IP_HPP

#include <iostream>
#include <list>
#include <tuple>
#include <type_traits>
#include <vector>

//////////////// vector ////////////////
template <typename>
struct is_vector
{
    static const bool value = false;
};

template <typename T>
struct is_vector<std::vector<T>>
{
    static const bool value = true;
};

//////////////// list //////////////////
template <typename>
struct is_list
{
    static const bool value = false;
};

template <typename T>
struct is_list<std::list<T>>
{
    static const bool value = true;
};

//////////////// tuple /////////////////
template <typename>
struct is_tuple
{
    static const bool value = false;
};

template <typename... Args>
struct is_tuple<std::tuple<Args...>>
{
    static const bool value = true;
};

template <typename T>
struct is_tuple_same
{
    static const bool value = true;
};

template <typename T, typename... Args>
struct is_tuple_same<std::tuple<T, Args...>>
    : std::conditional_t<(std::is_same<T, Args>::value && ...), std::true_type, std::false_type>
{};

/////////////////////////////////////// print_ip ///////////////////////////////////////////////////////////

/// @brief Побайтно выводит в консоль число с разделителем '.' м/у байтами, начиная со старшего
/// @tparam T - целое
/// @return void
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type print_ip(T addr)
{
    for (size_t i = 0; i != sizeof(T); ++i) {
        std::cout << ((addr >> (sizeof(T) - i - 1) * 8) & 0xFF);
        std::cout << ((i != sizeof(T) - 1) ? '.' : '\n');
    }
}

/// @brief Выводит строку в консоль
/// @tparam T - std::string
/// @return void
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type print_ip(T addr)
{
    std::cout << addr << std::endl;
}

/// @brief Поэлементно выводит содержимое контейнера в консоль с разделителем '.'
/// @tparam T - std::vector / std::list
/// @return void
template <typename T>
typename std::enable_if<is_vector<T>::value || is_list<T>::value, void>::type print_ip(T addr)
{
    size_t idx = 0;
    for (auto& elem : addr)
        std::cout << ((idx++ > 0) ? "." : "") << elem;

    std::cout << std::endl;
}

/// @brief Поэлементно выводит содержимое кортежа в консоль с разделителем '.'
/// @tparam T - std::tuple
/// @return void
template <typename T>
typename std::enable_if<is_tuple<T>::value && is_tuple_same<T>::value, void>::type print_ip(T addr)
{
    std::string addr2print;
    size_t idx = 0;
    std::apply([&idx](auto&&... args) { ((std::cout << ((idx++ > 0) ? "." : "") << args), ...); }, addr);
    std::cout << std::endl;
}

#endif // PRINT_IP_HPP
