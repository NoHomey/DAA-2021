package searcher

type Searcher interface {
	Check(int) bool
	Count() int
}

type Shifted struct {
	Left      int
	Right     int
	CheckFunc func(int) bool
}

func (searcher Shifted) Count() int {
	return searcher.Right - searcher.Left
}

//func (this Type) MethodName(args...) ReturnType
func (searcher Shifted) Check(idx int) bool {
	return searcher.CheckFunc(searcher.Left + idx)
}
