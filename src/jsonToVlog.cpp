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
#include "jsonToVlog.h"




void JsonToVerilog::getVars()
{

  for (size_t i = 0; i < states.size(); i++)
  {
    if (states[i].description.length() < 2 || states[i].id.compare("_init") == 0)
      continue;
    string temp = states[i].description;
    string token;
    temp.erase(std::remove_if(temp.begin(), temp.end(), ::isspace), temp.end());

    stringstream S(temp);
    while (getline(S, token, ';'))
    {
      int a = token.find("<");
      string var = token.substr(0, a);
      if (find(vars.begin(), vars.end(), var) != vars.end() || var.compare("b") == 0)
      {
        continue;
      }
      else
      {
        vars.push_back(var);
      }
    }
  }
}

void JsonToVerilog::readFile(QString fileName, bool isFromCCode)
{
  ifstream myFile(fileName.toStdString());
  string line;
  states.clear();

  json jsonFile;
  if(myFile.is_open()){
      myFile >> jsonFile;
      if (isFromCCode || (jsonFile.find("init") != jsonFile.end() && !jsonFile["init"].get<string>().empty()))
      {
        init = jsonFile["init"].get<string>();
      }
      else
      {
        init = "module noName(b,clk);\ninput clk;\nreg[31:0]_State;\noutput[31:0]b;\nreg[31:0]b;\n";
      }
      vector<json> statesJson = jsonFile["states"].get<vector<json>>();
      for (size_t i = 0; i < statesJson.size(); i++)
      {
        struct _State s = {statesJson[i]["id"], statesJson[i]["x"], statesJson[i]["y"], statesJson[i]["description"]};
        states.push_back(s);
      }

      vector<json> transJson = jsonFile["transitions"].get<vector<json>>();
      for (size_t i = 0; i < transJson.size(); i++)
      {
        struct _Transition s = {transJson[i]["src_state"], transJson[i]["dst_state"], transJson[i]["location"], transJson[i]["label"]};
        int index = atoi(s.srcState.c_str());
        states[states.size()-1-index].transitions.push_back(s);
      }
      if (!isFromCCode)
      {
        getVars();
      }
  }

  // cout << jsonFile["states"].get<vector<json>>()[0]["id"] << endl;
}

void JsonToVerilog::toVlog(QString fileName, bool isFromCCode)
{
  ofstream myFile(fileName.toStdString());
  if (myFile.is_open())
  {
    myFile << init;
    myFile << "\nlocalparam\n";
    for (size_t i = 0; i < states.size(); i++)
    {
      myFile << "  S" << i << " = " << i << endl;
    }
    myFile << "\n";
    for (size_t i = 0; i < vars.size(); i++)
    {
      myFile << "reg[31:0] " << vars[i] << ";" << endl;
    }
    myFile << "initial begin" << endl;
    bool flag = true;
    if (isFromCCode)
    {
      for (int i = states.size()-1; i >= 0 ; i--)
      {
        if (states[i].id.compare("_init") == 0)
        {
          flag = false;
          if(states[i].description.empty()){
              getVars();
              myFile << "state <= 0\n";
              for (size_t i = 0; i < vars.size(); i++)
              {
                myFile << vars[i] << "<= 0\n";
              }
          }
          else{
              myFile << states[i].description;
          }
        }
      }
      if(flag){
          getVars();
          myFile << "state <= 0\n";
          for (size_t i = 0; i < vars.size(); i++)
          {
            myFile << vars[i] << "<= 0\n";
          }
      }
    }
    else
    {
      myFile << "state <= 0\n";
      for (size_t i = 0; i < vars.size(); i++)
      {
        myFile << vars[i] << "<= 0\n";
      }
    }
    myFile << "end\n\n";

    myFile << "always @(posedge clk)\n";
    myFile << "case(state)\n\n";

    for (int i = states.size()-1; i >= 0 ; i--)
    {
      struct _State s = states[i];
      if (s.id.compare("_init") == 0)
        continue;
      myFile << "S" << s.id << ":" << endl;
      myFile << "begin" << endl;
      string temp = s.description;
      string token;
      stringstream S(temp);
      while (getline(S, token, ';'))
      {
        if(token.length() > 2)
        myFile << "  " << token << ";" << endl;
      }
      if(s.transitions.size()==1){
        myFile << "  state <= S" << s.transitions[0].destState << ";" << endl;
      }else if(s.transitions.size() == 2){
        if(s.transitions[0].label.find("!") == std::string::npos){
          myFile << "  if" << s.transitions[0].label << endl;
          myFile << "    begin" << endl;
          myFile << "      state <= S" << s.transitions[0].destState << endl;
          myFile << "    end" << endl;
          myFile << "  else" << endl;
          myFile << "    begin" << endl;
          myFile << "      state <= S" << s.transitions[1].destState << endl;
          myFile << "    end" << endl;
        }else{
          myFile << "  if" << s.transitions[1].label << endl;
          myFile << "    begin" << endl;
          myFile << "      state <= S" << s.transitions[1].destState << endl;
          myFile << "    end" << endl;
          myFile << "  else" << endl;
          myFile << "    begin" << endl;
          myFile << "      state <= S" << s.transitions[0].destState << endl;
          myFile << "    end" << endl;
        }
      }
      
      
      myFile << "end" << endl; 
    }
    myFile << "endcase\n";
    myFile << "endmodule\n";
  }
}


