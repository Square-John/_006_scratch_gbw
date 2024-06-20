#include <regex.h>
#include <stdio.h>
#include <string.h>

#define FILE_LEN 1024 * 1024
#define BUFFER 1024

int main() {
  FILE *file;
  char file_text[FILE_LEN];
  char buffer[BUFFER];

  file = fopen("_02_examples/example1.txt", "r");
  while (fgets(buffer, BUFFER, file)) {
    strcat(file_text, buffer);
  }

  // 关闭文件
  fclose(file);

  // Regular expression pattern
  char pattern[] = "<thead[^>]*>((.*(<tr >(.*?)</tr>).*?</tr>.*?</tr>.*?</tr>.*?</table>).*?</table>).*?</table>";

  // Compile the regular expression
  regex_t regex;
  int reti = regcomp(&regex, pattern, REG_EXTENDED);
  if (reti) {
    fprintf(stderr, "Could not compile regular expression\n");
    return 1;
  }

  // Search for matches
  regmatch_t matches[5];
  reti = regexec(&regex, file_text, 5, matches, 0);
  if (reti) {
    fprintf(stderr, "No match found\n");
    return 1;
  }

  // Extract and print the match
  char *match = file_text + matches[4].rm_so;
  int match_len = matches[4].rm_eo - matches[4].rm_so;
  printf("%.*s\n", match_len, match);

  // Free the regular expression
  regfree(&regex);

  return 0;
}