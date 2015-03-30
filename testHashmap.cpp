#include "hashMap.hpp"
#include <iostream>

int main()
{
    std::cout<<"Testing hashmap"<<std::endl;

    HashMap< char*, char*> hMap;

    std::cout<<"Inserting testKey"<<std::endl;
    hMap.insert( (char*)"testKey", (char*)"testValueKey" );
    std::cout<<"Inserting banana"<<std::endl;
    hMap.insert( (char*)"banana", (char*)"testValueBanna" );
    std::cout<<"Inserting blue"<<std::endl;
    hMap.insert( (char*)"blue", (char*)"testValueBlue" );
    std::cout<<"Inserting /source/images/test.png"<<std::endl;
    hMap.insert( (char*)"/source/images/test.png", (char*)"testValueSource" );
    std::cout<<"Inserting /models/textures/knight.obj"<<std::endl;
    hMap.insert( (char*)"/models/textures/knight.obj", (char*)"testValueModels" );
	std::cout<<"Inserting a"<<std::endl;
	hMap.insert( (char*)"a", (char*)"testValueA" );
	std::cout<<"Inserting banana"<<std::endl;	
	hMap.insert( (char*)"banana", (char*)"testValueBannaTwo");
	std::cout<<"Inserting a"<<std::endl;
	hMap.insert( (char*)"a", (char*)"testValueATwo" );

	std::cout<<"Removing a"<<std::endl;
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

	hMap.destroyHashMap();
}
