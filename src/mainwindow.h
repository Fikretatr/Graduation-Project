/************************************************************************************/
/*                                                                                  */
/* This file is part of the CtoVer (Simple Algoritmic State Diagram Editor) package */
/*                                                                                  */
/*  Copyright (c) 2022-present, Muhammet Fikret ATAR (atarfikret146@gmail.com)      */
/*                       All rights reserved.                                       */
/*                                                                                  */
/*                                                                                  */
/*                                                                                  */
/*                                                                                  */
/************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "state.h"
#include "properties.h"

#include <QMainWindow>
#include <QFrame>
#include "secdialog.h"

class Fsd;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();

private slots:
    void toolButtonClicked(int id);
    /* void stateInserted(State *); */
    /* void transitionInserted(State *); */
    void stateSelected(State *);
    void transitionSelected(Transition *);
    void fsdModified();
    void save();
    void saveAs();
    void openFile();
    void newDiagram();
    void quit();
    void about();
    void exportDot();
    void CtoAsmtoVerilog();

private:
    void createActions();
    void createMenus();
    void createToolbar();
    void createPropertiesPanel();

    void checkUnsavedChanges();
    void saveToFile(QString fname);
    
    Fsd *fsd;
    QGraphicsView *view;
    PropertiesPanel* properties_panel;

    QAction *newDiagramAction;
    QAction *openFileAction;
    QAction *saveFileAction;
    QAction *saveFileAsAction;
    QAction *aboutAction;
    QAction *exitAction;
    QAction *exportDotAction;
    QAction *CtoAsmtoVerAction;

    QMenu *aboutMenu;
    QMenu *fileMenu;
    QMenu *exportMenu;
    QMenu *CtoVerMenu;

    QToolBar *toolBar;
    QButtonGroup *toolSet;

    bool unsaved_changes;
    QString currentFileName;

    static QString title;
    
public:
   Fsd* getFsd() const { return fsd; }
   void setUnsavedChanges(bool unsaved_changes = true);
};

#endif // MAINWINDOW_H
