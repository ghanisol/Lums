function [i j] = div( x, y )
i = 1;
while ( mul(y, i) <= x)
    i = i + 1;
end
i = i - 1;

j = x - mul(y, i);



end

