clc
clear
close all
figure;
axis equal
h1 = rectangle('Position',[-20 -20 40 40],'curvature',[1 1], ...
 'facecolor',rand(1,3));
for i=1:100
 set(h1,'facecolor',rand(1,3));
 pause(0.1); % pause of 0.1 seconds so that I can see the output
end