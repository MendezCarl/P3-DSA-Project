//
// Created by Carlos Mendez on 12/1/25.
//

#include "Edge.h"

Edge::Edge(int from, int to, int time) {
    From = from;
    To = to;
    Time = time;
}

int Edge::getFrom() {
    return From;
}

int Edge::getTo() {
    return To;
}

int Edge::getTime() {
    return Time;
}

void Edge::closeEdge() {
    Open = false;
}

void Edge::openEdge() {
    Open = true;
}

bool Edge::isEdgeOpen() {
    return Open;
}

