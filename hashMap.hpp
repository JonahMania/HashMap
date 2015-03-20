#ifndef HASHMAP_HPP_
#define HASHMAP_HPP_

/**********************
* Author: Jonah Mania *
* Date: 3/6/2015      *
**********************/

#include <vector>   //std::vector
#include <stdint.h> //uint32_t
#include <cstring>  //strcmp

//TEMP
#include <iostream>

typedef int ( *hashMapCompare )( void *x, void *y ); 
typedef uint32_t ( *hashMapHash )( void *k );
const int defaultBuckets = 100; 

template <typename K, typename V>
struct HashMapNode
{
    K *key;
    void *value;
    uint32_t hash;

	HashMapNode()
	{
		value = NULL;
	};
};


template <typename K, typename V>
class HashMap
{
    public:
        HashMap();                                  //Default constructor
        HashMap( hashMapHash h );                   //Constructor when hash is provided
        HashMap( hashMapCompare c );                //Constructor when compare is provided
        HashMap( hashMapHash h, hashMapCompare c ); //Constructor when hash and compare are provided
        V insert( K k, V v);                        //Insert a key value pair to the hashmap
        V get( K k );                               //Get a value from the hashmap with key k 
        V remove( K k );                            //Remove value mapped to key k
        void clear();                               //Removes all key, value pairs from the hashmap
        ~HashMap();                                 //Deconstructor for Hashmap
    private:
        HashMapNode<K,V>* buckets;                  //Array of buckets to hold hashing nodes
        int numBuckets;                             //Number of buvkets in the hashmap
        hashMapCompare compare;                     //Function to compare two nodes
        hashMapHash hash;                           //Hashing function
};

//Default compare function used in the case that no compare function is passed to the constructor
int defaultCompare( void *x, void *y  )
{
    return strcmp( (char*)x , (char*)y );
}

uint32_t defaultHash( void *k )
{
    char* key = (char*)k;
    int len = strlen( key );
    uint32_t hash = 0;
    unsigned int higherorder = hash & (int)0xf8000000;
    hash = hash << 5;
    hash = hash ^ ( higherorder >> 27 );

    for( int i = 0; i < len; ++i )
    {
        
        hash = hash ^ (unsigned int)key[i];
        //std::cout<< int(key[i]) <<std::endl;
    }
    std::cout << hash << std::endl; 

    return hash;
}

template <typename K, typename V>
HashMap<K,V>::HashMap()
{
    hash = defaultHash;
    compare = defaultCompare;

    HashMapNode<K,V> b[defaultBuckets];    
    buckets = b;

    numBuckets = defaultBuckets;
}

template <typename K, typename V>
HashMap<K,V>::HashMap( hashMapHash h )
{
    hash = h;
    compare = defaultCompare;

    HashMapNode<K,V> b[defaultBuckets];    
    buckets = b;

    numBuckets = defaultBuckets;
}

template <typename K, typename V>
HashMap<K,V>::HashMap( hashMapCompare c )
{
    hash = defaultHash;
    compare = c;

    HashMapNode<K,V> b[defaultBuckets];    
    buckets = b;

    numBuckets = defaultBuckets;
}

template <typename K, typename V>
HashMap<K,V>::HashMap( hashMapHash h, hashMapCompare c )
{
    hash = h;
    compare = c;

    HashMapNode<K,V> b[defaultBuckets];    
    buckets = b;

    numBuckets = defaultBuckets;
}

template <typename K, typename V>
V HashMap<K,V>::insert( K k, V v )
{
    //Get hash value from key k
    uint32_t hashValue = hash( k );

    //If the hash is larger then the number of buckets expand the array
    if( hashValue > numBuckets )
    {
        HashMapNode<K,V> tempBuckets[hashValue];

        for( int i = 0; i < numBuckets; ++i )
            tempBuckets[i] = buckets[i];

        //delete [] buckets;
        buckets = tempBuckets;
        numBuckets = hashValue;
    }


    buckets[hashValue].value = v;

	//Must typecast a void* to the desired datatype before dereferencing so the compiler knows what size to look for
	std::cout<< (char*)(V)buckets[hashValue].value <<std::endl;

}

template <typename K, typename V>
V HashMap<K,V>::remove( K k )
{

}

template <typename K, typename V>
V HashMap<K,V>::get( K k )
{

}

template <typename K, typename V>
HashMap<K,V>::~HashMap()
{

}

#endif
