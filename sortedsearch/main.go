package main

import (
	"fmt"

	"github.com/NoHomey/DAA-2021/sortedsearch/expsearch"
)

type IntAscOrdSearcher struct {
	Array   []int
	Element int
}

func (s IntAscOrdSearcher) Check(i int) bool {
	return s.Array[i] >= s.Element
}

func (s IntAscOrdSearcher) Count() int {
	return len(s.Array)
}

func searchElement(arr []int, x int) bool {
	idx := expsearch.Search(IntAscOrdSearcher{
		Array:   arr,
		Element: x,
	})
	return 0 <= idx && idx < len(arr) && arr[idx] == x
}

func main() {
	arr := []int{1, 3, 3, 5, 7, 8, 8, 8, 9, 10, 11, 11, 13}
	fmt.Println(searchElement(arr, -4))
	fmt.Println(searchElement(arr, 14))
	fmt.Println(searchElement(arr, 4))
	fmt.Println(searchElement(arr, 5))
	fmt.Println(searchElement(arr, 11))
	fmt.Println(searchElement(arr, 8))
	fmt.Println(searchElement(arr, 9))
	fmt.Println(searchElement(arr, 10))
	fmt.Println(searchElement(arr, 1))
	fmt.Println(searchElement(arr, 13))
	fmt.Println(searchElement(arr, 12))
}
