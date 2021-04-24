package util

func ShiftResult(res int, left int, right int, end int) int {
	switch res {
	case -1:
		return -1
	case right - left:
		return end
	default:
		return left + res
	}
}
