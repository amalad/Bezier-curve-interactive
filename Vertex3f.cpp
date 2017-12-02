#include "Vertex3f.h"

Vertex3f::Vertex3f(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

double Vertex3f::getX(){
    return this->x;
}

double Vertex3f::getY(){
    return this->y;
}

double Vertex3f::getZ(){
    return this->z;
}