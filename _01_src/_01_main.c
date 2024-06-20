#include "_01_global.h"
#include "_02_get_input_info.h"
#include "_03_request_gbw.h"
#include "_04_reduce_response.h"

int main(int argc, char const *argv[]) {

  /***步骤一：读取文件内容，并保存在结构体St_Info数组中***/
  // 1.1 定义结构体St_Info数组
  St_Info st_arr[ST_ARR_LENGTH];

  // 1.2 读取文件内容
  //line_count表示读取文件的行数
  int line_count = read_input(st_arr,ST_ARR_LENGTH,SINGLE_LINE_LENGTH);

  /***步骤二：读取文件内容，并保存在结构体St_Info数组中***/
  request_gbw(st_arr, line_count);

  /***步骤三：response文件处理，读取查询的规范信息***/
  reduce_response();







  return 0;
}
