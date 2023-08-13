#ifndef PUZZLE_NODE_H
#define PUZZLE_NODE_H

#include <string>

// Node represents a puzzle piece, carrying color and type attributes (smile/eyes)
class Node
{
private:
    int up;
    int right;
    int down;
    int left;

public:
    // Constructors
    Node();
    Node(int u, int r, int d, int l);

    // Accessor methods
    int get_up() const;
    int get_right() const;
    int get_down() const;
    int get_left() const;

    // Utility methods (Node)
    std::string typeToString(int type) const;
    std::string printUpNode() const;
    std::string printRightNode() const;
    std::string printDownNode() const;
    std::string printLeftNode() const;
    Node rotate() const;

    // Operator overloads
    bool operator!() const;
    
};

#endif
