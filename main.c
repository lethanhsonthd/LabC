/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: son
 *
 * Created on September 19, 2018, 9:12 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char dictionary[10000000][123], word[123];
int lengOfDictionary=-1;


void readData(FILE *f){
    char cur[123];
    while (fscanf(f,"%s",cur) == 1){
        lengOfDictionary++;
        strcpy(dictionary[lengOfDictionary],cur);
    }
    return;
}
void inputData(){
    int ok = 0;
    FILE *f;
    do{
        f = fopen("dictionary.txt","r");
        if (!f){
            printf("Data file does not exist!. Try again\n");
        }
    } while (!f);
    readData(f);
    printf("The dictionary has been loaded\n");
    return;
}
int substring(char shortstr[], char longstr[]){
    char* ret;
    ret = strstr(longstr,shortstr);
    if (!ret){
        return 0;
    }
    return 1;
}
int subsequence(char shortstr[], char longstr[]){
    int cnt = 0, tmp = 0;
    for (int i=0;i<strlen(shortstr);i++){
        for (int j=tmp;j<strlen(longstr);j++)
            if (shortstr[i]==longstr[j]){
                cnt++;
                tmp=j+1;
                break;
            }
    }
    if (cnt==strlen(shortstr)) return 1; else return 0;
}
int permutation(char shortstr[], char longstr[]){
    int markShort[123], markLong[123];
    memset(markShort,0,sizeof(markShort));
    memset(markLong,0,sizeof(markLong));
    if (strlen(shortstr)!=strlen(longstr)) return 0;
    for (int i=0;i<strlen(shortstr);i++) {
        markShort[shortstr[i]-'a']++;
        markLong[longstr[i]-'a']++;
    }
    for (int i=0;i<='z'-'a';i++){
        if (markLong[i]!=markShort[i]) return 0;
    }
    return 1;
}
int matchScore(char string1[], char string2[]){
    int cnt = 0;
    if (strlen(string1)!=strlen(string2)) return 100;
    for (int i=0;i<strlen(string1);i++){
        if (string1[i]!=string2[i]) cnt++;
    }
    return cnt;
}
void show(){
    printf("Welcome to the Spell Checker\n");
    inputData();
    printf("Please enter the word you would like checked: \n");
    scanf("%s",word);
}
void swapString(char str1[], char str2[]){
    char tmp[123];
    strcpy(tmp,str1);
    strcpy(str1,str2);
    strcpy(str2,tmp);
    return;
}
void solve(){
    for (int i=0;i<lengOfDictionary;i++){
        if (strcmp(word,dictionary[i])==0){
            printf("Great, %s is in the dictionary\n",word);
            return;
        }
    }
    printf("Here are the possible words you could have meant: \n");
    for (int i=0;i<lengOfDictionary;i++){
        char tmp1[123]="", tmp2[123]="";
        strcpy(tmp1,dictionary[i]);
        strcpy(tmp2,word);
        if (strlen(tmp2)>strlen(tmp1)) swapString(tmp2,tmp1);
        if (strlen(tmp2)-strlen(tmp1)>2) continue;
        if (substring(tmp2,tmp1)==1 
                || subsequence(tmp2,tmp1)==1
                || permutation(tmp2,tmp1)==1 || matchScore(tmp2,tmp1)<3)
                printf("%s\n",tmp1);
        }
    return;
}
int main(int argc, char** argv) {
    show();
    solve();
    
    return (EXIT_SUCCESS);
}

