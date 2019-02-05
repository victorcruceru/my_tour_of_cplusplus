/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: Mainly this is about std::weak_ptr. It covers the relationship
 * weak_ptr <-> shared_ptr (how to lock an weak_ptr to get the shared_ptr).
 * The example implements a Directed Graph and the BFS traversal. 
 */ 


#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <memory> // std::make_shared
#include <algorithm> 
#include <queue>
#include <set>

// A node in a Directed Graph 
class DGNode{
  private:
    std::string name_ = ""; // the label (name) of the node
    std::vector<std::weak_ptr<DGNode>> neighbors_ = {}; // list of adjacent 
                                                  // nodes to the current node  

  public:  
    DGNode(){
      std::cout << "DEBUG: Default constructor called" << std::endl; 
    }

    DGNode(std::string name): name_{name} {
      std::cout << "DEBUG: "<< __func__ <<" constructor called for node: "
                << name_ << std::endl; 
    }

    ~DGNode(){
      std::cout << "DEBUG: "<< __func__ <<" destructor  called for node: "
                << name_ << std::endl; 
    }
    
    // Getters
    const std::string& get_name(void) const{
      return (this->name_);
    }

    const std::vector<std::weak_ptr<DGNode>>& get_neighbors(void) const{
      return (this->neighbors_);
    }
    
    // Add new_node as an adjacent node to the current one
    // Nodes are identified by names (labels).
    // If new_node already in the adjacency list then it is silently discarded
    void add_neighbor(const std::shared_ptr<DGNode>& new_node){

      auto result_iter = std::find_if(
        std::begin(neighbors_), 
        std::end(neighbors_), 
        [new_node] (std::weak_ptr<DGNode> n) {
          // catch error from lock() !
          try{
            return (n.lock()->get_name() == new_node->get_name());		
          }catch (std::bad_weak_ptr& b){
            std::cout << "ERROR#1: Null object: " << b.what() << std::endl;
            return (false);
          }
        }
      );

      if (result_iter == std::end(neighbors_)){
        // not found, insert it
        std::cout << "DEBUG: [Node: " << name_ 
                  << "] inserting new neigbor node: " << new_node->get_name() 
                  << std::endl;
        neighbors_.push_back(std::weak_ptr<DGNode>(new_node));
      }

    }
    
    // Add a list of nodes as adjacent nodes to the current mode
    void add_neighbor(const std::initializer_list<std::shared_ptr<DGNode>>& 
                      new_nodes){
      for (const auto& node: new_nodes) {
        this->add_neighbor(node);
      }
    }  

    // Method used for visiting  the current node 
    virtual 
    void visit(void){
      std::cout << "VISITing node named '" << name_ << "'" << std::endl;
    }
};

// BFS (Breadth First Search) traversal.
// It uses a queue to keep the list of nodes to be visited
// and a std::set of keep track of the nodes already visited. 
static 
void BFS_traversal(const std::shared_ptr<DGNode>& start_node){
  std::cout << " ---> BFS traversal starting with node named '" 
            << start_node->get_name() << "':" << std::endl;

  std::queue<std::shared_ptr<DGNode>> _queue = {};
  std::set<std::shared_ptr<DGNode>> _visited = {};

  _queue.push(start_node);
  _visited.insert(start_node);
  start_node->visit();

  while (_queue.size() > 0){

    auto vertex = _queue.front();
    _queue.pop();
    
    for (const auto& neighbor: vertex->get_neighbors()){
        if (auto n = neighbor.lock()){
          if (_visited.find(n) == _visited.end()){
            // not yet visited
            n->visit();
            _visited.insert(n);
            _queue.push(n) ;
          }
        } else {
          std::cout << "ERROR#3: Can't lock a weak_ptr " << std::endl; 
        }
    }
  }
  std::cout << " <--- BFS traversal starting with node named '" 
            << start_node->get_name() << "' completed" << std::endl;
}

int main(){
  std::shared_ptr<DGNode> n1 = std::make_shared<DGNode>("N1");
  std::shared_ptr<DGNode> n2 = std::make_shared<DGNode>("N2");
  std::shared_ptr<DGNode> n3 = std::make_shared<DGNode>("N3");
  std::shared_ptr<DGNode> nx = std::make_shared<DGNode>("NX");
  std::shared_ptr<DGNode> isolated = std::make_shared<DGNode>("Isolated");

  n1->add_neighbor(n2);
  n2->add_neighbor({n1, n2, n3});
  nx->add_neighbor({n1, n3, n3, n1}); 

  BFS_traversal(n1);

  BFS_traversal(nx);

  BFS_traversal(isolated);

  return (EXIT_SUCCESS);
}