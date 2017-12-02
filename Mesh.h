/* 
 * File:   Mesh.h
 * Author: amalad
 *
 * Created on November 23, 2017, 10:05 PM
 */

#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex3f.h"

class Mesh{
public:
    std::vector< Vertex3f > vertices;
    std::vector< std::vector<int> > faces;
    int no_edges;
    
    /**
     * Adds a vertex to the mesh
     * @param vertex Vertex to be added
     */
    void addVertex(Vertex3f vertex);
    
    /**
     * Adds a face to the mesh
     * @param vertices Vector of vertex indices
     */
    void addFace(std::vector <int> vertices);
    
    /**
     * Sets the edge count
     * @param no_edges Number of edges
     */
    void setEdgeCount(int no_edges);
};

#endif /* MESH_H */

