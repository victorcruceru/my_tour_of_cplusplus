/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: std::weak_ptr examples
 */ 


#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <memory> // std::make_shared
#include <algorithm> 

class DAGNode{
  private:
    std::string name_ = "";
    std::vector<std::weak_ptr<DAGNode>> neighbors_ = {};

  public:  
    DAGNode(){
      std::cout << "DEBUG: Default constructor called" << std::endl; 
    }

    DAGNode(std::string name): name_{name} {
      std::cout << "DEBUG: "<< __func__ <<" constructor called for node: "
                << name_ << std::endl; 
    }

    ~DAGNode(){
      std::cout << "DEBUG: "<< __func__ <<" destructor  called for node: "
                << name_ << std::endl; 
    }

    const std::string& get_name(void) const{
      return (this->name_);
    }

    void add_neighbor(const std::shared_ptr<DAGNode>& new_node){
      auto result_iter = std::find_if(
        std::begin(neighbors_), 
        std::end(neighbors_), 
        [new_node] (std::weak_ptr<DAGNode> n) {
          // catch error from lock() !
          return (n.lock()->get_name() == new_node->get_name());		
        }
      );

      if (result_iter == std::end(neighbors_)){
        // not found, insert it
        std::cout << "DEBUG: inserting new node: " << new_node->get_name() 
                  << std::endl;
        neighbors_.push_back(std::weak_ptr<DAGNode>(new_node));
      }

    }



};

int main(){
  std::shared_ptr<DAGNode>  n1 = std::make_shared<DAGNode>("N1");
  std::shared_ptr<DAGNode>  n2 = std::make_shared<DAGNode>("N2");
  n1->add_neighbor(n2);
  return (EXIT_SUCCESS);
}