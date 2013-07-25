/*************************************************************************
	> File Name: merge_sort.c
	> Author: yexingkong
	> Mail: abqyexingkong@gmail.com 
	> Created Time: Fri 19 Jul 2013 16:56:42 CST
    > Description: 分治法排序
    ************************************************************************/

#include<stdio.h>

#define NUM 10


int merge_sort(int sort[],int p, int r);

int merge(int sort[], int p,int q, int r);

int print_merge(int sort[], int num_length);


//将分解的各个子序列排序并合并起来

int merge(int sort[], int p, int q, int r){

    int nl = q - p + 1;//计算左序列元素的个数，
    int nr = r - q; //计算右序列元素的个数
    
    int L[nl],R[nr]; //用来保存左右两个序列

    int i = 0, j = 0, k = p; //注意:k 要从左值下标开始

    for ( i = 0,j = p; j < q+1; i++,j++ ){
        L[i] = sort[j];
    }
    for (i = 0,j = q+1; j < r+1; j++,i++){
        R[i] = sort[j];
    }

    i = p;
    j = q+1;

    int m = 0, n =0;

    while (i <= q && j <= r ){
        
        if ( L[m] <= R[n] ){
            
            sort[k] = L[m];
            k++;
            i++;
            m++;
        } else {
            sort[k] = R[n];
            k++;
            j++;
            n++;
        }
    }

    if ( j <= r ){
        while (j <= r){
            sort[k] = R[n];
            k++;
            j++;
            n++;
        }
    }else {
        while (i <= q){
            sort[k] = L[m];
            k++;
            i++;
            m++;
        }
    }
    return 0 ;
    
}





//分治法排序，参数sort是需要排序的数组，p是子序列的起始下标，
//r是子序列的终止下标,排序由小到大

int merge_sort(int sort[], int p, int r){

        int q ;

        q = ( p + r ) / 2;

    //保证序列中不少于两个元素
    if ( p < r ){
        merge_sort(sort,p,q);
        merge_sort(sort,q+1,r);
        merge(sort,p,q,r);
    }

    return 0;
}



//打印数组序列,参数sort是所传的数组序列,num_length是数组序列的长度

int print_merge(int sort[], int num_length){
    
    int i = 1;

    for ( i = 1;i < num_length+1;i++ ){
        
        printf("%d ",sort[i]);
    }
        
    printf("\n");

    return 0;

}



