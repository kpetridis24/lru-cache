#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

template <typename KeyType, typename ItemType>
struct ListNode {
    KeyType id;
    ItemType* item;
    ListNode* prev;
    ListNode* next;
    ListNode(KeyType id, ItemType* item) : id(id), item(item), prev(nullptr), next(nullptr) {}
};

template <typename KeyType, typename ItemType>
class DoublyLinkedList {
private:
    using TemplateNode = ListNode<KeyType, ItemType>;

    size_t length;
    TemplateNode* head;
    TemplateNode* tail;

public:
    DoublyLinkedList() : length(0), head(nullptr), tail(nullptr) {}

    inline size_t len() const {
        return length;
    } 

    inline TemplateNode* front() const {
        return head;
    }

    inline TemplateNode* back() const {
        return tail;
    }

    inline void pushBack(TemplateNode* newNode) {
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    inline void popFront() {
        if (head == nullptr) {
            return;
        }

        TemplateNode* nodeToRemove = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }

        delete nodeToRemove;
        length--;
    }

    inline void spliceToBack(TemplateNode* nodeToMove){
        if (nodeToMove == tail) {
            return;
        }

        if (nodeToMove == head) {
            head = nodeToMove->next;
            head->prev = nullptr;
        } else {
            nodeToMove->prev->next = nodeToMove->next;
            nodeToMove->next->prev = nodeToMove->prev;
        }
        
        tail->next = nodeToMove;
        nodeToMove->prev = tail;
        nodeToMove->next = nullptr;
        tail = nodeToMove;
    }

    inline void display() const {
        if (length == 0) {
            std::cout << "empty" << "\n";
            return;
        }
        TemplateNode* node = head;
        while (node != nullptr) {
            std::cout << node->id << " ";
            node = node->next;
        }
        std::cout << std::endl;
    }

};

#endif