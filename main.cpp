#include "Utils.h"
#include "Node.h"
#include <iostream>
#include <vector>

int main()
{
    // Define puzzle piece meanings:
    //  1 = red smile
    // -1 = red eyes
    //  2 = green smile
    // -2 = green eyes
    //  3 = blue smile
    // -3 = blue eyes
    //  4 = yellow smile
    // -4 = yellow eyes

    // Define the puzzle pieces using the 'Node' class, each representing a square from the puzzle (original.png)
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

    // Test Case 1 - Not solvable configuration
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

    // Test Case 2 - Handling an immediate end if a blank 'Node' is present in the input
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

    // Solving and printing puzzle solutions
    std::cout << "Puzzle 1:" << std::endl;
    solve_puzzle(nodes);

    std::cout << "Puzzle 2:" << std::endl;
    solve_puzzle(nodes2);

    std::cout << "Puzzle 3:" << std::endl;
    solve_puzzle(nodes3);

    return 0;
}
