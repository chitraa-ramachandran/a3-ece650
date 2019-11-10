//
// Created by Jimisha Thakkar on 18/10/19.
//
#include <iostream>
#include <regex>
#include<sstream>
#include<queue>
using namespace std;

int stringToInt(string temp) {
    int V;
    stringstream ss(temp);
    ss >> V;
    return V;
}



int parseStringV(string strVertices)
{
    string temp = "";
    int V = 0;
    for(int i = 2; strVertices[i] != '\0'; i++)
    {
        temp += strVertices[i];
    }
    V = stringToInt(temp);
    return V;
}

vector<int> parseStringE(string strEdges)
{
    vector<int> edgesVector;
    char *tempCharArr = new char[strEdges.length()+1];
    copy(strEdges.begin(),strEdges.end(),tempCharArr);
    tempCharArr[strEdges.length()] = '\0';
    char *p;
    p = strtok(tempCharArr, "E {<,>}");
    while(p != NULL)
    {
        edgesVector.push_back(stringToInt(p));
        p = strtok(NULL, "E {<,>}");
    }
    return edgesVector;
}

vector<int> parseStringS(string strS)
{
    vector<int> srcDestVector;
    char *tempCharArr = new char[strS.length()+1];
    copy(strS.begin(),strS.end(),tempCharArr);
    tempCharArr[strS.length()] = '\0';
    char *p;
    p = strtok(tempCharArr, " ");
    int count = 0;
    while(p != NULL)
    {
        if(count != 0)
        {
            srcDestVector.push_back(stringToInt(p));
        }
        count++;
        p = strtok(NULL, " ");
    }
    return srcDestVector;
}

bool checkForEInRangeOfV(vector<int> edgesVector,int V)
{
    for(unsigned i = 0; i < edgesVector.size(); i++)
    {
        if(edgesVector[i] < 0 || edgesVector[i] >= V)
            return false;
    }
    return true;
}
