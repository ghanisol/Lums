
% Position %
    referee.xPos = 0;
    referee.yPos = 41;
% Position %

% Face %
    r = 0.25;
    [X,Y,Z] = sphere(100);
    referee.face = surf(X * r + referee.xPos, Y * r + referee.yPos, Z * r + 3);
% Face %

% Body %
    xLine = [referee.xPos referee.xPos];
    yLine = [referee.yPos referee.yPos];
    zLine = [1 3]; 
    referee.body = line(xLine, yLine, zLine , 'color', 'y', 'linewidth', 2);
% Body %

% Legs %
    xLine = [referee.xPos referee.xPos+0.5];
    yLine = [referee.yPos referee.yPos];
    zLine = [1 0]; 
    referee.leg1 = line(xLine, yLine, zLine , 'color', [0, 0, 0], 'linewidth', 2);

    xLine = [referee.xPos referee.xPos-0.5];
    yLine = [referee.yPos referee.yPos];
    zLine = [1 0]; 
    referee.leg2 = line(xLine, yLine, zLine , 'color', [0, 0, 0], 'linewidth', 2);
% Legs %

% Arms %
    xLine = [referee.xPos referee.xPos+0.5];
    yLine = [referee.yPos referee.yPos];
    zLine = [2.5 1.5]; 
    referee.arm1 = line(xLine, yLine, zLine , 'color', 'y', 'linewidth', 2);

    xLine = [referee.xPos referee.xPos-0.5];
    yLine = [referee.yPos referee.yPos];
    zLine = [2.5 1.5]; 
    referee.arm2 = line(xLine, yLine, zLine , 'color', 'y', 'linewidth', 2);
% Arms %

