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

#include "state.h"
#include "transition.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <qDebug>

QSize State::dskSize = QSize(15,15);
QSize State::boxSize = QSize(100,70);
QColor State::boxBackground = Qt::white;
QColor State::selectedColor = Qt::darkCyan;
QColor State::unSelectedColor = Qt::black;
QString State::initPseudoId = "_init";

State::State(QString id,QString description ,QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
{
    QPainterPath path;
    myPolygon << QPointF(-boxSize.width()/2, -boxSize.height()/2) // P1-----P2
              << QPointF(boxSize.width()/2, -boxSize.height()/2)  //  |     |
              << QPointF(boxSize.width()/2, boxSize.height()/2)   //  |     |
              << QPointF(-boxSize.width()/2, boxSize.height()/2)  // P4-----P3
              << QPointF(-boxSize.width()/2, -boxSize.height()/2);
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->id = id;
    this->Description = description;
    isPseudoState = false;
}

State::State(QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
{
    QPainterPath path;
    myPolygon << QPointF(-dskSize.width()/2, -dskSize.height()/2) 
              << QPointF(dskSize.width()/2, -dskSize.height()/2) 
              << QPointF(dskSize.width()/2, dskSize.height()/2) 
              << QPointF(-dskSize.width()/2, dskSize.height()/2)
              << QPointF(-dskSize.width()/2, -dskSize.height()/2);
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->id = initPseudoId;
    isPseudoState = true;
}


void State::removeTransition(Transition *transition)
{
    int index = transitions.indexOf(transition);

    if (index != -1)
        transitions.removeAt(index);
}

void State::removeTransitions()
{
    foreach (Transition *transition, transitions) {
        transition->srcState()->removeTransition(transition);
        transition->dstState()->removeTransition(transition);
        scene()->removeItem(transition);
        delete transition;
    }
}

void State::addTransition(Transition *transition)
{
    transitions.append(transition);
}

void State::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->setRenderHint(QPainter::Antialiasing);
  if ( isPseudoState ) {
    painter->setBrush(Qt::black);
    painter->drawEllipse(myPolygon.boundingRect());
    }
  else {
    painter->setPen(QPen(isSelected() ? selectedColor : unSelectedColor, 1));
    painter->setBrush(boxBackground);
    painter->drawPolygon(myPolygon);
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, Description);
    painter->drawText(boundingRect(), Qt::AlignAbsolute | Qt::AlignAbsolute, id);
    }
}

QVariant State::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (Transition *transition, transitions) {
            transition->updatePosition();
        }
    }
    return value;
}

QList<Transition*> State::getTransitionsTo(State* dstState)
{
  QList<Transition *> res;
  for ( auto a : transitions ) 
    if ( a->dstState() == dstState ) res.append(a);
  return res;
}

QList<Transition*> State::getTransitionsFrom(State* srcState)
{
  QList<Transition *> res;
  for ( auto a : transitions ) 
    if ( a->srcState() == srcState ) res.append(a);
  return res;
}

State::Location State::locateEvent(QGraphicsSceneMouseEvent *event)
{
  QPointF p = event->scenePos();
  QPointF c = mapToScene(0,0);
  QPolygonF r = mapToScene(boundingRect());
  QPolygonF north, east, south, west;
  north << c << r.at(0) << r.at(1) << c;
  east << c << r.at(1) << r.at(2) << c;
  south << c << r.at(2) << r.at(3) << c;
  west << c << r.at(3) << r.at(0) << c;
  if ( north.containsPoint(p,Qt::OddEvenFill) ) return State::North;
  else if ( east.containsPoint(p,Qt::OddEvenFill) ) return State::East;
  else if ( south.containsPoint(p,Qt::OddEvenFill) ) return State::South;
  else if ( west.containsPoint(p,Qt::OddEvenFill) ) return State::West;
  return State::None;
}
