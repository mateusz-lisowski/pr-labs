package main


// import "fmt"

type iNode struct {
  value int
  next *iNode
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

func (il *iList) swap(firstIndex, secondIndex int) {
}


func (il *iList) print() {

}

func main() {
  var integerList iList
  integerList.push(6)
  integerList.push(0)
  integerList.push(3)
}
