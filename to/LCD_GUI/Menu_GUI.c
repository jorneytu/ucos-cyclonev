//========================================================================
// �ļ���: Menu_GUI.c
// ��  ��: Xinqiang Zhang(email: Xinqiang@Mzdesign.com.cn)
//			www.Mzdesign.com.cn
// ��  ��: 2007/03/24
// ��  ��: �˵�Ӧ�÷�������--UI��ʾˢ�¿��ƺ��������MzDesign�ṩ��ͨ�ð�
//			LCD������������
//			�˴�����������byte������16λMCU����������unspϵ��MCU
//
// ��  ��:
// ��  ��:
//      2007/03/24      First version    Mz Design
//      2007/07/26      V1.01			 Mz Design
//			�޸�Show_Item����,ʹ֮��Ӧ��ͬ��LCDģ�������
//
//========================================================================

#include "Menu_GUI.h"
#include "LCD_Main.h"
#include "resources.h"
#include "global.h"
#include "stdio.h"
#include "status.h"

#ifdef IIC_Key_Board_LCD
UCHAR Dis_Menu_Num_Page = 0;
UCHAR UILanguage = chs;

UCHAR First_Index_old=0xff;
UCHAR y_Index_old = 0xff;

INT8U LastDisMode_Main = TRUE;//��ǰ��ʾ
enum StatusTypeEnum Last_Status = E_ST_RDY; //��ǰ״̬
CHAR Last_MainInfo_MediaWidth[8] = {0};      //value is float *. unit is inch.
CHAR Last_MainInfo_PrintOrigin[8] = {0};     //value is float *. unit is inch.
#ifdef RIPSTAR_FLAT_EX
CHAR Last_MainInfo_MediaLength[8] = {0};      //value is float *. unit is inch.
CHAR Last_MainInfo_YOrigin[8] = {0};     //value is float *. unit is inch.
CHAR Last_MainInfo_MediaHigh[8] = {0};      //value is float *. unit is inch.
CHAR Last_MainInfo_ZOrigin[8] = {0};     //value is float *. unit is inch.
#endif
CHAR Last_MainInfo_PassNum[8] = {0};         //value is INT8U *.
CHAR Last_MainInfo_Resolution[8] = {0};      //value is INT16U *.
CHAR Last_MainInfo_percent[8] = {0};
CHAR MainInfo_last_pid[8] = {0};
CHAR MainInfo_Last_PrinterName[16] = {0};     //value is C string.
CHAR MainInfo_Last_ManufactureName[16] = {0}; //value is C string.
char Dis_Inf[100] = {0};
char *Dis_Inf_Case;
//
//void CalcMenuItemPos(int *x,int*y,struct MenuItem* item)
//{	
//  unsigned short i,j,List_Num,visibelNum;	
//  unsigned short MainScreen_ColCount = 3;
//  List_Num = item->Parents->ItemCount;
//  visibelNum = GetMLNum(item->Parents);
//  for(i=First_Index_old,j=0;i<List_Num && j< Dis_Menu_Num_Page;i++)
//  {
//    if((item->Parents->ChildItems+i)->Visible == 1)
//      j++;
//    else
//      continue;
//    switch(CurrentDisMode)
//    {
//    case MainScreen:
//      if((j-1) == item->Parents->Selected_Offset)
//      {
//        *x =((j-1)%MainScreen_ColCount)*LCD_PIXEL_WIDTH/MainScreen_ColCount;
//        *y= LCD_MENUITEM_HEIGHT*((j-1)/MainScreen_ColCount);	
//      }
//      break;
//    case Menu:
//    case Edit:			
//      if((j-1) == item->Parents->Selected_Offset)
//      {
//        *x = 0;
//        *y = (j-1)*LCD_MENUITEM_HEIGHT;		
//        (item->Parents->ChildItems+i)->selected = 1;
//        item->Parents->SelectedIndex = i;
//      }
//      else
//        (item->Parents->ChildItems+i)->selected = 0;
//      break;		
//    case Reserved:
//    default:
//      break;
//    }
//  }
//}

unsigned char Tmp_Image[] = {
	0x20,0x00,0x53,0xF4,0x24,0x0C,0x08,0x04,0x08,0x04,0x10,0x00,0x10,0x00,0x10,0x00,
	0x10,0x00,0x10,0x00,0x10,0x00,0x08,0x04,0x08,0x04,0x04,0x08,0x03,0xF0,0x00,0x00
};
void Change_Menu_Name(INT8U *text,INT8U *Menu_Name)
{
	int i = 0;
	int len = strlen(text);
	for(i = 0;i < MENU_NAME_LEN;i++)
	{
		if(i < len)
			Menu_Name[i] = text[i];
		else
			Menu_Name[i] = ' ';
	}
	Menu_Name[MENU_NAME_LEN-1] = 0;

}
//=====================================================================//
//������UCHAR ShowMenu_Item(UCHAR y,UINT* Menu_String,UCHAR Font_Color)
//��������ʾ�˵����Ӻ���
//������space_front  ��ʾ����ֵ
//		y            Y������
//		Menu_String  �˵���������׵�ַָ��
//���أ���ʾ������  0�����    1�������
//ע�⣺��
//=====================================================================//
UCHAR ShowMenu_Item(UINT x,UINT y,struct MenuItem* displayitem)
{
	//  unsigned short String_right[]={41,0};///*--  ����41:  ��  --*/
	//  unsigned short String_checked1[]={34,0};//""��");
	//  unsigned short String_checked2[]={37,0};//"��");
	char Menu_Name[MENU_NAME_LEN] = {0};
	INT8U Menu_Mask = 0;
	static INT8U  Next_Refresh = False;
	static INT8U  Cur_Refresh = False;
	static INT8U  Last_Y = 0;
#if defined(LCD_MODULE_128_64_ST5668A)
	LCD_DrawPicture(radiocheckbox_offset, y, 8, 16, imgZero);//LCD_DrawText(0, LCD_PIXEL_HIGH - LCD_MENUITEM_HEIGHT, "v");
#else
	LCD_DrawPicture(8, y, 8, 16, imgZero);//LCD_DrawText(0, LCD_PIXEL_HIGH - LCD_MENUITEM_HEIGHT, "v");
#endif
	if(y==16||y==32)
		LCD_DrawPicture(0, y, 8, 16, imgZero);//LCD_DrawText(0, LCD_PIXEL_HIGH - LCD_MENUITEM_HEIGHT, "v");
	if(displayitem->status != editting && displayitem->GetFloatFunc!=0)
	{
		float tempval = CallUIGetFuncByType(displayitem); //��ȡҪ��ʾ��ֵ
		SetUIMenuItemValue(displayitem, tempval);//��ֵ��������ʾ�ĸ�ʽ
	}
	if(Next_Refresh == False)
		Cur_Refresh = False;
	else if((Next_Refresh == True)&&(Last_Y == y))
	{
		Cur_Refresh = True;
		Next_Refresh = False;
		Last_Y = 0xFF;
	}
	//LCD_FillRectangle(x, y, LCD_PIXEL_WIDTH-x, LCD_MENUITEM_HEIGHT, 0);
	if(displayitem->status != editting && CurrentDisMode!= MainScreen)
	{
		#if defined(LCD_MODULE_128_64_ST5668A)
			x += CHECKBOX_WIDTH + radiocheckbox_offset;					//Mune show front space....
		#else
			x += CHECKBOX_WIDTH + INDICATE_AREAS_WIDTH;					//Mune show front space....
		#endif
	}
	else
	{
		Menu_Mask |=3;
		Next_Refresh = True;
		Last_Y = y;
	}
	if(UILanguage == chs)//(displayitem->Lang == chs)	
		//LCD_DrawMixedText(x,y,(unsigned short*)displayitem->Text_ch);
		Change_Menu_Name((INT8U *)displayitem->Text_ch,Menu_Name);
	else
		//LCD_DrawText(x,y,(char*)displayitem->Text_en);
		Change_Menu_Name((INT8U *)displayitem->Text_en,Menu_Name);
	LCD_DrawText(x,y,Menu_Name);
	if(displayitem->ItemCount>0)
	{
		LCD_DrawPicture(LCD_PIXEL_WIDTH - INDICATE_AREAS_WIDTH, y, 8, 16, imgZero);
		LCD_DrawPicture(LCD_PIXEL_WIDTH - INDICATE_AREAS_WIDTH, y+(LCD_MENUITEM_HEIGHT-8)/2, 8, 8, imgRight);//LCD_DrawText(LCD_PIXEL_WIDTH - INDICATE_AREAS_WIDTH, y, ">");///*--  ����41:  ��  --*/
		Menu_Mask |=8;
	}
#if defined(LCD_MODULE_128_64_ST5668A)
	else
	{
		Menu_Mask |=8;
	}
#endif
	if(displayitem->type == editor)
	{
		int dotindex = displayitem->maxVal;
		if(displayitem->DecimalPlaces > 0)
			dotindex = displayitem->DecimalPlaces + 1;
		if(displayitem->status== editting)		
		{
			LCD_FillRectangle(LCD_PIXEL_WIDTH-(displayitem->maxVal*8+UNIT_AREAS_WIDTH), y, displayitem->maxVal*8+UNIT_AREAS_WIDTH, LCD_MENUITEM_HEIGHT, 0);
			if(displayitem->Value[0]==0)
				LCD_DrawText(LCD_PIXEL_WIDTH-((displayitem->maxVal+1)*8+UNIT_AREAS_WIDTH), y, "=-");
			else
				LCD_DrawText(LCD_PIXEL_WIDTH-((displayitem->maxVal+1)*8+UNIT_AREAS_WIDTH), y, "=+");
			
			for(int i = 1; i<displayitem->maxVal;i++)
			{	
				char temp[6] = {0};
				sprintf(temp,"%d",(INT32U)displayitem->Value[i]);
				if(i!=(displayitem->maxVal - dotindex))
					LCD_DrawText(LCD_PIXEL_WIDTH-((displayitem->maxVal-i)*8+UNIT_AREAS_WIDTH), y, temp);
				else
					LCD_DrawText(LCD_PIXEL_WIDTH-((displayitem->maxVal-i)*8+UNIT_AREAS_WIDTH), y, ".");
			}
		}
		else
		{
			//LCD_DrawText(LCD_PIXEL_WIDTH-((EDITOR_MAX_LEN+1)*8+UNIT_AREAS_WIDTH), y, "=");
			
			int bstart = -1;
			int bZero = 1;
			for(int i = 1; i<displayitem->maxVal;i++)
			{	
				if(((INT32U)displayitem->Value[i])>0)
				{
					bZero = 0;
					if(((displayitem->maxVal <= dotindex)|| i<(displayitem->maxVal - dotindex))&&bstart<0)
						bstart = i;
				}
			}
			if(bstart < 0)
				bstart = displayitem->maxVal -dotindex-1;
			
			if(bZero == 0)//bZeroΪ��ʱ����valueֵ��Ϊ0ʱ��
			{
				LCD_FillRectangle(LCD_PIXEL_WIDTH-((displayitem->maxVal-bstart+2)*8+UNIT_AREAS_WIDTH), y, (displayitem->maxVal-bstart+2)*8+UNIT_AREAS_WIDTH, LCD_MENUITEM_HEIGHT, 0);
				
				LCD_DrawText(LCD_PIXEL_WIDTH-((displayitem->maxVal-bstart+2)*8+UNIT_AREAS_WIDTH), y, "=");
				if(displayitem->Value[0]==0)
					LCD_DrawText(LCD_PIXEL_WIDTH-((displayitem->maxVal-bstart+1)*8+UNIT_AREAS_WIDTH), y, "-");
				for(int i = bstart; i<displayitem->maxVal;i++)
				{	
					char temp[6] = {0};
					sprintf(temp,"%d",(INT32U)displayitem->Value[i]);
					if(i!=(displayitem->maxVal - dotindex))
						LCD_DrawText(LCD_PIXEL_WIDTH-((displayitem->maxVal-i)*8+UNIT_AREAS_WIDTH), y, temp);
					else
						LCD_DrawText(LCD_PIXEL_WIDTH-((displayitem->maxVal-i)*8+UNIT_AREAS_WIDTH), y, ".");
				}      
			}
			else
			{ 
				LCD_FillRectangle(LCD_PIXEL_WIDTH-(3*8+UNIT_AREAS_WIDTH), y, 3*8+UNIT_AREAS_WIDTH, LCD_MENUITEM_HEIGHT, 0);
				LCD_DrawText(LCD_PIXEL_WIDTH-UNIT_AREAS_WIDTH-3*8, y, "=");//�����˷���λռλ
				LCD_DrawText(LCD_PIXEL_WIDTH-UNIT_AREAS_WIDTH-8, y, "0");
			}
		}
		// ��ʾ��λ
		switch(displayitem->Unit)
		{
		case utNone:
			break;
		case utInch:
		case utCM:
			switch(CurrentLengthUnit)
			{
			case utInch:
				LCD_DrawText(LCD_PIXEL_WIDTH-2*8, y, "in");
				Menu_Mask |= 12;
				break;
			case utCM:
				LCD_DrawText(LCD_PIXEL_WIDTH-2*8, y, "cm");
				Menu_Mask |= 12;
				break;
			}
			break;
		case utSec:
			LCD_DrawText(LCD_PIXEL_WIDTH-8, y, "s");
			Menu_Mask |= 8;
			break;
		case utKHz:
			LCD_DrawText(LCD_PIXEL_WIDTH-2*8, y, "kh");
			Menu_Mask |= 12;
			break;
		case utT:
			LCD_DrawPicture(LCD_PIXEL_WIDTH-2*8, y, 16, 16, Tmp_Image);
			Menu_Mask |= 12;
			break;
		case utH:
			LCD_DrawText(LCD_PIXEL_WIDTH-2*8, y, "h");
			Menu_Mask |= 12;
			break;
		}
	}
	else if(displayitem->type == pwdEditor)
	{
		LCD_FillRectangle(LCD_PIXEL_WIDTH-displayitem->maxVal*8, y, displayitem->maxVal*8, LCD_MENUITEM_HEIGHT, 0);
		LCD_DrawText(LCD_PIXEL_WIDTH-(displayitem->maxVal+2)*8, y, " :");
		for(int i = 0; i<displayitem->maxVal;i++)
		{	
			char temp[2];
			temp[0] = displayitem->Value[i];
			temp[1] = 0;
			LCD_DrawText(LCD_PIXEL_WIDTH-(displayitem->maxVal-i)*8, y, temp);
		}
		Menu_Mask |= 12;
	}
	switch(displayitem->status)
	{
	case normalStatus:
		if(displayitem->type == checkbox)
		{
			LCD_FillRectangle(INDICATE_AREAS_WIDTH+1, y+5, 6, 6, 1);
			LCD_FillRectangle(INDICATE_AREAS_WIDTH+2, y+6, 4, 4, 0);
			//LCD_FillRectangle(INDICATE_AREAS_WIDTH+2, y+6, 4, 4, 1);
			Menu_Mask |= 2;
		}
		break;
	case checked:
		//LCD_DrawChineseText(X_SPACE_FRONT, y, String_checked1);//""��");
		//    LCD_FillRectangle(INDICATE_AREAS_WIDTH+1, y+3, 5, 5, 1);
		LCD_FillRectangle(INDICATE_AREAS_WIDTH+1, y+5, 6, 6, 1);
		LCD_FillRectangle(INDICATE_AREAS_WIDTH+2, y+6, 4, 4, 0);
		LCD_FillRectangle(INDICATE_AREAS_WIDTH+3, y+7, 2, 2, 1);
		Menu_Mask |= 2;
		break;
	case radiochecked:
		LCD_DrawText(INDICATE_AREAS_WIDTH, y, "*");//"��");
		Menu_Mask |= 2;
		break;
	case editting:
		if(displayitem->type == pwdEditor)
			LCD_InverseRegion(LCD_PIXEL_WIDTH-(displayitem->maxVal-displayitem->ActiveIndex)*8,y,8, LCD_MENUITEM_HEIGHT);
		else
			LCD_InverseRegion(LCD_PIXEL_WIDTH-(displayitem->maxVal+2-displayitem->ActiveIndex)*8,y,8, LCD_MENUITEM_HEIGHT);
		break;
	}
	if(!(Menu_Mask & 1)&&(Cur_Refresh == True))
		LCD_DrawPicture(0, y, 8, 16, imgZero);	
#if defined(LCD_MODULE_128_64_ST5668A)
	if(!(Menu_Mask & 2))
		LCD_DrawPicture(radiocheckbox_offset, y, 8, 16, imgZero);
#else
	if(!(Menu_Mask & 2))
		LCD_DrawPicture(INDICATE_AREAS_WIDTH, y, 8, 16, imgZero);
#endif
#if !defined(LCD_MODULE_128_64_ST5668A)
	if(!(Menu_Mask & 4))
		LCD_DrawPicture(LCD_PIXEL_WIDTH - INDICATE_AREAS_WIDTH*2, y, 8, 16, imgZero);
#endif
	if(!(Menu_Mask & 8))
		LCD_DrawPicture(LCD_PIXEL_WIDTH - INDICATE_AREAS_WIDTH, y, 8, 16, imgZero);
	if(displayitem->selected && displayitem->status!= editting)		
		LCD_InverseRegion(INDICATE_AREAS_WIDTH,y,LCD_PIXEL_WIDTH-INDICATE_AREAS_WIDTH, LCD_MENUITEM_HEIGHT);
	
	return 1;
}

//=====================================================================//
//������void Redraw_Menu(UCHAR First_Index,UCHAR Menu_Index,UINT** Menu_List)
//������ˢ�������˵���ʾ����
//������First_Index  ������ʾҳ�ĵ�һ���˵���
//		offset   ��ǰ����ѡ�õĲ˵��������First_Index��ƫ����
//		Menu_List    �˵���Դ����ָ��
//���أ�
//ע�⣺��
//=====================================================================//
void RefreshScreen(UCHAR First_Index,struct MenuItem *Menu_List,enum LCD_DisModeEnum DisMode)
{
	CurrentDisMode = DisMode;
	First_Index_old=First_Index;
	//Language = Menu_List->Lang;
	Dis_Menu_Num_Page = GetMLiNum_Page();
	unsigned short i,j,x,y,List_Num,visibelNum;
	List_Num = Menu_List->ItemCount;
	visibelNum = GetMLNum(Menu_List);
	//	LCD_ClearScreen();
	
	if(DisMode == MainScreen)
		DrawMainScreen(CurrentStatus, &MainScreenRoot);
	else
	{
		LastDisMode_Main = False;
		//LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
		for(i=First_Index,j=0;i<List_Num;i++)
		{
			if(DisMode != MainScreen &&  j >= Dis_Menu_Num_Page)
				break;
			if((Menu_List->ChildItems+i)->Visible == 1)
				j++;
			else
				continue;
			switch(DisMode)
			{
			case MainScreen:
				//x =((j-1)%MainScreen_ColCount)*LCD_PIXEL_WIDTH/MainScreen_ColCount;
				//y= LCD_MENUITEM_HEIGHT*((j-1)/MainScreen_ColCount);	
				break;
			case Menu:
			case Edit:		
				x = 0;
				y = (j-1)*LCD_MENUITEM_HEIGHT;
				if(Menu_List->SelectedIndex == i)//((j-1) == offset)
				{
					(Menu_List->ChildItems+i)->selected = 1;
				}
				else
					(Menu_List->ChildItems+i)->selected = 0;
				ShowMenu_Item(x, y, (Menu_List->ChildItems+i));
				break;		
			case Reserved:
			default:
				break;
			}
		}
	#if defined(LCD_MODULE_128_64_ST5668A)
		radiocheckbox_offset = 0;
	#endif
		if(j!=4)	
			LCD_FillRectangle(0, j*16, LCD_PIXEL_WIDTH, (4-j)*16, 0);
		
	}
	//�˵�ģʽ�»�ָʾ��ͷ
	if(DisMode == Menu)
	{	
		//    unsigned short String_top[]={38,0};/*--  ����38:  ��  --*/
		//    unsigned short String_down[]={39,0};/*--  ����39:  ��  --*/
		//    unsigned short String_left[]={40,0};/*--  ����40:  ��  --*/
		UCHAR IsStart = 1;
		for(int m=0;m<First_Index;m++)
		{
			if((Menu_List->ChildItems+m)->Visible)
			{
				IsStart = 0;
				break;
			}
		}
		if(IsStart==0)
		{
			LCD_DrawPicture(0, 0, 8, 8, imgTop);//LCD_DrawText(0, 0, "^");
		}
		UCHAR IsEnd = 1;
		for(;i<List_Num;i++)
		{
			if((Menu_List->ChildItems+i)->Visible)
			{
				IsEnd = 0;
				break;
			}
		}
		if(IsEnd == 0)
		{
			LCD_DrawPicture(0, LCD_PIXEL_HIGH - 8, 8, 8, imgBot);//LCD_DrawText(0, LCD_PIXEL_HIGH - LCD_MENUITEM_HEIGHT, "v");
			LCD_DrawPicture(0, LCD_PIXEL_HIGH - 16, 8, 8, imgZero);
		}
		else
			LCD_DrawPicture(0, LCD_PIXEL_HIGH - 16, 8, 16, imgZero);
		
		if(Menu_List->Parents!=0)
		{
			LCD_DrawPicture(0, LCD_MENUITEM_HEIGHT/2, 8, 8, imgLeft);//LCD_DrawText(0, LCD_MENUITEM_HEIGHT/2, "<");
			if(IsStart!=0)
				LCD_DrawPicture(0, 0, 8, 8, imgZero);//LCD_DrawText(0, LCD_PIXEL_HIGH - LCD_MENUITEM_HEIGHT, "v");
		}
		else
		{
			if(IsStart!=0)
				LCD_DrawPicture(0, 0, 8, 16, imgZero);//LCD_DrawText(0, LCD_PIXEL_HIGH - LCD_MENUITEM_HEIGHT, "v");
			else
				LCD_DrawPicture(0, LCD_MENUITEM_HEIGHT/2, 8, 8, imgZero);//LCD_DrawText(0, LCD_MENUITEM_HEIGHT/2, "<");
		}
	}
}
CHAR MainInfo_PrintQuality[20] = {0};	
extern CHAR MainInfo_Step[];
extern CHAR Last_MainInfo_Step[];
void Set_PrintQuality(INT8U index)
{
	INT8U level = index & 0x0f;			//��ǿ��
	INT8U type = (index & 0xf0) >> 4;	//������
#if defined(LCD_MODULE_128_64_ST5668A)
	const char level_en[][13] = {"Off", "weak", "mid", "high"};
#else
	const char level_en[][13] = {"Feather off", "weak", "normal", "high"};
#endif
	const char level_cn[][8] = {"�𻯹�", "��", "��", "ǿ"};
	const char type_en[][4] = {"G:", "U:", "W:", "A:", "UG:", "T:"};
	const char type_cn[][10] = {"����:", "ƽ��:", "����:", "���䲨��:", "ƽ������:", "����:"};
	
	if(UILanguage == en)
	{
		if(level == 0)
		{
			sprintf(MainInfo_PrintQuality,level_en[level]);
			return;
		}
		sprintf(MainInfo_PrintQuality,type_en[type]);
		strcat(MainInfo_PrintQuality,level_en[level]);
		return;
	}
	else
	{
		if(level == 0)
		{
			sprintf(MainInfo_PrintQuality,level_cn[level]);
			return;
		}
	#if defined(LCD_MODULE_128_64_ST5668A)
		sprintf(MainInfo_PrintQuality,type_en[type]);
	#else
		sprintf(MainInfo_PrintQuality,type_cn[type]);
	#endif
		strcat(MainInfo_PrintQuality,level_cn[level]);
		return;
	}
#if 0
	if(UILanguage == en)
	{
		switch(index)
		{
#ifdef MANUFACTURER_GZ  	
		case 0:
		case 1:
			sprintf(MainInfo_PrintQuality,"    low");
			break;
		case 2:
			sprintf(MainInfo_PrintQuality,"    normal");
			break;
		case 3:
			sprintf(MainInfo_PrintQuality,"    high");
			break;
#else
		case 0:
			sprintf(MainInfo_PrintQuality,"F: off");
			break;
		case 1:
			sprintf(MainInfo_PrintQuality,"F: weak");
			break;
		case 2:
			sprintf(MainInfo_PrintQuality,"F: normal");
			break;
		case 3:
			sprintf(MainInfo_PrintQuality,"F: strong");
			break;
#endif				
		}
	}
	else
	{
		switch(index)
		{
#ifdef MANUFACTURER_GZ  	
		case 0:
		case 1:
			sprintf(MainInfo_PrintQuality,"    ��");
			break;
		case 2:
			sprintf(MainInfo_PrintQuality,"    ��");
			break;
		case 3:
			sprintf(MainInfo_PrintQuality,"    ��");
			break;
#else  		
		case 0:
			sprintf(MainInfo_PrintQuality,"��:��");
			break;
		case 1:
			sprintf(MainInfo_PrintQuality,"��:��");
			break;
		case 2:
			sprintf(MainInfo_PrintQuality,"��:��");
			break;
		case 3:
			sprintf(MainInfo_PrintQuality,"��:ǿ");
			break;
#endif				
		}
	}
#endif
}
void Draw_PrintQuality(void)
{
#ifdef RIPSTAR_FLAT_EX
	LCD_FillRectangle(LCD_PIXEL_WIDTH/2, LCD_PIXEL_HIGH-16, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
#else
	LCD_FillRectangle(0, LCD_PIXEL_HIGH-16, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
#endif
#ifdef MANUFACTURER_DYSS
	LCD_FillRectangle(strlen(MainInfo_PrintOrigin)*8 + CHECKBOX_WIDTH + 3*8, LCD_PIXEL_HIGH-16, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
#endif
	if(UILanguage == en) //(Menu_List->Lang == en)
	{
#ifndef RIPSTAR_FLAT_EX    
		LCD_DrawText(CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, "Quality");//����
		LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);
#else
		LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
		
#endif        
	}
	else
	{
#ifndef RIPSTAR_FLAT_EX    	
		LCD_DrawText(CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, "����");//����
		LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);
#else
		LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
#endif       
	}
}
extern void Draw_Print_QualityStep(void);
void DrawMainScreen(enum StatusTypeEnum status,struct MenuItem *Menu_List)
{
	int baseX = CHECKBOX_WIDTH;// + INDICATE_AREAS_WIDTH	
	INT8U Be_Refresh = True;
#if defined(LCD_MODULE_128_64_ST5668A)
	baseX = 0;
#endif
	if((Last_Status != CurrentStatus)||(LastDisMode_Main == False))
	{
		Be_Refresh = True;
	}
	else
	{
		Be_Refresh = False;
	}
	
	if(CurrentDisMode == MainScreen)
	{
		//	LCD_ClearScreen();
		//   LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
		if(UILanguage == en) //(Menu_List->Lang == en)
		{
			//    LCD_DrawText(baseX, 0, (Menu_List->ChildItems+0)->Text_en);//״̬
			switch(CurrentStatus)
			{
			case E_ST_SVC:
			case E_ST_FTA:
			case E_ST_ERR:
			case E_ST_ERR_AUTO:
			case E_ST_WAR:	
				LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
				LCD_DrawText(baseX, 0, (Menu_List->ChildItems+0)->Text_en);//״̬
			#if defined(LCD_MODULE_128_64_ST5668A)
				LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount+baseX, 0, (Menu_List->ChildItems+2)->Text_en);//�����
			#else
				LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount-baseX, 0, (Menu_List->ChildItems+2)->Text_en);//�����
			#endif
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT, (Menu_List->ChildItems+7)->Text_en);//��δʵ���Զ�����
				break;			
			case E_ST_INI:
				if(!strncmp((Menu_List->ChildItems+2)->Text_en, MainInfo_last_pid, strlen((Menu_List->ChildItems+2)->Text_en))&& \
					!strncmp(MainInfo_ManufactureName, MainInfo_Last_ManufactureName, strlen(MainInfo_ManufactureName))&& \
						!strncmp(MainInfo_PrinterName, MainInfo_Last_PrinterName, strlen(MainInfo_PrinterName))&& \
							(Be_Refresh == FALSE))
				{
					break;
				}
				LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
				LCD_DrawText(baseX, 0, (Menu_List->ChildItems+0)->Text_en);//״̬
			#if defined(LCD_MODULE_128_64_ST5668A)
				LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount+baseX, 0, (Menu_List->ChildItems+2)->Text_en);//���̺�
			#else
				LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount-baseX, 0, (Menu_List->ChildItems+2)->Text_en);//���̺�
			#endif
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT, MainInfo_ManufactureName);//ManufactureName
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*2, MainInfo_PrinterName);//PrinterName
				strcpy(MainInfo_last_pid, (Menu_List->ChildItems+0)->Text_en);
				strcpy(MainInfo_Last_ManufactureName, MainInfo_ManufactureName);
				strcpy(MainInfo_Last_PrinterName, MainInfo_PrinterName);
				break;
			case E_ST_MOVING:
			case E_ST_CLEANING:
			case E_ST_CANCELING:
			case E_ST_RDY:			  	
#ifdef FUNC_MAINTAIN
			case E_ST_MAINTAIN:
#endif
				//LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount, 0, (Menu_List->ChildItems+1)->Text_en);//�ٷֱ�
				// LCD_FillRectangle(LCD_PIXEL_WIDTH/MainScreen_ColCount, 0, LCD_PIXEL_WIDTH/MainScreen_ColCount, LCD_MENUITEM_HEIGHT, 0);
#ifdef RIPSTAR_FLAT_EX
				if(!strncmp(MainInfo_MediaWidth, Last_MainInfo_MediaWidth, strlen(MainInfo_MediaWidth))&& \
					!strncmp(MainInfo_PrintOrigin, Last_MainInfo_PrintOrigin, strlen(MainInfo_PrintOrigin))&& \
						!strncmp(MainInfo_MediaLength, Last_MainInfo_MediaLength, strlen(MainInfo_MediaLength))&& \
							!strncmp(MainInfo_YOrigin, Last_MainInfo_YOrigin, strlen(MainInfo_YOrigin))&& \
								!strncmp(MainInfo_ZOrigin, Last_MainInfo_ZOrigin, strlen(MainInfo_ZOrigin))&& \
									(Be_Refresh == FALSE))
#else
					if(!strncmp(MainInfo_MediaWidth, Last_MainInfo_MediaWidth, strlen(MainInfo_MediaWidth))&& \
						!strncmp(MainInfo_PrintOrigin, Last_MainInfo_PrintOrigin, strlen(MainInfo_PrintOrigin))&& \
							(Be_Refresh == FALSE))
#endif			 
					{
						break;
					}
					else
					{
#ifdef FUNC_MAINTAIN
						#ifdef RIPSTAR_FLAT_EX
						if(!strncmp(MainInfo_MediaWidth, Last_MainInfo_MediaWidth, strlen(MainInfo_MediaWidth))&& \
							!strncmp(MainInfo_PrintOrigin, Last_MainInfo_PrintOrigin, strlen(MainInfo_PrintOrigin))&& \
							!strncmp(MainInfo_MediaLength, Last_MainInfo_MediaLength, strlen(MainInfo_MediaLength))&& \
							!strncmp(MainInfo_YOrigin, Last_MainInfo_YOrigin, strlen(MainInfo_YOrigin))&& \
							!strncmp(MainInfo_ZOrigin, Last_MainInfo_ZOrigin, strlen(MainInfo_ZOrigin))&& \
							(LastDisMode_Main == True) && ((Last_Status ==E_ST_MOVING)||(Last_Status ==E_ST_CLEANING)||(Last_Status ==E_ST_CANCELING)||(Last_Status ==E_ST_RDY)||(Last_Status ==E_ST_MAINTAIN)))					
#else
							if(!strncmp(MainInfo_MediaWidth, Last_MainInfo_MediaWidth, strlen(MainInfo_MediaWidth))&& \
								!strncmp(MainInfo_PrintOrigin, Last_MainInfo_PrintOrigin, strlen(MainInfo_PrintOrigin))&& \
								(LastDisMode_Main == True) && ((Last_Status ==E_ST_MOVING)||(Last_Status ==E_ST_CLEANING)||(Last_Status ==E_ST_CANCELING)||(Last_Status ==E_ST_RDY)||(Last_Status ==E_ST_MAINTAIN)))
#endif			
#else	//else undef FUNC_MAINTAIN
#ifdef RIPSTAR_FLAT_EX
						if(!strncmp(MainInfo_MediaWidth, Last_MainInfo_MediaWidth, strlen(MainInfo_MediaWidth))&& \
							!strncmp(MainInfo_PrintOrigin, Last_MainInfo_PrintOrigin, strlen(MainInfo_PrintOrigin))&& \
							!strncmp(MainInfo_MediaLength, Last_MainInfo_MediaLength, strlen(MainInfo_MediaLength))&& \
							!strncmp(MainInfo_YOrigin, Last_MainInfo_YOrigin, strlen(MainInfo_YOrigin))&& \
							!strncmp(MainInfo_ZOrigin, Last_MainInfo_ZOrigin, strlen(MainInfo_ZOrigin))&& \
							(LastDisMode_Main == True) && ((Last_Status ==E_ST_MOVING)||(Last_Status ==E_ST_CLEANING)||(Last_Status ==E_ST_CANCELING)||(Last_Status ==E_ST_RDY)))					
#else
							if(!strncmp(MainInfo_MediaWidth, Last_MainInfo_MediaWidth, strlen(MainInfo_MediaWidth))&& \
								!strncmp(MainInfo_PrintOrigin, Last_MainInfo_PrintOrigin, strlen(MainInfo_PrintOrigin))&& \
								(LastDisMode_Main == True) && ((Last_Status ==E_ST_MOVING)||(Last_Status ==E_ST_CLEANING)||(Last_Status ==E_ST_CANCELING)||(Last_Status ==E_ST_RDY)))
#endif			
#endif	//FUNC_MAINTAIN
							{
								LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, 16, 0);
								LCD_DrawText(baseX, 0, (Menu_List->ChildItems+0)->Text_en);//״̬
								break;
							}			 
						strcpy(Last_MainInfo_MediaWidth, MainInfo_MediaWidth);
						strcpy(Last_MainInfo_PrintOrigin, MainInfo_PrintOrigin);
#ifdef RIPSTAR_FLAT_EX
						strcpy(Last_MainInfo_MediaLength, MainInfo_MediaLength);
						strcpy(Last_MainInfo_YOrigin, MainInfo_YOrigin);
						strcpy(Last_MainInfo_ZOrigin, MainInfo_ZOrigin);
#endif
					}
				LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
				LCD_DrawText(baseX, 0, (Menu_List->ChildItems+0)->Text_en);//״̬
#ifdef RIPSTAR_FLAT_EX
			#if defined(LCD_MODULE_128_64_ST5668A)
				LCD_DrawText(LCD_PIXEL_WIDTH-8*INDICATE_AREAS_WIDTH-baseX*6, LCD_MENUITEM_HEIGHT, "W:");//ֽ��				
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_MediaWidth)*8-baseX*6, LCD_MENUITEM_HEIGHT, MainInfo_MediaWidth);//ֽ��ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT, "X:");//ԭ��
				LCD_DrawText(INDICATE_AREAS_WIDTH*2, LCD_MENUITEM_HEIGHT, MainInfo_PrintOrigin);//ԭ��ֵ		
				LCD_DrawText(LCD_PIXEL_WIDTH-8*INDICATE_AREAS_WIDTH-baseX*6, LCD_MENUITEM_HEIGHT*2, "L:");//ֽ��			   
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_MediaLength)*8-baseX*6, LCD_MENUITEM_HEIGHT*2, MainInfo_MediaLength);//ֽ��ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*2, "Y:");//ԭ��
				LCD_DrawText(INDICATE_AREAS_WIDTH*2, LCD_MENUITEM_HEIGHT*2, MainInfo_YOrigin);//ԭ��ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*3, "Z:");//����
				LCD_DrawText(INDICATE_AREAS_WIDTH*2, LCD_MENUITEM_HEIGHT*3, MainInfo_ZOrigin);//ԭ��ֵ
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
			#else
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintOrigin)*8-baseX*6, LCD_MENUITEM_HEIGHT, "W:");//ֽ��				
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_MediaWidth)-baseX*6, LCD_MENUITEM_HEIGHT, MainInfo_MediaWidth);//ֽ��ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT, "X:");//ԭ��
				LCD_DrawText(baseX*4, LCD_MENUITEM_HEIGHT, MainInfo_PrintOrigin);//ԭ��ֵ		
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintOrigin)*8-baseX*6, LCD_MENUITEM_HEIGHT*2, "L:");//ֽ��			   
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_MediaWidth)-baseX*6, LCD_MENUITEM_HEIGHT*2, MainInfo_MediaLength);//ֽ��ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*2, "Y:");//ԭ��
				LCD_DrawText(baseX*4, LCD_MENUITEM_HEIGHT*2, MainInfo_YOrigin);//ԭ��ֵ
				LCD_DrawText(CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, "Z:");//����
				LCD_DrawText(baseX*4, LCD_MENUITEM_HEIGHT*3, MainInfo_ZOrigin);//ԭ��ֵ
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
			#endif
#else
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT, (Menu_List->ChildItems+3)->Text_en);//ֽ��				
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_MediaWidth)*8-baseX, LCD_MENUITEM_HEIGHT, MainInfo_MediaWidth);//ֽ��ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*2, (Menu_List->ChildItems+4)->Text_en);//ԭ��
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintOrigin)*8-baseX, LCD_MENUITEM_HEIGHT*2, MainInfo_PrintOrigin);//ԭ��ֵ
			#if defined(LCD_MODULE_128_64_ST5668A)
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*3, "Quality");//����
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-baseX, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
			#else
				LCD_DrawText(CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, "Quality");//����
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
#endif
#endif
				
				// Draw_PrintQuality();
				break;			
			case E_ST_UPDATING:
				LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
				LCD_DrawText(baseX, 0, (Menu_List->ChildItems+0)->Text_en);//״̬
		#if defined(LCD_MODULE_128_64_ST5668A)
				LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount+2*CHECKBOX_WIDTH, 0, MainInfo_percent);//�ٷֱ�
		#else
				LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount-baseX, 0, MainInfo_percent);//�ٷֱ�
		#endif
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT, MainInfo_ManufactureName);//ManufactureName
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*2, MainInfo_PrinterName);//PrinterName
				break;
			case E_ST_PRINT:
			case E_ST_PAUSE:
				if(!strncmp(MainInfo_percent, Last_MainInfo_percent, strlen(MainInfo_percent))&& \
					!strncmp(MainInfo_PassNum, Last_MainInfo_PassNum, strlen(MainInfo_PassNum))&& \
						!strncmp(MainInfo_Resolution, Last_MainInfo_Resolution, strlen(MainInfo_Resolution))&& \
							!strncmp(MainInfo_Step, Last_MainInfo_Step, strlen(MainInfo_Step))&& \
								(Be_Refresh == FALSE))
				{
					break;
				}
				else
				{	
					if(!strncmp(MainInfo_PassNum, Last_MainInfo_PassNum, strlen(MainInfo_PassNum))&& \
						!strncmp(MainInfo_Resolution, Last_MainInfo_Resolution, strlen(MainInfo_Resolution))&& \
							!strncmp(MainInfo_Step, Last_MainInfo_Step, strlen(MainInfo_Step))&& \
								(LastDisMode_Main == True) && ((Last_Status ==E_ST_PRINT)||(Last_Status ==E_ST_PAUSE)))			{
								LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, 16, 0);
								LCD_DrawText(baseX, 0, (Menu_List->ChildItems+0)->Text_en);//״̬
								if(CurrentStatus == E_ST_PRINT)
						#if defined(LCD_MODULE_128_64_ST5668A)
									LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount+2*CHECKBOX_WIDTH, 0, MainInfo_percent);//�ٷֱ�
						#else
									LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount-baseX, 0, MainInfo_percent);//�ٷֱ�
						#endif
#ifdef MICOLOR_AUTOFUCTION				 
								else if(!Media_Lack&&!Cover_up&&!Media_Not_Fixed)
#else
								else
#endif
									LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount-baseX, 0, Last_MainInfo_PassNum);//�ٷֱ�
								if((CurrentStatus == E_ST_PRINT)&&(Last_Status == E_ST_PAUSE))  
									Draw_Print_QualityStep();
								strcpy(Last_MainInfo_PassNum, MainInfo_PassNum);
								strcpy(Last_MainInfo_Resolution, MainInfo_Resolution);
								strcpy(Last_MainInfo_percent, MainInfo_percent);
								strcpy(Last_MainInfo_Step, MainInfo_Step);
								break;
							}	
				}
				LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
				LCD_DrawText(baseX, 0, (Menu_List->ChildItems+0)->Text_en);//״̬
				if(CurrentStatus == E_ST_PRINT)
			#if defined(LCD_MODULE_128_64_ST5668A)
					LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount+2*CHECKBOX_WIDTH, 0, MainInfo_percent);//�ٷֱ�
			#else
					LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount-baseX, 0, MainInfo_percent);//�ٷֱ�
			#endif
#ifdef MICOLOR_AUTOFUCTION				 
				else if(!Media_Lack&&!Cover_up&&!Media_Not_Fixed)
#else
				else
#endif
		#if defined(LCD_MODULE_128_64_ST5668A)
				LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount+2*CHECKBOX_WIDTH, 0, Last_MainInfo_percent);//�ٷֱ�
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT, (Menu_List->ChildItems+5)->Text_en);//pass��
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintOrigin)*8+CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT, MainInfo_PassNum);//pass��ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*2, (Menu_List->ChildItems+6)->Text_en);//�ֱ���
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_Resolution)*8-baseX, LCD_MENUITEM_HEIGHT*2, MainInfo_Resolution);//�ֱ���ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*3, "Quality");//����
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-baseX, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
		#else
					LCD_DrawText(LCD_PIXEL_WIDTH/MainScreen_ColCount-baseX, 0, Last_MainInfo_PassNum);//�ٷֱ�
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT, (Menu_List->ChildItems+5)->Text_en);//pass��
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintOrigin)*8-baseX, LCD_MENUITEM_HEIGHT, MainInfo_PassNum);//pass��ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*2, (Menu_List->ChildItems+6)->Text_en);//�ֱ���
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_Resolution)*8-baseX, LCD_MENUITEM_HEIGHT*2, MainInfo_Resolution);//�ֱ���ֵ
				LCD_DrawText(CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, "Quality");//����
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
		#endif
				strcpy(Last_MainInfo_PassNum, MainInfo_PassNum);
				strcpy(Last_MainInfo_Resolution, MainInfo_Resolution);
				strcpy(Last_MainInfo_percent, MainInfo_percent);	
				strcpy(Last_MainInfo_Step, MainInfo_Step);
				//Draw_PrintQuality();
				if(CurrentStatus == E_ST_PRINT)
					Draw_Print_QualityStep();
				break;			
			default:
				break;
			}
		}
		else
		{
			// LCD_DrawMixedText(baseX, 0, (Menu_List->ChildItems+0)->Text_ch);//״̬
			switch(CurrentStatus)
			{			
			case E_ST_SVC:
			case E_ST_FTA:
			case E_ST_ERR:
			case E_ST_ERR_AUTO:
			case E_ST_WAR:
				LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
				LCD_DrawMixedText(baseX, 0, (Menu_List->ChildItems+0)->Text_ch);//״̬
			#if defined(LCD_MODULE_128_64_ST5668A)
				LCD_DrawMixedText(LCD_PIXEL_WIDTH/MainScreen_ColCount+baseX, 0, (Menu_List->ChildItems+2)->Text_ch);//����?			
			#else
				LCD_DrawMixedText(LCD_PIXEL_WIDTH/MainScreen_ColCount-baseX, 0, (Menu_List->ChildItems+2)->Text_ch);//�����
			#endif
				LCD_DrawMixedText(baseX, LCD_MENUITEM_HEIGHT, (Menu_List->ChildItems+7)->Text_ch);//��δʵ���Զ�����
				break;			
			case E_ST_INI:
				if(!strncmp((CHAR*)(Menu_List->ChildItems+2)->Text_ch, MainInfo_last_pid, strlen((CHAR*)(Menu_List->ChildItems+2)->Text_ch))&& \
					!strncmp(MainInfo_ManufactureName, MainInfo_Last_ManufactureName, strlen(MainInfo_ManufactureName))&& \
						!strncmp(MainInfo_PrinterName, MainInfo_Last_PrinterName, strlen(MainInfo_PrinterName))&& \
							(Be_Refresh == FALSE))
				{
					break;
				}
				LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
				LCD_DrawMixedText(baseX, 0, (Menu_List->ChildItems+0)->Text_ch);//״̬
			#if defined(LCD_MODULE_128_64_ST5668A)
				LCD_DrawMixedText(LCD_PIXEL_WIDTH/MainScreen_ColCount+baseX, 0, (Menu_List->ChildItems+2)->Text_ch);//���̺�
			#else
				LCD_DrawMixedText(LCD_PIXEL_WIDTH/MainScreen_ColCount-baseX, 0, (Menu_List->ChildItems+2)->Text_ch);//���̺�
			#endif
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT, MainInfo_ManufactureName);//ManufactureName
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*2, MainInfo_PrinterName);//PrinterName
				strcpy(MainInfo_last_pid, (CHAR*)(Menu_List->ChildItems+2)->Text_ch);
				strcpy(MainInfo_Last_ManufactureName, MainInfo_ManufactureName);
				strcpy(MainInfo_Last_PrinterName, MainInfo_PrinterName);
				break;
			case E_ST_MOVING:
			case E_ST_CLEANING:
			case E_ST_CANCELING:
			case E_ST_RDY:	
#ifdef FUNC_MAINTAIN
			case E_ST_MAINTAIN:
#endif
				//LCD_DrawMixedText(LCD_PIXEL_WIDTH/MainScreen_ColCount, 0, (Menu_List->ChildItems+1)->Text_ch);//�ٷֱ�
				//LCD_FillRectangle(LCD_PIXEL_WIDTH/MainScreen_ColCount-baseX, 0, LCD_PIXEL_WIDTH/MainScreen_ColCount, LCD_MENUITEM_HEIGHT, 0);
#ifdef RIPSTAR_FLAT_EX
				if(!strncmp(MainInfo_MediaWidth, Last_MainInfo_MediaWidth, strlen(MainInfo_MediaWidth))&& \
					!strncmp(MainInfo_PrintOrigin, Last_MainInfo_PrintOrigin, strlen(MainInfo_PrintOrigin))&& \
						!strncmp(MainInfo_MediaLength, Last_MainInfo_MediaLength, strlen(MainInfo_MediaLength))&& \
							!strncmp(MainInfo_YOrigin, Last_MainInfo_YOrigin, strlen(MainInfo_YOrigin))&& \
								!strncmp(MainInfo_ZOrigin, Last_MainInfo_ZOrigin, strlen(MainInfo_ZOrigin))&& \
									(Be_Refresh == FALSE))
#else	
					if(!strncmp(MainInfo_MediaWidth, Last_MainInfo_MediaWidth, strlen(MainInfo_MediaWidth))&& \
						!strncmp(MainInfo_PrintOrigin, Last_MainInfo_PrintOrigin, strlen(MainInfo_PrintOrigin))&& \
							(Be_Refresh == FALSE))
#endif
					{
						break;
					}
					else
					{
#ifdef FUNC_MAINTAIN
						#ifdef RIPSTAR_FLAT_EX
						if(!strncmp(MainInfo_MediaWidth, Last_MainInfo_MediaWidth, strlen(MainInfo_MediaWidth))&& \
							!strncmp(MainInfo_PrintOrigin, Last_MainInfo_PrintOrigin, strlen(MainInfo_PrintOrigin))&& \
							!strncmp(MainInfo_MediaLength, Last_MainInfo_MediaLength, strlen(MainInfo_MediaLength))&& \
							!strncmp(MainInfo_YOrigin, Last_MainInfo_YOrigin, strlen(MainInfo_YOrigin))&& \
							!strncmp(MainInfo_ZOrigin, Last_MainInfo_ZOrigin, strlen(MainInfo_ZOrigin))&& \
							(LastDisMode_Main == True) && ((Last_Status ==E_ST_MOVING)||(Last_Status ==E_ST_CLEANING)||(Last_Status ==E_ST_CANCELING)||(Last_Status ==E_ST_RDY)||(Last_Status ==E_ST_MAINTAIN)))
#else
							if(!strncmp(MainInfo_MediaWidth, Last_MainInfo_MediaWidth, strlen(MainInfo_MediaWidth))&& \
								!strncmp(MainInfo_PrintOrigin, Last_MainInfo_PrintOrigin, strlen(MainInfo_PrintOrigin))&& \
								(LastDisMode_Main == True) && ((Last_Status ==E_ST_MOVING)||(Last_Status ==E_ST_CLEANING)||(Last_Status ==E_ST_CANCELING)||(Last_Status ==E_ST_RDY) ||(Last_Status ==E_ST_MAINTAIN)))
#endif	
#else	//else undef FUNC_MAINTAIN
#ifdef RIPSTAR_FLAT_EX
						if(!strncmp(MainInfo_MediaWidth, Last_MainInfo_MediaWidth, strlen(MainInfo_MediaWidth))&& \
							!strncmp(MainInfo_PrintOrigin, Last_MainInfo_PrintOrigin, strlen(MainInfo_PrintOrigin))&& \
								!strncmp(MainInfo_MediaLength, Last_MainInfo_MediaLength, strlen(MainInfo_MediaLength))&& \
									!strncmp(MainInfo_YOrigin, Last_MainInfo_YOrigin, strlen(MainInfo_YOrigin))&& \
										!strncmp(MainInfo_ZOrigin, Last_MainInfo_ZOrigin, strlen(MainInfo_ZOrigin))&& \
											(LastDisMode_Main == True) && ((Last_Status ==E_ST_MOVING)||(Last_Status ==E_ST_CLEANING)||(Last_Status ==E_ST_CANCELING)||(Last_Status ==E_ST_RDY)))
#else
							if(!strncmp(MainInfo_MediaWidth, Last_MainInfo_MediaWidth, strlen(MainInfo_MediaWidth))&& \
								!strncmp(MainInfo_PrintOrigin, Last_MainInfo_PrintOrigin, strlen(MainInfo_PrintOrigin))&& \
									(LastDisMode_Main == True) && ((Last_Status ==E_ST_MOVING)||(Last_Status ==E_ST_CLEANING)||(Last_Status ==E_ST_CANCELING)||(Last_Status ==E_ST_RDY)))
#endif	
#endif //end FUNC_MAINTAIN
							{
								LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, 16, 0);
								LCD_DrawMixedText(baseX, 0, (Menu_List->ChildItems+0)->Text_ch);//״̬
								break;
							}	
						strcpy(Last_MainInfo_MediaWidth, MainInfo_MediaWidth);
						strcpy(Last_MainInfo_PrintOrigin, MainInfo_PrintOrigin);
#ifdef RIPSTAR_FLAT_EX
						strcpy(Last_MainInfo_MediaLength, MainInfo_MediaLength);
						strcpy(Last_MainInfo_YOrigin, MainInfo_YOrigin);
						strcpy(Last_MainInfo_ZOrigin, MainInfo_ZOrigin);
#endif
					}
				LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
				LCD_DrawMixedText(baseX, 0, (Menu_List->ChildItems+0)->Text_ch);//״̬
#ifdef RIPSTAR_FLAT_EX
			#if defined(LCD_MODULE_128_64_ST5668A)
				LCD_DrawText(LCD_PIXEL_WIDTH-8*INDICATE_AREAS_WIDTH-baseX*6, LCD_MENUITEM_HEIGHT, "W:");//ֽ��				
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_MediaWidth)*8-baseX*6, LCD_MENUITEM_HEIGHT, MainInfo_MediaWidth);//ֽ��ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT, "X:");//ԭ��
				LCD_DrawText(2*INDICATE_AREAS_WIDTH, LCD_MENUITEM_HEIGHT, MainInfo_PrintOrigin);//ԭ��ֵ
				
				
				LCD_DrawText(LCD_PIXEL_WIDTH-8*INDICATE_AREAS_WIDTH-baseX*6, LCD_MENUITEM_HEIGHT*2, "L:");//ֽ��			   
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_MediaLength)*8-baseX*6, LCD_MENUITEM_HEIGHT*2, MainInfo_MediaLength);//ֽ��ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*2, "Y:");//ԭ��
				LCD_DrawText(2*INDICATE_AREAS_WIDTH, LCD_MENUITEM_HEIGHT*2, MainInfo_YOrigin);//ԭ��ֵ
				
				
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*3, "Z:");
				LCD_DrawText(2*INDICATE_AREAS_WIDTH, LCD_MENUITEM_HEIGHT*3, MainInfo_ZOrigin);//ԭ��ֵ
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
			#else
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintOrigin)*8-baseX*6, LCD_MENUITEM_HEIGHT, "W:");//ֽ��				
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_MediaWidth)-baseX*6, LCD_MENUITEM_HEIGHT, MainInfo_MediaWidth);//ֽ��ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT, "X:");//ԭ��
				LCD_DrawText(baseX*4, LCD_MENUITEM_HEIGHT, MainInfo_PrintOrigin);//ԭ��ֵ
				
				
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintOrigin)*8-baseX*6, LCD_MENUITEM_HEIGHT*2, "L:");//ֽ��			   
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_MediaWidth)-baseX*6, LCD_MENUITEM_HEIGHT*2, MainInfo_MediaLength);//ֽ��ֵ
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*2, "Y:");//ԭ��
				LCD_DrawText(baseX*4, LCD_MENUITEM_HEIGHT*2, MainInfo_YOrigin);//ԭ��ֵ
				
				
				LCD_DrawText(CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, "Z:");
				LCD_DrawText(baseX*4, LCD_MENUITEM_HEIGHT*3, MainInfo_ZOrigin);//ԭ��ֵ
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
			#endif
#else
				LCD_DrawMixedText(baseX, LCD_MENUITEM_HEIGHT, (Menu_List->ChildItems+3)->Text_ch);//ֽ��
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_MediaWidth)*8-baseX, LCD_MENUITEM_HEIGHT, MainInfo_MediaWidth);//ֽ��ֵ
				LCD_DrawMixedText(baseX, LCD_MENUITEM_HEIGHT*2, (Menu_List->ChildItems+4)->Text_ch);//ԭ��
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintOrigin)*8-baseX, LCD_MENUITEM_HEIGHT*2, MainInfo_PrintOrigin);//ԭ��ֵ
			#if defined(LCD_MODULE_128_64_ST5668A)
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*3, "����");//����
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-baseX, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
			#else
				LCD_DrawText(CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, "����");//����
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
#endif
#endif
				// Draw_PrintQuality();
				break;			
			case E_ST_UPDATING:
				LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
				LCD_DrawMixedText(baseX, 0, (Menu_List->ChildItems+0)->Text_ch);//״̬
				LCD_DrawMixedText(LCD_PIXEL_WIDTH/MainScreen_ColCount-baseX, 0, (unsigned short *)MainInfo_percent);//�ٷֱ�
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT, MainInfo_ManufactureName);//ManufactureName
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*2, MainInfo_PrinterName);//PrinterName
				break;
			case E_ST_PRINT:
			case E_ST_PAUSE:
				if(!strncmp(MainInfo_percent, Last_MainInfo_percent, strlen(MainInfo_percent))&& \
					!strncmp(MainInfo_PassNum, Last_MainInfo_PassNum, strlen(MainInfo_PassNum))&& \
						!strncmp(MainInfo_Resolution, Last_MainInfo_Resolution, strlen(MainInfo_Resolution))&& \
							!strncmp(MainInfo_Step, Last_MainInfo_Step, strlen(MainInfo_Step))&& \
								(Be_Refresh == FALSE))
					
				{
					break;
				}
				else
				{
					if(!strncmp(MainInfo_PassNum, Last_MainInfo_PassNum, strlen(MainInfo_PassNum))&& \
						!strncmp(MainInfo_Resolution, Last_MainInfo_Resolution, strlen(MainInfo_Resolution))&& \
							!strncmp(MainInfo_Step, Last_MainInfo_Step, strlen(MainInfo_Step))&& \
								(LastDisMode_Main == True) && ((Last_Status ==E_ST_PRINT)||(Last_Status ==E_ST_PAUSE)))			{
								LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, 16, 0);
								LCD_DrawMixedText(baseX, 0, (Menu_List->ChildItems+0)->Text_ch);//״̬
								if(CurrentStatus == E_ST_PRINT)
									LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_percent)*8-baseX, 0, MainInfo_percent);//�ٷֱ�
#ifdef MICOLOR_AUTOFUCTION				 
								else if(!Media_Lack&&!Cover_up&&!Media_Not_Fixed)
#else
								else
#endif
									LCD_DrawText(LCD_PIXEL_WIDTH-strlen(Last_MainInfo_percent)*8-baseX, 0, Last_MainInfo_percent);//�ٷֱ�
								if((CurrentStatus == E_ST_PRINT)&&(Last_Status == E_ST_PAUSE))
									Draw_Print_QualityStep();
								strcpy(Last_MainInfo_PassNum, MainInfo_PassNum);
								strcpy(Last_MainInfo_Resolution, MainInfo_Resolution);
								strcpy(Last_MainInfo_percent, MainInfo_percent);
								strcpy(Last_MainInfo_Step, MainInfo_Step);
								break;
							}	
				}
				LCD_FillRectangle(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HIGH, 0);
				LCD_DrawMixedText(baseX, 0, (Menu_List->ChildItems+0)->Text_ch);//״̬
				if(CurrentStatus == E_ST_PRINT)
					LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_percent)*8-baseX, 0, MainInfo_percent);//�ٷֱ�
#ifdef MICOLOR_AUTOFUCTION				 
				else if(!Media_Lack&&!Cover_up&&!Media_Not_Fixed)
#else
				else
#endif
					LCD_DrawText(LCD_PIXEL_WIDTH-strlen(Last_MainInfo_percent)*8-baseX, 0, Last_MainInfo_percent);//�ٷֱ�
				LCD_DrawMixedText(baseX, LCD_MENUITEM_HEIGHT, (Menu_List->ChildItems+5)->Text_ch);//pass��
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PassNum)*8-baseX, LCD_MENUITEM_HEIGHT, MainInfo_PassNum);//pass��ֵ
				LCD_DrawMixedText(baseX, LCD_MENUITEM_HEIGHT*2, (Menu_List->ChildItems+6)->Text_ch);//�ֱ���
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_Resolution)*8-baseX, LCD_MENUITEM_HEIGHT*2, MainInfo_Resolution);//�ֱ���ֵ
			#if defined(LCD_MODULE_128_64_ST5668A)
				LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*3, "����");//����
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-baseX, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
			#else
				LCD_DrawText(CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, "����");//����
				LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH, LCD_MENUITEM_HEIGHT*3, MainInfo_PrintQuality);//�ֱ���ֵ
			#endif
				strcpy(Last_MainInfo_PassNum, MainInfo_PassNum);
				strcpy(Last_MainInfo_Resolution, MainInfo_Resolution);
				strcpy(Last_MainInfo_percent, MainInfo_percent);
				strcpy(Last_MainInfo_Step, MainInfo_Step);
				//Draw_PrintQuality();
				if(CurrentStatus == E_ST_PRINT)
					Draw_Print_QualityStep();
				break;			
			default:
				break;
			}			
		}
	}
	Last_Status = CurrentStatus;
	LastDisMode_Main = TRUE;
}
//=====================================================================//
//������void Initial_Menu(UINT** Menu_List)
//������ˢ�������˵���ʾ����
//������Menu_List    �˵���Դ����ָ��
//���أ�
//ע�⣺��
//=====================================================================//
void Initial_Menu(struct MenuItem *Menu_List)
{
	//UCHAR *Menu_Config;
	First_Index_old=0xff;
	y_Index_old = 0xff;
	//Menu_Config = (UCHAR *)(*Menu_List);
	//Language = Menu_List->Lang;//*(Menu_Config+1);
	//Font_String = *(Menu_Config+2);
	//Y_WIDTH_MENU = Menu_List->Height;
	//X_SPACE_FRONT = Menu_List->OffsetX;
	Dis_Menu_Num_Page = GetMLiNum_Page();
	//UpDate_Menu(0,0,Menu_List);
}
//=====================================================================//
//������unsigned int GetMLNum(unsigned int* Menu_List)
//��������ȡ��ǰ�˵��ڵĿɼ��Ӳ˵�����
//������ Menu_List    �˵���Դ����ָ��
//���أ��˵������
//ע�⣺��
//=====================================================================//
UCHAR GetMLNum(struct MenuItem *Menu_List)
{
	UCHAR uiTemp = 0;
	for(int i = 0;i< Menu_List->ItemCount;i++)
		if((Menu_List->ChildItems+i)->Visible)
			uiTemp++;
	return uiTemp;
}
//=====================================================================//
//������unsigned int GetMLiNum_Page(unsigned int* Menu_List)
//��������ȡ�˵���Դ��һ��������ʾ�Ĳ˵����������
//������
//���أ��˵������
//ע�⣺��
//=====================================================================//
UCHAR GetMLiNum_Page()
{
	UCHAR uiTemp;
	//UCHAR *Menu_Config;
	//Menu_Config = (UCHAR *)(Menu_List[0]);
	uiTemp = LCD_MENUITEM_HEIGHT;
	uiTemp = (LCD_PIXEL_HIGH)/uiTemp;			//
	return uiTemp;
}
#endif
