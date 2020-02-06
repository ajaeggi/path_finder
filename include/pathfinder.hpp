#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <node.hpp>


class PathFinder{
    public:
        //Rule of five
        PathFinder() = delete;
        ~PathFinder() = default;

        PathFinder(int x, int y);

        void setStart(int x, int y);
        Node* getStart(void){return start_node_;}
        void setTarget(int x, int y);
        Node* getTarget(void){return target_node_;}
        std::vector<std::vector<Node>> createNodeArray(int x, int y);
        std::vector<std::vector<Node>>& getNodeArray(void){return field_;}
        bool processNextNode(void);
        void obstacleToggle(int x, int y);
        void reset(void);
        void drawPath(void);

    private:
        Node* start_node_;
        Node* target_node_;
        std::vector<std::vector<Node>> field_;
        std::vector<Node*> stack_;

        float calcHeuristicDistance(Node* node);
        void exploreNode(Node* node, Node* parent);
        void addNodeToVector(Node* node);
        void resetNode(Node& node);
};
