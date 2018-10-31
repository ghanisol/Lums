AudImg = imread('images/aud1.jpg');  % gets the field image.
xImg = [-70 70; -70 70];    % sets x Data.
yImg = [-50 -50; -60 -60];    % sets y Data.
zImg = [10 10; 30 30];  %sets z Data.

surf(xImg, yImg, zImg, 'CData', AudImg, 'FaceColor','texturemap');

xImg = [70 80; 70 80];    % sets x Data.
yImg = [-40 -40; 40 40];    % sets y Data.
zImg = [10 30; 10 30];  %sets z Data.

surf(xImg, yImg, zImg, 'CData', AudImg, 'FaceColor','texturemap');