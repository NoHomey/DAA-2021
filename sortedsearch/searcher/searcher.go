package searcher

type Searcher interface {
	Check(int) bool
	Count() int
}
