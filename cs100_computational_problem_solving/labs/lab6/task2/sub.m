function [ j ] = sub( x, y )
j = x;
for a = 1:y
    [i, j] = incdec(j);
end

