close all;
figure;
axis equal;
hold on;
title('ProjectilePractice');

%% Generating the landscape
ball_radius = 2;
background = rectangle('Position',[0, 0, 100, 100],'FaceColor', [0 0 160/255]);
axis([0 100 0 100]);
moon = rectangle('Position',[55, 75, 10, 10],'FaceColor', [0.9 0.9 1], 'Curvature', [1 1]);
ball = rectangle('Position',[0, 0, ball_radius, ball_radius],'FaceColor', 'r', 'Curvature', [1 1]);


%% Generating the target
for a = 1:10
    ym = randi([50 80]);
    xm = randi([0 100]);
    x_ship = [xm xm+5 xm xm-5];
    y_ship = [ym-2.5 ym ym+2.5 ym];
    ship = fill(x_ship, y_ship, [0.9 0.9 1]);
end

%% Getting input angle from player
[x_input, y_input] = ginput(1);
vector_length = sqrt((x_input ^ 2) + (y_input ^ 2));
x_input = x_input / vector_length;
y_input = y_input / vector_length;
%% Computing the path of the projectile and the ship
for i = 0:100
    
    %% ship movement
    x_ship = [i i+5 i i-5];
    set(ship, 'XData', x_ship, 'YData', y_ship);
    
    %% projectile movement
    x_projectile = x_input * i/2;
    y_projectile = (y_input*i/2) + (0.5 * 10 * (i/2 ^ 2));
    set(ball, 'Position', [x_projectile, y_projectile ball_radius ball_radius]);
    pause(0.1);
end