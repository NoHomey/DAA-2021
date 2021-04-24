package expsearch

import (
	"github.com/NoHomey/DAA-2021/sortedsearch/darysearch"
	"github.com/NoHomey/DAA-2021/sortedsearch/searcher"
	"github.com/NoHomey/DAA-2021/sortedsearch/util"
)

func Search(srcher searcher.Searcher) int {
	bound, n := 1, srcher.Count()
	// O(log idx)
	for bound < n && !srcher.Check(bound) {
		bound *= 2
	}
	// idx <= bound ~ 2^ceil(log idx) ~ idx
	left, right := bound/2, min(bound, n)
	// right - left = bound - bound / 2 = bound / 2
	//              ~ idx / 2
	// O(log(idx / 2)) = O(log idx)
	res := darysearch.Search(searcher.Shifted{
		Left:      left,
		Right:     right,
		CheckFunc: srcher.Check,
	}, 4)
	// Theta(1)
	return util.ShiftResult(res, left, right, n)
}

func min(x, y int) int {
	if x < y {
		return x
	}
	return y
}
