#include <utility>
#include <memory>

template<typename T>
struct node {
  T value;
  std::shared_ptr<node> tail;

  ~node() {
    // std::move is necessary here. Otherwise, next_node.unique() will never return true.
    auto next_node{ std::move(tail) };
    while (next_node) {
      // If you're not the only owner of the node, don't do anything.
      if (!next_node.unique()) break;

      // Steals the tail of the node you're processing, to stop the node's destructor from destroying it recursively
      std::shared_ptr<node> tail;
      std::swap(tail, next_node->tail);
      // Freely destroys the node; no recursive calls because you've set its tail to be nullptr
      next_node.reset();

      // std::move isn't necessary here but could improve performance.
      next_node = std::move(tail);
    }
  }
};