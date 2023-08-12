#include <iostream>
#include <string>

std::string typeToString(int type)
{
    switch (type)
    {
    case 1:
        return "r1";
    case -1:
        return "r2";
    case 2:
        return "g1";
    case -2:
        return "g2";
    case 3:
        return "b1";
    case -3:
        return "b2";
    case 4:
        return "y1";
    case -4:
        return "y2";
    default:
        return "unknown";
    }
}

struct Smile
{
    int type;

    Smile(int t) : type(t) {}
};

class Node
{
    Smile up;
    Smile right;
    Smile down;
    Smile left;

public:
    Node(const Smile &u, const Smile &r, const Smile &d, const Smile &l)
        : up(u), right(r), left(l), down(d) {}

    std::string printUpNode() const
    {
        return typeToString(up.type);
    }
    std::string printRightNode() const
    {
        return typeToString(right.type);
    }
    std::string printDownNode() const
    {
        return typeToString(down.type);
    }
    std::string printLeftNode() const
    {
        return typeToString(left.type);
    }
};

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

int main()
{
    Node nodes[9] = {
        Node({1}, {4}, {-1}, {-2}),
        Node({-3}, {-4}, {3}, {2}),
        Node({-1}, {-4}, {3}, {4}),
        Node({1}, {-3}, {-2}, {1}),
        Node({-3}, {-2}, {1}, {4}),
        Node({3}, {4}, {-1}, {-2}),
        Node({3}, {2}, {-4}, {-3}),
        Node({-3}, {1}, {3}, {-4}),
        Node({-4}, {1}, {2}, {-2})};

    printNodes(nodes);

    return 0;
}
