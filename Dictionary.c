#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include <stdbool.h>
#include "Dictionary.h"

#define tableSize 101	
//	const int tableSize=101;
    
	typedef struct NodeObj{
		char* key;
		char* value;
		struct NodeObj* next;
	} NodeObj;

	typedef NodeObj* Node;

	Node newNode(char* k, char* v){
		Node N = malloc(sizeof(NodeObj));
		assert(N != NULL);
		N->key = k;
		N->value = v;
		N->next = NULL;	
		return N;
	}
	
	typedef struct DictionaryObj{
		Node hashTable[tableSize];
		int numItems;
	} DictionaryObj;
	
	typedef DictionaryObj* Dictionary;

	Dictionary newDictionary(){
		Dictionary D = malloc(sizeof(DictionaryObj));
		D->numItems = 0;
		return D;
	}

	void freeDictionary(Dictionary* pD){
		if( pD!=NULL && *pD!=NULL ){
    		if( !isEmpty(*pD) ) makeEmpty(*pD);
     			free((*pD)->hashTable);
			free(*pD);
     		    *pD = NULL;
   		}
	}	
	
	void freeNode(Node* pN){
    	if( pN!=NULL && *pN!=NULL ){
        	free(*pN);
        	*pN = NULL;
   }
}

	// rotate_left()
	// rotate the bits in an unsigned int
	unsigned int rotate_left(unsigned int value, int shift) {
 		int sizeInBits = 8*sizeof(unsigned int);
 		shift = shift & (sizeInBits - 1);
 		if ( shift == 0 )
 		return value;
 		return (value << shift) | (value >> (sizeInBits - shift));
	}
	// pre_hash()
	// turn a string into an unsigned int
	unsigned int pre_hash(char* input) {
 		unsigned int result = 0xBAE86554;
 		while (*input) {
 			result ^= *input++;
 			result = rotate_left(result, 5);
 		}
 		return result;
	}
	// hash()
	// turns a string into an int in the range 0 to tableSize-1
	int hash(char* key){
 		return pre_hash(key)%tableSize;
	}

	int isEmpty(Dictionary D) {
		return D->numItems == 0;
	}
	

	int size(Dictionary D) {
		return D->numItems;
	}
	
	char* lookup(Dictionary D,char* k) {
		int position = hash(k);
		Node temp = D->hashTable[position];
		while(temp != NULL) {
			if(strcmp(temp->key,k) == 0){
				return temp->value;
			}
			temp = temp->next;
		}
		return NULL;
	}
	
	void insert(Dictionary D, char* k, char* v){
		Node insert = newNode(k,v);
		if(lookup(D,k) == NULL) {
			int position = hash(k);
			if(D->hashTable[position] != NULL){
			//	Node temp = D->hashTable[position]->next;
			//	while(temp != NULL){
			//		temp = temp->next;
			//	}
			//	temp = insert;
				insert->next = D->hashTable[position];
				D->hashTable[position] = insert;
				
			}
			else{
				D->hashTable[position] = insert;
				
			}	
			D->numItems++;		
		}
		else {
			printf("cannot insert duplicate keys");
		}
//		free(insert);
	}
	
	void delete(Dictionary D, char* k){
		int position = hash(k);
	        Node temp = D->hashTable[position];
	//	Node* pointer = temp;
		bool found = false;
		if(strcmp(temp->key,k) == 0) {
		//	fprintf(stdout,"%s", temp->key);
			D->hashTable[position] = temp->next;
			found = true;
			D->numItems--;
			freeNode(&temp);
			temp = NULL;
		}
	
		else {
			Node remove = temp->next;
			while(remove != NULL && !found) {
				if(strcmp(remove->key,k) == 0) {
		//			fprintf(stdout,"%s",remove->key);
					temp->next = temp->next->next;
					found = true;
					D->numItems--;
				}
				temp = temp->next;
				remove = remove->next;
				freeNode(&remove);
				remove = NULL;
				freeNode(&temp);
			//	remove = NULL;
				temp = NULL;	
			}
		}
			if(!found){
			printf("cannot delete non-existent key");	
		}
	}

	void makeEmpty(Dictionary D) {
		Node temp;
		for(int i = 0; i < tableSize; i++){
		        temp = D->hashTable[i];
		    	  while(D->hashTable[i] != NULL){
				
				temp = temp->next;  
				freeNode(&D->hashTable[i]);
				D->hashTable[i] = NULL;
			//	temp = temp->next;
				D->hashTable[i] = temp;
			  }
		}  
		D->numItems = 0;
	}
	
	void printDictionary(FILE* out, Dictionary D){
		for(int i = 0; i < tableSize; i++){
			Node temp = D->hashTable[i];
			while(temp != NULL){
				fprintf(out, "%s %s\n",temp->key,temp->value );
				temp = temp->next;
			}
		}
	}


	

