#ifndef MTBDD_H
#define MTBDD_H

#include "Node.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class MTBDD {
private:
    std::unordered_map<std::string, Node*> nodes;   // Non-terminal nodes
    std::vector<std::string> roots;                // Root edges
    int nodeCounter = 1;                           // Counter for naming non-terminal nodes

public:
    // Add a non-terminal node
    std::string addNode(int level, const std::string& low, const std::string& high) {
        // Generate node name
        std::string handle = "N" + std::to_string(nodeCounter++);
        nodes[handle] = new Node(level, low, high);
        return handle;
    }

    // Add a root
    void addRoot(const std::string& root) {
        roots.push_back(root);
    }

    // Generate BDD/MTBDD from input bit patterns and terminal values
    void buildMTBDD(const std::vector<std::pair<std::string, int>>& inputs) {
        std::unordered_map<std::string, std::string> terminalHandles;

        // Assign terminal handles (e.g., T0, T1)
        int terminalCounter = 0;
        for (const auto& input : inputs) {
            std::string terminalHandle = "T" + std::to_string(terminalCounter++);
            terminalHandles[std::to_string(input.second)] = terminalHandle;
        }

        // Process inputs bottom-up
        std::unordered_map<int, std::vector<std::string>> levelNodes;
        for (const auto& input : inputs) {
            const std::string& bitPattern = input.first;
            const std::string& terminalHandle = terminalHandles[std::to_string(input.second)];
            std::string currentHandle = terminalHandle;

            // Create nodes bottom-up
            for (int level = bitPattern.size() - 1; level >= 0; --level) {
                std::string low = (bitPattern[level] == '0') ? terminalHandle : currentHandle;
                std::string high = (bitPattern[level] == '1') ? terminalHandle : currentHandle;

                // Add a node for this level
                currentHandle = addNode(level, low, high);
            }

            // Add to root
            addRoot(currentHandle);
        }
    }

    // Output the BDD/MTBDD structure
    void outputStructure() {
        // Print nodes
        std::cout << "NODES {\n";
        for (const auto& [handle, node] : nodes) {
            std::cout << "    " << handle << " L " << node->level << ": "
                      << "0:<" << node->lowEdge << ">, 1:<" << node->highEdge << ">\n";
        }
        std::cout << "}\n";

        // Print roots
        std::cout << "ROOTS {\n";
        int rootCounter = 1;
        for (const auto& root : roots) {
            std::cout << "    r" << rootCounter++ << " <" << root << ">\n";
        }
        std::cout << "}\n";
    }
};

#endif
