awayPlayerPosX = [60 40 40 5 5 15];
awayPlayerPosY = [0 20 -20 20 -20 0];

for i = 1:6
    % Position %
        awayPlayers(i).xPos = awayPlayerPosX(i);
        awayPlayers(i).yPos = awayPlayerPosY(i);
    % Position %
    
    % Possession %
        awayPlayers(i).poss = 0;
    % Possession %
    
    % Face %
    r = 0.25;
    [X,Y,Z] = sphere(100);
    awayPlayers(i).face = surf(X * r + awayPlayerPosX(i), Y * r + awayPlayerPosY(i), Z * r + 3);
    % Face %

    % Body %
    xLine = [awayPlayerPosX(i) awayPlayerPosX(i)];
    yLine = [awayPlayerPosY(i) awayPlayerPosY(i)];
    zLine = [1 3]; 
    awayPlayers(i).body = line(xLine, yLine, zLine , 'color', 'b', 'linewidth', 2);
    % Body %

    % Legs %
    xLine = [awayPlayerPosX(i) awayPlayerPosX(i)];
    yLine = [awayPlayerPosY(i) awayPlayerPosY(i)+0.5];
    zLine = [1 0]; 
    awayPlayers(i).leg1 = line(xLine, yLine, zLine , 'color', [0, 0, 0], 'linewidth', 2);

    xLine = [awayPlayerPosX(i) awayPlayerPosX(i)];
    yLine = [awayPlayerPosY(i) awayPlayerPosY(i)-0.5];
    zLine = [1 0]; 
    awayPlayers(i).leg2 = line(xLine, yLine, zLine , 'color', [0, 0, 0], 'linewidth', 2);
    % Legs %

    % Arms %
    xLine = [awayPlayerPosX(i) awayPlayerPosX(i)];
    yLine = [awayPlayerPosY(i) awayPlayerPosY(i)+0.5];
    zLine = [2.5 1.5]; 
    awayPlayers(i).arm1 = line(xLine, yLine, zLine , 'color', [0, 0, 0], 'linewidth', 2);

    xLine = [awayPlayerPosX(i) awayPlayerPosX(i)];
    yLine = [awayPlayerPosY(i) awayPlayerPosY(i)-0.5];
    zLine = [2.5 1.5]; 
    awayPlayers(i).arm2 = line(xLine, yLine, zLine , 'color', [0, 0, 0], 'linewidth', 2);
    % Arms %
end