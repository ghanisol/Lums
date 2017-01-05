clc
clear
close all
myStr = ['lets ' 'se' 'e if you' ' ca' 'n do it on ' 'your own.'];
wordLength = [4 3 2 3 3 2 2 2 4 3]; % this contains length of each word
startPoint = 1;
for i = wordLength;
    disp(myStr(startPoint:startPoint+i));
    startPoint = startPoint + i + 1;
end

