function [ i ] = fac( x )
    if (x == 1)
        i = 1;
    else
        i = x * fac(x-1);
end

