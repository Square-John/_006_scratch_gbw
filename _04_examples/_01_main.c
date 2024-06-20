/*
程序功能介绍：本程序通过工标网，进行建筑规范批量查新工作

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 200       // 规范名称最大长度
#define MAX_SERIAL 200     // 规范编号最大长度
#define MAX_STANDARD 100   // 规范最大数量
#define MAX_RESULT 50      // 规范查询结果最大长度
#define PATH_LEN 512       // 文件路径最大长度
#define LINE_MAX_LENTH 512 // 读取一行的最大长度

// 保存规范信息的结构体
typedef struct st_info {
  int serial;                     // 规范序号
  char name[MAX_NAME];            // 规范名称
  char serial_number[MAX_SERIAL]; // 规范编号
  char name_result
      [MAX_RESULT]; // 规范名称查询结果,现行、即将实施、作废、废止、未找到
  char serial_number_result
      [MAX_RESULT]; // 规范编号查询结果,现行、即将实施、作废、废止、未找到
  char name_get_serial[MAX_SERIAL]; // 按名称查找得到的规范编号
  char serial_number_get_name[MAX_NAME]; // 按规范编号查找得到的规范名称
  char result[MAX_RESULT];
  // 如果名称和编号查找都“未找到”，结果为无此规范
  // 如果按名称找到规范编号和规范编号不一致，结果为名称对，编号不对
  // 如果按规范编号找到规范名称和规范名称不一致，结果为编号对，名称不对
  // 否则为正确
} Standard_Info;

/*
函数功能：按行读取指定文件的内容并返回读取到的值
参数说明：
    fp：需要读取的文件
    standard_info_array：存放读取到的值的数组
    max_line：最大读取的行数
返回值：
    成功则返回读取到的行数
    读取失败返回-1

*/

int read_file_info(FILE *fp, Standard_Info *standard_info_array, int max_line);

int main(int argc, char *argv[]) {

  // 步骤1：读取"_02_files\_01_input_file\standrad_file.txt"中的内容并保存在结构体数组中
  // 1.1 定义结构体数组
  Standard_Info st_info[MAX_STANDARD];
  // 1.2 指定文件路径
  char input_file_path[PATH_LEN] =
      "_02_files\\_01_input_file\\standrad_file.txt";
  // 1.3 打开文件
  FILE *input_file = fopen(input_file_path, "r");
  // 1.4 文件打开失败处理
  if (input_file == NULL) {
    printf("文件打开失败！\n");
    return 0;
  }
  // 1.5 读取文件
  read_file_info(input_file, st_info, MAX_STANDARD);

  // 1.6 关闭文件
  fclose(input_file);

  return 0;
}

/*
函数功能：按行读取指定文件的内容并返回读取到的值
参数说明：
    fp：需要读取的文件
    standard_info_array：存放读取到的值的数组
    max_line：最大读取的行数
返回值：
    成功则返回读取到的行数
    读取失败返回-1

*/

int read_file_info(FILE *fp, Standard_Info *standard_info_array, int max_line) {
  // 1、定义一个字符串数组
  char line[LINE_MAX_LENTH];

  // 2、定义一个变量记录读取到的行数
  int line_count = 0;

  // 3、按行读取文件
  while (fgets(line, LINE_MAX_LENTH, fp) != NULL && line_count < max_line)
  {
    
  }

    return line_count;
  }
