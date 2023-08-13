#include "Utils.h"
#include "Node.h"
#include <iostream>
#include <cmath>

// Counter to keep track of the number of combinations tried during puzzle solving.
int counter_comb = 0;

// Function pointers for getting specific edges from a Node.
// These lambda functions are used to retrieve the values of the edges (up, right, down, left) of a given Node.
// For instance, 'getUpFunc' retrieves the value of the upper edge of a Node by calling 'node.get_up()'.
auto getUpFunc = [](const Node &node)
{
    return node.get_up();
};

auto getRightFunc = [](const Node &node)
{
    return node.get_right();
};

auto getDownFunc = [](const Node &node)
{
    return node.get_down();
};

auto getLeftFunc = [](const Node &node)
{
    return node.get_left();
};

// Func to print grid
void printNodes(const std::vector<Node> &node_array)
{
    if (node_array.empty())
        return;
    // Iterate through rows of the puzzle grid.
    for (int i = 0; i < 3; ++i)
    {
        // Print horizontal separator lines between rows.
        if (i == 0)
            std::cout << std::string(28, '-') << std::endl;

        // Iterate through columns of the puzzle grid.
        for (int j = 0; j < 3; j++)
        {
            // Print the upper edge values of each node in the row.
            if (j == 0)
            {
                std::cout << "|   " << node_array[i * 3].printUpNode() << "   |   "
                          << node_array[i * 3 + 1].printUpNode() << "   |   " << node_array[i * 3 + 2].printUpNode() << "   |" << std::endl;
            }

            // Print the left and right edge values of each node in the row.
            if (j == 1)
            {
                std::cout << "| " << node_array[i * 3].printLeftNode() << "  " << node_array[i * 3].printRightNode() << " | "
                          << node_array[i * 3 + 1].printLeftNode() << "  " << node_array[i * 3 + 1].printRightNode() << " | "
                          << node_array[i * 3 + 2].printLeftNode() << "  " << node_array[i * 3 + 2].printRightNode() << " | " << std::endl;
            }

            // Print the lower edge values of each node in the row.
            if (j == 2)
            {
                std::cout << "|   " << node_array[i * 3].printDownNode() << "   |   "
                          << node_array[i * 3 + 1].printDownNode() << "   |   " << node_array[i * 3 + 2].printDownNode() << "   |" << std::endl;
            }
        }

        // Print horizontal separator lines between rows.
        std::cout << std::string(28, '-') << std::endl;
    }
}

// This function validates whether the edge of a new puzzle piece can be inserted at a specified position.
// Parameters:
// - grid: The current grid configuration.
// - x: X-coordinate of the puzzle position to compare with.
// - y: Y-coordinate of the puzzle position to compare with.
// - get_edge: A function that retrieves a specific edge value from a Node.
// - new_edge: The edge value of the new puzzle piece.
// - grid_width: Width of the puzzle grid.
// - grid_height: Height of the puzzle grid.
// Returns:
// - True if the new edge can be inserted at the specified position, otherwise, false.
bool match_edge(const std::vector<Node> &grid, int x, int y, const std::function<int(const Node &)> &get_edge, int new_edge, int grid_width, int grid_height)
{
    // empty = can be 0-8 (position in vector - in grid)
    int empty = x + (y * grid_width);
    // x == -1 (left side), x >= grid_width (right side), y == -1 TOP, y >= grid_height BOTTOM, puzzle empty -> nothing to compare, last is compare if == 0 match (OK)
    return (x < 0) || (y < 0) || (x >= grid_width) || (y >= grid_height) || (empty >= grid_width * grid_height) || (!grid[empty]) || ((get_edge(grid[empty]) + new_edge) == 0);
}

// Function to validate the insertion of a new puzzle node into a specific position on the grid.
// This function ensures that the edges of a new puzzle node are compatible with adjacent edges of neighboring nodes.
// Parameters:
// - grid: The current grid configuration.
// - new_node: The new puzzle node to be inserted.
// - x: X-coordinate of the puzzle position to insert.
// - y: Y-coordinate of the puzzle position to insert.
// - grid_width: Width of the puzzle grid.
// - grid_height: Height of the puzzle grid.
// Returns:
// - True if the new node's edges can be inserted at the specified position without violating compatibility; otherwise, false.
bool insert_node(const std::vector<Node> &grid, Node new_node, int x, int y, int grid_width, int grid_height)
{
    return (match_edge(grid, (x - 1), y, getRightFunc, new_node.get_left(), 3, 3)) &&
           (match_edge(grid, (x + 1), y, getLeftFunc, new_node.get_right(), 3, 3)) &&
           (match_edge(grid, x, (y - 1), getDownFunc, new_node.get_up(), 3, 3)) &&
           (match_edge(grid, x, (y + 1), getUpFunc, new_node.get_down(), 3, 3));
}

// Attempt to insert a puzzle candidate into a specified position on the grid.
// This function checks if a given candidate puzzle node can be inserted at a specific position,
// considering the current configuration of the sorted grid and the remaining candidates.
// Parameters:
// - sorted_grid: The current grid configuration with some nodes already inserted.
// - candidate: The puzzle node candidate to be inserted.
// - candidates: The list of remaining puzzle candidates.
// - position: The index (0-8) in the vector where the candidate will be inserted.
// - grid_width: Width of the puzzle grid.
// - grid_height: Height of the puzzle grid.
// Counter Effect:
// - Increments the counter for the total number of combinations attempted.
void try_node(std::vector<Node> sorted_grid, Node candidate, std::vector<Node> candidates, int position, int grid_width, int grid_height)
{
    // here we count combs
    counter_comb++;
    // here we test if it really fits
    if (insert_node(sorted_grid, candidate, (position % grid_width), std::floor(position / grid_width), grid_width, grid_height))
    {
        // inserting candidate
        sorted_grid[position] = candidate;
        // we continue to another position
        sort(sorted_grid, std::move(candidates), position + 1, grid_width, grid_height);
    }
}

// Recursive function to attempt inserting puzzle candidates and solving the puzzle.
// This function iterates through the remaining list of puzzle candidates and attempts to insert them
// into the grid at different positions, considering all possible rotations of each candidate.
// If a successful combination is found, it prints the result.
// Parameters:
// - sorted_grid: The current grid configuration with some nodes already inserted.
// - candidates: The list of remaining puzzle candidates.
// - position: The index (0-8) in the vector where the candidate will be inserted.
// - grid_width: Width of the puzzle grid.
// - grid_height: Height of the puzzle grid.
void sort(const std::vector<Node> &sorted_grid, std::vector<Node> candidates, int position, int grid_width, int grid_height)
{
    // If there are no more candidates left, we have solved the puzzle.
    if (candidates.empty())
    {
        // prints result
        printNodes(sorted_grid);
        return;
    }
    // Iterate through the remaining puzzle candidates and try to insert them at different positions.
    for (int i = 0; i < 9 - position; i++)
    {
        Node to_remove = candidates[i];

        // If the candidate contains a 0 value, we cannot proceed.
        if (!to_remove)
            return;

        // Remove the current candidate from the list.
        candidates.erase(candidates.begin() + i);

        // Try inserting the candidate and its rotated versions into the grid.
        try_node(sorted_grid, to_remove, candidates, position, grid_width, grid_height);
        try_node(sorted_grid, to_remove.rotate(), candidates, position, grid_width, grid_height);
        try_node(sorted_grid, to_remove.rotate().rotate(), candidates, position, grid_width, grid_height);
        try_node(sorted_grid, to_remove.rotate().rotate().rotate(), candidates, position, grid_width, grid_height);

        // Add the candidate back to its original position in the list.
        candidates.insert(candidates.begin() + i, to_remove);
    }
}

// Function to initiate the puzzle-solving process.
// This function prepares the necessary variables and calls the sorting function to solve the puzzle.
// Parameters:
// - candidates: A vector containing the puzzle candidates.
void solve_puzzle(std::vector<Node> candidates)
{
    // Reset the global combination counter before starting another function call.
    counter_comb = 0;
    sort(std::vector<Node>(9), candidates, 0, 3, 3);

    // Print the total number of combinations tried and indicate the puzzle-solving process is finished.
    std::cout << "Combinations tried: " << counter_comb << std::endl;
    std::cout << "Finished" << std::endl
              << std::endl;
};