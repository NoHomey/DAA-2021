package main

import (
	"fmt"

	"github.com/NoHomey/DAA-2021/sortedsearch/maxsearch"
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
	idx := maxsearch.Search(IntAscOrdSearcher{
		Array:   arr,
		Element: x,
	}, 4)
	return idx < len(arr) && arr[idx] == x
}

func main() {
	arr := []int{1, 3, 3, 5, 7, 8, 8, 8, 9, 10, 11, 11, 13}
	t := []test{
		{-4, false},
		{14, false},
		{4, false},
		{5, true},
		{11, true},
		{8, true},
		{9, true},
		{10, true},
		{1, true},
		{13, true},
		{12, false},
	}
	for i, c := range t {
		res := searchElement(arr, c.elem)
		if res != c.res {
			fmt.Println(i, c.elem, c.res, res)
		}
	}
}

type test struct {
	elem int
	res  bool
}
