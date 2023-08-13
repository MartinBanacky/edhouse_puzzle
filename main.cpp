#include "Utils.h"
#include "Node.h"
#include <iostream>
#include <vector>

int main()
{
    // MAX SIZE OF GRID 3x3
    //  1 = red smile
    //-1 = red eyes
    //  2 = green smile
    //-2 = green eyes
    //  3 = blue smile
    //-3 = blue eyes
    //  4 = yellow smile
    //-4 = yellow eyes

    // One square from puzzle(original.png) is represented here as Node
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

    // TEST1 - not solvable
    std::vector<Node> nodes2 = {
        Node(1, 1, 1, 1),
        Node(1, 1, 1, 1),
        Node(1, 1, 1, 1),
        Node(1, 1, 1, 1),
        Node(1, 1, 1, 1),
        Node(4, 4, 4, 4),
        Node(4, 4, 4, 4),
        Node(4, 4, 4, 4),
        Node(4, 4, 4, 4)};

    // TEST2 - end immedietely if blank Node is in input
    std::vector<Node> nodes3 = {
        Node(),
        Node(),
        Node(),
        Node(),
        Node(),
        Node(),
        Node(),
        Node(),
        Node()};

    std::cout << "Puzzle1:" << std::endl;
    solve_puzzle(nodes);

    std::cout << "Puzzle2:" << std::endl;
    solve_puzzle(nodes2);

    std::cout << "Puzzle3:" << std::endl;
    solve_puzzle(nodes3);

    return 0;
}