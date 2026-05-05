#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QWidget>
#include <QTreeWidget>

class LeftPanel : public QWidget
{
    Q_OBJECT
public:
    explicit LeftPanel(QWidget *parent = nullptr);
};

#endif