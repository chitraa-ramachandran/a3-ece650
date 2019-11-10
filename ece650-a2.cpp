#include <iostream>
#include "syntaxChecker.cpp"
#include "parserAndConverter.cpp"
#include "shortestPathAlgo.cpp"
using namespace std;

int main()
{
    //cout<<"\n";
    bool checkForVE = false;
    int V = 0;
    vector<int> edgesVector;
    while(true)
    {
        string strVertices;
        getline(cin,strVertices);
	cout<<strVertices<<endl;
        if(!cin || strVertices == "")
        {
            if(cin.eof())
            {
                break;
            }
            else
            {
                break;
            }

        }
        else
        {
            if(strVertices[0] == 'V')
            {
                bool checkSyntaxForV = regexCheckForV(strVertices);
                if(checkSyntaxForV)
                {
                    V = parseStringV(strVertices);
                    string strEdges;
                    getline(cin, strEdges);
		    cout<<strEdges<<endl;
                    if(!cin || strEdges == "")
                    {
                        if(cin.eof())
                        {
                            break;
                        }
                        else
                        {
                            break;
                        }

                    }
                    else
                    {
                        if(strEdges[0] == 'E')
                        {
                            bool checkSyntaxForE = regexCheckForE(strEdges);
                            if(checkSyntaxForE)
                            {
                                edgesVector = parseStringE(strEdges);
                                bool rangeCheckE = checkForEInRangeOfV(edgesVector, V);
                                if(rangeCheckE)
                                {
                                    checkForVE = true;
                                }
                                else
                                {
                                    cout<<"Error: E is out of range"<<endl;
                                    checkForVE = false;
                                }

                            }
                            else
                            {
                                cout<<"Error: Syntax Error in E"<<endl;
                                checkForVE = false;
                            }

                        }
                        else
                        {
                            cout<<"Error: Bad Input"<<endl;
                            checkForVE = false;
                        }
                    }
                }
                else
                {
                    cout<<"Error: Syntax Error in V"<<endl;
                    checkForVE = false;
                }

            }
            else if(strVertices[0] == 's' && checkForVE == true)
            {
                bool checkSyntaxForS = regexCheckForS(strVertices);
                if(checkSyntaxForS)
                {
                    vector<int> srcDestVector;
                    srcDestVector = parseStringS(strVertices);
                    bool rangeCheckS = checkForEInRangeOfV(srcDestVector, V);
                    if(rangeCheckS)
                    {
                        vector<int> adjMatrix[V];
                        for(unsigned i = 0; i < edgesVector.size(); i = i +2)
                        {
                            adjMatrix[edgesVector[i]].push_back(edgesVector[i+1]);
                            adjMatrix[edgesVector[i+1]].push_back(edgesVector[i]);
                        }
                        int src = srcDestVector[0];
                        int dest = srcDestVector[1];

                        printPath(adjMatrix, src, dest, V);
                    }
                    else
                    {
                        cout<<"Error: s is out of range"<<endl;
                    }
                }
                else
                {
                    cout<<"Error: syntax Error in s"<<endl;
                }

            }
            else
            {
                cout<<"Error: Bad Input"<<endl;
                checkForVE = false;
            }


        }
    }
    return 0;
}



