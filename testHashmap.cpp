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
	std::cout<<"a: ";
	hMap.insert( (char*)"a", (char*)"testValueA" );
	std::cout<<"banana: ";	
	hMap.insert( (char*)"banana", (char*)"testValueBannaTwo");
	std::cout<<"a: ";
	hMap.insert( (char*)"a", (char*)"testValueATwo" );

	hMap.remove( (char*)"a" );
	
	std::cout<<"Find"<<std::endl;
	if( hMap.get( (char*)"banana" ) )
		std::cout<<"banana: "<<(char*)hMap.get((char*)"banana")<<std::endl;
	else
		std::cout<<"key: banana does not exist in the hash map"<<std::endl;
	if( hMap.get( (char*)"/models/textures/knight.obj" ) )
		std::cout<<"/models/textures/knight.obj: "<<(char*)hMap.get((char*)"/models/textures/knight.obj")<<std::endl;
	else
		std::cout<<"key: /models/textures/knight.obj does not exitst in the hash map"<<std::endl;
	if( hMap.get( (char*)"a" ) )
		std::cout<<"a: "<<(char*)hMap.get((char*)"a")<<std::endl;
	else
		std::cout<<"key: a does not exist in the hash map"<<std::endl;
	if( hMap.get( (char*)"nav" ) )
		std::cout<<"nav: "<<(char*)hMap.get((char*)"nav")<<std::endl;
	else
		std::cout<<"key: nav does not exist in the has map"<<std::endl;
}
