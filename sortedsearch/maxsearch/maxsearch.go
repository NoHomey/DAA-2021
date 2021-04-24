package maxsearch

import (
	"github.com/NoHomey/DAA-2021/sortedsearch/binsearch"
	"github.com/NoHomey/DAA-2021/sortedsearch/darysearch"
	"github.com/NoHomey/DAA-2021/sortedsearch/searcher"
)

func Search(searcher searcher.Searcher, max int) int {
	n := searcher.Count()
	d := n / max
	if d <= 2 {
		return binsearch.Search(searcher)
	}
	return darysearch.Search(searcher, d)
}
