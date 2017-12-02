/* 
 * File:   main.cpp
 * Author: amalad
 *
 * Created on November 22, 2017, 12:07 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "BezierCurve.h"
#include "Mesh.h"
#include "Vertex3f.h"

#define _USE_MATH_DEFINES
#define SQ_DIST 50
#define ROTATE_ANGLE 10

using namespace std;
BezierCurve *curve_ptr;
int WIDTH = 600;
int HEIGHT = 600;
double sample_rate = 0.1;
int move_flag, move_index;

/**
 * Saves a mesh in a file of .off format
 * @param mesh Mesh object
 * @param name Name of file
 */
void saveAsOFF(Mesh mesh, string name){
    ofstream f;
    f.open(name);
    f << "OFF\n";
    f << mesh.vertices.size() << " " << mesh.faces.size() << " " << mesh.no_edges << endl;
    for(Vertex3f vertex: mesh.vertices){
        f << vertex.getX() << " " << vertex.getY() << " " << vertex.getZ() << endl;
    }
    for(vector<int> face: mesh.faces){
        f << face.size();
        for(int index: face)
            f << " " << index;
        f << endl;
    }
    f.close();
}

/**
 * Rotates a point along the Y-axis by increments of delta degrees
 * @param point Point to be rotated
 * @param delta Value of angle increment
 * @return Vector of all the generated points
 */
vector< Vertex3f > rotatePoint(Vertex3f point, double delta){
    double angle = 0;
    vector< Vertex3f > points;
    while(angle<360){
        double len = point.getX();
        points.push_back(Vertex3f(len*cos(angle* M_PI / 180.0), point.getY(), -1*len*sin(angle* M_PI / 180.0)));
        angle+=delta;
    }
    return points;
}
/**
 * Trianguates a surface defined by 4 points
 * @param quad Indices of points in anticlockwise manner
 * @return Two groups of triangulated points
 */
vector< vector<int> > triangulate(vector<int> quad){
    vector < vector<int> > faces;
    vector <int> face1;
    face1.push_back(quad[0]);
    face1.push_back(quad[1]);
    face1.push_back(quad[2]);
    vector <int> face2;
    face2.push_back(quad[0]);
    face2.push_back(quad[2]);
    face2.push_back(quad[3]);
    faces.push_back(face1);
    faces.push_back(face2);
    return faces;
}

/**
 * Rotates a curve around the Y-axis
 * @param angle Angle of rotation
 * @return Mesh generated
 */
Mesh rotateCurve(double angle){
    Mesh mesh = Mesh();
    vector< vector< Vertex3f > > mpoints;
    for(auto cpoint: curve_ptr->curvePoints){
        auto points = rotatePoint(cpoint, angle);
        mpoints.push_back(points);
        for(Vertex3f point : points){
            mesh.addVertex(Vertex3f(point.getX(), point.getY(), point.getZ()));
        }
    }
    int no_vertices_ring = mpoints[0].size();
    mesh.setEdgeCount(no_vertices_ring*(curve_ptr->curvePoints.size()+2));
    for(int i=1; i<mpoints.size(); i++){
        int count = 0;
        for (int j=1; j<=no_vertices_ring; j++){
            vector <int> quad;
            int temp = j;
            if(j==no_vertices_ring)
                temp = 0;
            quad.push_back((i-1)*no_vertices_ring+(j-1));
            quad.push_back((i-1)*no_vertices_ring+temp);
            quad.push_back(i*no_vertices_ring+temp);
            quad.push_back(i*no_vertices_ring+(j-1));
            auto faces = triangulate(quad);
            mesh.addFace(faces[0]);
            mesh.addFace(faces[1]);
            count+=2;
        }
    }
    return mesh;
}

/**
 * Computes the quared Euclidian distance between two points
 * @param x1 X coordinate of point 1
 * @param y1 Y coordinate of point 1
 * @param x2 X coordinate of point 2
 * @param y2 Y coordinate of point 2
 * @return Squared Euclidian distance
 */
int sqEuclidianDist(int x1, int y1, int x2, int y2){
	return (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
}

/**
 * Returns the index of a point whose squared Euclidian distance from a point is less than SQ_DIST
 * @param x X coordinate
 * @param y Y coordinate
 * @return Index of closest point withing the range, -1 if no such index exists
 */
int getIndex(int x, int y){
	int min = SQ_DIST+1;
	int index = -1;
	int temp;
	for(int i=0; i<curve_ptr->controlPoints.size(); i++){
		temp = sqEuclidianDist(x,y,curve_ptr->controlPoints[i].getX(),curve_ptr->controlPoints[i].getY());
		if(temp<min){
			min = temp;
			index = i;
		}
	}
	return index;
}

/**
 * Callback function for mouse clicks
 * @param button Mouse button
 * @param state State of button
 * @param x X coordinate of point clicked
 * @param y Y coordinate of point clicked
 */
void mouseClick(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
    	curve_ptr->addControlPoint(x,HEIGHT-y,0);
	}
	else if(button == GLUT_RIGHT_BUTTON){
		if(state==GLUT_DOWN){
			move_index = getIndex(x, HEIGHT-y);
			if(move_index>=0)
				move_flag = 1;
		}
		else if(state==GLUT_UP){
			move_flag = 0;
			curve_ptr->changeControlPoint(move_index, x, HEIGHT-y, 0);
		}
	}
	else if(button == GLUT_MIDDLE_BUTTON && state==GLUT_DOWN){
		int delete_index = getIndex(x, HEIGHT-y);
		curve_ptr->deleteControlPoint(delete_index);
	}
    glutPostRedisplay();
}

/**
 * Callback function for mouse movements
 * @param x X coordinate of pointer location
 * @param y Y coordinate of pointer location
 */
void mouseMove(int x, int y){
	if(move_flag){
		curve_ptr->changeControlPoint(move_index, x, HEIGHT-y, 0);
		glutPostRedisplay();
	}
}
/**
 * Draws the Bezier curve
 */
void draw(){ 
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_LINE_STRIP);
        for(Vertex3f point: curve_ptr->controlPoints){
            glVertex2f(point.getX(), point.getY());
        }
    glEnd();
    glColor3f(0,1,0);
    glBegin(GL_LINE_STRIP);
        for(Vertex3f point: curve_ptr->curvePoints){
            glVertex2f(point.getX(), point.getY());
        }
    glEnd();
    glFlush();
}

/**
 * Main function
 */
int main(int argc, char** argv) {    
    
    BezierCurve curve = BezierCurve(sample_rate);
    curve_ptr = &curve;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("bezier1");
    glClearColor(0,0,0,0);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);
    glutDisplayFunc (draw);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
              GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutMainLoop();
    
    cout << "Rotating along Y axis..." << endl;
    Mesh mesh = rotateCurve(ROTATE_ANGLE);
    cout << "Rotated." << endl;
    cout << "Saving in OFF format..." << endl;
    saveAsOFF(mesh, "mesh.off");
    cout << "Saved" << endl;
    return 0;
}
