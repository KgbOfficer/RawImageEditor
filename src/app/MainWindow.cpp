#include "MainWindow.h"
#include "core/RawProcessor.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include <QProgressDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("RAW Photo Editor");

    splitter  = new QSplitter(Qt::Horizontal, this);
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

    QList<QAction*> toolbarActions = { importAction, exportAction, cullAction,
                                       shareAction, resetAction, undoAction,
                                       redoAction, autoAdjustAction, cursorToolsAction };
    Toolbar *toolbar = new Toolbar("Main Toolbar", toolbarActions, this);
    addToolBar(toolbar);

    statusLabel = new QLabel("No image loaded");
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

    undoAction       = new QAction("Undo", this);
    undoAction->setShortcut(QKeySequence::Undo);
    redoAction       = new QAction("Redo", this);
    redoAction->setShortcut(QKeySequence::Redo);

    importAction      = new QAction("Import", this);
    exportAction      = new QAction("Export", this);
    cullAction        = new QAction("Cull", this);
    shareAction       = new QAction("Share online", this);
    resetAction       = new QAction("Reset", this);
    autoAdjustAction  = new QAction("Auto Adjust", this);
    cursorToolsAction = new QAction("Cursor Tools", this);

    connect(importAction, &QAction::triggered, this, &MainWindow::openImage);
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
    // Build filter – standard formats first, then every known RAW extension
    const QString filter =
        "All Supported Images ("
        "*.png *.jpg *.jpeg *.bmp *.tiff *.tif "
        "*.cr2 *.cr3 *.crw *.nef *.nrw *.arw *.srf *.sr2 "
        "*.raf *.orf *.rw2 *.pef *.ptx *.srw *.x3f "
        "*.3fr *.fff *.mef *.iiq *.raw *.rwl *.dng);;"
        "RAW Files ("
        "*.cr2 *.cr3 *.crw *.nef *.nrw *.arw *.srf *.sr2 "
        "*.raf *.orf *.rw2 *.pef *.ptx *.srw *.x3f "
        "*.3fr *.fff *.mef *.iiq *.raw *.rwl *.dng);;"
        "Standard Images (*.png *.jpg *.jpeg *.bmp *.tiff *.tif);;"
        "All Files (*)";

    QString fileName = QFileDialog::getOpenFileName(
        this, "Open Image", QString(), filter);

    if (fileName.isEmpty())
        return;

    if (RawProcessor::isRawFile(fileName)) {
        loadRawFile(fileName);
    } else {
        loadStandardFile(fileName);
    }
}

void MainWindow::loadRawFile(const QString &fileName)
{
    // Show a progress dialog – RAW decoding can take 1-3 seconds
    QProgressDialog progress("Decoding RAW file…", QString(), 0, 0, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(300);
    progress.setValue(0);
    qApp->processEvents();

    RawProcessor proc;
    if (!proc.open(fileName)) {
        progress.close();
        QMessageBox::critical(this, "RAW Import Failed", proc.errorString());
        return;
    }

    progress.close();

    QPixmap pix = proc.toPixmap();
    if (pix.isNull()) {
        QMessageBox::critical(this, "RAW Import Failed",
                              "The RAW file was decoded but produced an empty image.");
        return;
    }

    imageView->setImage(pix);

    QFileInfo fi(fileName);
    setWindowTitle(QString("RAW Photo Editor — %1").arg(fi.fileName()));
    statusLabel->setText(QString("%1  |  %2 × %3 px")
                         .arg(fi.fileName())
                         .arg(pix.width())
                         .arg(pix.height()));
}

void MainWindow::loadStandardFile(const QString &fileName)
{
    QPixmap pix(fileName);
    if (pix.isNull()) {
        QMessageBox::warning(this, "Open Failed",
                             "Could not load the selected file.");
        return;
    }

    imageView->setImage(pix);

    QFileInfo fi(fileName);
    setWindowTitle(QString("RAW Photo Editor — %1").arg(fi.fileName()));
    statusLabel->setText(QString("%1  |  %2 × %3 px")
                         .arg(fi.fileName())
                         .arg(pix.width())
                         .arg(pix.height()));
}
