#include "MTBDD.h"

// Read input file into vector of pairs
std::vector<std::pair<std::string, int>> readInputFile(const std::string& filename) {
    std::vector<std::pair<std::string, int>> inputs;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return inputs;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string bitPattern;
        int value;
        if (iss >> bitPattern >> value) {
            inputs.emplace_back(bitPattern, value);
        }
    }

    file.close();
    return inputs;
}

int main() {
    MTBDD mtbdd;

    // Read input file
    std::string filename = "input.txt";
    auto inputs = readInputFile(filename);

    if (inputs.empty()) {
        std::cerr << "Error: No valid inputs found.\n";
        return 1;
    }

    // Build MTBDD
    mtbdd.buildMTBDD(inputs);

    // Output MTBDD structure
    mtbdd.outputStructure();

    return 0;
}
