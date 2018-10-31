close all;
figure;
axis equal;
x = 50;
y = 50;
l = 10;
h = 5;
rectangle('Position', [x, y, l, h], 'FaceColor', rand(1, 3));

for i = 1:53
    x = x + (rand*10 - 5);
    y = y + 5;
    rectangle('Position', [x, y, l, h], 'FaceColor', rand(1, 3));
end
