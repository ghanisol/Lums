function setReferee( referee, newX, newY )
    % Position %
    referee.xPos = newX;
    referee.yPos = newY;
    % Position %

    % face %
    r = 0.25;
    [X,Y,Z] = sphere(100);
    set(referee.face, 'XData', X * r + newX, 'YData', Y * r + newY, 'ZData', Z * r + 3);
    % face %
    
    % body %
    xLine = [newX newX];
    yLine = [newY newY];
    set(referee.body, 'XData', xLine, 'YData', yLine);
    % body %
    
    % Legs %
    xLine = [newX newX+0.5];
    yLine = [newY newY];
    set(referee.leg1, 'XData', xLine, 'YData', yLine);
    
    xLine = [newX newX-0.5];
    yLine = [newY newY];
    set(referee.leg2, 'XData', xLine, 'YData', yLine);
    % Legs %
    
    % Arms %
    xLine = [newX newX+0.5];
    yLine = [newY newY];
    set(referee.arm1, 'XData', xLine, 'YData', yLine);
    
    xLine = [newX newX-0.5];
    yLine = [newY newY];
    set(referee.arm2, 'XData', xLine, 'YData', yLine);
    % Arms %

end

