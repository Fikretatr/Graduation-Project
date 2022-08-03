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

#ifndef FSD_H
#define FSD_H

#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>

#include "state.h"
#include "jsonToVlog.h"


QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QColor;
QT_END_NAMESPACE

class Fsd : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertState, InsertPseudoState, InsertTransition, InsertLoopTransition, SelectItem, DeleteItem,ConvertJtoVer };

    explicit Fsd(QWidget *parent = 0);
    void fromString(QString& json_text);
    QString toString();

    void exportDot(QString fname);

    State* initState();
    QList<State*> states();
    QList<Transition*> transitions();
    string initData;

    State* getState(QString id);
    bool hasPseudoState();
    void setfilename(QString filename){
        FileNameJson=filename;
    };
    void convert_jtover();
    inline static bool isFromCCode =false;
public slots:
    void setMode(Mode mode);

signals:
    /* void stateInserted(State *item); */
    /* void transitionInserted(Transition *item); */
    void fsdModified();
    void stateSelected(State *item);
    void transitionSelected(Transition *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    static int stateCounter;

private:
    bool isItemChange(int type);
    State* addState(QPointF pos, QString id,QString description);
    State* addPseudoState(QPointF pos);
    Transition* addTransition(State* srcState, State* dstState, QString label, State::Location location);
    QString FileNameJson;
    JsonToVerilog converter;
    Mode mode;
    QGraphicsLineItem *line;  // Line being drawn
    State *startState;

    QWidget *mainWindow;

    static QColor lineColor;
    static QColor boxColor;
};

#endif // FSD_H
