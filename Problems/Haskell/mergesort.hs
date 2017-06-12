split :: [Int] -> ([Int], [Int])
split [] = ([], [])
split [x] = ([x], [])
split (x:y:xys) = let (xp, yp) = split xys in (x:xp, y:yp)

merge :: [Int] -> [Int] -> [Int]
merge x [] = x
merge [] y = y
merge (x:xs) (y:ys) | x <= y = x : merge xs (y:ys)
merge (x:xs) (y:ys) = y : merge (x:xs) ys

mergesort :: [Int] -> [Int]
mergesort [] = []
mergesort [x] = [x]
mergesort x = let (xs,ys) = split x in merge (mergesort xs) (mergesort ys)
