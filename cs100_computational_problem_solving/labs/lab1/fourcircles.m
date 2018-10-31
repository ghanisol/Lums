% Radius = 5, Color = Green
theta = 0:360;
r = 5;
x = r*cosd(theta);
y = r*sind(theta);
fill(x,y, 'g');
axis equal
hold on

% Radius = 4, Color = Red
r = 4;
x = r*cosd(theta);
y = r*sind(theta);
fill(x, y, 'r');

% Radius = 3, Color = Cyan
r = 3;
x = r*cosd(theta);
y = r*sind(theta);
fill(x, y, 'c');

% Radius = 2, Color = Megenta
r = 2;
x = r*cosd(theta);
y = r*sind(theta);
fill(x, y, 'm');