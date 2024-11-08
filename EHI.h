#ifndef EHI_H_INCLUDED
#define EHI_H_INCLUDED


#include "hItem.h"

#define GROW_POLICY 2

template <typename  E>
class EHI {  // Enhanced Array of Heap Item Pointers (All “resizing” auto-done here)
    size_t _size;
    size_t _capacity;
    hItem<E> **_array = NULL;
    void grow_the_array() {
        hItem<E>** tmp = new hItem<E>*[_capacity*GROW_POLICY];
        for (size_t i = 0; i < _capacity; ++i) {
            tmp[i] = _array[i];
        }
        delete[] _array;
        _array = tmp;
        _capacity=_capacity*GROW_POLICY;
    }
    public:
        EHI(size_t initSz) : _size(0), _capacity(initSz), _array(new hItem<E>*[initSz]) { }
        //EHI(EHI &esi) {};
        ~EHI() { delete[] _array; }  // Copy constructor & Destructor unsigned
        size_t getNum() { return _size;}  // Size of Array
        hItem<E>* get (int index) {
            if (index >= _size) return NULL;
            return _array[index];
        }; // Get elem at index // Return -1 if specified index illegal
        int set(int index, hItem<E> *ep) {
            if (index >= _size) return -1;
            _array[index] = ep;
	    return index;
        } // Overwrite existing elem at index
        size_t append (hItem<E> *ep) {// Append to back. Resize if needed
           if (_size == _capacity)
                grow_the_array();
           _array[_size] = ep;
           ++_size;
           return _size-1;
        }

        size_t insert (size_t index, hItem<E> *ep){ // Insert element, push others back. Resize if needed
            if (index > _size) {
                std::cout << "ERROR: insert attempt out of range, index = "<<index<<"  curent size is "<<_size<<std::endl;
                exit(1);
            }
            if (_size == _capacity)
                grow_the_array();
            //...We need to free the space at the index, shifting all elements right
            for (size_t i = _size; i > index; --i) {
                _array[i] = _array[i-1];
            }
            ++_size;
            return index;
        } // insert

        size_t prepend (hItem<E>* ep) {// Prepend to front, push others back.  Resize if needed
            return insert(0, ep);
        }


        size_t remove (int index){ // Remove element, move others down
        if (index > _size) {
                std::cout << "ERROR: insert attempt out of range, index = "<<index<<"  curent size is "<<_size<<std::endl;
                 exit(1);
            }
        hItem<E>* removed_element = _array[index];


        for (size_t i = index; i < _size; ++i){
            _array[i] = _array[i+1];
        };
        _size--;

        return index;
        }
    };

#endif // EHI_H_INCLUDED
