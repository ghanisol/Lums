function table = makeTable( n, bombs )
    table = zeros(n);
    bombPosX = randi([1, n], [1, 2]);
    bombPosY = randi([1, n], [1, 2]);
    table(bombPosX(1), bombPosY(1)) = -1;
    table(bombPosX(2), bombPosY(2)) = -1;
end

