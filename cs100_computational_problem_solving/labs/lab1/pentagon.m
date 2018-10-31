theta = 0:360/5:360;
x = cosd(theta);
% y = sind(theta);
y = (90*cosd(45)).*(90*sind(sind(theta)));
fill(x,y, 'r');
