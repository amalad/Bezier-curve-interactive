#include "BezierCurve.h"
#include <queue>
#include <iostream>

Vertex3f lerp(Vertex3f vertex_a, Vertex3f vertex_b, double t){
    return Vertex3f(vertex_a.getX()+(vertex_b.getX()-vertex_a.getX())*t, vertex_a.getY()+(vertex_b.getY()-vertex_a.getY())*t, vertex_a.getZ()+(vertex_b.getZ()-vertex_a.getZ())*t);
}

BezierCurve::BezierCurve(double sample_rate){
    this->sample_rate = sample_rate;
}

void BezierCurve::addControlPoint(double x, double y, double z){
    this->controlPoints.push_back(Vertex3f(x,y,z));
    if(this->controlPoints.size()==1){
        for(double i=0; i<=1.0; i+=this->sample_rate){
            this->curvePoints.push_back(this->controlPoints[0]);
        }
        return;
    }
    int j=0;
    for(double i=0; i<=1.0; i+=this->sample_rate, j++){
        this->curvePoints[j] = lerp(this->curvePoints[j], this->generatePoint(i, 1, this->controlPoints.size()-1), i);
    }
}

void BezierCurve::deleteControlPoint(int index){
    if(index>=this->controlPoints.size()){
        std::cout << "Invalid index" << std::endl;
        return;
    }
    this->curvePoints.clear();
    this->controlPoints.erase(this->controlPoints.begin()+index);
    for(double i=0; i<=1.0; i+=this->sample_rate){
        this->curvePoints.push_back(this->generatePoint(i, 0, this->controlPoints.size()-1));
    }
}

void BezierCurve::changeControlPoint(int index, double x, double y, double z){
    if(index>=this->controlPoints.size()){
        std::cout << "Invalid index" << std::endl;
        return;
    }
    this->curvePoints.clear();
    this->controlPoints[index] = Vertex3f(x,y,z);
    for(double i=0; i<=1.0; i+=this->sample_rate){
        this->curvePoints.push_back(this->generatePoint(i, 0, this->controlPoints.size()-1));
    }
}

void BezierCurve::changeSampleRate(double delta){
    this->sample_rate += delta;
    this->curvePoints.clear();
    if(this->sample_rate>1)
        this->sample_rate = 1.0;
    else if(this->sample_rate<0)
        this->sample_rate = 0.0;
    for(double i=0; i<=1.0; i+=this->sample_rate){
        this->curvePoints.push_back(this->generatePoint(i, 0, this->controlPoints.size()-1));
    }
}

Vertex3f BezierCurve::generatePoint(double t, int s_index, int e_index){
    if(e_index==s_index)
        return this->controlPoints[s_index];
    std::vector < Vertex3f > vec;
    for(int i=s_index; i<=e_index; i++){
        vec.push_back(this->controlPoints[i]);
    }
    for(int i=0; i<(e_index-s_index); i++){
        for(int j=0; j<vec.size()-1; j++){
            vec[j] = lerp(vec[j], vec[j+1], t);
        }
        vec.erase(vec.begin()+(vec.size()-1));
    }
    return vec[0];
}

std::vector < Vertex3f > BezierCurve::getCurve(){
    return this->curvePoints;
}
