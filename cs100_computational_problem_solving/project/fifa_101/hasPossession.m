function [players ,playerI] = hasPossession( homePlayers, awayPlayers)
    playerI = -1;
    players = 'none';
    for i = 1:6
       if (homePlayers(i).hasPoss == 1)
           playerI = i;
           players = 'home';
       end
       if (awayPlayers(i).hasPoss == 1)
           playerI = i;
           players = 'away';
       end
    end
    


end

