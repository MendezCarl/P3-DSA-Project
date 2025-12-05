//
// Created by Carlos Mendez on 12/1/25.
//

#ifndef EDGE_H
#define EDGE_H
#include <utility>

class Edge {
    int From;
    int To;
    int Time;

    bool Open = true; //default to true

public:
    Edge(int from, int to, int time);
    // void createEdge(int from, int to, std::pair<int, int> time);

    int getFrom();
    int getTo();
    int getTime();

    void closeEdge();
    void openEdge();
    bool isEdgeOpen();
};

#endif //EDGE_H

