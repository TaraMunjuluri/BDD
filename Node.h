#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node {
public:
    int level;                // Level of the node
    std::string lowEdge;      // Low edge target (handle or terminal)
    std::string highEdge;     // High edge target (handle or terminal)

    // Constructor
    Node(int lvl, const std::string& low, const std::string& high)
        : level(lvl), lowEdge(low), highEdge(high) {}
};

#endif
