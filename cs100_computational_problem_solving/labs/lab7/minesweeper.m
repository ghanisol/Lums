function minesweeper(n, bombs)
    if (bombs > (n*n))
        display('Error: The number of bombs are greater than the number of boxes');
        return;
    end
    
    hold on;
    grid(n);
    table = makeTable(n, bombs);

    while (true)
        [x, y, inputTable] = input(table);
        updateGrid(x, y, inputTable);
        win = winLose(x, y, table);
        
        if (win == -1)
           title('You Lost'); 
           [fail,Fs] = audioread('failSound.wav');
           sound(fail,Fs);
           return;
        end
        
        table(y+1, x+1) = 1;
        win = 1;
        
        for i = 1:n
           for j = 1:n
              if (table(j, i) == 0)
                  win = 0;
                  break;
              end
           end
           if (win == 0)
              break; 
           end
        end
        
        if (win == 1)
           title('You Won'); 
           [won,Fs] = audioread('Winning.wav');
           sound(won,Fs);
           return;
        end
        
    end
end