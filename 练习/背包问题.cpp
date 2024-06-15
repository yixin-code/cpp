// 有 N 件物品和一个容量是 V 的背包。每件物品只能使用一次。
// 第i件物品的体积是 vi，价值是 wi
// 求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。
// 输出最大价值。
// 输入格式
// 第一行两个整数，N，V
// ，用空格隔开，分别表示物品数量和背包容积。
// 接下来有N行，每行两个整数 vi, wi，用空格隔开，分别表示第i件物品的体积和价值。
// 输出格式
// 输出一个整数，表示最大价值。
// 数据范围
// 0 < N, V ≤ 1000
// 0 < vi, wi ≤ 1000
// 输入样例
// 4 5
// 1 2
// 2 4
// 3 4
// 4 5
#include <iostream>

int main(int argc, char *argv[]) {
    constexpr int LIMIT = 1000;

    int N                   = 0;    // N个物品
    int V                   = 0;    // 背包体积
    int v                   = 0;    // 物品体积
    int w                   = 0;    // 物品价值
    int package[LIMIT]      = {0};  // 背包容量

    std::cin >> N >> V;
    for (int )

    return 0;
}