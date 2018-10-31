fieldImg = imread('images/field.jpg');  % gets the field image.
xImg = [-70 70; -70 70];    % sets x Data.
yImg = [40 40; -40 -40];    % sets y Data.
zImg = [0 0; 0 0];  %sets z Data.

surf(xImg, yImg, zImg, 'CData', fieldImg, 'FaceColor','texturemap');
