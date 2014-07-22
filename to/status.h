#ifndef _STATUS_H_
#define _STATUS_H_

#include "os_includes.h"

#define STATUS_BITS				0x1FFFFF00

//#define STATUS_NO_PRINT_BITS	0x0FCFE800

//#define STATUS_NO_PRINT_BITS	0x0FCFC800  //20090910 Change, Print huge band, pause sometimes will cause hung up
//#define STATUS_NO_PRINT_BITS	0x0FCFCA00  //20100128 V2.4.0 Add STATUS_ERR_AUTO
//#define STATUS_NO_PRINT_BITS	0x0FCFEA00  //20110520 Add CMD_PAUSE. 
#define STATUS_NO_PRINT_BITS	0x0FCFCA00  //20111029 remove CMD_PAUSE. see the comment at main.c UART_DSP_RPT_STOP.

#define STATUS_NO_X_MOVE_BITS	0x0FAFCE00  
#define STATUS_NO_Y_MOVE_BITS	0x0FEFCE00  

#define STATUS_NO_CLEAN_BITS	0x0FAFAE00  
#define STATUS_NO_CLEAN_BITS_FOR_PAUSE	0x0F8F8E00  

//0x80000000 is used for STATUS_CHANGE in status.c

/*
#define EXT_STATUS_LEVEL_RDY	0		
#define EXT_STATUS_LEVEL_SVC	1
#define EXT_STATUS_LEVEL_FTA	2
#define EXT_STATUS_LEVEL_ERR	3
#define EXT_STATUS_LEVEL_WAR	4*/

//Status number must be less than 255, 
//DSP number: 0xD0~0xFF 

#define STATUS_NO_CANCEL  	0x10000000

#define STATUS_SVC		0x08000000 	//Highest priority
#define STATUS_FTA		0x04000000
#define STATUS_ERR		0x02000000

#define STATUS_INI		0x01000000
#define STATUS_MOVING   	0x00800000  
#define STATUS_PAUSE    	0x00400000
#define STATUS_PRINT		0x00200000  
#define STATUS_WAR		0x00100000
#define STATUS_RDY		0x00000000	//Lowest priority
#define STATUS_CLEANING 	0x00080000

#define CMD_CLEAN_MANUAL 	0x00040000
#define CMD_CLEAN_SINGLE	0x00020000
#define CMD_CLEAN_AUTO		0x00010000
#define CMD_START_MOVE		0x00008000
//#define CMD_MEDIA_MOVE	0x00004000
#define CMD_EPSON_OPERATION     0x00004000
#define CMD_PAUSE		0x00002000
#define CMD_CANCEL_REQ	        0x00001000

#define STATUS_UPDATING		0x00000800  //For updating
#define STATUS_MOVING_FLASH	0x00000400  //MOVING=>MOVING_FLASH=>NOT MOVING_FLASH=>NOT MOVING: ��ʾ�Ƿ���"��X"�˶��������˶���Ӱ������
//��STATUS_MOVING_FLASH����ʱ��STATUS_MOVING�����Ѿ�����
//��STATUS_MOVING���ʱ��STATUS_MOVING_FLASH�����Ѿ������
#define STATUS_ERR_AUTO		0x00000200  //20100128, V2.4.0

#define STATUS_CAPPED		0x00000100  //20100128, V2.4.0

#define BUF_STATUS_BITS	(STATUS_UPDATING|STATUS_WAR|STATUS_ERR|STATUS_ERR_AUTO|STATUS_INI|STATUS_FTA|STATUS_SVC)


//If have high priority status, only show higher priority status
//Warning maybe can show together with printing, pause, and move
//But: PRINT & PAUSE & MOVING 		== Pausing
//	   PRINT & PAUSE & !MOVING		== Pause
//	   PRINT & !PAUSE & MOVING		== Printing		
//	   PRINT & !PAUSE & !MOVING		== Printing		
//	   !PRINT & PAUSE & MOVING 		== Moving;   XXX error status
//	   !PRINT & PAUSE & !MOVING		== Ready;	 XXX error status
//	   !PRINT & !PAUSE & MOVING		== Moving		
//	   !PRINT & !PAUSE & !MOVING	== Ready		

//	   CANCEL & PRINT & PAUSE & MOVING 		== Canceling
//	   CANCEL & PRINT & PAUSE & !MOVING		== Canceling
//	   CANCEL & PRINT & !PAUSE & MOVING		== Printing		
//	   CANCEL & PRINT & !PAUSE & !MOVING		== Printing		
//	   CANCEL & !PRINT & PAUSE & MOVING 		== Moving;   XXX error status
//	   CANCEL & !PRINT & PAUSE & !MOVING		== Ready;	 XXX error status
//	   CANCEL & !PRINT & !PAUSE & MOVING		== Moving		
//	   CANCEL & !PRINT & !PAUSE & !MOVING	== Ready		


#define STATUS_SVC_SX2						(STATUS_SVC+0) //USB chip. ����0.5�룬USBоƬ��û������������USBоƬ������
#define STATUS_SVC_FPGA0					(STATUS_SVC+1) //FPGA chip 1. �ϵ��FPGA��nSTATUS����Ϊ�ߣ�FPGAоƬ������ 
#define STATUS_SVC_FPGA1					(STATUS_SVC+2) //FPGA chip 2. ����nCONFIG֮��CONFIG_Done����nSTATUS���Ǹ�
#define STATUS_SVC_FPGA2					(STATUS_SVC+3) //FPGA chip 3. nCONFIG����֮��, nSTATUS���ָ�.
#define STATUS_SVC_FPGA3					(STATUS_SVC+4) //FPGA chip 4. When config FPGA, FPGA report err, and retry 10 times
#define STATUS_SVC_UPDATE_FAIL				(STATUS_SVC+5) //UPDATE Main Board Failed.
#define STATUS_SVC_BYHX_DATA				(STATUS_SVC+6) //����û�о���BYHX��ʼ��
#define STATUS_SVC_EEPROM_CHK				(STATUS_SVC+16) //BYHX_TOOL check EEPROM û��ͨ����
#define STATUS_SVC_SDRAM_CHECK				(STATUS_SVC+7)  //SDRAM ��Checkû��ͨ��
#define STATUS_SVC_FLASH					(STATUS_SVC+8) //Flash. Cann't read FPGA from flash. 
#define STATUS_SVC_SDRAM_NOMATCH			(STATUS_SVC+9)  //SDRAM ̫С������֧�ֵ�ǰ�����á�
#define STATUS_SVC_READBOARDID_FAIL			(STATUS_SVC+10)  //Read board id Error��ʵ�����ǲ�������оƬʧ��
#define STATUS_SVC_ARM_MOTION       		(STATUS_SVC+11)  //ARM Motion system initial error.
#define STATUS_SVC_HEADBOARD_INIT_FAIL		(STATUS_SVC+12)  //HEAD board initial fail��ʵ������EPSONͷ���������оƬʧ��
#define STATUS_SVC_POWER_OFF_MODE		(STATUS_SVC+13)  //�ػ�ģʽ

#define STATUS_FTA_SX2RESET					(STATUS_FTA+0) //USB chip�쳣����
#define STATUS_FTA_INTERNAL_WRONGHEADER		(STATUS_FTA+1) //Wrong data header
#define STATUS_FTA_INTERNAL_WRONGHEADERSIZE (STATUS_FTA+2) //Wrong data header size
#define STATUS_FTA_INTERNAL_JOBSTARTHEADER	(STATUS_FTA+3) //Job header��Ӧ������������
#define STATUS_FTA_INTERNAL_BANDDATASIZE	(STATUS_FTA+4) //Band Header�е�BAND����������ʵ��BAND������������
#define STATUS_FTA_INTERNAL_WRONGFORMAT		(STATUS_FTA+5) //�õ��Ĵ������ݸ�ʽ����
#define STATUS_FTA_INTERNAL_DMA0WORKING		(STATUS_FTA+6) //DMA0 still working after a band complete
#define STATUS_FTA_INTERNAL_PRINTPOINT		(STATUS_FTA+7) //Wrong startpoint and endpoint when print
#define STATUS_FTA_INTERNAL_OLIMIT			(STATUS_FTA+8) //Band�Ĵ�ӡ��ʼ��С��ԭ��
#define STATUS_FTA_INTERNAL_OPPLIMIT		(STATUS_FTA+9) //ͼ�����λ�ó����˴�ӡ����Զ��,Image too width
#define STATUS_FTA_DSPINITS1				(STATUS_FTA+10) //�˶����Ƶ�һ�׶γ�ʼ��û��ͨ��
#define STATUS_FTA_DSPINITS2				(STATUS_FTA+11) //�˶����Ƶڶ��׶γ�ʼ��û��ͨ��
#define STATUS_FTA_HEADINITS1				(STATUS_FTA+12) //ͷ���һ�׶γ�ʼ��û��ͨ��
#define STATUS_FTA_HEADINITS2				(STATUS_FTA+13) //ͷ��ڶ��׶γ�ʼ��û��ͨ��
#define STATUS_FTA_HEADTOMAINROAD			(STATUS_FTA+14) //�����LVDS����оƬû��LOCK,����û�в�
#define STATUS_FTA_INTERNAL_BANDDIRECTION   (STATUS_FTA+15) //Band�����еķ���ֵ��������
#define STATUS_FTA_DSPUPDATE_FAIL			(STATUS_FTA+16) //����ʧ�ܣ�����д��׶�
#define STATUS_FTA_EEPROM_READ				(STATUS_FTA+17) //��ȡEEPROMʧ��	
#define STATUS_FTA_EEPROM_WRITE				(STATUS_FTA+18) //д��EEPROMʧ��
#define STATUS_FTA_FACTORY_DATA				(STATUS_FTA+19) //����û�о���������ʼ������
#define STATUS_FTA_HEADBOARD_RESET			(STATUS_FTA+20) //ͷ�屻��������
#define STATUS_FTA_SPECTRAHVBINITS1			(STATUS_FTA+21) //Spectra High Voltage Board��һ�׶γ�ʼ��ʧ��
#define STATUS_FTA_PRINTHEAD_NOTMATCH		(STATUS_FTA+22) //ͷ�屨�����ͷ������FactoryData������趨��ƥ�䣬 �����ͷ��������趨Ӳ�����á�
#define STATUS_FTA_MANUFACTURERID_NOTMATCH  (STATUS_FTA+23) //����ϵͳ��FW���������̲�ƥ�䣬�����ϵͳ��������FW 
#define STATUS_FTA_LIMITEDTIME_RUNOUT		(STATUS_FTA+24) //������ʱʱ�䣬�������������
#define STATUS_FTA_INTERNAL_SW1				(STATUS_FTA+25) //Internal error, blank band and y-distance == 0
#define STATUS_FTA_USB1_USB1CONNECT			(STATUS_FTA+26)  //���ӵ�USB1��   //This error is moved to Fatal error, 2.0�汾����д���ˣ�дΪ(STATUS_ERR+26)
#define STATUS_FTA_UILANGUAGE_NOT_MATCH		(STATUS_FTA+27)  //UIʹ�õ�������Ȩ�޲����� �������������Ի���������������
#define STATUS_FTA_INTERNAL_WRONGPINCONF	(STATUS_FTA+28)  //PINCONFд��FPGA����
#define STATUS_FTA_FACTORY_COLORNUM_WRONG	(STATUS_FTA+29)  //Factory ��д���color number ����
#define STATUS_FTA_HB_EEPROM_WRT_ERR		(STATUS_FTA+30)  //ͷ���EEPROMд��ʧ��
#define STATUS_FTA_HB_OVERHEAT				(STATUS_FTA+31)  ////��ͷ���ȳ�����55�ȣ����м��ȱ�ǿ�йرա�
#define STATUS_FTA_SHAKEHAND_ERR			(STATUS_FTA+32)  //���������߰汾����û��ͨ������Э�顣
#define STATUS_FTA_SWVERSION_ERR			(STATUS_FTA+33)  //�̼�Ҫ�����������汾���汾����
#define STATUS_FTA_NOT_SUPPORT_2C_SHARE_1H	(STATUS_FTA+34)  //��ǰϵͳ���ò�֧��һͷ��ɫ��
#define STATUS_FTA_LIMITEDINK_RUNOUT		(STATUS_FTA+35)  //����īˮ�������ƣ��������������
#define STATUS_FTA_SWVERSION_ERR_INK_PWD	(STATUS_FTA+36)  //�̼�Ҫ������汾֧��īˮ���룬�汾����
#define STATUS_FTA_EPSON_HEAD_BAD			(STATUS_FTA+37)  //EPSON��ӡͷ����.
#define STATUS_FTA_EPSON_HEAD_FPGA_ERR		(STATUS_FTA+38)  //EPSONͷ��FPGA����.ͨ���ǳ�Ƶ�����ݱ����š�
#define STATUS_FTA_SECURITY_CHIP_ERR		(STATUS_FTA+39)  //Write board id error.
#define STATUS_FTA_CALIBRATION_DATA 		(STATUS_FTA+41)  //������ʼ�����ó���
#define STATUS_FTA_PRINT_DATA_ERROR 		(STATUS_FTA+47)  //��ӡ���ݴ�������ʧ
#define STATUS_FTA_FACTORY_DATA_ERROR 		(STATUS_FTA+48)  //FACTORY_DATA���ݴ���
#define STATUS_FTA_WASTE_INK_FULL 			(STATUS_FTA+49)	//��ī���
#define STATUS_FTA_DPI_NOT_SUPPORT 			(STATUS_FTA+50)	//��֧�ֵķֱ���

#define STATUS_ERR_EP0OVERUN_SETUPDATA		(STATUS_ERR+0)  //EP0������
//#define STATUS_ERR_USB1_USB1CONNECT			(STATUS_ERR+1)  //���ӵ�USB1��   //This error is moved to Fatal error
#define STATUS_ERR_UART1_TXTIMEOUT			(STATUS_ERR+3)  //ͷ��������ͨѶ��ʱ
#define STATUS_ERR_UART2_TXTIMEOUT			(STATUS_ERR+2)  //�˶�ͨѶ��ʱ
#define STATUS_ERR_INTERNAL_PRINTDATA		(STATUS_ERR+4)  //Band����û�д�ӡ���
#define STATUS_ERR_FPGA_LESSDATA			(STATUS_ERR+5)  //Print data is less than fire number or empty when trigger
#define STATUS_ERR_FPGA_ULTRADATA			(STATUS_ERR+6)  //Print data is more than fire number
#define STATUS_ERR_FPGA_WRONGSTATUS			(STATUS_ERR+7)
#define STATUS_ERR_UV_CTR_WRONGSTATUS		(STATUS_ERR+8)	//Internal Status
#define STATUS_ERR_FPGA_WRONGCOMMAND		(STATUS_ERR+9)  //FPGA �յ����������
#define STATUS_ERR_MOTION_SPEED_BAD			(STATUS_ERR+10) //�˶��ٶ�̫��򲻾��ȣ����ݻ��ڳ��飬ȴ�е������
#define STATUS_ERR_INTERNAL_MOVING_TIMEOUT	(STATUS_ERR+11) //�˶������30���û���յ��˶��������
#define STATUS_ERR_INTERNAL_WRONGAUTOCLEAN	(STATUS_ERR+12)  //�����AUTOCLEAN�����Ӧ�÷���
#define STATUS_ERR_INTERNAL_WRONGBANDINFO	(STATUS_ERR+13)  //�����AUTOCLEAN�����Ӧ�÷���

#define STATUS_ERR_INTERNAL_DEBUG1	(STATUS_ERR+0x50) //Debug status 1
#define STATUS_ERR_INTERNAL_DEBUG2	(STATUS_ERR+0x51) //Debug status 1



#define STATUS_INI_ARM				(STATUS_INI+0)  //���ڳ�ʼ�����ذ�
#define STATUS_INI_SX2				(STATUS_INI+1)  //���ڳ�ʼ��USBͨѶ
#define STATUS_INI_FPGA				(STATUS_INI+2)  //���ڳ�ʼ��FPGA
#define STATUS_INI_DSP				(STATUS_INI+3)	//���ڳ�ʼ���˶�
#define STATUS_INI_HEADBOARD		(STATUS_INI+4)  //���ڳ�ʼ��ͷ��
#define STATUS_INI_HVB				(STATUS_INI+5)  //Spectra ���ڳ�ʼ����ѹ��

#define STATUS_WAR_UNKNOWNHEADERTYPE (STATUS_WAR+0) //δ���������ͷ��ʾ����������
#define STATUS_WAR_EP0OVERUN_REQUEST_IGNORE	(STATUS_WAR+1) //EP0���ݴ���δ��ɣ����յ��µ�EP0����ɵ����ݴ������
#define STATUS_WAR_PUMP_CYAN	(STATUS_WAR+2)
#define STATUS_WAR_PUMP_MAGENTA	(STATUS_WAR+3)
#define STATUS_WAR_PUMP_YELLOW	(STATUS_WAR+4)
#define STATUS_WAR_PUMP_BLACK	(STATUS_WAR+5)
#define STATUS_WAR_PUMP_LIGHTCYAN		(STATUS_WAR+6)
#define STATUS_WAR_PUMP_LIGHTMAGENTA	(STATUS_WAR+7)

#define STATUS_WAR_TIME_PASSWORD_WRONGINPUT	(STATUS_WAR+8) //������ʱ������󣬺��з�0~F��ֵ
#define STATUS_WAR_TIME_PASSWORD_WRONG		(STATUS_WAR+9)	//����һ���Ϸ���ʱ����
#define STATUS_WAR_TIME_PASSWORD_MANUFACTURERIDNOTMATCH (STATUS_WAR+10)  //��ʱ����ͳ��̲�ƥ��
#define STATUS_WAR_TIME_PASSWORD_BOARDIDNOTMATCH (STATUS_WAR+11) //��ʱ����Ͱ��Ӳ�ƥ��

#define STATUS_WAR_LIMITEDTIME_FIRST	(STATUS_WAR+12) //����100��Сʱ�ͳ�����ʱ�ˣ���һ�ξ���
#define STATUS_WAR_LIMITEDTIME_SECOND	(STATUS_WAR+13) //����50��Сʱ�ͳ�����ʱ�ˣ��ڶ��ξ���
#define STATUS_WAR_LIMITEDTIME_LAST		(STATUS_WAR+14) //����1��Сʱ�ͳ�����ʱ�ˣ����һ�ξ���

#define STATUS_WAR_OPTION_PASSWORD_WRONGINPUT	(STATUS_WAR+16) //����ѡ��������󣬺��з�0~F��ֵ
#define STATUS_WAR_OPTION_PASSWORD_WRONG		(STATUS_WAR+17)	//����һ���Ϸ�ѡ������
#define STATUS_WAR_OPTION_PASSWORD_MANUFACTURERIDNOTMATCH (STATUS_WAR+18)  //ѡ������ͳ��̲�ƥ��
#define STATUS_WAR_OPTION_PASSWORD_BOARDIDNOTMATCH (STATUS_WAR+19) //ѡ������Ͱ��Ӳ�ƥ��

#define STATUS_WAR_PUMP_PROHIBIT_SENSOR	(STATUS_WAR+20) //ʹ�ܽ�ֹī�б�ī������ʱ
#define STATUS_WAR_OVER_SPEED_NOT_SUPPORT	(STATUS_WAR+21) //KM512LN ��ͼ��Ƶ������ͷ�岻֧�֣�ȡ����Ƶ

#define STATUS_WAR_INK_PASSWORD_WRONGINPUT	(STATUS_WAR+22) //����īˮ������󣬺��з�0~F��ֵ
#define STATUS_WAR_INK_PASSWORD_WRONG		(STATUS_WAR+23)	//����һ���Ϸ�īˮ����
#define STATUS_WAR_INK_PASSWORD_MANUFACTURERIDNOTMATCH (STATUS_WAR+24)  //īˮ����ͳ��̲�ƥ��
#define STATUS_WAR_INK_PASSWORD_BOARDIDNOTMATCH (STATUS_WAR+25) //īˮ����Ͱ��Ӳ�ƥ��

#define STATUS_WAR_LIMITEDINK_FIRST	(STATUS_WAR+26) //����10���ͳ���īˮ�����ˣ���һ�ξ���
#define STATUS_WAR_LIMITEDINK_SECOND	(STATUS_WAR+27) //����5���ͳ���īˮ�����ˣ��ڶ��ξ���
#define STATUS_WAR_LIMITEDINK_LAST		(STATUS_WAR+28) //����1���ͳ���īˮ�����ˣ����һ�ξ���

#define STATUS_WAR_INK_PASSWORD_UNKNOWN_DOT_VOLUME	(STATUS_WAR+29) //��ǰ��ֻ֧��Konica��Polaris��������ͷ��ī�δ�С���ԣ�����42pl��

#define STATUS_WAR_PUMP_SPOTCOLOR1	(STATUS_WAR+30)
#define STATUS_WAR_PUMP_SPOTCOLOR2	(STATUS_WAR+31)

#define STATUS_WAR_FPGA_LESSDATA	(STATUS_WAR+32)  //Print data is less than fire number or empty when trigger
#define STATUS_WAR_FPGA_ULTRADATA	(STATUS_WAR+33)  //Print data is more than fire number

#define STATUS_WAR_EPSONHEAD_TEMP_TOO_LOW	(STATUS_WAR+34)  //Head temperature too low.
#define STATUS_WAR_EPSONHEAD_TEMP_TOO_HIGH	(STATUS_WAR+35)  //Head temperature too high.
#define STATUS_WAR_EPSONHEAD_NOT_CONNECT	(STATUS_WAR+36)  //Print head is not connected.
#define STATUS_WAR_EPSON_FPGA_ULTRADATA		(STATUS_WAR+37)  //core board FPGA report data too more.
#define STATUS_WAR_EPSON_FPGA_LESSDATA		(STATUS_WAR+38)  //core board FPGA report data too less. .

#define STATUS_WAR_UNKNOWN_NOZZLE_COUNT	(STATUS_WAR+39) //��ǰ��ͷ��������δ֪��

#define STATUS_WAR_EPSON_DRIVER_OVERHEAT	(STATUS_WAR+40)  //EPSON Head Driver over heat.
#define STATUS_WAR_EPSON_XHOT_ERROR	(STATUS_WAR+41)     //XHOT error.
#define STATUS_WAR_HB_FW_VERSION			(STATUS_WAR+44)	// ����������ͷ���FW�汾̫�ͣ��Ѳ�֧��
#define STATUS_WAR_HB_FW_ID_ERROR			(STATUS_WAR+45)	// ͷ��FW ID��ƥ�䣬��ǰͷ�岻��������FW
#define STATUS_WAR_HB_FW_UPDATER			(STATUS_WAR+46)	// ͷ���������̷�������
#define STATUS_WAR_EPSON_HEAD_FPGA_ERR		(STATUS_WAR+49)  //ͷ��FPGA���� ԭFTA38���� ��Ϊwaring
#define STATUS_WAR_EPSON_HEAD_LVDS_ERR		(STATUS_WAR+50)  //��ʼ���� ����LVDSʧ����Ϊwaring
#define STATUS_WAR_EPSON_HEAD_REPORT_LVDS_ERR		(STATUS_WAR+51)  //ͷ�屨��LVDSʧ��

#define STATUS_WAR_K_LACK			(STATUS_WAR+52)  //k ȱī
#define STATUS_WAR_C_LACK			(STATUS_WAR+53)  //C ȱī
#define STATUS_WAR_M_LACK			(STATUS_WAR+54)  //M ȱī
#define STATUS_WAR_Y_LACK			(STATUS_WAR+55)  //Y ȱī
#define STATUS_WAR_W_LACK		(STATUS_WAR+56)  //W ȱī
#define STATUS_WAR_V_LACK			(STATUS_WAR+57)  //V ȱī
#define STATUS_WAR_Waste_Ink_FULL 			(STATUS_WAR+58)  //��ī���

#define STATUS_UPDATE_SUCCESS 		(STATUS_UPDATING+1) //Can not use (STATUS_UPDATING+0)
#define STATUS_UPDATEERR_DSP_BEGIN_TIMEOUT	(STATUS_UPDATING+2)
#define STATUS_UPDATEERR_DSP_DATA_TIMEOUT	(STATUS_UPDATING+3)
#define STATUS_UPDATEERR_DSP_END_TIMEOUT	(STATUS_UPDATING+4)
#define STATUS_UPDATEERR_ILIGALFILE 		(STATUS_UPDATING+5)
#define STATUS_UPDATEERR_INTERNAL_DATA		(STATUS_UPDATING+6)
#define STATUS_UPDATEERR_CHECKSUM			(STATUS_UPDATING+7)
#define STATUS_UPDATEERR_EREASE				(STATUS_UPDATING+8)
#define STATUS_UPDATEERR_FLASHOP			(STATUS_UPDATING+9) //ARM flash erease or write error, 10 times retry
#define STATUS_UPDATEERR_GZ_ILIGALFILE 		(STATUS_UPDATING+10)
#define STATUS_UPDATEERR_INKP_ILIGALFILE 	(STATUS_UPDATING+11)
#define STATUS_UPDATEERR_16H_ILIGALFILE 	(STATUS_UPDATING+12)
#define STATUS_UPDATEERR_HB_BEGIN_TIMEOUT	(STATUS_UPDATING+13)
#define STATUS_UPDATEERR_HB_DATA_TIMEOUT	(STATUS_UPDATING+14)
#define STATUS_UPDATEERR_HB_END_TIMEOUT		(STATUS_UPDATING+15)
#define STATUS_UPDATEERR_UVP_ILLEGALFILE	(STATUS_UPDATING+16)
#define STATUS_UPDATEERR_TRY_AGAIN       	(STATUS_UPDATING+17)

#ifdef CONVERSION_BOARD
#define HEAD_ERROR_SET 2
#define HEAD_ERROR_CLEAR 3
#endif

#define STATUS_SET	1
#define STATUS_CLR	0

void status_ReportStatus(INT32U number, INT8U op);
INT8U status_IsPrinting(void);
void status_FlushAllErrStatus(void);

enum SciError
{
	SciError_OK      = 0xF0,  //û�д���
	
	SciError_Command     = 0xF1,  //���������
	SciError_Parameter     = 0xF2,  //����Ĳ���
	SciError_MoveAgain     = 0xF3,  //�����д��� �Ѿ��˶�,�ַ��˶����� 
	SciError_TxTimeOut     = 0xF4,  //���ͳ�ʱ
	SciError_FormatErr     = 0xF5,  //У��ʹ���
	SciError_Encoder     = 0xF6,     //������λ����դ����
	SciError_MeasureSensor    = 0xF7,  //ֽ����������
	SciError_NoPaper     = 0xF8,  //û�н���
	SciError_PaperJamX     = 0xF9,  //X���˶�����
	SciError_PaperJamY     = 0xFA,  //Y���˶�����
	SciError_IndexNoMatch    = 0xFB,//��������
	SciError_LimitSensor    = 0xFC,     //�Ӵ���λ������
	SciError_StepEncoder    = 0xFD,     //û�з��ֲ���������
	
	SciError_ReadEEPROM     = 0xE1,//�� EEPROM ����
	SciError_WriteEEPROM     = 0xE2,//д EEPROM ����
	
	SciError_WriteEEPROMTwice   = 0xE3,//дEEPROM  2 ��
	SciError_TimeOver     = 0xE4,//���Ƶ�ʱ���Ҫ�ù���
	SciError_TimeWarning    = 0xE5,//�����Ƶ�ʱ�仹��50��Сʱ
	SciError_Lang      = 0xE6,//���Ժ����ƵĲ�ƥ��
	SciError_IllegalContent    = 0xE7,//�����EEPROM �����ݣ�EEPROM ����û�����
	SciError_IllegalPwd        = 0xE8,//���������
	
	SciError_SwDogEey        = 0xE9, //���û��ʹ�ü��ܹ�
	
	SciError_SensorPause       = 0xEE,//�Ӵ���λ������
	//cheney add.
	SciError_OverCurrent_Protect = 0xDF, //��������
	SciError_OverTemp_Protect = 0xDE,   //�¶ȹ��߱��� 
	SciError_InternalErr_1 = 0xDD,//�˶��ڲ�����1
	SciError_InternalErr_2 = 0xDC //�˶��ڲ�����2
};
#ifdef MANUFACTURER_DYSS
void changeLeddisplay(INT8U state);
#endif
#ifdef FUNC_MAINTAIN
//same with the flag "CMD_CLEAN_MANUAL", can not use as flag,
//�����ڸ�PM���͵�״̬�б�ʾ"ά��״̬��
#define STATUS_MAINTAIN 0x00040000		
extern INT8U bStatus_Maintain;
#endif	//end FUNC_MAINTAIN
#endif

