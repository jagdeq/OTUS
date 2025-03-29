#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>
#include <string>
#include <vector>

#define UNUSED(x) (void)x

namespace model {
/// @brief Интерфейсный чисто виртуальный класс графического примитива
class IBaseFigure
{
public:
    virtual ~IBaseFigure() noexcept {}
    virtual void draw() const noexcept = 0;

    std::pair<int, int> getCoords() { return m_coords; }

private:
    std::pair<int, int> m_coords;
};

/// @brief  Графический примитив - окружность
class Circle : public IBaseFigure
{
public:
    void draw() const noexcept override {}
};

/// @brief  Графический примитив - треугольник
class Rectangle : public IBaseFigure
{
public:
    void draw() const noexcept override {}
};

/// @brief  Класс хранилище графических примитивов проекта
class Project
{
public:
    void createProject() {}

    /// @brief  Выполняет загрузку проекта из файла + обновляет список примитивов проекта
    /// @param doc_name  - имя файла
    void importDocument(const std::string& doc_name) noexcept { UNUSED(doc_name); }

    /// @brief Выполняет сохранение текущего проекта в файл
    /// @param doc_name
    void exportDocument(const std::string& doc_name) noexcept { UNUSED(doc_name); }

    /// @brief  Добавляет примитив в хранилище
    /// @param figure - расшаренный умный указатель на примитив
    void addFigure(std::shared_ptr<IBaseFigure> figure) noexcept;

    /// @brief Удаляет примитив из хранилища
    /// @param idx - индекс (ID) примитива
    void deleteFigure(size_t idx) noexcept;

    /// @brief  Перегруженная функция
    /// @return - все примитивы в хранилище
    std::vector<std::shared_ptr<IBaseFigure>> getFigures() noexcept;

    /// @brief Перегруженная функция возврата примитивов из хранилища
    /// @param idx - индекс примитива
    /// @return - примтив по индексу
    std::shared_ptr<IBaseFigure> getFigures(size_t idx) noexcept;

private:
    std::vector<std::shared_ptr<IBaseFigure>> m_objects;
};

} // namespace model

#endif // MODEL_HPP
