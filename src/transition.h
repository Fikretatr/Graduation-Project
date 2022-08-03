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

#ifndef TRANSITION_H
#define TRANSITION_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSimpleTextItem>
#include "state.h"

QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
QT_END_NAMESPACE

class Transition : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 4 };

    Transition(State *srcState, State *dstState, QString label, State::Location location, QGraphicsItem *parent = 0);

    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    State *srcState() const { return mySrcState; }
    State *dstState() const { return myDstState; }
    QString getLabel();
    State::Location location() const { return myLocation; }
    void setSrcState(State *s) { mySrcState = s; }
    void setDstState(State *s) { myDstState = s; }
    void setLabel(QString s);
    bool isInitial();

    void updatePosition();

    static QColor selectedColor;
    static QColor unSelectedColor;
    static double arrowSize;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

private:
    State *mySrcState;
    State *myDstState;
    QPolygonF arrowHead;
    QGraphicsSimpleTextItem *myLabel;
    State::Location myLocation;
};

#endif // TRANSITION_H
