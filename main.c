//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2


int trackInfester(int patient_no, int *detected_time, int *place);

int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int index, age, time;
    int placeHist[N_HISTORY];
    
    int i, j;
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1],"r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    
    //1-2. loading each patient informations
    
    fp = fopen("patientInfo_sample.txt", "r");
    
    while(3==fscanf(fp, "%d %d %d", &index, &age, &time))
    {
    	for(i=0; i<5; i++){
    		fscanf(fp, "%s", &placeHist[i]);
		}
		ifct_element = ifctele_genElement(index, age, time, placeHist);
		ifctdb_addTail(ifct_element);
		
	}
	
	
    //1-3. FILE pointer close
    fclose(fp);
   /* {
    	int place1, place2;
    	
    	place1 = 3;
    	place2 = 9;
    	
    	printf("The first place is %s\n", ifctele_getPlace(place1));
    	printf("The second place is %s\n", ifctele_getPlace(place2));
    	
	}
   */
    

    
    
    
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                     //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                    //MENU_TRACK
        printf("0. Exit.\n");                                              //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        int num;
        int minAge, maxAge;
        char num_place[MAX_PLACENAME];
        
        switch(menu_selection)
        {
            case MENU_EXIT:
                printf("Exiting the program... Bye bye bye.\n");
                break;
                
                
                
            case MENU_PATIENT: // 환자 번호 선택, 함수 이용해 환자 정보 출력  
			    printf("Select patient index :\n");
				scanf("%i", &num);
				
				if (num > ifctdb_len()-1 || num < 0){
					printf(" [ERROR] WRONG INDEX ! PLEASE CHOOSE BETWEEN 0~%i\n", ifctdb_len()-1);
				}
				else{
					printf("\n ----------Patient Information----------\n");
					ifctele_printElement(ifctdb_getData(num));
					
				}
                
                break;
                
                
                   
            case MENU_PLACE: // 감염 장소 선택
                printf("Enter Place Name:\n");
                scanf("%s", &num_place);
                
                for(i=0; i<ifctdb_len(); i++)
				{
					for(j=0; j<N_HISTORY; j++)
					{
						int placeIndex[N_HISTORY];
						placeIndex[j] = ifctele_getHistPlaceIndex(ifctdb_getData(i), j);
						
						if (strcmp(ifctele_getPlace(placeIndex[j]), num_place) == 0)
						{
							printf("------------------------");
							ifctele_printElement(ifctdb_getData(i));
						}
					}
				 } 
                
                
                break;
                
                
                
            case MENU_AGE: // 나이 선택, 범위에 있는 환자 정보 출력  
			    printf("Enter minimal age :\n ");  // 최소 나이 입력받기  
				scanf("%d", &minAge);
				printf("Enter maximal age :\n");   // 최대 나이 입력받기  
				scanf("%d", &maxAge);
				
				for (i=0; i<ifctdb_len(); i++)
				{					
					if(minAge <= ifctele_getAge(ifctdb_getData(i)) && ifctele_getAge(ifctdb_getData(i)) <= maxAge)
					{
						printf("--------------------");
						ifctele_printElement(ifctdb_getData(i));
					}
				}
                
                break;
                
            case MENU_TRACK:
                    
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
