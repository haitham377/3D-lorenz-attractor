# How to compile on linux (tested on ubuntu)

Typing ``g++ lorenz-attractor.cpp lib/libraylib.a -o [executable name]`` creates an executable with your chosen name in the current directory.

Changing the macro label ``STEP`` in the cpp code gives you the option to either use the runge-kutta method ``rk(x)`` or euler's
method ``euler(x)`` (where x is a 3-dimensional position vector) to get the next step in the simulation. 

