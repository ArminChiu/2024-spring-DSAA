//堆排序
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 20000
float begin, end;

//堆的数据结构
typedef struct {
    int *data;
    int length;
} HeapType;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//将一个无序数组调整为堆，然后打印堆，最后再输出堆排序的结果
void HeapSort(HeapType *H){
    int i;
    //调整为堆
    for(i = H->length / 2; i > 0; i--){
        //从最后一个非叶子节点开始调整
        int parent = i;
        int child = 2 * parent;
        while(child <= H->length){
            if(child + 1 <= H->length && H->data[child] < H->data[child + 1]){
                child++;
            }
            if(H->data[parent] >= H->data[child]){
                break;
            }
            swap(&H->data[parent], &H->data[child]);
            parent = child;
            child = 2 * parent;
        }
    }
    /*打印堆
    for(i = 1; i <= H->length; i++){
        printf("%d ", H->data[i]);
    }
    printf("\n");
    */
    //堆排序
    for(i = H->length; i > 1; i--){
        swap(&H->data[1], &H->data[i]);
        int parent = 1;
        int child = 2 * parent;
        while(child <= i - 1){
            if(child + 1 <= i - 1 && H->data[child] < H->data[child + 1]){
                child++;
            }
            if(H->data[parent] >= H->data[child]){
                break;
            }
            swap(&H->data[parent], &H->data[child]);
            parent = child;
            child = 2 * parent;
        }
    }
}

int main(){
    printf("HeapSort\n");
    float time = 0.0;
    HeapType *heap;
    heap = (HeapType *) malloc(sizeof(HeapType));
    heap->data = (int *) malloc(sizeof(int) * MAX);
    heap->length = 20000;
    //正序
    for(int j = 0; j < 10; j++){
        for(int i = 1; i <= heap->length; i++){
            heap->data[i] = i - 1;
        }
        begin = clock();
        HeapSort(heap);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time1: %fms\n", time/10);
    time = 0.0;
    //逆序
    for(int j = 0; j < 10; j++){
        for(int i = 1; i <= heap->length; i++){
            heap->data[i] = heap->length - i;
        }
        begin = clock();
        HeapSort(heap);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time2: %fms\n", time/10);
    time = 0.0;
    //随机
    for(int j = 0; j < 10; j++){
        for(int i = 1; i <= heap->length; i++){
            heap->data[i] = rand() % heap->length;
        }
        begin = clock();
        HeapSort(heap);
        end = clock();
        time += (end - begin)/CLOCKS_PER_SEC*1000;
    }
    printf("Time3: %fms\n", time/10);
    return 0;
}
