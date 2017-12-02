/* 
 * File:   BezierCurve.h
 * Author: amalad
 *
 * Created on November 22, 2017, 12:07 AM
 */

#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <vector>
#include "Vertex3f.h"


/**
 * Generates and manipulates a bezier curve
 */
class BezierCurve{
public:
    std::vector < Vertex3f > controlPoints;
    std::vector < Vertex3f > curvePoints;
    double sample_rate;
    
    /**
     * Class Constructor
     * @param sample_rate Sample rate for generating points on the curve
     */
    BezierCurve(double sample_rate);
    
    /**
     * Adds a control point and regenerates the curve
     * @param x X coordinate of new control point
     * @param y Y coordinate of new control point
     * @param z Z coordinate of new control point
     */
    void addControlPoint(double x, double y, double z);
    
    /**
     * Deletes a control point and regenerates the curve
     * @param index Index of the control point to be deleted
     */
    void deleteControlPoint(int index);
    
    /**
     * Changes the position of the control point and regenerates the curve
     * @param index Index of control point
     * @param x New x coordinate of control point
     * @param y New y coordinate of control point
     * @param z New z coordinate of control point
     */
    void changeControlPoint(int index, double x, double y, double z);
    
    /**
     * Changes the sampling rate and regenerates the curve
     * @param delta Change in the sampling rate
     */
    void changeSampleRate(double delta);
    
    /**
     * Generates point t on the curve using De Casteljau's algorithm
     * @param t Parameter value of the point
     * @param s_index Index of first control point
     * @param e_index Index of last control point
     * @return Point t on the curve 
     */
    Vertex3f generatePoint(double t, int s_index, int e_index);
    
    /**
     * Returns the curve
     * @return Curve points in their increasing order
     */
    std::vector < Vertex3f > getCurve();
    
};

#endif /* BEZIERCURVE_H */

