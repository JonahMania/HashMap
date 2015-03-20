#include "hashMap.hpp"
#include <iostream>

int main()
{
    std::cout<<"Testing hashmap"<<std::endl;

    HashMap< char*, char*> hMap;

    std::cout<<"testKey: ";
    hMap.insert( (char*)"testKey", (char*)"testValueKey" );
    std::cout<<"banana: ";
    hMap.insert( (char*)"banana", (char*)"testValueBanna" );
    std::cout<<"blue: ";
    hMap.insert( (char*)"blue", (char*)"testValueBlue" );
    std::cout<<"/source/images/test.png: ";
    hMap.insert( (char*)"/source/images/test.png", (char*)"testValueSource" );
    std::cout<<"/models/textures/knight.obj: ";
    hMap.insert( (char*)"/models/textures/knight.obj", (char*)"testValueModels" );
}
