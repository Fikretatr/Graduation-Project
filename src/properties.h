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

#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QComboBox>
#include <QFrame>
#include <QGraphicsItem>
#include <QGroupBox>
#include <QLineEdit>
#include <QListView>
#include <QString>
#include <QStringListModel>

class MainWindow;
class State;
class Transition;

class PropertiesPanel : public QFrame
{
    Q_OBJECT

  private:
    MainWindow* main_window;

    QGraphicsItem* selected_item;

    QGroupBox* state_panel;
    QLineEdit* state_name_field;
    QLineEdit* Deslabel_field;

    QGroupBox* transition_panel;
    QComboBox* transition_start_state_field;
    QComboBox* transition_end_state_field;
    QLineEdit* transition_label_field;

    QGroupBox* itransition_panel;
    QComboBox* itransition_end_state_field;
    QLineEdit* itransition_label_field;

  public:
    explicit PropertiesPanel(MainWindow* parent);
    ~PropertiesPanel();

    void unselectItem();
    void setSelectedItem(State* state);
    void setSelectedItem(Transition* transition);

    void toggleStimuliPanel();                                                    

  public slots:
    void setStateName(const QString& name);
    void setStateDescription(const QString& Description);

    void setTransitionSrcState(int index);
    void setTransitionDstState(int index);
    void setTransitionLabel(const QString& label);
    void setITransitionDstState(int index);

    void clear();

  private:
    void createStatePanel();
    void createTransitionPanel();
    void createInitTransitionPanel();
};

#endif
