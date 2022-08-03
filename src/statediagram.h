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
#include<fstream>
// Drawing shapes

#include <string>
#include <map>
#include <stack>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

int stacko = 0;
bool firstState = false;
map<int, int> points;

map<int, vector<string>> textStates;

int stateNum = 1;
int writeState = 1;

stack<int> states;
vector<string> login;
vector<string> initialBegin;

bool s = false;

void tabStackTimes() {
    for (int i = 0; i < stacko; i++) {
        cout << "\t";
    }
}

int findInt(string s) {
    int res = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] - '0' >= 0 && s[i] - '9' <= 0) {
            res *= 10;
            res += s[i] - '0';
        }
    }
    return res;
}
string withoutBracket(string s) {
    string res = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '[')
            break;
        res += s[i];
    }
    return res;
}

bool isHaveBracket(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '[')
            return true;
    }
    return false;
}

void convertAndPrint(string File_C_code, ofstream& myFile) {
    // filestream variable file
    fstream file;
    string word, t, q, filename, prev = "";

    // filename of the file
    filename = File_C_code;
    printf("CODE TEXT OKUNDU");
    // opening file
    file.open(filename.c_str());
    login.clear();

    // extracting words from the file
    while (file >> word) {
        if (word == "{") {
            stacko++;
            tabStackTimes();
            cout << "begin\n";
            myFile << "begin\n";
        }
        else if (word == "}") {
            tabStackTimes();
            stacko--;
            cout << "end\n";
            myFile << "end\n";
        }

        else if (word == "void") {
            file >> word;
            cout << "module " << word;
            myFile << "module " << word;
            file >> word;

            cout << word;
            myFile << word;
            while (word != ")") {
                if (word == ",") {
                    cout << ",";
                    myFile << ",";

                }
                file >> word;
                if (word == ")") break;
                if (word == "int" || word == "char" || word == "float" || word == "double" || word == ",")
                    continue;

                else if (word[0] == '*') {
                    cout << word.substr(1, word.size());
                    myFile << word.substr(1, word.size());
                    login.push_back(word);
                }
                else {
                    cout << word;
                    myFile << word;
                    login.push_back(word);

                }
            }
            cout << ",clk";
            myFile << ",clk";
            cout << word << ";\n";
            myFile << word << ";\n";
            file >> word;
            prev = word;
            cout << "input clk;\nreg[31:0]state; \n";
            myFile << "input clk;\nreg[31:0]state; \n";

            for (int i = 0; i < login.size(); i++) {
                if (login[i][0] == '*') {
                    cout << "output[31:0]" << login[i].substr(1, word.size()) << ";" << endl;
                    myFile << "output[31:0]" << login[i].substr(1, word.size()) << ";" << endl;
                    cout << "reg[31:0]" << login[i].substr(1, word.size()) << ";" << endl;
                    myFile << "reg[31:0]" << login[i].substr(1, word.size()) << ";" << endl;

                }
                else {
                    cout << "input[31:0]" << login[i] << ";" << endl;
                    myFile << "input[31:0]" << login[i] << ";" << endl;
                }
            }

            /*
            input[31:0] n;//
            input clk;
            reg[31:0]state;
            output[31:0] b;//
            reg[31:0] b;//
            */


            cout << "\nlocalparam\n";
            myFile << "\nlocalparam\n";

            for (int i = 0; i < stateNum; i++) {
                cout << "\tS" << i << " = " << i;
                myFile << "\tS" << i << " = " << i;

                if (i == stateNum - 1) {
                    cout << ";\n\n";
                    myFile << ";\n\n";
                }

                else {
                    cout << ",\n";
                    myFile << ",\n";
                }
            }


        }
        else if (word == "(") {
            cout << word;
            while (word != ")") {
                if (word == ",")
                    cout << ",";
                file >> word;
                if (word == ")") break;
                if (word == "int" || word == "char" || word == "float" || word == "double" || word == ",")
                    continue;

                else if (word[0] == '*') {
                    cout << "output [4:0] " << word;
                    myFile << "output [4:0] " << word;
                }
                else {
                    cout << "input [4:0] " << word;
                    myFile << "input [4:0] " << word;
                }
            }
            cout << word << ";\n";
            myFile << word << ";\n";
            file >> word;
            prev = word;
        }
        else if (word == "if" || word == "for") {

            if (!firstState) {
                firstState = true;
                cout << "initial begin\n";
                myFile << "initial begin\n";
                cout << "state <= 0 ;\n";
                myFile << "state <= 0 ;\n";

                for (int i = 0; i < initialBegin.size(); i++) {
                    cout << initialBegin[i] << " <= 0;\n";
                    myFile << initialBegin[i] << " <= 0;\n";

                }

                cout << "end\n";
                myFile << "end\n";
                /*initial
begin
i <= 1;
state <= 0;
end*/


                cout << "\nalways @(posedge clk)\n";
                myFile << "\nalways @(posedge clk)\n";
                cout << "case(state)\n\n";
                myFile << "case(state)\n\n";
                return;
            }


            tabStackTimes();
            while (word != ")") {
                cout << word << " ";
                myFile << word << " ";

                file >> word;
            }
            cout << word << " \n";
            myFile << word << " \n";
        }

        else if (word == ";") {
            cout << ";\n";
            myFile << ";\n";
        }


        else if (word == "int") {
            file >> word;
            tabStackTimes();
            if (!isHaveBracket(word)) {
                initialBegin.push_back(word);
                cout << "reg [31:0] " << word;
                myFile << "reg [31:0] " << word;
            }
            else {
                cout << "reg [31:0] " << withoutBracket(word);
                myFile << "reg [31:0] " << withoutBracket(word);
                int curint = findInt(word);
                string tempres = "[0:"; 
                tempres += to_string(curint - 1);
                tempres += "]";
                cout << tempres;
                myFile << tempres;

            }
        }
        else {

            if (!firstState) {
                firstState = true;

                cout << "initial begin\n";
                myFile << "initial begin\n";
                cout << "state <= 0 ;\n";
                myFile << "state <= 0 ;\n";

                for (int i = 0; i < initialBegin.size(); i++) {
                    cout << initialBegin[i] << " <= 0;\n";
                    myFile << initialBegin[i] << " <= 0;\n";

                }

                cout << "end\n";
                myFile << "end\n";

                cout << "\nalways @(posedge clk)\n";
                myFile << "\nalways @(posedge clk)\n";

                cout << "case(state)\n\n";
                myFile << "case(state)\n\n";
                return;
            }

            if (prev == ";" || prev == "{")
                tabStackTimes();
            cout << word << " ";
            myFile << word << " ";

        }



        prev = word;
    }
    cout << "endmodule " << word;
    myFile << "endmodule " << word;

}



void convertt(string File_C_code) {
    // filestream variable file
    fstream file;
    string word, t, q, filename, prev = "";
    int currentStack = 0;
    // filename of the file
    filename = File_C_code;
    printf("CODE TEXT OKUNDU CONVERT EDILDI");
    // opening file
    file.open(filename.c_str());
    bool stop = true;
    // extracting words from the file
    textStates.clear();
    stateNum = 1;
    while (file >> word) {
        if (word == "if" || word == "for" || word == "while") {
            if (!stop) {
                currentStack++;
                //stateNum++;
                stop = true;
            }
        }
        if (word == "for") {
            s = true;

            if (!stop) currentStack++;

            string incrementer;
            file >> word;
            file >> word;
            incrementer = word;
            file >> word;
            file >> word;
            file >> word;
            file >> word;

            textStates[currentStack].push_back("if(");
            textStates[currentStack].push_back(word);
            file >> word;
            textStates[currentStack].push_back(word);
            file >> word;
            textStates[currentStack].push_back(word);
            textStates[currentStack].push_back(")\nbegin\n\tstate <= S" + to_string(currentStack + 1));
            textStates[currentStack].push_back("; \nend\n");
            textStates[currentStack].push_back("else\nbegin\n\tstate <= S" + to_string((currentStack + 3)));
            textStates[currentStack].push_back("; \n end ");

            while (word != ")")file >> word;

            file >> word;

            textStates[currentStack + 1].push_back("\t");
            file >> word;

            if (word == "if") {
                if (!stop) currentStack++;
                file >> word;
                file >> word;

                textStates[currentStack + 1].push_back("if(");
                textStates[currentStack + 1].push_back(word);
                file >> word;
                textStates[currentStack + 1].push_back(word);
                file >> word;
                textStates[currentStack + 1].push_back(word);
                textStates[currentStack + 1].push_back(")\nbegin\n\tstate <= S" + to_string(currentStack + 2));
                textStates[currentStack + 1].push_back("; \nend\n");
                textStates[currentStack + 1].push_back("else\nbegin\n\tstate <= S" + to_string((currentStack + 3)));
                textStates[currentStack + 1].push_back("; \n end ");

                file >> word;

                file >> word;

                textStates[currentStack + 2].push_back("\t");
                file >> word;




                if (word == "for") {

                    string incrementer2;
                    file >> word;
                    file >> word;
                    incrementer2 = word;
                    file >> word;
                    file >> word;
                    file >> word;
                    file >> word;

                    textStates[currentStack + 2].push_back("if(");
                    textStates[currentStack + 2].push_back(word);
                    file >> word;
                    textStates[currentStack + 2].push_back(word);
                    file >> word;
                    textStates[currentStack + 2].push_back(word);
                    textStates[currentStack + 2].push_back(")\nbegin\n\tstate <= S" + to_string(currentStack + 3));
                    textStates[currentStack + 2].push_back("; \nend\n");
                    textStates[currentStack + 2].push_back("\nelse\nbegin\n\tstate <= S" + to_string((currentStack + 6)));
                    textStates[currentStack + 2].push_back("; \n end ");

                    while (word != ")")file >> word;

                    file >> word;

                    textStates[currentStack + 3].push_back("\t");
                    file >> word;

                    while (word[0] != '}') {
                        if (word == "=")
                            textStates[currentStack + 3].push_back("<");
                        textStates[currentStack + 3].push_back(word);
                        if (word[0] == ';')
                            textStates[currentStack + 3].push_back("\n\t");
                        file >> word;

                    }
                    textStates[currentStack + 3].push_back(incrementer2 + " <= " + incrementer2 + " + 1;\n");

                    textStates[currentStack + 3].push_back("\n\tstate <= S" + to_string((currentStack + 4)) + ";");

                    //textStates[currentStack + 4].push_back("\n\tstate <= S" + to_string(currentStack + 1));




                    //textStates[currentStack + 1].push_back("\n\tstate <= S" + to_string((currentStack + 2)));

                    //textStates[currentStack + 1].push_back(incrementer + " <= " + incrementer + " + 1\n");



                    //textStates[currentStack + 4].push_back("\n\tstate <= S" + to_string(currentStack));







                    while (word != "{")file >> word;

                    file >> word;

                    textStates[currentStack + 5].push_back("\t");

                    while (word[0] != '}') {
                        if (word == "=")
                            textStates[currentStack + 5].push_back("<");
                        textStates[currentStack + 5].push_back(word);
                        if (word[0] == ';')
                            textStates[currentStack + 5].push_back("\n\t");
                        file >> word;

                    }

                    textStates[currentStack + 5].push_back("\tstate <= S" + to_string((currentStack + 6)) + ";");




                    textStates[currentStack + 1].push_back("\n" + incrementer + " <= " + incrementer + " + 1;\n");

                    textStates[currentStack + 6].push_back("\n\tstate <= S" + to_string((currentStack)) + ";");

                    textStates[currentStack + 4].push_back("\n\tstate <= S" + to_string(currentStack + 2) + ";");
                    //cout << textStates[currentStack].size();
                    textStates[currentStack][textStates[currentStack].size() - 2] = ("\nelse\nbegin\n\tstate <= S" + to_string((currentStack + 7)) + ";");
                    textStates[currentStack + 1][7] = ("\nelse\nbegin\n\tstate <= S" + to_string((currentStack + 5)) + ";");




                    stop = true;
                    stateNum += 7;
                    currentStack += 7;

                    continue;

                }





                while (word[0] != '}') {
                    if (word == "=")
                        textStates[currentStack + 2].push_back("<");
                    textStates[currentStack + 2].push_back(word);
                    if (word[0] == ';')
                        textStates[currentStack + 2].push_back("\n\t");
                    file >> word;

                }

                textStates[currentStack + 2].push_back("\tstate <= S" + to_string((currentStack + 4)) + ";");

                while (word != "{")file >> word;

                file >> word;

                textStates[currentStack + 3].push_back("\t");

                while (word[0] != '}') {
                    if (word == "=")
                        textStates[currentStack + 3].push_back("<");
                    textStates[currentStack + 3].push_back(word);
                    if (word[0] == ';')
                        textStates[currentStack + 3].push_back("\n\t");
                    file >> word;

                }

                textStates[currentStack + 3].push_back("\tstate <= S" + to_string((currentStack + 4)) + ";");




                textStates[currentStack + 1].push_back("\n" + incrementer + " <= " + incrementer + " + 1;\n");

                //textStates[currentStack + 1].push_back("\n\tstate <= S" + to_string((currentStack + 4)));

                textStates[currentStack + 4].push_back("\n\tstate <= S" + to_string(currentStack) + ";");
                if (textStates[currentStack].size() >= 2)
                    textStates[currentStack][textStates[currentStack].size() - 2] = ("else\nbegin\n\tstate <= S" + to_string((currentStack + 5)) + " ");



                stop = true;
                stateNum += 5;
                currentStack += 5;
                continue;
            }


            if (word == "for") {

                string incrementer2;
                file >> word;
                file >> word;
                incrementer2 = word;
                file >> word;
                file >> word;
                file >> word;
                file >> word;

                textStates[currentStack + 1].push_back("if(");
                textStates[currentStack + 1].push_back(word);
                file >> word;
                textStates[currentStack + 1].push_back(word);
                file >> word;
                textStates[currentStack + 1].push_back(word);
                textStates[currentStack + 1].push_back(")\nbegin\n\tstate <= S" + to_string(currentStack + 2));
                textStates[currentStack + 1].push_back("; \nend\n");
                textStates[currentStack + 1].push_back("else\nbegin\n\tstate <= S" + to_string((currentStack + 4)));
                textStates[currentStack + 1].push_back("; \n end ");

                while (word != ")")file >> word;

                file >> word;

                textStates[currentStack + 2].push_back("\t");
                file >> word;

                while (word[0] != '}') {
                    if (word == "=")
                        textStates[currentStack + 2].push_back("<");
                    textStates[currentStack + 2].push_back(word);
                    if (word[0] == ';')
                        textStates[currentStack + 2].push_back("\n\t");
                    file >> word;

                }
                textStates[currentStack + 2].push_back(incrementer2 + " <= " + incrementer2 + " + 1;\n");

                textStates[currentStack + 2].push_back("\n\tstate <= S" + to_string((currentStack + 3)) + ";");

                textStates[currentStack + 3].push_back("\n\tstate <= S" + to_string(currentStack + 1) + ";");




                //textStates[currentStack + 1].push_back("\n\tstate <= S" + to_string((currentStack + 2)));

                textStates[currentStack + 1].push_back(incrementer + " <= " + incrementer + " + 1\n");



                textStates[currentStack + 4].push_back("\n\tstate <= S" + to_string(currentStack) + ";");


                textStates[currentStack][textStates[currentStack].size() - 2] = ("else\nbegin\n\tstate <= S" + to_string((currentStack + 5)) + ";");


                stop = true;
                stateNum += 5;
                currentStack += 5;

                continue;

            }

            while (word[0] != '}') {
                if (word == "=")
                    textStates[currentStack + 1].push_back("<");
                textStates[currentStack + 1].push_back(word);
                if (word[0] == ';')
                    textStates[currentStack + 1].push_back("\n\t");
                file >> word;

            }
            textStates[currentStack + 1].push_back(incrementer + " <= " + incrementer + " + 1;\n");

            textStates[currentStack + 1].push_back("\n\tstate <= S" + to_string((currentStack + 2)) + ";");

            textStates[currentStack + 2].push_back("\n\tstate <= S" + to_string(currentStack) + ";");


            stop = true;
            stateNum += 3;
            currentStack += 3;
        }
        else if (word == "while") {
            s = true;

            if (!stop) currentStack++;

            file >> word;
            file >> word;

            textStates[currentStack].push_back("if(");
            textStates[currentStack].push_back(word);
            file >> word;
            textStates[currentStack].push_back(word);
            file >> word;
            textStates[currentStack].push_back(word);
            textStates[currentStack].push_back(")\nbegin\n\tstate <= S" + to_string(currentStack + 1));
            textStates[currentStack].push_back("; \nend\n");
            textStates[currentStack].push_back("else\nbegin\n\tstate <= S" + to_string((currentStack + 3)));
            textStates[currentStack].push_back("; \n end ");

            while (word != ")")file >> word;

            file >> word;

            textStates[currentStack + 1].push_back("\t");
            file >> word;

            if (word == "if") {
                if (!stop) currentStack++;
                file >> word;
                file >> word;

                textStates[currentStack + 1].push_back("if(");
                textStates[currentStack + 1].push_back(word);
                file >> word;
                textStates[currentStack + 1].push_back(word);
                file >> word;
                textStates[currentStack + 1].push_back(word);
                textStates[currentStack + 1].push_back(")\nbegin\n\tstate <= S" + to_string(currentStack + 2));
                textStates[currentStack + 1].push_back("; \nend\n");
                textStates[currentStack + 1].push_back("else\nbegin\n\tstate <= S" + to_string((currentStack + 3)));
                textStates[currentStack + 1].push_back("; \n end ");

                file >> word;

                file >> word;

                textStates[currentStack + 2].push_back("\t");
                file >> word;




                if (word == "for") {

                    string incrementer2;
                    file >> word;
                    file >> word;
                    incrementer2 = word;
                    file >> word;
                    file >> word;
                    file >> word;
                    file >> word;

                    textStates[currentStack + 2].push_back("if(");
                    textStates[currentStack + 2].push_back(word);
                    file >> word;
                    textStates[currentStack + 2].push_back(word);
                    file >> word;
                    textStates[currentStack + 2].push_back(word);
                    textStates[currentStack + 2].push_back(")\nbegin\n\tstate <= S" + to_string(currentStack + 3));
                    textStates[currentStack + 2].push_back("; \nend\n");
                    textStates[currentStack + 2].push_back("\nelse\nbegin\n\tstate <= S" + to_string((currentStack + 6)));
                    textStates[currentStack + 2].push_back("; \n end ");

                    while (word != ")")file >> word;

                    file >> word;

                    textStates[currentStack + 3].push_back("\t");
                    file >> word;

                    while (word[0] != '}') {
                        if (word == "=")
                            textStates[currentStack + 3].push_back("<");
                        textStates[currentStack + 3].push_back(word);
                        if (word[0] == ';')
                            textStates[currentStack + 3].push_back("\n\t");
                        file >> word;

                    }
                    textStates[currentStack + 3].push_back(incrementer2 + " <= " + incrementer2 + " + 1;\n");

                    textStates[currentStack + 3].push_back("\n\tstate <= S" + to_string((currentStack + 4)) + ";");

                    //textStates[currentStack + 4].push_back("\n\tstate <= S" + to_string(currentStack + 1));




                    //textStates[currentStack + 1].push_back("\n\tstate <= S" + to_string((currentStack + 2)));

                    textStates[currentStack + 1].push_back(incrementer2 + " <= " + incrementer2 + " + 1;\n");



                    //textStates[currentStack + 4].push_back("\n\tstate <= S" + to_string(currentStack));







                    while (word != "{")file >> word;

                    file >> word;

                    textStates[currentStack + 5].push_back("\t");

                    while (word[0] != '}') {
                        if (word == "=")
                            textStates[currentStack + 5].push_back("<");
                        textStates[currentStack + 5].push_back(word);
                        if (word[0] == ';')
                            textStates[currentStack + 5].push_back("\n\t");
                        file >> word;

                    }

                    textStates[currentStack + 5].push_back("\tstate <= S" + to_string((currentStack + 6)) + ";");




                    //textStates[currentStack + 1].push_back("\n" + incrementer + " <= " + incrementer + " + 1\n");

                    textStates[currentStack + 6].push_back("\n\tstate <= S" + to_string((currentStack)) + ";");

                    textStates[currentStack + 4].push_back("\n\tstate <= S" + to_string(currentStack + 2) + ";");
                    //cout << textStates[currentStack].size();
                    textStates[currentStack][textStates[currentStack].size() - 2] = ("\nelse\nbegin\n\tstate <= S" + to_string((currentStack + 7)) + ";");
                    textStates[currentStack + 1][7] = ("\nelse\nbegin\n\tstate <= S" + to_string((currentStack + 5)) + ";");




                    stop = true;
                    stateNum += 7;
                    currentStack += 7;

                    continue;

                }





                while (word[0] != '}') {
                    if (word == "=")
                        textStates[currentStack + 2].push_back("<");
                    textStates[currentStack + 2].push_back(word);
                    if (word[0] == ';')
                        textStates[currentStack + 2].push_back("\n\t");
                    file >> word;

                }

                textStates[currentStack + 2].push_back("\tstate <= S" + to_string((currentStack + 4)) + ";");

                while (word != "{")file >> word;

                file >> word;

                textStates[currentStack + 3].push_back("\t");

                while (word[0] != '}') {
                    if (word == "=")
                        textStates[currentStack + 3].push_back("<");
                    textStates[currentStack + 3].push_back(word);
                    if (word[0] == ';')
                        textStates[currentStack + 3].push_back("\n\t");
                    file >> word;

                }

                textStates[currentStack + 3].push_back("\tstate <= S" + to_string((currentStack + 4)) + ";");




                //textStates[currentStack + 1].push_back("\n" + incrementer + " <= " + incrementer + " + 1\n");

                //textStates[currentStack + 1].push_back("\n\tstate <= S" + to_string((currentStack + 4)));

                textStates[currentStack + 4].push_back("\n\tstate <= S" + to_string(currentStack) + ";");

                textStates[currentStack][textStates[currentStack].size() - 2] = ("else\nbegin\n\tstate <= S" + to_string((currentStack + 5)) + ";");



                stop = true;
                stateNum += 5;
                currentStack += 5;
                continue;
            }


            if (word == "for") {

                string incrementer2;
                file >> word;
                file >> word;
                incrementer2 = word;
                file >> word;
                file >> word;
                file >> word;
                file >> word;

                textStates[currentStack + 1].push_back("if(");
                textStates[currentStack + 1].push_back(word);
                file >> word;
                textStates[currentStack + 1].push_back(word);
                file >> word;
                textStates[currentStack + 1].push_back(word);
                textStates[currentStack + 1].push_back(")\nbegin\n\tstate <= S" + to_string(currentStack + 2) + ";");
                textStates[currentStack + 1].push_back("; \nend\n");
                textStates[currentStack + 1].push_back("else\nbegin\n\tstate <= S" + to_string((currentStack + 4)) + ";");
                textStates[currentStack + 1].push_back("; \n end ");

                while (word != ")")file >> word;

                file >> word;

                textStates[currentStack + 2].push_back("\t");
                file >> word;

                while (word[0] != '}') {
                    if (word == "=")
                        textStates[currentStack + 2].push_back("<");
                    textStates[currentStack + 2].push_back(word);
                    if (word[0] == ';')
                        textStates[currentStack + 2].push_back("\n\t");
                    file >> word;

                }
                textStates[currentStack + 2].push_back(incrementer2 + " <= " + incrementer2 + " + 1;\n");

                textStates[currentStack + 2].push_back("\n\tstate <= S" + to_string((currentStack + 3)) + ";");

                textStates[currentStack + 3].push_back("\n\tstate <= S" + to_string(currentStack + 1) + ";");




                //textStates[currentStack + 1].push_back("\n\tstate <= S" + to_string((currentStack + 2)));

                //textStates[currentStack + 1].push_back(incrementer + " <= " + incrementer + " + 1\n");



                textStates[currentStack + 4].push_back("\n\tstate <= S" + to_string(currentStack) + ";");


                textStates[currentStack][textStates[currentStack].size() - 2] = ("else\nbegin\n\tstate <= S" + to_string((currentStack + 5)) + ";");


                stop = true;
                stateNum += 5;
                currentStack += 5;

                continue;

            }






            while (word[0] != '}') {
                if (word == "=")
                    textStates[currentStack + 1].push_back("<");
                textStates[currentStack + 1].push_back(word);
                if (word[0] == ';')
                    textStates[currentStack + 1].push_back("\n\t");
                file >> word;

            }

            textStates[currentStack + 1].push_back("\n\tstate <= S" + to_string((currentStack + 2)) + ";");

            textStates[currentStack + 2].push_back("\n\tstate <= S" + to_string(currentStack) + ";");


            stop = true;
            stateNum += 3;
            currentStack += 3;
        }
        else if (word == "if") {
            s = true;
            if (!stop) currentStack++;
            file >> word;
            file >> word;

            textStates[currentStack].push_back("if(");
            textStates[currentStack].push_back(word);
            file >> word;
            textStates[currentStack].push_back(word);
            file >> word;
            textStates[currentStack].push_back(word);
            textStates[currentStack].push_back(")\nbegin\n\tstate <= S" + to_string(currentStack + 1));
            textStates[currentStack].push_back("; \nend\n");
            textStates[currentStack].push_back("else\nbegin\n\tstate <= S" + to_string((currentStack + 2)));
            textStates[currentStack].push_back("; \n end ");

            file >> word;

            file >> word;

            textStates[currentStack + 1].push_back("\t");
            file >> word;

            if (word == "for") {

                string incrementer2;
                file >> word;
                file >> word;
                incrementer2 = word;
                file >> word;
                file >> word;
                file >> word;
                file >> word;

                textStates[currentStack + 1].push_back("if(");
                textStates[currentStack + 1].push_back(word);
                file >> word;
                textStates[currentStack + 1].push_back(word);
                file >> word;
                textStates[currentStack + 1].push_back(word);
                textStates[currentStack + 1].push_back(")\nbegin\n\tstate <= S" + to_string(currentStack + 2));
                textStates[currentStack + 1].push_back("; \nend\n");
                textStates[currentStack + 1].push_back("else\nbegin\n\tstate <= S" + to_string((currentStack + 5)));
                textStates[currentStack + 1].push_back("; \n end ");

                while (word != ")")file >> word;

                file >> word;

                textStates[currentStack + 2].push_back("\t");
                file >> word;

                while (word[0] != '}') {
                    if (word == "=")
                        textStates[currentStack + 2].push_back("<");
                    textStates[currentStack + 2].push_back(word);
                    if (word[0] == ';')
                        textStates[currentStack + 2].push_back("\n\t");
                    file >> word;

                }
                textStates[currentStack + 2].push_back(incrementer2 + " <= " + incrementer2 + " + 1;\n");

                textStates[currentStack + 2].push_back("\n\tstate <= S" + to_string((currentStack + 3)) + ";");

                textStates[currentStack + 3].push_back("\n\tstate <= S" + to_string(currentStack + 1) + ";");




                //textStates[currentStack + 1].push_back("\n\tstate <= S" + to_string((currentStack + 2)));

                //textStates[currentStack + 1].push_back(incrementer + " <= " + incrementer + " + 1\n");



                //textStates[currentStack + 4].push_back("\n\tstate <= S" + to_string(currentStack + 5));


                textStates[currentStack][textStates[currentStack].size() - 2] = ("else\nbegin\n\tstate <= S" + to_string((currentStack + 4)) + ";");




                while (word != "{")file >> word;

                file >> word;

                textStates[currentStack + 4].push_back("\t");

                while (word[0] != '}') {
                    if (word == "=")
                        textStates[currentStack + 4].push_back("<");
                    textStates[currentStack + 4].push_back(word);
                    if (word[0] == ';')
                        textStates[currentStack + 4].push_back("\n\t");
                    file >> word;

                }

                textStates[currentStack + 4].push_back("\tstate <= S" + to_string((currentStack + 5)) + ";");





                stop = true;
                stateNum += 5;
                currentStack += 5;

                continue;

            }

            if (word == "while") {


                file >> word;
                file >> word;

                textStates[currentStack + 1].push_back("if(");
                textStates[currentStack + 1].push_back(word);
                file >> word;
                textStates[currentStack + 1].push_back(word);
                file >> word;
                textStates[currentStack + 1].push_back(word);
                textStates[currentStack + 1].push_back(")\nbegin\n\tstate <= S" + to_string(currentStack + 2));
                textStates[currentStack + 1].push_back("; \nend\n");
                textStates[currentStack + 1].push_back("else\nbegin\n\tstate <= S" + to_string((currentStack + 5)));
                textStates[currentStack + 1].push_back("; \n end ");

                while (word != ")")file >> word;

                file >> word;

                textStates[currentStack + 2].push_back("\t");
                file >> word;

                while (word[0] != '}') {
                    if (word == "=")
                        textStates[currentStack + 2].push_back("<");
                    textStates[currentStack + 2].push_back(word);
                    if (word[0] == ';')
                        textStates[currentStack + 2].push_back("\n\t");
                    file >> word;

                }


                textStates[currentStack + 2].push_back("\n\tstate <= S" + to_string((currentStack + 3)) + ";");

                textStates[currentStack + 3].push_back("\n\tstate <= S" + to_string(currentStack + 1) + ";");




                //textStates[currentStack + 1].push_back("\n\tstate <= S" + to_string((currentStack + 2)));

                //textStates[currentStack + 1].push_back(incrementer + " <= " + incrementer + " + 1\n");



                //textStates[currentStack + 4].push_back("\n\tstate <= S" + to_string(currentStack + 5));


                textStates[currentStack][textStates[currentStack].size() - 2] = ("else\nbegin\n\tstate <= S" + to_string((currentStack + 4)) + ";");




                while (word != "{")file >> word;

                file >> word;

                textStates[currentStack + 4].push_back("\t");

                while (word[0] != '}') {
                    if (word == "=")
                        textStates[currentStack + 4].push_back("<");
                    textStates[currentStack + 4].push_back(word);
                    if (word[0] == ';')
                        textStates[currentStack + 4].push_back("\n\t");
                    file >> word;

                }

                textStates[currentStack + 4].push_back("\tstate <= S" + to_string((currentStack + 5)) + ";");





                stop = true;
                stateNum += 5;
                currentStack += 5;

                continue;

            }




            while (word[0] != '}') {
                if (word == "=")
                    textStates[currentStack + 1].push_back("<");
                textStates[currentStack + 1].push_back(word);
                if (word[0] == ';')
                    textStates[currentStack + 1].push_back("\n\t");
                file >> word;

            }

            textStates[currentStack + 1].push_back("\tstate <= S" + to_string((currentStack + 3)) + ";");

            while (word != "{")file >> word;

            file >> word;

            textStates[currentStack + 2].push_back("\t");

            while (word[0] != '}') {
                if (word == "=")
                    textStates[currentStack + 2].push_back("<");

                textStates[currentStack + 2].push_back(word);
                if (word[0] == ';')
                    textStates[currentStack + 2].push_back("\n\t");
                file >> word;

            }

            textStates[currentStack + 2].push_back("\tstate <= S" + to_string((currentStack + 3)) + ";");



            stop = true;
            stateNum += 3;
            currentStack += 3;
        }
        else if (word == "=") {
            if (stop) {
                stateNum++;
                //currentStack++;
            }
            //if (!s) currentStack--;
            textStates[currentStack].push_back(prev);

            while (word[0] != ';') {
                if (word == "=")
                    textStates[currentStack].push_back("<");
                textStates[currentStack].push_back(word + " ");
                file >> word;
            }
            textStates[currentStack].push_back(";");
            string text = "\tstate <= S" + to_string((currentStack + 1)) + ";";
            if (!count(textStates[currentStack].begin(), textStates[currentStack].end(), text)) {
                textStates[currentStack].push_back(text);

            }


            stop = false;
        }
        prev = word;
    }
}


void printStates(ofstream& myFile) {
    for (int i = 0; i < stateNum; i++) {
        cout << "S" << i << ":\n";
        myFile << "S" << i << ":\n";

        cout << "begin\n";
        myFile << "begin\n";

        if (textStates[i].size() > 0) {
            for (int j = 0; j < textStates[i].size(); j++) {
                cout << textStates[i][j];
                myFile << textStates[i][j];

            }
        }

        if (i == stateNum - 1) {
            //cout << "EXIT\n";
            //myFile << "EXIT\n";

        }
        cout << "\nend\n";
        myFile << "\nend\n";

    }

    myFile << " endcase\n";
    cout << " endcase\n";

    myFile << " endmodule\n";
    cout << " endmodule\n";

}





////****ASSSÝNGMENT SÝTUATÝON
           /*  if (isContained(word, operators, 6)) {

                  cout << "dogrumu";
                  Point p1(30, matrix_a);//for rectangular
                  Point p2(120, matrix_b);//for rectangular
                  Point p3(15, matrix_d);//for text

                  draw_diagram(image,line,p1,p2,p3);
                  matrix_a += 120;
                  matrix_b += 120;
                  matrix_c += 120;
                  matrix_d += 120;
              }*/
