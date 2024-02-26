package main


import "fmt"

type iNode struct {
  value int
  next *iNode
}

type iList struct {
  first *iNode
}

func (il *iList) push(newVal int) {

}

func (il *iList) pop() int {
  return 1
}

func (il *iList) swap(firstIndex, secondIndex int) {
}


func (il *iList) print() {

}

func main() {
  fmt.Println("xD1")
}
