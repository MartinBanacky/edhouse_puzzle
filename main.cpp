#include <iostream>
#include <string>
#include <functional>
#include <cmath>
#include <vector>

int counter_nodes = 0;

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

    Node rotate() const
    {
        Node rotatedNode = *this; // Create a copy of the current node
        int tmp = rotatedNode.up;
        rotatedNode.up = rotatedNode.right;
        rotatedNode.right = rotatedNode.down;
        rotatedNode.down = rotatedNode.left;
        rotatedNode.left = tmp;
        return rotatedNode;
    }
};

/// Function to print grid
void printNodes(std::vector<Node> node_array)
{
    if (node_array.empty())
        return;
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

bool match_edge(std::vector<Node> grid, int x, int y, const std::function<int(const Node &)> &get_edge, int new_edge, int grid_width, int grid_height)
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

bool insert_node(const std::vector<Node> &grid, Node new_node, int x, int y, int grid_width, int grid_height)
{
    return (match_edge(grid, (x - 1), y, getRightFunc, new_node.get_left(), 3, 3)) &&
           (match_edge(grid, (x + 1), y, getLeftFunc, new_node.get_right(), 3, 3)) &&
           (match_edge(grid, x, (y - 1), getDownFunc, new_node.get_up(), 3, 3)) &&
           (match_edge(grid, x, (y + 1), getUpFunc, new_node.get_down(), 3, 3));
}

void try_node(std::vector<Node> sorted_grid, Node candidate, std::vector<Node> candidates, int position, int grid_width, int grid_height);

void sort(const std::vector<Node> &sorted_grid, std::vector<Node> candidates, int position, int grid_width, int grid_height)
{
    if (candidates.empty())
    {
        std::cout << counter_nodes << std::endl;
        printNodes(sorted_grid);
        exit(0); // comment this if full solution is needed
        // return;
    }
    for (int i = 0; i < 9 - position; i++)
    {
        Node to_remove = candidates[i];
        candidates.erase(candidates.begin() + i);
        try_node(sorted_grid, to_remove, candidates, position, grid_width, grid_height);
        try_node(sorted_grid, to_remove.rotate(), candidates, position, grid_width, grid_height);
        try_node(sorted_grid, to_remove.rotate().rotate(), candidates, position, grid_width, grid_height);
        try_node(sorted_grid, to_remove.rotate().rotate().rotate(), candidates, position, grid_width, grid_height);
        candidates.insert(candidates.begin() + i, to_remove);
    }
}

void try_node(std::vector<Node> sorted_grid, Node candidate, std::vector<Node> candidates, int position, int grid_width, int grid_height)
{
    counter_nodes++;
    if (insert_node(sorted_grid, candidate, (position % grid_width), std::floor(position / grid_width), grid_width, grid_height))
    {
        // printNodes(sorted_grid);
        // std::cout << "Hello" << std::endl;
        sorted_grid[position] = candidate;
        sort(sorted_grid, candidates, position + 1, grid_width, grid_height);
        sorted_grid[position] = Node();
    }
}

int main()
{
    std::vector<Node> nodes = {
        Node(1, 4, -1, -2),
        Node(-3, -4, 3, 2),
        Node(-1, -4, 3, 4),
        Node(1, -3, -2, 1),
        Node(-3, -2, 1, 4),
        Node(3, 4, -1, -2),
        Node(3, 2, -4, -3),
        Node(-3, 1, 3, -4),
        Node(-4, 1, 2, -2)};

    std::vector<Node> sorted_grid(9);

    sort(sorted_grid, nodes, 0, 3, 3);

    // std::vector<Node> nodes_test(9);
    // nodes_test[0] = {1, 1, 1, 1};
    // nodes_test[1] = {-2, -2, -2, -1};
    // Node test = {2, 3, 3, 3};
    // printNodes(nodes);
    // printNodes(sorted_grid);

    // if (insert_node(nodes_test, test, 1, 1, 3, 3))
    // {
    //     nodes_test[4] = test;
    //     std::cout << "Yes" << std::endl;
    // }
    // else
    // {
    //     std::cout << "No" << std::endl;
    // }

    // printNodes(nodes_test);
    return 0;
}