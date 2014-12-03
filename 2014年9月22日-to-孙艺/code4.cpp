#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BUFFER 4096

int main()
{
	int i, j, k, TF;
	char *buffer = (char *)malloc(MAX_BUFFER);
	char *buffer2 = (char *)malloc(MAX_BUFFER);
	char shipname[100], type[100], load_status[10], loa[20],breadth[20],draft[20], disp[20];

	//printf("Hello World!");

	FILE *input = fopen("./2011_08_22_10_41_33.TXT", "r");
	for(j=0; ;) 
	{
		fgets(buffer, MAX_BUFFER, input);
		if (feof(input)) break;
		//先匹配到OS，获取船名等信息
		if(buffer[0] == 'O' && buffer[1] == 'S')
		{
			printf("%s", buffer);
			fgets(buffer2, MAX_BUFFER, input);
			printf("%s", buffer2);
			for(int ii = 4, num = 0; num < 3 ; ii++)
			{
				if(buffer[ii]!=':')
					continue;
				else
				{
					num ++;
					int jj,iii;
					for(jj = ii+2; buffer[jj]; jj++)
					{
						if(buffer[jj] == ',')
							break;
						// else
						// 	continue;
					}
					switch(num)
					{
						case 1:
						{
							for(iii = 0; iii < jj-ii-2; iii++)
							{
								shipname[iii] = buffer[ii+2+iii];
							}
							shipname[iii] = '\0';
							break;
						}
						case 2:
						{
							for(iii = 0; iii < jj-ii-2; iii++)
							{
								type[iii] = buffer[ii+2+iii];
							}
							type[iii] = '\0';
							break;
						}
						case 3:
						{
							for(iii = 0; iii < jj-ii-2; iii++)
							{
								load_status[iii] = buffer[ii+2+iii];
							}
							load_status[iii-1] = '\0';
							break;
						}
						
					}
				}
			}

			for(int ii = 0, num = 3; num < 7 ; ii++)
			{
				if(buffer2[ii]!=':')
					continue;
				else
				{
					num ++;
					int jj,iii;
					for(jj = ii+2; buffer2[jj]; jj++)
					{
						if(buffer2[jj] == ',')
							break;
						// else
						// 	continue;
					}
					switch(num)
					{
						case 4:
						{
							for(iii = 0; iii < jj-ii-2; iii++)
							{
								loa[iii] = buffer2[ii+2+iii];
							}
							loa[iii] = '\0';
							break;
						}
						case 5:
						{
							for(iii = 0; iii < jj-ii-2; iii++)
							{
								breadth[iii] = buffer2[ii+2+iii];
							}
							breadth[iii] = '\0';
							break;
						}
						case 6:
						{
							for(iii = 0; iii < jj-ii-2; iii++)
							{
								draft[iii] = buffer2[ii+2+iii];
							}
							draft[iii-1] = '\0';
							break;
						}
						case 7:
						{
							for(iii = 0; iii < jj-ii-2; iii++)
							{
								disp[iii] = buffer2[ii+2+iii];
							}
							disp[iii-1] = '\0';
							break;
						}
						
					}
				}
			}
		}
		else
			continue;


		printf("%s\n", shipname);
		printf("%s\n", type);
		printf("%s\n", load_status);
		printf("%s\n", loa);
		printf("%s\n", breadth);
		printf("%s\n", draft);
		printf("%s\n", disp);
	}

	// system("pause");
}