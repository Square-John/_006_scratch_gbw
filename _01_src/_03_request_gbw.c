#include "_03_request_gbw.h"

/*
函数功能：向工标网查询信息
参数：
    st_arr：规范信息数组
    lines：规范信息数组行数
返回值：
    lines：查新规范条数

*/
int request_gbw(St_Info *st_arr, int lines) {
  // 1、获取规范名字或者编号，进行urlencode

  // 编码最大长度
  int encode_length = NAME_LENTH * 4;
  // 编码后的字符串
  char encoded_key[encode_length];

  // 1.1 获取编码字符串

  // 以st_arr[0]为例
  if (st_arr[0].flag == 1) {
    get_url_encode(encoded_key, encode_length, st_arr[0].name);
  } else if (st_arr[0].flag == 2) {
    get_url_encode(encoded_key, encode_length, st_arr[0].serial);
  }

  // 1.2 打印编码后的字符串
  printf("编码成功，编码后的字符串：%s\n", encoded_key);

  // 2、get请求获取规范信息
  get_info_from_gbw(encoded_key, PAGE_SIZE, PAGE_NUM);

  // 3、规范信息处理

  return lines;
}

/*
函数功能：对字符串进行urlencode编码
参数：
    encoded：编码后的字符串
    encode_length：编码后的字符串最大长度
    src：需要编码的字符串
返回值：
    flag：编码是否成功,flag=1表示成功，flag=0表示编码后长度超长
*/
int get_url_encode(char *encoded, int encode_length, const char *src) {

  int flag = 1;

  const char *hex = "0123456789ABCDEF";

  // 对st_arr进行urlencode
  size_t pos = 0;
  // 需要编码字符串的长度
  int len = strlen(src);

  for (size_t i = 0; i < len; i++) {
    if (isalnum((unsigned char)src[i]) || src[i] == '-' || src[i] == '_' ||
        src[i] == '.' || src[i] == '~') {
      // 不需要编码的字符直接复制
      encoded[pos++] = src[i];
    } else {
      // 需要编码的字符转换为%xx形式
      encoded[pos++] = '%';
      encoded[pos++] = hex[(unsigned char)src[i] >> 4];   // 取高四位
      encoded[pos++] = hex[(unsigned char)src[i] & 0x0F]; // 取低四位
    }
    if (pos >= encode_length) {
      // 编码长度超过最大长度
      flag = 0;
      break;
    }
  }

  encoded[pos] = '\0'; // 添加字符串结束符

  return flag;
}

/*
函数功能：从GBW获取encoded_key对应的规范信息
参数：
    encoded_key：编码后的规范名字或者编号
    page_size：规范信息每页数量
    page_num：规范信息页数

返回值：返回请求响应状态码,0表示成功，其他表示失败

*/
int get_info_from_gbw(const char *encoded_key, int page_size, int page_num) {

  int status = 0;
  // 1、初始化套接字库
  WSADATA wsaData;

  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    printf("初始化套接字库失败\n");
    status = 1;
    return status;
  }

  // 2、创建套接字
  SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (clientSocket == INVALID_SOCKET) {
    printf("套接字创建失败\n");
    WSACleanup();
    status = 2;
    return status;
  }

  // 设置服务器地址
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  // HTTP默认端口
  serverAddr.sin_port = htons(PORT);
  // 替换为实际的服务器IP地址或域名
  serverAddr.sin_addr.s_addr = inet_addr(IP); // 替换为实际的服务器IP地址或域名

  // 连接服务器
  if (connect(clientSocket, (struct sockaddr *)&serverAddr,
              sizeof(serverAddr)) == SOCKET_ERROR) {
    printf("连接服务器失败\n");
    closesocket(clientSocket);
    WSACleanup();
    status = 3;
    return status;
  }

  // 构建HTTP请求头
  char request[HTTP_HEADER_LENGTH];
  // encoded_key 规范编码
  // page_num 返回的页码
  // HOST 服务器域名
  sprintf(request, HTTP_REQUEST, encoded_key, page_size, page_num, HOST);

  // 打印请求头
  // printf("请求头编码成功：%s\n", request);

  // 发送请求
  if (send(clientSocket, request, strlen(request), 0) == SOCKET_ERROR) {
    printf("发送请求失败\n");
    closesocket(clientSocket);
    WSACleanup();
    status = 4;
    return status;
  }

  // 打印输出请求成功信息
  printf("请求发送成功\n");

  // 接收响应迭代器
  char response[HTTP_RESPONSE_LENGTH];
  int bytes_received = 0;
  // 迭代器
  int iterator = 1;
  while ((bytes_received = recv(clientSocket, response, sizeof(response), 0)) >
         0) {
    // 处理响应数据，例如打印到控制台
    // printf("%.*s", bytes_received, response);
    // 将响应数据写入到文件
    write_response_to_file(response, SAVE_FILE_NAME, SAVE_PATH, 1);
    // 打印写入第iterator部分到SAVE_FILE_NAME文件中
    printf("第%d部分响应信息已接收并写入到%s文件中\n", iterator,
           SAVE_FILE_NAME);
    iterator++;
  }

  // 打印响应信息已接收并写入到文件SAVE_FILE_NAME中
  printf("响应信息接收成功并写入到 : %s\n", SAVE_FILE_NAME);

  // 关闭套接字
  closesocket(clientSocket);
  WSACleanup();

  return status;
}

/**
 * 函数功能：将响应数据写入到文件
 * 参数：
 *    response：响应数据
 *    filename：文件名
 *    file_type：文件类型
 *    path：文件路径
 * 返回值：成功0，失败-1
 */
int write_response_to_file(char *response, char *filename, char *path) {

  // 将文件路径和文件名拼接成文件路径
  char filepath[FILE_PATH_LENGTH];
  sprintf(filepath, "%s%s", path, filename);

  // 打开文件
  FILE *fp = NULL;
  fp = fopen(filepath, "a");

  if (fp == NULL) {
    printf("打开文件失败\n");
    return -1;
  }

  // 将响应内容从<html>标签开始写入响应数据到文件
  char *start_tag = "<html>";

  // 如果响应数据中有<html>标签，则从<html>标签开始写入响应数据到文件
  if (strstr(response, start_tag) != NULL) {
    char *start_pos = strstr(response, start_tag);

    // 打印strlen(response) - (start_pos - response)
    // printf("strlen(response) - (start_pos - response) = %lld\n",
    //  (long long)strlen(response) - (start_pos - response));
    fwrite(start_pos, 1, strlen(response) - (start_pos - response), fp);
  }

  // 如果响应数据中没有<html>标签，则直接写入响应数据到文件
  else {

    fputs(response, fp);
  }

  // 刷新缓冲区
  fflush(fp);

  // 关闭文件
  fclose(fp);

  return 0;
}

/*函数功能：删除文件

参数说明：
*/
int remove_file(char *file_path, char *file_name) {
  // 文件路径，这里以"example.txt"为例
  const char *filename = "example.txt";

  // 使用remove()函数尝试删除文件
  int result = remove(filename);

  if (result == 0) {
    printf("文件 '%s' 删除成功。\n", filename);
  } else {
    perror("删除文件时出错"); // 使用perror打印错误信息
  }
}