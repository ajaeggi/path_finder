#pragma once

#include <limits>

class Node{
    
    //Rule of five
    //We keep all constructors at default

    public:
        float id = 0;
        bool visited = false;
        bool is_start = false;
        bool is_target = false;
        bool is_obstacle = false;
        bool is_path = false;
        int x_pos = 0;
        int y_pos = 0;
        float local_cost = std::numeric_limits<float>::max();
        float path_cost = std::numeric_limits<float>::max();
        float heuristic_cost = 0;
        Node* parent = nullptr;

};