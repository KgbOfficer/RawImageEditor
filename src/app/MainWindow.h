#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QLabel>
#include "ui/LeftPanel.h"
#include "ui/RightPanel.h"
#include "ui/Toolbar.h"
#include "ui/ImageView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void openImage();

private:
    void createActions();
    void createMenus();

    QSplitter *splitter;
    LeftPanel  *leftPanel;
    ImageView  *imageView;
    RightPanel *rightPanel;
    QLabel     *statusLabel;

    // Actions shared by menus and toolbar
    QAction *openAction;
    QAction *exitAction;
    QAction *undoAction;
    QAction *redoAction;

    // Toolbar only actions
    QAction *importAction;
    QAction *exportAction;
    QAction *cullAction;
    QAction *shareAction;
    QAction *resetAction;
    QAction *autoAdjustAction;
    QAction *cursorToolsAction;
};

#endif