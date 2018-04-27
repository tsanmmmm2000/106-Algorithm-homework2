#include <stdio.h>

struct lps_result {
    int first_index;
    int last_index;
};

int find_max(int a, int b) {
    return (a > b) ? a : b;
}

int find_lps(char *input[], int input_size){
    int lps[input_size][input_size];

    for(int l = 1; l < input_size + 1; l++) {
        for (int i = 0; i < input_size - l + 1; i++) {
            int j = i + l - 1;

            printf("l: %d, i:%d, j:%d\n", l, i, j);
            printf("input[i]: %s\n", input[i]);
            printf("input[j]: %s\n\n", input[j]);

            if(input[i] == input[j]) {
                lps[i][j] = (l == 1) ? 1 : lps[i + 1][j - 1] + 2;
            } else {
                lps[i][j] = find_max(lps[i][j - 1], lps[i + 1][j]);
            }
            printf("lps[%d][%d] = %d\n\n", i,j,lps[i][j]);          
        }
    }
    return lps[0][input_size - 1];
}

int main() {
    char* input[] = {"6","1","b","c","a","7","a","8","s","b","6"};
    int input_size = sizeof(input) / sizeof(input[0]);
    int result = find_lps(input, input_size);
    printf("%d\n", result);
}