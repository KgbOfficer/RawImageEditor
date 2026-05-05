#include "LeftPanel.h"
#include <QVBoxLayout>
#include <QTreeWidgetItem>

LeftPanel::LeftPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto *tree = new QTreeWidget;
    tree->setHeaderHidden(true);
    tree->setRootIsDecorated(true);
    tree->setAnimated(true);

    QStringList sections = {"Library", "TETHER", "SHAPE", "STYLE", "ADJUST", "REFINE"};
    for (const QString &sec : sections) {
        auto *item = new QTreeWidgetItem(tree);
        item->setText(0, sec);
        item->setFlags(Qt::ItemIsEnabled);
        for (int i = 0; i < 3; ++i) {
            auto *child = new QTreeWidgetItem(item);
            child->setText(0, sec + " item " + QString::number(i + 1));
        }
    }
    layout->addWidget(tree);
}