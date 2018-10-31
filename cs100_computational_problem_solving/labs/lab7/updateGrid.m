function updateGrid(x, y, table)
    if (table(y+1,x+1) == -1)
        drawBomb(x,y);
    else
        drawSafe(x,y);
    end
end

