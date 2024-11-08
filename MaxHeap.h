#ifndef MAXHEAP_H_INCLUDED
#define MAXHEAP_H_INCLUDED

template <typename E>
class MaxHeap {  // Collection is max Heap.  Element 0 is Root
private: EHI<E>* ehi; // Ptr to Orderable array (of hItem ptrs)
  // 0th element is Heap root (maximum)
  int hmax;  // Current size of the EHI (from EHI::getNum())
  int hidx;  // Index to current EHI element
public:
  MaxHeap(size_t size) : ehi(new EHI<E>(size)), hmax(ehi->getNum()), hidx(0) {}
  //MaxHeap(MaxHeap&);
  //~MaxHeap();
  size_t push (hItem<E> *hp) { // Push to bottom, percolate up
    size_t pidx = 0; // Parent item index
    hItem<E> *pp = NULL; // Holding item ptr of parent
    hidx = ehi->append(hp);//Append current element to back. Then percolate up
    hmax = ehi->getNum();
    while (hidx > 0) { // While entry !=root, check if new priority > Parent priority
	pidx = (hidx -1) /2; // Get Parent index
	pp = ehi->get(pidx); // Get ptr to Parent Item
	if ((hp->priority) > (pp->priority)) { // New priority > Parent priority. Swap
	  ehi->set(pidx, hp);
	  ehi->set(hidx, pp);
	  hidx = pidx; // Set current index to parent index, repeat
	} else {
	  break;
	}
      } // while
    return hidx;
  } // push

  hItem<E>*  pop() { // Pops root & repositions lower nodes
    // Pops root & repositions lower nodes
    // Size adjusted (so last node known)

    if (hmax == 0) return NULL;

    size_t pidx = 0; // Parent item index
    hItem<E> *pp = NULL; // Holding item ptr of parent

    hItem<E>* temp = ehi->get(0); // Hold root temporarily

    ehi->remove(0);// Remove root node
    hmax = ehi->getNum();
    hidx = hmax-1;
    hItem<E> *hp;
    while (hidx > 0) { // percolate from the bottom to top
      pidx = (hidx -1);
      hp = ehi->get(hidx);
      pp = ehi->get(pidx); // Get ptr to Parent Item
      if ((hp->priority) > (pp->priority)) { // New priority > Parent priority. Swap
	ehi->set(pidx, hp);
	ehi->set(hidx, pp);
      }
      hidx = pidx; // Set current index to parent index, repeat
    } // while
    return temp;



  }
  // Size adjusted (so last node known)
  hItem<E>*  look() const {  // Peeks at Root Node (No Pop)
    if (hmax == 0) return NULL;
    return ehi->get(0);

  }

  void printHeap() {
    for (size_t i = 0; i < hmax; ++i) {
      std::cout << ehi->get(i)->priority << "\t";
    }
    std::cout << std::endl;
  }

};

#endif // MAXHEAP_H_INCLUDED


