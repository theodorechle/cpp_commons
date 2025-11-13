#ifndef VALUE_NODE_HPP
#define VALUE_NODE_HPP

#include "node.hpp"

namespace commons {
    template <typename T>
    class ValueNode : public Node<ValueNode<T>> {
        T _value;

    public:
        void value(T value) { _value = value; }
        T value() { return _value; }
        const T value() const { return _value; }
    };
} // namespace commons

#endif // VALUE_NODE_HPP