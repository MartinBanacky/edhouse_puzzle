#include "Utils.h"
#include "Node.h"
#include <iostream>
#include <cmath>

// counter for combination count
int counter_comb = 0;

// getters for functions
auto getUpFunc = [](const Node &node)
{ return node.get_up(); };
auto getRightFunc = [](const Node &node)
{ return node.get_right(); };
auto getDownFunc = [](const Node &node)
{ return node.get_down(); };
auto getLeftFunc = [](const Node &node)
{ return node.get_left(); };

// Func to print grid
void printNodes(const std::vector<Node> &node_array)
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

// Func return true if next move is valid move (only one side test we have to call it for every side)
// grid = actual grid where we insert our puzzle
// x = position of puzzle we compare with
// y = position of puzzle we compare with
// get_edge = here we store function we gonna call on testing puzzle (it return value of that side so we can compare it)
// new_edge = is value of new puzzle we wanna insert (gonna compare with testing puzzle)
// grid_width = 3
// grid_height = 3
bool match_edge(const std::vector<Node> &grid, int x, int y, const std::function<int(const Node &)> &get_edge, int new_edge, int grid_width, int grid_height)
{
    // empty = index in grid (0-8)
    int empty = x + (y * grid_width);
    // x == -1 (left side), x >= grid_width (right side), y == -1 TOP, y >= grid_height BOTTOM, puzzle empty -> nothing to compare, last is compare if == 0 match (OK)
    return (x < 0) || (y < 0) || (x >= grid_width) || (y >= grid_height) || (empty >= grid_width * grid_height) || (!grid[empty]) || ((get_edge(grid[empty]) + new_edge) == 0);
}

// grid = actual grid where we insert our puzzle
// new_node = puzzle we wanna insert
//  x = position of puzzle we insert
//  y = position of puzzle we insert
//  grid_width = 3
//  grid_height = 3
//(x - 1), y form like this because we compare our puzzle (x,y) with puzzle (x-1,y) and every other side
bool insert_node(const std::vector<Node> &grid, Node new_node, int x, int y, int grid_width, int grid_height)
{
    return (match_edge(grid, (x - 1), y, getRightFunc, new_node.get_left(), 3, 3)) &&
           (match_edge(grid, (x + 1), y, getLeftFunc, new_node.get_right(), 3, 3)) &&
           (match_edge(grid, x, (y - 1), getDownFunc, new_node.get_up(), 3, 3)) &&
           (match_edge(grid, x, (y + 1), getUpFunc, new_node.get_down(), 3, 3));
}

// sorted_grid = actual grid where we insert our puzzle
// candidate = puzzle we insert
// candidates = list of ready puzzle not inserted yet
// position 0-8 (in vector) where we insert
//  grid_width = 3
//  grid_height = 3
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
        // if we return from recursion we have to remove it from sorted grid bcs it was incorrect
        sorted_grid[position] = Node(); // nwm ci to tu ma byt?? nerobi to rozdiel
    }
}

// sorted_grid = actual grid where we insert our puzzle
// candidates = list of ready puzzle not inserted yet
// position 0-8 (in vector) where we insert
//  grid_width = 3
//  grid_height = 3
void sort(const std::vector<Node> &sorted_grid, std::vector<Node> candidates, int position, int grid_width, int grid_height)
{
    // if no more candidates = we solved it
    if (candidates.empty())
    {
        // prints result
        printNodes(sorted_grid);
        return;
    }
    // we try for every puzzle every possible placement (also with rotations )
    for (int i = 0; i < 9 - position; i++)
    {
        Node to_remove = candidates[i];
        // if candiadate contain 0 value = we dont continue (bad input)
        if (!to_remove)
            return;
        // removing candidate
        candidates.erase(candidates.begin() + i);
        // we trie every rotation of puzzle
        try_node(sorted_grid, to_remove, candidates, position, grid_width, grid_height);
        try_node(sorted_grid, to_remove.rotate(), candidates, position, grid_width, grid_height);
        try_node(sorted_grid, to_remove.rotate().rotate(), candidates, position, grid_width, grid_height);
        try_node(sorted_grid, to_remove.rotate().rotate().rotate(), candidates, position, grid_width, grid_height);
        // adding candidate back (on same palce!) because we returned from recursion so another iteration we can work with every puzzle
        candidates.insert(candidates.begin() + i, to_remove);
    }
}

// function calls sort
// candidates = vector full of candidates
void solve_puzzle(std::vector<Node> candidates)
{
    // restoring global var before another func call
    counter_comb = 0;
    sort(std::vector<Node>(9), candidates, 0, 3, 3);
    std::cout << "Combinations tried: " << counter_comb << std::endl;
    std::cout << "Finished" << std::endl
              << std::endl;
};