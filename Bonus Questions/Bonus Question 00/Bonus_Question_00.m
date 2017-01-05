clear all;
clc;

%% Initialization
sec_code = 'acafataua!aUaBa!afawafasa"aNavaoabaga!ajata!auaiafa!';

%% Display Menu
disp('Welcome to the best encryption and decryption software.');
disp('Please Choose the encryption type.');
disp('1. Off by one.');
disp('2. Slice from half.');
disp('3. aa aa aaa.');
disp('4. Bonus: Decrypt the Secret Code!');

option =  input('Option : ','s');

if (option == '1' || option == '2' || option == '3')
    type = input('Press e for encryption, or d for decryption : ', 's');
    msg = input('Please enter the message : ', 's');
end

%% Algorithms

% Type 1
if (option == '1')
    if (type == 'd')
        for i = 1:length(msg)
            d_msg(i) = char(double(msg(i)) - 1);
        end
        disp('The decrypted message is : ');
        disp(d_msg);
   elseif (type == 'e')
        for i = 1:length(msg)
            e_msg(i) = char(double(msg(i)) + 1);
        end
        disp('The encrypted message is : ');
        disp(e_msg);
    else
        disp('Error : The type you have selected is invalid');
    end

% Type 2    
elseif (option == '2')
    if (type == 'd')
        half = length(msg) / 2;
        for i = 1:half
            d_msg(i) = msg(half+i);
            d_msg(half+i) = msg(i);
        end
        disp('The decrypted message is : ');
        disp(d_msg);
    elseif (type == 'e')
        half = length(msg) / 2;
        for i = 1:half
            e_msg(i) = msg(half+i);
            e_msg(half+i) = msg(i);
        end
        disp('The encrypted message is : ');
        disp(e_msg);
    else
        disp('Error : The type you have selected is invalid');
    end

% Type 3
elseif (option == '3')
    if (type == 'd')
        j = 1;
        for i = 2:2:length(msg)
            d_msg(j) = msg(i);
            j = j + 1;
        end
        disp('The decrypted message is : ');
        disp(d_msg);
    elseif (type == 'e')
        a = 1; 
        for i = 1:length(msg)
            e_msg(a) = 'a';
            e_msg(a + 1) = msg(i);
            a = a + 2;
        end
        disp('The encrypted message is : ');
        disp(e_msg);
    else
         disp('Error : The type you have selected is invalid');
    end
    
% Secret Code
elseif (option == '4')
    % Type 3
    j = 1;
    for i = 2:2:length(sec_code)
        d_sec_code_1(j) = sec_code(i);
        j = j + 1;
    end
    % Type 2
    half = length(d_sec_code_1) / 2;
    for i = 1:half
        d_sec_code_2(i) = d_sec_code_1(half+i);
        d_sec_code_2(half+i) = d_sec_code_1(i);
    end
    % Type 1
    for i = 1:length(d_sec_code_2)
        d_sec_code_3(i) = char(double(d_sec_code_2(i)) - 1);
    end 
    
    disp('The secret code is : ');
    disp(d_sec_code_3);
else
    disp('Error: This type of encryption technique does not exist on Planet Earth');
    disp('Kindly choose one of the options from above');
end

