//
//  ifs_element.c
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ifct_element.h"

typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
} place_t;

char countryName[N_PLACE+1][MAX_PLACENAME] =
{   "Seoul",
    "Jeju",
    "Tokyo",
    "LosAngeles",
    "NewYork",
    "Texas",
    "Toronto",
    "Paris",
    "Nice",
    "Rome",
    "Milan",
    "London",
    "Manchester",
    "Basel",
    "Luzern",
    "Munich",
    "Frankfurt",
    "Berlin",
    "Barcelona",
    "Madrid",
    "Amsterdam",
    "Stockholm",
    "Oslo",
    "Hanoi",
    "Bangkok",
    "KualaLumpur",
    "Singapore",
    "Sydney",
    "SaoPaulo",
    "Cairo",
    "Beijing",
    "Nairobi",
    "Cancun",
    "BuenosAires",
    "Reykjavik",
    "Glasgow",
    "Warsow",
    "Istanbul",
    "Dubai",
    "CapeTown",
    "Unrecognized"
};

////////// ȯ�� ���� ����  
typedef struct ifs_ele{  
	int index;  // ��ȣ  
	int age;    // ����  
	int time;   // ���� ����  
	place_t place[N_HISTORY]; //ȯ�� �̵� ��� enum Ȱ���� place_t �� ����  
}ifs_ele_t;



////////// ȯ�� ������ ����ü ����  
void* ifctele_genElement( int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
{
	ifs_ele_t * ptr;
	
	ptr = (ifs_ele_t*)malloc(5*sizeof (ifs_ele_t*));
	ptr -> index = index;
	ptr -> age = age;
	ptr -> time = detected_time;
	
	int i;
	
	for (i=0; i<N_HISTORY; i++)
	{
		ptr -> place[i] = history_place[i];
	
	return ptr;
    }
	
}

//{ ifs_ele_t*ptr;
//  ptr= malloc[];
//  ptr->index 

////////// ȯ�� ���� ��ȯ  
int ifctele_getAge(void*obj)
{
	ifs_ele_t *ptr = (ifs_ele_t*)obj;
	
	return (ptr ->age);
}

////////// ȯ�� �̵� ��� ��ȯ  
int ifctele_getHistPlaceIndex(void* obj, int index)
{
	ifs_ele_t * ptr = (ifs_ele_t *)obj;
	
	return ( ptr -> place[index]);
}


////////// ȯ�� ���� ����  ��ȯ  
unsigned int ifctele_getinfectedTime(void* obj)
{
	ifs_ele_t *ptr = (ifs_ele_t*)obj;
	
	return (ptr -> time);
}


////////// ��� ��ȯ  
char* ifctele_getPlace(int placeIndex)
{
	return countryName[placeIndex];
	 
}

////////// ȯ�� ���� ���  
void ifctele_printElement(void *obj)
{
	ifs_ele_t* ptr = (ifs_ele_t*)obj; //�����ͷ� ����ü ����Ŵ  
	
	printf("Index : %d\n", ptr->index);
	printf("Age : %i\n", ptr->age);
	printf("Time : %i\n", ptr->time);
	printf("History Place :  ");
	
	int i;
	for (i=0; i < N_HISTORY; i++)
	{
		printf("%s", ifctele_getPlace(ptr ->place[i]));
	}

	printf("\n"); 
}


