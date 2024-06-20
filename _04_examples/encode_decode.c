#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// 函数声明
char* url_encode(const char* src, size_t len);

int main() {
    const char* input = "蒸压加气混凝土砌块";
    char* encoded = url_encode(input, strlen(input));
    printf("Original: %s\n", input);
    printf("Encoded: %s\n", encoded);
    // 记得释放分配的内存
    free(encoded);
    return 0;
}

// 实现URL编码
char* url_encode(const char* src, size_t len) {
    const char* hex = "0123456789ABCDEF";
    char* encoded = (char*)malloc(len * 3 + 1); // 分配足够的内存，假设每个字符最多变为3个字符（%xx）
    if (encoded == NULL) return NULL; // 内存分配失败处理

    size_t pos = 0;
    for (size_t i = 0; i < len; ++i) {
        if (isalnum((unsigned char)src[i]) || src[i] == '-' || src[i] == '_' || src[i] == '.' || src[i] == '~') {
            // 不需要编码的字符直接复制
            encoded[pos++] = src[i];
        } else {
            // 需要编码的字符转换为%xx形式
            encoded[pos++] = '%';
            encoded[pos++] = hex[(unsigned char)src[i] >> 4]; // 取高四位
            encoded[pos++] = hex[(unsigned char)src[i] & 0x0F]; // 取低四位
        }
    }
    encoded[pos] = '\0'; // 添加字符串结束符
    return encoded;
}