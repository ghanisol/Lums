package main
import "fmt"

func PrefixSum(data, output []int, parent chan int) {
	if len(data) > 1{
		mid := len(data)/2
		left := make(chan int)
		right := make(chan int)
		go PrefixSum(data[:mid], output[:mid], left)
		go PrefixSum(data[mid:], output[mid:], right)
		leftSum := <-left
		parent<- leftSum + <-right
		fromLeft := <-parent
		left<- fromLeft
		right<- fromLeft + leftSum
		<-left
		<-right
	} else if len(data)==1 {
		parent<- data[0]
		output[0] = data[0] + <-parent
	} else {
		parent<- 0
		<-parent
	}
	parent<- 0
}

func  main() {
	data := []int{6, 4, 16, 10, 16, 14, 2, 8}
	output := make([]int, len(data))
	parent := make(chan int)
	go PrefixSum(data, output, parent)
	<-parent	// Sum
	fromLeft := 0
	parent<- fromLeft
	<-parent	// doneZero
	fmt.Printf("%v\n%v\n", data, output)	
}