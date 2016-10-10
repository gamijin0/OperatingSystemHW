//
// Created by 49738 on 2016/10/10.
//
#include <iostream>
#include <windows.h>

int main(int argc, char *argv[]){
    for (int i =0;i<argc;i++){
        std::cout<<argv[i]<<std::endl;
    }
    system("pause");
}