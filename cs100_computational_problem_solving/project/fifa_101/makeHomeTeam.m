homePlayerPosX = [-60 -40 -40 -5 -5 -15];
homePlayerPosY = [0 20 -20 20 -20 0];

for i = 1:6
    
    % Position %
        homePlayers(i).xPos = homePlayerPosX(i);
        homePlayers(i).yPos = homePlayerPosY(i);
    % Position %
    
    % Possession %
        homePlayers(i).poss = 0;
    % Possession %
    
    % Face %
    r = 0.25;
    [X,Y,Z] = sphere(100);
    homePlayers(i).face = surf(X * r + homePlayerPosX(i), Y * r + homePlayerPosY(i), Z * r + 3);
    % Face %

    % Body %
    xLine = [homePlayerPosX(i) homePlayerPosX(i)];
    yLine = [homePlayerPosY(i) homePlayerPosY(i)];
    zLine = [1 3]; 
    homePlayers(i).body = line(xLine, yLine, zLine , 'color', 'r', 'linewidth', 2);
    % Body %

    % Legs %
    xLine = [homePlayerPosX(i) homePlayerPosX(i)];
    yLine = [homePlayerPosY(i) homePlayerPosY(i)+0.5];
    zLine = [1 0]; 
    homePlayers(i).leg1 = line(xLine, yLine, zLine , 'color', [0, 0, 0], 'linewidth', 2);

    xLine = [homePlayerPosX(i) homePlayerPosX(i)];
    yLine = [homePlayerPosY(i) homePlayerPosY(i)-0.5];
    zLine = [1 0]; 
    homePlayers(i).leg2 = line(xLine, yLine, zLine , 'color', [0, 0, 0], 'linewidth', 2);
    % Legs %

    % Arms %
    xLine = [homePlayerPosX(i) homePlayerPosX(i)];
    yLine = [homePlayerPosY(i) homePlayerPosY(i)+0.5];
    zLine = [2.5 1.5]; 
    homePlayers(i).arm1 = line(xLine, yLine, zLine , 'color', [0, 0, 0], 'linewidth', 2);

    xLine = [homePlayerPosX(i) homePlayerPosX(i)];
    yLine = [homePlayerPosY(i) homePlayerPosY(i)-0.5];
    zLine = [2.5 1.5]; 
    homePlayers(i).arm2 = line(xLine, yLine, zLine , 'color', [0, 0, 0], 'linewidth', 2);
    % Arms %
end