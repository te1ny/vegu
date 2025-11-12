#ifndef ACTION_MANAGER_HPP
#define ACTION_MANAGER_HPP

#include <QWidget>
#include <QKeyEvent>

#include <functional>
#include <stack>
#include <string>

class ActionManager : QWidget {
    struct Action {
        std::string undoName;
        std::string redoName;
        std::function<void()> undo;
        std::function<void()> redo;
    };

public:
    static ActionManager& instance(QWidget* parent = nullptr);

    void add(const std::string& undoName, 
             const std::string& redoName, 
             std::function<void()> undo, 
             std::function<void()> redo);

    const std::string& getUndoName() const;
    const std::string& getRedoName() const;

    void keyPressEvent(QKeyEvent* event) override;

private:
    void undo();
    void redo();

    std::stack<Action> mUndo;
    std::stack<Action> mRedo;

    ActionManager(QWidget* parent = nullptr);
    ~ActionManager() = default;
};

#endif // ACTION_MANAGER_HPP
