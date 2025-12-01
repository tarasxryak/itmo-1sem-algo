package main

type Node struct {
	Val    int
	Height int
	Right  *Node
	Left   *Node
}

func Height(n *Node) int {
	if n == nil {
		return 0
	}
	return n.Height
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func (n *Node) updateHeight() {
	n.Height = 1 + max(n.Right.Height, n.Left.Height)
}

func (n *Node) balanceFactor() int {
	return Height(n.Right) - Height(n.Left)
}
