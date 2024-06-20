#include "_02_get_input_info.h"

/**
 * 函数功能：获取输入文件内容
 * 参数：
 *  st_arr：存放输入文件的结构体数组
 *  max_lines：最多读取行数
 *  max_line_length：每行最大读取字符长度
 * 返回值：返回读取的行数,-1表示读取失败
 */

int read_input(St_Info *st_arr, int max_lines, int max_line_length) {

  // 以只读方式打开输入文件
  FILE *input_file = fopen(INPUT_FILE_PATH, "r");

  // 文件打开失败处理
  if (input_file == NULL) {
    printf("文件打开失败！\n");
    return -1;
  }

  // 文件打开成功，则进行读取处理，每次读取一行，单行最大读取SINGLE_LINE_LENGTH个字符
  int line_count =
      get_input_info(st_arr, input_file, max_lines, max_line_length);

  fclose(input_file);

  // 打印读取成功信息，并输出读取的行数
  printf("读取成功！共成功读取 : %d 行。\n", line_count);

  return line_count;
}

/*
函数功能：按行读取输入文件信息，并将信息保存到St_Info结构体数组中
参数：
    FILE *fp：输入文件指针
    St_Info *info：St_Info结构体数组指针
    int max_lines：最大读取行数
    int max_chars：单行最大读取字符数

返回值：有效读取行数
*/
int get_input_info(St_Info *st_arr, FILE *input_file, int max_lines,
                   int max_chars) {
  // 初始化变量
  int line_count = 0;
  // 定义一个字符数组read_line，临时存储每一行内容
  char read_line[max_chars];
  // 循环读取每一行，每一行最多读取max_chars个字符，最多读取max_lines行
  while (fgets(read_line, max_chars, input_file) != NULL &&
         line_count < max_lines) {
    // printf("%s", read_line);

    // 1、如果read_line开头为"N"，则将该行内容保存到st_arr[line_count].name中
    if (read_line[0] == 'N') {
      // 将read_line从第3个字符开始复制到st_arr[line_count].name中
      strcpy(st_arr[line_count].name, read_line + 2);

      // 将flag设置为1，表示已存入名称
      st_arr[line_count].flag = 1;

      // 将line_count加1赋值给st_arr[line_count].num，即更新序号
      st_arr[line_count].num = line_count + 1;
    }

    // 2、如果read_line开头为"S"，则将该行内容保存到st_arr[line_count].serial中
    else if (read_line[0] == 'S') {
      // 将read_line从第3个字符开始复制到st_arr[line_count].serial中
      strcpy(st_arr[line_count].serial, read_line + 2);

      // 将flag设置为2，表示已存入编号
      st_arr[line_count].flag = 2;

      // 将line_count加1赋值给st_arr[line_count].num，即更新序号
      st_arr[line_count].num = line_count + 1;
    }

    // 3、不是以上两种情况统统认为输入文本格式有误
    else {
      printf("输入格式有误，跳过该行\n");
      // 跳过格式输入错误行
      continue;
    }

    line_count++;
  }

  // 返回有效读取行数
  return line_count;
}
