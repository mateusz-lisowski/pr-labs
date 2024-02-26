package main

import (
	"errors"
)

type iNode struct {
	value int
	next  *iNode
}

type iList struct {
	first *iNode
}

func (il *iList) push(newVal int) {
	var newNode iNode
	newNode.value = newVal
	newNode.next = il.first
	il.first = &newNode
}

func (il *iList) pop() int {
	np := il.first
	prev := np
	for np.next != nil {
		prev = np
		np = np.next
	}
	prev.next = nil
	return np.value
}

func (il *iList) swap(firstIndex, secondIndex int) error {
	firstNode := il.first
	for i := 0; i < firstIndex; i++ {
		if firstNode.next == nil {
			return errors.New("Index out of range")
		}
		firstNode = firstNode.next
	}

	secondNode := il.first
	for i := 0; i < secondIndex; i++ {
		if secondNode.next == nil {
			return errors.New("Index out of range")
		}
		secondNode = secondNode.next
	}

	firstNode.value, secondNode.value = secondNode.value, firstNode.value

	return nil
}

func (il *iList) print() {

}

func main() {
	var integerList iList
	integerList.push(6)
	integerList.push(0)
	integerList.push(3)
}
