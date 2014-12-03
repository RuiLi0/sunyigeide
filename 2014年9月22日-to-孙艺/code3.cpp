#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BUFFER 4096

//【function】从字符串里读进一个整数，直到空格、字符为结尾

int readAnInt(char *head, int * position)
{
	int sum, i, OK=0;
	int * p;
	for (i=(*position), sum=0; head[i]; i++) {
		if (OK && (head[i] < '0' || head[i]> '9') ) break;
		if (head[i] <= '9' && head[i] >= '0') 
		{
			OK = 1;
			sum = sum*10 + head[i] - '0';
		}
	}
	*position = i;
	return sum;
}


//查找含位置数据的行的坐标结尾
const char *find_end(const char *start) 
{
	if (start == NULL) return NULL;
	for (; *start != 0; ++start) 
	{
		switch (*start) 
		{
			case 'N':
			case 'S':
			case 'W':
			case 'E':
			return start;
		}
	}
	return NULL;
}

//查找含位置数据的行的坐标开头
const char *find_begin(const char *min_pos, const char *end) 
{
	int TF=0, TF2=0;
	if (end == NULL) return NULL;
	for (--end; end > min_pos; --end) 
	{
		char val = *end;
		if (val <= '9' && val >= '0') 
		{
			continue;
		}
		if (val == '\'' || val == '"') 
		{
			TF2 = 1;
			continue;
		}
		if (val == ' ' && TF<2) 
		{
			TF++;
			continue;
		}
		if(TF2)
			return end + 1;
	}
	return NULL;
}

//查找含位置数据的行的坐标
const char *find_pos(const char *min_pos, const char *begin, char **ret_string) 
{
	const char *end = find_end(begin);
	const char *start = find_begin(min_pos, end);
	*ret_string = NULL;
	if (start == NULL) return NULL;

	size_t len = end - start + 1;
	if (len <= 2) return end + 1;

	*ret_string = (char *)malloc(len + 1);
	(*ret_string)[len] = 0;
	memcpy(*ret_string, start, len);

	return end + 1;
}

//将时分秒形式转换成小数，纬度0~180，经度-180~180
double transLat(char *lat) 
{
	double latitude;
	int i;
	int *position;

	position = (int *)malloc(sizeof(int));
	*position = 0;
	
	latitude = readAnInt(lat, position);
	latitude += readAnInt(lat, position)/60.0;
	latitude += readAnInt(lat, position)/3600.0;
	if(lat[*position+1] == 'N')
		latitude = 90 - latitude;
	else if(lat[*position+1] == 'S')
		latitude = 90 + latitude;
	return latitude;
}
double transLgt(char *lgt) 
{
	double longitude;
	int i;
	int *position;

	position = (int *)malloc(sizeof(int));
	*position = 0;

	longitude = readAnInt(lgt, position);
	longitude += readAnInt(lgt, position)/60.0;
	longitude += readAnInt(lgt, position)/3600.0;
	if(lgt[*position+1] == 'W')
		longitude =  -longitude;
	else if(lgt[*position+1] == 'E')
		longitude = longitude;
	return longitude;
}

void calWidth(double *latitude, double *longitude, double * width) 
{
	int i;	
	int len_lat, len_lon;
	double x0, y0, x1, y1;
	double k, b;//表达式参数
	// double width[9999];//宽度集，返回值

	//获取latitude的长度
	for(i=0; latitude[i]; i++)
	{}
len_lat = i;

	//获取longitude的长度
for(i=0; longitude[i]; i++)
{}
len_lon = i;
	// printf("len=%d\n", len_lon); 

	//给初始点和终点赋值
x0 = latitude[0];
y0 = longitude[0];
x1 = latitude[len_lat - 1];
y1 = longitude[len_lon - 1];

if(x1 != x0)
{
	k = (y1 - y0)/(x1 - x0);
	b = y0 - k * x0;
	for(i=0; i<len_lon; i++)
	{
		width[i] = (longitude[i] - k * latitude[i] - b ) / sqrt(1 + k*k);
			// printf("【width %d】%lf\n", i, width[i]);
	}
}
else
{
	for(i = 0; i<len_lon; i++)
	{
		width[i] = latitude[i] - x0;
	}
}
}

double GetMaxWidth(double *width)
{
	int i;
	double maxWidth = width[0];
	double minWidth = width[0];

	for(i=0; width[i]!=-9999 && i<9999; i++)
	{
		if(maxWidth > width[i])
			maxWidth = width[i];
		else if(minWidth < width[i])
			minWidth = width[i];
	}

	return maxWidth - minWidth;
}

int main()
{
	int i, j, k, TF;
	double latitude[9999]={0}, longitude[9999]={0}, width[9999]={-9999};
	char *buffer = (char *)malloc(MAX_BUFFER);
	char shipname[100], type[100], load_status[10], loa[20],breadth[20],draft[20], disp[20];

	//printf("Hello World!");

	FILE *input = fopen("./2011_08_22_10_41_33.TXT", "r");
	for(j=0; ;) 
	{
		for(i=0; i<9999; i++)
		{
			latitude[i] = 0;
			longitude[i] = 0;
			width[i] = -9999;
		}
		for(i=0; i<MAX_BUFFER; i++)
		{
			buffer[i] = '\0';
		}
		fgets(buffer, MAX_BUFFER, input);
		if (feof(input)) break;
		//先匹配到OS，获取船名等信息
		if(buffer[0] == 'O' && buffer[1] == 'S')
		{
			printf("%s\n", buffer);
			// fgets(buffer, MAX_BUFFER, input);
			// printf("%s\n", buffer);
			for(int ii = 4, num = 0; num < 7 ; ii++)
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
							load_status[iii] = '\0';
							break;
						}
						case 4:
						{
							for(iii = 0; iii < jj-ii-2; iii++)
							{
								loa[iii] = buffer[ii+2+iii];
							}
							loa[iii] = '\0';
							break;
						}
						case 5:
						{
							for(iii = 0; iii < jj-ii-2; iii++)
							{
								breadth[iii] = buffer[ii+2+iii];
							}
							breadth[iii] = '\0';
							break;
						}
						case 6:
						{
							for(iii = 0; iii < jj-ii-2; iii++)
							{
								draft[iii] = buffer[ii+2+iii];
							}
							draft[iii] = '\0';
							break;
						}
						case 7:
						{
							for(iii = 0; iii < jj-ii-2; iii++)
							{
								disp[iii] = buffer[ii+2+iii];
							}
							disp[iii] = '\0';
							break;
						}
					}
				}
			}
		}


		// printf("%s\n", shipname);
		// printf("%s\n", type);
		// printf("%s\n", load_status);
		// printf("%s\n", loa);
		// printf("%s\n", breadth);
		// printf("%s\n", draft);
		// printf("%s\n", disp);


		//先匹配到一行行头为‘-’，找到新的一块儿数据，j为块号
		if(buffer[0] != '-')
			continue;
		else
		{
			j++;	
			printf("【%d】\n", j);
		}

		for (i=0, k=0, TF=0; ; i++) 
		{

			fgets(buffer, MAX_BUFFER, input);
			if (feof(input)) break;
			if(buffer[0] == '-') break;

			char *lat, *lgt;
			const char *tmp = buffer;
			tmp = find_pos(buffer, tmp, &lat);
			tmp = find_pos(buffer, tmp, &lgt);
			if ((lat == NULL || lgt == NULL) && TF) break;
			else if(lat == NULL || lgt == NULL) continue;
			else TF=1;

			latitude[k] = transLat(lat);
			longitude[k] = transLgt(lgt);
			printf("%lf %lf\n", latitude[k], longitude[k]);
			k++;

			free(lat);
			free(lgt);
		}

		calWidth(latitude, longitude, width);
		for(i=0; width[i]!=-9999 && i<9999; i++)
		{
			printf("【width %d】%lf\n", i, width[i]);
		}

		
	}

	system("pause");
}