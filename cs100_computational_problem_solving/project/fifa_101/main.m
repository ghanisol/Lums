% Pre-Start %

preMain;    % clears the stuff.
setAxis;    % sets the axis required.
setField;   % lays down the football field.
setGoalPosts;   % lays down the goal posts.
[ball, ballX, ballY] = createFootball();    % creates the football.
makeHomeTeam;   % lays down the home team.
makeAwayTeam;   % lays down the away team.
makeReferee;    % draws the referee.
setAudience;    % sets the audience.
setSideTrack;   % sets the side tracks.
setAds; %sets the side ads.
setCamera;  % sets the camera.

% Pre-Start %

% Initialization %

homeGoals = 0; awayGoals = 0;
done = 0; poss = 0;

set(gcf, 'KeyPressFcn', 'key = get(gcf, ''CurrentCharacter'');');
key = 1;
pause(2);
[crowdSound,cFs] = audioread('sounds/crowd.mp3');
sound(crowdSound,cFs);
[goalSound,gFs] = audioread('sounds/goal.mp3');
[saveSound,sFs] = audioread('sounds/save.mp3');
% Initialization %

% The Game %


while ~done
    double(key);
    
    % determine which player has the possession %
    [players, playerI] = getPossession( ball, ballX, ballY, homePlayers, awayPlayers);
    if (playerI ~= -1)
       if (players == 'home')
           homePlayers(playerI).poss = 1;
           poss = 1;
       elseif (players == 'away')
           awayPlayers(playerI).poss = 1; 
           poss = 2;
       end
    end
    
    % if home team has the possession %
    if (poss == 1)
        
        % Home Players Movement %
        if (homePlayers(4).poss == 0)
            [newX1, newY1, moved1] = movePlayer( homePlayers(4), key );
            if (moved1 == 1)
                homePlayers(4).xPos = newX1;
                homePlayers(4).yPos = newY1;
            end
        end
        if (homePlayers(5).poss == 0)
            [newX2, newY2, moved2] = movePlayer( homePlayers(5), key );
            if (moved2 == 1)
                homePlayers(5).xPos = newX2;
                homePlayers(5).yPos = newY2;
            end
        end
        
        % Pass
        if (double(key) == 115)
            homePlayers(playerI).poss = 0;
            if (ballX >= -40)
                passRand = randi([1,2]);
                if (passRand == 1)
                    playerI = 4;
                else
                    playerI = 5;
                end
                homePlayers(playerI).poss = 1;
                
                newX = homePlayers(playerI).xPos;
                newY = homePlayers(playerI).yPos;
                [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, newX+1, newY);
            end
            
        end
        
        % Away Team Select %
        if (ballX >= 0 && ballX <= 20 && ballY <= 0)
            selectPlayerI = 5;
        elseif (ballX >= 0 && ballX <= 20 && ballY >= 0)
            selectPlayerI = 4;
       elseif (ballX >= 20 && ballX <= 50 && ballY <= 0)
            selectPlayerI = 3;
       elseif (ballX >= 20 && ballX <= 50 && ballY <= 0)
            selectPlayerI = 2;
       else
            selectPlayerI = 6;
        end
       
       % Away Player Movement %
       if (awayPlayers(selectPlayerI).xPos > ballX && awayPlayers(selectPlayerI).yPos < ballY)
            setPlayerPos(awayPlayers(selectPlayerI), awayPlayers(selectPlayerI).xPos-1, awayPlayers(selectPlayerI).yPos+1);
            awayPlayers(selectPlayerI).xPos = awayPlayers(selectPlayerI).xPos-1;
            awayPlayers(selectPlayerI).yPos = awayPlayers(selectPlayerI).yPos+1;
       elseif (awayPlayers(selectPlayerI).xPos > ballX && awayPlayers(selectPlayerI).yPos > ballY)
            setPlayerPos(awayPlayers(selectPlayerI), awayPlayers(selectPlayerI).xPos-1, awayPlayers(selectPlayerI).yPos-1);
            awayPlayers(selectPlayerI).xPos = awayPlayers(selectPlayerI).xPos-1;
            awayPlayers(selectPlayerI).yPos = awayPlayers(selectPlayerI).yPos-1;
       elseif (awayPlayers(selectPlayerI).xPos < ballX && awayPlayers(selectPlayerI).yPos < ballY)
            setPlayerPos(awayPlayers(selectPlayerI), awayPlayers(selectPlayerI).xPos-1, awayPlayers(selectPlayerI).yPos-1);
            awayPlayers(selectPlayerI).xPos = awayPlayers(selectPlayerI).xPos+1;
            awayPlayers(selectPlayerI).yPos = awayPlayers(selectPlayerI).yPos+1;
       elseif (awayPlayers(selectPlayerI).xPos < ballX && awayPlayers(selectPlayerI).yPos > ballY)
            setPlayerPos(awayPlayers(selectPlayerI), awayPlayers(selectPlayerI).xPos-1, awayPlayers(selectPlayerI).yPos-1);
            awayPlayers(selectPlayerI).xPos = awayPlayers(selectPlayerI).xPos+1;
            awayPlayers(selectPlayerI).yPos = awayPlayers(selectPlayerI).yPos-1;
       end
        
       % Home Player Movement %
       [newX, newY, moved] = movePlayer( homePlayers(playerI), key );
        if (moved == 1)
        homePlayers(playerI).xPos = newX;
        homePlayers(playerI).yPos = newY;
        end
        
        % Football movement %
        if (double(key) == 28)
            [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, newX-1, newY);
        elseif(double(key) == 29)
            [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, newX+1, newY);
        elseif (double(key) == 30)
            [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, newX, newY-1);
        elseif (double(key) == 31)
            [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, newX, newY+1);
        end
        
        % Shoot
        if (double(key) == 100 && ballX >= 30)
           
            goalRand = randi([1,2]);
            if (goalRand == 1)
                while ~(ballX > 61)
                    [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, ballX+3, ballY); 
                    set(gca,'CameraPosition',[ballX 100 90]);
                    pause(0.1);
                end
            else
                while ~(ballX > 62)
                    [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, ballX+3, ballY+0.25); 
                    set(gca,'CameraPosition',[ballX 100 90]);
                    pause(0.1);
                end
            end
        end
        
    % if away team has the possession %    
    elseif (poss == 2)
        
        % Select home player %
       if (ballX >= -50 && ballX <= -20 && ballY <= 0)
            selectPlayerI = 3;
       elseif (ballX >= -50 && ballX <= -20 && ballY >= 0)
            selectPlayerI = 2;
       elseif (ballX >= -20 && ballX <= 0 && ballY <= 0)
            selectPlayerI = 5;
       elseif (ballX >= -20 && ballX <= 0 && ballY <= 0)
            selectPlayerI = 4;
       else
            selectPlayerI = 6;
       end
        % home player movement %
        [newX, newY, moved] = movePlayer( homePlayers(selectPlayerI), key );
        if (moved == 1)
        homePlayers(selectPlayerI).xPos = newX;
        homePlayers(selectPlayerI).yPos = newY;
        end
        
        % away player movement %
        setPlayerPos(awayPlayers(6), awayPlayers(6).xPos - 1, ballY);
        if (moved == 1)
            awayPlayers(6).xPos = awayPlayers(6).xPos - 1;
            awayPlayers(6).yPos = ballY;
        end
        
        [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, awayPlayers(6).xPos - 1, ballY  );
        
        if (ballX <= -40)
           while ~(ballX < -61)
              [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, ballX-3, ballY); 
                set(gca,'CameraPosition',[ballX 100 90]);
              pause(0.1);
           end
        end
        
    else
       % home player movement %
        [newX, newY, moved] = movePlayer( homePlayers(6), key );
        if (moved == 1)
            homePlayers(6).xPos = newX;
            homePlayers(6).yPos = newY;
        end 
    end
    
    setReferee(referee, ballX, 40); % resets the referee.
    camtarget([ballX ballY 0]); % resets the camera target.
    set(gca,'CameraPosition',[ballX 100 90]);   %resets the camera position.
    set(gameFig, 'name', ['Futsal: ' num2str(homeGoals) ' - ' num2str(awayGoals)]);
    goalCountnFouls;    % resets the goal counter.
    pause(0.1);
end

% The Game %

% Pro-Start %

winLose;
ProMain;

% Pro-Start %