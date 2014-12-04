// Ship1.cpp : 实现文件
//

#include "stdafx.h"
#include "ship_path.h"
#include "Ship1.h"
#include "afxdialogex.h"

#define MAX_BUFFER 4096

// Ship1 对话框

IMPLEMENT_DYNAMIC(Ship1, CPropertyPage)

Ship1::Ship1()
	: CPropertyPage(Ship1::IDD)
{

}

Ship1::~Ship1()
{
}

void Ship1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE1, image1);
	DDX_Control(pDX, IDC_SHIPNAME1, shipName1);
	DDX_Control(pDX, IDC_TYPE1, type1);
	DDX_Control(pDX, IDC_LOADSTATUS1, loadStatus1);
	DDX_Control(pDX, IDC_LOA1, LOA1);
	DDX_Control(pDX, IDC_BREADTH1, breadth1);
	DDX_Control(pDX, IDC_DRAFT1, draft1);
	DDX_Control(pDX, IDC_DISPV1, DISP_V1);
	DDX_Control(pDX, IDC_HINT, hint);
}


BEGIN_MESSAGE_MAP(Ship1, CPropertyPage)

	ON_WM_PAINT()
END_MESSAGE_MAP()


// Ship1 消息处理程序


//读取坐标需要的函数
int readAnInt(char *head, int * position)
{
	int sum, i, OK = 0;
	int * p;

	for (i = (*position), sum = 0; head[i]; i++) {
		if (OK && (head[i] < '0' || head[i]> '9')) break;
		if (head[i] <= '9' && head[i] >= '0')
		{
			OK = 1;
			sum = sum * 10 + head[i] - '0';
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
const char *findBegin(const char *min_pos, const char *end)
{
	int TF = 0, TF2 = 0;
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
		if (val == ' ' && TF < 2)
		{
			TF++;
			continue;
		}
		if (TF2)
			return end + 1;
	}
	return NULL;
}

const char* find_pos(const char *min_pos, const char *begin, char **ret_string)
{
	const char *find_end(const char *start);
	const char *findBegin(const char *min_pos, const char *end);
	const char *end = find_end(begin);
	const char *start = findBegin(min_pos, end);
	*ret_string = NULL;
	if (start == NULL) return NULL;

	int len;
	len = end - start + 1;
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
	latitude += readAnInt(lat, position) / 60.0;
	latitude += readAnInt(lat, position) / 3600.0;
	if (lat[*position + 1] == 'N')
		latitude = 90 - latitude;
	else if (lat[*position + 1] == 'S')
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
	longitude += readAnInt(lgt, position) / 60.0;
	longitude += readAnInt(lgt, position) / 3600.0;
	if (lgt[*position + 1] == 'W')
		longitude = -longitude;
	else if (lgt[*position + 1] == 'E')
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
	for (i = 0; latitude[i]; i++)
	{
	}
	len_lat = i;

	//获取longitude的长度
	for (i = 0; longitude[i]; i++)
	{
	}
	len_lon = i;
	// printf("len=%d\n", len_lon); 

	//给初始点和终点赋值
	x0 = latitude[0];
	y0 = longitude[0];
	x1 = latitude[len_lat - 1];
	y1 = longitude[len_lon - 1];

	if (x1 != x0)
	{
		k = (y1 - y0) / (x1 - x0);
		b = y0 - k * x0;
		for (i = 0; i < len_lon; i++)
		{
			width[i] = (longitude[i] - k * latitude[i] - b) / sqrt(1 + k*k);
			// printf("【width %d】%lf\n", i, width[i]);
		}
	}
	else
	{
		for (i = 0; i < len_lon; i++)
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

	for (i = 0; width[i] != -9999 && i<9999; i++)
	{
		if (maxWidth > width[i])
			maxWidth = width[i];
		else if (minWidth < width[i])
			minWidth = width[i];
	}

	return maxWidth - minWidth;
}




void Ship1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CPropertyPage::OnPaint()



	//获取经纬度用到的变量
	int i, j, k, TF;
	const char *find_pos(const char *min_pos, const char *begin, char **ret_string);
	double transLgt(char *lgt);
	double transLat(char *lat);
	void calWidth(double *latitude, double *longitude, double * width);
	double latitude[9999] = { 0 }, longitude[9999] = { 0 }, width[9999] = { -9999 };
	char *buffer = (char *)malloc(MAX_BUFFER);

	//获取船信息用到的变量
	char *buffer2 = (char *)malloc(MAX_BUFFER);
	char *buffer3 = (char *)malloc(MAX_BUFFER);
	char shipname[100], type[100], load_status[10], loa[20], breadth[20], draft[20], disp[20];
	int bound[1000];

	FILE *input;

	//将CString转换成const char *
	LPCTSTR p = pathname1.GetBuffer();
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_ACP, NULL, p, -1, NULL, 0, NULL, FALSE);
	char *pathname_c = new char[dwMinSize];;
	WideCharToMultiByte(CP_OEMCP, NULL, p, -1, pathname_c, dwMinSize, NULL, FALSE);

	fopen_s(&input, pathname_c, "r");

	int flag = 0;
	int jj, iii;
	//获取船的信息
	for (j = 0;;)
	{
		if (flag == 1)
			break;
		fgets(buffer2, MAX_BUFFER, input);
		if (feof(input)) break;
		//先匹配到OS，获取船名等信息
		if (buffer2[0] == 'O' && buffer2[1] == 'S')
		{
			flag++;
			// printf("%s", buffer);
			fgets(buffer3, MAX_BUFFER, input);
			// printf("%s", buffer2);
			for (int ii = 4, num = 0; num < 3; ii++)
			{
				if (buffer2[ii] != ':')
					continue;
				else
				{
					num++;
					int jj, iii;
					for (jj = ii + 2; buffer2[jj]; jj++)
					{
						if (buffer2[jj] == ',')
							break;
						// else
						// 	continue;
					}
					switch (num)
					{
					case 1:
					{
							  for (iii = 0; iii < jj - ii - 2; iii++)
							  {
								  shipname[iii] = buffer2[ii + 2 + iii];
							  }
							  shipname[iii] = '\0';
							  break;
					}
					case 2:
					{
							  for (iii = 0; iii < jj - ii - 2; iii++)
							  {
								  type[iii] = buffer2[ii + 2 + iii];
							  }
							  type[iii] = '\0';
							  break;
					}
					case 3:
					{
							  for (iii = 0; iii < jj - ii - 2; iii++)
							  {
								  load_status[iii] = buffer2[ii + 2 + iii];
							  }
							  load_status[iii - 1] = '\0';
							  break;
					}

					}
				}
			}

			for (int ii = 0, num = 3; num < 7; ii++)
			{
				if (buffer3[ii] != ':')
					continue;
				else
				{
					num++;
					int jj, iii;
					for (jj = ii + 2; buffer3[jj]; jj++)
					{
						if (buffer3[jj] == ',')
							break;
						// else
						// 	continue;
					}
					switch (num)
					{
					case 4:
					{
							  for (iii = 0; iii < jj - ii - 2; iii++)
							  {
								  loa[iii] = buffer3[ii + 2 + iii];
							  }
							  loa[iii] = '\0';
							  break;
					}
					case 5:
					{
							  for (iii = 0; iii < jj - ii - 2; iii++)
							  {
								  breadth[iii] = buffer3[ii + 2 + iii];
							  }
							  breadth[iii] = '\0';
							  break;
					}
					case 6:
					{
							  for (iii = 0; iii < jj - ii - 2; iii++)
							  {
								  draft[iii] = buffer3[ii + 2 + iii];
							  }
							  draft[iii] = '\0';
							  break;
					}
					case 7:
					{
							  for (iii = 0; iii < jj - ii - 2; iii++)
							  {
								  disp[iii] = buffer3[ii + 2 + iii];
							  }
							  disp[iii - 1] = '\0';
							  break;
					}

					}
				}
			}
		}
		else
			continue;

	}

	_bstr_t bstrShipname(shipname);
	shipName1.SetWindowTextW((LPTSTR)bstrShipname);

	_bstr_t bstrType(type);
	type1.SetWindowTextW((LPTSTR)bstrType);

	_bstr_t bstrLoadstatus(load_status);
	loadStatus1.SetWindowTextW((LPTSTR)bstrLoadstatus);

	_bstr_t bstrLoa(loa);
	LOA1.SetWindowTextW((LPTSTR)bstrLoa);

	_bstr_t bstrBreadth(breadth);
	breadth1.SetWindowTextW((LPTSTR)bstrBreadth);

	_bstr_t bstrDraft(draft);
	draft1.SetWindowTextW((LPTSTR)bstrDraft);

	_bstr_t bstrDisp_v(disp);
	DISP_V1.SetWindowTextW((LPTSTR)bstrDisp_v);



	//获取经纬度
	int count_l = 0;
	for (j = 0;;)
	{
		if (count_l == 1)
			break;
		for (i = 0; i < 9999; i++)
		{
			latitude[i] = 0;
			longitude[i] = 0;
			width[i] = -9999;
		}
		int test = 0;
		fgets(buffer, MAX_BUFFER, input);
		if (feof(input)) break;
		//先匹配到一行行头为‘-’，找到新的一块儿数据，j为块号
		if (buffer[0] != '-')
			continue;
		else
		{
			j++;
			// printf("【%d】\n", j);
		}
		count_l++;
		for (i = 0, k = 0, TF = 0;; i++)
		{

			fgets(buffer, MAX_BUFFER, input);
			if (feof(input)) break;

			char *lat, *lgt;
			const char *tmp = buffer;
			tmp = find_pos(buffer, tmp, &lat);
			tmp = find_pos(buffer, tmp, &lgt);
			if ((lat == NULL || lgt == NULL) && TF) break;
			else if (lat == NULL || lgt == NULL) continue;
			else TF = 1;

			latitude[k] = transLat(lat);
			longitude[k] = transLgt(lgt);
			printf("%lf %lf\n", latitude[k], longitude[k]);
			k++;

			free(lat);
			free(lgt);
		}

		int final, count_dc = 0;
		CWnd *pwnd = GetDlgItem(IDC_IMAGE1);
		CRect rect;
		pwnd->GetWindowRect(&rect);
		int width_rec = rect.Width();
		int height_rec = rect.Height();
		double max_lat = 0.0, min_lat = latitude[0];
		double max_lon = 0.0, min_lon = longitude[0];
		double new_longitude[MAX_BUFFER], new_latitude[MAX_BUFFER];

		//初始化新声明的坐标数组
		for (i = 0; i < MAX_BUFFER; i++)
		{
			new_latitude[i] = 0.0;
			new_longitude[i] = 0.0;
		}
		//求最大，最小的经度和纬度
		for (i = 0;; i++)
		{
			if (latitude[i] == 0 && longitude[i] == 0)
				break;
			if (latitude[i] > max_lat)
				max_lat = latitude[i];
			if (latitude[i] < min_lat)
				min_lat = latitude[i];
			if (longitude[i]>max_lon)
				max_lon = longitude[i];
			if (longitude[i] < min_lon)
				min_lon = longitude[i];
		}

		//将坐标等比例转换为控件坐标
		for (i = 0;; i++)
		{
			if (latitude[i] == 0 && longitude[i] == 0)
				break;
			if (max_lon != min_lon)
				new_longitude[i] = height_rec*((longitude[i] - min_lon) / (max_lon - min_lon));
			else
				new_longitude[i] = longitude[i];

			if (max_lat != min_lat)
				new_latitude[i] = width_rec*((latitude[i] - min_lat) / (max_lat - min_lat));
			else
				new_latitude[i] = latitude[i];
		}




		CClientDC *dc[MAX_BUFFER];
		int flag_diff = 0;//判断是否全部相同
		for (i = 1;; i++)
		{
			if (new_latitude[i] == 0 && new_longitude[i] == 0)
				break;
			//若有不同坐标，则画线
			if (new_latitude[i] != new_latitude[i - 1] || new_longitude[i] != new_longitude[i - 1])
			{
				flag_diff = 1;
				dc[count_dc] = new CClientDC(pwnd);
				(*dc[count_dc]).MoveTo((int)new_latitude[i - 1], (int)new_longitude[i - 1]);
				(*dc[count_dc]).LineTo((int)new_latitude[i], (int)new_longitude[i]);
				count_dc++;
			}
		}

		if (!flag_diff)
		{
			_bstr_t bstrHint("该艘船的位置没有变化!!!!!!");
			hint.SetWindowTextW((LPTSTR)bstrHint);

			CFont m_Font;
			m_Font.CreatePointFont(100, (LPCTSTR)"Arial", NULL);
			hint.SetFont(&m_Font, true);
		}




		calWidth(latitude, longitude, width);







	}
}
