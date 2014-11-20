#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX_BUFFER 4096
// #define MAX_NUMBER 9999;

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

//【function】从字符串里读进一个整数，直到空格、字符为结尾
int readAnInt(char *head, int * position)
{
	int sum, i, OK=0;
	int * p;
	for (i=*position, sum=0; head[i]; i++) {
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

//将时分秒形式转换成小数，纬度0~180，经度-180~180
double transLat(char *lat) 
{
	double latitude;
	int i;
	int *position;

	position = (int *)malloc(sizeof(int));
	
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

int main(int argc, char **argv) 
{
	int i, j, k, TF;
	double latitude[9999], longitude[9999], width[9999]={-9999};
	char *buffer = (char *)malloc(MAX_BUFFER);
	FILE *input = fopen("./2011_08_22_10_41_33.TXT", "r");


	for(j=0; ;) 
	{
		fgets(buffer, MAX_BUFFER, input);
		if (feof(input)) break;
		//先匹配到一行行头为‘-’，找到新的一块儿数据，j为块号
		if(buffer[0] != '-')
			continue;
		else
		{
			j++;	
			// printf("【%d】\n", j);
		}
		for (i=0, k=0, TF=0; ; i++) 
		{
			fgets(buffer, MAX_BUFFER, input);
			if (feof(input)) break;

			char *lat, *lgt;
			const char *tmp = buffer;
			tmp = find_pos(buffer, tmp, &lat);
			tmp = find_pos(buffer, tmp, &lgt);
			if ((lat == NULL || lgt == NULL) && TF) break;
			else if(lat == NULL || lgt == NULL) continue;
			else TF=1;

			latitude[k] = transLat(lat);
			longitude[k] = transLgt(lgt);
			printf("%d->%lf %lf\n", k, latitude[k], longitude[k]);
			k++;

			free(lat);
			free(lgt);
		}

		calWidth(latitude, longitude, width);
		for(i=0; width[i]!=-9999 && i<9999; i++)
		{
			printf("【width %d】%lf\n", i, width[i]);
		}

		for(i=0; i<9999; i++)
		{
			latitude[i] = 0;
			longitude[i] = 0;
			width[i] = -9999;
		}

	}

	

	// PositivePosition();
	//abcd
	return 0;
}