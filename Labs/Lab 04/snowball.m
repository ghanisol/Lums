figure;
axis equal;
axis([0 100 0 100]);
hold on;

c1_xCor = randi([40, 60]);
c1_yCor = randi([40, 60]);
c1_d = randi([20 30]);
c1_color = rand(1, 3);
c1_x = randi([-10 10]);
c1_y = randi([-10 10]);
c1 = rectangle('Position', [c1_xCor c1_yCor c1_d c1_d], 'FaceColor', c1_color, 'Curvature', [1 1]);  

c2_xCor = randi([40, 60]);
c2_yCor = randi([40, 60]);
c2_d = randi([20, 30]);
c2_color = rand(1, 3);
c2_x = randi([-10 10]);
c2_y = randi([-10 10]);
c2 = rectangle('Position', [c2_xCor c2_yCor c2_d c2_d], 'FaceColor', c2_color, 'Curvature', [1 1]);  

for i = 1:1000
    if c1_xCor >= 100 - c1_d
        c1_x = -c1_x;
    elseif c1_xCor <= 0
        c1_x = -c1_x;
    end
    
    if c1_yCor >= 100 - c1_d
        c1_y = -c1_y;
    elseif c1_yCor <= 0
        c1_y = -c1_y;
    end
    
    if c2_xCor >= 100 - c2_d
        c2_x = -c2_x;
    elseif c2_xCor <= 0
        c2_x = -c2_x;
    end
    
    if c2_yCor >= 100 - c2_d
        c2_y = -c2_y;
    elseif c2_yCor <= 0
        c2_y = -c2_y;
    end
    
    if c1_d < 2 || c2_d <2
       break; 
    end
    c1_d = c1_d - 1;
    c1_xCor = c1_xCor + c1_x;
    c1_yCor = c1_yCor + c1_y;
    c1_color = rand(1, 3);
    set(c1, 'Position', [c1_xCor c1_yCor c1_d c1_d], 'FaceColor', c1_color); 
    
    c2_xCor = c2_xCor + c2_x;
    c2_yCor = c2_yCor + c2_y;
    c2_color = rand(1, 3);
    c2_d = c2_d - 1;
    set(c2, 'Position', [c2_xCor c2_yCor c2_d c2_d], 'FaceColor', c2_color);
    pause(0.1);
end