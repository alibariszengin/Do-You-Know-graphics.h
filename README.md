# The Smallest Circle

Drawing the solution of  finding the smallest circle that completely contains a set of random points (The Smallest Circle or Minimum Enclosing Circle Problem) and drawing the b-spline of these points.

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)




## General info
Project gets input from user to how many random points must create. After randomly creating coordinates of points, it calculates the smallest circle that contains the points. To do that, first caclulates the center coordinates of points. After, controls of possibilities for if 2 or 3 points are crossing with the border of circle or not. It's rare possibility to get 4 points on the border so, it's enough to control 2 or 3.

Draw the circle and a line from center point to circle border as circle radius on the coordinate system.

Finally, calculates and draw the b-spline of points.

Uses different color for every line or point type.
	
![Drawing](https://github.com/alibariszengin/Do-You-Know-graphics.h/blob/master/Do-You-Know-graphics.h/circle.png)
	
## Technologies-Tools
Project is created with:
* C/C++
* graphics.h library
* Dev-C++

	
## Setup
To run this project, run from the IDE or after change directory to project folder, run 'Son' on the terminal.

`$.\Do-You-Know-graphics.h\Son`

