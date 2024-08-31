#include <vector>
#include <iostream>

void subsetsum(std::vector<std::vector<int>>& results, std::vector<int>& choices, std::vector<int>& state, int target, int total, int start) {
    if (total == target) {
        results.push_back(state);
        return;
    }

    for (int i = start; i < choices.size(); i++) {
        if ((total + choices[i]) > target ) {
            continue;
        }
        state.push_back(choices[i]);
        subsetsum(results, choices, state, target, total + choices[i], i);
        state.pop_back();
    }
}


int main(int, char**) {
    std::vector<std::vector<int>> results;
    std::vector<int> choices{3, 4, 5};
    std::vector<int> state;
    subsetsum(results, choices, state, 9, 0, 0);
    for (int i = 0; i < results.size(); i++) {
        for (int j = 0; j < results[i].size(); j++) {
            std::cout << results[i][j] << " ";
        }

        std::cout << std::endl;
    } 
    return 0;
}