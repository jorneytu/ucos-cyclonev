#ifndef	__MENU_GUI_h__
#define	__MENU_GUI_h__
//	write your header here
#include "LCD_Main.h"

typedef unsigned int UINT;
typedef unsigned char UCHAR;
typedef char CHAR;

#define LCD_MENUITEM_HEIGHT (16)
#define EDITOR_MAX_LEN  (8)
#define INDICATE_AREAS_WIDTH (8)
#define CHECKBOX_WIDTH (8)
#define UNIT_AREAS_WIDTH (16)
#if defined(LCD_MODULE_128_64_ST5668A)
	#define MENU_NAME_LEN (16)
#else
	#define MENU_NAME_LEN (21)
#endif

extern UCHAR Dis_Menu_Num_Page;
extern UCHAR UILanguage;
extern UCHAR DistanceUnit; //0:inch, 1:CM.
extern UCHAR TimeUnit;  //0:second.
extern enum LCD_DisModeEnum CurrentDisMode;//��ǰ��ʾģʽ
extern enum StatusTypeEnum CurrentStatus; //��ǰ״̬
extern enum UnitType CurrentLengthUnit;  //��ǰ���ȵ�λ
extern enum UnitType CurrentTimeUnit;      //��ǰʱ�䵥λ
extern enum UnitType CurrentFreUnit;       //��ǰƵ�ʵ�λ

extern UCHAR MainScreen_ColCount;

extern char Dis_Inf[];
extern char *Dis_Inf_Case;

//��ʾģʽ
enum LCD_DisModeEnum
{
	MainScreen,
	Menu,
	Edit,
	Reserved
};

//�˵�������
enum MenuItemType
{
	normal,         //��ͨ�˵�
	checkbox,       //��ѡ��
	radiocheckbox,  //��ѡ��
	editor,         //�༭��
	pwdEditor		//���������
};

//�˵����ֵ����
enum ItemValueType
{
	tNone,
	tFloat,         //��������
	tInt,       //����
	tShort,		//������
	tByte  //�ֽ�
};

////�˵���״̬
enum MenuItemStatus
{
	normalStatus,   //��ͨ��ʾ״̬
	selected,       //ѡ��״̬
	checked,        //��ѡѡ��״̬
	radiochecked,   //��ѡѡ��״̬
	editting        //�༭״̬
};

////�˵�����
enum Language
{
	chs,   //����
	en     //Ӣ��
};

////�˵�����
enum UnitType
{
	utNone,   //��
	//Length part
	utInch,     //Ӣ��
	utCM,     //����
	//Time part
	utSec,    //��
	utH,		//Сʱ
	//Freq part
	utKHz,    //ǧ����
	utT
};

struct MenuItem
{
	struct MenuItem *Parents; //�����˵�
	int Index;			//index of parents menuitem
	UCHAR LastFirstIndex;  // ���һ����ʾ�ĵ�һ���index
	UCHAR SelectedIndex;//��ǰѡ������ChildItems�е����
	unsigned short *Text_ch;   //�����ı�
	CHAR *Text_en;   //Ӣ���ı�
	//UINT Height;                //�߶�
	//UINT ch_SizeMode;          //���������С
	//UINT en_SizeMode;          //Ӣ�������С
	struct MenuItem *ChildItems;        //�Ӳ˵�
	UCHAR ItemCount;            //�Ӳ˵���
	enum Language Lang;                 //��ʾ����
	enum MenuItemType type;   //�˵�����
	enum MenuItemStatus status;         //��ǰ״̬
	UCHAR DecimalPlaces;		//type = editorʱ,С�����λ��,������0Ϊ����������������Ϊ����
	enum ItemValueType vlaueType;		//type = editorʱ,�˵����ֵ����
	float maxVal;			//type = editorʱ,���ֵ
	float minVal;			//type = editorʱ,��Сֵ
	UCHAR ActiveIndex;		//type = editorʱ,��ǰ���ڱ༭��λ��
	UCHAR selected;			//�Ƿ�ѡ��״̬		
	UCHAR Visible;			//�Ƿ�ɼ�
	UCHAR Value[EDITOR_MAX_LEN];			//type = editorʱ,ֵ
	UIGetFloatFuncExType GetFloatFunc;    //get����
	UISetFloatFuncExType SetFloatFunc;    //Set����
	UIActionFuncExType ActionFunc;      //Action����
	float ActionParameters;       //Action����
	enum UnitType Unit;       //Value�ĵ�λ��
};

//rn struct MenuItem mMainMenu = 0; 
//struct MenuItem MainMenu = 0;

/*struct MenuItemList
{
struct MenuItemInfo *Items;
}*mMainMenu;*/

UCHAR GetMLNum(struct MenuItem *Menu_List);
UCHAR GetMLiNum_Page();
void RefreshScreen(UCHAR First_Index,struct MenuItem *Menu_List,enum LCD_DisModeEnum DisMode);
void DrawMainScreen(enum StatusTypeEnum status,struct MenuItem *Menu_List);
void Initial_Menu(struct MenuItem *Menu_List);

float CallUIGetFuncByType(struct MenuItem *mitem);
float GetValueFormUI(struct MenuItem *mitem);
void SetUIMenuItemValue(struct MenuItem *mitem,float val);
UCHAR CallUISetFuncByType(struct MenuItem *mitem,int index,float val);

void Set_PrintQuality(INT8U index);
void Draw_PrintQuality(void);
#endif
