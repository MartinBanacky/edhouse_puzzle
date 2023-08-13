#include "Node.h"

// Constructors
Node::Node() : up(0), right(0), down(0), left(0) {}

Node::Node(int u, int r, int d, int l)
    : up(u), right(r), left(l), down(d) {}

// Returns up value
int Node::get_up() const
{
    return this->up;
}

// Returns right value
int Node::get_right() const
{
    return this->right;
}

//Returns down value
int Node::get_down() const
{
    return this->down;
}

//Returns left value
int Node::get_left() const
{
    return this->left;
}

//Function converts type to its string represation
std::string Node::typeToString(int type) const
{
    switch (type)
    {
    case 1:
        return "r1"; // red with mouth
    case -1:
        return "r2"; // red with eyes
    case 2:
        return "g1"; // green with mouth
    case -2:
        return "g2"; // green with eyes
    case 3:
        return "b1"; // blue with mouth
    case -3:
        return "b2"; // blue with eyes
    case 4:
        return "y1"; // yellow with mouth
    case -4:
        return "y2"; // yellow with eyes
    default:
        return "  ";
    }
}

//Prints
std::string Node::printUpNode() const
{
    return typeToString(up);
}

std::string Node::printRightNode() const
{
    return typeToString(right);
}

std::string Node::printDownNode() const
{
    return typeToString(down);
}

std::string Node::printLeftNode() const
{
    return typeToString(left);
}

//operator overload - one or more zero values == empty/invalid
bool Node::operator!() const
{
    return (up == 0) || (right == 0) || (down == 0) || (left == 0);
}

//Func rotates Node values (like irl rotate)
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