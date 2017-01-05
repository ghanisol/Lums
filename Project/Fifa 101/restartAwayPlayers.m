awayPlayerPosX = [60 40 40 5 5 15];
awayPlayerPosY = [0 20 -20 20 -20 0];

for i = 1:6
    % Position %
    awayPlayers(i).xPos = awayPlayerPosX(i);
    awayPlayers(i).yPos = awayPlayerPosY(i);
    % Position %

    % face %
    r = 0.25;
    [X,Y,Z] = sphere(100);
    set(awayPlayers(i).face, 'XData', X * r + awayPlayerPosX(i), 'YData', Y * r + awayPlayerPosY(i), 'ZData', Z * r + 3);
    % face %
    
    % body %
    xLine = [awayPlayerPosX(i) awayPlayerPosX(i)];
    yLine = [awayPlayerPosY(i) awayPlayerPosY(i)];
    set(awayPlayers(i).body, 'XData', xLine, 'YData', yLine);
    % body %
    
    % Legs %
    xLine = [awayPlayerPosX(i) awayPlayerPosX(i)];
    yLine = [awayPlayerPosY(i) awayPlayerPosY(i)+0.5];
    set(awayPlayers(i).leg1, 'XData', xLine, 'YData', yLine);
    
    xLine = [awayPlayerPosX(i) awayPlayerPosX(i)];
    yLine = [awayPlayerPosY(i) awayPlayerPosY(i)-0.5];
    set(awayPlayers(i).leg2, 'XData', xLine, 'YData', yLine);
    % Legs %
    
    % Arms %
    xLine = [awayPlayerPosX(i) awayPlayerPosX(i)];
    yLine = [awayPlayerPosY(i) awayPlayerPosY(i)+0.5];
    set(awayPlayers(i).arm1, 'XData', xLine, 'YData', yLine);
    
    xLine = [awayPlayerPosX(i) awayPlayerPosX(i)];
    yLine = [awayPlayerPosY(i) awayPlayerPosY(i)-0.5];
    set(awayPlayers(i).arm2, 'XData', xLine, 'YData', yLine);
    % Arms %
    
end