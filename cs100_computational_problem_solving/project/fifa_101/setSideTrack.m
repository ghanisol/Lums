trackImg = imread('images/sidetrack.jpg');  % gets the field image.
xImg = [-70 0; -70 0];    % sets x Data.
yImg = [40 40; 60 60];    % sets y Data.
zImg = [0 0; 0 0];  %sets z Data.
surf(xImg, yImg, zImg, 'CData', trackImg, 'FaceColor','texturemap');

xImg = [0 70; 0 70];    % sets x Data.
yImg = [40 40; 60 60];    % sets y Data.
zImg = [0 0; 0 0];  %sets z Data.
surf(xImg, yImg, zImg, 'CData', trackImg, 'FaceColor','texturemap');


xImg = [-70 0; -70 0];    % sets x Data.
yImg = [-40 -40; -50 -50];    % sets y Data.
zImg = [0 0; 0 0];  %sets z Data.
surf(xImg, yImg, zImg, 'CData', trackImg, 'FaceColor','texturemap');

xImg = [0 70; 0 70];    % sets x Data.
yImg = [-40 -40; -50 -50];    % sets y Data.
zImg = [0 0; 0 0];  %sets z Data.
surf(xImg, yImg, zImg, 'CData', trackImg, 'FaceColor','texturemap');