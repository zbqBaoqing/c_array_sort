/*************************************************************************
	> File Name: straight_sort.c
	> Author: yexingkong
	> Mail: abqyexingkong@gmail.com 
	> Created Time: Thu 18 Jul 2013 20:15:51 CST
    > Description: 直接插入排序算法
 ************************************************************************/

#include<stdio.h>




// 直接插入排序，参数num_lenght所表示的意义是所要排序队列的长度，
// sort[]数组表示的是所要排序的数组,排序是由小到大

int straight_sort(int num_length, int sort[])
{
    int i = 0, k = 0;
    
    for (i = 2; i <= num_length; i++){
        
        k = i-1 ;
        sort[0]= sort[i];

        while (sort[0] < sort[k] && 0 < k ){
            sort[k+1] = sort[k];
            k--;
        }
        sort[k+1] = sort[0];
    }

    for (i = 1; i <= num_length; i++){
        printf("%d ", sort[i]);
    }
    printf("\n");

    return 0;

}


