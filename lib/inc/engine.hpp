#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <vector>

#include "gui.hpp"
#include "model.hpp"

namespace controller {
/// @brief Класс ловит события пользовательских запросов и делегирует задачи в model/view
class EditorEngine
{
public:
    explicit EditorEngine(model::Project& proj, view::UI& ui) noexcept;

    /// @brief  Создание нового пустого проекта
    void createNewProject() noexcept;

    /// @brief Загрузка проекта из файла
    /// @param name - имя файла
    void importDocument(const std::string& name) noexcept;

    /// @brief  Сохранение проекта в файл
    /// @param name - имя файла
    void exportDocument(const std::string& name) noexcept;

    /// @brief Добавление графического примитива в проект
    /// @param figure - указатель на интерфейсный класс примитива (допустим прилетает из ui)
    void createFigure(std::shared_ptr<model::IBaseFigure> figure) noexcept;

    /// @brief Удаление графического примитива из проекта
    /// @param idxs - массив индексов элементов для удаления (тк. можно выделить несколько за раз)
    void deleteFigure(std::vector<size_t> idxs) noexcept;

private:
    model::Project& m_rProject;
    view::UI& m_rUI;
};
} // namespace controller

#endif // ENGINE_HPP
