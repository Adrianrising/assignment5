//
// Created by BMT on 9/25/2022.
//
//
// Created by BMT on 9/18/2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#define MAX_LINE 2048
#include "iostream"
using namespace std;
class FileMain{
    int choice;
public:
    int getter(){
        return choice;
    }
    void setter(int c){
        choice=c;
    }
    void insertData(FILE *fptr){
        int inputCount=0;
        int count=0;
        int id;
        int amount;
        char userName[MAX_LINE];
        char password[MAX_LINE];
        //opens the file in apppend mode
        fptr= fopen("assignment4.txt","a");
        if(fptr==NULL){
            fptr= fopen("assignment4.txt","w");
        }
        //ask for the input count
        printf("Enter the number of data you want to input: ");
        scanf("%d",&inputCount);
        //prints data into file
        while(count<inputCount){
            puts("Enter id,username,password,amount");
            scanf("%d%s%s%d",&id,userName,password,&amount);
            fprintf(fptr,"%d%8s%8s%5d\n",id,userName,password,amount);
            count+=1;
        }
    }

    void searchData(FILE *fptr){
        char search[MAX_LINE];
        char temp[MAX_LINE];
        int lineNum=1;
        int findResult=0;
        //opens file in read mode
        fptr= fopen("assignment4.txt","r");
        //if file does not exist or is null exit with code 1
        if(fptr==NULL){
            printf("File cannot be opened!");
            exit(1);
        }
        //asks for the word to search
        printf("Enter the data you want to search: ");
        scanf("%s",search);
        //search in the file for word
        //fgets searchs the file line by line with while loop
        while(fgets(temp,sizeof temp,fptr)!=NULL){
            //strstr() search for the word in file and store it in the temp array
            if(strstr(temp,search)!=NULL){
                printf("we found %s at line %d \n",search,lineNum);
                printf(" %s",temp);
                findResult++;
            }
            lineNum++;
        }
        lineNum=1;
        if(findResult==0){
            puts("we couldn't find your data.");
        }
    }

    void updateData(FILE *fptr){
        FILE *tempF;
        int replaceLineNo;
        char buffer[MAX_LINE];
        int currentLine=1;
        int id;
        int amount;
        char userName[MAX_LINE];
        char password[MAX_LINE];
        //opens file in read mode
        fptr= fopen("assignment4.txt","r");
        if(fptr==NULL){
            printf("Cannot open file or file does not exist");
            exit(1);
        }
        //opens temporary file in write mode
        tempF= fopen("temporaryFile.txt","w");
        if(tempF==NULL){
            printf("Cannot open file or file does not exist");
            exit(1);
        }
        //asks for the line to remove
        printf("Enter the line to remove: ");
        scanf("%d",&replaceLineNo);
        bool keepReading=true;
        do {
            //gets each line of fptr into buffer array
            fgets(buffer,MAX_LINE,fptr);
            if(feof(fptr)){
                keepReading=false;
            }
                //if replace line>>prints the replace line to the file instead of ori line
            else if(currentLine==replaceLineNo){
                puts("Enter id,username,password,amount");
                scanf("%d%s%s%d",&id,userName,password,&amount);
                fprintf(tempF,"%d%8s%8s%5d\n",id,userName,password,amount);
            }else{
                //if not replace line>>puts ori line in file
                fputs(buffer,tempF);
            }
            currentLine++;

        } while (keepReading);
        fclose(fptr);
        fclose(tempF);
        remove("assignment4.txt");
        rename("temporaryFile.txt","assignment4.txt");
    }

};
//inheritance
class File_Main1:public FileMain{
};


int main(){
    //obj of first class
    FileMain obj;
    //obj of the child class of first class
    File_Main1 obj1;
    //file pointer
    FILE *fptr;
    int c;
    //do while loop
    do {
        //prints user options
        puts("Press 1 to insert data,Press 2 to Find data,Press 3 to update data,Press 4 to exit.");
        scanf(" %d",&c);
        //change the value of choice in parent class
        obj.setter(c);
        switch (obj.getter()) {
            case 1:
                obj.insertData(fptr);
                break;
            case 2:
                obj1.searchData(fptr);
                break;
            case 3:
                obj.updateData(fptr);
                break;
            default:break;
        }
    }while(obj.getter()!=4);
    fclose(fptr);
    return 0;
}




