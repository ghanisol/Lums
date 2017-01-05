figure
hold on;
axis equal;
axis([-100 100 -100 100]);
h = rectangle('Position', [-50 -50 100 100], 'facecolor','g', 'curvature', [1 1]);
x_line = [0 50];
y_line = 0;
l = line(x_line, y_line, 'LineWidth', 2, 'Color', 'b');
for i = 360:-6:0
 xCor = [0 50*cosd(i)];
 yCor = [0 50*sind(i)];

 set(l, 'XData', xCor, 'YData', yCor);
 pause(1);
end;