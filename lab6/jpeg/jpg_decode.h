#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50000 //实际有28521个字节

/*--------以下是所用到的结构体类型的定义--------*/

//APP0段数据
typedef struct app0{
    unsigned char *data; //数据起始位置
    int size; //数据长度
    char id[5]; //标识符
    float version; //版本号
    int density_unit; //密度单位
    int x_density; //水平像素密度
    int y_density; //垂直像素密度
    int x_thumbnail; //缩略图水平像素数
    int y_thumbnail; //缩略图垂直像素数
    unsigned char *thumbnail; //缩略图数据
} app0;

//APPn段数据
typedef struct appn{
    int num; //标记号
    unsigned char *data; //数据起始位置
    int size; //数据长度
} appn;

//DQT段数据
typedef struct dqt{
    unsigned char *data; //数据起始位置
    int size; //数据长度
    struct {
        int precision; //精度
        int id; //量化表ID
        unsigned char *table; //量化表
    } component[4]; //最多4个量化表
} dqt;

//SOF0段数据
typedef struct sof0{
    unsigned char *data; //数据起始位置
    int size; //数据长度
    int precision; //精度
    int height; //图像高度
    int width; //图像宽度
    int num; //颜色分量数
    struct {
        int id; //颜色分量ID
        int x_sampling;//水平采样因子
        int y_sampling;//垂直采样因子
        int quantization_table; //量化表ID
    } component[3]; //3个颜色分量
} sof0;

//DRI段数据
typedef struct dri{
    unsigned char *data; //数据起始位置
    int size; //数据长度
    int interval; //RST间隔
} dri;

//哈夫曼树
typedef struct huffman{
    int code; //码字
    int length; //码字长度
    int value; //码字对应的值
    struct huffman *left; //左子树
    struct huffman *right; //右子树
} huffman;

//DHT段数据
typedef struct dht{
    unsigned char *data; //数据起始位置
    int size; //数据长度
    int num[4][18]; //0~15各位长码字数量 16直流交流类型 17码字总数
    huffman *tree; //哈夫曼树
} dht;

//SOS段数据
typedef struct sos{
    unsigned char *data; //数据起始位置
    int size; //数据长度
    int num; //颜色分量数
    struct {
        int id; //颜色分量ID
        int dc_id; //DC表ID
        int ac_id; //AC表ID
    } component[3]; //3个颜色分量
    int start; //谱选择开始
    int end; //谱选择结束
    int selection;//谱选择
} sos;

//jpg文件
typedef struct{
    int size; //字节总数
    unsigned char data[MAX_SIZE]; //全部数据
    int imagesize; //图像数据字节数
    unsigned char *imagedata; //SOI数据
    app0 *APP0; //APP0数据
    appn *APPn; //APPn数据
    dqt *DQT; //DQT数据
    sof0 *SOF0; //SOF0数据
    dri *DRI; //DRI数据
    dht *DHT; //DHT数据
    sos *SOS; //SOS数据
}jpg;