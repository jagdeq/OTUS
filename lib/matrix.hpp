#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "proxy.hpp"

namespace math {

/// @brief Вспомогательная функция создания кортежа из вектора
/// @tparam T - любой целочисленный
/// @tparam U - любой целочисленный или с плавающей точкой (значение элемента матрицы)
/// @tparam ...idx - параметр-пак для работы с вектором
/// @param vec - вектор с индексами элементов
/// @param val - значение в ячейке, добавляемое в конец кортежа
/// @return - кортеж
template <typename T, typename U, size_t... idx>
auto vector2tuple(const std::vector<T>& vec, U val, std::index_sequence<idx...>)
{
    return std::make_tuple(vec[idx]..., val);
}

/// @brief Структура для хранения информации о матричных ячейках
template <typename T>
struct Element
{
    std::vector<size_t> m_indices;
    T m_value;
};

/// @brief Основной класс N-мерной разреженной бесконечной матрицы, предоставляющий интерфейс
/// @tparam T - любой целочисленный или с плавающей точкой
/// @tparam defv - значение по умолчанию
/// @tparam N - размерность матрицы
template <typename T, T defv, size_t N>
class Matrix
{
public:
    /// @brief Кастомный матричный итератор.
    ///         Основная суть - перегруженный оператор * для возврата кортежа со значениями и индексами
    class Iterator
    {
    public:
        Iterator(Element<T>* ptr) noexcept
            : m_ptr{ptr}
        {}

        auto operator*() { return vector2tuple(m_ptr->m_indices, m_ptr->m_value, std::make_index_sequence<N>()); }

        Iterator& operator++()
        {
            ++m_ptr;
            return *this;
        }

        bool operator!=(const Iterator& other) { return m_ptr != other.m_ptr; }

    private:
        Element<T>* m_ptr;
    };

    Iterator begin() noexcept { return Iterator(m_elements.data()); }
    Iterator end() noexcept { return Iterator(m_elements.data() + m_elements.size()); }

    Proxy<T, defv, N> operator[](size_t idx) noexcept
    {
        std::vector<size_t> indices{idx};
        return Proxy<T, defv, N>(*this, indices);
    }

    /// @brief Функция чтения элемента из ячейки
    ///         Может быть вызвана напрямую, либо через proxy-класс
    /// @param indices - вектор индексов читаемого элемента
    /// @return копию запрашиваемого элемента
    T getElement(std::vector<size_t>& indices)
    {
        if (indices.size() != N)
            throw std::out_of_range("Matrix::getElement() Invalid matrix dimention");

        for (auto& elem : m_elements)
            if (elem.m_indices == indices)
                return elem.m_value;

        return defv;
    }

    /// @brief Функция записи элемента в ячейку. Может юыть вызвана напрямую, либо неявно через proxy-класс
    ///         При записи значения по умолчанию освобождает ячейку
    /// @param indices - вектор с индексами элемента
    /// @param el  - фактическое значение
    void setElement(std::vector<size_t>& indices, T el)
    {
        if (indices.size() != N)
            throw std::out_of_range("Matrix::setElement() Invalid matrix dimention");

        for (auto it = m_elements.begin(); it != m_elements.end(); ++it)
            if ((*it).m_indices == indices) {
                if (el == defv)
                    m_elements.erase(it);
                else
                    (*it).m_value = el;

                return;
            }

        if (el != defv)
            m_elements.push_back(Element<T>{indices, el});
    }

    /// @brief size() и этим все сказано
    /// @return количество реально заполненных элементов
    size_t size() const noexcept { return m_elements.size(); }

private:
    /// @brief вектор со всеми заполненными значениями матрицы
    std::vector<Element<T>> m_elements;
};

} // namespace math

#endif // MATRIX_HPP
