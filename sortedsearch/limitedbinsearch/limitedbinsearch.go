package limitedbinsearch

import (
	"github.com/NoHomey/DAA-2021/sortedsearch/binsearch"
	"github.com/NoHomey/DAA-2021/sortedsearch/searcher"
)

type Limit struct {
	Left  int
	Right int
}

func Search(searcher searcher.Searcher, limit Limit) int {
	res := binsearch.Search(limited{
		Limit:     limit,
		CheckFunc: searcher.Check,
	})
	return shiftResult(res, limit.Left, limit.Right, searcher.Count())
}

type limited struct {
	Limit
	CheckFunc func(int) bool
}

func (searcher limited) Count() int {
	return searcher.Limit.Right - searcher.Limit.Left
}

func (searcher limited) Check(idx int) bool {
	return searcher.CheckFunc(searcher.Left + idx)
}

func shiftResult(res int, left int, right int, end int) int {
	shifted := left + res
	if shifted > right {
		return end
	}
	return shifted
}
