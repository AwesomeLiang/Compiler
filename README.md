# 东北大学编译原理课程设计

- 环境：Vs2017

- 前端：LL(1)文法分析

- 后端： 四元式生成汇编，适配Goasm

- 优化：Dag图配合Graphviz可视化

- 文件说明：

  - test.txt 源程序文件 符合C语言文法 以#结尾

  - dag.dot  Dag优化过程文件 

    ```bash
    dot -png dag.dot -o dag.png
    ```

    