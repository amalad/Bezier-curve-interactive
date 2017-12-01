# Compilation instructions
  1. cd into the "CG_Assignment_3" folder
  2. Execute the following commands from the command line: `$ g++ -std=c++11 bezier1.cpp BezierCurve.cpp Mesh.cpp Vertex3f.cpp -lGL -lGLU -lglut`
		
# Running instructions
  1. Run the a.out file
  2. To add control points on the window, left click on the desired location. To change the position of an existing control point, click on it and drag with the right mouse button. To delete a control point, click on it with the middle mouse button.
  3. Close the window once the curved has been created with the desired shape. The application will automatically create a surface of rotation and save the corresponding mesh in "mesh.off".

# Viewing the mesh:
  1. To view the mesh, run any mesh viewer with the "mesh.off" file. To run the file with Geomview, execute the following command: `$ geomview mesh.off`
