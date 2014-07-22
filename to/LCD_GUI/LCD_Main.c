#include "status.h"
#include "resources.h"
#include "Menu_GUI.h"
#include "LCD_Main.h"
#include "GUI_LED_Task.h"
#include "stdlib.h"
#include "stdio.h"
#include "global.h"
#include "usb.h"
#include "commpipe.h"
#include "calibration.h"
#include "job.h"
#include "motion.h"
#include "control.h"
#include "Miscellance.h"
#include "uv.h"

extern struct Struct_JobStart job_info;
#ifdef IIC_Key_Board_LCD
extern INT8U Lcd_Cmd_Q[];
extern INT16U Lcd_Cmd_Num;
extern INT8U CLEAN_head_group;
OS_EVENT *MenuSem; //Sem to lock LCD menu operate
//static OS_EVENT *Lcd_Cmd;
extern INT8U IIC_Write_LCD(void);
extern INT8U IIC_Read_LCD(INT8U subaddr, INT8U * data, INT8U count);
extern unsigned char CRC8_Table(unsigned char *p, char counter);
enum LCD_DisModeEnum CurrentDisMode = MainScreen;//��ǰ��ʾģʽ
enum StatusTypeEnum CurrentStatus = E_ST_RDY; //��ǰ״̬
void Init_Lcd_Cmd_Q(void);
enum UnitType CurrentLengthUnit = utCM;  //��ǰ���ȵ�λ
enum UnitType CurrentTimeUnit = utSec;      //��ǰʱ�䵥λ
enum UnitType CurrentFreUnit = utKHz;       //��ǰƵ�ʵ�λ

struct MenuItem *PDisMenuItemsParent = 0;//��ǰ��Ļ��ʾ�˵���ĸ��˵���
struct MenuItem *PMainScreen = 0; //����Ļ��ʾ��Ϣ��Ҳ��MenuItem�ṹ�洢
#ifdef FUNC_WAVE_MAP
struct MenuItem *pMenuStep[8] = {0};	//����(��ȣ��Ĳ˵�,����8��
INT8U menuStepIndex = 0;				//��������ȣ��Ĳ˵�������,��ǰֵ��ʾ����Ĳ���
#endif
//UCHAR PDisMenuItemsParent->LastFirstIndex = 0;//��Ļ��ʾ��һ������
UCHAR bNeedRefresh = 0;
UCHAR MainScreen_ColCount = 2;
INT8U IsAdvancedMode = 0;
//MainInfo field
CHAR MainInfo_MediaWidth[8] = {0};      //value is float *. unit is inch.
CHAR MainInfo_PrintOrigin[8] = {0};     //value is float *. unit is inch.
#ifdef RIPSTAR_FLAT_EX
CHAR MainInfo_MediaHigh[8] = {0};
CHAR MainInfo_MediaLength[8] = {0};
CHAR MainInfo_YOrigin[8] = {0};
CHAR MainInfo_ZOrigin[8] = {0};
#endif
CHAR MainInfo_PassNum[8] = {0};         //value is INT8U *.
CHAR MainInfo_Resolution[8] = {0};      //value is INT16U *.
CHAR MainInfo_PrinterName[16] = {0};     //value is C string.
CHAR MainInfo_ManufactureName[16] = {0}; //value is C string.
CHAR MainInfo_HeadHeightLevel[8] = {0}; //value is INT8U *. the valid value is 1,2,3(high, middle, low).
CHAR MainInfo_QualitySetting[8] = {0};  //value is INT8U *. the valid value is 0,1,2(OFF/type1/type2).
CHAR MainInfo_CleaningStrong[8] = {0};  //value is INT8U *. the valid value is 1,2,3(weak, normal, strong).
CHAR MainInfo_DataReceiving[8] = {0};   //value is INT8U *. the valid value is 0,1(FALSE/TRUE).
CHAR MainInfo_Busy[8] = {0};            //value is INT8U *. the valid value is 0,1(FALSE/TRUE).
CHAR MainInfo_strinfo[16] = {0};
CHAR MainInfo_percent[8] = {0};
CHAR MainInfo_errorcode[8] = {0};
extern struct MenuItem MI_EM_2_ID59_Feed[];
extern struct MenuItem MI_UM_2_ID27_FEEDadjust[];
extern unsigned char MenuStr_UM_4_ID30_Print[];
extern unsigned char MenuStr_UM_4_ID30_Print_EN[];
extern struct MenuItem MI_0_ID00_MenuChilds[];
extern struct MenuItem MI_EM_3_ID236_Spot1Name[];
extern struct MenuItem MI_EM_3_ID236_Spot2Name[];
extern struct MenuItem MI_EM_3_ID236_Spot3Name[];
extern struct MenuItem MI_EM_3_ID236_Spot4Name[];
extern struct MenuItem MI_MICOLOR_EM_1_ID16_SetAutofunction[];
extern struct MenuItem MI_1_ID3FB_Head_Decryption[];
#if defined(LCD_MODULE_128_64_ST5668A)
	INT8U radiocheckbox_offset = 0;
#endif

#if defined( EPSON_BOTTOM_BOARD_V3)||defined( EPSON_BOTTOM_BOARD_V2_1)
extern struct MenuItem MI_EM_1_ID3F4_Heater[];
#endif
#if defined (EPSON_CLEAN_INTEGRATE)||defined (EPSON_CLEAN_INTEGRATE_1) ||defined(EPSON_CLEAN_INTEGRATE_2)||defined(EPSON_CLEAN_INTEGRATE_3)	//ͷ��ϴѡ��
extern struct MenuItem MI_MICOLOR_1_ID28B_HEADCLEANING[];
#else
extern struct MenuItem MI_ALLWIN_1_ID23C_HEADCLEANING[];
#endif
#ifdef MICOLOR_AUTOFUCTION
extern struct MenuItem MI_1_ID0D_OriginAndMediaWidth[];
#elif defined RIPSTAR_FLAT_EX
extern struct MenuItem MI_1_ID0D_OriginAndMediaWidth[];
#else
extern struct MenuItem MI_1_ID0D_OriginAndMediaWidth[];
#endif
extern struct MenuItem MI_UM_1_ID25_ADJUSTMENT[];
extern struct MenuItem MI_EM_1_ID3F3_HeadSwitch[];
#ifdef EPSON_4H
extern struct MenuItem MI_EM_1_ID3F3_Head4Switch[];
#endif
#ifdef MANUFACTURER_DYSS
extern struct MenuItem MI_UM_2_ID27_Adjustsetting[];
#endif
#ifdef RIPSTAR_FLAT_EX
extern struct MenuItem MI_UM_2_ID27_Adjustsetting[];
#endif
#ifdef AUTO_CLEAN_BYTIME
unsigned char MenuStr_1_Auoto_Clean_Time[]="ʱ����";
unsigned char MenuStr_1_Auoto_Clean_Time_EN[]="Time Interval";
#endif
#ifdef FAST_CLEAN
extern unsigned char MenuStrAutoFlashOnOff[];
extern unsigned char MenuStrAutoFlashOnOff_EN[];
#endif
extern struct MenuItem MI_ALLWIN_EM_2_ID283_AutoClean[];
static char *floatToStr(char *str, double src,int decimal);
//========================================================================
// ����: void GetErrorCode_CHS(INT16U errorCode,unsigned short* chsErrorCode)
// ����: ����errorCode ����chsinfo��ֵ
// ����: sour Ҫת�����ִ�
//		 dest ת����������ַ�����ָ��
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
void GetPercent_CHS(char* sour)
{
	//	int len = sour->Length;
	//	unsigned short dest_temp[len] ={0};
	//	dest = dest_temp;
	for(int i=0;i<3;i++)
	{
		MenuStr_2_ID3FF_Percent[i] =sour[i];
		if(sour[i] == 0)
			break;
	}
	
}
#ifdef MICOLOR_AUTOFUCTION
extern INT8U Media_Lack;
extern INT8U Cover_up;
extern INT8U Media_Not_Fixed;
#endif
//========================================================================
// ����: void GetErrorCode_CHS(INT16U errorCode,unsigned short* chsErrorCode)
// ����: ����errorCode ����chsinfo��ֵ
// ����: status ״̬ö��ֵ
//		 chsstatus ״̬�����ִ�
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
void GetStatus_CHS(enum StatusTypeEnum status,unsigned short** chsstatus)
{
	switch(status)
	{		
	case E_ST_SVC:
		*chsstatus = CHS_STATUS_SVC;
		break;
	case E_ST_FTA:
		*chsstatus = CHS_STATUS_FTA;
		break;
	case E_ST_ERR:
		*chsstatus = CHS_STATUS_ERR;
		break;
	case E_ST_ERR_AUTO:
		*chsstatus = CHS_STATUS_ERR_AUTO;
		break;
	case E_ST_WAR:
		*chsstatus = CHS_STATUS_WAR;
		break;
	case E_ST_INI:
		*chsstatus = CHS_STATUS_INI;
		break;
	case E_ST_RDY:
		*chsstatus = CHS_STATUS_RDY;
		break;
#ifdef FUNC_MAINTAIN
	case E_ST_MAINTAIN:
		if(bStatus_Maintain & 0x01)
			*chsstatus = CHS_STATUS_MAINTAIN;
		else
			*chsstatus = CHS_STATUS_RDY;
		break;
#endif
	case E_ST_MOVING:
		*chsstatus = CHS_STATUS_MOVING;
		break;
	case E_ST_PRINT:
		*chsstatus = CHS_STATUS_PRINT;
		break;
	case E_ST_PAUSE:
		*chsstatus = CHS_STATUS_PAUSE;
#ifdef MICOLOR_AUTOFUCTION
		if(Media_Lack)
			*chsstatus = CHS_STATUS_PAUSE_3;
		if(Cover_up)
			*chsstatus = CHS_STATUS_PAUSE_2;
		if(Media_Not_Fixed)
			*chsstatus = CHS_STATUS_PAUSE_1;
#endif
		break;
	case E_ST_CLEANING:
		*chsstatus = CHS_STATUS_CLEANING;
		break;
	case E_ST_CANCELING:
		*chsstatus = CHS_STATUS_CANCELING;
		break;
	case E_ST_UPDATING:
		*chsstatus = CHS_STATUS_UPDATING;
		break;
	default:
		break;
	}
}
void GetStatus_EN(enum StatusTypeEnum status,CHAR** ENstatus)
{
	switch(status)
	{		
	case E_ST_SVC:
		*ENstatus = "SVC";
		break;
	case E_ST_FTA:
		*ENstatus = "FTA";
		break;
	case E_ST_ERR:
		*ENstatus = "Error";
		break;
	case E_ST_ERR_AUTO:
		*ENstatus = "ERR_AUTO";
		break;
	case E_ST_WAR:
		*ENstatus = "Warning";
		break;
	case E_ST_INI:
		*ENstatus = "Init";
		break;
	case E_ST_RDY:
		*ENstatus = "Ready";
		break;
#ifdef FUNC_MAINTAIN
	case E_ST_MAINTAIN:
		if(bStatus_Maintain & 0x01)
			*ENstatus = "Maintain";
		else
			*ENstatus = "Ready";
		break;
#endif
	case E_ST_MOVING:
		*ENstatus = "Moving";
		break;
	case E_ST_PRINT:
		*ENstatus = "Printing";
		break;
	case E_ST_PAUSE:
		*ENstatus = "Pause";
#ifdef MICOLOR_AUTOFUCTION
		if(Media_Lack)
			*ENstatus = "Pause(Media Lack)";
		if(Cover_up)
			*ENstatus = "Pause(Cover Up)";
		if(Media_Not_Fixed)
			*ENstatus = "Pause(Media Not Fixed)";
#endif		
		break;
	case E_ST_CLEANING:
		*ENstatus = "Cleaning";
		break;
	case E_ST_UPDATING:
		*ENstatus = "Updating";
		break;
	case E_ST_CANCELING:
		*ENstatus = "Canceling";
		break;        
	default:
		*ENstatus = "Unkown";
		break;
	}
}

//========================================================================
// ����: void GetErrorCode_CHS(INT16U errorCode,unsigned short* chsErrorCode)
// ����: ����errorCodeȡ��errorCode�������ִ�
// ����: errorCode �����
//		 chsErrorCode ȡ�����Ĵ����
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
void GetErrorCode_CHS(INT16U errorCode)
{
	char strerrorcode[12] = {0};	
	sprintf(strerrorcode, "%#4.2X",errorCode);
	for(int i = 0;i< 10; i++)
		ErrorCodeCHS[i] = (unsigned short)(strerrorcode[i]);
}
//========================================================================
// ����: void GetErrorInfo_CHS(INT16U errorCode,unsigned short* chsinfo)
// ����: ����errorCode ����chsinfo��ֵ
// ����: errorCode �����
//		 chsinfo ȡ�����Ĵ�����Ϣ
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
void GetErrorInfo_CHS(INT16U errorCode,unsigned short** chsinfo)
{
	INT32U Realcode = 0;
	if(CurrentStatus != E_ST_SVC
	   &&CurrentStatus != E_ST_FTA
		   &&CurrentStatus != E_ST_ERR
			   &&CurrentStatus != E_ST_ERR_AUTO
				   &&CurrentStatus != E_ST_WAR
					   &&CurrentStatus != E_ST_INI
						   )
	{
		*chsinfo = 0;
		return;
	}
	switch(CurrentStatus)
	{
	case E_ST_SVC:
		Realcode = STATUS_SVC +errorCode;
		break;
	case E_ST_FTA:
		Realcode = STATUS_FTA +errorCode;
		break;
	case E_ST_ERR:
		Realcode = STATUS_ERR +errorCode;
		break;
	case E_ST_INI:
		Realcode = STATUS_INI +errorCode;
		break;
	case E_ST_ERR_AUTO:
		Realcode = STATUS_ERR_AUTO +errorCode;
		break;
	case E_ST_WAR:							
		Realcode = STATUS_WAR +errorCode;
		break;
	}
	switch(Realcode)
	{
	case STATUS_SVC_SX2://��USB chip�з������.
		*chsinfo = CHS_SVC_SX2;
		break;
	case STATUS_SVC_FPGA0://Service Call: chip1.
		*chsinfo = CHS_SVC_FPGA0;
		break;
	case STATUS_SVC_FPGA1://Service Call: chip2.
		*chsinfo = CHS_SVC_FPGA1;
		break;
	case STATUS_SVC_FPGA2://Service Call: chip3.
		*chsinfo = CHS_SVC_FPGA2;
		break;
	case STATUS_SVC_FPGA3://Service Call: chip4
		*chsinfo = CHS_SVC_FPGA3;
		break;
	case STATUS_SVC_UPDATE_FAIL://Service Call: chip5.
		*chsinfo = CHS_SVC_UPDATE_FAIL;
		break;
	case STATUS_SVC_BYHX_DATA://Service Call: 6.
		*chsinfo = CHS_SVC_BYHX_DATA;
		break;
	case STATUS_SVC_EEPROM_CHK://BYHX_TOOL check EEPROM û��ͨ����
		*chsinfo = CHS_SVC_EEPROM_CHK;
		break;
	case STATUS_SVC_SDRAM_CHECK://SDRAM ��Checkû��ͨ��
		*chsinfo = CHS_SVC_SDRAM_CHECK;
		break;
	case STATUS_SVC_FLASH://�޷���Falsh��ȡFPGA.
		*chsinfo = CHS_SVC_FLASH;
		break;
	case STATUS_SVC_SDRAM_NOMATCH://SDRAM ̫С������֧�ֵ�ǰ�����á�
		*chsinfo = CHS_SVC_SDRAM_NOMATCH;
		break;
	case STATUS_SVC_READBOARDID_FAIL://���������
		*chsinfo = CHS_SVC_READBOARDID_FAIL;
		break;
	case STATUS_SVC_ARM_MOTION://���������
		*chsinfo = CHS_SVC_MOTION_FAIL;
		break;
	case STATUS_SVC_HEADBOARD_INIT_FAIL://���������
		*chsinfo = CHS_SVC_HEADBOARD_FAIL;
		break;
	case STATUS_SVC_POWER_OFF_MODE://���������
		*chsinfo = CHS_SVC_POWEROFF_MODE;
		break;		
	case STATUS_FTA_SX2RESET://USB chip�쳣����
		*chsinfo = CHS_FTA_SX2RESET;
		break;
	case STATUS_FTA_INTERNAL_WRONGHEADER://�ڲ����� 1.
		*chsinfo = CHS_FTA_INTERNAL_WRONGHEADER;
		break;
	case STATUS_FTA_INTERNAL_WRONGHEADERSIZE://�ڲ����� 2.
		*chsinfo = CHS_FTA_INTERNAL_WRONGHEADERSIZE;
		break;
	case STATUS_FTA_INTERNAL_JOBSTARTHEADER://�ڲ����� 3.
		*chsinfo = CHS_FTA_INTERNAL_JOBSTARTHEADER;
		break;
	case STATUS_FTA_INTERNAL_BANDDATASIZE://�ڲ����� 4.
		*chsinfo = CHS_FTA_INTERNAL_BANDDATASIZE;
		break;
	case STATUS_FTA_INTERNAL_WRONGFORMAT://�ڲ����� 5.
		*chsinfo = CHS_FTA_INTERNAL_WRONGFORMAT;
		break;
	case STATUS_FTA_INTERNAL_DMA0WORKING://�ڲ����� 6.
		*chsinfo = CHS_FTA_INTERNAL_DMA0WORKING;
		break;
	case STATUS_FTA_INTERNAL_PRINTPOINT://�ڲ����� 7.
		*chsinfo = CHS_FTA_INTERNAL_PRINTPOINT;
		break;
	case STATUS_FTA_INTERNAL_OLIMIT://�ڲ����� 8.
		*chsinfo = CHS_FTA_INTERNAL_OLIMIT;
		break;
	case STATUS_FTA_INTERNAL_OPPLIMIT://�ڲ����� 9.
		*chsinfo = CHS_FTA_INTERNAL_OPPLIMIT;
		break;
	case STATUS_FTA_DSPINITS1://�˶�step 1.
		*chsinfo = CHS_FTA_DSPINITS1;
		break;
	case STATUS_FTA_DSPINITS2://�˶�step 2.
		*chsinfo = CHS_FTA_DSPINITS2;
		break;
	case STATUS_FTA_HEADINITS1://ͷ��step1.
		*chsinfo = CHS_FTA_HEADINITS1;
		break;
	case STATUS_FTA_HEADINITS2://ͷ��step2.
		*chsinfo = CHS_FTA_HEADINITS2;
		break;
	case STATUS_FTA_HEADTOMAINROAD://LVDS����.
		*chsinfo = CHS_FTA_HEADTOMAINROAD;
		break;
	case STATUS_FTA_INTERNAL_BANDDIRECTION://Band�����еķ���ֵ��������
		*chsinfo = CHS_FTA_INTERNAL_BANDDIRECTION;
		break;
	case STATUS_FTA_DSPUPDATE_FAIL://DSP����ʧ��.
		*chsinfo = CHS_FTA_DSPUPDATE_FAIL;
		break;
	case STATUS_FTA_EEPROM_READ://EEPROM��ȡʧ��	
		*chsinfo = CHS_FTA_EEPROM_READ;
		break;
	case STATUS_FTA_EEPROM_WRITE://EEPROMд��ʧ��
		*chsinfo = CHS_FTA_EEPROM_WRITE;
		break;
	case STATUS_FTA_FACTORY_DATA://���ӳ���û�г�ʼ��.
		*chsinfo = CHS_FTA_FACTORY_DATA;
		break;
	case STATUS_FTA_HEADBOARD_RESET://ͷ�帴λ.
		*chsinfo = CHS_FTA_HEADBOARD_RESET;
		break;
	case STATUS_FTA_SPECTRAHVBINITS1://Spectra��ѹ���޷��ڵ�1����ʼ��.
		*chsinfo = CHS_FTA_SPECTRAHVBINITS1;
		break;
	case STATUS_FTA_PRINTHEAD_NOTMATCH://ͷ����������ݲ�ƥ��,�����ó������ݻ��߸���ͷ��.
		*chsinfo = CHS_FTA_PRINTHEAD_NOTMATCH;
		break;
	case STATUS_FTA_MANUFACTURERID_NOTMATCH://���ӵĳ���ID��ƥ��,�������̼�.
		*chsinfo = CHS_FTA_MANUFACTURERID_NOTMATCH;
		break;
	case STATUS_FTA_LIMITEDTIME_RUNOUT://���ش���: ������ʱʱ�䣬�������µ�����.
		*chsinfo = CHS_FTA_LIMITEDTIME_RUNOUT;
		break;
	case STATUS_FTA_INTERNAL_SW1://�ڲ�����,�հ�Band��Y�����Ϊ��.
		*chsinfo = CHS_FTA_INTERNAL_SW1;
		break;
	case STATUS_FTA_USB1_USB1CONNECT://USB1.1����.
		*chsinfo = CHS_FTA_USB1_USB1CONNECT;
		break;
	case STATUS_FTA_UILANGUAGE_NOT_MATCH://UIʹ�õ�������Ȩ�޲����� �������������Ի���������������
		*chsinfo = CHS_FTA_UILANGUAGE_NOT_MATCH;
		break;
	case STATUS_FTA_INTERNAL_WRONGPINCONF://PINCONFд��FPGA����
		*chsinfo = CHS_FTA_INTERNAL_WRONGPINCONF;
		break;
	case STATUS_FTA_FACTORY_COLORNUM_WRONG://����������д�����ɫ������.
		*chsinfo = CHS_FTA_FACTORY_COLORNUM_WRONG;
		break;
	case STATUS_FTA_HB_EEPROM_WRT_ERR://ͷ���EEPROMд��ʧ��
		*chsinfo = CHS_FTA_HB_EEPROM_WRT_ERR;
		break;
	case STATUS_FTA_HB_OVERHEAT://��ͷ���ȣ����м��ȱ�ǿ�йرա�
		*chsinfo = CHS_FTA_HB_OVERHEAT;
		break;
	case STATUS_FTA_SHAKEHAND_ERR://���������߰汾����û��ͨ������Э�顣
		*chsinfo = CHS_FTA_SHAKEHAND_ERR;
		break;
	case STATUS_FTA_SWVERSION_ERR://�̼�Ҫ�����������汾���汾����
		*chsinfo = CHS_FTA_SWVERSION_ERR;
		break;
	case STATUS_FTA_NOT_SUPPORT_2C_SHARE_1H://��ǰϵͳ���ò�֧��һͷ��ɫ��
		*chsinfo = CHS_FTA_NOT_SUPPORT_2C_SHARE_1H;
		break;
	case STATUS_FTA_LIMITEDINK_RUNOUT://����īˮ�������ƣ��������������
		*chsinfo = CHS_FTA_LIMITEDINK_RUNOUT;
		break;
	case STATUS_FTA_SWVERSION_ERR_INK_PWD://�̼�Ҫ������汾֧��īˮ���룬�汾����
		*chsinfo = CHS_FTA_SWVERSION_ERR_INK_PWD;
		break;
	case STATUS_FTA_EPSON_HEAD_BAD://������ID����
		*chsinfo = CHS_FTA_EPSON_HEAD_BAD;
		break;
	case STATUS_FTA_EPSON_HEAD_FPGA_ERR://ͷ��FPGA����.
		*chsinfo = CHS_FTA_EPSON_HEAD_FPGA_ERR;
		break;
	case STATUS_FTA_SECURITY_CHIP_ERR://д�������.
		*chsinfo = CHS_FTA_SECURITY_CHIP_ERR;
		break;
	case STATUS_FTA_CALIBRATION_DATA://������ʼ�����ó���
		*chsinfo = CHS_FTA_CALIBRATION_DATA;
		break;
	case STATUS_FTA_PRINT_DATA_ERROR: //��ӡ���ݴ�������ʧ
		*chsinfo = CHS_FTA_PRINT_DATA_ERROR;
		break;		
	case STATUS_FTA_FACTORY_DATA_ERROR://FACTORY_DATA ���ݴ���
		*chsinfo = CHS_FTA_FACTORY_DATA_ERROR;
		break;	
	case STATUS_FTA_WASTE_INK_FULL://��ī���
		*chsinfo = CHS_FTA_WASTE_INK_FULL;
		break;
		//#if defined(EPSON_BOTTOM_BOARD_V3)  ||defined (EPSON_BOTTOM_BOARD_V2_1)
#if 1
	case STATUS_FTA + SciError_Command:
		*chsinfo =(unsigned short*)"���������";
		break;
	case STATUS_FTA + SciError_Parameter:
		*chsinfo =(unsigned short*)"����Ĳ���";
		break;
	case STATUS_FTA + SciError_MoveAgain:
		*chsinfo =(unsigned short*)"�����д��� �Ѿ��˶�,�ַ��˶�����";
		break;
	case STATUS_FTA + SciError_TxTimeOut:
		*chsinfo =(unsigned short*)"���ͳ�ʱ";
		break;	
	case STATUS_FTA + SciError_FormatErr:
		*chsinfo =(unsigned short*)"У��ʹ���";
		break;	
	case STATUS_FTA + SciError_Encoder:
		*chsinfo =(unsigned short*)"��դ����";
		break;	
	case STATUS_FTA + SciError_MeasureSensor:
		*chsinfo =(unsigned short*)"ֽ����������";
		break;		
	case STATUS_FTA + SciError_NoPaper:
		*chsinfo =(unsigned short*)"û�н���";
		break;	
	case STATUS_FTA + SciError_PaperJamX:
		*chsinfo =(unsigned short*)"X���˶�����";
		break;
	case STATUS_FTA + SciError_PaperJamY:
		*chsinfo =(unsigned short*)"Y���˶�����";
		break;
	case STATUS_FTA + SciError_IndexNoMatch:
		*chsinfo =(unsigned short*)"��������";
		break;	
	case STATUS_FTA + SciError_LimitSensor:
		*chsinfo =(unsigned short*)"�Ӵ���λ������";
		break;	
	case STATUS_FTA + SciError_StepEncoder:
		*chsinfo =(unsigned short*)"û�з��ֲ���������";
		break;		
	case STATUS_FTA + SciError_ReadEEPROM:
		*chsinfo =(unsigned short*)"�� EEPROM ����";
		break;	
	case STATUS_FTA + SciError_WriteEEPROM:
		*chsinfo =(unsigned short*)"д EEPROM ����";
		break;
	case STATUS_FTA + SciError_WriteEEPROMTwice:
		*chsinfo =(unsigned short*)"дEEPROM  2 ��";
		break;	
	case STATUS_FTA + SciError_TimeOver:
		*chsinfo =(unsigned short*)"���Ƶ�ʱ���Ҫ�ù���";
		break;
	case STATUS_FTA + SciError_TimeWarning:
		*chsinfo =(unsigned short*)"�����Ƶ�ʱ�仹��50��Сʱ";
		break;
	case STATUS_FTA + SciError_Lang:
		*chsinfo =(unsigned short*)"���Ժ����ƵĲ�ƥ��";
		break;	
	case STATUS_FTA + SciError_IllegalContent:
		*chsinfo =(unsigned short*)"�����EEPROM �����ݣ�EEPROM ����û�����";
		break;	
	case STATUS_FTA + SciError_IllegalPwd:
		*chsinfo =(unsigned short*)"���������";
		break;	
	case STATUS_FTA + SciError_SwDogEey:
		*chsinfo =(unsigned short*)"���û��ʹ�ü��ܹ�";
		break;	
	case STATUS_FTA + SciError_SensorPause:
		*chsinfo =(unsigned short*)"�Ӵ���λ������";
		break;		
	case STATUS_FTA + SciError_OverCurrent_Protect:
		*chsinfo =(unsigned short*)"����������Ƿѹ����";
		break;		
	case STATUS_FTA + SciError_OverTemp_Protect:
		*chsinfo =(unsigned short*)"�¶ȹ��߱��� ";
		break;	
	case STATUS_FTA + SciError_InternalErr_1:
		*chsinfo =(unsigned short*)"�˶��ڲ�����1";
		break;		
	case STATUS_FTA + SciError_InternalErr_2:
		*chsinfo =(unsigned short*)"�˶��ڲ�����2";
		break;	
#endif
	case STATUS_ERR_EP0OVERUN_SETUPDATA://EP0������
		*chsinfo = CHS_ERR_EP0OVERUN_SETUPDATA;
		break;
	case STATUS_ERR_UART1_TXTIMEOUT://ͷ��COM��ʱ.
		*chsinfo = CHS_ERR_UART1_TXTIMEOUT;
		break;
	case STATUS_ERR_UART2_TXTIMEOUT://�˶�COM��ʱ.
		*chsinfo = CHS_ERR_UART2_TXTIMEOUT;
		break;
	case STATUS_ERR_INTERNAL_PRINTDATA://��ӡ���ݺ͵��Ƶ�ʲ�ƥ��.
		*chsinfo = CHS_ERR_INTERNAL_PRINTDATA;
		break;
	case STATUS_ERR_FPGA_LESSDATA://��ӡ����С�ڵ��Ƶ��
		*chsinfo = CHS_ERR_FPGA_LESSDATA;
		break;
	case STATUS_ERR_FPGA_ULTRADATA://��ӡ���ݳ������Ƶ��.
		*chsinfo = CHS_ERR_FPGA_ULTRADATA;
		break;
	case STATUS_ERR_FPGA_WRONGSTATUS://��ӡ�����ݺͿ�������ƥ��.
		*chsinfo = CHS_ERR_FPGA_WRONGCHS;
		break;
	case STATUS_ERR_UV_CTR_WRONGSTATUS://�ڲ�״̬.
		*chsinfo = CHS_ERR_UV_CTR_WRONGCHS;
		break;
	case STATUS_ERR_FPGA_WRONGCOMMAND://FPGA �յ����������
		*chsinfo = CHS_ERR_FPGA_WRONGCOMMAND;
		break;
	case STATUS_ERR_MOTION_SPEED_BAD://�˶��ٶ�̫��򲻾��ȣ����ݻ��ڳ��飬ȴ�е������
		*chsinfo = CHS_ERR_MOTION_SPEED_BAD;
		break;
	case STATUS_ERR_INTERNAL_MOVING_TIMEOUT://�˶������30���û���յ��˶��������
		*chsinfo = CHS_ERR_INTERNAL_MOVING_TIMEOUT;
		break;
	case STATUS_ERR_INTERNAL_WRONGAUTOCLEAN://�����AUTOCLEAN����.
		*chsinfo = CHS_ERR_INTERNAL_WRONGAUTOCLEAN;
		break;
	case STATUS_ERR_INTERNAL_WRONGBANDINFO://�����AUTOCLEAN����.
		*chsinfo = CHS_ERR_INTERNAL_WRONGBANDINFO;
		break;
	case STATUS_ERR_INTERNAL_DEBUG1://����״̬1
		*chsinfo = CHS_ERR_INTERNAL_DEBUG1;
		break;
	case STATUS_ERR_INTERNAL_DEBUG2://����״̬2
		*chsinfo = CHS_ERR_INTERNAL_DEBUG2;
		break;
	case STATUS_INI_ARM://���ڳ�ʼ��ARM.
		*chsinfo = CHS_INI_ARM;
		break;
	case STATUS_INI_SX2://���ڳ�ʼ��USB
		*chsinfo = CHS_INI_SX2;
		break;
	case STATUS_INI_FPGA://���ڳ�ʼ��FPGA
		*chsinfo = CHS_INI_FPGA;
		break;
	case STATUS_INI_DSP://���ڳ�ʼ��DSP.
		*chsinfo = CHS_INI_DSP;
		break;
	case STATUS_INI_HEADBOARD://���ڳ�ʼ��ͷ��
		*chsinfo = CHS_INI_HEADBOARD;
		break;
	case STATUS_INI_HVB://��װ Spectra ��ѹ��.
		*chsinfo = CHS_INI_HVB;
		break;
	case STATUS_WAR_UNKNOWNHEADERTYPE://��֪���ľ���
		*chsinfo = CHS_WAR_UNKNOWNHEADERTYPE;
		break;
	case STATUS_WAR_EP0OVERUN_REQUEST_IGNORE://EP0���.
		*chsinfo = CHS_WAR_EP0OVERUN_REQUEST_IGNORE;
		break;
	case STATUS_WAR_PUMP_CYAN://��ɫ���ڱ�ī.
		*chsinfo = CHS_WAR_PUMP_CYAN;
		break;
	case STATUS_WAR_PUMP_MAGENTA://Ʒɫ���ڱ�ī.
		*chsinfo = CHS_WAR_PUMP_MAGENTA;
		break;
	case STATUS_WAR_PUMP_YELLOW://��ɫ���ڱ�ī.
		*chsinfo = CHS_WAR_PUMP_YELLOW;
		break;
	case STATUS_WAR_PUMP_BLACK://��ɫ���ڱ�ī.
		*chsinfo = CHS_WAR_PUMP_BLACK;
		break;
	case STATUS_WAR_PUMP_LIGHTCYAN://ǳ��ɫ���ڱ�ī.
		*chsinfo = CHS_WAR_PUMP_LIGHTCYAN;
		break;
	case STATUS_WAR_PUMP_LIGHTMAGENTA://ǳƷɫ���ڱ�ī.
		*chsinfo = CHS_WAR_PUMP_LIGHTMAGENTA;
		break;
	case STATUS_WAR_TIME_PASSWORD_WRONGINPUT://������ʱ������󣬺��к��зǷ��ַ�;
		*chsinfo = CHS_WAR_TIME_PASSWORD_WRONGINPUT;
		break;
	case STATUS_WAR_TIME_PASSWORD_WRONG://����һ���Ϸ���ʱ����;
		*chsinfo = CHS_WAR_TIME_PASSWORD_WRONG;
		break;
	case STATUS_WAR_TIME_PASSWORD_MANUFACTURERIDNOTMATCH://��ʱ����ͳ��̲�ƥ��
		*chsinfo = CHS_WAR_TIME_PASSWORD_MANUFACTURERIDNOTMATCH;
		break;
	case STATUS_WAR_TIME_PASSWORD_BOARDIDNOTMATCH://��ʱ����Ͱ��Ӳ�ƥ��
		*chsinfo = CHS_WAR_TIME_PASSWORD_BOARDIDNOTMATCH;
		break;
	case STATUS_WAR_LIMITEDTIME_FIRST://��һ�ξ���:����100��Сʱ�ͳ�����ʱ��, ���򳧼���ȡ����.
		*chsinfo = CHS_WAR_LIMITEDTIME_FIRST;
		break;
	case STATUS_WAR_LIMITEDTIME_SECOND://�ڶ��ξ���: ����50��Сʱ�ͳ�����ʱ��,���򳧼���ȡ����.
		*chsinfo = CHS_WAR_LIMITEDTIME_SECOND;
		break;
	case STATUS_WAR_LIMITEDTIME_LAST://���һ�ξ���: ����1��Сʱ�ͳ�����ʱ��ֹͣ��ӡ, �������򳧼���ȡ����.
		*chsinfo = CHS_WAR_LIMITEDTIME_LAST;
		break;
	case STATUS_WAR_OPTION_PASSWORD_WRONGINPUT://����ѡ��������󣬺��з�0~F��ֵ
		*chsinfo = CHS_WAR_OPTION_PASSWORD_WRONGINPUT;
		break;
	case STATUS_WAR_OPTION_PASSWORD_WRONG://����һ���Ϸ�ѡ������
		*chsinfo = CHS_WAR_OPTION_PASSWORD_WRONG;
		break;
	case STATUS_WAR_OPTION_PASSWORD_MANUFACTURERIDNOTMATCH://ѡ������ͳ��̲�ƥ��
		*chsinfo = CHS_WAR_OPTION_PASSWORD_MANUFACTURERIDNOTMATCH;
		break;
	case STATUS_WAR_OPTION_PASSWORD_BOARDIDNOTMATCH://ѡ������Ͱ��Ӳ�ƥ��
		*chsinfo = CHS_WAR_OPTION_PASSWORD_BOARDIDNOTMATCH;
		break;
	case STATUS_WAR_PUMP_PROHIBIT_SENSOR://��ī��ȫƿ����, ����ī��ֹͣ��ī.
		*chsinfo = CHS_WAR_PUMP_PROHIBIT_SENSOR;
		break;
	case STATUS_WAR_OVER_SPEED_NOT_SUPPORT://��ͼ�ڲ�֧�ֳ�Ƶ��ͷ��汾��ʹ�ó�Ƶ, ϵͳǿ��ʹ�ø��ٴ�ӡ.
		*chsinfo = CHS_WAR_OVER_SPEED_NOT_SUPPORT;
		break;
	case STATUS_WAR_INK_PASSWORD_WRONGINPUT://����īˮ������󣬺��з�0~F��ֵ
		*chsinfo = CHS_WAR_INK_PASSWORD_WRONGINPUT;
		break;
	case STATUS_WAR_INK_PASSWORD_WRONG://����һ���Ϸ�īˮ����
		*chsinfo = CHS_WAR_INK_PASSWORD_WRONG;
		break;
	case STATUS_WAR_INK_PASSWORD_MANUFACTURERIDNOTMATCH://īˮ����ͳ��̲�ƥ��
		*chsinfo = CHS_WAR_INK_PASSWORD_MANUFACTURERIDNOTMATCH;
		break;
	case STATUS_WAR_INK_PASSWORD_BOARDIDNOTMATCH://īˮ����Ͱ��Ӳ�ƥ��
		*chsinfo = CHS_WAR_INK_PASSWORD_BOARDIDNOTMATCH;
		break;
	case STATUS_WAR_LIMITEDINK_FIRST://����10���ͳ���īˮ�����ˣ���һ�ξ���
		*chsinfo = CHS_WAR_LIMITEDINK_FIRST;
		break;
	case STATUS_WAR_LIMITEDINK_SECOND://����5���ͳ���īˮ�����ˣ��ڶ��ξ���
		*chsinfo = CHS_WAR_LIMITEDINK_SECOND;
		break;
	case STATUS_WAR_LIMITEDINK_LAST://����1���ͳ���īˮ�����ˣ����һ�ξ���
		*chsinfo = CHS_WAR_LIMITEDINK_LAST;
		break;
	case STATUS_WAR_INK_PASSWORD_UNKNOWN_DOT_VOLUME://��ǰ��ͷ��֧��īˮ���빦��.
		*chsinfo = CHS_WAR_INK_PASSWORD_UNKNOWN_DOT_VOLUME;
		break;
	case STATUS_WAR_PUMP_SPOTCOLOR1://רɫ1���ڱ�ī.
		*chsinfo = CHS_WAR_PUMP_SPOTCOLOR1;
		break;
	case STATUS_WAR_PUMP_SPOTCOLOR2://רɫ2���ڱ�ī.
		*chsinfo = CHS_WAR_PUMP_SPOTCOLOR2;
		break;
	case STATUS_WAR_FPGA_LESSDATA://��ӡ����С�ڵ����.
		*chsinfo = CHS_WAR_FPGA_LESSDATA;
		break;
	case STATUS_WAR_FPGA_ULTRADATA://��ӡ���ݶ��ڵ����.
		*chsinfo = CHS_WAR_FPGA_ULTRADATA;
		break;
	case STATUS_WAR_EPSONHEAD_TEMP_TOO_LOW://��ͷ�¶�̫��.
		*chsinfo = CHS_WAR_EPSONHEAD_TEMP_TOO_LOW;
		break;
	case STATUS_WAR_EPSONHEAD_TEMP_TOO_HIGH://��ͷ�¶�̫��.
		*chsinfo = CHS_WAR_EPSONHEAD_TEMP_TOO_HIGH;
		break;
	case STATUS_WAR_EPSONHEAD_NOT_CONNECT://��ͷδ����.
		*chsinfo = CHS_WAR_EPSONHEAD_NOT_CONNECT;
		break;
	case STATUS_WAR_EPSON_FPGA_ULTRADATA://����FPGA���������̫��.
		*chsinfo = CHS_WAR_EPSON_FPGA_ULTRADATA;
		break;
	case STATUS_WAR_EPSON_FPGA_LESSDATA://����FPGA���������̫��.
		*chsinfo = CHS_WAR_EPSON_FPGA_LESSDATA;
		break;
	case STATUS_WAR_EPSON_HEAD_FPGA_ERR://ͷ��FPGA���� .
		*chsinfo = CHS_WAR_EPSON_FPGA_ERR;
		break;
	case STATUS_WAR_EPSON_HEAD_LVDS_ERR://LVDSʧ��.
		*chsinfo = CHS_WAR_EPSON_LVDS_ERR;
		break;	
	case STATUS_WAR_EPSON_HEAD_REPORT_LVDS_ERR://ͷ�屨��LVDSʧ��.
		*chsinfo = CHS_WAR_EPSON_REPORT_LVDS_ERR;
		break;			
	case STATUS_WAR_UNKNOWN_NOZZLE_COUNT://��ǰ��ͷ��������δ֪��
		*chsinfo = CHS_WAR_UNKNOWN_NOZZLE_COUNT;
		break;
	case STATUS_UPDATE_SUCCESS://�����ɹ�.
		*chsinfo = CHS_UPDATE_SUCCESS;
		break;
	case STATUS_UPDATEERR_DSP_BEGIN_TIMEOUT://DSP��ʼ�������ʱ.
		*chsinfo = CHS_UPDATEERR_DSP_BEGIN_TIMEOUT;
		break;
	case STATUS_UPDATEERR_DSP_DATA_TIMEOUT://DSP���ݳ�ʱ.
		*chsinfo = CHS_UPDATEERR_DSP_DATA_TIMEOUT;
		break;
	case STATUS_UPDATEERR_DSP_END_TIMEOUT://DSP������ʱ.
		*chsinfo = CHS_UPDATEERR_DSP_END_TIMEOUT;
		break;
	case STATUS_UPDATEERR_ILIGALFILE://����������ļ���ʽ.
		*chsinfo = CHS_UPDATEERR_ILIGALFILE;
		break;
	case STATUS_UPDATEERR_INTERNAL_DATA://���Ϸ��������ļ�.
		*chsinfo = CHS_UPDATEERR_INTERNAL_DATA;
		break;
	case STATUS_UPDATEERR_CHECKSUM://����У�������.
		*chsinfo = CHS_UPDATEERR_CHECKSUM;
		break;
	case STATUS_UPDATEERR_EREASE://ARM �������.
		*chsinfo = CHS_UPDATEERR_EREASE;
		break;
	case STATUS_UPDATEERR_FLASHOP://Flash����.
		*chsinfo = CHS_UPDATEERR_FLASHOP;
		break;
	case STATUS_UPDATEERR_GZ_ILIGALFILE://��Ҫ�ر�̼���
		*chsinfo = CHS_UPDATEERR_GZ_ILIGALFILE;
		break;
	case STATUS_UPDATEERR_INKP_ILIGALFILE://��Ҫ����īˮ����̼���
		*chsinfo = CHS_UPDATEERR_INKP_ILIGALFILE;
		break;
	case STATUS_UPDATEERR_16H_ILIGALFILE://8ͷӲ���޷�����16ͷ�Ĺ̼���
		*chsinfo = CHS_UPDATEERR_16H_ILIGALFILE;
		break;
	default://δ֪�Ĵ���
		*chsinfo = CHS_UNKNOWN_ERR;
		break;
	}
}

//========================================================================
// ����: double xPow( double d , int n )
// ����: ����d��n�η�
// ����: d  ����
//		 n  ��
// ����: d��n�η�
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
double xPow( double d , int n )
{
	int s;
	double r = 1;
	
	if( n == 0 )
		return 1;
	
	if( n < 0 )
		s = 1 , n = -n;
	else
		s = 0;
	//#if 0
	//    while( n != 1 )
	//    {
	//        if( n&1 ) r*=d;
	//        n /= 2;
	//        d *= d;
	//    }
	//#else
	for(int i =0; i< n;i++)
		r *= d;
	//#endif
	return s?1/r:r;
}
struct MenuItem *lastmenu;
INT8U tofloat = FALSE;
//========================================================================
// ����: float CallUIGetFuncByType(struct MenuItem *mitem)
// ����: ���ݲ˵�ֵ���͵��ö�Ӧȡֵ����
// ����: mitem  �˵���
// ����: ȡ�õĲ˵�ֵ
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
float CallUIGetFuncByType(struct MenuItem *mitem)
{
	float retv = 0;
	INT32U reti = 0;
	if(tofloat == TRUE)
	{
		tofloat = FALSE;
		lastmenu-> DecimalPlaces = 2;
	}
	if(mitem->GetFloatFunc==0)
		return retv;
	switch(mitem->type)
	{
	case normal:
		break;
	case checkbox:
		reti = ((UIGetIndexFuncType)mitem->GetFloatFunc)(&mitem->ActionParameters);
		if(reti == mitem->Index)
			mitem->status = checked;
		else
			mitem->status = normalStatus;
		retv = reti;
		break;
	case radiocheckbox:	  	
		reti = ((UIGetIndexFuncExType)mitem->GetFloatFunc)(mitem,(int)(mitem->ActionParameters+0.5));
		if(reti == mitem->Index)
			mitem->status = radiochecked;
		else
			mitem->status = normalStatus;
		retv = reti;
		break;
	case editor:
		switch(mitem->vlaueType)
		{
		case tFloat:
			if(mitem->status != editting)
			{
				if(Cali_UM_Get_Step_Modify == mitem->GetFloatFunc)
				{
					mitem-> DecimalPlaces =0;
					tofloat = TRUE;
					lastmenu = mitem;
					retv = (float)Cali_UM_Get_Step(mitem,(int)(mitem->ActionParameters+0.5));
				}
				else if(Cali_EM_Get_Step_Modify == mitem->GetFloatFunc)
				{
					mitem-> DecimalPlaces =0;
					tofloat = TRUE;
					lastmenu = mitem;
					retv = (float)Cali_EM_Get_Step(mitem,(int)(mitem->ActionParameters+0.5));
				}
				else
				{
					retv = (float)mitem->GetFloatFunc(mitem,(int)(mitem->ActionParameters+0.5));
				}
			}
			else
			{
				retv = (float)mitem->GetFloatFunc(mitem,(int)(mitem->ActionParameters+0.5));
			}
			break;
		case tInt:
			retv = (float)((UIGetIntFuncExType)mitem->GetFloatFunc)(mitem,(int)(mitem->ActionParameters+0.5));
			break;
		case tShort:
		case tByte:
			break;
		}
		break;
	case pwdEditor:
		break;
	}
	return retv;
}

UCHAR CheckValidByCallUISetFunc(struct MenuItem *mitem,int index,float val)
{
	INT8U err, ret = True;
	INT32S val_i;
	
	if(mitem->SetFloatFunc==0)
		return ret;
	if(val <0)
		val_i = (int)(val - 0.5);
	else
		val_i = (int)(val + 0.5);
	switch(mitem->type)
	{
	case normal:
		break;
	case checkbox:
		OSSemPost(MenuSem);
		ret = ((UISetIndexFuncType)mitem->SetFloatFunc)((void*)-1,val_i);
		OSSemPend(MenuSem, 0, &err);
		break;
	case radiocheckbox:	  	
		OSSemPost(MenuSem);
		ret = ((UISetIndexFuncExType)mitem->SetFloatFunc)((void*)-1,index,val_i);
		OSSemPend(MenuSem, 0, &err);
		break;
	case editor:
		switch(mitem->vlaueType)
		{
		case tFloat:
			OSSemPost(MenuSem);
			ret = mitem->SetFloatFunc((void*)-1,index,val);
			OSSemPend(MenuSem, 0, &err);
			break;
		case tInt:
			OSSemPost(MenuSem);
			ret = ((UISetIntFuncExType)mitem->SetFloatFunc)((void*)-1,index, val_i);
			OSSemPend(MenuSem, 0, &err);
			break;
		case tShort:
		case tByte:
			break;
		}
		break;
	case pwdEditor:
		break;
	}
	return ret;
	
}

UCHAR CheckValid(struct MenuItem *mitem,int index,float val)
{
	if(!CheckValidByCallUISetFunc(mitem,index,val))
	{
		Control_SetAlarm(ALARM_TYPE_MENUERR, ALARM_SET);
		return False;
	}
	else
		return True;
}

//========================================================================
// ����: void CallUISetFuncByType(struct MenuItem *mitem,float val)
// ����: ���ݲ˵�ֵ���͵��ö�Ӧ��ֵ����
// ����: mitem  �˵���
//       index  �˵��������ֵ
//	 val  Ҫ�趨��ֵ checkbox���Ƿ�ѡ�У�radiocheckbox���趨��ActionParameters��editor��float/int/shortֵ
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
UCHAR CallUISetFuncByType(struct MenuItem *mitem,int index,float val)
{
	INT8U err, ret = True;
	INT32S val_i;
	
	if(mitem->SetFloatFunc==0)
		return ret;
	if(val <0)
		val_i = (int)(val - 0.5);
	else
		val_i = (int)(val + 0.5);
	switch(mitem->type)
	{
	case normal:
		break;
	case checkbox:
		OSSemPost(MenuSem);
		ret = ((UISetIndexFuncType)mitem->SetFloatFunc)(0,val_i);
		OSSemPend(MenuSem, 0, &err);
		break;
	case radiocheckbox:	  	
		OSSemPost(MenuSem);
		ret = ((UISetIndexFuncExType)mitem->SetFloatFunc)(0,index,val_i);
		OSSemPend(MenuSem, 0, &err);
		break;
	case editor:
		switch(mitem->vlaueType)
		{
		case tFloat:
			OSSemPost(MenuSem);
			ret = mitem->SetFloatFunc(0,index,val);
			OSSemPend(MenuSem, 0, &err);
			break;
		case tInt:
			OSSemPost(MenuSem);
			ret = ((UISetIntFuncExType)mitem->SetFloatFunc)(0,index, val_i);
			OSSemPend(MenuSem, 0, &err);
			break;
		case tShort:
		case tByte:
			break;
		}
		break;
	case pwdEditor:
		break;
	}
	return ret;
	
}

//========================================================================
// ����: void SetUIMenuItemValue(struct MenuItem *mitem,float val)
// ����: ���˵������ʵֵת��Ϊlcd editor����ʾ��ʽ
// ����: mitem  �˵���
//		val  �˵������ʵֵ
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
void SetUIMenuItemValue(struct MenuItem *mitem,float val)
{
	int dotindex = 0;
	double dtemp = 0;
	float tmp = 0.5;
	int point = mitem->DecimalPlaces;
	if( point != 0 )
	{
		while(point--)
		{
			tmp/= 10;
		}
	}
	
	switch(mitem->type)
	{
	case normal:
		break;
	case checkbox:
		if(val != 0)
			mitem->status = checked;
		else
			mitem->status = normalStatus;
		break;
	case radiocheckbox:
		for(int i = 0;i<mitem->Parents->ItemCount;i++)
		{
			if(i!=val)
				(mitem->Parents->ChildItems+i)->status = normalStatus;
			else
				(mitem->Parents->ChildItems+i)->status = radiochecked;
		}											
		break;
	case editor:				
		if(val >= 0)
			mitem->Value[0]=1;
		else
		{
			mitem->Value[0]=0;
			val = val *(-1);
		}
		if( (point != 0)&&(mitem->Unit != utCM))
			val += tmp;
		// ��λ����
		switch(mitem->Unit)
		{
		case utNone:
			break;
		case utInch:
			break;
		case utCM:
			val *= 2.54;
			if( point != 0 )
				val += tmp;
			break;
		case utSec:
			break;
		case utKHz:
			break;
		}
		
		if(mitem->DecimalPlaces > 0)
			dotindex = mitem->DecimalPlaces + 1;
		for(int i = 1;i< mitem->maxVal;i++)
		{
			if(i < (mitem->maxVal - dotindex))
				dtemp = xPow(10,(mitem->maxVal-1-i)-dotindex);
			else if(i > (mitem->maxVal - dotindex))
				dtemp = xPow(10,(mitem->maxVal-i)-dotindex);
			else
				continue;
			mitem->Value[i] = (UCHAR)(val/dtemp);
			if(mitem->Value[i] > 0)
				val -= mitem->Value[i] * dtemp;
		}
		break;
	}
}

//========================================================================
// ����: float GetValueFormUI(struct MenuItem *mitem)
// ����: ��Ϊlcd editor����ʾֵת��Ϊ�˵������ʵֵ
// ����: mitem  �˵���
//		
// ����: �˵������ʵֵ
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
float GetValueFormUI(struct MenuItem *mitem)
{
	float val=0;
	double dtemp = 0;	
	int dotindex = 0;
	if(mitem->DecimalPlaces > 0)
		dotindex = mitem->DecimalPlaces + 1;
	for(int i = 1;i< mitem->maxVal;i++)
	{	
		if(i < (mitem->maxVal - dotindex))
			dtemp = xPow(10,(mitem->maxVal-1-i)-dotindex);
		else if(i > (mitem->maxVal - dotindex))
			dtemp = xPow(10,(mitem->maxVal-i)-dotindex);
		else
			continue;
		val+= (mitem->Value[i] * dtemp);
	}
	//  if(mitem->DecimalPlaces > 0)
	//      ; //val += 5 * xPow(10,-dotindex); //float doen't 4��5��
	//  else
	//      val += 5 * xPow(10,-dotindex-1); //int ��Ҫ4��5��
	if(mitem->Value[0] == 0)
		val *= (-1);
	// ��λ����
	switch(mitem->Unit)
	{
	case utNone:
		break;
	case utInch:
		break;
	case utCM:
		val /= 2.54;
		break;
	case utSec:
		break;
	case utKHz:
		break;
	}
	return val;
}

//========================================================================
// ����: void CheckValChanged(struct MenuItem *mitem)
// ����: ���edit�ؼ��ĵ�ǰֵ�Ƿ���Ч �����Ч��ָ���Чֵ
// ����: mitem  edit�ؼ�ָ��
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
void CheckValChanged(struct MenuItem *mitem)
{
	//  float val = GetValueFormUI(mitem);
	//  if(val > mitem->maxVal)
	//  {
	//    val = mitem->maxVal;
	//    SetUIMenuItemValue(mitem,val);
	//  }
	//  if(val < mitem->minVal)
	//  {
	//    val = mitem->minVal;
	//    SetUIMenuItemValue(mitem,val);
	//  }
}

//========================================================================
// ����: INT8U GetUILanguage(void* Data)
// ����: ��ȡ������ʾ���Բ����ý�����ʾ
// ����: Data  0:en/1:chs
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
INT8U GetUILanguage(void* Data,int index)
{
	INT8U lang = UI_Get_Language(Data);
	if(lang == 0)
	{
		UILanguage = en;
		// CurrentLengthUnit = utInch;  //��ǰ���ȵ�λ
		CurrentTimeUnit = utSec;      //��ǰʱ�䵥λ
		CurrentFreUnit = utKHz;       //��ǰƵ�ʵ�λ
	}
	else if(lang == 1)
	{
		UILanguage = chs;
		CurrentLengthUnit = utCM;  //��ǰ���ȵ�λ
		CurrentTimeUnit = utSec;      //��ǰʱ�䵥λ
		CurrentFreUnit = utKHz;       //��ǰƵ�ʵ�λ
	}
	return lang;
}
extern void Change_Unit_For_Language(void);
//========================================================================
// ����: INT8U SetUILanguage(void* Data)
// ����: ���ý�����ʾ����
// ����: Data  0:en/1:chs
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
void SetUILanguage(void * pData, int Index, int Data)
{	
	//������������
	if(UI_Set_Language(pData,Index)==True)
	{
		if(Index == 0)
		{
			UILanguage = en;
			// CurrentLengthUnit = utInch;  //��ǰ���ȵ�λ
			CurrentTimeUnit = utSec;      //��ǰʱ�䵥λ
			CurrentFreUnit = utKHz;       //��ǰƵ�ʵ�λ
		}
		else if(Index == 1)
		{
			UILanguage = chs;
			CurrentLengthUnit = utCM;  //��ǰ���ȵ�λ
			CurrentTimeUnit = utSec;      //��ǰʱ�䵥λ
			CurrentFreUnit = utKHz;       //��ǰƵ�ʵ�λ
		}
		Change_Unit_For_Language();	
	}
}

#ifdef FUNC_WAVE_MAP
INT8U ReadWaveName()
{
	INT16U dataLen = 0;
	INT8U tmp[32];	
	
	DATA_LEN = 0;
	//���Ͷ�ȡ�����������ͷ��
	tmp[0] = 2;
	tmp[1] = UART_HEAD_WAVE_NAME_READ;
	while (!UART_SendCMD(UART_HEAD_CHANNEL, tmp))
		OSTimeDly(1);
	
	return 0;
}

INT8U ReadWaveMapTable()
{
	INT16U dataLen = 0;
	INT8U tmp[32];	
	
	DATA_LEN = 0;

	//���Ͷ�ȡ����ӳ������ͷ��
	tmp[0] = 2;
	tmp[1] = UART_HEAD_WAVE_CHANNEL_READ ;
	
	while (!UART_SendCMD(UART_HEAD_CHANNEL, tmp))
		OSTimeDly(1);
	return 0;
}

INT8U GetUIWaveMap(void* pData,int index)
{
	int parentIndex = -1;
	int parentParentIndex = -1;
	int val = -1;
	INT8U i = 0;
	
	if(menuStepIndex < 2)	//this condition is impossible
		return 0;
	
	parentIndex = pMenuStep[menuStepIndex-1]->Index;
	parentParentIndex = pMenuStep[menuStepIndex-2]->Index;
	
	memcpy(MenuStr_VSD_WaveName_EN, &WAVE_NAME_BUF[parentIndex * 8 * 8], sizeof(MenuStr_VSD_WaveName_EN));
	memcpy(MenuStr_VSD_WaveName_CN, &WAVE_NAME_BUF[parentIndex * 8 * 8], sizeof(MenuStr_VSD_WaveName_CN));
	
	val = WAVE_MAP_TABLE[parentParentIndex * 2 + parentIndex / 2]&(0xF << (parentIndex % 2 * 4));
	val >>= parentIndex % 2 * 4;
	return val;
}

INT8U SetUIWaveMap(void* pData,int index, int Data)
{
	int parentIndex = -1;
	int parentParentIndex = -1;
	if(pData == (void *)-1)
			return True;
	
	if(menuStepIndex < 2)	//this condition is impossible
		return 0;

	parentIndex = pMenuStep[menuStepIndex-1]->Index;
	parentParentIndex = pMenuStep[menuStepIndex-2]->Index;

	WAVE_MAP_TABLE[parentParentIndex * 2 + parentIndex / 2] =
		WAVE_MAP_TABLE[parentParentIndex * 2 + parentIndex / 2] & (~(0xF << (parentIndex % 2 * 4)))| (index << (parentIndex % 2 * 4));
	
	DATA_LEN = sizeof(WAVE_MAP_TABLE);
	memcpy(WAVE_BUF, WAVE_MAP_TABLE, sizeof(WAVE_MAP_TABLE));		//��WAVE_SET_FUN�궨��ʱ�����Ͳ���ӳ���ͷ��ʹ�ñ��� "WAVE_BUF" 
	TRANSFER_MODE = 43 - 25;		//��������ӳ������޸ģ�֪ͨͷ��
	
	return True;
}
#endif

//========================================================================
// ����: void SwitchMenuMode_S_A(INT8U isToAdvanced)
// ����: �˵�ģʽ�ڼ򵥺͸߼�ģʽ���л�
// ����: isToAdvanced  0:��/1:�߼�
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
void SwitchMenuMode_S_A(INT8U IsAdvMode)
{
	IsAdvancedMode = IsAdvMode;
	CurrentDisMode = MainScreen;
	
	PDisMenuItemsParent = &MainMenuRoot;
	Initial_Menu(PDisMenuItemsParent);
	
	//У׼��ģʽ�͸߼�ģʽ����
#if !defined(MICOLOR_AUTOFUCTION)
	(PDisMenuItemsParent->ChildItems+7)->Visible = 0;
#else
	//  (PDisMenuItemsParent->ChildItems+7)->Visible = IsAdvMode;
#endif
	(PDisMenuItemsParent->ChildItems+3)->Visible = !IsAdvMode;
	(PDisMenuItemsParent->ChildItems+4)->Visible = IsAdvMode;
	(PDisMenuItemsParent->ChildItems+0)->Visible = !IsAdvMode;
	(PDisMenuItemsParent->ChildItems+1)->Visible = IsAdvMode;
	
	((PDisMenuItemsParent->ChildItems+14)->ChildItems+1)->Visible = IsAdvMode;
	((PDisMenuItemsParent->ChildItems+14)->ChildItems+2)->Visible = IsAdvMode;
#if defined(EPSON_BOTTOM_BOARD_V3) ||defined (EPSON_BOTTOM_BOARD_V2_1)
	// ((PDisMenuItemsParent->ChildItems+3)->ChildItems+2)->Visible = IsAdvMode;
	// ((PDisMenuItemsParent->ChildItems+3)->ChildItems+3)->Visible = IsAdvMode;
	((PDisMenuItemsParent->ChildItems+8)->ChildItems+6)->Visible = IsAdvMode;
	((PDisMenuItemsParent->ChildItems+8)->ChildItems+7)->Visible = IsAdvMode;
	((PDisMenuItemsParent->ChildItems+8)->ChildItems+8)->Visible = IsAdvMode;
	((PDisMenuItemsParent->ChildItems+8)->ChildItems+9)->Visible = IsAdvMode;
	((PDisMenuItemsParent->ChildItems+14)->ChildItems+3)->Visible = IsAdvMode;
#endif
	
#ifdef SUPPORT_MOTOR_CONTROL_ONLY_STEP
	((PDisMenuItemsParent->ChildItems+14)->ChildItems+3)->Visible = IsAdvMode;
#endif
	
	if(GetColorNumber() > 4)
		((PDisMenuItemsParent->ChildItems+14)->ChildItems+4)->Visible = IsAdvMode;
	else
		((PDisMenuItemsParent->ChildItems+14)->ChildItems+4)->Visible = 0;
	
#if defined(EPSON_CLEAN_UPDOWN)
	MI_ALLWIN_1_ID23C_HEADCLEANING[5].Visible = IsAdvMode;
	MI_ALLWIN_1_ID23C_HEADCLEANING[7].Visible = IsAdvMode;
	MI_ALLWIN_1_ID23C_HEADCLEANING[8].Visible = IsAdvMode;
#elif defined (EPSON_CLEAN_INTEGRATE)||defined (EPSON_CLEAN_INTEGRATE_1) ||defined(EPSON_CLEAN_INTEGRATE_2)||defined(EPSON_CLEAN_INTEGRATE_3)
	MI_MICOLOR_1_ID28B_HEADCLEANING[5].Visible = IsAdvMode;
	MI_MICOLOR_1_ID28B_HEADCLEANING[7].Visible = IsAdvMode;
	MI_MICOLOR_1_ID28B_HEADCLEANING[8].Visible = IsAdvMode;
#elif defined(RICOH_CLEAN_PRESS)	
	MI_0_ID00_MenuChilds[2].Visible = IsAdvMode;
	MI_ALLWIN_1_ID23C_HEADCLEANING[7].Visible = IsAdvMode;
#endif
#ifdef MANUFACTURER_DYSS
	if(IsAdvMode)
	{
		MI_UM_2_ID27_Adjustsetting[0].Parents = &MI_EM_1_ID4B_ADJUSTMENT[9];
		MI_UM_2_ID27_Adjustsetting[1].Parents = &MI_EM_1_ID4B_ADJUSTMENT[9];
	}
	else
	{
		MI_UM_2_ID27_Adjustsetting[0].Parents = &MI_UM_1_ID25_ADJUSTMENT[7];
		MI_UM_2_ID27_Adjustsetting[1].Parents = &MI_UM_1_ID25_ADJUSTMENT[7];
	}
#endif
#ifdef RIPSTAR_FLAT_EX
	if(IsAdvMode)
	{
		MI_UM_2_ID27_Adjustsetting[0].Parents = &MI_EM_1_ID4B_ADJUSTMENT[10];
		MI_UM_2_ID27_Adjustsetting[1].Parents = &MI_EM_1_ID4B_ADJUSTMENT[10];
	}
	else
	{
		MI_UM_2_ID27_Adjustsetting[0].Parents = &MI_UM_1_ID25_ADJUSTMENT[7];
		MI_UM_2_ID27_Adjustsetting[1].Parents = &MI_UM_1_ID25_ADJUSTMENT[7];
	}
#endif
	//for aging testing
#ifdef MICOLOR_AUTOFUCTION
  MI_1_ID0D_OriginAndMediaWidth[9].Visible = IsAdvMode;
#elif defined RIPSTAR_FLAT_EX
#else
	MI_1_ID0D_OriginAndMediaWidth[5].Visible = IsAdvMode;
#endif
	if((fwInfo.hd_version>>31) != 0)
		MI_1_ID3FB_System[5].Visible = IsAdvMode;
	else
		MI_1_ID3FB_System[5].Visible = 0;
#ifdef FUNC_WAVE_MAP
	MI_1_ID3FB_System[6].Visible = IsAdvMode;
#endif
}

//========================================================================
// ����: void SwitchDisMode(INT8U isToMainMode)
// ����: �����ڲ˵�ģʽ����������л�
// ����: isToMainMode  0:�˵�/1:������
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
void SwitchDisMode(INT8U isToMainMode)
{	
	if(isToMainMode == 0)
	{
		CurrentDisMode = Menu;	
		PDisMenuItemsParent = &MainMenuRoot;
		while(PDisMenuItemsParent->Parents!=0)
		{
			PDisMenuItemsParent = PDisMenuItemsParent->Parents;
		}
		for(int i = 0;i< PDisMenuItemsParent->ItemCount;i++)
		{
			if((PDisMenuItemsParent->ChildItems+i)->Visible)
			{
				PDisMenuItemsParent->LastFirstIndex=i;
				PDisMenuItemsParent->SelectedIndex = i;
				break;
			}
		}		
	}
	else
	{
		CurrentDisMode = MainScreen;
	}
#ifdef FUNC_WAVE_MAP
	if(isToMainMode == 0)
		pMenuStep[menuStepIndex++] = &MainMenuRoot;
	else
	{
		pMenuStep[0] = 0;
		menuStepIndex = 0;
	}	
#endif
}

#if defined(LCD_MODULE_128_64_ST5668A)
int SubMenuHaveRadiocheckbox(struct MenuItem *temp)
{
	for(int i = 0;i< temp->ItemCount;i++)
	{
		if ((temp->ChildItems+i)->type == checkbox || (temp->ChildItems+i)->type == radiocheckbox)
		{
			return 1;
		}
	}
	return 0;
}
#endif

#if defined(QICAIHONG)
void OpenAdvanceModemenu(void)
{
	char str1[] = "System";
	char str2[] = "Adjustment";
	char str[16] = "";
	struct MenuItem * pMenuList;
	
	CurrentDisMode = Menu;	
	pMenuList = &MainMenuRoot;

	if (IsAdvancedMode)
	{
		strcpy(str, str2);
	}
	else
	{
		strcpy(str, str1);
	}
	for(int i = 0;i< pMenuList->ItemCount;i++)
	{
		if ((strncmp((pMenuList->ChildItems+i)->Text_en, str, strlen(str)) == 0)&&
			(pMenuList->ChildItems+i)->Visible != 0)
		{
			PDisMenuItemsParent = pMenuList->ChildItems+i;
			break;
		}
	}

	for(int i = 0;i< PDisMenuItemsParent->ItemCount;i++)
	{
		if((PDisMenuItemsParent->ChildItems+i)->Visible)
		{
			PDisMenuItemsParent->LastFirstIndex=i;
			PDisMenuItemsParent->SelectedIndex = i;
			break;
		}
	}	
}

void OpenMediaTypemenu(void)
{
	char str[] = "Media Type";
	struct MenuItem * pMenuList;
	
	CurrentDisMode = Menu;	
	pMenuList = &MainMenuRoot;

	for(int i = 0;i< pMenuList->ItemCount;i++)
	{
		if (strncmp((pMenuList->ChildItems+i)->Text_en, str, strlen(str)) == 0)
		{
			PDisMenuItemsParent = pMenuList->ChildItems+i;
			break;
		}
	}

	for(int i = 0;i< PDisMenuItemsParent->ItemCount;i++)
	{
		if((PDisMenuItemsParent->ChildItems+i)->Visible)
		{
			PDisMenuItemsParent->LastFirstIndex=i;
			PDisMenuItemsParent->SelectedIndex = i;
			break;
		}
	}	

#if defined(LCD_MODULE_128_64_ST5668A)
	if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
	{
		radiocheckbox_offset = INDICATE_AREAS_WIDTH;
	}
#endif
}

void OpenHeaterMenu(void)
{
	char str[] = "Platform Heat";
	struct MenuItem * pMenuList;
	
	CurrentDisMode = Menu;	
	pMenuList = &MainMenuRoot;

	for(int i = 0;i< pMenuList->ItemCount;i++)
	{
		if (strncmp((pMenuList->ChildItems+i)->Text_en, str, strlen(str)) == 0)
		{
			PDisMenuItemsParent = pMenuList->ChildItems+i;
			break;
		}
	}

	for(int i = 0;i< PDisMenuItemsParent->ItemCount;i++)
	{
		if((PDisMenuItemsParent->ChildItems+i)->Visible)
		{
			PDisMenuItemsParent->LastFirstIndex=i;
			PDisMenuItemsParent->SelectedIndex = i;
			break;
		}
	}	

#if defined(LCD_MODULE_128_64_ST5668A)
	if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
	{
		radiocheckbox_offset = INDICATE_AREAS_WIDTH;
	}
#endif
}
#endif


//========================================================================
// ����: void OpenSubMenu()
// ����: �򿪵�ǰ�˵�����Ӳ˵�,�����
// ����: ��
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
void OpenSubMenu()
{
	struct MenuItem *temp = (PDisMenuItemsParent->ChildItems+PDisMenuItemsParent->SelectedIndex);								
	if(temp->ItemCount!= 0)
	{
		PDisMenuItemsParent = temp;
		for(int i = 0;i< PDisMenuItemsParent->ItemCount;i++)
		{
			if((PDisMenuItemsParent->ChildItems+i)->Visible)
			{
				PDisMenuItemsParent->LastFirstIndex=i;
				PDisMenuItemsParent->SelectedIndex = i;
				break;
			}
		}
	#if defined(LCD_MODULE_128_64_ST5668A)
		//if ((PDisMenuItemsParent->ChildItems)->type == radiocheckbox)
		if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
		{
			radiocheckbox_offset = INDICATE_AREAS_WIDTH;
		}
	#endif
#ifdef FUNC_WAVE_MAP
		pMenuStep[menuStepIndex++] = PDisMenuItemsParent;
#endif
		bNeedRefresh = 1;
	}
#if defined(LCD_MODULE_128_64_ST5668A)
	else
	{
		if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
		{
			radiocheckbox_offset = INDICATE_AREAS_WIDTH;
		}
	}
#endif

}

//========================================================================
// ����: static void Btn_BasePoint_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: BasePoint�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_BasePoint_RaisedEvent(enum KeyEventEnum keyEvent)
{
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		{
#ifdef FULGENCY_FUN
			FULGENCY_PLC_MASK |=START_PRT; 
#else
			INT8U err;
			OSSemPost(MenuSem);
			UIAction_SetBasePoint(0);
			OSSemPend(MenuSem, 0, &err);
#endif
		}
		bNeedRefresh = 1;
		break;
	}	
}

//========================================================================
// ����: static void Btn_SheetCut_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: SheetCut�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_SheetCut_RaisedEvent(enum KeyEventEnum keyEvent)
{
	INT8U err;
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
#if (defined( RIPSTAR_FLAT_EX)||defined( RIPSTAR_SIX_AXIS_MODEL)) && !defined(FLAT_NO_Z_KEY)
		if(CurrentDisMode == MainScreen&&CurrentStatus != E_ST_PRINT)
		{
			OSSemPost(MenuSem);
			UIAction_Move_Z_Down_Start(0);
			OSSemPend(MenuSem, 0, &err);				
		}
#endif
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
#if defined(MICOLOR_AUTOFUCTION)&&!defined(DGEN_AUTOFUCTION)		
		{
			OSSemPost(MenuSem);
			UIAction_SheetCut(0);
			OSSemPend(MenuSem, 0, &err);
		}
#elif defined(MANUFACTURER_BEMAJET)||defined(MANUFACTURER_INKWIN)||defined(MANUFACTURER_DESIGN_EPSON)||defined(MANUFACTURER_DESIGN_EPSON_UV)||defined(FULGENCY_FUN)
		OSSemPost(MenuSem);
		UIAction_CheckNozzle(0);
		OSSemPend(MenuSem, 0, &err);
#elif defined(ALLWIN_EPSON_SAME)||defined(DGEN_AUTOFUCTION)	
		OSSemPost(MenuSem);
		UIAction_MeasureMedia(0,0);
		OSSemPend(MenuSem, 0, &err);	
#elif (defined( RIPSTAR_FLAT_EX)||defined( RIPSTAR_SIX_AXIS_MODEL)) && !defined(FLAT_NO_Z_KEY)
		OSSemPost(MenuSem);
		UIAction_Move_Z_Down_End(0);
		OSSemPend(MenuSem, 0, &err);
#elif defined(MANUFACTURER_TATE_EPSON)&&defined(EPSON_CLEAN_UPDOWN)&&defined(HEAD_RICOH_G4)	  
		RegPostMoveOfUncapping(1,cleanparam_EPSON_ALLWIN.factory.Carriage_X_WipePos_End[0] + cleanparam_EPSON_ALLWIN.factory.Carriage_X_WipePos_End[1]+ cleanparam_EPSON_ALLWIN.factory.Carriage_X_WipePos_End[2]+ cleanparam_EPSON_ALLWIN.factory.Carriage_X_WipePos_End[3] - curPos.x);
		StartUnCapping();	  
#endif
		bNeedRefresh = 0;
		break;
	}	
	bNeedRefresh = 0;
}
void LCD_SetPrintQuality(void)
{
	U8 err;
#ifdef FUNC_MAINTAIN
	if((CurrentStatus == E_ST_RDY)||(CurrentStatus == E_ST_MOVING)||(CurrentStatus == E_ST_CLEANING)||(CurrentStatus==E_ST_MAINTAIN))
#else
	if((CurrentStatus == E_ST_RDY)||(CurrentStatus == E_ST_MOVING)||(CurrentStatus == E_ST_CLEANING))
#endif
	{
		UIAction_SetPrintQuality(NULL);
                Set_PrintQuality(LCDMenuConfig.PrintQuality);
		if(CurrentDisMode == MainScreen)
		{
			Draw_PrintQuality();
		}
	}
	
}
//========================================================================
// ����: static void Btn_PrintQuality_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: PrintQuality�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_PrintQuality_RaisedEvent(enum KeyEventEnum keyEvent)
{
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
		case Menu:
#if defined(MANUFACTURER_BEMAJET)
			INT8U err;
			OSSemPost(MenuSem);
			UIAction_MeasureMedia(0,0);
			OSSemPend(MenuSem, 0, &err);	
#else			
			LCD_SetPrintQuality();
#endif
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 1;
		break;
	}	
}

//========================================================================
// ����: static void Btn_Width_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: Width�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_Width_RaisedEvent(enum KeyEventEnum keyEvent)
{
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		{
			INT8U err;
			OSSemPost(MenuSem);
			UIAction_MeasureMedia(0,0);
			OSSemPend(MenuSem, 0, &err);
		}
		bNeedRefresh = 1;
		break;
	}	
}

//========================================================================
// ����: static void Btn_Menu_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: Menu�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_Menu_RaisedEvent(enum KeyEventEnum keyEvent)
{
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			SwitchDisMode(0);
			break;
		case Menu:
			SwitchDisMode(1);
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 1;
		break;
	}
}
#define CHECK_PASSWORD_NUM 2
INT8U Check_Password(UCHAR * password)
{
	return UI_CheckPassword(NULL, password, EDITOR_MAX_LEN);
}
void Clear_Password(UCHAR * password)
{
	int i = 0;
	while(i < EDITOR_MAX_LEN)
	{
		password[i] = 0;
		i++;
	}
}
//========================================================================
// ����: static void Btn_Enter_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: Enter�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_Enter_RaisedEvent(enum KeyEventEnum keyEvent)
{
	struct MenuItem* temp;
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			{
				INT8U err;
				OSSemPost(MenuSem);
#ifdef EPSON_FLASH_IDLE
				UIAction_FLAH_IDLE(0,0);
#else
				UIAction_X_GoHome_by_key(0);
#endif
				OSSemPend(MenuSem, 0, &err);
			}
			break;
		case Menu:							
			{
				temp = (PDisMenuItemsParent->ChildItems+PDisMenuItemsParent->SelectedIndex);								
				switch(temp->type)
				{
				case normal:
					{
						CurrentDisMode = Menu;
						temp->status=normalStatus;
						OpenSubMenu();
					}
					break;
				case checkbox:
					{
						CurrentDisMode = Menu;
						if(temp->status==checked)
							temp->status=normalStatus;
						else
							temp->status=checked;
						//Ӧ����ֵ
						float fEditorVal = (float)(temp->status==checked);
						UCHAR ret = CheckValid(temp,(int)temp->ActionParameters, fEditorVal);
						if(!ret)
						{
							break;
						}
						ret = CallUISetFuncByType(temp, (int)temp->ActionParameters, fEditorVal);
						if(!ret)
							Control_SetAlarm(ALARM_TYPE_MENUERR, ALARM_SET);
				#if defined(LCD_MODULE_128_64_ST5668A)
						radiocheckbox_offset = INDICATE_AREAS_WIDTH;
				#endif
					}
					break;
				case radiocheckbox:
					{
						CurrentDisMode = Menu;										
						if(temp->status!=radiochecked)
						{
							//Ӧ����ֵ
							UCHAR ret = CheckValid(temp,(int)temp->ActionParameters, temp->ActionParameters);
							if(!ret)
							{
								break;
							}
							ret = CallUISetFuncByType(temp, (int)temp->ActionParameters, temp->ActionParameters);
							if(!ret)
								Control_SetAlarm(ALARM_TYPE_MENUERR, ALARM_SET);
						#if defined(LCD_MODULE_128_64_ST5668A)
							radiocheckbox_offset = INDICATE_AREAS_WIDTH;
						#endif
						}
					}
					break;
				case editor:
				case pwdEditor:
					{
						if(temp->SetFloatFunc != 0)
						{
							UCHAR ret = CheckValid(temp,(int)temp->ActionParameters, 0.0f);
							if(!ret)
							{
								break;
							}
						}					
						CurrentDisMode = Edit;
						temp->status=editting;
						if(temp->status!=normalStatus && temp->GetFloatFunc!= 0)
						{
							float fPWDVal = CallUIGetFuncByType(temp); //��ȡҪ��ʾ��ֵ
							SetUIMenuItemValue(temp, fPWDVal);//��ֵ��������ʾ�ĸ�ʽ
						}
				#if defined(LCD_MODULE_128_64_ST5668A)
						//if ((PDisMenuItemsParent->ChildItems)->type == radiocheckbox)
						if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
						{
							radiocheckbox_offset = INDICATE_AREAS_WIDTH;
						}
				#endif
					}
					break;
				}		
				if(temp->ActionFunc != 0)
				{
					INT8U err;
					OSSemPost(MenuSem);
					UCHAR ret = temp->ActionFunc(0,(int)temp->ActionParameters);
					if(!ret)
						Control_SetAlarm(ALARM_TYPE_MENUERR, ALARM_SET);
					OSSemPend(MenuSem, 0, &err);
				}
			}
			break;
		case Edit:							
			{
				temp = (PDisMenuItemsParent->ChildItems+PDisMenuItemsParent->SelectedIndex);								
				if(temp->type == editor &&temp->status==editting)
				{
					CurrentDisMode = Menu;
					temp->status = normalStatus;
					//(PDisMenuItemsParent->ChildItems+PDisMenuItemsParent->SelectedIndex)->status==normalStatus;
					//Ӧ����ֵ
					float fEditorVal = 0;
					if(temp->SetFloatFunc != 0)
					{
						fEditorVal = GetValueFormUI(temp);
						UCHAR ret = CallUISetFuncByType(temp,(int)temp->ActionParameters, fEditorVal);
						if(!ret)
							Control_SetAlarm(ALARM_TYPE_MENUERR, ALARM_SET);
					}
					if(temp->GetFloatFunc!= 0)
					{
						fEditorVal = CallUIGetFuncByType(temp); //��ȡҪ��ʾ��ֵ
						SetUIMenuItemValue(temp, fEditorVal);//��ֵ��������ʾ�ĸ�ʽ
					}
				}
				else if(temp->type == pwdEditor &&temp->status==editting)
				{
					CurrentDisMode = Menu;
					temp->status = normalStatus;
					if(Check_Password(temp->Value))
					{
						//�������ȡ����
						IsAdvancedMode=!IsAdvancedMode;
						//��֤����,��ִ�ж���
						SwitchMenuMode_S_A(IsAdvancedMode);
					}
					else
						Control_SetAlarm(ALARM_TYPE_MENUERR, ALARM_SET);
					
					Clear_Password(temp->Value);
					temp->ActiveIndex = 0;
				}
			#if defined(LCD_MODULE_128_64_ST5668A)
				//if ((PDisMenuItemsParent->ChildItems)->type == radiocheckbox)
				if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
				{
					radiocheckbox_offset = INDICATE_AREAS_WIDTH;
				}
			#endif
			}
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 1;
		break;
	}
}

//========================================================================
// ����: static void Btn_Cleaning_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: Cleaning�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_Cleaning_RaisedEvent(enum KeyEventEnum keyEvent)
{
	INT8U err;
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		{
#if (defined( RIPSTAR_FLAT_EX)||defined( RIPSTAR_SIX_AXIS_MODEL)) && !defined(FLAT_NO_Z_KEY)
			if(CurrentDisMode == MainScreen&&CurrentStatus != E_ST_PRINT)
			{
				OSSemPost(MenuSem);
				UIAction_Move_Z_Up_Start(0);
				OSSemPend(MenuSem, 0, &err);
			}
#endif						
		}        
		bNeedRefresh = 1;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
#if (defined( RIPSTAR_FLAT_EX)||defined( RIPSTAR_SIX_AXIS_MODEL)) && !defined(FLAT_NO_Z_KEY)
		OSSemPost(MenuSem);
		UIAction_Move_Z_Up_End(0);
		OSSemPend(MenuSem, 0, &err);	
#elif !defined( RICOH_CLEAN_PRESS)
		OSSemPost(MenuSem);
		UIAction_QuickCleaning(0);
		OSSemPend(MenuSem, 0, &err);
#endif				
		bNeedRefresh = 1;
		break;
	}
}

//========================================================================
// ����: static void Btn_Pause_resume_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: Pause_resume�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_Pause_resume_RaisedEvent(enum KeyEventEnum keyEvent)
{
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		{
			INT8U err;
			OSSemPost(MenuSem);
			UIAction_PauseResumePrint(0);
			OSSemPend(MenuSem, 0, &err);
		}
		bNeedRefresh = 1;
		break;
	}
}

//========================================================================
// ����: static void Btn_Abort_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: Abort�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_Abort_RaisedEvent(enum KeyEventEnum keyEvent)
{
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		{
			INT8U err;
			OSSemPost(MenuSem);
			UIAction_CancelPrint(0);
			OSSemPend(MenuSem, 0, &err);
		}
		bNeedRefresh = 1;
		break;
	}
}

//========================================================================
// ����: static void Btn_Checknozzle_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: Checknozzle�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_Checknozzle_RaisedEvent(enum KeyEventEnum keyEvent)
{
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		{
			INT8U err;
			OSSemPost(MenuSem);
			UIAction_CheckNozzle(0);
			OSSemPend(MenuSem, 0, &err);
		}
		//bNeedRefresh = 1;
		break;
	}
}


//========================================================================
// ����: static void Btn_left_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: left�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_Move_left_RaisedEvent(enum KeyEventEnum keyEvent)
{
	struct MenuItem* temp;
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			{
				INT8U err;
				OSSemPost(MenuSem);
				UIAction_Move_Left_Start(0);
				OSSemPend(MenuSem, 0, &err);
			}
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			{
				INT8U err;
				OSSemPost(MenuSem);
				UIAction_Move_Left_End(0);
				OSSemPend(MenuSem, 0, &err);
			}
			break;
		case Menu:
#ifdef FUNC_WAVE_MAP
			pMenuStep[menuStepIndex--] = 0;
			if(menuStepIndex > 0)
			{
				PDisMenuItemsParent = pMenuStep[menuStepIndex-1];				
				PDisMenuItemsParent->LastFirstIndex = PDisMenuItemsParent->LastFirstIndex;
			}
#else
			if(PDisMenuItemsParent->Parents != 0)
			{
				PDisMenuItemsParent = PDisMenuItemsParent->Parents; 							
				PDisMenuItemsParent->LastFirstIndex = PDisMenuItemsParent->LastFirstIndex;
			}
#endif
			else
				SwitchDisMode(1);
		#if defined(LCD_MODULE_128_64_ST5668A)
			//if ((PDisMenuItemsParent->ChildItems)->type == radiocheckbox)
			if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
			{
				radiocheckbox_offset = INDICATE_AREAS_WIDTH;
			}
		#endif
			break;
		case Edit:							
			{
				temp = (PDisMenuItemsParent->ChildItems+PDisMenuItemsParent->SelectedIndex);								
				if((temp->type == editor||temp->type == pwdEditor )&&temp->status==editting)
				{
					if(temp->ActiveIndex >0)
						temp->ActiveIndex--;
					else
						temp->ActiveIndex = temp->maxVal-1;
				}
		#if defined(LCD_MODULE_128_64_ST5668A)
				//if ((PDisMenuItemsParent->ChildItems)->type == radiocheckbox)
				if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
				{
					radiocheckbox_offset = INDICATE_AREAS_WIDTH;
				}
		#endif
			}
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 1;
		break;
	}
	
}

//========================================================================
// ����: static void Btn_right_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: right�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_Move_right_RaisedEvent(enum KeyEventEnum keyEvent)
{
	struct MenuItem* temp;
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			{
				INT8U err;
				OSSemPost(MenuSem);
				UIAction_Move_Right_Start(0);
				OSSemPend(MenuSem, 0, &err);
			}
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			{
				INT8U err;
				OSSemPost(MenuSem);
				UIAction_Move_Right_End(0);
				OSSemPend(MenuSem, 0, &err);
			}
			break;
		case Menu:
			{
				OpenSubMenu();
			}	
			break;
		case Edit:
			{
				temp = (PDisMenuItemsParent->ChildItems+PDisMenuItemsParent->SelectedIndex);								
				if((temp->type == editor||temp->type == pwdEditor )
				   &&temp->status==editting)
				{
					if(temp->ActiveIndex < temp->maxVal-1)
						temp->ActiveIndex++;
					else
						temp->ActiveIndex=0;
				}
				bNeedRefresh = 0;
		#if defined(LCD_MODULE_128_64_ST5668A)
				//if ((PDisMenuItemsParent->ChildItems)->type == radiocheckbox)
				if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
				{
					radiocheckbox_offset = INDICATE_AREAS_WIDTH;
				}
		#endif
			}
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 1;
		break;
	}
	
}
INT8U Can_Not_Need_Refresh = FALSE;
void Menu_Refresh_Quick(INT8U num,INT8U is_forward)
{
	if(is_forward)
		LCD_InverseRegion(INDICATE_AREAS_WIDTH,UNIT_AREAS_WIDTH*(num-1),LCD_PIXEL_WIDTH-INDICATE_AREAS_WIDTH, LCD_MENUITEM_HEIGHT);
	else
		LCD_InverseRegion(INDICATE_AREAS_WIDTH,UNIT_AREAS_WIDTH*(num+1),LCD_PIXEL_WIDTH-INDICATE_AREAS_WIDTH, LCD_MENUITEM_HEIGHT);
	LCD_InverseRegion(INDICATE_AREAS_WIDTH,UNIT_AREAS_WIDTH*(num),LCD_PIXEL_WIDTH-INDICATE_AREAS_WIDTH, LCD_MENUITEM_HEIGHT);
}
INT8U Get_Real_Num()
{
	INT8U i,j=(PDisMenuItemsParent->SelectedIndex - PDisMenuItemsParent->LastFirstIndex);
	i = PDisMenuItemsParent->SelectedIndex;
	while(i != PDisMenuItemsParent->LastFirstIndex)
	{
		if(!((PDisMenuItemsParent->ChildItems+i)->Visible))
			j--;
		i--;
	}
	return j;
}
CHAR MainInfo_Step[14] = {0};	
CHAR Last_MainInfo_Step[14] = {0};	
extern CHAR MainInfo_PrintQuality[20];	
void Set_PrintStep(INT32U Step)
{
	if(UILanguage == en)
	{
		sprintf(MainInfo_Step,"Step:%d",Step);
	}
	else
	{
		sprintf(MainInfo_Step,"����:%d",Step);
	}
}
extern INT8U MediaType;
void Draw_Print_QualityStep(void)
{
#if defined(LCD_MODULE_128_64_ST5668A)
	int baseX = 0;
#else
	int baseX = CHECKBOX_WIDTH;
#endif
	LCD_FillRectangle(baseX, LCD_PIXEL_HIGH-16, LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-baseX - baseX*5, LCD_MENUITEM_HEIGHT, 0);
	Set_PrintStep(GetPrintingStep(NULL));
	if(UILanguage == en) //(Menu_List->Lang == en)
	{
		LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*3, MainInfo_Step);//����ֵ
	}
	else
	{
		LCD_DrawText(baseX, LCD_MENUITEM_HEIGHT*3, MainInfo_Step);//����ֵ
	}
#if 0
	LCD_FillRectangle(CHECKBOX_WIDTH*5, LCD_PIXEL_HIGH-16, LCD_PIXEL_WIDTH-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH - CHECKBOX_WIDTH*5, LCD_MENUITEM_HEIGHT, 0);
	Set_PrintStep(GetPrintingStep(NULL));
	if(UILanguage == en) //(Menu_List->Lang == en)
	{
		LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_Step)*8-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH*2, LCD_MENUITEM_HEIGHT*3, MainInfo_Step);//����ֵ
	}
	else
	{
		LCD_DrawText(LCD_PIXEL_WIDTH-strlen(MainInfo_Step)*8-strlen(MainInfo_PrintQuality)*8-CHECKBOX_WIDTH*2, LCD_MENUITEM_HEIGHT*3, MainInfo_Step);//����ֵ
	}
#endif
}
//========================================================================
// ����: static void Btn_forward_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: forward�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_Move_forward_RaisedEvent(enum KeyEventEnum keyEvent)
{
	struct MenuItem* temp;
	int dotindex = 0;
	INT8U err = 0;
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			{
				if(CurrentStatus == E_ST_PRINT)
				{
					//INT8U err;
					//OSSemPend(Lcd_Cmd, 0, &err);
					//Init_Lcd_Cmd_Q();
					Can_Not_Need_Refresh = True;		
					UpDownPrintingStep(NULL, False);
					Draw_Print_QualityStep();
				}
				else
				{
					//INT8U err;
					OSSemPost(MenuSem);
					UIAction_Move_Down_Start(0);
					OSSemPend(MenuSem, 0, &err);		
				}
			}
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			{
				if(CurrentStatus != E_ST_PRINT)
				{
					//INT8U err;
					OSSemPost(MenuSem);
					UIAction_Move_Down_End(0);
					OSSemPend(MenuSem, 0, &err);
				}
			}
			bNeedRefresh = 0;
			break;
		case Menu:
			{
				UINT iCount = 0;
				int iFirstVisble = -1;
				int iTempFI = -1;
				for(int i = PDisMenuItemsParent->LastFirstIndex;i< PDisMenuItemsParent->ItemCount;i++)
				{
					if((PDisMenuItemsParent->ChildItems+i)->Visible)
					{
						if(i>PDisMenuItemsParent->LastFirstIndex && iTempFI<0)
							iTempFI = i;
						if(i <= PDisMenuItemsParent->SelectedIndex)
							iCount++;
						else if(iFirstVisble < 0)
							iFirstVisble = i;
					}
				}
				if(iCount==Dis_Menu_Num_Page&&iFirstVisble>=0)
				{
					PDisMenuItemsParent->LastFirstIndex=iTempFI;
					PDisMenuItemsParent->SelectedIndex=iFirstVisble;
				}
				else if(iCount < Dis_Menu_Num_Page && iFirstVisble>=0)
				{
					//OSSemPend(Lcd_Cmd, 0, &err);
					//Init_Lcd_Cmd_Q();
					PDisMenuItemsParent->SelectedIndex=iFirstVisble;
					Menu_Refresh_Quick(Get_Real_Num(),True);
					Can_Not_Need_Refresh = True;			
				}
				else
				{
					for(int i = 0;i< PDisMenuItemsParent->ItemCount;i++)
					{
						if((PDisMenuItemsParent->ChildItems+i)->Visible)
						{
							PDisMenuItemsParent->LastFirstIndex=i;
							PDisMenuItemsParent->SelectedIndex=i;
							break;
						}
					}
				}							
			#if defined(LCD_MODULE_128_64_ST5668A)
				//if ((PDisMenuItemsParent->ChildItems)->type == radiocheckbox)
				if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
				{
					radiocheckbox_offset = INDICATE_AREAS_WIDTH;
				}
			#endif
			}
			break;
		case Edit:
			{
				temp = (PDisMenuItemsParent->ChildItems+PDisMenuItemsParent->SelectedIndex);								
				if(temp->DecimalPlaces > 0)
					dotindex = temp->DecimalPlaces + 1;
				if(temp->type == editor && temp->status==editting && temp->ActiveIndex != (temp->maxVal - dotindex))
				{
					if(temp->ActiveIndex==0)
					{
						if(temp->Value[temp->ActiveIndex]==0)
							temp->Value[temp->ActiveIndex]=1;
						else
							temp->Value[temp->ActiveIndex]=0;
					}
					else
					{
						if(temp->Value[temp->ActiveIndex]>0)
							temp->Value[temp->ActiveIndex]--;
						else
							temp->Value[temp->ActiveIndex]=9;
					}
					CheckValChanged(temp);
				}
				if(temp->type == pwdEditor && temp->status==editting)
				{
					if(temp->Value[temp->ActiveIndex]<'0'
					   ||(temp->Value[temp->ActiveIndex]>'9' && temp->Value[temp->ActiveIndex]<'A')
						   ||temp->Value[temp->ActiveIndex]>'Z'
							   )
						temp->Value[temp->ActiveIndex]='0';
					else if(temp->Value[temp->ActiveIndex]=='0')
						temp->Value[temp->ActiveIndex]='Z';						
					else if(temp->Value[temp->ActiveIndex]=='A')
						temp->Value[temp->ActiveIndex]='9';
					else
						temp->Value[temp->ActiveIndex]--;
				}
		#if defined(LCD_MODULE_128_64_ST5668A)
				//if ((PDisMenuItemsParent->ChildItems)->type == radiocheckbox)
				if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
				{
					radiocheckbox_offset = INDICATE_AREAS_WIDTH;
				}
		#endif
				bNeedRefresh = 0;
			}
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 1;
		break;
	}
	
}

//========================================================================
// ����: static void Btn_backward_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: backward�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2010/11/13      First version
//========================================================================
static void Btn_Move_backward_RaisedEvent(enum KeyEventEnum keyEvent)
{
	struct MenuItem* temp;	
	int dotindex = 0;
	INT8U err =0;
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			{			
				if(CurrentStatus == E_ST_PRINT)
				{
					//INT8U err;
					//OSSemPend(Lcd_Cmd, 0, &err);
					//Init_Lcd_Cmd_Q();
					Can_Not_Need_Refresh = True;	
					UpDownPrintingStep(NULL, True);
					Draw_Print_QualityStep();
				}
				else
				{
					//INT8U err;
					OSSemPost(MenuSem);
					UIAction_Move_Up_Start(0);
					OSSemPend(MenuSem, 0, &err);
				}
			}
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			{
				if(CurrentStatus != E_ST_PRINT)
				{
					//INT8U err;
					OSSemPost(MenuSem);
					UIAction_Move_Up_End(0);
					OSSemPend(MenuSem, 0, &err);
				}
			}
			bNeedRefresh = 0;
			break;
		case Menu:
			{
				int CurOffset = PDisMenuItemsParent->SelectedIndex - PDisMenuItemsParent->LastFirstIndex;
				UINT iCount = 0;
				int i = PDisMenuItemsParent->SelectedIndex-1;
				for(;i>=0;i--)
				{
					if((PDisMenuItemsParent->ChildItems+i)->Visible)
					{
						iCount=1;
						break;
					}
				}
				
				if(CurOffset>0 && iCount==1)
				{
					//OSSemPend(Lcd_Cmd, 0, &err);
					//Init_Lcd_Cmd_Q();
					PDisMenuItemsParent->SelectedIndex = i;
					Menu_Refresh_Quick(Get_Real_Num(),False);
					Can_Not_Need_Refresh = True;	
					bNeedRefresh = 0;
				}
				else if(CurOffset==0)
				{
					if(iCount==1)
					{
						PDisMenuItemsParent->LastFirstIndex=i;
						PDisMenuItemsParent->SelectedIndex = i;
					}
					else
					{
						iCount=0;
						int j = -1;
						for(i = PDisMenuItemsParent->ItemCount-1;i>=0;i--)
						{
							if((PDisMenuItemsParent->ChildItems+i)->Visible)
							{
								iCount++;
								if(j<0)
									j=i;
							}
							if(iCount == Dis_Menu_Num_Page)
								break;
						}
						if(i<0)
							i=0;
						PDisMenuItemsParent->LastFirstIndex = i;
						PDisMenuItemsParent->SelectedIndex = j;
					}
					bNeedRefresh = 1;
				}
			#if defined(LCD_MODULE_128_64_ST5668A)
				//if ((PDisMenuItemsParent->ChildItems)->type == radiocheckbox)
				if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
				{
					radiocheckbox_offset = INDICATE_AREAS_WIDTH;
				}
			#endif
			}
			break;
		case Edit:
			{
				temp = (PDisMenuItemsParent->ChildItems+PDisMenuItemsParent->SelectedIndex);								
				if(temp->DecimalPlaces > 0)
					dotindex = temp->DecimalPlaces + 1;			
				if(temp->type == editor && temp->status==editting && temp->ActiveIndex != (temp->maxVal - dotindex))
				{	
					if(temp->ActiveIndex==0)
					{
						if(temp->Value[temp->ActiveIndex]==0)
							temp->Value[temp->ActiveIndex]=1;
						else
							temp->Value[temp->ActiveIndex]=0;
					}
					else
					{
						if(temp->Value[temp->ActiveIndex]<9)
							temp->Value[temp->ActiveIndex]++;
						else
							temp->Value[temp->ActiveIndex]=0;
					}
					CheckValChanged(temp);
				}
				if(temp->type == pwdEditor && temp->status==editting)
				{
					if(temp->Value[temp->ActiveIndex]<'0'//48
					   ||(temp->Value[temp->ActiveIndex]>'9'//57
						  && temp->Value[temp->ActiveIndex]<'A'//65
							  )
						   ||temp->Value[temp->ActiveIndex]>'Z'//90
							   )
						temp->Value[temp->ActiveIndex]='0';//48;
					else if(temp->Value[temp->ActiveIndex]=='9')
						temp->Value[temp->ActiveIndex]='A';//90;						
					else if(temp->Value[temp->ActiveIndex]=='Z')//65)
						temp->Value[temp->ActiveIndex]='0';//57;
					else
						temp->Value[temp->ActiveIndex]++;
				}
		#if defined(LCD_MODULE_128_64_ST5668A)
				//if ((PDisMenuItemsParent->ChildItems)->type == radiocheckbox)
				if (SubMenuHaveRadiocheckbox(PDisMenuItemsParent))
				{
					radiocheckbox_offset = INDICATE_AREAS_WIDTH;
				}
		#endif
				bNeedRefresh = 0;
			}
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 1;
		break;
	}
	
}

#ifdef FUNC_MAINTAIN
static void Btn_Maintain_RaisedEvent(enum KeyEventEnum keyEvent)
{
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		{
			INT8U err;
			OSSemPost(MenuSem);
			UIAction_Maintain(0);
			OSSemPend(MenuSem, 0, &err);
		}
		bNeedRefresh = 1;
		break;
	}
}
#endif

#if defined(QICAIHONG)
//========================================================================
// ����: static void Btn_AdvanceModeOrCalibrationMenu_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: Btn_AdvanceModeOrCalibrationMenu�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2013/12/27      First version
//========================================================================
static void Btn_AdvanceModeOrCalibrationMenu_RaisedEvent(enum KeyEventEnum keyEvent)
{
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
		case Menu:
			OpenAdvanceModemenu();
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 1;
		break;
	}
}

//========================================================================
// ����: static void Btn_MeadiaTypeMenu_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: MeadiaTypeMenu�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2013/12/27      First version
//========================================================================
static void Btn_MeadiaTypeMenu_RaisedEvent(enum KeyEventEnum keyEvent)
{
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
		case Menu:
			OpenMediaTypemenu();
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 1;
		break;
	}
}

//========================================================================
// ����: static void Btn_HeaterMenu_RaisedEvent(enum KeyEventEnum keyEvent)
// ����: HeaterMenu�������¼��������
// ����: keyEvent �¼�����
//		
// ����: ��
// ��ע: ��
// �汾:
//      2013/12/27      First version
//========================================================================
static void Btn_HeaterMenu_RaisedEvent(enum KeyEventEnum keyEvent)
{
	switch(keyEvent)
	{
	case KeyDown:
		switch(CurrentDisMode)
		{
		case MainScreen:
			// to do ...
			break;
		case Menu:
			// to do ...
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 0;
		break;
	case KeyUp:
		switch(CurrentDisMode)
		{
		case MainScreen:
		case Menu:
			OpenHeaterMenu();
			break;
		case Edit:
			// to do ...
			break;
		case Reserved:
			// to do ...
			break;
		}
		bNeedRefresh = 1;
		break;
	}
}
#endif

#define LCD_BUSY_STATE  0x20000000
void Init_Lcd_Cmd_Q(void)
{
	//  INT8U err = 0;
	//	Lcd_Cmd_Num = 0;
	//	OSFlagPost(mix_FLAG_GRP, LCD_BUSY_STATE, OS_FLAG_CLR, &err);
}
void Send_Lcd_Cmd_Q(void)
{
	INT8U ret = 0;
	INT8U err = 0;
	extern OS_EVENT *LCDSem;
	
	if(Lcd_Cmd_Num== 0)
		return;
	
	OSSemPend(LCDSem, 0, &err);
	
	IIC_Write_LCD();	
	OSFlagPend(mix_FLAG_GRP, LCD_BUSY_STATE, OS_FLAG_WAIT_SET_ANY|OS_FLAG_CONSUME, 1000, &err);
	if(err != OS_NO_ERR) //only for debug
		OSTimeDly(100);
	
	OSSemPost(LCDSem);
	
	Lcd_Cmd_Num = 0;
}
extern INT8U DO_NOT_ANSWER_KEY ;
//========================================================================
// ����: void PutChar(unsigned char x,unsigned char y,unsigned char a)
// ����: д��һ����׼ASCII�ַ�
// ����: nKeyID  ��ֵid
//		 keyEvent  �¼�ö��ֵ
// ����: ��
// ��ע: ��
// �汾:
//      2010/08/13      First version
//========================================================================
INT8U LCD_SendKey(unsigned int nKeyID,enum KeyEventEnum keyEvent)
{
	//  int x,y;
	enum KeyIDEnum mkeyid = (enum KeyIDEnum)nKeyID;
	INT8U err;
	if(DO_NOT_ANSWER_KEY == True)
	{
		return 0;
	}
	OSSemPend(MenuSem, 0, &err);
	switch(mkeyid)
	{
	case Btn_Width:
		Btn_Width_RaisedEvent(keyEvent);
		break;
	case Btn_Menu:			
		Btn_Menu_RaisedEvent(keyEvent);
		break;
	case Btn_Enter:			
		Btn_Enter_RaisedEvent(keyEvent);
		break;
	case Btn_Cleaning:
#if defined(MANUFACTURER_TATE_EPSON_UV)&&defined(HEAD_RICOH_G4)&&defined(RIPSTAR_FLAT_EX)	
		Btn_PrintQuality_RaisedEvent(keyEvent);
#else
		Btn_Cleaning_RaisedEvent(keyEvent);
#endif
		break;
	case Btn_Pause_resume:
		Btn_Pause_resume_RaisedEvent(keyEvent);
		break;
	case Btn_Abort:
		Btn_Abort_RaisedEvent(keyEvent);
		break;
	case Btn_Checknozzle:
		Btn_Checknozzle_RaisedEvent(keyEvent);
		break;
	case Btn_Move_left:
		Btn_Move_left_RaisedEvent(keyEvent);
		break;
	case Btn_Move_right:
		Btn_Move_right_RaisedEvent(keyEvent);
		break;
	case Btn_Move_forward:
		Btn_Move_forward_RaisedEvent(keyEvent);
		break;
	case Btn_Move_backward:
		Btn_Move_backward_RaisedEvent(keyEvent);
		break;
	case Btn_BASEPOINT:
		Btn_BasePoint_RaisedEvent(keyEvent);
		break;
	case Btn_SHEETCUT:
#if defined(QICAIHONG)
		// open advance menu
		Btn_AdvanceModeOrCalibrationMenu_RaisedEvent(keyEvent);
#else
		Btn_SheetCut_RaisedEvent(keyEvent);
#endif
		break;
	case Btn_PRINTQUALITY:
#if defined(MANUFACTURER_TATE_EPSON_UV)&&defined(HEAD_RICOH_G4)&&defined(RIPSTAR_FLAT_EX)	
		Btn_Cleaning_RaisedEvent(keyEvent);
#elif defined(QICAIHONG)
		// open media type menu
		Btn_MeadiaTypeMenu_RaisedEvent(keyEvent);
		//Btn_HeaterMenu_RaisedEvent(keyEvent);  // for test heater
#else
		Btn_PrintQuality_RaisedEvent(keyEvent);
#endif		
		break;
#ifdef FUNC_MAINTAIN
	case Btn_Maintain:
		Btn_Maintain_RaisedEvent(keyEvent);
		break;
#endif	
#if defined(QICAIHONG)
	case Btn_HEATER:
		// open heater menu
		Btn_HeaterMenu_RaisedEvent(keyEvent);
		break;
#endif	
	default:
		//#error excepted KeyID
		break;
	}	
	if((bNeedRefresh == 1)&&(Can_Not_Need_Refresh != True))
	{
		RefreshScreen(PDisMenuItemsParent->LastFirstIndex, PDisMenuItemsParent,CurrentDisMode);
		bNeedRefresh = 0;
	}
	else if(Can_Not_Need_Refresh == True)
	{
		Can_Not_Need_Refresh = False;
	}
	Send_Lcd_Cmd_Q();
	//OSSemPost(Lcd_Cmd);
	OSSemPost(MenuSem);
	return 0;
}

//========================================================================
// ����: void LCD_SetDisStatus(StatusTypeEnum status, int errorcode, int percent, void * extraInfo)
// ����: ������������ʾ��״̬
// ����: status  ״̬ö��ֵ
//		 errorcode  �����
//       percent    �ٷֱ�
//       extraInfo  ״ֵ̬
// ����: ��
// ��ע: ��
// �汾:
//      2010/08/13      First version
//========================================================================
INT8U LCD_SetDisStatus(enum StatusTypeEnum status, INT32U errorcode, INT8U percent, void * extraInfo)
{
	INT8U err;
	OSSemPend(MenuSem, 0, &err);
	//OSSemPend(Lcd_Cmd, 0, &err);
	//Init_Lcd_Cmd_Q();
	CurrentStatus = status;
	sprintf(MainInfo_percent, "%d%%",(INT32U)percent);
	sprintf(MainInfo_errorcode, "%d",errorcode);
	//����Ӣ����ʾ�ִ�
	GetStatus_EN(status,&(PMainScreen->ChildItems+0)->Text_en);
	(PMainScreen->ChildItems+1)->Text_en = MainInfo_percent;
	(PMainScreen->ChildItems+2)->Text_en = MainInfo_errorcode;
	(PMainScreen->ChildItems+7)->Text_en = extraInfo;
	//����������ʾ�ִ�
	GetStatus_CHS(status,&(PMainScreen->ChildItems+0)->Text_ch);//st
	GetPercent_CHS(MainInfo_percent);
	GetErrorCode_CHS(errorcode);
#ifdef LCD_MODULE_ZX19264M1A
	(PMainScreen->ChildItems+2)->Text_ch = (unsigned short *)MainInfo_errorcode;
#endif
	GetErrorInfo_CHS(errorcode, &(PMainScreen->ChildItems+7)->Text_ch);
	
	if(CurrentDisMode == MainScreen)
		DrawMainScreen(CurrentStatus,PMainScreen);
	
	Send_Lcd_Cmd_Q();
	//OSSemPost(Lcd_Cmd);
	OSSemPost(MenuSem);
	//	RefreshScreen(0, 0, PMainScreen, CurrentDisMode);
	return 0;
}
void Menu_BiDir_Changed(void)
{
#if defined(RIPSTAR_FLAT_EX)&&(defined(MANUFACTURER_DYSS)||defined(FULGENCY_FUN_6SPEED))
	if(LCDMenuConfig_EX.Calc_X_Speed == 0)
	{
		strcpy(MenuStr_UM_4_ID30_Print, "��ӡ(����)");
		strcpy(MenuStr_UM_4_ID30_Print_EN,"Print (Low Speed)");
	}
	else if(LCDMenuConfig_EX.Calc_X_Speed == 1)
	{
		strcpy(MenuStr_UM_4_ID30_Print, "��ӡ(����)");
		strcpy(MenuStr_UM_4_ID30_Print_EN,"Print (Middle Speed)");
	}
	else
	{
		strcpy(MenuStr_UM_4_ID30_Print, "��ӡ(����)");
		strcpy(MenuStr_UM_4_ID30_Print_EN,"Print (High Speed)");
	}
#else
	if(MainInfo_HeadHeightLevel[0] == 0x33)
	{
		strcpy(MenuStr_UM_4_ID30_Print, "��ӡ(��)");
		strcpy(MenuStr_UM_4_ID30_Print_EN,"Print(Low)");
	}
	else
	{
		strcpy(MenuStr_UM_4_ID30_Print, "��ӡ(��)");
		strcpy(MenuStr_UM_4_ID30_Print_EN,"Print(High)");
	}
	if(((PDisMenuItemsParent ->ChildItems)->Text_ch == (unsigned short *)MenuStr_UM_4_ID30_Print) &&(CurrentDisMode == Menu))
	{
		bNeedRefresh = 1;
	}
#endif		
}
void Display_Inf(CHAR * inf)
{
	LCD_ClearScreen();
	LCD_DrawText(0,0,inf);
}

/*
* ��һ��С��ת����һ���ַ���
* str:�洢ת������ַ���
* src:Ҫ����ת����С��
* decimal:Ҫ������С��λ��
* return������ת������ַ���
* note:Ŀǰ��֧�ָ���
*/
static char *floatToStr(char *str, double src,int decimal)   
{   
	int decp = 1;   
	char *s = str;
	int loop = 0;
	
	if(str == NULL || decimal < 0)
		return NULL;
	
	for(loop = 0; loop < decimal; loop++)
		src *= 10;
	
	src = src + 0.5;		//��һ����Чλ����������
	
	for(loop = 0; loop < decimal; loop++)
		src /= 10;
	if(src >= 0.0)				//������ʱ��   
	{   
		while(src >= 10.0)		//��С����λ�á�   
		{   
			decp++;   
			src /= 10;   
		}   
		for(loop = 0;loop < 8; loop++)   
		{   
			if(loop == decp && decimal >= 0)   
			{   
				if(decimal == 0)	//�������С�����Ϊ0λ�����˳�
					break;
				s[loop]= '.';		//���С����
				continue;   
			}   
			
			s[loop] = (int)src;   
			src -= s[loop];   
			s[loop] += '0';			//����������ת����ascii�ַ�����
			src*=10.0;
			
			if(loop >= decp)		//��������꣬����С��������
			{
				decimal --;
				if(decimal <= 0)	//С��λ��乻���˳�
					break;
			}
		}   
		return(str);   
	}
}

extern void Set_PrintQuality(INT8U index);
//========================================================================
// ����: INT8U LCD_SetMainInfo(enum InfoTypeEnum infoType, void * value)
// ����: ������������ʾ��media��ȣ�head�߶ȣ������ã���ϴǿ�ȣ����ݽ�����ʾ����Ϣ
// ����: infoType  ��Ϣ���
//		 value  ��Ϣֵ
// ����: ��
// ��ע: ��
// �汾:
//      2010/08/13      First version
//========================================================================
INT8U LCD_SetMainInfo(enum InfoTypeEnum infoType, void * value)
{
	//  int i,x,y;	
	//  i = -1;
	INT8U err;
	OSSemPend(MenuSem, 0, &err);
	//OSSemPend(Lcd_Cmd, 0, &err);
	Init_Lcd_Cmd_Q();
	switch(infoType)
	{
	case E_IT_MediaWidth://value is float *. unit is inch.
		memset(MainInfo_MediaWidth, 0, sizeof(MainInfo_PrintOrigin));
		floatToStr(MainInfo_MediaWidth, (*(__packed float*)value)*2.54, 2);
		break;
	case E_IT_PrintOrigin://value is float *. unit is inch.
		memset(MainInfo_PrintOrigin, 0, sizeof(MainInfo_PrintOrigin));
		floatToStr(MainInfo_PrintOrigin, (*(__packed float*)value)*2.54, 2);
		break;
#ifdef RIPSTAR_FLAT_EX
	case E_IT_PrintZOrigin://value is float *. unit is inch.
		sprintf(MainInfo_ZOrigin, "%.2f", (*(__packed float*)value)*2.54);
		break;
	case E_IT_MediaLength://value is float *. unit is inch.
		sprintf(MainInfo_MediaLength, "%.2f", (*(__packed float*)value)*2.54);
		break;
	case E_IT_PrintYOrigin://value is float *. unit is inch.
		sprintf(MainInfo_YOrigin, "%.2f", (*(__packed float*)value)*2.54);
		break;
#endif
	case E_IT_PassNum://value is INT8U *.
		sprintf(MainInfo_PassNum, "%d",*(INT8U*)value);
		break;	
	case E_IT_Resolution: //value is INT16U *.	  	
		sprintf(MainInfo_Resolution, "%d",*(INT16U*)value);
		break;	
	case E_IT_PrinterName: //value is C string. 	  	
		sprintf(MainInfo_PrinterName, "%s",(CHAR*)value);
		break;
	case E_IT_ManufactureName: //value is C string. 	  	
		sprintf(MainInfo_ManufactureName, "%s",(CHAR*)value);
		break;
	case E_IT_HeadHeightLevel://value is INT8U *. the valid value is 1,2,3(high, middle, low). 	  	
#ifndef RIPSTAR_FLAT_EX
		sprintf(MainInfo_HeadHeightLevel, "%d",*(INT8U*)value);
#endif
		Menu_BiDir_Changed();
		break;
	case E_IT_QualitySetting://value is INT8U *. the valid value is 0,1,2(OFF/type1/type2). 	  	
		sprintf(MainInfo_QualitySetting, "%d",*(INT8U*)value);
		Set_PrintQuality(*(INT8U*)value);
		break;
	case E_IT_CleaningStrong://value is INT8U *. the valid value is 1,2,3(weak, normal, strong). 	  	
		sprintf(MainInfo_CleaningStrong, "%d",*(INT8U*)value);
		break;
	case E_IT_DataReceiving://value is INT8U *. the valid value is 0,1(FALSE/TRUE). 	  	
		sprintf(MainInfo_DataReceiving, "%d",*(INT8U*)value);
		break;
	case E_IT_Busy://value is INT8U *. the valid value is 0,1(FALSE/TRUE). 	  	
		//sprintf(MainInfo_Busy, "%d",*(INT8U*)value);
		if(*(INT8U*)value == 0)
			UI_DisplayLED(E_LI_Busy, E_LS_OFF);
		else
			UI_DisplayLED(E_LI_Busy, E_LS_ON);
		break;	
	case E_IT_DIS_INF:
		Display_Inf((CHAR *)value);
		Send_Lcd_Cmd_Q();
		OSTimeDly(3000);
		bNeedRefresh = 1;
		break;	
	default:
		//OSSemPost(Lcd_Cmd);
		OSSemPost(MenuSem);
		return False;
	}
	if(CurrentDisMode == MainScreen)
		DrawMainScreen(CurrentStatus,PMainScreen);
	else if(CurrentDisMode == Menu)
	{
		if( bNeedRefresh == 1)
		{
			RefreshScreen(PDisMenuItemsParent->LastFirstIndex, PDisMenuItemsParent,CurrentDisMode);
			bNeedRefresh = 0;
		}
	}
	Send_Lcd_Cmd_Q();
	//OSSemPost(Lcd_Cmd);
	OSSemPost(MenuSem);
	return True;
}
extern void Change_Unit_For_Language(void);
#if !(defined (DYSS_UV_CLEAN) ||defined (RICOH_3H))      
char group1_chs[] = "��1";
char group2_chs[] = "��2";
char groupAll_chs[] = "��1��2";
char group1_en[] = "Group1";
char group2_en[] = "Group2";
char groupAll_en[] = "Group1&2";
#endif
char closeGroup1_chs[] = "�ر���1";
char closeGroup2_chs[] = "�ر���2";
char closeGroup1_en[] = "Disable Group1";
char closeGroup2_en[] = "Disable Group2";

char DataChNO2DriverNO_EPSON_Gen5_2H[] = {
	0,1,2,3
};
char DataChNO2DriverNO_RICOH_G4P_8H[] = {
	0,1,2,3,4,5,6,7
};
#if defined(EPSON_4H)||defined(HEAD_RICOH_G4)
INT8U IS_SAME(char* str1,char *str2,INT8U len)
{
	INT8U i = 0;
	if(str1 == str2)
		return False;
	while(i < len)
	{
		if( *(str1 + i) != *(str2 + i))
			return False;
		i++;
	}
	return True;
}
INT8U Find_last_color(INT8U channel,char * str, INT8U len)
{
	INT8U i,j,k;
	if(MAX_HEAD_DRIVE_NUM != channel)
	{
		for( j = 0;j < MAX_HEAD_PARAM_NAME;j++)
		{
			if(MenuStr_EM_4_ID1C8[channel][j] != 0 && IS_SAME(&MenuStr_EM_4_ID1C8[channel][j],str,len))	
				return True;
		}
		return False;
	}
	else
	{
		for( i = 0;i < MAX_HEAD_DRIVE_NUM;i++)
		{
			for( j = 0;j < MAX_HEAD_PARAM_NAME;j++)
			{
				if(MenuStr_EM_4_ID1C8[i][j] != 0 && IS_SAME(&MenuStr_EM_4_ID1C8[i][j],str,len))	
					k++;
			}
		}
		return k;
	}
}
#endif
void UpdateHeadParamName()
{
	INT8U i,j,k,m,driver_num;
#ifdef EPSON_4H
	MI_0_ID00_MenuChilds[11].Visible = 1;
	driver_num = MAX_HEAD_DRIVE_NUM;
#else
	if(factoryData.HeadType == HeadNo_Epson_Gen5 && headboardInfo.headBoardType == HEAD_BOARD_TYPE_EPSON_GEN5_2HEAD)
	{
		MI_0_ID00_MenuChilds[11].Visible = 1;
		driver_num = 4;
	}
	else if((factoryData.HeadType == HeadNo_Ricoh_Gen4_64Pin || factoryData.HeadType == HeadNo_Ricoh_Gen4_G4 ||
			 factoryData.HeadType == HeadNo_Ricoh_Gen4_G4L) && headboardInfo.headBoardType == HEAD_BOARD_TYPE_RICOH_GEN4_64Pin_8H)
	{
		MI_0_ID00_MenuChilds[11].Visible = 1;
#ifdef RICOH_G4_16H
		driver_num = 16;
#else		
		driver_num = 8;
#endif
	}
	else if((factoryData.HeadType == HeadNo_Ricoh_Gen4_64Pin || factoryData.HeadType == HeadNo_Ricoh_Gen4_G4 ||
			 factoryData.HeadType == HeadNo_Ricoh_Gen4_G4L) && headboardInfo.headBoardType == HEAD_BOARD_TYPE_RICOH_GEN4_3H)
	{
		MI_0_ID00_MenuChilds[11].Visible = 1;
		driver_num = 3;
	}
	else if(factoryData.HeadType == HeadNo_Ricoh_Gen5_2C_100Pin)
	{
		MI_0_ID00_MenuChilds[11].Visible = 1;
		driver_num = MAX_HEAD_DRIVE_NUM;
	}
	else
		return;
#endif
	for(i=0; i<MAX_HEAD_DRIVE_NUM; i++)
	{
		MenuStr_EM_4_ID1C8[i][0] = 0;
		MenuStr_EM_4_ID1C8_E[i][0] = 0;
	}
	
	for(i=0; i<epsonCaliSetting.printerSetting.ColorCount; i++)
	{
#if defined(EPSON_4H)||defined(HEAD_RICOH_G4)
		INT8U	j,k,g;
		for(g = 0; g < epsonCaliSetting.printerSetting.GroupCount_YContinue; g++ )
		{
			for(k = 0; k < epsonCaliSetting.printerSetting.YInterleaveNum; k++ )
			{
				INT8U colorCode = factoryDataEx.m_nColorOrder[i];
				INT8U lineNo = GetNozzleLineIndex(colorCode, k);
				INT8U HeadNo = GetHeadIndexWithInterleave(g, colorCode, k);
				INT8U GroupNo = g+ (k%epsonCaliSetting.printerSetting.GroupCount_YInterleave)*epsonCaliSetting.printerSetting.GroupCount_YContinue;
				INT8U Channle = epsonCaliSetting.colorMap.ColorIndex2DataChannelIndex[HeadNo][lineNo];
#ifdef HEAD_RICOH_G4
#if defined(RICOH_G5_3H)||defined(RICOH_G5_4H)
				INT8U Menu_Channle = Channle;
#else
				INT8U Menu_Channle = Channle/2 ;
#endif
#else
				INT8U Menu_Channle = (Channle%8)/2 +(Channle/16)*4;
#endif
				INT8U DIS_HEAD_NUM =True;
				INT8U DIS_COLOR_NUM =True;
				INT8U j_base = 0,color_tmp = 0,comma = 0;
				j=0;
				while(MenuStr_EM_4_ID1C8[Menu_Channle][j] != 0)
					j++;
				j_base = j; 		
				if(j!= 0)
				{
					MenuStr_EM_4_ID1C8[Menu_Channle][j] = ',';
					MenuStr_EM_4_ID1C8_E[Menu_Channle][j] = ',';
					j++;
					comma = 1;
				}
				if( EPSON_ACTIVE_GROUPNUM == 1)
				{
					DIS_HEAD_NUM = False;
				}
				else
				{
					DIS_HEAD_NUM = True;
				}
				if((factoryDataEx.LayoutType & 0x2) == 0)
				{
					DIS_COLOR_NUM = False;
				}
				else
				{
					DIS_COLOR_NUM = True;
				}
#if defined(RICOH_G5_3H)||defined(RICOH_G5_4H)
				DIS_COLOR_NUM = True;
#endif
				if(DIS_HEAD_NUM)
				{
					if(GetGroupHeadNumber()==1)
					{ 
						MenuStr_EM_4_ID1C8[Menu_Channle][j] = 'H';
						MenuStr_EM_4_ID1C8_E[Menu_Channle][j] = 'H';
						j++;
						MenuStr_EM_4_ID1C8[Menu_Channle][j] = '1' + HeadNo;
						MenuStr_EM_4_ID1C8_E[Menu_Channle][j] = '1' + HeadNo;							
					}
					else
					{ 
						MenuStr_EM_4_ID1C8[Menu_Channle][j] = 'G';
						MenuStr_EM_4_ID1C8_E[Menu_Channle][j] = 'G';
						j++;
						MenuStr_EM_4_ID1C8[Menu_Channle][j] = '1' + GroupNo;
						MenuStr_EM_4_ID1C8_E[Menu_Channle][j] = '1' + GroupNo;		
					}
					j++;			
				}
				if(factoryDataEx.m_nColorOrder[i] >= COLORCODE_SPOTCOLOR0 && factoryDataEx.m_nColorOrder[i] <= COLORCODE_SPOTCOLOR3)
				{
					color_tmp = factoryDataEx.m_nColorOrder[i] - COLORCODE_SPOTCOLOR0;
					color_tmp = LCDMenuConfig.SpotColorName[color_tmp];
					INT8U * pName = GetPrintedSpotColorName(color_tmp);
					
					for(color_tmp=0; pName[color_tmp] != 0; color_tmp++)
					{
						MenuStr_EM_4_ID1C8[Menu_Channle][j] = pName[color_tmp];
						MenuStr_EM_4_ID1C8_E[Menu_Channle][j] = pName[color_tmp];
						j++;
					}
				}
				else
				{
					MenuStr_EM_4_ID1C8[Menu_Channle][j] = factoryDataEx.m_nColorOrder[i];
					MenuStr_EM_4_ID1C8_E[Menu_Channle][j] = factoryDataEx.m_nColorOrder[i];
					j++;
				}
				INT8U is_zero = 0;
				if(MenuStr_EM_4_ID1C8[Menu_Channle][j_base] == ',')
					is_zero = 1;
				
				if(DIS_COLOR_NUM)
				{
					color_tmp = Find_last_color(MAX_HEAD_DRIVE_NUM,&MenuStr_EM_4_ID1C8[Menu_Channle][j_base + is_zero],j - j_base - comma);
					
					{
						MenuStr_EM_4_ID1C8[Menu_Channle][j] = '0' + color_tmp;
						MenuStr_EM_4_ID1C8_E[Menu_Channle][j] = '0' + color_tmp;
					}
				}
				else
				{
					if(Find_last_color(Menu_Channle,&MenuStr_EM_4_ID1C8[Menu_Channle][j_base + is_zero],j - j_base - comma))
					{
						MenuStr_EM_4_ID1C8[Menu_Channle][j_base] = 0;
						MenuStr_EM_4_ID1C8_E[Menu_Channle][j_base] = 0;
						j = j_base;
					}				
				}
				
			}				
		}
#else
		INT8U last_d;
		for(m=0; m<epsonCaliSetting.printerSetting.GroupCount; m++)
		{
			INT8U h = GetHeadIndex(m, factoryDataEx.m_nColorOrder[i]);
			INT8U l = GetNozzleLineIndex(factoryDataEx.m_nColorOrder[i], 0);
			INT8U d = epsonCaliSetting.colorMap.ColorIndex2DataChannelIndex[h][l];
			
			if(factoryData.HeadType == HeadNo_Epson_Gen5 && headboardInfo.headBoardType == HEAD_BOARD_TYPE_EPSON_GEN5_2HEAD)
				d = d%8;
			d /= NOZZLE_BIT_WIDTH;
			if(factoryData.HeadType == HeadNo_Epson_Gen5 && headboardInfo.headBoardType == HEAD_BOARD_TYPE_EPSON_GEN5_2HEAD)
				d = DataChNO2DriverNO_EPSON_Gen5_2H[d];
			else
				d = DataChNO2DriverNO_RICOH_G4P_8H[d];
			
			if(m==0)
				last_d = d;
			else if(last_d == d)
				continue;
			
			j=0;
			while(MenuStr_EM_4_ID1C8[d][j] != 0)
				j++;
			if(j!= 0)
			{
				MenuStr_EM_4_ID1C8[d][j] = ',';
				MenuStr_EM_4_ID1C8_E[d][j] = ',';
				j++;
			}
			if( epsonCaliSetting.printerSetting.GroupCount > 1 &&
			   epsonCaliSetting.printerSetting.HeadCount > 2)
			{
				if(epsonCaliSetting.printerSetting.head_group == 1)
				{ //for epson 4H 4C
					MenuStr_EM_4_ID1C8[d][j] = 'H';
					MenuStr_EM_4_ID1C8_E[d][j] = 'H';
					j++;
				}
				else
				{ //for ricoh. and epson 4H 8C.
					MenuStr_EM_4_ID1C8[d][j] = 'G';
					MenuStr_EM_4_ID1C8_E[d][j] = 'G';
					j++;
				}
				MenuStr_EM_4_ID1C8[d][j] = '1'+m;
				MenuStr_EM_4_ID1C8_E[d][j] = '1'+m;
				j++;
			}
			if(factoryDataEx.m_nColorOrder[i] >= COLORCODE_SPOTCOLOR0 && factoryDataEx.m_nColorOrder[i] <= COLORCODE_SPOTCOLOR3)
			{
				k = factoryDataEx.m_nColorOrder[i] - COLORCODE_SPOTCOLOR0;
				k = LCDMenuConfig.SpotColorName[k];
				INT8U * pName = GetPrintedSpotColorName(k);
				
				for(k=0; pName[k] != 0; k++)
				{
					MenuStr_EM_4_ID1C8[d][j] = pName[k];
					MenuStr_EM_4_ID1C8_E[d][j] = pName[k];
					j++;
				}
			}
			else
			{
				MenuStr_EM_4_ID1C8[d][j] = factoryDataEx.m_nColorOrder[i];
				MenuStr_EM_4_ID1C8_E[d][j] = factoryDataEx.m_nColorOrder[i];
				j++;
			}
			
			MenuStr_EM_4_ID1C8[d][j] = 0;
			MenuStr_EM_4_ID1C8_E[d][j] = 0;
		}
#endif				
	}
	
	for(i=0; i<MAX_HEAD_DRIVE_NUM; i++)
	{
		if(i<driver_num)
		{
			MI_EM_1_ID3F3_Nozzleparameter[i].Visible = 1;
			if( MenuStr_EM_4_ID1C8[i][0] == 0)
			{
				MenuStr_EM_4_ID1C8[i][0] = 'N';
				MenuStr_EM_4_ID1C8_E[i][0] = 'N';
				MenuStr_EM_4_ID1C8[i][1] = 'C';
				MenuStr_EM_4_ID1C8_E[i][1] = 'C';
				MenuStr_EM_4_ID1C8[i][2] = 0;
				MenuStr_EM_4_ID1C8_E[i][2] = 0;
#ifdef MANUFACTURER_DYSS
				MI_EM_1_ID3F3_Nozzleparameter[i].Visible = 0;
#endif
			}
		}
		else
			MI_EM_1_ID3F3_Nozzleparameter[i].Visible = 0;
	}
	
}
void Set_Clean_Dis(void)
{
	if(GetGroupHeadNumber() == 1 && EPSON_PERMIT_GROUPNUM == 4)
	{
#ifdef EPSON_4H_CLEAN_SPLIT
		CLEAN_head_group = 1;
		if(UILanguage == en)
		{		
			sprintf(MenuStr_Clean_Color_Name_E[0],"Head 1");
			sprintf(MenuStr_Clean_Color_Name_E[1],"Head 2");
			sprintf(MenuStr_Clean_Color_Name_E[2],"Head 3");
			sprintf(MenuStr_Clean_Color_Name_E[3],"Head 4");
		}
		else
		{
			sprintf(MenuStr_Clean_Color_Name[0],"ͷ 1");
			sprintf(MenuStr_Clean_Color_Name[1],"ͷ 2");
			sprintf(MenuStr_Clean_Color_Name[2],"ͷ 3");
			sprintf(MenuStr_Clean_Color_Name[3],"ͷ 4");
		}
#else
		if(UILanguage == en)
		{
			sprintf(MenuStr_ALLWIN_UM_3_CleanHead1_E,"Head 1,3");
			sprintf(MenuStr_ALLWIN_UM_3_CleanHead2_E,"Head 2,4");
			sprintf(MenuStr_ALLWIN_UM_3_CleanHeadAll_E,"All Head");
		}
		else
		{
			sprintf(MenuStr_ALLWIN_UM_3_CleanHead1,"��ͷ1,3");
			sprintf(MenuStr_ALLWIN_UM_3_CleanHead2,"��ͷ2,4");
			sprintf(MenuStr_ALLWIN_UM_3_CleanHeadAll,"��ͷ1,2,3,4");
		}
		CLEAN_head_group = 2;
#endif		
	}
	else if(GetGroupHeadNumber() ==  2 && EPSON_PERMIT_GROUPNUM == 2)
	{
		
	}
}
#ifdef RIPSTAR_FLAT_EX
extern void RIPSTAR_FLAT_INIT(void);
#endif

#if defined(MANUFACTURER_DYSS)||defined(FULGENCY_FUN)
extern void RICOH_VSD34_INIT(void);
#endif
#ifdef DYSS_UV_CLEAN
extern void RICOH_DYSS_CLEAN_DIS_INIT(void);
#endif
#ifdef RICOH_G4_16H
void CONVERSION_BOARD_DIS_INIT(void)
{
	for(INT8U i = 8; i < MAX_HEAD_DRIVE_NUM;i++)
	{
		MI_EM_1_ID3F3_Nozzleparameter[i] = MI_EM_1_ID3F3_Nozzleparameter[0];
		MI_EM_1_ID3F3_Nozzleparameter[i].Index = i;
		MI_EM_1_ID3F3_Nozzleparameter[i].ActionParameters = i;
		MI_EM_1_ID3F3_Nozzleparameter[i].Text_ch = (unsigned short *)&MenuStr_EM_4_ID1C8[i];
		MI_EM_1_ID3F3_Nozzleparameter[i].Text_en = (char *)&MenuStr_EM_4_ID1C8_E[i];
	}
}
#endif
//========================================================================
// ����: void Initial_Dis()
// ����: ��ʼ����ʾ�߼���ָ�����
// ����: ��
// ����: ��
// ��ע: ��
// �汾:
//      2010/08/13      First version
//========================================================================
void Initial_Dis()
{
	INT8U groupnum = 0, grouphead = 0, j,k,l,m;
	INT8U colornum = 0;
	INT8U isWeakSolventprinter = 0;
	MenuSem = OSSemCreate(1);             /* Random number semaphore */
	//Lcd_Cmd = OSSemCreate(1);
	PMainScreen = &MainScreenRoot;
	PDisMenuItemsParent = &MainMenuRoot;
	
	Initial_Menu(PDisMenuItemsParent);
	GetUILanguage(0,0);//��ȡ��ǰ�˵���ʾ����
	//StartFlickerTask(); //not used.
	/*��ȡ��ǰ״̬��Ϣ,���ò˵�����ʾ*/
	//��ȡ��ʾģʽ��ģʽ�͸߼�ģʽ
	//IsAdvancedMode = 1;//to do
	SwitchMenuMode_S_A(IsAdvancedMode);
	
	//��ȡͷ��,��ɫ��
	//Printer configure part
	groupnum = GetGroupNumber();
	grouphead = GetGroupHeadNumber();
	colornum = GetColorNumber();
	isWeakSolventprinter = IsWeakSolventPrinter();
#ifdef RICOH_G4_16H
	CONVERSION_BOARD_DIS_INIT();
#endif
#ifdef RIPSTAR_FLAT_EX
	RIPSTAR_FLAT_INIT();
	LCD_SetMainInfoEx(E_IT_HeadHeightLevel, 0);	
#endif
	
#if defined( MANUFACTURER_ALLWIN_EPSON)||defined( MANUFACTURER_ALLWIN_FLAT)||defined(MANUFACTURER_ALLWIN_2H_ROLL_UV)||defined(RICOH_G4_16H)
	LCD_SetMainInfoEx(E_IT_HeadHeightLevel, 0);
	LCDMenuConfig.Head_Height_Level = 0;
#endif
	
#if defined(MANUFACTURER_DYSS)||defined(FULGENCY_FUN)
	RICOH_VSD34_INIT();
#endif
#ifdef DYSS_UV_CLEAN
	RICOH_DYSS_CLEAN_DIS_INIT();
#endif
		
#ifdef DGEN_AUTOFUCTION
	LCDMenuConfig.AutoLoad = 0;
	LCDMenuConfig.AutoPlateFan = 0;
	LCDMenuConfig.AutoPowerOnClean = 0;
	MI_1_ID0D_OriginAndMediaWidth[7].Visible = 0;
	MI_1_ID0D_OriginAndMediaWidth[5].Visible = 1;
	MI_1_ID0D_OriginAndMediaWidth[6].Visible = 1;
	MI_MICOLOR_EM_1_ID16_SetAutofunction[2].Visible = 0;
	MI_MICOLOR_EM_1_ID16_SetAutofunction[5].Visible = 0;
	MI_MICOLOR_EM_1_ID16_SetAutofunction[7].Visible = 0;
#endif
	
	if(!IsIntegradeHead())
	{
#ifdef EPSON_CLEAN_UPDOWN_TATE_8H_RICOH
		MenuStr_Clean_Color_Name[0][0] =  MenuStr_Clean_Color_Name_E[0][0] =factoryDataEx.m_nColorOrder[3];
		MenuStr_Clean_Color_Name[1][0] =  MenuStr_Clean_Color_Name_E[1][0] =factoryDataEx.m_nColorOrder[2];
		MenuStr_Clean_Color_Name[2][0] =  MenuStr_Clean_Color_Name_E[2][0] =factoryDataEx.m_nColorOrder[1];
		MenuStr_Clean_Color_Name[3][0] =  MenuStr_Clean_Color_Name_E[3][0] =factoryDataEx.m_nColorOrder[0];
#else    
		//for head selection for clean head.
#if !(defined (DYSS_UV_CLEAN) ||defined (RICOH_3H))      
		memcpy(MenuStr_ALLWIN_UM_3_CleanHead1, group1_chs, sizeof(group1_chs));
		memcpy(MenuStr_ALLWIN_UM_3_CleanHead2, group2_chs, sizeof(group2_chs));
		memcpy(MenuStr_ALLWIN_UM_3_CleanHeadAll, groupAll_chs, sizeof(groupAll_chs));
		memcpy(MenuStr_ALLWIN_UM_3_CleanHead1_E, group1_en, sizeof(group1_en));
		memcpy(MenuStr_ALLWIN_UM_3_CleanHead2_E, group2_en, sizeof(group2_en));
		memcpy(MenuStr_ALLWIN_UM_3_CleanHeadAll_E, groupAll_en, sizeof(groupAll_en));
#endif				
#endif        
	}
	
	if(grouphead != 1)
	{
		//for disable head.
		memcpy(MenuStr_EM_1_ID3F3_DisableHead1, closeGroup1_chs, sizeof(closeGroup1_chs));
		memcpy(MenuStr_EM_1_ID3F3_DisableHead2, closeGroup2_chs, sizeof(closeGroup2_chs));
		memcpy(MenuStr_EM_1_ID3F3_DisableHead1_E, closeGroup1_en, sizeof(closeGroup1_en));
		memcpy(MenuStr_EM_1_ID3F3_DisableHead2_E, closeGroup2_en, sizeof(closeGroup2_en));
	}
	
	MI_0_ID00_MenuChilds[11].Visible = 0; //waiting head board info.
	/* add white for UV printer */
	if(factoryData.spot_color1_headnum < 2)
	{
		int i;
		for ( i = 0; i < 16; i++)
		{	
			MI_EM_3_ID236_Spot1Name[i].Visible = 1;
			MI_EM_3_ID236_Spot2Name[i].Visible = 1;
			MI_EM_3_ID236_Spot3Name[i].Visible = 1;
			MI_EM_3_ID236_Spot4Name[i].Visible = 1;
		}	
		for ( i = 16; i < 20; i++)
		{	
			MI_EM_3_ID236_Spot1Name[i].Visible = 0;
			MI_EM_3_ID236_Spot2Name[i].Visible = 0;
			MI_EM_3_ID236_Spot3Name[i].Visible = 0;
			MI_EM_3_ID236_Spot4Name[i].Visible = 0;
		}
	}	
	else if (factoryData.spot_color1_headnum == 2)
	{
		int i;
		for ( i = 0; i < 14; i++)
		{	
			MI_EM_3_ID236_Spot1Name[i].Visible = 1;
			MI_EM_3_ID236_Spot2Name[i].Visible = 1;
			MI_EM_3_ID236_Spot3Name[i].Visible = 1;
			MI_EM_3_ID236_Spot4Name[i].Visible = 1;
		}
		MI_EM_3_ID236_Spot1Name[14].Visible = 0;
		MI_EM_3_ID236_Spot2Name[14].Visible = 0;
		MI_EM_3_ID236_Spot3Name[14].Visible = 0;
		MI_EM_3_ID236_Spot4Name[14].Visible = 0;
		
		for ( i = 15; i < 18; i++)
		{	
			MI_EM_3_ID236_Spot1Name[i].Visible = 1;
			MI_EM_3_ID236_Spot2Name[i].Visible = 1;
			MI_EM_3_ID236_Spot3Name[i].Visible = 1;
			MI_EM_3_ID236_Spot4Name[i].Visible = 1;
		}
		for ( i = 18; i < 20; i++)
		{	
			MI_EM_3_ID236_Spot1Name[i].Visible = 0;
			MI_EM_3_ID236_Spot2Name[i].Visible = 0;
			MI_EM_3_ID236_Spot3Name[i].Visible = 0;
			MI_EM_3_ID236_Spot4Name[i].Visible = 0;
		}
	}
	else if (factoryData.spot_color1_headnum == 3)
	{
		int i;
		for ( i = 0; i < 14; i++)
		{	
			MI_EM_3_ID236_Spot1Name[i].Visible = 1;
			MI_EM_3_ID236_Spot2Name[i].Visible = 1;
			MI_EM_3_ID236_Spot3Name[i].Visible = 1;
			MI_EM_3_ID236_Spot4Name[i].Visible = 1;
		}
		MI_EM_3_ID236_Spot1Name[14].Visible = 0;
		MI_EM_3_ID236_Spot2Name[14].Visible = 0;
		MI_EM_3_ID236_Spot3Name[14].Visible = 0;
		MI_EM_3_ID236_Spot4Name[14].Visible = 0;
		
		for ( i = 15; i < 19; i++)
		{	
			MI_EM_3_ID236_Spot1Name[i].Visible = 1;
			MI_EM_3_ID236_Spot2Name[i].Visible = 1;
			MI_EM_3_ID236_Spot3Name[i].Visible = 1;
			MI_EM_3_ID236_Spot4Name[i].Visible = 1;
		}
		
		for ( i = 19; i < 20; i++)
		{	
			MI_EM_3_ID236_Spot1Name[i].Visible = 0;
			MI_EM_3_ID236_Spot2Name[i].Visible = 0;
			MI_EM_3_ID236_Spot3Name[i].Visible = 0;
			MI_EM_3_ID236_Spot4Name[i].Visible = 0;
		}
	}
	else
	{	
		int i;
		for ( i = 0; i < 14; i++)
		{	
			MI_EM_3_ID236_Spot1Name[i].Visible = 1;
			MI_EM_3_ID236_Spot2Name[i].Visible = 1;
			MI_EM_3_ID236_Spot3Name[i].Visible = 1;
			MI_EM_3_ID236_Spot4Name[i].Visible = 1;
		}
		MI_EM_3_ID236_Spot1Name[14].Visible = 0;
		MI_EM_3_ID236_Spot2Name[14].Visible = 0;
		MI_EM_3_ID236_Spot3Name[14].Visible = 0;
		MI_EM_3_ID236_Spot4Name[14].Visible = 0;
		for ( i = 15; i < 20; i++)
		{	
			MI_EM_3_ID236_Spot1Name[i].Visible = 1;
			MI_EM_3_ID236_Spot2Name[i].Visible = 1;
			MI_EM_3_ID236_Spot3Name[i].Visible = 1;
			MI_EM_3_ID236_Spot4Name[i].Visible = 1;
		}
	}
	// X Head_Space
	if(groupnum * grouphead == 1)
	{
		MI_EM_1_ID4B_ADJUSTMENT[5].Visible = 0;
		MI_UM_1_ID25_ADJUSTMENT[5].Visible = 0;
	}
	else if(groupnum * grouphead == 2 && factoryData.HeadType == HeadNo_Epson_Gen5)
	{
		MI_EM_1_ID4B_ADJUSTMENT[5].Visible = 1;
		MI_UM_1_ID25_ADJUSTMENT[2].Visible = 1;
		
		MI_EM_6_ID74_VSD1_CorrectionValue[1].Visible = 1;
		MI_EM_6_ID74_VSD1_CorrectionValue[2].Visible = 0;
		
		MI_EM_6_ID74_VSD2_CorrectionValue[1].Visible = 1;
		MI_EM_6_ID74_VSD2_CorrectionValue[2].Visible = 0;
		
		MI_EM_6_ID74_VSD3_CorrectionValue[1].Visible = 1;
		MI_EM_6_ID74_VSD3_CorrectionValue[2].Visible = 0;
		
		MI_EM_6_ID74_VSD4_CorrectionValue[1].Visible = 1;
		MI_EM_6_ID74_VSD4_CorrectionValue[2].Visible = 0;
		
		MI_UM_6_ID74_VSD1_CorrectionValue[1].Visible = 1;
		MI_UM_6_ID74_VSD1_CorrectionValue[2].Visible = 0;
		
		MI_UM_6_ID74_VSD2_CorrectionValue[1].Visible = 1;
		MI_UM_6_ID74_VSD2_CorrectionValue[2].Visible = 0;
		
		MI_UM_6_ID74_VSD3_CorrectionValue[1].Visible = 1;
		MI_UM_6_ID74_VSD3_CorrectionValue[2].Visible = 0;
		
		MI_UM_6_ID74_VSD4_CorrectionValue[1].Visible = 1;
		MI_UM_6_ID74_VSD4_CorrectionValue[2].Visible = 0;
	}
	else
	{
		MI_EM_1_ID4B_ADJUSTMENT[5].Visible = 1;
		MI_UM_1_ID25_ADJUSTMENT[2].Visible = 1;
		
		MI_EM_6_ID74_VSD1_CorrectionValue[1].Visible = 0;
		MI_EM_6_ID74_VSD1_CorrectionValue[2].Visible = 1;
		
		MI_EM_6_ID74_VSD2_CorrectionValue[1].Visible = 0;
		MI_EM_6_ID74_VSD2_CorrectionValue[2].Visible = 1;
		
		MI_EM_6_ID74_VSD3_CorrectionValue[1].Visible = 0;
		MI_EM_6_ID74_VSD3_CorrectionValue[2].Visible = 1;
		
		MI_EM_6_ID74_VSD4_CorrectionValue[1].Visible = 0;
		MI_EM_6_ID74_VSD4_CorrectionValue[2].Visible = 1;
		
		MI_UM_6_ID74_VSD1_CorrectionValue[1].Visible = 0;
		MI_UM_6_ID74_VSD1_CorrectionValue[2].Visible = 1;
		
		MI_UM_6_ID74_VSD2_CorrectionValue[1].Visible = 0;
		MI_UM_6_ID74_VSD2_CorrectionValue[2].Visible = 1;
		
		MI_UM_6_ID74_VSD3_CorrectionValue[1].Visible = 0;
		MI_UM_6_ID74_VSD3_CorrectionValue[2].Visible = 1;
		
		MI_UM_6_ID74_VSD4_CorrectionValue[1].Visible = 0;
		MI_UM_6_ID74_VSD4_CorrectionValue[2].Visible = 1;
		
		for(j =0; j<groupnum; j++)
		{
			for(k=0; k<grouphead; k++)
			{          
				if(epsonCaliSetting.printerSetting.bIntegratedHead)
				{
					MI_UM_6_ID74_CorrectionValue_VSD1[j*grouphead + k].ActionParameters = j*grouphead + k;
					MI_EM_6_ID74_CorrectionValue_VSD1[j*grouphead + k].ActionParameters = j*grouphead + k;
					
					MI_UM_6_ID74_CorrectionValue_VSD2[j*grouphead + k].ActionParameters = 1*1000+j*grouphead + k;
					MI_EM_6_ID74_CorrectionValue_VSD2[j*grouphead + k].ActionParameters = 1*1000+j*grouphead + k;
					
					MI_UM_6_ID74_CorrectionValue_VSD3[j*grouphead + k].ActionParameters = 2*1000+j*grouphead + k;
					MI_EM_6_ID74_CorrectionValue_VSD3[j*grouphead + k].ActionParameters = 2*1000+j*grouphead + k;
					
					MI_UM_6_ID74_CorrectionValue_VSD4[j*grouphead + k].ActionParameters = 3*1000+j*grouphead + k;
					MI_EM_6_ID74_CorrectionValue_VSD4[j*grouphead + k].ActionParameters = 3*1000+j*grouphead + k;
				}
				else
				{
					MI_UM_6_ID74_CorrectionValue_VSD1[j*grouphead + k].ActionParameters = j*100+k;
					MI_EM_6_ID74_CorrectionValue_VSD1[j*grouphead + k].ActionParameters = j*100+k;
					
					MI_UM_6_ID74_CorrectionValue_VSD2[j*grouphead + k].ActionParameters = 1*1000+j*100+k;
					MI_EM_6_ID74_CorrectionValue_VSD2[j*grouphead + k].ActionParameters = 1*1000+j*100+k;
					
					MI_UM_6_ID74_CorrectionValue_VSD3[j*grouphead + k].ActionParameters = 2*1000+j*100+k;
					MI_EM_6_ID74_CorrectionValue_VSD3[j*grouphead + k].ActionParameters = 2*1000+j*100+k;
					
					MI_UM_6_ID74_CorrectionValue_VSD4[j*grouphead + k].ActionParameters = 3*1000+j*100+k;
					MI_EM_6_ID74_CorrectionValue_VSD4[j*grouphead + k].ActionParameters = 3*1000+j*100+k;
				}
				l=0;
				if(groupnum!=1 && grouphead!= 1)
				{
					MenuStr_Head_Space_Name[j*grouphead + k][l]='G';
					MenuStr_Head_Space_Name_E[j*grouphead + k][l]='G';
					l++;
					MenuStr_Head_Space_Name[j*grouphead + k][l]='1'+j;
					MenuStr_Head_Space_Name_E[j*grouphead + k][l]='1'+j;
					l++;
				}
#ifdef MANUFACTURER_DYSS
#ifdef RICOH_3H
				if(k == 0 || k == 1)
				{
					sprintf(MenuStr_Head_Space_Name[k],"%c,%c", factoryDataEx.m_nColorOrder[k*2], factoryDataEx.m_nColorOrder[k*2+1]);
					sprintf(MenuStr_Head_Space_Name_E[k],"%c,%c", factoryDataEx.m_nColorOrder[k*2], factoryDataEx.m_nColorOrder[k*2+1]);
				}
				else
				{
					sprintf(MenuStr_Head_Space_Name[k],"%c,%c", COLORCODE_W, COLORCODE_V);
					sprintf(MenuStr_Head_Space_Name_E[k],"%c,%c", COLORCODE_W, COLORCODE_V);
				}
#else	//RICOH 6H
				if(k == 4)
				{
					sprintf(MenuStr_Head_Space_Name[k],"%c", COLORCODE_W);
					sprintf(MenuStr_Head_Space_Name_E[k],"%c", COLORCODE_W);
				}
				else if(k == 5)
				{
					sprintf(MenuStr_Head_Space_Name[k],"%c", COLORCODE_V);
					sprintf(MenuStr_Head_Space_Name_E[k],"%c", COLORCODE_V);
				}
				else
				{
					sprintf(MenuStr_Head_Space_Name[k],"%c", factoryDataEx.m_nColorOrder[k]);
					sprintf(MenuStr_Head_Space_Name_E[k],"%c", factoryDataEx.m_nColorOrder[k]);
				}
#endif	//enddef RICOH_3H
#else	//nodef MANUFACTURER_DYSS
				if(NOZZLE_LINE_COUNT_PER_HEAD == epsonCaliSetting.printerSetting.YInterleaveNum)
				{
					if(factoryDataEx.m_nColorOrder[k] >= COLORCODE_SPOTCOLOR0 && factoryDataEx.m_nColorOrder[k] <= COLORCODE_SPOTCOLOR3)
					{
						m = factoryDataEx.m_nColorOrder[k] - COLORCODE_SPOTCOLOR0;
						m = LCDMenuConfig.SpotColorName[m];
						INT8U * pName = GetPrintedSpotColorName(m);
						
						for(m=0; pName[m] != 0; m++)
						{
							MenuStr_Head_Space_Name[j*grouphead + k][l]=pName[m];
							MenuStr_Head_Space_Name_E[j*grouphead + k][l]=pName[m];
							l++;
						}
					}
					else
					{
						MenuStr_Head_Space_Name[j*grouphead + k][l]=factoryDataEx.m_nColorOrder[k];
						MenuStr_Head_Space_Name_E[j*grouphead + k][l]=factoryDataEx.m_nColorOrder[k];
						l++;
					}
				}
				else
				{
					MenuStr_Head_Space_Name[j*grouphead + k][l]='H';
					MenuStr_Head_Space_Name_E[j*grouphead + k][l]='H';
					l++;
					if(groupnum!=1 && grouphead!= 1)
					{
						MenuStr_Head_Space_Name[j*grouphead + k][l]='1'+k;
						MenuStr_Head_Space_Name_E[j*grouphead + k][l]='1'+k;
					}
					else
					{
						MenuStr_Head_Space_Name[j*grouphead + k][l]='1'+j*grouphead + k;
						MenuStr_Head_Space_Name_E[j*grouphead + k][l]='1'+j*grouphead + k;
					}
					l++;
				}
				MenuStr_Head_Space_Name[j*grouphead + k][l]=0;
				MenuStr_Head_Space_Name_E[j*grouphead + k][l]=0;
#endif
			}
		}
	}
#if 1		
	for(j = 0;j< MAX_HEAD_NUM;j++)	
	{
		if(j >= groupnum * grouphead)
		{
			MI_UM_6_ID74_CorrectionValue_VSD1[j].Visible = 0;
			MI_EM_6_ID74_CorrectionValue_VSD1[j].Visible = 0;
			
			MI_UM_6_ID74_CorrectionValue_VSD2[j].Visible = 0;
			MI_EM_6_ID74_CorrectionValue_VSD2[j].Visible = 0;
			
			MI_UM_6_ID74_CorrectionValue_VSD3[j].Visible = 0;
			MI_EM_6_ID74_CorrectionValue_VSD3[j].Visible = 0;
			
			MI_UM_6_ID74_CorrectionValue_VSD4[j].Visible = 0;
			MI_EM_6_ID74_CorrectionValue_VSD4[j].Visible = 0;
		}
	}
#endif
	
#if 0
	if(factoryData.HeadType == HeadNo_Epson_Gen5)
	{
		INT16U dpi_x;
		for(j=0; j<5; j++)
		{
			switch(j)
			{
			case 0:
				dpi_x = epsonCaliSetting.printerSetting.DPI_X/2;
				break;
			case 1:
				dpi_x = epsonCaliSetting.printerSetting.DPI_X;
				break;
			case 2:
				dpi_x = epsonCaliSetting.printerSetting.DPI_X/4*3/2;
				break;
			case 3:
				dpi_x = epsonCaliSetting.printerSetting.DPI_X/4*3;
				break;
			case 4:
				dpi_x = epsonCaliSetting.printerSetting.DPI_X*2;
				break;
			}
			if(dpi_x>=1000)
				l= 4+3;
			else
				l= 3+3;
			MenuStr_DPI_Name[j][l] = 0;
			MenuStr_DPI_Name_E[j][l] = MenuStr_DPI_Name[j][l];
			l--;
			MenuStr_DPI_Name[j][l] = 'I';
			MenuStr_DPI_Name_E[j][l] = MenuStr_DPI_Name[j][l];
			l--;
			MenuStr_DPI_Name[j][l] = 'P';
			MenuStr_DPI_Name_E[j][l] = MenuStr_DPI_Name[j][l];
			l--;
			MenuStr_DPI_Name[j][l] = 'D';
			MenuStr_DPI_Name_E[j][l] = MenuStr_DPI_Name[j][l];
			while(l>0)
			{
				MenuStr_DPI_Name[j][l-1] = '0' + dpi_x % 10 ;
				MenuStr_DPI_Name_E[j][l-1] = MenuStr_DPI_Name[j][l-1];
				l--;
				dpi_x = dpi_x/10;
			}
		}
	}
	else
	{
		INT16U dpi_x;
		for(j=0; j<3; j++)
		{
			switch(j)
			{
			case 0:
				dpi_x = epsonCaliSetting.printerSetting.DPI_X/2;
				break;
			case 1:
				dpi_x = epsonCaliSetting.printerSetting.DPI_X;
				break;
			case 2:
				dpi_x = epsonCaliSetting.printerSetting.DPI_X/3;
				break;
			}
			if(dpi_x>=1000)
				l= 4+3;
			else
				l= 3+3;
			MenuStr_DPI_Name[j][l] = 0;
			MenuStr_DPI_Name_E[j][l] = MenuStr_DPI_Name[j][l];
			l--;
			MenuStr_DPI_Name[j][l] = 'I';
			MenuStr_DPI_Name_E[j][l] = MenuStr_DPI_Name[j][l];
			l--;
			MenuStr_DPI_Name[j][l] = 'P';
			MenuStr_DPI_Name_E[j][l] = MenuStr_DPI_Name[j][l];
			l--;
			MenuStr_DPI_Name[j][l] = 'D';
			MenuStr_DPI_Name_E[j][l] = MenuStr_DPI_Name[j][l];
			while(l>0)
			{
				MenuStr_DPI_Name[j][l-1] = '0' + dpi_x % 10 ;
				MenuStr_DPI_Name_E[j][l-1] = MenuStr_DPI_Name[j][l-1];
				l--;
				dpi_x = dpi_x/10;
			}
		}
	}
#endif
	for(j=0; j<MAX_NOZZLE_LINE; j++)
	{
		if(j >= groupnum * epsonCaliSetting.printerSetting.YInterleaveNum * colornum)
		{
			INT8U i = j;
			//Horizotal alignment 360DPI VSD1 �����
			MI_EM_6_ID74_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD1 �Ҷ���
			MI_EM_6_ID8A_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD2 �����
			MI_EM_6_ID9E_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD2 �Ҷ���
			MI_EM_6_IDB4_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD3 �����
			MI_EM_6_IDC8_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD3 �Ҷ���
			MI_EM_6_IDDE_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD4 �����
			MI_EM_6_IDF2_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD4 �Ҷ���
			MI_EM_6_ID108_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD1 �����
			MI_EM_6_ID11D_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD1 �Ҷ���
			MI_EM_6_ID133_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD2 �����
			MI_EM_6_ID147_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD2 �Ҷ���
			MI_EM_6_ID15D_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD3 �����
			MI_EM_6_ID171_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD3 �Ҷ���
			MI_EM_6_ID187_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD4 �����
			MI_EM_6_ID19B_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD4 �Ҷ���
			MI_EM_6_ID1B1_CorrectionValue[i].Visible=0;
			
			
			//Horizotal alignment 360DPI VSD1 �����
			MI_EM_6_ID75_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD1 �Ҷ���
			MI_EM_6_ID8B_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD2 �����
			MI_EM_6_ID9F_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD2 �Ҷ���
			MI_EM_6_IDB5_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD3 �����
			MI_EM_6_IDC9_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD3 �Ҷ���
			MI_EM_6_IDDF_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD4 �����
			MI_EM_6_IDF3_CorrectionValue[i].Visible=0;
			//Horizotal alignment 360DPI VSD4 �Ҷ���
			MI_EM_6_ID109_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD1 �����
			MI_EM_6_ID11E_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD1 �Ҷ���
			MI_EM_6_ID134_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD2 �����
			MI_EM_6_ID148_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD2 �Ҷ���
			MI_EM_6_ID15E_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD3 �����
			MI_EM_6_ID172_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD3 �Ҷ���
			MI_EM_6_ID188_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD4 �����
			MI_EM_6_ID19C_CorrectionValue[i].Visible=0;
			//Horizotal alignment 720DPI VSD4 �Ҷ���
			MI_EM_6_ID1B2_CorrectionValue[i].Visible=0;
			
			continue;
		}
		else
		{
			INT8U i = j;
			
			//Horizotal alignment 360DPI VSD1 �����
			MI_EM_6_ID74_CorrectionValue[i].Visible=1;
			MI_EM_6_ID74_CorrectionValue[i].ActionParameters = 0*10000 + 0*1000 + 0*100 + j; //high/low+Res+VSD+GroupNO/ColorNO/InterleaveNO
			//Horizotal alignment 360DPI VSD1 �Ҷ���
			MI_EM_6_ID8A_CorrectionValue[i].Visible=1;
			MI_EM_6_ID8A_CorrectionValue[i].ActionParameters = 0*10000 + 0*1000 + 0*100 + j;
			//Horizotal alignment 360DPI VSD2 �����
			MI_EM_6_ID9E_CorrectionValue[i].Visible=1;
			MI_EM_6_ID9E_CorrectionValue[i].ActionParameters = 0*10000 + 0*1000 + 1*100 + j;
			//Horizotal alignment 360DPI VSD2 �Ҷ���
			MI_EM_6_IDB4_CorrectionValue[i].Visible=1;
			MI_EM_6_IDB4_CorrectionValue[i].ActionParameters = 0*10000 + 0*1000 + 1*100 + j;
			//Horizotal alignment 360DPI VSD3 �����
			MI_EM_6_IDC8_CorrectionValue[i].Visible=1;
			MI_EM_6_IDC8_CorrectionValue[i].ActionParameters = 0*10000 + 0*1000 + 2*100 + j;
			//Horizotal alignment 360DPI VSD3 �Ҷ���
			MI_EM_6_IDDE_CorrectionValue[i].Visible=1;
			MI_EM_6_IDDE_CorrectionValue[i].ActionParameters = 0*10000 + 0*1000 + 2*100 + j;
			//Horizotal alignment 360DPI VSD4 �����
			MI_EM_6_IDF2_CorrectionValue[i].Visible=1;
			MI_EM_6_IDF2_CorrectionValue[i].ActionParameters = 0*10000 + 0*1000 + 3*100 + j;
			//Horizotal alignment 360DPI VSD4 �Ҷ���
			MI_EM_6_ID108_CorrectionValue[i].Visible=1;
			MI_EM_6_ID108_CorrectionValue[i].ActionParameters = 0*10000 + 0*1000 + 3*100 + j;
			//Horizotal alignment 720DPI VSD1 �����
			MI_EM_6_ID11D_CorrectionValue[i].Visible=1;
			MI_EM_6_ID11D_CorrectionValue[i].ActionParameters = 0*10000 + 1*1000 + 0*100 + j;
			//Horizotal alignment 720DPI VSD1 �Ҷ���
			MI_EM_6_ID133_CorrectionValue[i].Visible=1;
			MI_EM_6_ID133_CorrectionValue[i].ActionParameters = 0*10000 + 1*1000 + 0*100 + j;
			//Horizotal alignment 720DPI VSD2 �����
			MI_EM_6_ID147_CorrectionValue[i].Visible=1;
			MI_EM_6_ID147_CorrectionValue[i].ActionParameters = 0*10000 + 1*1000 + 1*100 + j;
			//Horizotal alignment 720DPI VSD2 �Ҷ���
			MI_EM_6_ID15D_CorrectionValue[i].Visible=1;
			MI_EM_6_ID15D_CorrectionValue[i].ActionParameters = 0*10000 + 1*1000 + 1*100 + j;
			//Horizotal alignment 720DPI VSD3 �����
			MI_EM_6_ID171_CorrectionValue[i].Visible=1;
			MI_EM_6_ID171_CorrectionValue[i].ActionParameters = 0*10000 + 1*1000 + 2*100 + j;
			//Horizotal alignment 720DPI VSD3 �Ҷ���
			MI_EM_6_ID187_CorrectionValue[i].Visible=1;
			MI_EM_6_ID187_CorrectionValue[i].ActionParameters = 0*10000 + 1*1000 + 2*100 + j;
			//Horizotal alignment 720DPI VSD4 �����
			MI_EM_6_ID19B_CorrectionValue[i].Visible=1;
			MI_EM_6_ID19B_CorrectionValue[i].ActionParameters = 0*10000 + 1*1000 + 3*100 + j;
			//Horizotal alignment 720DPI VSD4 �Ҷ���
			MI_EM_6_ID1B1_CorrectionValue[i].Visible=1;
			MI_EM_6_ID19B_CorrectionValue[i].ActionParameters = 0*10000 + 1*1000 + 3*100 + j;
			
			//Horizotal alignment 360DPI VSD1 �����
			MI_EM_6_ID75_CorrectionValue[i].Visible=1;
			MI_EM_6_ID75_CorrectionValue[i].ActionParameters = 1*10000 + 0*1000 + 0*100 + j; //high/low+Res+VSD+GroupNO/ColorNO/InterleaveNO
			//Horizotal alignment 360DPI VSD1 �Ҷ���
			MI_EM_6_ID8B_CorrectionValue[i].Visible=1;
			MI_EM_6_ID8B_CorrectionValue[i].ActionParameters = 1*10000 + 0*1000 + 0*100 + j;
			//Horizotal alignment 360DPI VSD2 �����
			MI_EM_6_ID9F_CorrectionValue[i].Visible=1;
			MI_EM_6_ID9F_CorrectionValue[i].ActionParameters = 1*10000 + 0*1000 + 1*100 + j;
			//Horizotal alignment 360DPI VSD2 �Ҷ���
			MI_EM_6_IDB5_CorrectionValue[i].Visible=1;
			MI_EM_6_IDB5_CorrectionValue[i].ActionParameters = 1*10000 + 0*1000 + 1*100 + j;
			//Horizotal alignment 360DPI VSD3 �����
			MI_EM_6_IDC9_CorrectionValue[i].Visible=1;
			MI_EM_6_IDC9_CorrectionValue[i].ActionParameters = 1*10000 + 0*1000 + 2*100 + j;
			//Horizotal alignment 360DPI VSD3 �Ҷ���
			MI_EM_6_IDDF_CorrectionValue[i].Visible=1;
			MI_EM_6_IDDF_CorrectionValue[i].ActionParameters = 1*10000 + 0*1000 + 2*100 + j;
			//Horizotal alignment 360DPI VSD4 �����
			MI_EM_6_IDF3_CorrectionValue[i].Visible=1;
			MI_EM_6_IDF3_CorrectionValue[i].ActionParameters = 1*10000 + 0*1000 + 3*100 + j;
			//Horizotal alignment 360DPI VSD4 �Ҷ���
			MI_EM_6_ID109_CorrectionValue[i].Visible=1;
			MI_EM_6_ID109_CorrectionValue[i].ActionParameters = 1*10000 + 0*1000 + 3*100 + j;
			//Horizotal alignment 720DPI VSD1 �����
			MI_EM_6_ID11E_CorrectionValue[i].Visible=1;
			MI_EM_6_ID11E_CorrectionValue[i].ActionParameters = 1*10000 + 1*1000 + 0*100 + j;
			//Horizotal alignment 720DPI VSD1 �Ҷ���
			MI_EM_6_ID134_CorrectionValue[i].Visible=1;
			MI_EM_6_ID134_CorrectionValue[i].ActionParameters = 1*10000 + 1*1000 + 0*100 + j;
			//Horizotal alignment 720DPI VSD2 �����
			MI_EM_6_ID148_CorrectionValue[i].Visible=1;
			MI_EM_6_ID148_CorrectionValue[i].ActionParameters = 1*10000 + 1*1000 + 1*100 + j;
			//Horizotal alignment 720DPI VSD2 �Ҷ���
			MI_EM_6_ID15E_CorrectionValue[i].Visible=1;
			MI_EM_6_ID15E_CorrectionValue[i].ActionParameters = 1*10000 + 1*1000 + 1*100 + j;
			//Horizotal alignment 720DPI VSD3 �����
			MI_EM_6_ID172_CorrectionValue[i].Visible=1;
			MI_EM_6_ID172_CorrectionValue[i].ActionParameters = 1*10000 + 1*1000 + 2*100 + j;
			//Horizotal alignment 720DPI VSD3 �Ҷ���
			MI_EM_6_ID188_CorrectionValue[i].Visible=1;
			MI_EM_6_ID188_CorrectionValue[i].ActionParameters = 1*10000 + 1*1000 + 2*100 + j;
			//Horizotal alignment 720DPI VSD4 �����
			MI_EM_6_ID19C_CorrectionValue[i].Visible=1;
			MI_EM_6_ID19C_CorrectionValue[i].ActionParameters = 1*10000 + 1*1000 + 3*100 + j;
			//Horizotal alignment 720DPI VSD4 �Ҷ���
			MI_EM_6_ID1B2_CorrectionValue[i].Visible=1;
			MI_EM_6_ID1B2_CorrectionValue[i].ActionParameters = 1*10000 + 1*1000 + 3*100 + j;
		}
		
		l=0;
		if(groupnum > 1)
		{
			if(grouphead == 1)
			{
				MenuStr_LeftRightAlign_Name[j][l]='H';
				MenuStr_LeftRightAlign_Name_E[j][l] = MenuStr_LeftRightAlign_Name[j][l];
				l++;
			}
			else
			{
				MenuStr_LeftRightAlign_Name[j][l]='G';
				MenuStr_LeftRightAlign_Name_E[j][l] = MenuStr_LeftRightAlign_Name[j][l];
				l++;
			}
			MenuStr_LeftRightAlign_Name[j][l] = '1' + j / (epsonCaliSetting.printerSetting.YInterleaveNum * colornum);
			MenuStr_LeftRightAlign_Name_E[j][l] = MenuStr_LeftRightAlign_Name[j][l];
			l++;
		}
		
		k = j / epsonCaliSetting.printerSetting.YInterleaveNum;
		k %= colornum;
		if(factoryDataEx.m_nColorOrder[k] >= COLORCODE_SPOTCOLOR0 && factoryDataEx.m_nColorOrder[k] <= COLORCODE_SPOTCOLOR3)
		{
#if MANUFACTURER_DYSS
			if(factoryDataEx.m_nColorOrder[k] == COLORCODE_SPOTCOLOR0)
				MenuStr_LeftRightAlign_Name[j][l] = MenuStr_LeftRightAlign_Name_E[j][l] = COLORCODE_W;
			else if(factoryDataEx.m_nColorOrder[k] == COLORCODE_SPOTCOLOR1)
				MenuStr_LeftRightAlign_Name[j][l] = MenuStr_LeftRightAlign_Name_E[j][l] = COLORCODE_V;
			l++;
#else	//undef MANUFACTURER_DYSS
			m = factoryDataEx.m_nColorOrder[k] - COLORCODE_SPOTCOLOR0;
			m = LCDMenuConfig.SpotColorName[m];
			INT8U * pName = GetPrintedSpotColorName(m);
			
			for(m=0; pName[m] != 0; m++)
			{
				MenuStr_LeftRightAlign_Name[j][l]= pName[m];
				MenuStr_LeftRightAlign_Name_E[j][l] = pName[m];
				l++;
			}
#endif
		}
		else
		{
			MenuStr_LeftRightAlign_Name[j][l] = factoryDataEx.m_nColorOrder[k];
			MenuStr_LeftRightAlign_Name_E[j][l] = MenuStr_LeftRightAlign_Name[j][l];
			l++;
		}
		if(epsonCaliSetting.printerSetting.YInterleaveNum > 1)
		{
			MenuStr_LeftRightAlign_Name[j][l] = '1' + j % epsonCaliSetting.printerSetting.YInterleaveNum;
			MenuStr_LeftRightAlign_Name_E[j][l] = MenuStr_LeftRightAlign_Name[j][l];
			l++;
		}
		MenuStr_LeftRightAlign_Name[j][l] = 0;
		MenuStr_LeftRightAlign_Name_E[j][l] = MenuStr_LeftRightAlign_Name[j][l];
	}
	
	if(groupnum == 1)
	{
		//Angle Adjustment 360DPI VSD1 �����
		MI_EM_6_ID1D1_CorrectionValue[1].Visible=0;
		//Angle Adjustment 360DPI VSD1 �Ҷ���
		MI_EM_6_ID1D6_CorrectionValue[1].Visible=0;
		//Angle Adjustment 360DPI VSD2 �����
		MI_EM_6_ID1DC_CorrectionValue[1].Visible=0;
		//Angle Adjustment 360DPI VSD2 �Ҷ���
		MI_EM_6_ID1E1_CorrectionValue[1].Visible=0;
		//Angle Adjustment 360DPI VSD3 �����
		MI_EM_6_ID1E7_CorrectionValue[1].Visible=0;
		//Angle Adjustment 360DPI VSD3 �Ҷ���
		MI_EM_6_ID1EC_CorrectionValue[1].Visible=0;
		//Angle Adjustment 360DPI VSD4 �����
		MI_EM_6_ID1F2_CorrectionValue[1].Visible=0;
		//Angle Adjustment 360DPI VSD4 �Ҷ���
		MI_EM_6_ID1F7_CorrectionValue[1].Visible=0;
		//Angle Adjustment 720DPI VSD1 �����
		MI_EM_6_ID1FE_CorrectionValue[1].Visible=0;
		//Angle Adjustment 720DPI VSD1 �Ҷ���
		MI_EM_6_ID203_CorrectionValue[1].Visible=0;
		//Angle Adjustment 720DPI VSD2 �����
		MI_EM_6_ID209_CorrectionValue[1].Visible=0;
		//Angle Adjustment 720DPI VSD2 �Ҷ���
		MI_EM_6_ID20E_CorrectionValue[1].Visible=0;
		//Angle Adjustment 720DPI VSD3 �����
		MI_EM_6_ID214_CorrectionValue[1].Visible=0;
		//Angle Adjustment 720DPI VSD3 �Ҷ���
		MI_EM_6_ID219_CorrectionValue[1].Visible=0;
		//Angle Adjustment 720DPI VSD4 �����
		MI_EM_6_ID21F_CorrectionValue[1].Visible=0;
		//Angle Adjustment 720DPI VSD4 �Ҷ���
		MI_EM_6_ID224_CorrectionValue[1].Visible=0;
		
		//ͷ��ֱ�����
		if(IsYIntervalReplaceVertical())
		{
			MI_EM_1_ID4B_ADJUSTMENT[3].Visible = 1;
			MI_UM_1_ID25_ADJUSTMENT[2].Visible = 1;
		}
		else
		{
			MI_EM_1_ID4B_ADJUSTMENT[3].Visible = 0;
			MI_UM_1_ID25_ADJUSTMENT[2].Visible = 0;
		}
		
		//ͷˮƽ���У׼
#if 0	
		if(grouphead != 1)
		{
			MI_EM_1_ID4B_ADJUSTMENT[5].Visible = 1;	
			MI_UM_1_ID25_ADJUSTMENT[5].Visible = 1;	
		}
		else
		{
			MI_EM_1_ID4B_ADJUSTMENT[5].Visible = 0;	
			MI_UM_1_ID25_ADJUSTMENT[5].Visible = 0;	
		}
#endif
		if(GetCleanPartCount() == 1)
		{
#if defined (EPSON_CLEAN_INTEGRATE)||defined (EPSON_CLEAN_INTEGRATE_1) ||defined(EPSON_CLEAN_INTEGRATE_2)||defined(EPSON_CLEAN_INTEGRATE_3)//ͷ��ϴѡ��
			MI_MICOLOR_1_ID28B_HEADCLEANING[0] .Visible= 0;
#else
			MI_ALLWIN_1_ID23C_HEADCLEANING[0] .Visible= 0;
#endif
		}
		else
		{
#if defined (EPSON_CLEAN_INTEGRATE)||defined (EPSON_CLEAN_INTEGRATE_1) ||defined(EPSON_CLEAN_INTEGRATE_2)||defined(EPSON_CLEAN_INTEGRATE_3)	//ͷ��ϴѡ��
			MI_MICOLOR_1_ID28B_HEADCLEANING[0] .Visible= 1;
#else
			MI_ALLWIN_1_ID23C_HEADCLEANING[0] .Visible= 1;
#endif
		}
	}
	else
	{
		//ͷ��ֱ�����
		MI_EM_1_ID4B_ADJUSTMENT[3].Visible = 1;
		MI_UM_1_ID25_ADJUSTMENT[2].Visible = 1;
		//ͷˮƽ���У׼
		MI_EM_1_ID4B_ADJUSTMENT[5].Visible = 1;
		MI_UM_1_ID25_ADJUSTMENT[5].Visible = 1;
#if defined (EPSON_CLEAN_INTEGRATE)||defined (EPSON_CLEAN_INTEGRATE_1) ||defined(EPSON_CLEAN_INTEGRATE_2)||defined(EPSON_CLEAN_INTEGRATE_3)	//ͷ��ϴѡ��
		MI_MICOLOR_1_ID28B_HEADCLEANING[0] .Visible= 1;
#else
		MI_ALLWIN_1_ID23C_HEADCLEANING[0] .Visible= 1;
#endif
	}
	Change_Unit_For_Language();
	//Set_PrintQuality(LCDMenuConfig.PrintQuality);
	Set_Clean_Dis();
#if defined(ALLWIN_EPSON_SAME)
	if(EPSON_PERMIT_GROUPNUM > 1 && EPSON_ACTIVE_GROUPNUM > 1)
		MI_1_ID20_QUALITY[2].Visible = 1;
	else
		factoryDataEx.Only_Used_1head = 0;
#else
	MI_UM_1_ID25_ADJUSTMENT[0].Visible = 0;
	MI_UM_1_ID25_ADJUSTMENT[1].Visible = 0;
	MI_UM_1_ID25_ADJUSTMENT[2].Visible = 0;
	factoryDataEx.Only_Used_1head = 0;
#endif
	
	for(j=0; j<colornum; j++)
	{
		l = 0;
		if(factoryDataEx.m_nColorOrder[j] >= COLORCODE_SPOTCOLOR0 && factoryDataEx.m_nColorOrder[j] <= COLORCODE_SPOTCOLOR3)
		{
#if MANUFACTURER_DYSS
			if(factoryDataEx.m_nColorOrder[j] == COLORCODE_SPOTCOLOR0)
				MenuStr_Color_Name[j][l] = MenuStr_Color_Name_E[j][l] = COLORCODE_W;
			else if(factoryDataEx.m_nColorOrder[j] == COLORCODE_SPOTCOLOR1)
				MenuStr_Color_Name[j][l] = MenuStr_Color_Name_E[j][l] = COLORCODE_V;
			l++;
#else	//nodef MANUFACTURER_DYSS
			m = factoryDataEx.m_nColorOrder[j] - COLORCODE_SPOTCOLOR0;
			m = LCDMenuConfig.SpotColorName[m];
			INT8U * pName = GetPrintedSpotColorName(m);
			
			for(m=0; pName[m] != 0; m++)
			{
				MenuStr_Color_Name[j][l]=pName[m];
				MenuStr_Color_Name_E[j][l] = MenuStr_Color_Name[j][l];
				l++;
			}
#endif	//end MANUFACTURER_DYSS	
		}
		else
		{
			MenuStr_Color_Name[j][l] = factoryDataEx.m_nColorOrder[j];
			MenuStr_Color_Name_E[j][l] = MenuStr_Color_Name[j][l];
			l++;
		}
		MenuStr_Color_Name[j][l] = 0;
		MenuStr_Color_Name_E[j][l] = MenuStr_Color_Name[j][l];
	}
	
	//Vertical alignment У��ֵ
	if(epsonCaliSetting.printerSetting.bVerticalValid)
	{
		MI_EM_1_ID4B_ADJUSTMENT[7].Visible = 1;
		MI_UM_1_ID25_ADJUSTMENT[6].Visible = 1;
	}
	else
	{
		MI_EM_1_ID4B_ADJUSTMENT[7].Visible = 0;
		MI_UM_1_ID25_ADJUSTMENT[6].Visible = 0;
	}
	if( (epsonCaliSetting.printerSetting.head_group > 1 && epsonCaliSetting.printerSetting.verticalNozzleShift == 0) ||
	   ((factoryData.spot_color1_headnum + factoryData.spot_color2_headnum) > 0 && epsonCaliSetting.printerSetting.bIntegratedHead == 0))
		MI_EM_1_ID4B_ADJUSTMENT[8].Visible = 1;
	else
		MI_EM_1_ID4B_ADJUSTMENT[8].Visible = 0;
#ifdef MANUFACTURER_DYSS
	MI_EM_1_ID4B_ADJUSTMENT[8].Visible = 1;
#endif	
	for(int i = colornum;i<MAX_COLOR_NUM;i++)
	{
		MI_EM_3_ID1C7_CorrectionValue[i].Visible = 0;
		MI_EM_3_ID25_CorrectionValue[i].Visible = 0;
	}
	
	if(EPSON_PERMIT_GROUPNUM == 1)
	{
		MI_0_ID00_MenuChilds[12].Visible = 0;
		MI_EM_1_ID3F3_HeadSwitch[0].Visible = 0;
		MI_EM_1_ID3F3_HeadSwitch[1].Visible = 0;
	}
#ifdef EPSON_4H	
	else if(EPSON_PERMIT_GROUPNUM == 4)
	{
		MI_0_ID00_MenuChilds[12].Visible = 1;
		MI_0_ID00_MenuChilds[12].ChildItems = MI_EM_1_ID3F3_Head4Switch;
		MI_0_ID00_MenuChilds[12].ItemCount = 8;
	}
#endif	
	else 
	{
		MI_0_ID00_MenuChilds[12].Visible = 1;
		MI_EM_1_ID3F3_HeadSwitch[0].Visible = 1;
		MI_EM_1_ID3F3_HeadSwitch[1].Visible = 1;
#ifdef EPSON_4H			
		if(GetGroupHeadNumber() == 2)
		{
			MI_EM_1_ID3F3_HeadSwitch[0].Text_ch =(unsigned short *) MenuStr_EM_1_ID3F3_DisableGroup1;
			MI_EM_1_ID3F3_HeadSwitch[0].Text_en = MenuStr_EM_1_ID3F3_DisableGroup1_E;
			MI_EM_1_ID3F3_HeadSwitch[1].Text_ch =(unsigned short *) MenuStr_EM_1_ID3F3_DisableGroup2;
			MI_EM_1_ID3F3_HeadSwitch[1].Text_en = MenuStr_EM_1_ID3F3_DisableGroup2_E;			
		}
#endif		
	}
	
#if defined(EPSON_BOTTOM_BOARD_V3)||defined(EPSON_BOTTOM_BOARD_V2_1)
	if(isWeakSolventprinter)
	{
		//        if(EPSON_HEADNUM > 1)
		//        {
		//            MI_EM_1_ID3F4_Heater[2].Visible = 0;
		//            MI_EM_1_ID3F4_Heater[5].Visible = 0;
		//        }
		MI_EM_1_ID3F4_Heater[1].Visible = 1;
		MI_EM_1_ID3F4_Heater[2].Visible = 1;
		MI_EM_1_ID3F4_Heater[4].Visible = 1;
		MI_EM_1_ID3F4_Heater[5].Visible = 1;
	}
	else
	{
		MI_EM_1_ID3F4_Heater[1].Visible = 0;
		MI_EM_1_ID3F4_Heater[2].Visible = 0;
		MI_EM_1_ID3F4_Heater[4].Visible = 0;
		MI_EM_1_ID3F4_Heater[5].Visible = 0;
	}
#endif
#ifdef MANUFACTURER_GZ 
	MI_1_ID0D_OriginAndMediaWidth[0].Visible = 0; 
#endif
	//DrawMainScreen(CurrentStatus,PMainScreen);
#if defined(MANUFACTURER_MICOLOR_EPSON) || defined(MANUFACTURER_COLORFUL)
	MI_MICOLOR_1_ID28B_HEADCLEANING[9] .Visible= 1;
#endif
	
#ifdef AUTO_CLEAN_BYTIME
	MI_ALLWIN_EM_2_ID283_AutoClean[1].Text_ch = (unsigned short *)MenuStr_1_Auoto_Clean_Time;
	MI_ALLWIN_EM_2_ID283_AutoClean[1].Text_en = MenuStr_1_Auoto_Clean_Time_EN;
#endif

#ifdef RICOH_CLEAN_PRESS
	MI_0_ID00_MenuChilds[2].Visible = 0;
	for(j = 0;j<9;j++)
		MI_ALLWIN_1_ID23C_HEADCLEANING[j].Visible = 0;
#endif

#ifdef FAST_CLEAN
	MI_ALLWIN_EM_2_ID283_AutoClean[2].Visible = 0;
	MI_ALLWIN_EM_2_ID283_AutoClean[0].Text_ch =  (unsigned short *)MenuStrAutoFlashOnOff;
	MI_ALLWIN_EM_2_ID283_AutoClean[0].Text_en =  MenuStrAutoFlashOnOff_EN;
#endif

#ifdef EPSON_4H
	MI_1_ID3FB_System[5].ItemCount = 4;
#endif
}
//
//void ChangMenuDisMode(INT8U MenuMode)
//{
//  IsAdvancedMode = MenuMode;
//  CurrentDisMode = MainScreen;
//  Initial_Dis();
//}
#endif
