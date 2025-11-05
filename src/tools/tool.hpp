#ifndef TOOL_HPP
#define TOOL_HPP

#include <QString>
#include <QIcon>
#include <QAction>

class Tool {
public:
    QAction* action();

    Tool(const QString& name);
    virtual ~Tool() = default;

private:
    QAction* mAction;
};

#endif // TOOL_HPP
