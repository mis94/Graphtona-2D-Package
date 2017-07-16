# Graphtona 2D Package
A 2D graphics package that draws using <a href="https://en.wikipedia.org/wiki/Windows_API">Windows API</a> with self-implemented drawing algorithms for various graphical shapes in C++.

This package enables users to:

-Draw straight lines
	-Using Simple DDA algorithm
	-Using Parametric line equations
	-Using Bresenham midpoint algorithm
-Draw circles
	-Using direct Cartesian method
	-Using direct Polar method
	-Using iterative polar method
	-Using Bresenham midpoint algorithm
-Draw ellipses
	-Using Bresenham midpoint algorithm
-Draw curves of different degrees
	-First degree (straight line)
	-Second degree
	-Hermite curves (third degree)
	-Bezier curves (a special case of Hermite curves)
	-Cardinal splines
-Filling algorthims
	-Convex shapes filling using scanline filling algorthim
	-Circle filling in a simpler way than scanline filling
-Clipping algorithms
	-Clipping a point according to a rectangle & circle
	-Clipping a straight line according to a rectangle & circle


![alt tag](https://raw.githubusercontent.com/mis94/Graphtona-2D-Package/master/Screenshot.jpg)
