#include "engine.hpp"

controller::EditorEngine::EditorEngine(model::Project& proj, view::UI& ui) noexcept
    : m_rProject{proj},
      m_rUI{ui}
{}

void controller::EditorEngine::createNewProject() noexcept { m_rProject.createProject(); }

void controller::EditorEngine::importDocument(const std::string& name) noexcept
{
    m_rUI.clearWindow();
    m_rProject.importDocument(name);

    auto objects = m_rProject.getFigures();
    for (auto obj : objects)
        m_rUI.drawFigure(obj);
}

void controller::EditorEngine::exportDocument(const std::string& name) noexcept { m_rProject.exportDocument(name); }

void controller::EditorEngine::createFigure(std::shared_ptr<model::IBaseFigure> figure) noexcept
{
    m_rProject.addFigure(figure);
    m_rUI.drawFigure(figure);
}

void controller::EditorEngine::deleteFigure(std::vector<size_t> idxs) noexcept
{
    for (auto& idx : idxs) {
        m_rProject.deleteFigure(idx);
        m_rUI.eraseFigure(m_rProject.getFigures(idx));
    }
}
