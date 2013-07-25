/*************************************************************************
	> File Name: binary_sort.c
	> Author: yexingkong
	> Mail: abqyexingkong@gmail.com 
	> Created Time: Thu 18 Jul 2013 21:03:45 CST
    > Description:折半插入排序算法
 ************************************************************************/

#include<stdio.h>

//折半插入排序，参数sort[]是所需对其排序的数组，num_length指的是
//sort数组中所存的数的个数,排序是由小到大　

int binary_sort(int sort[],int num_length){
    
    int i = 0,j = 0, low = 0, heigh = 0, middle = 0;

    for (i = 2; i <= num_length;i++ ){
        
        low = 1; 
        heigh = i - 1;
        sort[0] = sort[i];

        while (low <= heigh ){
            
            middle = ( low + heigh ) / 2;
            if (sort[0] < sort[middle]){
                heigh= middle - 1;
            } else {
                low = middle + 1;
            }
        }
        
        for ( j =  i - 1; j >= heigh+1; j--){
            sort[j+1] = sort[j];
        }

        sort[j+1] = sort[0];

    }

    for (i = 1;i <= num_length; i++){
        printf("%d ",sort[i]);
    }
    printf("\n");

    return 0;
}


