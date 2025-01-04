#include <iostream>
#include <map>
#include <string>

int main(int argc, char *argv[]) {
    // 构造
    std::map<int, std::string, std::greater<int>> mm = {{1, "aaa"}, {2, "bbb"}, {3, "ccc"}, {4, "ddd"}, {5, "eee"}};
    auto comp = [](const int &num, const int &num2) {
        return num > num2;
    };
    std::map<int, std::string, decltype(comp)> m(comp);
    m = {std::make_pair(1, "aaa"), std::make_pair(2, "bbb"), std::make_pair(3, "ccc"), std::make_pair(4, "ddd"), std::make_pair(5, "eee")};

    // 增加元素
    auto p = m.insert(std::make_pair(6, "fff"));
    if (p.second == true) {
        std::cout << "insert success" << std::endl;
    } else {
        std::cout << "insert fail" << std::endl;
    }
    // c++17 插入相同key会更新val
    m.insert_or_assign(1, "aaaa");
    for (const auto &val : m) {
        std::cout << val.first << " " << val.second << std::endl;
    }

    // 删除元素
    m.erase(3);

    // 查找 计数
    std::multimap<int, std::string> mmm = {{1, "aaa"}, {1, "aaa"}, {2, "bbb"}, {3, "ccc"}, {4, "ddd"}, {5, "eee"}};
    std::cout << mmm.count(1) << std::endl; // 2
    auto it = mmm.find(1);
    if (it != mmm.end()) {
        std::cout << it->first << " " << it->second << std::endl; // 1 aaa
    } else {
        std::cout << "not found" << std::endl;
    }
    // 排序顺序会影响结果
    // 返回第一个不小于和第一个大于
    auto er = mmm.equal_range(3);
    std::cout << er.first->first << " " << er.first->second << std::endl; // 3 ccc
    std::cout << er.second->first << " " << er.second->second << std::endl; // 4 ddd
    // 不小于
    auto lb = mmm.lower_bound(2);
    std::cout << lb->first << " " << lb->second << std::endl; // 2 bbb
    // 大于
    auto ub = mmm.upper_bound(3);
    std::cout << ub->first << " " << ub->second << std::endl; // 4 ddd

    // c++17快速提取元素(会删除提取的元素) 放入另一个map中
    auto ele = m.extract(1);
    std::map<int, std::string> m2;
    m2.insert(std::move(ele));

    return 0;
}