#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QAction>
#include <QList>

class Toolbar : public QToolBar
{
    Q_OBJECT
public:
    explicit Toolbar(const QString &title, const QList<QAction*> &actions,
                     QWidget *parent = nullptr);
};

#endif