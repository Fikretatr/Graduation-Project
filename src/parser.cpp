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

using namespace std;

struct State_
{
  string id;
  float x;
  float y;
  string description;
};

struct Transition_
{
  string srcState;
  string destState;
  int location;
  string label;
};

vector<struct State_> states_;
vector<struct Transition_> transitions;
string init = "";

void parseState(ifstream &file, int currentState, int depth = 0, string label = "")
{
  string line;
  while (getline(file, line))
  {
    if (line.find("end") != std::string::npos)
      return;
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
    if (line.find("begin") != std::string::npos)
    {
      if (depth > 0)
      {
        parseState(file, currentState, depth++, label);
      }
      else
      {
        depth++;
      }
    }
    if (line.find("if") != std::string::npos)
    {
      int a = line.find("(");
      int b = line.find(")");
      label = line.substr(a, b);
    }
    if (line.find("else") != std::string::npos)
    {
      label = "!" + label;
    }
    if (line.find(";") != std::string::npos)
    {
      string newLine;
      stringstream S(line);
      while (getline(S, newLine, ';'))
      {
        if (newLine.find("state") != std::string::npos)
        {
          struct Transition_ t;
          t.srcState.append(to_string(currentState));
          int a = newLine.find("=S");
          int b = newLine.find(";");
          string dest = newLine.substr(a + 2, b - 1);
          t.destState = dest;
          t.label = label;
          t.location = 0;
          transitions.push_back(t);
        }
        else
        {
          states_[currentState].description.append(newLine);
          states_[currentState].description.append("; ");
        }
      }
    }
  }
}

void toJSON(string fileName)
{
  string mainStr = "{\n";
  ofstream myFile(fileName);

  if (myFile.is_open())
  {
    mainStr.append("  \"init\": ");
    mainStr.append("\""+init+"\",\n");
    mainStr.append("  \"states\": [\n");

    for (size_t i = 0; i < states_.size(); i++)
    {
      mainStr.append("    {\n");
      mainStr.append("      \"id\": ");
      mainStr.append("\""+states_[i].id+"\"");
      mainStr.append(",\n");
      mainStr.append("      \"description\": ");
      mainStr.append("\""+states_[i].description+"\"");
      mainStr.append(",\n");
      mainStr.append("      \"x\": ");
      char x[10];
      sprintf(x, "%0.1f", states_[i].x);
      mainStr.append(x);
      mainStr.append(",\n");
      mainStr.append("      \"y\": ");
      char y[10];
      sprintf(y, "%0.1f", states_[i].y);
      mainStr.append(y);
      mainStr.append("\n");
      if(i != states_.size()-1){
        mainStr.append("    },\n");
      }else{
        mainStr.append("    }\n");
      }
      
    }

    mainStr.append("  ],\n");

    mainStr.append("  \"transitions\": [\n");

    for (size_t i = 0; i < transitions.size(); i++)
    {
      mainStr.append("    {\n");
      mainStr.append("      \"src_state\": ");
      mainStr.append("\""+transitions[i].srcState+"\"");
      mainStr.append(",\n");
      mainStr.append("      \"dst_state\": ");
      mainStr.append("\""+transitions[i].destState+"\"");
      mainStr.append(",\n");
      mainStr.append("      \"label\": ");
      mainStr.append("\""+transitions[i].label+"\"");
      mainStr.append(",\n");
      mainStr.append("      \"location\": ");
      mainStr.append(to_string(transitions[i].location));
      mainStr.append("\n");
      if(i != transitions.size()-1){
        mainStr.append("    },\n");
      }else{
        mainStr.append("    }\n");
      }
      
    }

    mainStr.append("  ]\n");

    mainStr.append("}");
    myFile << mainStr;
  }
}

void printStates()
{
  for (size_t i = 0; i < states_.size(); i++)
  {
    cout << states_[i].id << ":" << endl;
    cout << states_[i].description << endl;
  }
}

void printTrans()
{
  for (size_t i = 0; i < transitions.size(); i++)
  {
    cout << transitions[i].srcState << endl;
    cout << transitions[i].destState << endl;
    cout << transitions[i].label << endl;
    cout << transitions[i].location << endl;
    cout << "end" << endl;
  }
}

void readFile(const string fileName)
{
  ifstream myFile(fileName);
  string line;
  int currentState = 0;
  states_.clear();
  transitions.clear();
  init = "";
  if (myFile.is_open())
  {
    while (getline(myFile, line))
    {
      // cout << line << endl;
      // cout << strcmp(line.c_str(),"localparam") << endl;
      // cout << line << endl;

      if((line.find("module") != std::string::npos && line.find("endmodule") == std::string::npos) || line.find("reg") != std::string::npos || line.find("input") != std::string::npos || line.find("output") != std::string::npos){
        line = regex_replace( line,std::regex("\\r\\n|\\r|\\n"),"");
        init.append(line + "\\n");
      }
      if(line.find("initial") != std::string::npos){
        struct State_ s;
        s.id = "_init";
        while (getline(myFile, line))
        {
          if(line.find("end") != std::string::npos) break;  
          line = regex_replace( line,std::regex("\\r\\n|\\r|\\n"),"");
          line.append("\\n");
          s.description.append(line);
        }
        states_.push_back(s);
      }
      if (line.find("localparam") != std::string::npos)
      {
        int cnt = 0;
        while (getline(myFile, line))
        {
          if (line.length() < 2)
            break;
          line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
          struct State_ s;
          int index = line.find('=');
          string temp;
          for (size_t i = index + 1; line.at(i) != ',' && line.at(i) != ';'; i++)
          {
            temp.push_back(line.at(i));
          }

          s.id = temp;
          s.x = 50.0;
          s.y = 70 + (cnt * 90);
          states_.push_back(s);
          cnt++;
        }
      }
      regex stateRegex("S[0-9]:|S[1-9][0-9]:");
      // cout << regex_search(line, stateRegex) << endl;
      if (regex_search(line, stateRegex))
      {
        // cout << line << endl;
        parseState(myFile, currentState);
        currentState++;
      }
    }
  }
}
