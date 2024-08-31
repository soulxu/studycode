#include "tree.h"

#include <vector>
#include <iostream>



int main(int, char**) { 
    std::cout << "----bst2" << std::endl;
    Algo::Tree<int> tree2;
    for (int i = 0; i < 10; i++) {
        int tmp = random() % 10;
        std::cout << "gen num " << tmp << std::endl;
        tree2.addBST3(tmp);
    }

    // std::cout << "----bst2 pre older, height=" << tree2.height() << std::endl;
    // tree2.travelPreOrder([](int data){
    //     std::cout << data << std::endl;
    // });
    // std::cout << "----bst2 in order" << std::endl;
    // tree2.travelInOrder([](int data){
    //     std::cout << data << std::endl;
    // });

    // std::cout << "----bst2 in level" << std::endl;
    // tree2.travelLevel([](int data){
    //     std::cout << data << std::endl;
    // });

    // std::cout << "find 6 = " << tree2.findBST2(6) << std::endl;
    // std::cout << "find 13 = " << tree2.findBST2(13) << std::endl;
    // tree2.removeBST2(9);
    // std::cout << "----bst2 in level after remove, height=" << tree2.height()  << std::endl;
    // tree2.travelLevel([](int data){
    //     std::cout << data << std::endl;
    // });
    // std::cout << "----bst2 in order" << std::endl;
    // tree2.travelInOrder([](int data){
    //     std::cout << data << std::endl;
    // });


    std::vector<int> pre_order;
    tree2.travelPreOrder([&pre_order](int data) {
        pre_order.push_back(data);
    });
    std::vector<int> in_order;
    tree2.travelInOrder([&in_order](int data) {
        in_order.push_back(data);
    });

    for (int i = 0; i < pre_order.size(); i++) {
        std::cout << pre_order[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < in_order.size(); i++) {
        std::cout << in_order[i] << " ";
    }
    std::cout << std::endl;

    Algo::Tree tree3(pre_order, in_order);

    std::vector<int> pre_order2;
    tree3.travelPreOrder([&pre_order2](int data) {
        pre_order2.push_back(data);
    });
    std::vector<int> in_order2;
    tree3.travelInOrder([&in_order2](int data) {
        in_order2.push_back(data);
    });

    for (int i = 0; i < pre_order2.size(); i++) {
        std::cout << pre_order2[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < in_order2.size(); i++) {
        std::cout << in_order2[i] << " ";
    }
    return 0;
}