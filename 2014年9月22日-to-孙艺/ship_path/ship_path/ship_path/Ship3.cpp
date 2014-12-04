// Ship3.cpp : 实现文件
//

#include "stdafx.h"
#include "ship_path.h"
#include "Ship3.h"
#include "afxdialogex.h"
#include <math.h>

#define MAX_BUFFER 4096
// Ship3 对话框

IMPLEMENT_DYNAMIC(Ship3, CPropertyPage)

Ship3::Ship3()
: CPropertyPage(Ship3::IDD)
{

}

Ship3::~Ship3()
{
}

void Ship3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHIPNAME3, shipName3);
	DDX_Control(pDX, IDC_TYPE3, type3);
	DDX_Control(pDX, IDC_LOADSTATUS3, loadStatus3);
	DDX_Control(pDX, IDC_LOA3, LOA3);
	DDX_Control(pDX, IDC_BREADTH3, breadth3);
	DDX_Control(pDX, IDC_DRAFT3, draft3);
	DDX_Control(pDX, IDC_DISPV3, DISP_V3);
	DDX_Control(pDX, IDC_IMAGE3, image3);

	DDX_Control(pDX, IDC_DISTANCE, distance);
}


BEGIN_MESSAGE_MAP(Ship3, CPropertyPage)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Ship3 消息处理程序


void Ship3::OnPaint()
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
	LPCTSTR p = pathname3.GetBuffer();
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
		if (flag == 3)
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
	shipName3.SetWindowTextW((LPTSTR)bstrShipname);

	_bstr_t bstrType(type);
	type3.SetWindowTextW((LPTSTR)bstrType);

	_bstr_t bstrLoadstatus(load_status);
	loadStatus3.SetWindowTextW((LPTSTR)bstrLoadstatus);

	_bstr_t bstrLoa(loa);
	LOA3.SetWindowTextW((LPTSTR)bstrLoa);

	_bstr_t bstrBreadth(breadth);
	breadth3.SetWindowTextW((LPTSTR)bstrBreadth);

	_bstr_t bstrDraft(draft);
	draft3.SetWindowTextW((LPTSTR)bstrDraft);

	_bstr_t bstrDisp_v(disp);
	DISP_V3.SetWindowTextW((LPTSTR)bstrDisp_v);



	//获取经纬度
	int count_l = 0;
	for (j = 0;;)
	{
		if (count_l == 2)
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
		CWnd *pwnd = GetDlgItem(IDC_IMAGE3);

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
			new_longitude[i] = height_rec*((longitude[i] - min_lon) / (max_lon - min_lon));
			new_latitude[i] = width_rec*((latitude[i] - min_lat) / (max_lat - min_lat));
		}




		CClientDC *dc[MAX_BUFFER];
		int end_l;
		for (i = 1;; i++)
		{
			if (new_latitude[i] == 0 && new_longitude[i] == 0)
			{
				end_l = i - 1;
				break;
			}

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
		double width_max = 0.0;
		int width_max_order;
		//找出绝对宽度最大的那个点的下标
		for (i = 0; width[i] != -9999 && i < 9999; i++)
		{
			//printf("【width %d】%lf\n", i, width[i]);
			if (width[i] < 0)
			{
				if (-width[i]>width_max)
				{
					width_max = (-width[i]);
					width_max_order = i;
				}


			}
			else
			{
				if (width[i] > width_max)
				{
					width_max = width[i];
					width_max_order = i;
				}

			}
		}

		//计算需要画的平行线的另外一个点的坐标
		double k_v;//斜率
		double a0 = new_latitude[end_l], b0 = new_longitude[end_l],
			a2 = new_latitude[0], b2 = new_longitude[0],
			a1 = new_latitude[width_max_order], b1 = new_longitude[width_max_order];

		k_v = (b0 - b2) / (a0 - a2);
		/*a = 1 + k_x*k_x;
		b = 2 * k_x*b1 - 2 * a0 - 2 * a1 * k_x*k_x - 2 * b0*k_x;
		c = a0*a0 + b1*b1 + a1 * a1*k_x*k_x + 2 * a1*k_x*b0 + b0*b0 - 2 * k_x*a1*b1 - 2 * b0*b1 - width_max*width_max;

		double delta = b*b - 4 * a*c;
		if (delta > 0)
		{
			//x_v=
		}*/

		
		double x_v,y_v;//所画直线在y轴上的截点的纵坐标和在x轴上的截点的横坐标
		y_v = b1 - a1*k_v;
		x_v = a1 - b1 / k_v;

		CPen pen,pen_point;
		pen.CreatePen(PS_SOLID,0,RGB(255,0,0));
		pen_point.CreatePen(PS_SOLID, 100, RGB(0, 0, 0));
		

		CClientDC dc_v(pwnd);
		CClientDC dc_v_point(pwnd);
		dc_v.SelectObject(&pen);
		dc_v_point.SelectObject(&pen_point);

		dc_v.MoveTo(0,(int)y_v);
		dc_v.LineTo((int)x_v,0);
		dc_v_point.Ellipse((int)a1, (int)b1, (int)a1, (int)b1);

		CClientDC dc_v2(pwnd);
		dc_v2.SelectObject(&pen);
		dc_v2.MoveTo((int)a2,(int)b2);
		dc_v2.LineTo((int)a0,(int)b0);

		CString distance_hint = _T("最大船的距离为：");
		CString distance_value;
		distance_value.Format(_T("%lf"), width_max);
		CString distance_s = distance_hint + distance_value;

		_bstr_t bstrHint(distance_s);
		distance.SetWindowTextW((LPTSTR)bstrHint);
		break;


	}

}
