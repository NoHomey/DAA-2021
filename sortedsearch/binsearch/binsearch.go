package binsearch

import "github.com/NoHomey/DAA-2021/sortedsearch/searcher"

func Search(searcher searcher.Searcher) int {
	// We define that pred(-1) is false and pred(n) is true.
	// Invariant pred(j) is true and pred(i - 1) is false.
	// Condition: If pred(k) is true then pred(k+1) is true and so on.
	n := searcher.Count()
	i, j := 0, n
	for i < j {
		mid := i + (j-i)/2
		if !searcher.Check(mid) {
			i = mid + 1
		} else {
			j = mid
		}
	}
	// Termination: i == j.
	// pred(j) is true thus pred(i) is true and pred(i - 1) is false.
	// Therefore i is the smallest number from 0 to n inclusive
	// such that pred(i) is true.
	return i
}
