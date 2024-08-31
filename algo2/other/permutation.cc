
#include <vector>
#include <iostream>
#include <set>

void permutation(std::vector<std::vector<int>>& result, std::vector<int>& choices, std::vector<int>& state, std::vector<int>& selected) {
    if (state.size() == choices.size()) {
        result.push_back(state);
        return;
    }

    std::set<int> duplicated;
    for (int i = 0; i < choices.size(); i++) {
        if (!selected[i] && duplicated.find(choices[i]) == duplicated.end()) {
            duplicated.insert(choices[i]);
            state.push_back(choices[i]);
            selected[i] = true;
            permutation(result, choices, state, selected);
            selected[i] = false;
            state.pop_back();
        }
    }
}

int main(int, char**) {
    std::vector<std::vector<int>> result;
    std::vector<int> choices{1, 1, 3};
    std::vector<int> state;
    std::vector<int> selected(choices.size(), false);
    permutation(result, choices, state, selected);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            std::cout << result[i][j] << " ";
        }

        std::cout << std::endl;
    }
    return 0;
}