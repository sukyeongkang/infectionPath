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
				
				
				if (num > ifctdb_len()-1 || num < 0)
				{
					printf(" [ERROR] WRONG INDEX ! PLEASE CHOOSE BETWEEN 0~%i\n", ifctdb_len()-1);
					break;
				}
			
					printf("\n ----------Patient Information----------\n");
					ifctele_printElement(ifctdb_getData(num));
					
				
                
                break;
        
                
                   
            case MENU_PLACE: // 감염 장소 선택
            {
                int place;
                
                printf("Enter Place Name:\n"); //장소 입력  
                scanf("%i", &place);
                
                int place_index;
                int cnt;
                
                // 입력 받은 장소에서 감염된 환자 수 세기  
                for(i=0; i<ifctdb_len(); i++)
				{
					ifct_element = ifctdb_getData(i);
					place_index = ifctele_getHistPlaceIndex(ifct_element, N_HISTORY -1);
					
					if (!strcmp(ifctele_getPlace(place_index), place))
					{
						cnt++;
						ifctele_printElement(ifct_element);
						break;
					}
				    printf("There are %i patients detected in %c \n", cnt, place);
            
                }
                break;
         }
                
                
            case MENU_AGE: // 나이 선택, 범위에 있는 환자 정보 출력  
            {
            	int minAge, maxAge;
            	int cnt;
	
			    printf("Enter minimal age :\n ");  // 최소 나이 입력받기  
				scanf("%d", &minAge);
				printf("Enter maximal age :\n");   // 최대 나이 입력받기  
				scanf("%d", &maxAge);
				
				// 입력받은 범위 내에 있는 환자 수 세기  
				for (i=0; i<ifctdb_len(); i++)
				{					
					if(minAge <= ifctele_getAge(ifctdb_getData(i)) && ifctele_getAge(ifctdb_getData(i)) <= maxAge)
					{
						cnt++; 
						printf("--------------------");
						ifctele_printElement(ifctdb_getData(i));
					}
					
					printf("There are %i patients whose age is between %i and %i\n", cnt, minAge, maxAge);
					
				}
                
                break;
            }
                
            case MENU_TRACK: // 감염 경로 및 최초 전파자 출력하기  
                
                {
				
                int patient_num;
                printf("Patient index:\n");
                scanf("%d", &patient_num);
                
                ifct_element = ifctdb_getData(patient_num); 
                
                if(ifct_element == NULL)  // 범위 외의 번호를 고를 경우  
                {
                	printf(" [ERROR] WRONG INDEX ! PLEASE CHOOSE BETWEEN 0~%i\n", ifctdb_len()-1);
                    break; 
				}
				
				int defected_time = ifctele_getinfestedTime(ifct_element);
				int defected_place = ifctele_getHistPlaceIndex(ifct_element, -1);
				
				printf("[TRACKING] patient %d is infected by %d (time : %d, place : %s)\n", patient_num, patient_num, defected_time, ifctele_getPlace(defected_place));  //범위 내의 환자 번호 고를 경우   
                    
                break;
                
                }
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
