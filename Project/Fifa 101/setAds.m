adImg = imread('images/pepsiad.jpg');  % gets the field image.

xImg = [-70 -20; -70 -20];    % sets x Data.
yImg = [-50 -50; -50 -50];    % sets y Data.
zImg = [0 0; 10 10];  %sets z Data.
surf(xImg, yImg, zImg, 'CData', adImg, 'FaceColor','texturemap');


xImg = [-20 20; -20 20];    % sets x Data.
yImg = [-50 -50; -50 -50];    % sets y Data.
zImg = [0 0; 10 10];  %sets z Data.
surf(xImg, yImg, zImg, 'CData', adImg, 'FaceColor','texturemap');

xImg = [20 70; 20 70];    % sets x Data.
yImg = [-50 -50; -50 -50];    % sets y Data.
zImg = [0 0; 10 10];  %sets z Data.
surf(xImg, yImg, zImg, 'CData', adImg, 'FaceColor','texturemap');

% Right %
xImg = [70 70; 70 70];    % sets x Data.
yImg = [-40 0; -40 0];    % sets y Data.
zImg = [0 0; 10 10];  %sets z Data.
surf(xImg, yImg, zImg, 'CData', adImg, 'FaceColor','texturemap');


xImg = [70 70; 70 70];    % sets x Data.
yImg = [0 40; 0 40];    % sets y Data.
zImg = [0 0; 10 10];  %sets z Data.
surf(xImg, yImg, zImg, 'CData', adImg, 'FaceColor','texturemap');
