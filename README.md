# Graphtona 2D Package
A 2D graphics package that draws using <a href="https://en.wikipedia.org/wiki/Windows_API">Windows API</a> with self-implemented drawing algorithms for various graphical shapes in C++.

This package enables users to:

- Draw straight lines
	- Using <a href="https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)"> DDA algorithm </a>
	- Using <a href="https://en.wikipedia.org/wiki/Parametric_equation"> parametric line equations </a>
	- Using <a href="https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm"> Bresenham algorithm </a>
- Draw circles
	- Using <a href="https://en.wikipedia.org/wiki/Circle#Cartesian_coordinates"> direct Cartesian method </a>
	- Using <a href="https://en.wikipedia.org/wiki/Circle#Polar_coordinates"> direct polar method </a>
	- Using iterative polar method (similar to direct polar with a slight change to improve performance)
	- Using <a href="https://en.wikipedia.org/wiki/Midpoint_circle_algorithm"> Bresenham midpoint algorithm </a>
- Draw ellipses
	- Using <a href="https://en.wikipedia.org/wiki/Ellipse#Computer_graphics"> Bresenham algorithm </a>
- Draw curves of different degrees
	- <a href="https://en.wikipedia.org/wiki/List_of_curves#Degree_1"> First degree </a> (straight line)
	- <a href="https://en.wikipedia.org/wiki/List_of_curves#Degree_2"> Second degree </a>
	- <a href="https://en.wikipedia.org/wiki/Cubic_Hermite_spline"> Hermite curves </a> (third degree)
	- <a href="https://en.wikipedia.org/wiki/B%C3%A9zier_curve"> Bezier curves </a> (a special case of Hermite curves)
	- <a href="https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline"> Cardinal splines </a>
- Use Filling algorithms
	- Convex shapes filling using <a href="https://en.wikipedia.org/wiki/Flood_fill#Scanline_fill"> scanline filling algorithm </a>
	- Circle filling in a simple way
- Use <a href="https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm"> Cohen–Sutherland </a> Clipping algorithm
	- Clipping a point according to a rectangle & circle
	- Clipping a straight line according to a rectangle & circle


![alt tag](https://raw.githubusercontent.com/mis94/Graphtona-2D-Package/master/Screenshot.jpg)
