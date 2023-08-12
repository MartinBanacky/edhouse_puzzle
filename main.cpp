#include <iostream>
#include <string>
#include <functional>

std::string typeToString(int type)
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

class Node
{
    int up;
    int right;
    int down;
    int left;

public:
    Node() : up(0), right(0), down(0), left(0) {}
    Node(int u, int r, int d, int l)
        : up(u), right(r), left(l), down(d) {}

    int get_up() const { return this->up; }
    int get_right() const { return this->right; }
    int get_down() const { return this->down; }
    int get_left() const { return this->left; }

    std::string printUpNode() const
    {
        return typeToString(up);
    }
    std::string printRightNode() const
    {
        return typeToString(right);
    }
    std::string printDownNode() const
    {
        return typeToString(down);
    }
    std::string printLeftNode() const
    {
        return typeToString(left);
    }

    // Overloading the ! operator
    bool operator!() const
    {
        return (up == 0) && (right == 0) && (down == 0) && (left == 0);
    }
};

/// Function to print grid
void printNodes(Node *node_array)
{
    for (int i = 0; i < 3; ++i)
    {
        if (i == 0)
            std::cout << std::string(28, '-') << std::endl;
        for (int j = 0; j < 3; j++)
        {

            if (j == 0)
            {
                std::cout << "|   " << node_array[i * 3].printUpNode() << "   |   "
                          << node_array[i * 3 + 1].printUpNode() << "   |   " << node_array[i * 3 + 2].printUpNode() << "   |" << std::endl;
            }

            if (j == 1)
            {
                std::cout << "| " << node_array[i * 3].printLeftNode() << "  " << node_array[i * 3].printRightNode() << " | "
                          << node_array[i * 3 + 1].printLeftNode() << "  " << node_array[i * 3 + 1].printRightNode() << " | "
                          << node_array[i * 3 + 2].printLeftNode() << "  " << node_array[i * 3 + 2].printRightNode() << " | " << std::endl;
            }

            if (j == 2)
            {
                std::cout << "|   " << node_array[i * 3].printDownNode() << "   |   "
                          << node_array[i * 3 + 1].printDownNode() << "   |   " << node_array[i * 3 + 2].printDownNode() << "   |" << std::endl;
            }
        }
        std::cout << std::string(28, '-') << std::endl;
    }
}

bool match_edge(Node grid[], int x, int y, std::function<int(const Node &)> get_edge, int new_edge, int grid_width, int grid_height)
{
    int empty = x + (y * grid_width);
    return (x < 0) || (y < 0) || (x >= grid_width) || (y >= grid_height) || (empty >= grid_width * grid_height) || (!grid[empty]) || ((get_edge(grid[empty]) + new_edge) == 0);
}

auto getUpFunc = [](const Node &node)
{ return node.get_up(); };
auto getRightFunc = [](const Node &node)
{ return node.get_right(); };
auto getDownFunc = [](const Node &node)
{ return node.get_down(); };
auto getLeftFunc = [](const Node &node)
{ return node.get_left(); };

bool insert_node(Node grid[], Node new_node, int x, int y, int grid_width, int grid_height)
{
    return (match_edge(grid, (x - 1), y, getRightFunc, new_node.get_left(), 3, 3)) &&
           (match_edge(grid, (x + 1), y, getLeftFunc, new_node.get_right(), 3, 3)) &&
           (match_edge(grid, x, (y - 1), getDownFunc, new_node.get_up(), 3, 3)) &&
           (match_edge(grid, x, (y + 1), getUpFunc, new_node.get_down(), 3, 3));
}

int main()
{
    Node nodes[9] = {
        Node(1, 4, -1, -2),
        Node(-3, -4, 3, 2),
        Node(-1, -4, 3, 4),
        Node(1, -3, -2, 1),
        Node(-3, -2, 1, 4),
        Node(3, 4, -1, -2),
        Node(3, 2, -4, -3),
        Node(-3, 1, 3, -4),
        Node(-4, 1, 2, -2)};

    Node nodes_test[9];

    nodes_test[0] = {1, 1, 1, 1};
    nodes_test[1] = {-2, -2, -2, -2};
    Node test = {3, 3, 3, 3};

    printNodes(nodes);
    // printNodes(nodes_test);

    // if (insert_node(nodes_test, test, 2, 0, 3, 3))
    // {
    //     std::cout << "Yes" << std::endl;
    // }
    // else
    // {
    //     std::cout << "No" << std::endl;
    // }
    return 0;
}
