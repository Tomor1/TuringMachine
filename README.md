应提交的文档结构解压示例如下：

$ > cmake . -B build
$ > cd build
$ > make
$ > ../bin/turing <-v|verbose> <-h|--help> .tm input1 input2 ...
input最多可以输入N个

可能因为系统原因导致.tm在clone到Linux后无法识别，在Linux下新建.tm拷贝过去即可
