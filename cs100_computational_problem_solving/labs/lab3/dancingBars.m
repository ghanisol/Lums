close all;
hold on;
axis([0 150 0 100]);
index = 0:15:135;
time = 0;
w = 15;

for c = 1:10
    r(c) = rectangle('Position', [index(c) 0 w randi([10 100])], 'FaceColor', rand(1, 3));
end

while time < 10
    
    for c = 1:10
        h = randi([10 100]);
        %%x = index(randi([1 10]));
        set(r(c), 'Position', [index(c) 0 w h], 'FaceColor', rand(1, 3)); 
    end
    pause(0.1)
    time = time + 0.1;
    
end