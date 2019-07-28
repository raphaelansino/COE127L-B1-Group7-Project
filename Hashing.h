#ifndef HASHING_H
#define HASHING_H
#include <cstdio>


class Hashing
{
    public:
        Hashing();
        virtual ~Hashing();


        typedef struct HashTable Node;
        void readFunc(const char* filename, int index );
        void rmPunct2LowerFunc(char *p);
        void mapperFunc(int index);
        unsigned int hashComputeByHashFunc(const char* key);
        void hashTableInsertFunc(const char* key, int value, int index);
        Node* hashTableLookupFunc(const char* key, int index);
        void reducerFunc(int reduceCount);
        void writerFunc(FILE* fp);
        void hashTablePrintFunc(int index);




};

#endif // HASHING_H


