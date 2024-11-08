#ifndef HITEM_H_INCLUDED
#define HITEM_H_INCLUDED


// hItem:  Array Heap Item
template <typename E>
struct hItem {    // Element being “heaped”
    int priority;    // Priority of Node (~ the Array Item “key”)
    E* studp;  // Ptr to Thing represented in Heap
};
#endif // HITEM_H_INCLUDED

