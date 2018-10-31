screenSize = get(groot, 'ScreenSize'); % gets the screen size.
gameFig = figure('Name', 'Fifa 101',...
            'NumberTitle', 'off',...
            'Position', [screenSize(1) screenSize(2) screenSize(3) screenSize(4)],...
            'Resize', 'on'); % sets the game figure.
       
axis([-80 80 -60 60 0 30]); % sets the axis.
axis off;
axis equal;
hold on;
