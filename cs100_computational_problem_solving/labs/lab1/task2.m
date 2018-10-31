v = 100 * 1000/3600;
theta = 0:0.1:90;
xdot = v * cosd(theta);
ydot = v * sind(theta);
ydotdot = -9.8;
t1 = -ydot / ydotdot;
2 * t1 .* xdot;
plot(theta, ans);