axis([0 6 -20 5]);
hold on;
x = 0:1:5;
sinx_1 = x - (x.^3/factorial(3)) + (x.^5/factorial(5)) - (x.^7/factorial(7));
plot(x, sinx_1);

sinx_2 = x - (x.^3/factorial(3));
plot(x, sinx_2);
