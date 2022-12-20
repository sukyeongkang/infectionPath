//
//  ifct_database.c
//  Infection Path
//  Database platform code for storing infest path elements
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <stdlib.h>

#include "ifct_database.h"

#define LIST_END -1

//node definition for linked list 노드 정의  
typedef struct node{
    int index;          //index of the node 몇번째 노드 
    void* obj;          //object data 오브젝트 데이터  
    void* next;         //pointer to the next 다음 노드 가르키는 포인터  
    void* prev;         //pointer to the next 이전 노드 가르키는 포인터  
} node_t;


static node_t* list_database = NULL;
static node_t* listPtr = NULL;
static int list_cnt = 0;


//Inner functions (cannot used at the outside of this file)
static node_t* genNode(void) // 노드 생성  
{
    //allocate memory for creating the node
    node_t* ndPtr = (node_t*)malloc(sizeof(node_t)); // 동적메모리할당  사용  
    
	if (ndPtr != NULL)
    {
        ndPtr->next = NULL; // 다음 노드  포인터  
        ndPtr->obj = NULL;  // 현재 노드 포인터  
        ndPtr->prev = NULL; // 이전 노드 포인터  
    } //초기화 시켜줌  
    
    return ndPtr; //포인터 리턴  
}

static node_t* ifctList(int index)
{
    node_t* ndPtr = list_database; //노드 포인터 생성  
    if (listPtr != NULL && listPtr->index <= index)
    {
        ndPtr = listPtr;
    }
    
    
    //return for wrong input 잘못 입력했을때 출력되는 것  
    if (index <-1)
    {
        printf("[ERROR] ifctList() : either list is null or index is wrong! (offset : %i)\n", index);
        return NULL;
    }
    if (index >= list_cnt)
    {
        printf("[ERROR] ifctList() : index is larger than length (len:%i, index:%i)\n", list_cnt, index);
        return NULL;
    }
    
    
    //repeat travelling until the node is the end or offset becomes 0
    while (ndPtr != NULL)
    {
        if (ndPtr->index == index) // 노드의 번호가 일치하면 반복문 나가기  
            break;
        ndPtr = ndPtr->next; // 다음 노드 포인터 가르키게함  
    }
    
    return ndPtr;
}


static int updateIndex(void)
{
    int index=0;
    node_t* ndPtr = list_database;
    
    while ( ndPtr != NULL )//travel until it is the end node
    {
        ndPtr->index = index++;
        ndPtr = ndPtr->next; //travel once
    }
    
    return index;
}



//API function
/*
    description : adding a data object to the list end
    input parameters : obj - data object to add to the list
    return value : addition result (0 - succeeded, -1 - failed)
    
    operation : 1. make a new node
                2. find the last node in the list
                3. make the last node's next pointer to point the new node
                4. update the index
*/
int ifctdb_addTail(void* obj) // 노드 추가  
{
    node_t* ndPtr;
    node_t* newNdPtr;
    
    //parameter checking
    if (obj == NULL)
    {
        printf("[ERROR] ifsdb_addTail() : Failed to do addTail : input object indicates NULL!\n");
        return -1;
    }
    
    //generate new node
    newNdPtr = genNode();
    if (newNdPtr == NULL)   
    {
        printf("[ERROR] ifsdb_addTail() : Failed to do addTail : Failed to create a node\n");
        return -1; //indicate to the upper function that node addition is failed
    }
    newNdPtr->obj = obj; //매개변수 가르킴  
    
    //add node to the list tail
    if (list_database == NULL) //링크드리스트에 노드 없을때 
    {
        list_database = newNdPtr; // 헤더 포인터가 새로운 노드 가르킴  
        newNdPtr->index = 0;      
    }
    else //링크드리스트에 노드 있을때  
    {
        ndPtr = ifctList(list_cnt-1);     // 
        ndPtr->next = newNdPtr;           // 새로운 노드 가르킴  
        newNdPtr->prev = ndPtr;           // 기존의 노드 가르킴  
        newNdPtr->index = ndPtr->index+1; // 
    }
    
    listPtr = newNdPtr;
    
    list_cnt++;
    
    return 0;
}


/*
    description : delete data object from the list
    input parameters : index - index'th data to delete
    return value : deletion result (0 - succeeded, -1 - failed)
*/
int ifctdb_deleteData(int index)
{
    node_t* ndPrevPtr;
    node_t* ndNextPtr;
    node_t* delNdPtr;
    
    //parameter checking
    if ( (delNdPtr = ifctList(index)) == NULL) // 인덱스 통해 지우고 싶은 포인터 저장  
    {
        printf("[ERROR] ifctdb_deleteData() : Failed to do deleteData : input index is invalid (%i)!\n", index);
        return -1;
    }
    
    ndPrevPtr = delNdPtr->prev; // 지우려는 포인트의 이전 노드 포인터 저장  
 
    if (ndPrevPtr != NULL)
    {
        ndPrevPtr->next = delNdPtr->next; //delete next로 저장  
    }
    ndNextPtr = delNdPtr->next;
    
    if (ndNextPtr != NULL)
    {
        ndNextPtr->prev = delNdPtr->prev;
    }
    
    free(delNdPtr->obj); // obj 지우기  
    free(delNdPtr); // 지우기  
    
    list_cnt--;  // 리스트 개수 줄이기  
    
    if (list_cnt == 0)
    {
        list_database = NULL;
    }
    else
    {
        updateIndex(); //인덱스 업데이트 하기  
    }
    
    return 0;
}


//functions for list observation -----------------------------

/*
    description : return the number of data objects in the list
    return value : length
*/
int ifctdb_len(void)
{
    return list_cnt;  //노드 개수 리턴  
}


/*
    description : get the object data
    input parameters : index
    return value : object pointer
*/
void* ifctdb_getData(int index)
{
    void* obj = NULL;
    node_t* ndPtr;
    
    //parameter checking
    if ((ndPtr = ifctList(index)) != NULL) //ifctList 함수 통해 노드 가져온 것이 있을때  
    {
        obj = (void*)ndPtr->obj;
        listPtr = ndPtr;
    }
    
    if (obj == NULL) //
        printf("[ERROR] ifctdb_len() : there is no data of index %i\n", index);
    
    return obj; //메모리 주소 리턴  
}
