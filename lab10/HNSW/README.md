# 2024-spring-data_structure-NSW
## Develop Log
### 姜俊彦&邱明阳
- 2024.5.28
  - git工程建立，协作邀请完毕
- 2024.6.10-2024.6.12
  - 调研文章：[《一文看懂HNSW算法理论的来龙去脉》](https://blog.csdn.net/u011233351/article/details/85116719)
    - 理解NSW和HNSW的构图思想与查找方法
  - 调研文章：[HNSW的基本原理及应用](https://xzyin.github.io/%E7%AE%97%E6%B3%95/hnsw/)
- 2024.6.17
  - 调研文章：[python图片转向量](https://blog.51cto.com/u_16175526/9799368)
  - 调研文章：[图片转化为向量Tensor的方法](https://blog.csdn.net/weixin_42535423/article/details/122106480)
  - 调研文章：[向量数据库？那咱们就浅谈一下吧](https://cloud.tencent.com/developer/article/2333720)
    - Mark：评分算法
- 2024.6.17-2024.6.22
  - 数据集建构完毕（含下载、格式化处理，向量化）
    - [花卉数据集](https://www.kaggle.com/datasets/alxmamaev/flowers-recognition)
    - [衣服数据集](https://www.kaggle.com/datasets/agrigorev/clothing-dataset-full)
    - [商标数据集](https://github.com/msn199959/Logo-2k-plus-Dataset)
    - [飞机数据集](https://www.kaggle.com/datasets/seryouxblaster764/fgvc-aircraft)
    - [食物图像数据集](https://www.kaggle.com/datasets/kmader/food41)
  - 距离函数编写完毕
  - 主函数接口部分基本编写完毕
  - HNSW算法编写开始，初步编写了HNSW核心算法，还未测试
  - 暴力搜索性能测试算法初步编写，测试，还未接入
- 2024.6.22-2024.6.26
  - 主算法编写完成，Debug完成
- 2024.6.27-2024.6.29
  - 批处理脚本编写完成
  - 性能评估函数编写完成
  - 批处理运行完毕
- 2024.6.30
  - 实验报告撰写完毕