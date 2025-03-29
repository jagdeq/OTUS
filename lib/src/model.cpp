#include "model.hpp"

void model::Project::addFigure(std::shared_ptr<IBaseFigure> figure) noexcept { m_objects.push_back(figure); }

void model::Project::deleteFigure(size_t idx) noexcept
{
    if (idx < m_objects.size())
        m_objects.erase(m_objects.begin() + idx);
}

std::vector<std::shared_ptr<model::IBaseFigure>> model::Project::getFigures() noexcept { return m_objects; }

std::shared_ptr<model::IBaseFigure> model::Project::getFigures(size_t idx) noexcept
{
    if (idx < m_objects.size())
        return m_objects[idx];
    else
        return nullptr;
}
