#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

struct lps_data {
    int size;
    char data[MAX_SIZE];
};

int find_max(int a, int b) {
    return (a > b) ? a : b;
}

struct lps_data find_lps(char data[], int data_size){
	int lps[data_size][data_size];
	memset (lps, 0, sizeof lps);
	for(int l = 1; l < data_size + 1; l++) {
		for (int i = 0; i < data_size - l + 1; i++) {
			int j = i + l - 1;
			if(data[i] == data[j]) {
				lps[i][j] = (l == 1) ? 1 : lps[i + 1][j - 1] + 2;
			} else {
				lps[i][j] = find_max(lps[i][j - 1], lps[i + 1][j]);
			}
		}
	}
	
	int subseq_size = lps[0][data_size - 1];
	char subseq[MAX_SIZE] = "";
	
	int i = 0;
	int j = data_size - 1;
	int index = 0;
	
	while(i < data_size && j >= 0) {
		if (data[i] == data[j]) {
			if (lps[i][j] == 1) {
				subseq[index] = data[i];	
				break;
			}
			subseq[index] = data[i];
			subseq[subseq_size - index - 1] = data[i];
			i++;
			j--;
			index++;		
		} else if (lps[i][j - 1] > lps[i + 1][j]) {
			j--;
		} else {
			i++;
		}
	}
	
	struct lps_data result;
	result.size = subseq_size;
	strcpy(result.data, subseq);
	return result;
}

int main() {
	int input_num;
	scanf("%i", &input_num);
	struct lps_data input_list[input_num];
	
	// i should start at -1 becuase it have to skip the '\n' from scanf
	for (int i = -1; i < input_num; i++) {
		char input[MAX_SIZE];
		fgets(input, sizeof(input), stdin);	
		
		if (i >= 0) {
			input_list[i].size = -1;
			for(int j = 0; input[j] != '\0'; j++) {
				input_list[i].size++;
			}
			strcpy(input_list[i].data, input);
		}
	}

	for (int i = 0; i < input_num; i++) {
		struct lps_data result = find_lps(input_list[i].data, input_list[i].size);
		printf("%d\n%s\n", result.size, result.data);
	}
}
