/*************************************************************************
	> File Name: heap_sort.c
	> Author: yexingkong
	> Mail: abqyexingkong@gmail.com
	> Created Time: Mon 22 Jul 2013 21:07:18 CST
    > Description: 堆排序算法实现
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>


#define NUM 6  //定义数组的大小     



//大顶堆可得到有小到大的序列,相反,小顶堆可得到由大到小的序列.


//堆调整,将一个无序序列调整成一个堆.(非递归法)
//参数heap_array是一个待调整的数组,index是要调整的一个元素下标,
//need_adjust_length表示为需要调整堆大小(需要调整的数组元素个数),
//elem_size表示的是数组类型大小.
//返回值 !0 表示非正常返回.
//调整为大顶堆.

static int heap_adjust_A(void *heap_array,int index, int need_adjust_length,int elem_size)
{
    //为什么不用buffer[elem_size],而用malloc申请空间?原因是,
    //buffer[elem_size]分配空间是在栈上,在linux下buffer[elem_size]
    //可以在运行确定其数组大小,但在VC下栈上空间大小是在编译时就要确定,
    char *buffer = (char *)malloc(elem_size*(sizeof(char)));
    char  *alter_num, *wait_record , *lift_child,*right_child;


    alter_num =  (char *)malloc(elem_size*(sizeof(char)));
    wait_record =  (char *)malloc(elem_size*(sizeof(char)));
    lift_child =  (char *)malloc(elem_size*(sizeof(char)));
    right_child =  (char *)malloc(elem_size*(sizeof(char)));

    int max_num_index = 0;  //记录最大数的下标





    //每次沿最大的孩子节点向下筛选
    for (max_num_index = 2 * index; max_num_index <= need_adjust_length; max_num_index *= 2)
    {
        // 将heap_array数组中的第index个元素赋给wait_record.
        // 将数组的首地址强制转换成char类型的指针,是利用char类型的大小为1
        // 字节的特性,使heap_array指向index-1个元素的地址,由于不知道所传入
        // 的是什么类型的数据,系统无法确定此数组中一个元素的占多少字节,
        // 跳向下一个元素需要多少字节,所以强制转换为指向char的指针,再加上
        // 参数传入的元素类型大小elem_size和要访问的元素的下标index的乘积,
        // 即偏移地址,即可得到此数组第index个元素的地址.

        memcpy(wait_record,(char *)heap_array + index * elem_size,
               elem_size);


        //取待记录左孩子的值,并赋给lift_chaild变量
        memcpy(lift_child,(char *)heap_array +
               max_num_index * elem_size,elem_size);

        //取待记录右孩子的值,并赋给right_chaild变量
        memcpy(right_child,(char *)heap_array +
               (max_num_index+1) * elem_size,elem_size);

        //如果待调整记录的左孩子存在,且其右孩子大于于其左孩子的值,则
        //把右孩子的下标记录下来.否则,把待调整记录的下标记录下来.
        if (max_num_index < need_adjust_length && memcmp(lift_child,
                right_child,elem_size) < 0)
        {
            max_num_index = max_num_index + 1;

        }

        memcpy(alter_num,(char *)heap_array +
               max_num_index * elem_size,elem_size);
        //如果待调整记录最大,则跳出循环
        if ( memcmp(alter_num,wait_record,elem_size ) < 0)
        {
            break;
        }
        //如果待调整记录小于其或右孩子,则将待调整记录的左,右孩子中最
        //大的和其交换
        memcpy(buffer,wait_record,elem_size);

        memcpy((char *)heap_array+ index*elem_size, (char *)heap_array + max_num_index
               * elem_size,elem_size);

        memcpy((char *)heap_array + max_num_index * elem_size,
               buffer,elem_size);

        index = max_num_index;
    }
    free(alter_num);
    free(wait_record);
    free(lift_child);
    free(right_child);
    free(buffer);
    return  0;
}



//堆调整,将一个无序序列调整成一个堆.(递归法)
//参数heap_array是一个待调整的数组,index是要调整的一个元素下标,
//need_adjust__length表示为需要调整堆的大小(需要调整的数组元素个数),elem_size表示的是数组类型大小.
//返回值 !0 表示非正常返回.
//调整为大顶堆.

static int heap_adjust_B(void *heap_array,int index, int need_adjust_length,int elem_size)
{
    //为什么不用buffer[elem_size],而用malloc申请空间?原因是,
    //buffer[elem_size]分配空间是在栈上,在linux下buffer[elem_size]
    //可以在运行确定其数组大小,但在VC下栈上空间大小是在编译时就要确定,
    char *buffer = (char *)malloc(elem_size*(sizeof(char)));

    int lift_index = 2 * index; //记录index的做孩子的下标
    int right_index = 2 * index + 1;//记录index有孩子的下标
    int max_num_index = 0;  //记录最大数的下标


    char  *alter_num, *lift_child,*right_child, *wait_record;

    alter_num =  (char *)malloc(elem_size*(sizeof(char)));
    wait_record =  (char *)malloc(elem_size*(sizeof(char)));
    lift_child =  (char *)malloc(elem_size*(sizeof(char)));
    right_child =  (char *)malloc(elem_size*(sizeof(char)));

    // 将heap_array数组中的第lift_index个元素赋给lift_record.
    // 将数组的首地址强制转换成char类型的指针,是利用char类型的大小为1
    // 字节的特性,使heap_array指向lift_index个元素的地址,由于不知道所传入
    // 的是什么类型的数据,系统无法确定此数组中一个元素的占多少字节,
    // 跳向下一个元素需要多少字节,所以强制转换为指向char的指针,再加上
    // 参数传入的元素类型大小elem_size和要访问的元素的下标lift_index的乘积,
    // 即偏移地址,即可得到此数组第index个元素的地址.

    //取待记录左孩子的值,并赋给lift_chaild变量
    memcpy(lift_child,(char *)heap_array +
           lift_index * elem_size,elem_size);

    //取待记录右孩子的值,并赋给right_chaild变量
    memcpy(right_child,(char *)heap_array +
           right_index * elem_size,elem_size);

    // 将heap_array数组中的第index个元素赋给wait_record.
    memcpy(wait_record,(char *)heap_array + index * elem_size,
           elem_size);

    //如果待调整记录的左孩子存在,且小于其左孩子的值,则把左孩子的
    //下标记录下来.否则,把待调整记录的下标记录下来.
    if (lift_index <= need_adjust_length && memcmp(wait_record,lift_child,
                                            elem_size) < 0)
    {
        max_num_index = lift_index;
    }
    else 
    {
        max_num_index = index;
    }

    memcpy(alter_num,(char *)heap_array +
           max_num_index * elem_size,elem_size);
    //让以找出的最大值与待调整记录的右孩子比较,并记录其最大值下标.
    if (right_index <= need_adjust_length && memcmp(alter_num,right_child,
            elem_size) < 0)
    {
        max_num_index = right_index;
    }

    //如果最大值下标不是待调整记录的下标,则把最大值和待调整记录进行交换
    if (max_num_index != index)
    {
        memcpy(buffer,wait_record,elem_size);

        memcpy((char *)heap_array+index*elem_size, (char *)heap_array + max_num_index *
               elem_size,elem_size);

        memcpy((char *)heap_array + max_num_index * elem_size,
               buffer,elem_size);

     //递归调用来重复调整,接着调整交换后的max_num_index下标的记录,使之满足对性质.
        heap_adjust_B(heap_array,max_num_index,need_adjust_length,elem_size); 
    }
        free(buffer);
        free(alter_num);
        free(wait_record);
        free(lift_child);
        free(right_child);

    return 0;
}


//建堆,可一自底向上的用heap_adjust_ 来数组heap_array变成一个堆,
//因为子数组heap_array[(heap_length/2+) ...heap_length]中元素都是叶子
//每个都看作是只含一个元素的堆,过程bulid_heap对树中的每一个其他节点都
//调用一次heap_adjust_ ,对各个节点处理次序保证了以某节点i的子节点为根
//的子树都已成为堆后才处理i.
//参数:*heap_array是所传的数组(从1号下标开始存数),heap_length是数组
//的长度,elem_size是数组中元素类型的大小.
//返回值: !0 表示程序非正常退出.

static int bulid_heap(void *heap_array, int heap_length,int elem_size)
{
    int i;

    //断言处理
    assert(heap_array != NULL && 1 < heap_length && 0 < elem_size);

    for (i = heap_length/2; i > 0 ; i--)
    {
        heap_adjust_A(heap_array, i ,heap_length,elem_size); //非递归法
     
        heap_adjust_B(heap_array, i ,heap_length,elem_size); //递归法
    }

    return 0;
}


//堆排序,根据堆的性质根是最大的(大顶堆)/最小的(小顶堆)可知,
//对堆排序,只需要每次把根输出来就已经是有序的,这要求每次输出
//根后需从新调整堆,将根节点的子节点调整为根,只需将heap_array中
//的最后一个元素和根交换，将根放到了叶子上，叶子放到了根上
//(违反了堆性质),再调用heap_adjust_将其调整为堆.
//参数:*heap_array表示的是所传的数组,heap_length表示的数组的长度,
//elem_size表示的是数组类型大小.
//return: !0表示的函数非正常退出.

 int heap_sort(void *heap_array, int heap_length,int elem_size)
{
    int i = 0, k =1;

    char *buffer = (char *)malloc(elem_size*sizeof(char));

    //堆建立函数调用
    bulid_heap(heap_array,heap_length,elem_size);

    for (i = 1 ; i < heap_length+1; i++)
    {

        printf("%d ",*((char *)heap_array+elem_size*i));
    }

    printf("over\n");

    //将根和叶子节点进行交换,并调整堆
    for (i = heap_length; i > 1; i--,k++)
    {
       // printf("ss=%d ",*((char *)heap_array+elem_size));

        //将叶和根进行交换,使得此根在下一次调整时就可跳过,
        memcpy(buffer,(char *)heap_array+elem_size,elem_size);

        memcpy((char *)heap_array + elem_size,(char *)heap_array + elem_size * i, elem_size);

        memcpy((char *)heap_array+elem_size*i,buffer,elem_size);

        //调整堆,叶变成根后破坏了堆性质,所以要对根作调整.调整时,数组长度
        //为i-1,因为根已经访问过了,把根放到叶子上了,下次堆调整时就可通过
        //i-1控制对调整长度,而使的略过对上一个根的再次调整,
        
        heap_adjust_B(heap_array,1,i - 1,elem_size);//递归法调整
    
        heap_adjust_A(heap_array,1, i-1 ,elem_size);//非递归法调整

    }

    free(buffer);
    return 0;
}





//打印数组
//参数:heap_array是排序的数组,heap_length是数组的长度,
//elem_size表示的是数组类型大小,style表示想要打印的格式["%d","%c","%u","%f",]等.
//return: !0 表示非正常退出函数.
int print_array(void *heap_array,int heap_length,int elem_size,char *style)
{
    int i = 1;
    for (i = 1; i < heap_length+1; i++ )
    {
        printf(style,*((char *)heap_array+i*elem_size));
    }
    printf("/n");
    return 0;
}



int main(int argc,char *argv[])
{

    int i = 0;
    int a[NUM];
    char *style="%d "; //数组输出格式设置

    printf("输入%d个整数\n",NUM-1);
    for (i = 1; i< NUM; i++)
        scanf("%d",&a[i]);

    heap_sort(a,5,sizeof(int));

    print_array(a,NUM-1, sizeof(int), style);


    return 0;
}
