function playerI = playerDetectPass( ball, players, ballPlayerI )
    
    minX = 140;
    minY = 80;
    minI = 1;
    for i = 2:6
        if (abs(players(ballPlayerI).xPos - players(i).xPos) < minX ...
                && abs(players(ballPlayerI).yPos - players(i).yPos < minY)...
                && i ~= ballPlayerI)
            minI = i;
        end
    end
    
    playerI = players(minI);


end

