figure
hold on;
axis on;
axis equal;
grid on;
axis([-20 120 20 120]);
rectangle('Position', [20 40 60 60], 'Curvature', [1, 1], 'FaceColor', [1 0 1]);
rectangle('Position', [0 60 20 20], 'Curvature', [1, 1], 'FaceColor', 'g');
rectangle('Position', [80 60 20 20], 'Curvature', [1, 1], 'FaceColor', 'g');
rectangle('Position', [40 20 20 20], 'Curvature', [0.5, 0.5], 'FaceColor', 'b');
rectangle('Position', [40 100 20 20], 'Curvature', [0.5, 0.5], 'FaceColor', 'b');
rectangle('Position', [45 65 10 10], 'Curvature', [0.5, 0.5], 'FaceColor', 'y');
