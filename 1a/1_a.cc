#include <iostream>


int main(){
    int len = 300;
    int widt = 300;

    std::cout << "p6" << std::endl;
    std::cout << len << " " << widt << std::endl;
    std::cout << "255" << std::endl;

    for (int i = 0; i < len; i++){
        for (int j = 0; j < len; j++){

            unsigned char r = 0;
            unsigned char g = 0; 
            unsigned char b = 0;

            std::cout << r << " " << g << " " << b << std::endl;
        }
    }
}
