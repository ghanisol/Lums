v = 100 * 1000/3600;
xdot = v * cosd(45);
ydot = v * sind(45);
ydotdot = -9.8;
t1 = -ydot / ydotdot;
disp(2 * t1 * xdot);