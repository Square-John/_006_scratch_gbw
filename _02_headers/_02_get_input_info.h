#ifndef __02_GET_INPUT_INFO_H_
#define __02_GET_INPUT_INFO_H_

#include "_01_global.h"

/**
 * 函数功能：获取输入文件内容
 * 参数：
 *  st_arr：存放输入文件的结构体数组
 *  max_lines：最多读取行数
 *  max_line_length：每行最大读取字符长度
 * 返回值：返回读取的行数,-1表示读取失败
 */

int read_input(St_Info *st_arr, int max_lines, int max_line_length);

/*
函数功能：按行读取输入文件信息，并将信息保存到St_Info结构体数组中
参数：
    FILE *fp：输入文件指针
    St_Info *info：St_Info结构体数组指针
    int max_lines：最大读取行数
    int max_chars：单行最大读取字符数
    int line_count：当前读取行数

返回值：有效读取行数
*/
int get_input_info(St_Info *st_arr, FILE *input_file, int max_lines,
                   int max_chars);

#endif
