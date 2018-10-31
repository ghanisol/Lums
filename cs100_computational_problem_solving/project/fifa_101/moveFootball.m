function [ball, ballX, ballY] = moveFootball( ball, ballX, ballY, newX, newY)
    X = get(ball, 'XData');
    Y = get(ball, 'YData');
    Z = get(ball, 'ZData');
    
    set(ball, 'XData', X + (newX - ballX), 'YData', Y + (newY - ballY), 'ZData', Z);    
    
    ballX = newX;
    ballY = newY;
end

