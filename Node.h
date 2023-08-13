#ifndef PUZZLE_NODE_H
#define PUZZLE_NODE_H

#include <string>

//Node represents one piece of puzzle - every attribute carry color and type (smile/eyes)
class Node
{
private:
    int up;
    int right;
    int down;
    int left;

public:
    Node();
    Node(int u, int r, int d, int l);

    int get_up() const;
    int get_right() const;
    int get_down() const;
    int get_left() const;

    std::string typeToString(int type) const;
    std::string printUpNode() const;
    std::string printRightNode() const;
    std::string printDownNode() const;
    std::string printLeftNode() const;

    bool operator!() const;
    Node rotate() const;
};

#endif
