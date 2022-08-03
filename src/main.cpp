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
#include "mainwindow.h"

#include <QApplication>

int main(int argv, char *args[])
{
    QApplication app(argv, args);
    MainWindow mainWindow;
    mainWindow.setGeometry(100, 100, 700, 600);
    mainWindow.show();

    return app.exec();
}
