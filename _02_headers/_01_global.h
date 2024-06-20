#ifndef __01_GLOBAL_H_
#define __01_GLOBAL_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENTH 512    // 规范名字的最大长度
#define SERIAL_LENGTH 512 // 规范编号最大长度
#define DATE_LENGTH 32    // 规范实施日期最大长度
#define STATUS_LENGTH 32  // 规范状态最大长度

// 规范信息保存结构体
typedef struct {
  int num;                    // 序号
  char name[NAME_LENTH];      // 规范名字
  char serial[SERIAL_LENGTH]; // 规范编号
  char date[DATE_LENGTH];     // 规范实施日期
  char status[STATUS_LENGTH]; // 规范状态，未找到、即将实施、现行、作废、废止
  int flag; // 标记位，1表示已记录规范名字，2标识已记录规范编号，3表示已进行查新
} St_Info;


#define ST_ARR_LENGTH 100      // 结构体数组最大长度
#define SINGLE_LINE_LENGTH 512 // 单行读取最大长度

// 输入文件文件路径
#define INPUT_FILE_PATH "_03_files\\_01_input_file\\standrad_file.txt"
// 保存文件路径
#define SAVE_PATH "_06_temp_files/"
//保存文件名字
#define SAVE_FILE_NAME "response.html"
// 文件路径最大长度
#define FILE_PATH_LENGTH 2048

// 工标网（请求网站域名)
#define HOST "www.csres.com"
// 工标网（请求网站IP)
#define IP "211.152.51.146"
// HTTP请求端口
#define PORT 80

// HTTP请求头最大长度
#define HTTP_HEADER_LENGTH 2048
// HTTP请求头字符串
// http://www.csres.com/s.jsp?keyword=%BB%EC%C4%FD%CD%C1&submit12=%B1%EA%D7%BC%CB%D1%CB%F7&xx=on&wss=on&zf=on&fz=on&pageSize=50&pageNum=1&SortIndex=1&WayIndex=0&nowUrl=
#define HTTP_REQUEST                                                           \
  "GET /s.jsp?keyword=%s&pageSize=%d&pageNum=%d HTTP/1.1\r\nHost: %s\r\n\r\n"
// HTTP响应内容最大长度
#define HTTP_RESPONSE_LENGTH 1024 * 1024

// 获取响应内容的最大数目
#define PAGE_SIZE 50
// 获取响应内容的第几页
#define PAGE_NUM 1

#endif