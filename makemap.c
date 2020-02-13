#include <stdio.h>

//define map size
#define SIZE 50

int main()
{
	FILE *fp1 = fopen("my_map.pgm", "rb");
	FILE *fp2 = fopen("my_map.txt", "wb");

	//map save array
	unsigned int arr[SIZE][SIZE];

	int i = 0, j = 0;
	int min_x = 0, min_y = 0, max_x = 0, max_y = 0;
	unsigned char temp;

	//file open test
	if (fp1 == NULL && fp2 == NULL) {
		printf("File open fail");
		return -1;
	}

	//pgm setting byte except
	for (i = 0; i < 50; i++) {
		fscanf(fp1, "%c", &temp);
	}

	//pgm file define array
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			fscanf(fp1, "%c", &temp);

			//black - wall
			if (temp == 0) {
				//fprintf(fp2, "%d", 1);
				arr[i][j] = 1;
			}
			//white - ground
			else if (temp == 254) {
				//fprintf(fp2, "%d", 2);
				arr[i][j] = 2;
			}
			else {
				//fprintf(fp2, "%d", 0);
				arr[i][j] = 0;
			}
		}
	}

	//file hole
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (arr[i][j] == 0)
			{
				if (((arr[i - 1][j] == 1) || (arr[i - 1][j] == 2)) && ((arr[i + 1][j] == 1) || (arr[i + 1][j] == 2)) &&
					((arr[i][j - 1] == 1) || (arr[i][j - 1] == 2)) && ((arr[i][j + 1] == 1) || (arr[i][j + 1] == 2)))
					arr[i][j] = 2;
			}
		}
	}

	//cut array
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (arr[i][j] == 1) {
				min_x = i;
				break;
			}
		}
		if (min_x != 0)
			break;
	}

	for (i = SIZE - 1; i > 0; i--)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (arr[i][j] == 1) {
				max_x = i + 1;
				break;
			}
		}
		if (max_x != 0)
			break;
	}

	for (j = 0; j < SIZE; j++)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (arr[i][j] == 1) {
				min_y = j;
				break;
			}
		}
		if (min_y != 0)
			break;
	}

	for (j = SIZE - 1; j > 0; j--)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (arr[i][j] == 1) {
				max_y = j + 1;
				break;
			}
		}
		if (max_y != 0)
			break;
	}

	//print array to display
	for (i = min_x; i < max_x; i++)
	{
		for (j = min_y; j < max_y; j++) {
			//print to console
			//printf("%d", arr[i][j]);		
			
			//print to file - number ver.
			//fprintf(fp2, "%d", arr[i][j]);

			//print to char
			if (arr[i][j] == 0)
				fprintf(fp2, "＊");

			else if (arr[i][j] == 1)
				fprintf(fp2, "■");

			else if (arr[i][j] == 2)
				fprintf(fp2, "□");
		}
		//printf("\n");
		fprintf(fp2, "\r\n");
	}

	//check weight and height
	printf("w = %d, h = %d\n", max_x - min_x, max_y - min_y);

	fclose(fp1);
	fclose(fp2);

	return 0;
}