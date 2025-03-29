#ifndef GUI_HPP
#define GUI_HPP

#include "model.hpp"

namespace view {
/// @brief Класс перерисовывает интерфейс приложения (отрисовка/стирание графических примитивов)
class UI
{
public:
    /// @brief Имитация отрисовки графического примитива
    /// @param figure - расшаренный умный указатель на примитив
    void drawFigure(std::shared_ptr<model::IBaseFigure> figure) noexcept { figure->draw(); }

    /// @brief Имитация стирания графического примитива
    /// @param figure - расшаренный указатель на примитив
    void eraseFigure(std::shared_ptr<model::IBaseFigure> figure) noexcept
    {
        auto coords = figure->getCoords();
        UNUSED(coords);
        // some erase ui logic; }
    };

    void clearWindow() noexcept {}
};
} // namespace view

#endif // GUI_HPP
