/*--------以下为读取JPG文件、分类存储标记后数据并分析各类数据的函数--------*/
#include "jpg_decode.h"

void CreateDHT(jpg *JPG);
void PrintTree(huffman *tree, int n);

jpg *ReadJPG(char *filename) { //读取jpg文件到数组
    jpg *JPG;
    JPG = (jpg*)malloc(sizeof(jpg));
    JPG->size = 0;
    JPG->APPn = (appn*)malloc(15 * sizeof(appn));
    JPG->DHT = NULL;
    FILE *file;
    size_t bytes_read;
    printf("----------------------------------------------------------------\n");
    printf("开始读取%s···\n", filename);
    if ((file = fopen(filename, "rb")) == NULL) { //以二进制方式打开文件
        fprintf(stderr, "无法打开 %s\n", filename); //打开失败
        return NULL;
    }
    bytes_read = fread(JPG->data, 1, MAX_SIZE, file); //读取文件到buffer中
    JPG->size = bytes_read;
    /*打印文件内容
    for (int i = 0; i < bytes_read; i += 16) { //每行打印16个字节
        for (int j = 0; j < 16 && i + j < bytes_read; j++) { //打印每个字节
            printf("%02x ", buffer[i + j]);
        }
        printf("\n");
    }
    */
    fclose(file);
    printf("读取完毕，该JPEG文件有%d个字节。\n", JPG->size);
    printf("----------------------------------------------------------------\n");
    return JPG;
}

//遍历数组，读取并存储各个表段的数据
void CreateTable(jpg *JPG) {
    int i = 0; //全局指针
    int j = 0; //各表段用指针
    int k = 0; //各表段用计数器
    printf("----------------------------------------------------------------\n");
    printf("开始读取并存储各表段数据\n");
    while (i < JPG->size) { //遍历数组
        //跳过无意义填充
        if (JPG->data[i] == 0xff && JPG->data[i + 1] == 0xff) {
            i += 1; 
            continue; 
        }
        
        //SOI段 图像开始
        if (JPG->data[i] == 0xff && JPG->data[i + 1] == 0xd8) {
            printf("SOI  图像开始\n");
            i += 2; //跳过FFD8
            continue; 
        }
        
        //APP0段 应用程序保留标记0
        if (JPG->data[i] == 0xff && JPG->data[i + 1] == 0xe0) {
            printf("APP0 应用程序保留标记0\n");
            i += 2; //跳过FFE0
            j = i; //备份指针
            JPG->APP0 = (app0*)malloc(sizeof(app0));
            JPG->APP0->data = JPG->data + i;
            JPG->APP0->size = JPG->data[i] * 256 + JPG->data[i + 1]; //数据长度
            i += 2;
            strncpy(JPG->APP0->id, JPG->data + i, 5); //标识符
            i += 5;
            JPG->APP0->version = JPG->data[i] + JPG->data[i + 1] / 10.0; //版本号
            i += 2;
            JPG->APP0->density_unit = JPG->data[i]; //密度单位
            i += 1;
            JPG->APP0->x_density = JPG->data[i] * 256 + JPG->data[i + 1]; //水平像素密度
            i += 2;
            JPG->APP0->y_density = JPG->data[i] * 256 + JPG->data[i + 1]; //垂直像素密度
            i += 2;
            JPG->APP0->x_thumbnail = JPG->data[i]; //缩略图水平像素数
            i += 1;
            JPG->APP0->y_thumbnail = JPG->data[i]; //缩略图垂直像素数
            i += 1;
            if(JPG->APP0->size - 16 > 0){ //缩略图数据
                JPG->APP0->thumbnail = (unsigned char*)malloc(JPG->APP0->size - 16 * sizeof(unsigned char));
                JPG->APP0->thumbnail = JPG->data + i;
                i += JPG->APP0->size - 16;
            }
            continue;
        }

        //APPn段 应用程序保留标记n
        if (JPG->data[i] == 0xff && JPG->data[i + 1] >= 0xe1 && JPG->data[i + 1] <= 0xef) {
            printf("APP%x 应用程序保留标记%d\n", JPG->data[i + 1] % 16, JPG->data[i + 1] - 0xe0);
            k = JPG->data[i + 1] - 0xe1;
            i += 2; //跳过FFEn
            j = i; //备份指针
            JPG->APPn[k].data = JPG->data + i;
            JPG->APPn[k].size = JPG->data[i] * 256 + JPG->data[i + 1]; //数据长度
            i += 2;
            while(i < j + JPG->APPn[k].size) { //数据
                i += 1;
            }//事实上跳过了APPD段内的副本图像
            continue;
        }

        //DQT段 定义量化表
        if (JPG->data[i] == 0xff && JPG->data[i + 1] == 0xdb) {
            printf("DQT  定义量化表\n");
            i += 2; //跳过FFDB
            j = i; //备份指针
            JPG->DQT = (dqt*)malloc(sizeof(dqt));
            JPG->DQT->data = JPG->data + i;
            JPG->DQT->size = JPG->data[i] * 256 + JPG->data[i + 1]; //数据长度
            for (k = 0; k < 4; k++)
                JPG->DQT->component[k].precision = -1;
            i += 2;
            k = 0;
            while(i < j + JPG->DQT->size) { //读取1~4个量化表
                JPG->DQT->component[k].precision = JPG->data[i] / 16; //精度
                JPG->DQT->component[k].id = JPG->data[i] % 16; //量化表ID
                i += 1;
                JPG->DQT->component[k].table = JPG->data + i; //量化表
                i += 64 * (JPG->DQT->component[k].precision + 1);
                k += 1;
            }
            continue;
        }

        //SOF0段 帧图像开始
        if (JPG->data[i] == 0xff && JPG->data[i + 1] == 0xc0) {
            printf("SOF0 帧图像开始\n");
            i += 2; //跳过FFC0
            j = i; //备份指针
            JPG->SOF0 = (sof0*)malloc(sizeof(sof0));
            JPG->SOF0->data = JPG->data + i;
            JPG->SOF0->size = JPG->data[i] * 256 + JPG->data[i + 1]; //数据长度
            i += 2;
            JPG->SOF0->precision = JPG->data[i]; //精度
            i += 1;
            JPG->SOF0->height = JPG->data[i] * 256 + JPG->data[i + 1]; //图像高度
            i += 2;
            JPG->SOF0->width = JPG->data[i] * 256 + JPG->data[i + 1]; //图像宽度
            i += 2;
            JPG->SOF0->num = JPG->data[i]; //颜色分量数
            i += 1;
            for (k = 0; k < JPG->SOF0->num; k++) { //颜色分量
                JPG->SOF0->component[k].id = JPG->data[i]; //颜色分量ID
                i += 1;
                JPG->SOF0->component[k].x_sampling = JPG->data[i] / 16; //水平采样因子
                JPG->SOF0->component[k].y_sampling = JPG->data[i] % 16; //垂直采样因子
                i += 1;
                JPG->SOF0->component[k].quantization_table = JPG->data[i]; //量化表ID
                i += 1;
            }
            continue;
        }

        //DRI段 定义RST间隔
        if (JPG->data[i] == 0xff && JPG->data[i + 1] == 0xdd) {
            printf("DRI  定义RST间隔\n");
            i += 2; //跳过FFDD
            j = i; //备份指针
            JPG->DRI = (dri*)malloc(sizeof(dri));
            JPG->DRI->data = JPG->data + i;
            JPG->DRI->size = JPG->data[i] * 256 + JPG->data[i + 1]; //数据长度
            i += 2;
            JPG->DRI->interval = JPG->data[i] * 256 + JPG->data[i + 1]; //RST间隔
            i += 2;
            continue;
        }

        //DHT段 定义哈夫曼树表
        if (JPG->data[i] == 0xff && JPG->data[i+1] == 0xc4) {
            printf("DHT  定义哈夫曼树表\n");
            i += 2; //跳过FFC4
            JPG->DHT = (dht*)malloc(sizeof(dht));
            JPG->DHT->data = JPG->data + i;
            JPG->DHT->size = JPG->data[i] * 256 + JPG->data[i + 1]; //数据长度
            CreateDHT(JPG);
            i += JPG->DHT->size; //跳过DHT段
            continue;
        }

        //SOS段 扫描开始
        if (JPG->data[i] == 0xff && JPG->data[i + 1] == 0xda) {
            printf("SOS  扫描开始\n");
            i += 2; //跳过FFDA
            j = i; //备份指针
            JPG->SOS = (sos*)malloc(sizeof(sos));
            JPG->SOS->data = JPG->data + i;
            JPG->SOS->size = JPG->data[i] * 256 + JPG->data[i + 1]; //数据长度
            i += 2;
            JPG->SOS->num = JPG->data[i]; //颜色分量数
            i += 1;
            for (k = 0; k < JPG->SOS->num; k++) { //颜色分量
                JPG->SOS->component[k].id = JPG->data[i]; //颜色分量ID
                i += 1;
                JPG->SOS->component[k].dc_id = JPG->data[i] / 16; //DC表ID
                JPG->SOS->component[k].ac_id = JPG->data[i] % 16; //AC表ID
                i += 1;
            }
            JPG->SOS->start = JPG->data[i]; //谱选择开始
            i += 1;
            JPG->SOS->end = JPG->data[i]; //谱选择结束
            i += 1;
            JPG->SOS->selection = JPG->data[i]; //谱选择
            i += 1;
            JPG->imagedata = JPG->data + i;
            JPG->imagesize = JPG->size - i - 2; //图像数据字节数
            i += JPG->imagesize; //跳出循环
            continue;
        }
        
        //EOI段 图像结束
        if (JPG->data[i] == 0xff && JPG->data[i + 1] == 0xd9) {
            printf("EOI  图像结束\n");
            i += 2; //跳过FFD9
            continue;
        }
        i++;
    }
    printf("读取并存储完毕\n");
    printf("----------------------------------------------------------------\n");
}


//读取各表段数据，并打印至终端
void PrintTable(jpg *JPG) {
    int temp_int;
    printf("----------------------------------------------------------------\n");
    printf("打印各表段数据\n");
    printf("\n");

    //打印APP0段数据
    if(JPG->APP0 != NULL){
        printf("APP0 应用程序保留标记0\n");
        printf("数据长度：%d\n", JPG->APP0->size);
        printf("标识符：%s\n", JPG->APP0->id);
        printf("版本号：%f\n", JPG->APP0->version);
        temp_int = JPG->APP0->density_unit;
        if(temp_int == 0)
            printf("密度单位：无单位\n");
        else if(temp_int == 1)
            printf("密度单位：点数/英寸\n");
        else if(temp_int == 2)
            printf("密度单位：点数/厘米\n");
        else
            printf("密度单位：未知\n");
        printf("水平像素密度：%d\n", JPG->APP0->x_density);
        printf("垂直像素密度：%d\n", JPG->APP0->y_density);
        printf("缩略图水平像素数：%d\n", JPG->APP0->x_thumbnail);
        printf("缩略图垂直像素数：%d\n", JPG->APP0->y_thumbnail);
        temp_int = JPG->APP0->size - 16;
        if (temp_int == 0)
            printf("缩略图数据：无\n");
        else{
            printf("缩略图数据：\n");
            for (int i = 0, j = 0; i < JPG->APP0->size - 16; i++, j++) {
                printf("%02x ", JPG->APP0->thumbnail[i]);
                if(j == 16){
                    printf("\n");
                    j = 0;
                }
            }
            printf("\n");
        }
        printf("----------------------------------------------------------------\n");
        printf("\n");
    }

    //打印APPn段数据
    for (int i = 0; i < 15; i++) {
        if(JPG->APPn[i].size == 0)
            continue;
        printf("APP%x 应用程序保留标记%d\n", i + 1, i + 1);
        printf("数据长度：%d\n", JPG->APPn[i].size);
        printf("数据：\n");
        //以ASSIC码形式打印数据
        for (int j = 2; j < JPG->APPn[i].size; j++) {
            if(JPG->APPn[i].data[j] == 0xff && JPG->APPn[i].data[j+1] == 0xd8){
                while(JPG->APPn[i].data[j] != 0xff || JPG->APPn[i].data[j+1] != 0xd9){
                    j++;
                }
                j++;
                continue;
            }
            
            if(JPG->APPn[i].data[j] == 0x0a){
                printf("\n");
                continue;
            }

            if(JPG->APPn[i].data[j] == 0x0d){
                printf("\n");
                continue;
            }

            if(JPG->APPn[i].data[j] == 0x20){
                printf(" ");
                continue;
            }
                
            if (JPG->APPn[i].data[j] >= 32 && JPG->APPn[i].data[j] <= 126) {
                printf("%c", JPG->APPn[i].data[j]);
                continue;
            }

            if ((JPG->APPn[i].data[j] < 32 || JPG->APPn[i].data[j] > 126) 
            && (JPG->APPn[i].data[j + 1] < 32 || JPG->APPn[i].data[j + 1] > 126)) {
                j += 1;
                continue;
            }

            if (JPG->APPn[i].data[j] < 32 || JPG->APPn[i].data[j] > 126) {
                printf(" ");
                continue;
            }
        }
        printf("\n");
        printf("----------------------------------------------------------------\n");
        printf("\n");
    }

    //打印DQT段数据
    printf("DQT  定义量化表\n");
    printf("数据长度：%d\n", JPG->DQT->size);
    for(int i = 0; i < 4; i++) {
        if(JPG->DQT->component[i].precision == -1)
            continue;
        printf("量化表ID：%d\n", JPG->DQT->component[i].id);
        printf("精度：%d\n", JPG->DQT->component[i].precision);
        printf("量化表：\n");
        for (int j = 0; j < 64 * (1 + JPG->DQT->component[i].precision); j++) {
            printf("%3d ", JPG->DQT->component[i].table[j]);
            if(j % 8 == 7)
                printf("\n");
        }
    }
    printf("----------------------------------------------------------------\n");
    printf("\n");

    //打印SOF0段数据
    printf("SOF0 帧图像开始\n");
    printf("数据长度：%d\n", JPG->SOF0->size);
    printf("精度：%d\n", JPG->SOF0->precision);
    printf("图像高度：%d\n", JPG->SOF0->height);
    printf("图像宽度：%d\n", JPG->SOF0->width);
    printf("颜色分量数：%d\n", JPG->SOF0->num);
    printf("\n");
    for (int i = 0; i < JPG->SOF0->num; i++) {
        printf("颜色分量ID：%d\n", JPG->SOF0->component[i].id);
        printf("水平采样因子：%d\n", JPG->SOF0->component[i].x_sampling);
        printf("垂直采样因子：%d\n", JPG->SOF0->component[i].y_sampling);
        printf("量化表ID：%d\n", JPG->SOF0->component[i].quantization_table);
        printf("\n");
    }
    printf("----------------------------------------------------------------\n");
    printf("\n");

    //打印DRI段数据
    if(JPG->DRI != NULL){
        printf("DRI  定义RST间隔\n");
        printf("数据长度：%d\n", JPG->DRI->size);
        printf("RST间隔：%d\n", JPG->DRI->interval);
        printf("----------------------------------------------------------------\n");
        printf("\n");
    }
    
    //打印DHT段数据
    printf("DHT  定义哈夫曼树表\n");
    printf("数据长度：%d\n", JPG->DHT->size);
    printf("\n");
    for(int i = 0; i < 4; i++) {
        if(JPG->DHT->num[i][16] == -1)
            continue;
        printf("表号：%d\n", i);
        printf("这是第%d张", JPG->DHT->num[i][16] % 16 + 1);
        if(JPG->DHT->num[i][16] / 16 == 0)
            printf("直流表\n");
        else
            printf("交流表\n");
        printf("哈夫曼表：\n");
        printf(" key值| 码值\n");
        PrintTree(JPG->DHT->tree, i);
        printf("\n");
    }
    printf("----------------------------------------------------------------\n");
    printf("\n");

    //打印SOS段数据
    printf("SOS  扫描开始\n");
    printf("数据长度：%d\n", JPG->SOS->size);
    printf("颜色分量数：%d\n", JPG->SOS->num);
    printf("\n");
    for (int i = 0; i < JPG->SOS->num; i++) {
        printf("颜色分量ID：%d\n", JPG->SOS->component[i].id);
        printf("DC表ID：%d\n", JPG->SOS->component[i].dc_id);
        printf("AC表ID：%d\n", JPG->SOS->component[i].ac_id);
        printf("\n");
    }
    printf("谱选择开始：%d\n", JPG->SOS->start);
    printf("谱选择结束：%d\n", JPG->SOS->end);
    printf("谱选择：%d\n", JPG->SOS->selection);
    printf("\n");
    printf("图像数据：（共%d个字节）\n", JPG->imagesize);
    //只打印前16行和后16行
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            printf("%02x ", JPG->imagedata[i * 16 + j]);
        }
        printf("\n");
    }
    printf("......\n");
    for (int i = JPG->imagesize - JPG->imagesize % 16 - 256, j = 0; i < JPG->imagesize; i++, j++) {
        printf("%02x ", JPG->imagedata[i]);
        if(j % 16 == 15)
            printf("\n");
    }
    printf("\n");
}

//销毁所有表段数据
void DestroyTable(jpg *JPG) {
    free(JPG->APP0);
    free(JPG->APPn);
    free(JPG->DQT);
    free(JPG->SOF0);
    free(JPG->DRI);
    free(JPG->DHT);
    free(JPG->SOS);
    free(JPG);
}