mymap :: (Int -> Int) -> [Int] -> [Int]
mymap :: _ [] = []
mymap fn (x:xs) = fn x : mymap fn xs

myfold :: (Int->Int->Int)->[Int]->Int
myfold _ [] = undefined
myfold _ [x] = x
myfold fn (x:xs) = fn x (myfold fn xs) 

myfilter :: (Int -> Bool) -> [Int] -> [Int]
myfilter _ [] = []
myfilter fn (x:xs) | fn x = x:myfilter fn xs
				   | otherwise = myfilter fn xs

myremove :: (Int->Bool)->[Int]->[Int]
myremove _ [] = []
myremove fn x = myfilter (\x -> not (fn x)) x 

-- Calculate the average of those squares of the first 100 positive numbers whose rightmost decimal digit is less than 5
(\xs -> sum xs `div` length xs) $ filter (\x -> x `mod` 10 < 5) $ map (^2) [1..100]

