#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H

#include <QScrollArea>

class RightPanel : public QScrollArea
{
    Q_OBJECT
public:
    explicit RightPanel(QWidget *parent = nullptr);
};

#endif