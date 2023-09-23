#include <iostream>
#include <vector>

struct Node {
    Node() = default;
    int name = 0;
    std::vector<int> children;
    int depth = 0;
};

int SetDepth(std::vector<Node> &nodes, int parent){
    int index_max_depth = parent;
    if(nodes[parent].children.empty()) return nodes[parent].name;
    for(auto children : nodes[parent].children) {
        nodes[children].depth = nodes[parent].depth + 1;
        int tmp = SetDepth(nodes, nodes[children].name);
        if((nodes[tmp].depth) > nodes[index_max_depth].depth) {
            index_max_depth= tmp;
        }
    }
    return index_max_depth;
}


int main() {
    int n = 0;
    std::cin >> n;
    std::vector<Node> nodes(n + 1);
    nodes[0].name = 0;
    nodes[0].depth = 0;

    int max_depth = 0;
    int max_depth_index =0;
    for(int i = 1; i <= n ; ++i) {
        nodes[i].name = i;
        int parent = 0;
        std::cin >> parent;
        nodes[parent].children.push_back(i);
    }

    std::cout << SetDepth(nodes, 0) << std::endl;

    return 0;
}
