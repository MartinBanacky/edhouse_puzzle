#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <functional>
#include "Node.h"

void printNodes(const std::vector<Node> &node_array);
bool match_edge(const std::vector<Node> &grid, int x, int y, const std::function<int(const Node &)> &get_edge, int new_edge, int grid_width, int grid_height);
bool insert_node(const std::vector<Node> &grid, Node new_node, int x, int y, int grid_width, int grid_height);
void try_node(std::vector<Node> sorted_grid, Node candidate, std::vector<Node> candidates, int position, int grid_width, int grid_height);
void sort(const std::vector<Node> &sorted_grid, std::vector<Node> candidates, int position, int grid_width, int grid_height);
void solve_puzzle(std::vector<Node> candidates);

#endif