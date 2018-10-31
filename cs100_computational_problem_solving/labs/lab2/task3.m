close all;
figure;
axis equal
axis([0 120 0 120]);
for i = 1:40
    cor = 100 * rand(1,2);
    dia = 10 + 10 * rand;
    rectangle('Position', [cor, dia, dia], 'curvature', [1 1], 'FaceColor', rand(1, 3));
end

