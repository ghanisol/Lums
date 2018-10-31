

% Home Goal %
if (ballX >= 61 && ballY > -5 && ballY < 5)
   isGoalRand = randi([1,2]);
   if (isGoalRand == 1)
        homeGoals = homeGoals + 1; 
        msgbox('Home Team Scored');
        sound(goalSound,gFs);
        restart;
   else
        msgbox('GoalKeeper Saved');
        sound(saveSound, sFs);
        restartHomePlayers;
        restartAwayPlayers;
        resetFootball;
        poss = 2;
        key = 1;
        awayPlayers(1).poss = 1;
    
        r = 0.3;
        [X,Y,Z] = sphere(100);
        set(ball, 'XData', X * r + (awayPlayers(1).xPos - 1), 'YData', Y * r, 'ZData', Z * r);
        ballX = awayPlayers(1).xPos - 1;
        ballY = 0;
        pause(1);
    while ~(ballX <= 15)
        [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, ballX-3, ballY); 
        set(gca,'CameraPosition',[ballX 100 90]);
        pause(0.1); 
    end
        awayPlayers(1).poss = 0;
   end
end

% Away Goal %
if (ballX <= -61 && ballY > -5 && ballY < 5)
    isGoalRand = randi([1,2]); 
    if (isGoalRand == 1)
        awayGoals = awayGoals + 1; 
        msgbox('Away Team Scored');
        sound(goalSound,gFs);
        restart;
    else
        msgbox('GoalKeeper Saved');
        sound(saveSound, sFs);
        restartHomePlayers;
        restartAwayPlayers;
        resetFootball;
        poss = 1;
        key = 1;
        homePlayers(1).poss = 1;

        r = 0.3;
        [X,Y,Z] = sphere(100);
        set(ball, 'XData', X * r + (homePlayers(1).xPos + 1), 'YData', Y * r, 'ZData', Z * r);
        ballX = homePlayers(1).xPos + 1;
        ballY = 0;
        pause(1);
        while ~(ballX >= -15)
           [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, ballX+3, ballY); 
           set(gca,'CameraPosition',[ballX 100 90]);
           pause(0.1); 
        end
        homePlayers(1).poss = 0;
    end
end

% Away Kick %
if (ballX >= 61 && (ballY < -5 || ballY > 5))
    restartHomePlayers;
    restartAwayPlayers;
    resetFootball;
    poss = 2;
    key = 1;
    awayPlayers(1).poss = 1;
    
    r = 0.3;
    [X,Y,Z] = sphere(100);
    set(ball, 'XData', X * r + (awayPlayers(1).xPos - 1), 'YData', Y * r, 'ZData', Z * r);
    ballX = awayPlayers(1).xPos - 1;
    ballY = 0;
    pause(1);
    while ~(ballX <= 15)
       [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, ballX-3, ballY); 
       set(gca,'CameraPosition',[ballX 100 90]);
       pause(0.1); 
    end
    awayPlayers(1).poss = 0;
end

% Home Kick %
if (ballX <= -61 && (ballY < -5 || ballY > 5))
    restartHomePlayers;
    restartAwayPlayers;
    resetFootball;
    poss = 1;
    key = 1;
    homePlayers(1).poss = 1;
    
    r = 0.3;
    [X,Y,Z] = sphere(100);
    set(ball, 'XData', X * r + (homePlayers(1).xPos + 1), 'YData', Y * r, 'ZData', Z * r);
    ballX = homePlayers(1).xPos + 1;
    ballY = 0;
    pause(1);
    while ~(ballX >= -15)
       [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, ballX+3, ballY); 
       set(gca,'CameraPosition',[ballX 100 90]);
       pause(0.1); 
    end
    homePlayers(1).poss = 0;
end

% Down Throw
if (ballY >= 41)
    if (players == 'home')
    %reset with away have the ball
    else
    %reset with home have the ball
    end
end

% Up Throw
if (ballY <= -41)
    if (players == 'home')
    %reset with away have the ball
    else
    %reset with home have the ball
    end
end
