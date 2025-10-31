#ifndef TREE_HPP
#define TREE_HPP

#include <type_traits>

namespace commons {
    template <typename Derived>
    class Node {
        static_assert(std::is_base_of_v<Node<Derived>, Derived>, "Derived must inherit from Node<T, Derived>");

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
        void setParent(Derived *parent) { this->_parent = parent; }

        Derived *child() { return _child; }
        const Derived *child() const { return _child; }
        void setChild(Derived *newChild) {
            if (newChild == nullptr) return;
            if (_child == nullptr) {
                _child = newChild;
            }
            else {
                Derived *child = _child;
                for (int i = 1; i < _nbChilds; i++) {
                    child = child->_next;
                }
                child->setNext(newChild);
            }
            newChild->setParent(this);
            _nbChilds++;
        }

        Derived *next() { return _next; }
        const Derived *next() const { return _next; }
        void setNext(Derived *next) { this->_next = next; }

        int nbChilds() const { return _nbChilds; }
    };
} // namespace commons

#endif // TREE_HPP
