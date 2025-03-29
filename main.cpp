#include "engine.hpp"

int main()
{
    model::Project project;
    view::UI ui;
    controller::EditorEngine engine(project, ui);

    /// Имитация работы с ui
    engine.createNewProject();
    engine.createFigure(std::make_shared<model::Circle>());
    engine.createFigure(std::make_shared<model::Circle>());
    engine.createFigure(std::make_shared<model::Rectangle>());
    engine.createFigure(std::make_shared<model::Rectangle>());
    engine.createFigure(std::make_shared<model::Rectangle>());
    engine.deleteFigure(std::vector<size_t>{1, 2});
    engine.importDocument("example.42");
    engine.exportDocument("glhf.42");

    return 0;
}
