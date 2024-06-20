#ifndef __03_REQUEST_GBW_H_
#define __03_REQUEST_GBW_H_

#include "_01_global.h"

#include <winsock2.h>

/*
函数功能：向工标网查询信息
参数：
    st_arr：规范信息数组
    lines：规范信息数组行数
返回值：
    lines：查新规范条数

*/
int request_gbw(St_Info *st_arr, int lines);

/*
函数功能：对字符串进行urlencode编码
参数：
    encoded：编码后的字符串
    encode_length：编码后的字符串最大长度
    src：需要编码的字符串
返回值：
    flag：编码是否成功,flag=1表示成功，flag=0表示编码后长度超长
*/
int get_url_encode(char *encoded, int encode_length, const char *src);

/*
函数功能：从GBW获取encoded_key对应的规范信息
参数：
    encoded_key：编码后的规范名字或者编号
    page_size：规范信息每页数量
    page_num：规范信息页数

返回值：返回请求响应状态码,0表示成功，其他表示失败

*/
int get_info_from_gbw(const char *encoded_key, int page_size, int page_num);

/**
 * 函数功能：将响应数据写入到文件
 * 参数：
 *    response：响应数据
 *    filename：文件名
 *    file_type：文件类型
 *    path：文件路径
 * 返回值：成功0，失败-1
 */
int write_response_to_file(char *response, char *filename, char *path);

#endif