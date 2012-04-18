#include "EditorWindow.h"

#include <QDockWidget>
#include <QStyle>

EditorWindow::EditorWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Q_INIT_RESOURCE(icons);

    setWindowTitle("Phed-NG");

    createWorld();
    createDockWindows();
    createActions();
    createMenus();
    createToolBars();
//    createStatusBar();

//    readSettings();
}

EditorWindow::~EditorWindow()
{
    
}

void EditorWindow::createWorld()
{
//    m_world = new World(QPointF(0, -9.80665), this);
    m_view = new EditorView(/*m_world,*/ this);
    setCentralWidget(m_view);
//    connect(m_view, SIGNAL(mousePosChanged(QPointF)), this, SLOT(mousePosChanged(QPointF)));
//    connect(m_world, SIGNAL(objectsSelected(QList<Object*>)), this, SLOT(objectsSelected(QList<Object*>)));
}

void EditorWindow::createDockWindows() {
    m_propertyBrowserDock = new QDockWidget(this);
    m_propertyBrowserDock->setObjectName("PropertiesDock");
    m_propertyBrowserDock->setWindowTitle("Properties");
    m_propertyBrowserDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    m_propertyBrowser = new PropertyBrowser(m_propertyBrowserDock);
//    m_propertyBrowserDock->setWidget(m_propertyBrowser);
    addDockWidget(Qt::RightDockWidgetArea, m_propertyBrowserDock);
}

void EditorWindow::createActions()
{
    m_newAct = new QAction(QIcon(":/icons/silk/page_white.png"), tr("&New"), this);
    m_newAct->setShortcuts(QKeySequence::New);
    m_newAct->setStatusTip(tr("Create a new map"));
    connect(m_newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    m_openAct = new QAction(QIcon(":/icons/silk/folder_page_white.png"), tr("&Open"), this);
    m_openAct->setShortcuts(QKeySequence::Open);
    m_openAct->setStatusTip(tr("Open an existing map"));
    connect(m_openAct, SIGNAL(triggered()), this, SLOT(open()));

    m_saveAct = new QAction(QIcon(":/icons/silk/disk.png"), tr("&Save"), this);
    m_saveAct->setShortcuts(QKeySequence::Save);
    m_saveAct->setStatusTip(tr("Save the map to disk"));
    connect(m_saveAct, SIGNAL(triggered()), this, SLOT(save()));

    m_saveAsAct = new QAction(tr("Save &As..."), this);
    m_saveAsAct->setShortcuts(QKeySequence::SaveAs);
    m_saveAsAct->setStatusTip(tr("Save the map under a new name"));
    connect(m_saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    m_exitAct = new QAction(tr("E&xit"), this);
    m_exitAct->setShortcut(tr("Ctrl+Q"));
    m_exitAct->setStatusTip(tr("Exit Phed"));
    connect(m_exitAct, SIGNAL(triggered()), this, SLOT(close()));

    m_showGridAct = new QAction(tr("Show &Grid"), this);
    m_showGridAct->setShortcut(tr("Ctrl+G"));
    m_showGridAct->setStatusTip(tr("Display a grid over the map"));
    m_showGridAct->setCheckable(true);
    connect(m_showGridAct, SIGNAL(toggled(bool)), m_view, SLOT(showGrid(bool)));

    m_aboutAct = new QAction(tr("&About"), this);
    m_aboutAct->setStatusTip(tr("About Phed"));
    connect(m_aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    m_toolsActGroup = new QActionGroup(this);
    m_toolsActGroup->setExclusive(true);

    m_selectToolAct = new QAction(QIcon(":/icons/custom/select.png"), tr("&Select"), m_toolsActGroup);
    m_selectToolAct->setIconVisibleInMenu(false);
    m_selectToolAct->setShortcut(Qt::Key_S);
    m_selectToolAct->setCheckable(true);
    m_selectToolAct->setStatusTip(tr("Select objects to modify or delete"));
    m_selectToolAct->setProperty("tool", EditorView::Select);
    m_selectToolAct->setChecked(true);

    m_ellipseToolAct = new QAction(QIcon(":/icons/custom/ellipse.png"), tr("&Ellipse"), m_toolsActGroup);
    m_ellipseToolAct->setIconVisibleInMenu(false);
    m_ellipseToolAct->setShortcut(Qt::Key_E);
    m_ellipseToolAct->setCheckable(true);
    m_ellipseToolAct->setStatusTip(tr("Draw ellipse objects"));
    m_ellipseToolAct->setProperty("tool", EditorView::Ellipse);

    m_polygonToolAct = new QAction(QIcon(":/icons/custom/polygon.png"), tr("&Polygon"), m_toolsActGroup);
    m_polygonToolAct->setIconVisibleInMenu(false);
    m_polygonToolAct->setShortcut(Qt::Key_P);
    m_polygonToolAct->setCheckable(true);
    m_polygonToolAct->setStatusTip(tr("Draw polygonal objects"));
    m_polygonToolAct->setProperty("tool", EditorView::Polygon);

    m_rectToolAct = new QAction(QIcon(":/icons/custom/rectangle.png"), tr("&Rectangle"), m_toolsActGroup);
    m_rectToolAct->setIconVisibleInMenu(false);
    m_rectToolAct->setShortcut(Qt::Key_R);
    m_rectToolAct->setCheckable(true);
    m_rectToolAct->setStatusTip(tr("Draw rectangle objects"));
    m_rectToolAct->setProperty("tool", EditorView::Rectangle);

    m_edgeToolAct = new QAction(QIcon(":/icons/custom/line.png"), tr("Edge &Chain"), m_toolsActGroup);
    m_edgeToolAct->setIconVisibleInMenu(false);
    m_edgeToolAct->setShortcut(Qt::Key_C);
    m_edgeToolAct->setCheckable(true);
    m_edgeToolAct->setStatusTip(tr("Draw edge chains"));
    m_edgeToolAct->setProperty("tool", EditorView::EdgeChain);

    connect(m_toolsActGroup, SIGNAL(selected(QAction*)), this, SLOT(toolSelected(QAction*)));

    m_playIcon        = style()->standardIcon(QStyle::SP_MediaPlay);
    m_pauseIcon       = style()->standardIcon(QStyle::SP_MediaPause);
    m_playText        = tr("&Run");
    m_pauseText       = tr("&Pause");
    m_playStatusTip   = tr("Run physics");
    m_pauseStatusTip  = tr("Pause Physics");

    m_simStateAct = new QAction(this);
    m_simStateAct->setShortcut(Qt::Key_Space);
//    updateSimAct();
    connect(m_simStateAct, SIGNAL(triggered()), this, SLOT(toggleSimState()));

    m_propertyBrowserDock->toggleViewAction()->setText("&Properties");
}

void EditorWindow::newFile()
{
}

void EditorWindow::open()
{
}

void EditorWindow::save()
{
}

void EditorWindow::saveAs()
{
}

void EditorWindow::close()
{
}

void EditorWindow::about()
{
}

void EditorWindow::toolSelected(QAction*)
{
}

void EditorWindow::toggleSimState()
{
}

void EditorWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_newAct);
    m_fileMenu->addAction(m_openAct);
    m_fileMenu->addAction(m_saveAct);
    m_fileMenu->addAction(m_saveAsAct);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAct);

    m_viewMenu = menuBar()->addMenu(tr("&View"));
    m_viewMenu->addAction(m_showGridAct);

    m_simMenu = menuBar()->addMenu(tr("&Simulation"));
    m_simMenu->addAction(m_simStateAct);

    m_toolsMenu = menuBar()->addMenu(tr("&Tools"));
    m_toolsMenu->addAction(m_selectToolAct);
    m_toolsMenu->addAction(m_ellipseToolAct);
    m_toolsMenu->addAction(m_rectToolAct);
    m_toolsMenu->addAction(m_polygonToolAct);
    m_toolsMenu->addAction(m_edgeToolAct);

    m_windowsMenu = menuBar()->addMenu(tr("&Window"));
    m_windowsMenu->addAction(m_propertyBrowserDock->toggleViewAction());

    m_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_helpMenu->addAction(m_aboutAct);
}

void EditorWindow::createToolBars()
{
    m_fileToolBar = addToolBar(tr("File"));
    m_fileToolBar->setObjectName("FileToolBar");
    m_fileToolBar->addAction(m_newAct);
    m_fileToolBar->addAction(m_openAct);
    m_fileToolBar->addAction(m_saveAct);

    m_simToolBar = addToolBar(tr("Simulation"));
    m_simToolBar->setObjectName("SimToolBar");
    m_simToolBar->addAction(m_simStateAct);

    m_toolsToolBar = addToolBar(tr("Tools"));
    m_toolsToolBar->setObjectName("ToolsToolBar");
    m_toolsToolBar->addAction(m_selectToolAct);
    m_toolsToolBar->addAction(m_ellipseToolAct);
    m_toolsToolBar->addAction(m_rectToolAct);
    m_toolsToolBar->addAction(m_polygonToolAct);
    m_toolsToolBar->addAction(m_edgeToolAct);
}
