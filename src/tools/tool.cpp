#include "tool.hpp"

QAction* Tool::action() {
    return mAction;
}

Tool::Tool(const QString& name) {
    mAction = new QAction(QIcon("src/tools/icons/" + name.toLower() + "_tool.png"), name);
}
