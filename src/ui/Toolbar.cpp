#include "Toolbar.h"

Toolbar::Toolbar(const QString &title, const QList<QAction*> &actions,
                 QWidget *parent)
    : QToolBar(title, parent)
{
    setMovable(false);
    for (auto *action : actions)
        addAction(action);
}