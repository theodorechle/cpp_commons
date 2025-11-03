#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <string>
#include <type_traits>

namespace commons {
    template <typename Derived>
    class Node {
        Derived *_parent = nullptr;
        Derived *_child = nullptr;
        Derived *_next = nullptr;

        virtual std::string debugValue() const { return ""; }

    public:
        virtual ~Node() {
            delete _child;
            delete _next;
        }

        Derived *parent() { return _parent; }
        const Derived *parent() const { return _parent; }
        void parent(Derived *parent) { this->_parent = parent; }

        Derived *child() { return _child; }
        const Derived *child() const { return _child; }
        void addChild(Derived *newChild) {
            if (newChild == nullptr) return;
            if (_child == nullptr) {
                _child = newChild;
            }
            else {
                Derived *child;
                Derived *nextChild = _child;
                do {
                    child = nextChild;
                    nextChild = nextChild->next();
                } while (nextChild != nullptr);
                child->next(newChild);
            }
            newChild->parent(static_cast<Derived *>(this));
        }
        void removeChilds() { _child = nullptr; }

        Derived *next() { return _next; }
        const Derived *next() const { return _next; }
        void next(Derived *next) { this->_next = next; }

        int nbChilds() const {
            size_t nbChilds = 0;
            Derived *child = _child;
            while (child != nullptr) {
                nbChilds++;
                child = child->_next;
            }
            return nbChilds;
        }

        void debugDisplay(int indent) const {
            for (int i = 0; i < indent; i++) {
                std::cerr << "\t";
            }
            std::cerr << debugValue() << "\n";
            const Derived *elementChild = child();
            while (elementChild) {
                elementChild->debugDisplay(indent + 1);
                elementChild = elementChild->next();
            }
        };
    };
} // namespace commons

#endif // TREE_HPP
