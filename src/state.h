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

#ifndef STATE_H
#define STATE_H

#include <QGraphicsPixmapItem>
#include <QList>

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QMenu;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QPolygonF;
QT_END_NAMESPACE

class Transition;

class State : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };
    enum Location { None=0, North=1, South=2, East=3, West=4 }; // for looping transitions;

    State(QString id,QString description ,QGraphicsItem *parent = 0);
    State(QGraphicsItem *parent = 0); // For initial pseudo-states

    void removeTransition(Transition *transition);
    void removeTransitions();
    QPolygonF polygon() const { return myPolygon; }
    void addTransition(Transition *transition);
    int type() const override { return Type;}
    QString getId() const { return id; }
    QString getDes() const { return Description; }
    void setId(QString id) { this->id = id; }
    void setDescription(QString Description) { this->Description = Description; }
    QList<Transition *> getTransitionsTo(State *dstState);
    QList<Transition *> getTransitionsFrom(State *srcState);
    Location locateEvent(QGraphicsSceneMouseEvent* event);
    bool isPseudo() const { return isPseudoState; };

    static QSize boxSize;
    static QSize dskSize;
    static QString initPseudoId;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    static QColor boxBackground;
    static QColor selectedColor;
    static QColor unSelectedColor;

private:
    QString id;
    QString Description;
    QPolygonF myPolygon;
    QList<Transition *> transitions;
    bool isPseudoState;
};

#endif // STATE_H
