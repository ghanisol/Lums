filterLessThan :: [Int] -> Int -> [Int]
filterLessThan [] _ = []
filterLessThan (x:xs) y | x < y = x:filterLessThan xs y  
						| otherwise = filterLessThan xs y

filterGreaterThanOrEqual :: [Int] -> Int -> [Int]
filterGreaterThanOrEqual [] _ = []
filterGreaterThanOrEqual (x:xs) y | x >= y = x:filterGreaterThanOrEqual xs y
								  | otherwise = filterGreaterThanOrEqual xs y


quicksort :: [Int] -> [Int]
quicksort [] = []
quicksort (x:xs) = quicksort (filterLessThan xs x) ++ x:quicksort (filterGreaterThanOrEqual xs x) 

-- Another Approach
--quicksort (x:xs) = quicksort [i | i<-xs, i < x] ++ x:quicksort [i | i<-xs, i >= x] 


-- Quicksort using partial application concept
myfilter :: (Int -> Bool) -> [Int] -> [Int]
myfilter _ [] = []
myfilter fn (x:xs) | fn x = x:myfilter fn xs
				   | otherwise = myfilter fn xs


quicksort' :: [Int] -> [Int]
quicksort' [] = []
quicksort' (x:xs) = quicksort (myfilter (<x) xs) ++ x:quicksort (myfilter (>=x) xs) 