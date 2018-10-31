function grid(n)
    axis([0 n 0 n]); axis equal; axis on;
    
    for i = 0:n-1
       for j = 0:n-1
          box = rectangle('Position', [i j 1 1], 'faceColor', [0 0 0], 'EdgeColor','b'); 
       end
    end
end