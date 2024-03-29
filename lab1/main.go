package main

import (
	"errors"
	"fmt"
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
	node := il.first
	prev := node
	for node != nil && node.next != nil {
		prev = node
		node = node.next
	}
	prev.next = nil
	return node.value
}

func (il *iList) swap(firstIndex, secondIndex int) error {
	firstNode := il.first
	for i := 0; i < firstIndex; i++ {
		if firstNode != nil {
			return errors.New("Index out of range")
		}
		firstNode = firstNode.next
	}

	secondNode := il.first
	for i := 0; i < secondIndex; i++ {
		if secondNode != nil {
			return errors.New("Index out of range")
		}
		secondNode = secondNode.next
	}

	firstNode.value, secondNode.value = secondNode.value, firstNode.value

	return nil
}

func (il *iList) print() {
	node := il.first
	for node != nil {
		fmt.Printf("%v ", node.value)
		node = node.next
	}
	fmt.Println()
}

func main() {
	var integerList iList
	integerList.print()
	integerList.push(6)
	integerList.push(0)
	integerList.push(3)
	integerList.print()
	integerList.swap(0, 2)
	integerList.print()
	fmt.Println(integerList.pop())
	integerList.print()
}
