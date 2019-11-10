//
// Created by Jimisha Thakkar on 18/10/19.
//
#include <iostream>
#include <regex>
#include<sstream>
#include<queue>

using namespace std;

bool regexCheckForV(string strVertices)
{
    if (regex_match(strVertices, regex ("^[V]\\s\\d+$")))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool regexCheckForE(string strEdges)
{
    if(regex_match(strEdges, regex("^[E]\\s\\{[\\<\\d+\\,\\d+\\>\\,]*[\\<\\d+\\,\\d+\\>]*\\}")))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool regexCheckForS(string strS)
{
    if(regex_match(strS, regex("^[s]\\s\\d+\\s\\d+$")))
    {
        return true;
    }
    else
    {
        return false;
    }
}
