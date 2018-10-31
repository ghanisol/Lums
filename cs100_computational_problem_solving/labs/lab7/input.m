function [x, y, inputTable]  = input( inputTable )
    
    isOpen = true;
    
    while (isOpen == true)
        [x, y] = ginput(1);
        x = floor(x);
        y = floor(y);
        
        if (inputTable(y+1, x+1) ~= 1)
            isOpen = false;
        end
    end
    
end

