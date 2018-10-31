archie_original = imread('archie.jpg');


% Archie Copy
imwrite(archie_original, 'archiecopy.jpg');

%% Archie Avg
for i = 1:size(archie_original, 1)
   for j = 1:size(archie_original, 2)
      
      for rgb = 1:3
            a = double(archie_original(i,j,1));
            b = double(archie_original(i,j,2));
            c = double(archie_original(i,j,3));
            avg = (a+b+c) / 3;
            
          archie_avg(i,j,rgb) = avg; 
      end
   end
end

imwrite(archie_avg, 'archie_avg.jpg');

% Archie Red

for i = 1:size(archie_original, 1)
   for j = 1:size(archie_original, 2)
       archie_red(i,j,1) = 255;
       for rgb = 2:3
        archie_red(i,j,rgb) = archie_original(i,j,rgb); 
      end
   end
end

imwrite(archie_red, 'archie_red.jpg');

% No Archie Red


for i = 1:size(archie_original, 1)
   for j = 1:size(archie_original, 2)
       archie_nored(i,j,1) = 0;
       for rgb = 2:3
        archie_nored(i,j,rgb) = archie_original(i,j,rgb); 
      end
   end
end

imwrite(archie_nored, 'archie_nored.jpg');

% Archie Swap

for i = 1:size(archie_original, 1)
   for j = 1:size(archie_original, 2)
      if ((archie_original(i,j,1) > 250) && (archie_original(i,j,2) > 250) && (archie_original(i,j,3) > 250))
        archie_swap(i,j,2) = 0;
        for rgb = [1 3]
            archie_swap(i,j,rgb) = 255; 
        end
      else
         for rgb = 1:3
            archie_swap(i,j,rgb) = archie_original(i,j,rgb); 
         end
      end
          
         
   end
end

imwrite(archie_swap, 'archie_swap.jpg');

% Archie Crop

for i = 30:80
   for j = 90:140
      for rgb = 1:3
         archie_crop(i-29,j-89,rgb) = archie_original(i,j,rgb); 
      end
   end
end

imwrite(archie_crop, 'archie_crop.jpg');