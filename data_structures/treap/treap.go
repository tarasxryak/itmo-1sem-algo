package main

import (
	"fmt"
	"math/rand"
	"time"
)

func init() {
	rand.Seed(time.Now().Unix())
}

type Node struct {
	Val      int
	Priority int
	Right    *Node
	Left     *Node
}

func newNode(val int) *Node {
	return &Node{
		Val:      val,
		Priority: rand.Int(),
	}
}

func Split(t *Node, key int) (l, r *Node) {
	if t == nil {
		return nil, nil
	}
	if t.Val <= key {
		splitL, splitR := Split(t.Right, key)
		t.Right = splitL
		return t, splitR
	} else {
		splitL, splitR := Split(t.Left, key)
		t.Left = splitR
		return splitL, t
	}
}

func Merge(l, r *Node) *Node {
	if l == nil {
		return r
	}
	if r == nil {
		return l
	}

	if l.Priority > r.Priority {
		l.Right = Merge(l.Right, r)
		return l
	} else {
		r.Left = Merge(r.Left, l)
		return r
	}
}

func (n *Node) Exists(val int) bool {
	if n == nil {
		return false
	}
	if n.Val == val {
		return true
	}
	if n.Val > val {
		return n.Left.Exists(val)
	}
	return n.Right.Exists(val)
}

func (n *Node) Next(val int) (int, bool) {
	var res int
	found := false
	current := n
	for current != nil {
		if current.Val > val {
			res = current.Val
			found = true
			current = current.Left
		} else {
			current = current.Right
		}
	}
	return res, found
}

func (n *Node) Erase(val int) *Node {
	less, greaterOrEqual := Split(n, val-1)
	_, greater := Split(greaterOrEqual, val)

	return Merge(less, greater)
}

func main() {
	var a *int = nil

	fmt.Print(*a)
}
