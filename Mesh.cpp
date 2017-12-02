#include "Mesh.h"

void Mesh::addVertex(Vertex3f vertex){
    this->vertices.push_back(vertex);
}

void Mesh::addFace(std::vector<int> vertices){
    this->faces.push_back(vertices);
}

void Mesh::setEdgeCount(int no_edges){
    this->no_edges = no_edges;
}