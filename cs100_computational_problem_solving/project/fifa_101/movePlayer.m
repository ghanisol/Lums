function [newX, newY, moved] = movePlayer( player, key )

    X = player.xPos;
    Y = player.yPos;
     
    newX = X;
    newY = Y;
    moved = 0;
    
    if (double(key) == 28)
        setPlayerPos(player, X - 1, Y);
        newX = X - 1;
        moved = 1;
    elseif (double(key) == 29)
        setPlayerPos(player, X + 1, Y);
        newX = X + 1;
        moved = 1;
    elseif (double(key) == 30)
        setPlayerPos(player, X, Y - 1);
        newY = Y - 1;
        moved = 1;
    elseif (double(key) == 31)
        setPlayerPos(player, X, Y + 1);
        newY = Y + 1;
        moved = 1;
    end
    
end

