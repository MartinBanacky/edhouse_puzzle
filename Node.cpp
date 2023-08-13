#include "Node.h"

// Constructors
Node::Node() : up(0), right(0), down(0), left(0) {}

Node::Node(int u, int r, int d, int l)
    : up(u), right(r), left(l), down(d) {}

// Returns the value of the 'up' node
int Node::get_up() const
{
    return this->up;
}

// Returns the value of the 'right' node
int Node::get_right() const
{
    return this->right;
}

// Returns the value of the 'down' node
int Node::get_down() const
{
    return this->down;
}

// Returns the value of the 'left' node
int Node::get_left() const
{
    return this->left;
}

// Converts the type to its string representation for printing
std::string Node::typeToString(int type) const
{
    switch (type)
    {
    case 1:
        return "Rm"; // Red with mouth
    case -1:
        return "Re"; // Red with eyes
    case 2:
        return "Gm"; // Green with mouth
    case -2:
        return "Ge"; // Green with eyes
    case 3:
        return "Bm"; // Blue with mouth
    case -3:
        return "Be"; // Blue with eyes
    case 4:
        return "Ym"; // Yellow with mouth
    case -4:
        return "Ye"; // Yellow with eyes
    default:
        return "  "; // Empty
    }
}

// Returns a string representation of the 'up' node
std::string Node::printUpNode() const
{
    return typeToString(up);
}

// Returns a string representation of the 'right' node
std::string Node::printRightNode() const
{
    return typeToString(right);
}

// Returns a string representation of the 'down' node
std::string Node::printDownNode() const
{
    return typeToString(down);
}

// Returns a string representation of the 'left' node
std::string Node::printLeftNode() const
{
    return typeToString(left);
}

// Operator overload: Returns true if the Node is empty/invalid
bool Node::operator!() const
{
    return (up == 0) || (right == 0) || (down == 0) || (left == 0);
}

// Rotates the Node values (simulating a physical rotation)
Node Node::rotate() const
{
    Node rotatedNode = *this;
    int tmp = rotatedNode.up;
    rotatedNode.up = rotatedNode.right;
    rotatedNode.right = rotatedNode.down;
    rotatedNode.down = rotatedNode.left;
    rotatedNode.left = tmp;
    return rotatedNode;
}
