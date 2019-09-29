__kernel void sort(__global char* str, __global int* spaces, __global char* res)
{
	int id = get_global_id(0);
	int n = get_global_size(0);
	int start_index = spaces[id] + 1;
	int end_index = spaces[id+1];
	int i, j, flag = 0;

	int size_str = spaces[n];

	int len = end_index - start_index;

	for(i = start_index; i < start_index + len; i++){

		if(str[i] == ' ')
			continue;

		char data = str[i];
		printf("char is %c at %d\n", data, i);
		int pos = 0;

		for(j = 0; j < size_str; j++){
			if(str[j] != ' ' && (str[j] < data) || (str[j] == data && j < i))
				pos++;
		}

		printf("pos is %d at %d\n", pos, i);
		res[pos] = data;

	}
}