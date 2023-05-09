#include "Headers/library.h"

int main() {
    // 1
    cout << "==1==" << std::endl;

    std::vector<int> native;
    Vector<int> custom;

    native.reserve(222);
    custom.reserve(333);

    native.push_back(1);
    native.push_back(2);
    native.push_back(3);
    native.push_back(4);

    custom.push_back(1);
    custom.push_back(2);
    custom.push_back(3);
    custom.push_back(4);

    std::cout << "Native vector: ";
    for (auto i : native)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "Custom vector: ";
    for (auto i : custom)
        std::cout << i << " ";
    std::cout << std::endl << std::endl;

    std::cout << "Native vector size: " << native.size() << std::endl;
    std::cout << "Custom vector size: " << custom.size() << std::endl << std::endl;


    std::cout << "Native vector capacity: " << native.capacity() << std::endl;
    std::cout << "Custom vector capacity: " << custom.capacity() << std::endl << std::endl;


    std::cout << "Native vector empty: " << native.empty() << std::endl;
    std::cout << "Custom vector empty: " << custom.empty() << std::endl << std::endl;


    std::cout << "Native vector max size: " << native.max_size() << std::endl;
    std::cout << "Custom vector max size: " << custom.max_size() << std::endl << std::endl;


    std::cout << "Native vector front: " << native.front() << std::endl;
    std::cout << "Custom vector front: " << custom.front() << std::endl << std::endl;


    std::cout << "Native vector back: " << native.back() << std::endl;
    std::cout << "Custom vector back: " << custom.back() << std::endl << std::endl;


    std::cout << "Native vector at 2: " << native.at(2) << std::endl;
    std::cout << "Custom vector at 2: " << custom.at(2) << std::endl << std::endl;


    for (auto i : native)
        std::cout << i << " ";
    std::cout << std::endl;

    for (auto i : custom)
        std::cout << i << " ";
    std::cout << std::endl << std::endl;

    native.pop_back();
    custom.pop_back();
    custom.pop_back();

    for (auto i : native)
        std::cout << i << " ";
    std::cout << std::endl;

    for (auto i : custom)
        std::cout << i << " ";
    std::cout << std::endl << std::endl;


    native.clear();
    custom.clear();

    // 2
    cout << "==2==" << std::endl;

    unsigned int sz = 100000000;  // 100000, 1000000, 10000000, 100000000

    auto startNative = high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i){
        native.push_back(i);
    }
    auto endNative = high_resolution_clock::now();

    auto startCustom = high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i){
        custom.push_back(i);
    }
    auto endCustom = high_resolution_clock::now();

    duration<double> durationNative = endNative - startNative;
    duration<double> durationCustom = endCustom - startCustom;

    std::cout << "Native vector push_back time (" << sz << "): " << durationNative.count() << std::endl;
    std::cout << "Custom vector push_back time (" << sz << "): " << durationCustom.count() << std::endl << std::endl;

    native.clear();
    custom.clear();

    // ==3==
    cout << "==3==" << std::endl;

    std::vector<int> nativee;
    Vector<int> customm;

    int countNative = 0;
    int countCustom = 0;



    for (int i = 1; i <= sz; ++i){
        if(nativee.size() == nativee.capacity())
            countNative++;
        
        nativee.push_back(i);
    }

    for (int i = 1; i <= sz; ++i){
        if(customm.size() == customm.capacity())
            countCustom++;
        
        customm.push_back(i);
    }

    std::cout << "Native vector times when reallocated: " << countNative << std::endl;
    std::cout << "Custom vector times when reallocated: " << countCustom << std::endl << std::endl;

    nativee.clear();
    customm.clear();
}