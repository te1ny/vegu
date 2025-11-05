#include "action_manager.hpp"
#include <functional>

const std::string NO_ACTION = "No action";

ActionManager& ActionManager::instance() {
    static ActionManager obj{};
    return obj;
}

void ActionManager::add(const std::string& undoName, 
                        const std::string& redoName, 
                        std::function<void()> undo, 
                        std::function<void()> redo)
{
    mUndo.emplace(undoName, redoName, std::move(undo), std::move(redo));
    mRedo = std::stack<Action>();
}

const std::string& ActionManager::getUndoName() const {
    if (mUndo.empty())
        return NO_ACTION;
    return mUndo.top().undoName;
}

const std::string& ActionManager::getRedoName() const {
    if (mRedo.empty())
        return NO_ACTION;
    return mRedo.top().redoName;
}

void ActionManager::keyPressEvent(QKeyEvent* event) {
    if (event->key() != Qt::Key_Z) {
        QWidget::keyPressEvent(event);
        return;
    }
   
    if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier)) {
        redo();
        return;
    }

    if (event->modifiers() == (Qt::ControlModifier)) {
        undo();
        return;
    }

    QWidget::keyPressEvent(event);
}

void ActionManager::undo() {
    if (mUndo.empty())
        return;

    auto action = std::move(mUndo.top());
    mUndo.pop();

    action.undo();

    mRedo.emplace(std::move(action));
}

void ActionManager::redo() {
    if (mRedo.empty())
        return;

    auto action = std::move(mRedo.top());
    mRedo.pop();

    action.redo();

    mUndo.emplace(std::move(action));
}

ActionManager::ActionManager(QWidget* parent)
    : QWidget(parent)
    , mUndo()
    , mRedo() 
{
}

ActionManager::~ActionManager()
{
}
