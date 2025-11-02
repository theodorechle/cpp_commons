#ifndef TREE_HPP
#define TREE_HPP

#include <type_traits>

namespace commons {
    template <typename Derived>
    class Node {
        Derived *_parent = nullptr;
        Derived *_child = nullptr;
        Derived *_next = nullptr;
        int _nbChilds = 0;

    public:
        ~Node() {
            delete _child;
            delete _next;
        }

        Derived *parent() { return _parent; }
        const Derived *parent() const { return _parent; }
        void parent(Derived *parent) { this->_parent = parent; }

        Derived *child() { return _child; }
        const Derived *child() const { return _child; }
        void child(Derived *newChild) {
            if (newChild == nullptr) return;
            if (_child == nullptr) {
                _child = newChild;
            }
            else {
                Derived *child = _child;
                for (int i = 1; i < _nbChilds; i++) {
                    child = child->_next;
                }
                child->next(newChild);
            }
            newChild->parent(static_cast<Derived *>(this));
            _nbChilds++;
        }
        void removeChilds() { _child = nullptr; }

        Derived *next() { return _next; }
        const Derived *next() const { return _next; }
        void next(Derived *next) { this->_next = next; }

        int nbChilds() const { return _nbChilds; }
    };
} // namespace commons

#endif // TREE_HPP
