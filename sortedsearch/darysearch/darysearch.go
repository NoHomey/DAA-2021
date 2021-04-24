package darysearch

import (
	"github.com/NoHomey/DAA-2021/sortedsearch/binsearch"
	"github.com/NoHomey/DAA-2021/sortedsearch/searcher"
	"github.com/NoHomey/DAA-2021/sortedsearch/util"
)

func Search(srcher searcher.Searcher, d int) int {
	// pred is searcher.Check.
	// We define that pred(-1) is false and pred(n) is true.
	// Invariant pred(j) is true and pred(i - 1) is false.
	// Condition: If pred(k) is true then pred(k+1) is true and so on.
	n := srcher.Count()
	i, j := 0, n
	for i < j {
		step := (j - i) / d
		if step <= 1 {
			res := binsearch.Search(searcher.Shifted{
				Left:      i,
				Right:     j,
				CheckFunc: srcher.Check,
			})
			return util.ShiftResult(res, i, j, n)
		}
		blockSearcher := block{
			check:    srcher.Check,
			full:     d,
			lastFull: i + d*step,
			begin:    i,
			end:      j,
			size:     step,
		}
		res, count := binsearch.Search(blockSearcher), blockSearcher.Count()
		if res == -1 {
			return -1
		}
		if res == count {
			return n
		}
		if (j-i)%d > 0 && res == count-1 {
			i = blockSearcher.lastFull
		} else {
			i = i + res*step
			j = i + step + 1 //one past the range, in the begin j is equal to n
		}
	}
	return 0
}

type block struct {
	check    func(int) bool
	full     int
	lastFull int
	begin    int
	end      int
	size     int
}

func (searcher block) Count() int {
	if searcher.lastFull != searcher.end {
		return searcher.full + 1
	}
	return searcher.full
}

func (searcher block) Check(idx int) bool {
	shifted := searcher.begin + (idx+1)*searcher.size
	if searcher.lastFull != searcher.end && searcher.full == idx {
		// for the end always return true to keep the invariant for binsearch.Search
		return true
	}
	return searcher.check(shifted)
}

// func (this Type) Method(args...) ReturnType

// Time complexity: Theta(lg(d) * log_d(n) + lg(2d - 1))
// Space complexity: Theta(1)
