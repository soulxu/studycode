#include <vector>

#include <iostream>

void backTrack(std::vector<int>& choices, int state, int& result, int target) {
    if (state == target) {
        result++;
        return;
    }
    for (int i : choices) {
        if ((state + i) > target) {
            continue;
        }
        backTrack(choices, state + i, result, target);
    }
}

int climbingStairsBackTrack(int n) {
    std::vector<int> choices{1, 2};
    int state = 0;
    int result = 0;
    backTrack(choices, state, result, n);
    return result;
}

int dfs(int n) {
    if (n == 1 || n == 2) {
        return n;
    }

    return dfs(n - 1) + dfs(n - 2);
}

int climbingStairsDfs(int n) {
    return dfs(n);
}

int dfsWithMem(int n, std::vector<int>& mem) {
    if (n == 1 || n == 2) {
        return n;
    }

    if (mem[n] != -1) {
        return mem[n];
    }
    int count = dfsWithMem(n - 1, mem) + dfsWithMem(n - 2, mem);
    mem[n] = count;
    return count;
}

int climbingStairsDfsWithMem(int n) {
    std::vector<int> mem(n + 1, -1);
    return dfsWithMem(n, mem);
}


int climbingStairsDP(int n) {
    if (n == 1 || n == 2) {
        return n;
    }

    std::vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

int climbingStairsDP2(int n) {
    if (n == 1 || n == 2) {
        return n;
    }

    int n1 = 2;
    int n2 = 1;
    int tmp = 0;
    for (int i = 3; i <= n; i++) {
        tmp = n1;
        n1 = n1 + n2;
        n2 = tmp;

    }
    return n1;
}

int climbingStairsDPWithCost(const std::vector<int>& cost) {
    int n = cost.size() - 1;
    if (n == 1 || n == 2) {
        return cost[n];
    }
    std::vector<int> dp{n + 1};
    dp[0] = 0;
    dp[1] = cost[1];
    dp[2] = cost[2];
    for (int i = 3; i <= n; i++) {
        dp[i] = cost[i] + std::min(dp[i - 1], dp[i - 2]);
    }
    return dp[n];
}

int climbingStairsDPWithCost2(const std::vector<int>& cost) {
    int n = cost.size() - 1;
    if (n == 1 || n == 2) {
        return cost[n];
    }

    int cost1 = cost[1];
    int cost2 = cost[2];
    for (int i = 3; i <= n; i++) {
        int tmp = cost2;
        cost2 = cost[i] + std::min(cost2, cost1);
        cost1 = tmp;
    }
    return cost2;
}

int main(int, char**) {
    std::cout << "climbingStairsBackTrack = " << climbingStairsBackTrack(6) << std::endl;
    std::cout << "climbingStairsDfs = " << climbingStairsDfs(6) << std::endl;
    std::cout << "climbingStairsDfsWithMem = " << climbingStairsDfsWithMem(6) << std::endl;
    std::cout << "climbingStairsDP = " << climbingStairsDP(6) << std::endl;
    std::cout << "climbingStairsDP2 = " << climbingStairsDP2(6) << std::endl;
    std::cout << "climbingStairsDPWithCost = " << climbingStairsDPWithCost(std::vector<int>({0, 1, 10, 1})) << std::endl;
    return 0;
}