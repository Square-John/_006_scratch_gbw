#include "_04_reduce_response.h"

/**
 * 函数功能：对response.html文件的内容进行信息提取，获取规范的标准名称、标准编号、发布部门、实施日期和状态信息
 *
 */

int reduce_response() {

  // 1、打开response.html文件
  FILE *fp = fopen(SAVE_PATH SAVE_FILE_NAME, "r");
  if (fp == NULL) {
    printf("打开response.html文件失败\n");
    return -1;
  }

  printf("打开response.html文件成功\n");

  // 读取文件内容到response中
  char response[HTTP_RESPONSE_LENGTH + 10];
  // 定义一个char指针指向response
  char *p = response;
  char c;
  while ((c = fgetc(fp)) && p - response < HTTP_RESPONSE_LENGTH) {
    //打印p-response
    // printf("%lld\n", p - response);
    // 将读取到的字符写入response中
    *p = (char)c;
    p++;
  }
  //打印response
  // printf("response:%s\n", response);

  fclose(fp);

  return 0;
}