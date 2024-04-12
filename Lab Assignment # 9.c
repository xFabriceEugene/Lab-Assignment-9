#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 10 // Choose your hash table size

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// Node for linked list
struct Node
{
    struct RecordType data;
    struct Node *next;
};

// HashType structure
struct HashType
{
    struct Node *head;
};

// Compute the hash function
int hash(int x)
{
    return x % HASH_SIZE;
}

// Initialize the hash table
void initHashTable(struct HashType hashTable[])
{
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        hashTable[i].head = NULL;
    }
}

// Insert a record into the hash table
void insertRecord(struct HashType hashTable[], struct RecordType record)
{
    int index = hash(record.id);
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = record;
    newNode->next = hashTable[index].head;
    hashTable[index].head = newNode;
}

// Display records in the hash structure
void displayRecordsInHash(struct HashType hashTable[], int hashSz)
{
    printf("Records in Hash Table:\n");
    for (int i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);
        struct Node *current = hashTable[i].head;
        while (current != NULL)
        {
            printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Free memory allocated for the hash table
void freeHashTable(struct HashType hashTable[])
{
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        struct Node *current = hashTable[i].head;
        while (current != NULL)
        {
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }
        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    printf("\nRecords:\n");
    for (int i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize hash table
    struct HashType hashTable[HASH_SIZE];
    initHashTable(hashTable);

    // Insert records into hash table
    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(hashTable, pRecords[i]);
    }

    // Display records in hash table
    displayRecordsInHash(hashTable, HASH_SIZE);

    // Free memory
    free(pRecords);
    freeHashTable(hashTable);

    return 0;
}

