#ifndef HASHMAP_HPP_
#define HASHMAP_HPP_

/**********************
* Author: Jonah Mania *
* Date: 3/6/2015      *
**********************/

#include <stdint.h> //uint32_t
#include <cstddef> //NULL
#include <cstring> //strlen

//Hashing fuction
typedef uint32_t ( *hashMapHash )( void *k );
//Default bucket count
const int defaultBuckets = 100; 

template <typename K, typename V>
struct HashMapNode
{
    //Key value of the node
    void *key;
    //Stored value for the key value pair
    void *value;
    //The next hash node with the same hash value
    HashMapNode<K,V>* next; 
    //Default constructor
    HashMapNode()
    {
        value = NULL;
        next = NULL;
    }
    //Constructor with key and value pair
    HashMapNode( K k, V v )
    {
        value = v;
        key = k;
        next = NULL;
    }
};


template <typename K, typename V>
class HashMap
{
    public:
        HashMap();                                  //Default constructor
        HashMap( hashMapHash h );                   //Constructor when hash is provided
        V insert( K k, V v);                        //Insert a key value pair to the hashmap
        void *get( K k );                           //Get a value from the hashmap with key k 
        void remove( K k );                         //Remove value mapped to key k
        void clear();                               //Removes all key, value pairs from the hashmap
        void destroyHashMap();                      //Deconstructor for Hashmap
    private:
        HashMapNode<K,V>* buckets;                  //Array of buckets to hold hashing nodes
        int numBuckets;                             //Number of buckets in the hashmap
        hashMapHash hash;                           //Hashing function
};

//Default hash function used in the case that no hash function is passed to the constructor
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
    }
    return hash;
}

template <typename K, typename V>
HashMap<K,V>::HashMap()
{
    hash = defaultHash;

    HashMapNode<K,V>* b = new HashMapNode<K,V>[defaultBuckets];    
    buckets = b;

    numBuckets = defaultBuckets;
}

template <typename K, typename V>
HashMap<K,V>::HashMap( hashMapHash h )
{
    hash = h;

    HashMapNode<K,V>* b = new HashMapNode<K,V>[defaultBuckets]; 
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
        HashMapNode<K,V>* tempBuckets = new HashMapNode<K,V>[ hashValue + 1 ];

        for( int i = 0; i < numBuckets; ++i )
            tempBuckets[i] = buckets[i];

        delete [] buckets;
        buckets = tempBuckets;  
        numBuckets = hashValue + 1;
    }
    
    //If there is no value in the current hashvalue bucket
    if( !buckets[hashValue].value || buckets[hashValue].key == k )
    {
        buckets[hashValue].value = v;
        buckets[hashValue].key = k;
    }
    else
    {
        //Set a pointer to the current bucket
        HashMapNode<K,V>* currBucket = &buckets[hashValue];
        //Move through the linked lists of buckets until an empty bucket is found
        while( currBucket->next and currBucket->key != k )
        {
            currBucket = currBucket->next;
            if( currBucket->key == k )
            {
                currBucket->value = v;
                return v;
            }
        }
        //When an empty bucket is found attach a new node to it with the desired values
        currBucket->next = new HashMapNode<K,V>( k,v );
    }
    return v;
}

template <typename K, typename V>
void HashMap<K,V>::remove( K k )
{
    //Get hash value of k
    uint32_t hashValue = hash( k ); 

    if( buckets[hashValue].key == k )
    {
        buckets[hashValue] = *buckets[hashValue].next;
    }
    else
    {   
        //Set a pointer to the previous bucket
        HashMapNode<K, V>* prevBucket = &buckets[hashValue];
        //Set a pointer to the current bucket
        HashMapNode<K, V>* currBucket = buckets[hashValue].next;
        
        while( currBucket )
        {
            if( currBucket->key == k )
            {
                prevBucket->next = currBucket->next;
                delete currBucket;
                break;
            }
            prevBucket = prevBucket->next;
            currBucket = currBucket->next;
        }
    }
        
}

template <typename K, typename V>
void *HashMap<K,V>::get( K k )
{
    //Get the hash value of k
    uint32_t hashValue = hash( k );
    
    //Check if the bucket with this key exists
    if(  numBuckets < hashValue || !buckets[hashValue].key )
        return NULL;

    //Check if the has bucket has key k
    if( buckets[hashValue].key == k )
        return buckets[hashValue].value;
    else
    {
        //Look through the linked list to find key k
        HashMapNode<K,V>* currBucket = &buckets[hashValue];
        while( currBucket->next and currBucket->key != k )
            currBucket = currBucket->next;
        if( currBucket->key == k )
            return currBucket->value;
    }
    //In the case that the key does not exist return NULL   
    return NULL;
}

template <typename K, typename V>
void HashMap<K,V>::clear()
{
    //Clear all linked lists in each bucket
    for( int i = 0; i < numBuckets; ++i )
    {
        if( buckets[i].next )
        {
            HashMapNode<K,V>* currBucket = buckets[i].next;
            HashMapNode<K,V>* next;
            while( currBucket )
            {
                next = currBucket->next;
                delete currBucket;
                currBucket = next;
            }
        }
        //Set each bucket to NULL
        buckets[i] = NULL;
    }
}

template <typename K, typename V>
void HashMap<K,V>::destroyHashMap()
{
    //Clear all linked lists in each bucket
    for( int i = 0; i < numBuckets; ++i )
    {
        if( buckets[i].next )
        {
            HashMapNode<K,V>* currBucket = buckets[i].next;
            HashMapNode<K,V>* next;
            while( currBucket )
            {               
                next = currBucket->next;
                delete currBucket;
                currBucket = next;
            }
        }
    } 
    //Delete the buckets array
    delete []buckets;
}

#endif
