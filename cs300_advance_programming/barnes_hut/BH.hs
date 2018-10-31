-- CS300-SP17 Assignment 2: Barnes Hut Simulation
-- Deadline: 24 Feb 9pm
-- Submission: via LMS only
--
import System.Environment
import Data.List
import Graphics.Rendering.OpenGL hiding (($=))
import Graphics.UI.GLUT
import Control.Applicative
import Data.IORef
import Debug.Trace
import Data.Function (on)
import Data.Monoid

--
-- PART 1: You are given many input files in the inputs directory and given 
-- code can read and parse the input files. You need to run "cabal update 
-- && cabal install glut" on your system to work on this assignment. Then
-- run "./ghc BH.hs && ./BH 1 < inputs/planets.txt" to run 1 iteration of
-- the algorithm and print updated positions. Replace 1 with any number to
-- run more iteration. You may also run it without an argument and it will
-- display the simulation using OpenGL in a window.
--
-- In the first part, you are to write the updateBody function to correctly 
-- update body after 1 unit of time has passed. You have to correctly 
-- update the position of a body by calculating the effect of all other
-- bodies on it. The placeholder implementation just moves the body left
-- without doing any physics. Read http://www.cs.princeton.edu/courses/
-- archive/fall03/cs126/assignments/nbody.html for help with physics. Try
-- simplyfying equations on paper before implementing them. You can compare
-- answers with the given binary solution.
--
-- Make helper functions as needed
type Vec2 = (Double, Double)
data Body = Body Vec2 Vec2 Double (Color3 Double) deriving (Eq)

instance Monoid Double where
    mempty = 0
    x `mappend` y = x + y

calcForce :: Body -> Body -> (Double, Double)
calcForce b1@(Body (x1,y1) _ m1 _) b2@(Body (x2,y2) _ m2 _)
    | b1 == b2 = (0,0)
    | otherwise = (fx, fy) where
        g = 6.67 * (10^^(-11))
        (dx,dy) = (x2-x1,y2-y1)
        r = sqrt ((dx^2)+(dy^2))
        fx = (g*m1*m2*dx) / (r^3)
        fy = (g*m1*m2*dy) / (r^3)

updateBody :: (Foldable f) => f Body -> Body -> Body
updateBody xs b@(Body (posx,posy) (vel1, vel2) mass clr) =
    (Body (posx+vx,posy+vy) (vx,vy) mass clr) where
        (fx,fy) = foldMap (calcForce b) xs
        vx = vel1+(fx/mass)
        vy = vel2+(fy/mass)


-- PART 2: We will make a Quadtree to represent our universe. See 
-- http://www.cs.princeton.edu/courses/archive/fall03/cs126/assignments/
-- barnes-hut.html for help on this tree. The QT structure has the the
-- length of one side of quadrant) for internal nodes. The makeQT function
-- has arguments: center, length of quadrant side, a function to find
-- coordinates of an element of the tree (e.g. extract position from a Body
-- object), a function to summarize a list of nodes (e.g. to calculate a
-- Body with position center of gravity and total mass), and the list of
-- nodes to put in tree.
--
-- Note that inserting all nodes at once is much easier than inserting one
-- by one. Think of creating the root node (given all nodes), and then
-- divide the nodes into quadrants and let recursive calls create the
-- appropriate trees. In this part you do not have to give a correct
-- implementation of the summary function
--
-- Now make QT member of Foldable typeclass. See what function you are
-- required to implement. Once this is done, change the tick function below 
-- to create the tree and then pass it to updateBody function instead of a 
-- list of bodies. No change to updateBody function should be needed since
-- it works with any Foldable.
data QT a = Internal Double a (QT a,QT a,QT a,QT a) | Leaf a | Nil
makeQT :: Vec2 -> Double -> (a->Vec2) -> ([a]->a) -> [a] -> (QT a)
makeQT _ _ _ _ [] = Nil
makeQT _ _ _ _ [x] = Leaf x
makeQT (cx,cy) radius getPos summarize bodies = Internal radius (summarize bodies) (tLeft , bLeft, bRight, tRight) where
    tLeft = makeQT (cx-nr,cy+nr) nr getPos summarize [b | b <- bodies, (fst.getPos) b < cx && (snd.getPos) b >= cy]
    bLeft = makeQT (cx-nr,cy-nr) nr getPos summarize [b | b <- bodies, (fst.getPos) b < cx && (snd.getPos) b < cy]
    bRight = makeQT (cx+nr,cy-nr) nr getPos summarize [b | b <- bodies, (fst.getPos) b >= cx && (snd.getPos) b < cy]
    tRight = makeQT (cx+nr,cy+nr) nr getPos summarize [b | b <- bodies, (fst.getPos) b >= cx && (snd.getPos) b >= cy]
    nr = radius/2

getPos :: Body -> Vec2
getPos (Body pos _ _ _) = pos

summarize :: [Body] -> Body
summarize [b] = b  
summarize ((Body (x1,y1) v m1 clr):bs) = (Body (x,y) v m clr) where
    (Body (x2,y2) _ m2 _) = summarize bs
    m = m1+m2
    x = (x1*m1 + x2*m2) / m
    y = (y1*m1 + y2*m2) / m

instance Foldable QT where
    foldMap f Nil = mempty
    foldMap f (Leaf b) = f b
    foldMap f (Internal _ _ (tL,bL,bR,tR)) = foldMap f tL `mappend` foldMap f bL `mappend` foldMap f bR `mappend` foldMap f tR


-- This functions takes a set of bodies and returns an updated set of 
-- bodies after 1 unit of time has passed (dt=1)
tick ::Double -> [Body] -> [Body]
tick radius bodies = fmap (updateBody (BH isSuff bTree)) bodies where
    bTree = makeQT (7,7) radius getPos summarize bodies

-- PART 3: Now we create another datatype that contains a quadtree and a 
-- function which given radius and a summarized body (containing center of
-- gravity and total mass) returns true if the summarized body is a good
-- enough approximation. Use 0.5 as threshold.
--
-- Make a correct summarize function to pass to makeQT above and then make
-- BH an instance of Foldable typeclass as well. However this instance
-- should use the internal node if the predicate function returns true and
-- recurse only if it returns false. Make sure to recurse over a BH type
-- variable. If your implementation is correct, you will be as fast as the
-- provided binary BH2 on large inputs like galaxy1.txt
data BH a = BH (Double -> a -> Bool) (QT a)

isSuff :: Double -> Body -> Bool
isSuff r (Body (x1,y1) _ _ _) = r/d < 0.5 where
    nr = r/2
    d = (sqrt (((x1-nr)^2) + ((y1-nr)^2)))

instance Foldable BH where
    foldMap f (BH _ Nil) = mempty
    foldMap f (BH _ (Leaf b)) = f b
    foldMap f (BH g (Internal r sBody (tL,bL,bR,tR)))
        | g r sBody = f sBody 
        | otherwise = foldMap f (BH g tL) `mappend` foldMap f (BH g bL) `mappend` foldMap f (BH g bR) `mappend` foldMap f (BH g tR)

---------------------------------------------------------------------------
-- You don't need to study the code below to work on the assignment
---------------------------------------------------------------------------
main :: IO ()
main = do
    (_,args) <- getArgsAndInitialize
    stdin <- getContents
    uncurry (mainChoice args) (parseInput stdin)

mainChoice :: [String] -> Double -> [Body] -> IO ()
mainChoice (iter:_) r bodies = putStr $ applyNtimes r bodies (read iter)
mainChoice [] r bodies = do
    createWindow "Barnes Hut"
    windowSize $= Size 700 700
    bodiesRef <- newIORef bodies
    ortho2D (-r) r (-r) r
    displayCallback $= (display r bodiesRef)
    addTimerCallback 10 (timer r bodiesRef)
    mainLoop

applyNtimes :: Double -> [Body] -> Int -> String
applyNtimes r bodies n = (unlines.map show) (iterate (tick r) bodies !! n)

parseInput :: String -> (Double, [Body])
parseInput input = 
    let (cnt:r:bodies) = lines input
    in (read r, map read (take (read cnt) bodies))

dispBody :: Body -> IO ()
dispBody (Body (x,y) _ _ rgb) = color rgb >> vertex (Vertex2 x y)

display :: Double -> IORef [Body] -> IO ()
display r bodiesRef = do
    clear [ColorBuffer]
    bodies <- get bodiesRef
    renderPrimitive Points (mapM_ dispBody bodies)
    flush

timer :: Double -> IORef [Body] -> IO ()
timer r bodiesRef = do
    postRedisplay Nothing
    bodies <- get bodiesRef
    bodiesRef $= tick r bodies 
    addTimerCallback 10 (timer r bodiesRef)

instance Read Body where
    readsPrec _ input = 
        let (x:y:vx:vy:m:r:g:b:rest) = words input
        in (\str -> [(Body (read x,read y) (read vx,read vy) (read m) 
            (Color3 ((read r)/255) ((read g)/255) ((read b)/255)), 
            unwords rest)]) input

instance Show Body where
    show (Body (x,y) (vx,vy) _ _) =
        "x=" ++ show x ++ " y=" ++ show y ++ " vx=" ++ 
            show vx ++ " vy=" ++ show vy

