function [players, playerI] = getPossession( ball, ballX, ballY, homePlayers, awayPlayers )
    teams = ['home' 'away'];
    isHome = 0;
    isAway = 0;
    playerI = -1;
    players = 'none';
    playerHomeI = -1;
    playerAwayI = -1;
    for i = 1:6
       if (homePlayers(i).xPos <= ballX+1 && homePlayers(i).xPos >= ballX-1 ...
               && homePlayers(i).yPos <= ballY+1 && homePlayers(i).yPos >= ballY-1)
           playerHomeI = i;
           players = 'home';
           isHome = 1;
           break;
       end
    end
    for j = 1:6
       if (awayPlayers(i).xPos <= ballX+1 && awayPlayers(i).xPos >= ballX-1 ...
               && awayPlayers(i).yPos <= ballY+1 && awayPlayers(i).yPos >= ballY-1)
           playerAwayI = i;
           players = 'away';
           isAway = 1;
           break;
       end
    end
    
    if (isHome == 1 && isAway == 1)
        r = randi([1, 2]);
        if (r == 1)
            players = 'home';
        else
            players = 'away';
        end
       if (players == 'home')
           playerI = playerHomeI;
       else
           playerI = playerAwayI;
       end
    elseif (isHome == 1)
           playerI = playerHomeI;
    else
           playerI = playerAwayI;
    end
        
        
    


end

