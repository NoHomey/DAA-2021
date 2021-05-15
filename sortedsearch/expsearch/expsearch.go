package expsearch

import (
	"github.com/NoHomey/DAA-2021/sortedsearch/limitedbinsearch"
	"github.com/NoHomey/DAA-2021/sortedsearch/searcher"
)

func Search(srcher searcher.Searcher) int {
	if srcher.Check(0) {
		return 0
	}
	bound, n := 1, srcher.Count()
	// O(log idx)
	for bound < n && !srcher.Check(bound) {
		bound *= 2
	}
	// idx <= bound ~ 2^ceil(log idx) ~ idx
	left, right := bound/2, min(bound+1, n)
	// right - left = bound - bound / 2 = bound / 2
	//              ~ idx / 2
	// O(log(idx / 2)) = O(log idx)
	return limitedbinsearch.Search(srcher, limitedbinsearch.Limit{
		Left:  left,
		Right: right,
	})
}

func min(x, y int) int {
	if x < y {
		return x
	}
	return y
}
