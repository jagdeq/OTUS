#ifndef PROXY_HPP
#define PROXY_HPP

#include <cstddef>
#include <exception>
#include <vector>

#include "matrix.hpp"

namespace math {
template <typename T, T defv, size_t N>
class Matrix;

/// @brief Proxy класс для промежуточной отработки операторов [] и = класса матрицы
/// @tparam T - любой целочисленный или с плавающей точкой
/// @tparam defv - значение по умолчанию
/// @tparam N - размерность матрицы
template <typename T, T defv, size_t N>
class Proxy
{
public:
    /// @brief
    /// @param matrix - ссылка на объект основного класса матрицы
    /// @param idxs  - ссылка на вектор с индексами элемента
    explicit Proxy(Matrix<T, defv, N>& matrix, std::vector<size_t>& idxs) noexcept
        : m_rMatrix{matrix},
          m_indices{idxs}
    {}

    /// @brief Перегруженный оператор [], расширяет вектор индексами, передает во владе
    /// @param idx - индекс текущего оператора []
    /// @return новый Proxy объект с расширенным вектором
    Proxy<T, defv, N> operator[](size_t idx) noexcept
    {
        m_indices.push_back(idx);
        return Proxy<T, defv, N>(m_rMatrix, m_indices);
    }

    /// @brief Каноническая форма оператора присваивания. Передает управление основному классу матрицы.
    /// @param elem - константная lvalue-ссылка на добавляемый элемент
    /// @return текущий proxy-объект
    Proxy<T, defv, N>& operator=(const T& elem)
    {
        if (m_indices.size() != N)
            throw std::out_of_range("Proxy::operator=() Invalid matrix dimention");

        m_rMatrix.setElement(m_indices, elem);
        return *this;
    }

    /// @brief Перегруженный оператор приведения типа получения доступа к элементу в конструкциях [][][]...[]
    operator T()
    {
        if (m_indices.size() != N)
            throw std::out_of_range("Proxy::operatorT() Invalid matrix dimention");

        return m_rMatrix.getElement(m_indices);
    }

private:
    /// @brief ссылка на основной класс матрицы
    Matrix<T, defv, N>& m_rMatrix;

    /// @brief вектор индексов элемента
    std::vector<size_t> m_indices;
};
} // namespace math

#endif // CORE_HPP
