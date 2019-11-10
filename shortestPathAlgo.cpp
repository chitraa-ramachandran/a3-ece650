//
// Created by Jimisha Thakkar on 18/10/19.
//
#include <iostream>
#include <regex>
#include<sstream>
#include<queue>
using namespace std;

bool BFS(vector<int> adjMatrix[], int src, int dest, int pred[], int dist[], int V)
{
    int visited[V];
    for(int i = 0; i < V; i++)
    {
        pred[i] = -1;
        dist[i] = 0;
        visited[i] = false;
    }
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    pred[src] = -1;
    visited[src] = true;

    while(!q.empty())
    {
        int val = q.front();
        q.pop();
        for(unsigned i = 0; i < adjMatrix[val].size(); i++)
        {
            if(visited[adjMatrix[val][i]] == false)
            {
                visited[adjMatrix[val][i]] = true;
                pred[adjMatrix[val][i]] = val;
                dist[adjMatrix[val][i]] = dist[val] + 1;
                q.push(adjMatrix[val][i]);

                if(adjMatrix[val][i] == dest)
                    return true;
            }
        }
    }
    return false;
}

void printPath(vector<int> adjMatrix[], int src, int dest, int V)
{
    int pred[V], dist[V];
    if(BFS(adjMatrix, src, dest, pred, dist, V) == false)
    {
        cout<<"Error: no path exists"<<endl;
        return;
    }
    vector<int> tempVector;
    int tempInt = dest;
    while(tempInt != -1)
    {
        tempVector.push_back(tempInt);
        tempInt = pred[tempInt];
    }
    while(tempVector.size() != 0)
    {
        if(tempVector.size() == 1)
            cout<<tempVector.back();
        else
            cout<<tempVector.back()<<"-";
        tempVector.pop_back();
    }
    cout<<endl;
}