#ifndef LRUCACHE_HPP
#define LRUCACHE_HPP

#include <iostream>
#include <list>
#include <unordered_map> 
#include <algorithm>
#include "DoublyLinkedList.hpp"

/**
 * LRU (Least Recently Used) implementation of a Cache. 
 * 
 * All operations require constant time, including insertions, deletions and LRU tracking. 
 * To achieve this, the idea is the following:
 *   1. We don't store the items directly, but rather ListNodes that point to them, and also store their IDs.
 *   2. We use a hash map that given a key, returns the ListNode keeping the cached item with that ID.
 *   3. We use a double linked list that stores the ListNodes in an LRU fashion, such that the LRU item is 
 *      always the head of the list.
 * 
 * Benefits:
 *   1. O(1) time to insert/remove/peek at items in the list.
 *   2. If a queried ID is already cached, we are able to find the ListNode that keeps it and reposition it
 *      to the tail of the list in O(1), which would not be feasible if we stored the items directly. We would
 *      have to traverse through the list and find the item, before repositioning it, which yields O(N).
*/
template <typename KeyType, typename ValueType>
class LRUCache {
private:
    using TemplateNode = ListNode<KeyType, ValueType>;
    const size_t capacity;

    /**
     * Linked list, with each ListNode containing a pointer to the cached object, along with its ID.
     * This level of abstraction is added to facilitate O(1) time to locate a node in the list, 
     * regardless of its position. 
    */
    DoublyLinkedList<KeyType, ValueType> cachedItems;

    /**
     * Hash Map containing pointers to ListNodes. By using the pointer, combined with our custom 
     * DoublyLinkedList implementation, we don't have to keep track of the position of items in
     * the list (nor update them), because we achieve O(1) access to any ListNode, given a key.
    */
    std::unordered_map<KeyType, TemplateNode*> pointerToNode;

public:
    LRUCache(size_t capacity) : capacity(capacity) {}

    inline ValueType* retrieve(KeyType key, bool& existsInCache) {
        auto it = pointerToNode.find(key);
        if (it == pointerToNode.end()) {
            existsInCache = false;
            return nullptr;
        }

        existsInCache = true;
        cachedItems.spliceToBack(it->second); 
        return it->second->item;
    }

    inline void insert(KeyType key, ValueType* value) {
        if (cachedItems.len() == capacity) {
            evict();
        }

        TemplateNode* newNode = new TemplateNode(key, value);
        pointerToNode[key] = newNode;
        cachedItems.pushBack(newNode);
    }

    inline void evict() {
        auto lruId = cachedItems.front()->id;
        cachedItems.popFront();
        pointerToNode.erase(lruId);
    }

    inline void display() const {
        std::cout << "Cached items:\r\t\t";
        cachedItems.display();
    }
};

#endif