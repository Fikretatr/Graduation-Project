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

#ifndef JSONTOVLOG_H
#define JSONTOVLOG_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <regex>
#include <sstream>
#include <stdlib.h>
#include <QString>
#include "include/nlohmann_json.h"

using namespace std;
using namespace nlohmann;

struct _State
{
  string id;
  float x;
  float y;
  string description;
  vector<struct _Transition> transitions;
};

struct _Transition
{
  string srcState;
  string destState;
  int location;
  string label;
};

class JsonToVerilog{

public:
  void getVars();
  void readFile(QString fileName, bool isFromCCode = true);
  void toVlog(QString fileName, bool isFromCCode = true);
private: 

  vector<struct _State> states;

  string init = "";
  vector<string> vars;

};
#endif



