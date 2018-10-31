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
    
    % face %
    r = 0.25;
    [X,Y,Z] = sphere(100);
    set(homePlayers(i).face, 'XData', X * r + homePlayerPosX(i), 'YData', Y * r + homePlayerPosY(i), 'ZData', Z * r + 3);
    % face %
    
    % body %
    xLine = [homePlayerPosX(i) homePlayerPosX(i)];
    yLine = [homePlayerPosY(i) homePlayerPosY(i)];
    set(homePlayers(i).body, 'XData', xLine, 'YData', yLine);
    % body %
    
    % Legs %
    xLine = [homePlayerPosX(i) homePlayerPosX(i)];
    yLine = [homePlayerPosY(i) homePlayerPosY(i)+0.5];
    set(homePlayers(i).leg1, 'XData', xLine, 'YData', yLine);
    
    xLine = [homePlayerPosX(i) homePlayerPosX(i)];
    yLine = [homePlayerPosY(i) homePlayerPosY(i)-0.5];
    set(homePlayers(i).leg2, 'XData', xLine, 'YData', yLine);
    % Legs %
    
    % Arms %
    xLine = [homePlayerPosX(i) homePlayerPosX(i)];
    yLine = [homePlayerPosY(i) homePlayerPosY(i)+0.5];
    set(homePlayers(i).arm1, 'XData', xLine, 'YData', yLine);
    
    xLine = [homePlayerPosX(i) homePlayerPosX(i)];
    yLine = [homePlayerPosY(i) homePlayerPosY(i)-0.5];
    set(homePlayers(i).arm2, 'XData', xLine, 'YData', yLine);
    % Arms %
    
end