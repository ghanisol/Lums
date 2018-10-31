x = 1:10;
y = x.^2;
l = line(x, y, 'LineWidth', 4, 'Color', 'b');
set(l, 'Color', [1 0 0]);
