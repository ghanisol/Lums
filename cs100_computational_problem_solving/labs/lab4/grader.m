figure;
axis equal;
axis([0 100 0 100]);
hold on;

marks = randi([30, 100], [1, 20]);

for i = 1:20
   if marks(i) >= 90
       disp('A');
   elseif marks(i) >= 70
       disp('B');
   elseif marks(i) >= 50
       disp('C');
   else
       disp('fail');
   end
end

index = 0;
for j = 1:20 
   if marks(j) >= 90
       color = 'g';
   elseif marks(j) >= 70
       color = 'b';
   elseif marks(j) >= 50
       color = 'y';
   else
       color = 'r';
   end
    r = rectangle('Position', [index 0 5 marks(j)], 'FaceColor', color);
    index = index + 5;
end


