#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>
#include <type_traits>

namespace commons {
    /*
    A basic node class to create trees.
    The template parameter is to be able to take and return the child class type directly instead of needing a cast for every call.
    */
    template <typename Derived>
    class Node {
        Derived *_parent = nullptr;
        Derived *_child = nullptr;
        Derived *_next = nullptr;

    protected:
        virtual std::string debugValue() const { return ""; }

    public:
        Node(Derived *child = nullptr, Derived *next = nullptr) : _child{child}, _next{next} {}

        virtual ~Node() {
            delete _child;
            delete _next;
        }

        Derived *parent() { return _parent; }
        const Derived *parent() const { return _parent; }
        Derived *parent(Derived *parent) {
            this->_parent = parent;
            return parent;
        }

        Derived *child() { return _child; }
        const Derived *child() const { return _child; }
        Derived *addChild(Derived *newChild) {
            if (newChild == nullptr) return nullptr;
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
            return newChild;
        }
        void removeChilds() { _child = nullptr; }

        Derived *next() { return _next; }
        const Derived *next() const { return _next; }
        Derived *next(Derived *next) {
            _next = next;
            if (_next != nullptr) _next->parent(parent());
            return next;
        }

        int nbChilds() const {
            size_t nbChilds = 0;
            Derived *child = _child;
            while (child != nullptr) {
                nbChilds++;
                child = child->_next;
            }
            return nbChilds;
        }

        Derived *getLastChild() {
            Derived *childNode = child();
            Derived *nextChild = childNode;
            while (nextChild != nullptr) {
                childNode = nextChild;
                nextChild = nextChild->next();
            }
            return childNode;
        }

        Derived *getSpecificChild(int childNumber) {
            Derived *childNode = child();
            childNumber--;

            while (childNumber > 0) {
                if (childNode == nullptr) return nullptr;
                childNode = childNode->next();
                childNumber--;
            }
            return childNode;
        }

        void debugDisplay(std::ostream &flow = std::cerr, int indent = 0) const {
            for (int i = 0; i < indent; i++) {
                flow << "\t";
            }
            flow << debugValue() << "\n";
            const Derived *elementChild = child();
            while (elementChild) {
                elementChild->debugDisplay(flow, indent + 1);
                elementChild = elementChild->next();
            }
        };
    };
} // namespace commons

#endif // NODE_HPP
