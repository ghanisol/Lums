package main

import (
    "fmt"
    "os"
    "strconv"
    "math"
	"encoding/csv"
	"sync"
)

type CensusGroup struct {
	population int
	latitude, longitude float64
}

func ParseCensusData(fname string) ([]CensusGroup, error) {
	file, err := os.Open(fname)
    if err != nil {
		return nil, err
    }
    defer file.Close()

	records, err := csv.NewReader(file).ReadAll()
	if err != nil {
		return nil, err
	}
	censusData := make([]CensusGroup, 0, len(records))

    for _, rec := range records {
        if len(rec) == 7 {
            population, err1 := strconv.Atoi(rec[4])
            latitude, err2 := strconv.ParseFloat(rec[5], 64)
            longitude, err3 := strconv.ParseFloat(rec[6], 64)
            if err1 == nil && err2 == nil && err3 == nil {
                latpi := latitude * math.Pi / 180
                latitude = math.Log(math.Tan(latpi) + 1 / math.Cos(latpi))
                censusData = append(censusData, CensusGroup{population, latitude, longitude})
            }
        }
    }

	return censusData, nil
}

func FindCorners(censusData []CensusGroup, parent chan []float64) {
    if (len(censusData) > 1000) {
        mid := len(censusData)/2
        left := make(chan []float64)
        right := make(chan []float64)
        go FindCorners(censusData[:mid], left)
        go FindCorners(censusData[mid:], right)
        leftInfo := <-left
        rightInfo := <-right

        parent<- []float64{math.Max(leftInfo[0], rightInfo[0]), math.Min(leftInfo[1], rightInfo[1]), math.Max(leftInfo[2], rightInfo[2]), math.Min(leftInfo[3], rightInfo[3])}

    } else {
        maxLat, maxLong := censusData[0].latitude, censusData[0].longitude
        minLat, minLong := censusData[0].latitude, censusData[0].longitude

        for _, rec := range censusData[1:] {
            if rec.latitude > maxLat {
                maxLat = rec.latitude
            }
            if rec.latitude < minLat {
                minLat = rec.latitude
            }
            if rec.longitude > maxLong {
                maxLong = rec.longitude
            }
            if rec.longitude < minLong {
                minLong = rec.longitude
            }
        }

        parent<- []float64{maxLat, minLat, maxLong, minLong}

    }
}

func getQuery(censusData []CensusGroup, queryInfo, dimInfo []int, maxminInfo []float64, parent chan []int) {
    if len(censusData) > 1000 {
        mid := len(censusData)/2
        left := make(chan []int)
        right := make(chan []int)
        go getQuery(censusData[:mid], queryInfo, dimInfo, maxminInfo, left)
        go getQuery(censusData[mid:], queryInfo, dimInfo, maxminInfo, right)
        leftInfo := <-left
        rightInfo := <-right
        parent<- []int{leftInfo[0]+rightInfo[0], leftInfo[1]+rightInfo[1]} 

    } else {
        population := 0
        totalPop := 0

        for _, rec := range censusData {
          
            row := int((rec.latitude-maxminInfo[1]) / ((maxminInfo[0]-maxminInfo[1])/float64(dimInfo[0]))) + 1
            if row > dimInfo[0] {
                row -= 1
            }
            col := int((rec.longitude-maxminInfo[3]) / ((maxminInfo[2]-maxminInfo[3])/float64(dimInfo[1]))) + 1
            if col > dimInfo[1] {
                col -= 1
            }

            if (row >= queryInfo[1] && row <= queryInfo[3] && col >= queryInfo[0] && col <= queryInfo[2]) {
                population += rec.population
            }
            totalPop += rec.population

        }

        parent<- []int{population, totalPop} 
    }
}

func MutexMakeGrid(censusData []CensusGroup, grid [][]int, muGrid [][]*sync.Mutex, dimInfo []int, maxminInfo []float64, done chan bool) {
	if len(censusData) > 1000 {
		mid := len(censusData)/2
		left := make(chan bool)
        right := make(chan bool)
        go MutexMakeGrid(censusData[:mid], grid, muGrid, dimInfo, maxminInfo, left)
        go MutexMakeGrid(censusData[mid:], grid, muGrid, dimInfo, maxminInfo, right)
        <-left
        <-right

	} else {
		ydim, xdim := dimInfo[0], dimInfo[1]
        maxLat, minLat, maxLong, minLong := maxminInfo[0], maxminInfo[1], maxminInfo[2], maxminInfo[3]
        
        for _, rec := range censusData {
            row := int((rec.latitude-minLat) / ((maxLat-minLat)/float64(ydim))) + 1
            if row > ydim {
                row -= 1
            }
            col := int((rec.longitude-minLong) / ((maxLong-minLong)/float64(xdim))) + 1
            if col > xdim {
                col -= 1
            }
            
            muGrid[ydim-row][col-1].Lock()
            grid[ydim-row][col-1] += rec.population
            muGrid[ydim-row][col-1].Unlock()
        }
	}
	done<- true
}

func makeGrid(censusData []CensusGroup, dimInfo []int, maxminInfo []float64, parent chan [][]int) {
	if len(censusData) > 1000 {
		mid := len(censusData)/2
		left := make(chan [][]int)
		right := make(chan [][]int)
		go makeGrid(censusData[:mid], dimInfo, maxminInfo, left)
		go makeGrid(censusData[mid:], dimInfo, maxminInfo, right)
		leftGrid := <-left
		rightGrid := <-right

		for i:=0; i<dimInfo[0]; i++ {
			for j:=0; j<dimInfo[1]; j++ {
				leftGrid[i][j] += rightGrid[i][j]
			}
		}

		parent<- leftGrid

	} else {
		ydim, xdim := dimInfo[0], dimInfo[1]
		maxLat, minLat, maxLong, minLong := maxminInfo[0], maxminInfo[1], maxminInfo[2], maxminInfo[3]
		
		grid := make([][]int, ydim)
	    for i:=0; i<ydim; i++ {
	    	grid[i] = make([]int, xdim)
	    }

		for _, rec := range censusData {
     		row := int((rec.latitude-minLat) / ((maxLat-minLat)/float64(ydim))) + 1
            if row > ydim {
                row -= 1
            }
            col := int((rec.longitude-minLong) / ((maxLong-minLong)/float64(xdim))) + 1
            if col > xdim {
                col -= 1
            }

            grid[ydim-row][col-1] += rec.population
     	}

     	parent<- grid
	}
}


func main () {
	if len(os.Args) < 4 {
		fmt.Printf("Usage:\nArg 1: file name for input data\nArg 2: number of x-dim buckets\nArg 3: number of y-dim buckets\nArg 4: -v1, -v2, -v3, -v4, -v5, or -v6\n")
		return
	}
	fname, ver := os.Args[1], os.Args[4]
    xdim, err := strconv.Atoi(os.Args[2])
	if err != nil {
		fmt.Println(err)
		return
	}
    ydim, err := strconv.Atoi(os.Args[3])
	if err != nil {
		fmt.Println(err)
		return
	}
	censusData, err := ParseCensusData(fname)
	if err != nil {
		fmt.Println(err)
		return
	}

    // Some parts may need no setup code

    // Corner info
    var maxLat, minLat, maxLong, minLong float64

    // Initializing the grid
    grid := make([][]int, ydim)
    for i:=0; i<ydim; i++ {
    	grid[i] = make([]int, xdim)
    }

    // Initializing mutex grid
    muGrid := make([][]*sync.Mutex, ydim)
   

    switch ver {
    case "-v1":
        // YOUR SETUP CODE FOR PART 1
    
        maxLat, maxLong = censusData[0].latitude, censusData[0].longitude
        minLat, minLong = censusData[0].latitude, censusData[0].longitude

        for _, rec := range censusData[1:] {
            if rec.latitude > maxLat {
                maxLat = rec.latitude
            }
            if rec.latitude < minLat {
                minLat = rec.latitude
            }
            if rec.longitude > maxLong {
                maxLong = rec.longitude
            }
            if rec.longitude < minLong {
                minLong = rec.longitude
            }
        }


    case "-v2":
        // YOUR SETUP CODE FOR PART 2
    
        parent := make(chan []float64)
        go FindCorners(censusData, parent)
        maxminInfo := <-parent
        maxLat, minLat, maxLong, minLong = maxminInfo[0], maxminInfo[1], maxminInfo[2], maxminInfo[3]
    

    case "-v3":
        // YOUR SETUP CODE FOR PART 3

    	// Finding four corners O(n)
        maxLat, maxLong = censusData[0].latitude, censusData[0].longitude
        minLat, minLong = censusData[0].latitude, censusData[0].longitude

        for _, rec := range censusData[1:] {
            if rec.latitude > maxLat {
                maxLat = rec.latitude
            }
            if rec.latitude < minLat {
                minLat = rec.latitude
            }
            if rec.longitude > maxLong {
                maxLong = rec.longitude
            }
            if rec.longitude < minLong {
                minLong = rec.longitude
            }
        }


        // Making the grid
      
     	for _, rec := range censusData {
     		row := int((rec.latitude-minLat) / ((maxLat-minLat)/float64(ydim))) + 1
            if row > ydim {
                row -= 1
            }
            col := int((rec.longitude-minLong) / ((maxLong-minLong)/float64(xdim))) + 1
            if col > xdim {
                col -= 1
            }
            grid[ydim-row][col-1] += rec.population
     	}

     	// Updating the grid

     	for i:=0; i<ydim; i++ {
     		for j:=0; j<xdim; j++ {
     			if i == 0 && j == 0 {
     				continue		
     			} else if i == 0 {
     				grid[i][j] += grid[i][j-1]
     			} else if j == 0 {
     				grid[i][j] += grid[i-1][j]
     			} else {
     			 	grid[i][j] += grid[i][j-1] + grid[i-1][j] - grid[i-1][j-1]
     			}
     		}
     	} 
     	
    case "-v4":
        // YOUR SETUP CODE FOR PART 4

        parent := make(chan []float64)
        go FindCorners(censusData, parent)
        maxminInfo := <-parent
        maxLat, minLat, maxLong, minLong = maxminInfo[0], maxminInfo[1], maxminInfo[2], maxminInfo[3]

        // Making the grid

        dimInfo := []int{ydim, xdim}
        gridChan := make(chan [][]int)
        go makeGrid(censusData, dimInfo, maxminInfo, gridChan)
        grid = <-gridChan

        // Updating the grid

        for i:=0; i<ydim; i++ {
     		for j:=0; j<xdim; j++ {
     			if i == 0 && j == 0 {
     				continue		
     			} else if i == 0 {
     				grid[i][j] += grid[i][j-1]
     			} else if j == 0 {
     				grid[i][j] += grid[i-1][j]
     			} else {
     			 	grid[i][j] += grid[i][j-1] + grid[i-1][j] - grid[i-1][j-1]
     			}
     		}
     	} 

    case "-v5":
        // YOUR SETUP CODE FOR PART 5

        parent := make(chan []float64)
        go FindCorners(censusData, parent)
        maxminInfo := <-parent
        maxLat, minLat, maxLong, minLong = maxminInfo[0], maxminInfo[1], maxminInfo[2], maxminInfo[3]


		// Making mutex grid
		for i:=0; i<ydim; i++ {
			muGrid[i] = make([]*sync.Mutex, xdim)
			for j:=0; j<xdim; j++ {
				var mu sync.Mutex
				muGrid[i][j] = &mu
			}
		}

		dimInfo := []int{ydim, xdim}
		done := make(chan bool)
		go MutexMakeGrid(censusData, grid, muGrid, dimInfo, maxminInfo, done)
		<-done

        // Updating the grid

        for i:=0; i<ydim; i++ {
     		for j:=0; j<xdim; j++ {
     			if i == 0 && j == 0 {
     				continue		
     			} else if i == 0 {
     				grid[i][j] += grid[i][j-1]
     			} else if j == 0 {
     				grid[i][j] += grid[i-1][j]
     			} else {
     			 	grid[i][j] += grid[i][j-1] + grid[i-1][j] - grid[i-1][j-1]
     			}
     		}
     	} 


    case "-v6":
        // YOUR SETUP CODE FOR PART 6

        parent := make(chan []float64)
        go FindCorners(censusData, parent)
        maxminInfo := <-parent
        maxLat, minLat, maxLong, minLong = maxminInfo[0], maxminInfo[1], maxminInfo[2], maxminInfo[3]


        // Making mutex grid
        for i:=0; i<ydim; i++ {
            muGrid[i] = make([]*sync.Mutex, xdim)
            for j:=0; j<xdim; j++ {
                var mu sync.Mutex
                muGrid[i][j] = &mu
            }
        }

        dimInfo := []int{ydim, xdim}
        done := make(chan bool)
        go MutexMakeGrid(censusData, grid, muGrid, dimInfo, maxminInfo, done)
        <-done
   
        cols := make([]int, xdim)
        for i, _ := range cols {
            cols[i] = i
        }

        rowchan := make(chan int)
        go rowsPrefixSum(grid, rowchan)
        <-rowchan
        
        colchan := make(chan int)
        go colsPrefixSum(grid, cols, colchan)
        <-colchan
        

    default:
        fmt.Println("Invalid version argument")
        return
    }

    for {
        var west, south, east, north int
        n, err := fmt.Scanln(&west, &south, &east, &north)
        if n != 4 || err != nil || west<1 || west>xdim || south<1 || south>ydim || east<west || east>xdim || north<south || north>ydim {
            break
        }

        var population int
        var percentage float64
        switch ver {
        case "-v1":
            // YOUR QUERY CODE FOR PART 1
            
            population = 0
            totalPop := 0

            for _, rec := range censusData {
                row := int((rec.latitude-minLat) / ((maxLat-minLat)/float64(ydim))) + 1
                if row > ydim {
                    row -= 1
                }
                col := int((rec.longitude-minLong) / ((maxLong-minLong)/float64(xdim))) + 1
                if col > xdim {
                    col -= 1
                }
                
                if (row >= south && row <= north && col >= west && col <= east) {
                    population += rec.population
                }
                totalPop += rec.population

            }

            percentage = float64(population)/float64(totalPop) * 100
           
        case "-v2":
            // YOUR QUERY CODE FOR PART 2
            maxminInfo := []float64{maxLat, minLat, maxLong, minLong}
            dimInfo := []int{ydim, xdim}
            queryInfo := []int{west, south, east, north}

            parent := make(chan []int)
            go getQuery(censusData, queryInfo, dimInfo, maxminInfo, parent)
            popInfo := <-parent
            population = popInfo[0]
            percentage = float64(popInfo[0])/float64(popInfo[1]) * 100
        
        case "-v3":
            // YOUR QUERY CODE FOR PART 3
    		
    		topRow, bottomRow, rightCol, leftCol := ydim-north, ydim-south, east-1, west-1

            if topRow-1 < 0 && leftCol-1 < 0 {
                population = grid[bottomRow][rightCol]
            } else if topRow-1 < 0 {
                population = grid[bottomRow][rightCol] - grid[bottomRow][leftCol-1]
            } else if leftCol-1 < 0 {
                population = grid[bottomRow][rightCol] - grid[topRow-1][rightCol]
            } else {
                population = grid[bottomRow][rightCol] - grid[topRow-1][rightCol] - grid[bottomRow][leftCol-1] + grid[topRow-1][leftCol-1]   
            }

        	

        	percentage = float64(population) / float64(grid[ydim-1][xdim-1]) * 100 

        case "-v4":
            // YOUR QUERY CODE FOR PART 4

            topRow, bottomRow, rightCol, leftCol := ydim-north, ydim-south, east-1, west-1

            if topRow-1 < 0 && leftCol-1 < 0 {
                population = grid[bottomRow][rightCol]
            } else if topRow-1 < 0 {
                population = grid[bottomRow][rightCol] - grid[bottomRow][leftCol-1]
            } else if leftCol-1 < 0 {
                population = grid[bottomRow][rightCol] - grid[topRow-1][rightCol]
            } else {
                population = grid[bottomRow][rightCol] - grid[topRow-1][rightCol] - grid[bottomRow][leftCol-1] + grid[topRow-1][leftCol-1]   
            }

        	percentage = float64(population) / float64(grid[ydim-1][xdim-1]) * 100 
        
        case "-v5":
            // YOUR QUERY CODE FOR PART 5

            topRow, bottomRow, rightCol, leftCol := ydim-north, ydim-south, east-1, west-1

            if topRow-1 < 0 && leftCol-1 < 0 {
                population = grid[bottomRow][rightCol]
            } else if topRow-1 < 0 {
                population = grid[bottomRow][rightCol] - grid[bottomRow][leftCol-1]
            } else if leftCol-1 < 0 {
                population = grid[bottomRow][rightCol] - grid[topRow-1][rightCol]
            } else {
                population = grid[bottomRow][rightCol] - grid[topRow-1][rightCol] - grid[bottomRow][leftCol-1] + grid[topRow-1][leftCol-1]   
            }

        	percentage = float64(population) / float64(grid[ydim-1][xdim-1]) * 100 
        
        case "-v6":
            // YOUR QUERY CODE FOR PART 6
           topRow, bottomRow, rightCol, leftCol := ydim-north, ydim-south, east-1, west-1

            if topRow-1 < 0 && leftCol-1 < 0 {
                population = grid[bottomRow][rightCol]
            } else if topRow-1 < 0 {
                population = grid[bottomRow][rightCol] - grid[bottomRow][leftCol-1]
            } else if leftCol-1 < 0 {
                population = grid[bottomRow][rightCol] - grid[topRow-1][rightCol]
            } else {
                population = grid[bottomRow][rightCol] - grid[topRow-1][rightCol] - grid[bottomRow][leftCol-1] + grid[topRow-1][leftCol-1]   
            }

            percentage = float64(population) / float64(grid[ydim-1][xdim-1]) * 100 
        
        }

        fmt.Printf("%v %.2f%%\n", population, percentage)
    }
}




func rowsPrefixSum(grid [][]int, parent chan int) {
    if len(grid) > 1 {
        mid := len(grid)/2
        left := make(chan int)
        right := make(chan int)
        go rowsPrefixSum(grid[:mid], left)
        go rowsPrefixSum(grid[mid:], right)
        <-left
        <-right
    } else if len(grid) == 1 {
        rowchan := make(chan int)
        go rowPrefixSum(grid[0], rowchan)
        <-rowchan
        rowchan<- 0
        <-rowchan
    }
    parent<- 0
}


func colsPrefixSum(grid [][]int, cols []int, parent chan int) {
     if len(cols) > 1 {
        mid := len(cols)/2
        left := make(chan int)
        right := make(chan int)
        go colsPrefixSum(grid, cols[:mid], left)
        go colsPrefixSum(grid, cols[mid:], right)
        <-left
        <-right
    } else {
        colchan := make(chan int)
        go colPrefixSum(grid, cols[0], colchan)
        <-colchan
        colchan<- 0
        <-colchan
    }
    parent<-0
}

func rowPrefixSum(data []int, parent chan int) {
    if len(data) > 1 {
        mid := len(data)/2
        left := make(chan int)
        right := make(chan int)
        go rowPrefixSum(data[:mid], left)
        go rowPrefixSum(data[mid:], right)
        leftSum := <-left
        parent<- leftSum + <-right
        fromLeft := <-parent
        left<- fromLeft
        right<- fromLeft + leftSum
        <-left
        <-right
    } else if len(data)==1 {
        parent<- data[0]
        data[0] += <-parent
    } else {
        parent<- 0
        <-parent
    }
    parent<- 0
}

func colPrefixSum(data [][]int, col int, parent chan int) {
    if len(data) > 1 {
        mid := len(data)/2
        left := make(chan int)
        right := make(chan int)
        go colPrefixSum(data[:mid], col, left)
        go colPrefixSum(data[mid:], col, right)
        leftSum := <-left
        parent<- leftSum + <-right
        fromLeft := <-parent
        left<- fromLeft
        right<- fromLeft + leftSum
        <-left
        <-right
    } else if len(data) == 1 {
        parent<- data[0][col]
        data[0][col] += <-parent
    } else {
        parent<- 0
        <-parent
    }
    parent<- 0
}
