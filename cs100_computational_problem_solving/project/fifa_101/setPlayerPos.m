function  setPlayerPos( player, newX, newY )
    
    % Position %
    player.xPos = newX;
    player.yPos = newY;
    % Position %

    % face %
    r = 0.25;
    [X,Y,Z] = sphere(100);
    set(player.face, 'XData', X * r + newX, 'YData', Y * r + newY, 'ZData', Z * r + 3);
    % face %
    
    % body %
    xLine = [newX newX];
    yLine = [newY newY];
    set(player.body, 'XData', xLine, 'YData', yLine);
    % body %
    
    % Legs %
    xLine = [newX newX];
    yLine = [newY newY+0.5];
    set(player.leg1, 'XData', xLine, 'YData', yLine);
    
    xLine = [newX newX];
    yLine = [newY newY-0.5];
    set(player.leg2, 'XData', xLine, 'YData', yLine);
    % Legs %
    
    % Arms %
    xLine = [newX newX];
    yLine = [newY newY+0.5];
    set(player.arm1, 'XData', xLine, 'YData', yLine);
    
    xLine = [newX newX];
    yLine = [newY newY-0.5];
    set(player.arm2, 'XData', xLine, 'YData', yLine);
    % Arms %
end

