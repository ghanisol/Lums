function [football, ballX, ballY] = createFootball( )

    r = 0.3;
    [X,Y,Z] = sphere(100);
    ballImg = imread('images/football.jpg');  % gets the fooball image.
    football = warp(X*r, Y*r, Z*r+r,ballImg); % wraps the image around the sphere.
    ballX = 0;
    ballY = 0;
end

