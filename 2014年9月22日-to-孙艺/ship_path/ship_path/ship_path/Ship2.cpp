// Ship2.cpp : 实现文件
//

#include "stdafx.h"
#include "ship_path.h"
#include "Ship2.h"
#include "afxdialogex.h"

#define MAX_BUFFER 4096
// Ship2 对话框

IMPLEMENT_DYNAMIC(Ship2, CPropertyPage)

Ship2::Ship2()
	: CPropertyPage(Ship2::IDD)
{

}

Ship2::~Ship2()
{
}

void Ship2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHIPNAME2, shipName2);
	DDX_Control(pDX, IDC_TYPE2, type2);
	DDX_Control(pDX, IDC_LOADSTATUS2, loadStatus2);
	DDX_Control(pDX, IDC_LOA2, LOA2);
	DDX_Control(pDX, IDC_BREADTH2, breadth2);
	DDX_Control(pDX, IDC_DRAFT2, draft2);
	DDX_Control(pDX, IDC_DISPV2, DISP_V2);
	DDX_Control(pDX, IDC_IMAGE2, image2);
}


BEGIN_MESSAGE_MAP(Ship2, CPropertyPage)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Ship2 消息处理程序


void Ship2::OnPaint()
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
	LPCTSTR p = pathname2.GetBuffer();
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
		if (flag == 2)
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
	shipName2.SetWindowTextW((LPTSTR)bstrShipname);

	_bstr_t bstrType(type);
	type2.SetWindowTextW((LPTSTR)bstrType);

	_bstr_t bstrLoadstatus(load_status);
	loadStatus2.SetWindowTextW((LPTSTR)bstrLoadstatus);

	_bstr_t bstrLoa(loa);
	LOA2.SetWindowTextW((LPTSTR)bstrLoa);

	_bstr_t bstrBreadth(breadth);
	breadth2.SetWindowTextW((LPTSTR)bstrBreadth);

	_bstr_t bstrDraft(draft);
	draft2.SetWindowTextW((LPTSTR)bstrDraft);

	_bstr_t bstrDisp_v(disp);
	DISP_V2.SetWindowTextW((LPTSTR)bstrDisp_v);



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
			count_l++;
			// printf("【%d】\n", j);
		}

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
		CWnd *pwnd = GetDlgItem(IDC_IMAGE2);
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
		for (i = 1;; i++)
		{
			if (new_latitude[i] == 0 && new_longitude[i] == 0)
				break;
			//若有不同坐标，则画线
			if (new_latitude[i] != new_latitude[i - 1] || new_longitude[i] != new_longitude[i - 1])
			{
				dc[count_dc] = new CClientDC(pwnd);


				(*dc[count_dc]).MoveTo((int)new_latitude[i - 1], (int)new_longitude[i - 1]);
				(*dc[count_dc]).LineTo((int)new_latitude[i], (int)new_longitude[i]);
				count_dc++;
			}
		}


		calWidth(latitude, longitude, width);
		for (i = 0; width[i] != -9999 && i < 9999; i++)
		{
			printf("【width %d】%lf\n", i, width[i]);
		}




	}
}
