#include <cstdio>

void readTime(char * date)
{
	scanf("Record Output Time: %s", date);
}

void readOnePosition(char * latitude, char * longitude)
{
	int num;
	float temp;
	int number;

	while(1)
	{
		number = scanf("%d", &num);
		if(number == 1)
		{
			number = scanf("%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%s%f%s\n", &temp, &temp, &temp, &temp, &temp, &temp, &temp, &temp, &temp, &temp, &temp, &temp, &temp, &temp, &temp, latitude, &temp, longitude);
		// printf("%d\n", number);
			if(number == 19)
				break;
			else if(number == -1)
				break;
			else
				printf("%d", number);
		}
		else
		{
			char temp = '1';
			while(temp)
			{
				temp = getchar();
				printf("%c", temp);
				if(temp=='\n')
					break;
			}
		}
	}	
}

int main()
{
	//variables
	char date[20], latitude[10], longitude[10];
	int a;

	//input file
	// freopen("2011_08_22_10_41_33.TXT","r",stdin);
	freopen("test.txt","r",stdin);

	//main function
	// readTime(date);//读取时间
	// printf("%s\n", date);

	readOnePosition(latitude, longitude);
	printf("latitude:%s longitude:%s\n", latitude, longitude);
	// readOnePosition(latitude, longitude);
	// printf("latitude:%s longitude:%s\n", latitude, longitude);
	
	// while(1)
	// {
	// 	printf("%d", scanf("%d %s", &a, date));
	// }
	return 0;
}