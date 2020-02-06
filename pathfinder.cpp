#include <pathfinder.hpp>

PathFinder::PathFinder(int x, int y)
:
start_node_(),
target_node_()
{
    field_ = createNodeArray(x, y);
}

/**
 * 
 */
void PathFinder::reset(void){
    stack_.clear();
    stack_.push_back(start_node_);
    for(int i=0; i<field_.size(); i++){
        for(int j=0; j<field_[0].size(); j++){
            resetNode(field_[i][j]);
        }
    }
    start_node_->path_cost = 0;
    start_node_->visited = true;
}

/**
 * 
 */
void PathFinder::resetNode(Node& node){
    node.is_path = false;
    node.local_cost = std::numeric_limits<float>::max();
    node.path_cost = std::numeric_limits<float>::max();
    node.heuristic_cost = 0;
    node.visited = false;
    node.parent = nullptr;
}

/**
 * 
 */
void PathFinder::exploreNode(Node* node, Node* parent){
    //If we visit this node for the first time, set it as visited and calculate heuristic distance to target
    if(!node->is_obstacle){
        if(!node->visited) {
            std::cout << "found new node [" << node->x_pos << "][" << node->y_pos << "] with cost (";
            node->heuristic_cost = calcHeuristicDistance(node);
            std::cout << node->heuristic_cost << ")\n";
            
        }
        
        //Calculate cost for current path
        float cost = parent->path_cost+1 + node->heuristic_cost;
        //Update node if current path cost are smaller than current local costs
        if(cost < node->local_cost){
            //std::cout << "Update cost for node [" << node->x_pos << "][" << node->y_pos << "] from " << node->local_cost << " to " << cost << "\n";
            //std::cout << "Set parent node[" << parent->x_pos << "][" << parent->y_pos << "]\n";
            node->parent = parent;
            node->local_cost = cost;
            node->path_cost = parent->path_cost + 1;
        }
        if(!node->visited) {
            node->visited = true;
            addNodeToVector(node);
        }
    }
}

/**
 * 
 */
void PathFinder::addNodeToVector(Node* node){
    //Find position
    //std::cout << "stack-size = " << stack_.size() << "\n";
    if(stack_.empty()){
        stack_.push_back(node);
    } else {
        for(std::vector<Node*>::iterator pos = stack_.begin(); pos < stack_.end(); pos++){
            //std::cout << (*pos)->local_cost << "/" << node->local_cost << "\n";
            if((*pos)->local_cost < node->local_cost){
                //std::cout << "Add node to stack at position " << std::distance(stack_.begin(), pos) << "\n";
                stack_.insert(pos, node);
                break;
            }
            if(pos == stack_.end()-1){
                stack_.push_back(node); //If there was no node with a lower cost
                break;
            }
        }
    }
}

/**
 * 
 */
bool PathFinder::processNextNode(void){
    if(!stack_.empty()){
        Node* node = stack_.back();
        if(node->is_target){
            return true;
        }
        stack_.pop_back();
        //node->is_path = true;
        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                if(node->x_pos-i >= 0 && node->x_pos+i <= field_.size()){
                    if(node->y_pos-j >= 0 && node->y_pos+j <= field_[0].size()){
                        if(!(i == 0 && j == 0)){ //This would be the node itself
                            exploreNode(&field_[node->x_pos+i][node->y_pos+j], node);
                        }
                    }
                }
            }
        }
    }
    return false;
}

/**
 * 
 */
float PathFinder::calcHeuristicDistance(Node* node){
    int x_diff = abs(node->x_pos - target_node_->x_pos);
    int y_diff = abs(node->y_pos - target_node_->y_pos); 
    return sqrt(x_diff*x_diff + y_diff*y_diff);
}

/**
 * 
 */
std::vector<std::vector<Node>> PathFinder::createNodeArray(int x, int y){
    std::vector<std::vector<Node>> arr;
    for(int i = 0; i < x; i++){
        std::vector<Node> row;
        for(int j = 0; j < y; j++){
            Node node;
            node.x_pos = i;
            node.y_pos = j;
            row.push_back(node);
        }
        arr.push_back(row);
    }
    
    return arr;
}

/**
 * 
 */
void PathFinder::setTarget(int x, int y){
    if((0 <= x && x <= field_.size()) &&  (0 <= y && y <= field_[0].size())){
        if(target_node_ != nullptr){
            target_node_->is_target = false;
        }
        target_node_ = &field_[x][y];
        target_node_->is_target = true;
    }
}

/**
 * 
 */
void PathFinder::setStart(int x, int y){
    if((0 <= x && x <= field_.size()) &&  (0 <= y && y <= field_[0].size())){
        if(start_node_ != nullptr){
            start_node_->is_start = false;
        }
        start_node_ = &field_[x][y];
        start_node_->is_start = true;
        start_node_->path_cost = 0;
        start_node_->visited = true;
        start_node_->heuristic_cost = calcHeuristicDistance(start_node_);
        stack_.push_back(start_node_);
    }
}

/**
 * 
 */
void PathFinder::obstacleToggle(int x, int y){
    field_[x][y].is_obstacle = !field_[x][y].is_obstacle;
}

/**
 * 
 */
void PathFinder::drawPath(void){
    Node* next_node = target_node_;
    while(next_node != start_node_){
        //std::cout << "from node[" << next_node->x_pos << "][" << next_node->y_pos << "] to node["   << next_node->parent->x_pos << "][" << next_node->parent->y_pos << "]\n";
        next_node->is_path = true;
        next_node = next_node->parent;
    }
}