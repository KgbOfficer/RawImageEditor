#include "MainWindow.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("RAW Photo Editor");

    splitter = new QSplitter(Qt::Horizontal, this);
    leftPanel  = new LeftPanel(this);
    imageView  = new ImageView(this);
    rightPanel = new RightPanel(this);

    splitter->addWidget(leftPanel);
    splitter->addWidget(imageView);
    splitter->addWidget(rightPanel);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 4);
    splitter->setStretchFactor(2, 2);
    setCentralWidget(splitter);

    createActions();
    createMenus();

    // Toolbar
    QList<QAction*> toolbarActions = { importAction, exportAction, cullAction,
                                       shareAction, resetAction, undoAction,
                                       redoAction, autoAdjustAction, cursorToolsAction };
    Toolbar *toolbar = new Toolbar("Main Toolbar", toolbarActions, this);
    addToolBar(toolbar);

    // Status bar
    statusLabel = new QLabel("No images selected");
    statusBar()->addWidget(statusLabel);

    resize(1400, 800);
}

void MainWindow::createActions()
{
    openAction = new QAction("&Open...", this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::openImage);

    exitAction = new QAction("E&xit", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

    undoAction = new QAction("Undo", this);
    undoAction->setShortcut(QKeySequence::Undo);
    redoAction = new QAction("Redo", this);
    redoAction->setShortcut(QKeySequence::Redo);

    importAction      = new QAction("Import", this);
    exportAction      = new QAction("Export", this);
    cullAction        = new QAction("Cull", this);
    shareAction       = new QAction("Share online", this);
    resetAction       = new QAction("Reset", this);
    autoAdjustAction  = new QAction("Auto Adjust", this);
    cursorToolsAction = new QAction("Cursor Tools", this);
}

void MainWindow::createMenus()
{
    QMenuBar *mb = menuBar();

    QMenu *fileMenu = mb->addMenu("&File");
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    QMenu *editMenu = mb->addMenu("&Edit");
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);

    mb->addMenu("&Image")->addAction("Placeholder");
    mb->addMenu("&Adjustments")->addAction(autoAdjustAction);
    mb->addMenu("&Layer")->addAction("Placeholder");
    mb->addMenu("&Select")->addAction("Placeholder");
    mb->addMenu("&Camera")->addAction("Placeholder");
    mb->addMenu("&View")->addAction("Placeholder");
    mb->addMenu("&Window")->addAction("Placeholder");
    mb->addMenu("&Help")->addAction("About");
}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "Open Image", QString(),
        "Images (*.png *.jpg *.jpeg *.bmp *.tiff *.tif);;All Files (*)");
    if (!fileName.isEmpty()) {
        QPixmap pix(fileName);
        if (!pix.isNull()) {
            imageView->setImage(pix);
            statusLabel->setText(fileName);
        }
    }
}