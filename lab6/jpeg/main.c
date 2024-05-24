#include "jpg_decode.h"

jpg *ReadJPG(char *filename);
void CreateTable(jpg *JPG);
void PrintTable(jpg *JPG);
void DestroyJPG(jpg *JPG);

int main() {
    char *filename = "test.jpg"; //目录下的jpg文件
    jpg *JPG;
    JPG = ReadJPG(filename); //读取jpg文件到数组
    CreateTable(JPG); //遍历数组，读取并存储各个表段的数据，包括建立哈夫曼树
    PrintTable(JPG); //打印各个表段的数据
    DestroyJPG(JPG); //释放内存
    return 0;
}