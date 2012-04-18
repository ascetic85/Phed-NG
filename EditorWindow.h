#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QActionGroup>
#include <QMenuBar>
#include <QToolBar>

#include "EditorView.h"

class EditorWindow : public QMainWindow
{
    Q_OBJECT
    
public:


    EditorWindow(QWidget *parent = 0);
    ~EditorWindow();



private slots:
    void newFile();
    void open();
    void save();
    void saveAs();
    void close();

    void about();
    void toolSelected(QAction*);
    void toggleSimState();

private:
    void createWorld();
    void createDockWindows();
    void createActions();
    void createMenus();
    void createToolBars();

private:
    QMenu *m_fileMenu;
    QMenu *m_helpMenu;
    QMenu *m_viewMenu;
    QMenu *m_toolsMenu;
    QMenu *m_simMenu;
    QMenu *m_windowsMenu;

    QToolBar *m_fileToolBar;
    QToolBar *m_editToolBar;
    QToolBar *m_toolsToolBar;
    QToolBar *m_simToolBar;

    QAction *m_newAct;
    QAction *m_openAct;
    QAction *m_saveAct;
    QAction *m_saveAsAct;
    QAction *m_exitAct;
    QAction *m_aboutAct;
    QAction *m_showGridAct;
    QAction *m_snapToGridAct;

    QAction *m_simStateAct;
    QAction *m_stopSimAct;

    QIcon m_playIcon;
    QIcon m_pauseIcon;
    QString m_playText;
    QString m_pauseText;
    QString m_playStatusTip;
    QString m_pauseStatusTip;

    QActionGroup *m_toolsActGroup;
    QAction *m_selectToolAct;
    QAction *m_ellipseToolAct;
    QAction *m_polygonToolAct;
    QAction *m_rectToolAct;
    QAction *m_edgeToolAct;


    EditorView *m_view;
    QDockWidget *m_propertyBrowserDock;
//    PropertyBrowser *m_propertyBrowser;
};

#endif // MAINWINDOW_H
