/* 
 * File:   Vertex3f.h
 * Author: amalad
 *
 * Created on November 24, 2017, 4:55 AM
 */

#ifndef VERTEX3F_H
#define VERTEX3F_H

class Vertex3f{
public:
    double x;
    double y;
    double z;
    
    /**
     * Class constructor
     * @param x X coordinate of vertex
     * @param y Y coordinate of vertex
     * @param z Z coordinate of vertex
     */
    Vertex3f(double x, double y, double z);
    
    /**
     * Fetches X coordinate of vertex
     * @return X coordinate
     */
    double getX();
    
    /**
     * Fetches Y coordinate of vertex
     * @return Y coordinate
     */
    double getY();
    
    /**
     * Fetches Z coordinate of vertex
     * @return Z coordinate
     */
    double getZ();
};

#endif /* VERTEX3F_H */

