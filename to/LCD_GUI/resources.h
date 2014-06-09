#ifndef RESOURCES_H
#define RESOURCES_H
#include "Menu_GUI.h"
#include "calibration.h"
#define CHAR_TABLE_OFFSET (256)
extern struct MenuItem MainScreenRoot;
extern struct MenuItem MainMenuRoot;

#define MAX_HEAD_NUM 8

#ifdef HEAD_EPSON_GEN5

#ifdef EPSON_4H
#define MAX_HEAD_DRIVE_NUM 8
#else
#define MAX_HEAD_DRIVE_NUM 4
#endif

#else
#ifdef RICOH_G5_3H
#define MAX_HEAD_DRIVE_NUM 12
#elif defined(RICOH_G5_4H)
#define MAX_HEAD_DRIVE_NUM 16
#else
#define MAX_HEAD_DRIVE_NUM 8
#endif
#endif
#ifdef CONVERSION_BOARD
#ifdef RICOH_G4_16H
#define MAX_HEAD_DRIVE_NUM 16
#endif

#if defined(HEAD_EPSON_GEN5)||defined(RICOH_G5_3H)||defined(RICOH_G5_4H)
#error //need check
#endif

#endif

#ifdef EPSON_4H
#define MAX_NOZZLE_LINE (MAX_HEAD_NUMBER_CALIBRATION *NOZZLE_LINE_COUNT_PER_HEAD)
#else
#define MAX_NOZZLE_LINE (MAX_HEAD_NUM *2)
#endif
extern struct MenuItem MI_EM_1_ID3F3_Nozzleparameter[];
extern struct MenuItem MI_UM_3_ID3E_Head_Space[4];
extern struct MenuItem MI_EM_3_ID3E_Head_Space[4];
extern struct MenuItem MI_EM_6_ID74_CorrectionValue_VSD1[MAX_HEAD_NUM];
extern struct MenuItem MI_EM_6_ID74_CorrectionValue_VSD2[MAX_HEAD_NUM];
extern struct MenuItem MI_EM_6_ID74_CorrectionValue_VSD3[MAX_HEAD_NUM];
extern struct MenuItem MI_EM_6_ID74_CorrectionValue_VSD4[MAX_HEAD_NUM];

extern struct MenuItem MI_EM_6_ID74_VSD1_CorrectionValue[3];
extern struct MenuItem MI_EM_6_ID74_VSD2_CorrectionValue[3];
extern struct MenuItem MI_EM_6_ID74_VSD3_CorrectionValue[3];
extern struct MenuItem MI_EM_6_ID74_VSD4_CorrectionValue[3];

extern struct MenuItem MI_UM_6_ID74_CorrectionValue_VSD1[MAX_HEAD_NUM];
extern struct MenuItem MI_UM_6_ID74_CorrectionValue_VSD2[MAX_HEAD_NUM];
extern struct MenuItem MI_UM_6_ID74_CorrectionValue_VSD3[MAX_HEAD_NUM];
extern struct MenuItem MI_UM_6_ID74_CorrectionValue_VSD4[MAX_HEAD_NUM];

extern struct MenuItem MI_UM_6_ID74_VSD1_CorrectionValue[3];
extern struct MenuItem MI_UM_6_ID74_VSD2_CorrectionValue[3];
extern struct MenuItem MI_UM_6_ID74_VSD3_CorrectionValue[3];
extern struct MenuItem MI_UM_6_ID74_VSD4_CorrectionValue[3];

//Horizotal alignment 
extern struct MenuItem MI_EM_6_ID74_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID8A_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID9E_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_IDB4_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_IDC8_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_IDDE_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_IDF2_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID108_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID11D_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID133_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID147_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID15D_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID171_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID187_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID19B_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID1B1_CorrectionValue[MAX_NOZZLE_LINE];

extern struct MenuItem MI_EM_6_ID75_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID8B_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID9F_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_IDB5_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_IDC9_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_IDDF_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_IDF3_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID109_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID11E_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID134_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID148_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID15E_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID172_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID188_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID19C_CorrectionValue[MAX_NOZZLE_LINE];
extern struct MenuItem MI_EM_6_ID1B2_CorrectionValue[MAX_NOZZLE_LINE];
//Vertical alignment 
#define MAX_COLOR_NUM   8
extern struct MenuItem MI_EM_3_ID25_CorrectionValue[MAX_COLOR_NUM];
extern struct MenuItem MI_EM_3_ID1C7_CorrectionValue[MAX_COLOR_NUM];
extern struct MenuItem MI_EM_2_ID25_Verticalalignment[2];
//Angle Adjustment
extern struct MenuItem MI_EM_6_ID1D1_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID1D6_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID1DC_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID1E1_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID1E7_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID1EC_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID1F2_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID1F7_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID1FE_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID203_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID209_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID20E_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID214_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID219_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID21F_CorrectionValue[2];
extern struct MenuItem MI_EM_6_ID224_CorrectionValue[2];
extern struct MenuItem MI_EM_1_ID4B_ADJUSTMENT[11];
extern struct MenuItem MI_1_ID20_QUALITY[5];
extern struct MenuItem MI_1_ID3FB_System[];
#ifdef FUNC_WAVE_MAP
extern unsigned char MenuStr_VSD_WaveName_EN[8][8] ;
extern unsigned char MenuStr_VSD_WaveName_CN[8][8] ;
#endif
#ifdef LCD_MODULE_ZX19264M1A
#define MAX_COLOR_NAME  6
extern unsigned char MenuStr_Color_Name[MAX_COLOR_NUM][MAX_COLOR_NAME];
extern unsigned char MenuStr_Color_Name_E[MAX_COLOR_NUM][MAX_COLOR_NAME];

#define MAX_DPI_NAME 14
#define MAX_DPI_NUM 5
extern unsigned char MenuStr_DPI_Name[MAX_DPI_NUM][MAX_DPI_NAME];
extern unsigned char MenuStr_DPI_Name_E[MAX_DPI_NUM][MAX_DPI_NAME];

#define MAX_HOR_NAME 8
#define MAX_HEAD_NUM 8
extern unsigned char MenuStr_LeftRightAlign_Name[MAX_NOZZLE_LINE][MAX_HOR_NAME];
extern unsigned char MenuStr_LeftRightAlign_Name_E[MAX_NOZZLE_LINE][MAX_HOR_NAME];
#if defined(EPSON_CLEAN_UPDOWN_TATE_8H_RICOH)
extern unsigned char MenuStr_Clean_Color_Name[4][MAX_COLOR_NAME];
extern unsigned char MenuStr_Clean_Color_Name_E[4][MAX_COLOR_NAME];
#elif defined(EPSON_4H_CLEAN_SPLIT)
extern unsigned char MenuStr_Clean_Color_Name[4][MAX_COLOR_NAME+2];
extern unsigned char MenuStr_Clean_Color_Name_E[4][MAX_COLOR_NAME+2];
#endif
#define MAX_HEAD_SPACE_NAME 8
extern unsigned char MenuStr_Head_Space_Name[MAX_HEAD_NUM][MAX_HEAD_SPACE_NAME];
extern unsigned char MenuStr_Head_Space_Name_E[MAX_HEAD_NUM][MAX_HEAD_SPACE_NAME];
#define MAX_HEAD_PARAM_NAME 20
extern unsigned char MenuStr_EM_4_ID1C8[MAX_HEAD_DRIVE_NUM][MAX_HEAD_PARAM_NAME];
extern unsigned char MenuStr_EM_4_ID1C8_E[MAX_HEAD_DRIVE_NUM][MAX_HEAD_PARAM_NAME];

extern unsigned char MenuStr_ALLWIN_UM_3_CleanHead1[];
extern unsigned char MenuStr_ALLWIN_UM_3_CleanHead2[];
extern unsigned char MenuStr_ALLWIN_UM_3_CleanHeadAll[];
extern unsigned char MenuStr_ALLWIN_UM_3_CleanHead1_E[];
extern unsigned char MenuStr_ALLWIN_UM_3_CleanHead2_E[];
extern unsigned char MenuStr_ALLWIN_UM_3_CleanHeadAll_E[];

extern unsigned char MenuStr_EM_1_ID3F3_DisableHead1[];
extern unsigned char MenuStr_EM_1_ID3F3_DisableHead2[];
extern unsigned char MenuStr_EM_1_ID3F3_DisableHead1_E[];
extern unsigned char MenuStr_EM_1_ID3F3_DisableHead2_E[];
extern unsigned char MenuStr_EM_1_ID3F3_DisableGroup1[];
extern unsigned char MenuStr_EM_1_ID3F3_DisableGroup2[];
extern unsigned char MenuStr_EM_1_ID3F3_DisableGroup1_E[];
extern unsigned char MenuStr_EM_1_ID3F3_DisableGroup2_E[];

extern unsigned short ErrorCodeCHS[];
extern unsigned char MenuStr_2_ID3FF_Percent[];

extern unsigned short *CHS_SVC_SX2;//��USB chip�з������.
extern unsigned short *CHS_SVC_FPGA0;//Service Call: chip1.
extern unsigned short *CHS_SVC_FPGA1;//Service Call: chip2.
extern unsigned short *CHS_SVC_FPGA2;//Service Call: chip3.
extern unsigned short *CHS_SVC_FPGA3;//Service Call: chip4
extern unsigned short *CHS_SVC_UPDATE_FAIL;//Service Call: chip5.
extern unsigned short *CHS_SVC_BYHX_DATA;//Service Call: 6.
extern unsigned short *CHS_SVC_EEPROM_CHK;//BYHX_TOOL check EEPROM û��ͨ����
extern unsigned short *CHS_SVC_SDRAM_CHECK;//SDRAM ��Checkû��ͨ��
extern unsigned short *CHS_SVC_FLASH;//�޷���Falsh��ȡFPGA. 
extern unsigned short *CHS_SVC_SDRAM_NOMATCH;//SDRAM ̫С������֧�ֵ�ǰ�����á�
extern unsigned short *CHS_SVC_READBOARDID_FAIL;//���������
extern unsigned short *CHS_SVC_MOTION_FAIL;//MOTION��ʼ��ʧ��
extern unsigned short *CHS_SVC_HEADBOARD_FAIL;//��ʼ��ͷ�����оƬʧ��
extern unsigned short *CHS_SVC_POWEROFF_MODE;//�ػ�ģʽ����رմ�ӡ��
extern unsigned short *CHS_FTA_SX2RESET;//USB chip�쳣����
extern unsigned short *CHS_FTA_INTERNAL_WRONGHEADER;//�ڲ����� 1.
extern unsigned short *CHS_FTA_INTERNAL_WRONGHEADERSIZE;//�ڲ����� 2.
extern unsigned short *CHS_FTA_INTERNAL_JOBSTARTHEADER;//�ڲ����� 3.
extern unsigned short *CHS_FTA_INTERNAL_BANDDATASIZE;//�ڲ����� 4.
extern unsigned short *CHS_FTA_INTERNAL_WRONGFORMAT;//�ڲ����� 5.
extern unsigned short *CHS_FTA_INTERNAL_DMA0WORKING;//�ڲ����� 6.
extern unsigned short *CHS_FTA_INTERNAL_PRINTPOINT;//�ڲ����� 7.
extern unsigned short *CHS_FTA_INTERNAL_OLIMIT;//�ڲ����� 8.
extern unsigned short *CHS_FTA_INTERNAL_OPPLIMIT;//�ڲ����� 9.
extern unsigned short *CHS_FTA_DSPINITS1;//�˶�step 1.
extern unsigned short *CHS_FTA_DSPINITS2;//�˶�step 2.
extern unsigned short *CHS_FTA_HEADINITS1;//ͷ��step1.
extern unsigned short *CHS_FTA_HEADINITS2;//ͷ��step2.
extern unsigned short *CHS_FTA_HEADTOMAINROAD;//LVDS����.
extern unsigned short *CHS_FTA_INTERNAL_BANDDIRECTION;//Band�����еķ���ֵ��������
extern unsigned short *CHS_FTA_DSPUPDATE_FAIL;//DSP����ʧ��.
extern unsigned short *CHS_FTA_EEPROM_READ;//EEPROM��ȡʧ��	
extern unsigned short *CHS_FTA_EEPROM_WRITE;//EEPROMд��ʧ��
extern unsigned short *CHS_FTA_FACTORY_DATA;//���ӳ���û�г�ʼ��.
extern unsigned short *CHS_FTA_HEADBOARD_RESET;//ͷ�帴λ.
extern unsigned short *CHS_FTA_SPECTRAHVBINITS1;//Spectra��ѹ���޷��ڵ�1����ʼ��.
extern unsigned short *CHS_FTA_PRINTHEAD_NOTMATCH;//ͷ����������ݲ�ƥ��,�����ó������ݻ��߸���ͷ��.
extern unsigned short *CHS_FTA_MANUFACTURERID_NOTMATCH;//���ӵĳ���ID��ƥ��,�������̼�. 
extern unsigned short *CHS_FTA_LIMITEDTIME_RUNOUT;//���ش���: ������ʱʱ�䣬�������µ�����.
extern unsigned short *CHS_FTA_INTERNAL_SW1;//�ڲ�����,�հ�Band��Y�����Ϊ��.
extern unsigned short *CHS_FTA_USB1_USB1CONNECT;//USB1.1����.
extern unsigned short *CHS_FTA_UILANGUAGE_NOT_MATCH;//UIʹ�õ�������Ȩ�޲����� �������������Ի���������������
extern unsigned short *CHS_FTA_INTERNAL_WRONGPINCONF;//PINCONFд��FPGA����
extern unsigned short *CHS_FTA_FACTORY_COLORNUM_WRONG;//����������д�����ɫ������.
extern unsigned short *CHS_FTA_HB_EEPROM_WRT_ERR;//ͷ���EEPROMд��ʧ��
extern unsigned short *CHS_FTA_HB_OVERHEAT;//��ͷ���ȣ����м��ȱ�ǿ�йرա�
extern unsigned short *CHS_FTA_SHAKEHAND_ERR;//���������߰汾����û��ͨ������Э�顣
extern unsigned short *CHS_FTA_SWVERSION_ERR;//�̼�Ҫ�����������汾���汾����
extern unsigned short *CHS_FTA_NOT_SUPPORT_2C_SHARE_1H;//��ǰϵͳ���ò�֧��һͷ��ɫ��
extern unsigned short *CHS_FTA_LIMITEDINK_RUNOUT;//����īˮ�������ƣ��������������
extern unsigned short *CHS_FTA_SWVERSION_ERR_INK_PWD;//�̼�Ҫ������汾֧��īˮ���룬�汾����
extern unsigned short *CHS_FTA_EPSON_HEAD_BAD;//������ID����
extern unsigned short *CHS_FTA_EPSON_HEAD_FPGA_ERR;//ͷ��FPGA����.
extern unsigned short *CHS_FTA_SECURITY_CHIP_ERR;//д�������.
extern unsigned short *CHS_FTA_CALIBRATION_DATA;//������ʼ�����ó���
extern unsigned short *CHS_FTA_PRINT_DATA_ERROR;//��ӡ���ݴ�������ʧ
extern unsigned short *CHS_FTA_FACTORY_DATA_ERROR;//FACTORY_DATA ���ݴ���
extern unsigned short *CHS_FTA_WASTE_INK_FULL;//��ī���
extern unsigned short *CHS_ERR_EP0OVERUN_SETUPDATA;//EP0������
extern unsigned short *CHS_ERR_UART1_TXTIMEOUT;//ͷ��COM��ʱ.
extern unsigned short *CHS_ERR_UART2_TXTIMEOUT;//�˶�COM��ʱ.
extern unsigned short *CHS_ERR_INTERNAL_PRINTDATA;//��ӡ���ݺ͵��Ƶ�ʲ�ƥ��.
extern unsigned short *CHS_ERR_FPGA_LESSDATA;//��ӡ����С�ڵ��Ƶ��
extern unsigned short *CHS_ERR_FPGA_ULTRADATA;//��ӡ���ݳ������Ƶ��.
extern unsigned short *CHS_ERR_FPGA_WRONGCHS;//��ӡ�����ݺͿ�������ƥ��.
extern unsigned short *CHS_ERR_UV_CTR_WRONGCHS;//�ڲ�״̬.
extern unsigned short *CHS_ERR_FPGA_WRONGCOMMAND;//FPGA �յ����������
extern unsigned short *CHS_ERR_MOTION_SPEED_BAD;//�˶��ٶ�̫��򲻾��ȣ����ݻ��ڳ��飬ȴ�е������
extern unsigned short *CHS_ERR_INTERNAL_MOVING_TIMEOUT;//�˶������30���û���յ��˶��������
extern unsigned short *CHS_ERR_INTERNAL_WRONGAUTOCLEAN;//�����AUTOCLEAN����.
extern unsigned short *CHS_ERR_INTERNAL_WRONGBANDINFO;//�����AUTOCLEAN����.
extern unsigned short *CHS_ERR_INTERNAL_DEBUG1;//����״̬1
extern unsigned short *CHS_ERR_INTERNAL_DEBUG2;//����״̬2
extern unsigned short *CHS_INI_ARM;//���ڳ�ʼ��ARM.
extern unsigned short *CHS_INI_SX2;//���ڳ�ʼ��USB
extern unsigned short *CHS_INI_FPGA;//���ڳ�ʼ��FPGA
extern unsigned short *CHS_INI_DSP;//���ڳ�ʼ��DSP.
extern unsigned short *CHS_INI_HEADBOARD;//���ڳ�ʼ��ͷ��
extern unsigned short *CHS_INI_HVB;//��װ Spectra ��ѹ��.
extern unsigned short *CHS_WAR_UNKNOWNHEADERTYPE;//��֪���ľ���
extern unsigned short *CHS_WAR_EP0OVERUN_REQUEST_IGNORE;//EP0���.
extern unsigned short *CHS_WAR_PUMP_CYAN;//��ɫ���ڱ�ī.
extern unsigned short *CHS_WAR_PUMP_MAGENTA;//Ʒɫ���ڱ�ī.
extern unsigned short *CHS_WAR_PUMP_YELLOW;//��ɫ���ڱ�ī.
extern unsigned short *CHS_WAR_PUMP_BLACK;//��ɫ���ڱ�ī.
extern unsigned short *CHS_WAR_PUMP_LIGHTCYAN;//ǳ��ɫ���ڱ�ī.
extern unsigned short *CHS_WAR_PUMP_LIGHTMAGENTA;//ǳƷɫ���ڱ�ī.
extern unsigned short *CHS_WAR_TIME_PASSWORD_WRONGINPUT;//������ʱ������󣬺��к��зǷ��ַ�; 
extern unsigned short *CHS_WAR_TIME_PASSWORD_WRONG;//����һ���Ϸ���ʱ����; 
extern unsigned short *CHS_WAR_TIME_PASSWORD_MANUFACTURERIDNOTMATCH;//��ʱ����ͳ��̲�ƥ��
extern unsigned short *CHS_WAR_TIME_PASSWORD_BOARDIDNOTMATCH;//��ʱ����Ͱ��Ӳ�ƥ��
extern unsigned short *CHS_WAR_LIMITEDTIME_FIRST;//��һ�ξ���:����100��Сʱ�ͳ�����ʱ��, ���򳧼���ȡ����.
extern unsigned short *CHS_WAR_LIMITEDTIME_SECOND;//�ڶ��ξ���: ����50��Сʱ�ͳ�����ʱ��,���򳧼���ȡ����.
extern unsigned short *CHS_WAR_LIMITEDTIME_LAST;//���һ�ξ���: ����1��Сʱ�ͳ�����ʱ��ֹͣ��ӡ, �������򳧼���ȡ����.
extern unsigned short *CHS_WAR_OPTION_PASSWORD_WRONGINPUT;//����ѡ��������󣬺��з�0~F��ֵ
extern unsigned short *CHS_WAR_OPTION_PASSWORD_WRONG;//����һ���Ϸ�ѡ������
extern unsigned short *CHS_WAR_OPTION_PASSWORD_MANUFACTURERIDNOTMATCH;//ѡ������ͳ��̲�ƥ��
extern unsigned short *CHS_WAR_OPTION_PASSWORD_BOARDIDNOTMATCH;//ѡ������Ͱ��Ӳ�ƥ��
extern unsigned short *CHS_WAR_PUMP_PROHIBIT_SENSOR;//��ī��ȫƿ����, ����ī��ֹͣ��ī.
extern unsigned short *CHS_WAR_OVER_SPEED_NOT_SUPPORT;//��ͼ�ڲ�֧�ֳ�Ƶ��ͷ��汾��ʹ�ó�Ƶ, ϵͳǿ��ʹ�ø��ٴ�ӡ.
extern unsigned short *CHS_WAR_INK_PASSWORD_WRONGINPUT;//����īˮ������󣬺��з�0~F��ֵ
extern unsigned short *CHS_WAR_INK_PASSWORD_WRONG;//����һ���Ϸ�īˮ����
extern unsigned short *CHS_WAR_INK_PASSWORD_MANUFACTURERIDNOTMATCH;//īˮ����ͳ��̲�ƥ��
extern unsigned short *CHS_WAR_INK_PASSWORD_BOARDIDNOTMATCH;//īˮ����Ͱ��Ӳ�ƥ��
extern unsigned short *CHS_WAR_LIMITEDINK_FIRST;//����10���ͳ���īˮ�����ˣ���һ�ξ���
extern unsigned short *CHS_WAR_LIMITEDINK_SECOND;//����5���ͳ���īˮ�����ˣ��ڶ��ξ���
extern unsigned short *CHS_WAR_LIMITEDINK_LAST;//����1���ͳ���īˮ�����ˣ����һ�ξ���
extern unsigned short *CHS_WAR_INK_PASSWORD_UNKNOWN_DOT_VOLUME;//��ǰ��ͷ��֧��īˮ���빦��.
extern unsigned short *CHS_WAR_PUMP_SPOTCOLOR1;//רɫ1���ڱ�ī.
extern unsigned short *CHS_WAR_PUMP_SPOTCOLOR2;//רɫ2���ڱ�ī.
extern unsigned short *CHS_WAR_FPGA_LESSDATA;//��ӡ����С�ڵ����.
extern unsigned short *CHS_WAR_FPGA_ULTRADATA;//��ӡ���ݶ��ڵ����.
extern unsigned short *CHS_WAR_EPSONHEAD_TEMP_TOO_LOW;//��ͷ�¶�̫��.
extern unsigned short *CHS_WAR_EPSONHEAD_TEMP_TOO_HIGH;//��ͷ�¶�̫��.
extern unsigned short *CHS_WAR_EPSONHEAD_NOT_CONNECT;//��ͷδ����.
extern unsigned short *CHS_WAR_EPSON_FPGA_ULTRADATA;//����FPGA���������̫��.
extern unsigned short *CHS_WAR_EPSON_FPGA_LESSDATA;//����FPGA���������̫��.
extern unsigned short *CHS_WAR_EPSON_FPGA_ERR;//ͷ��FPGA����
extern unsigned short *CHS_WAR_EPSON_LVDS_ERR;//LVDSʧ��
extern unsigned short *CHS_WAR_EPSON_REPORT_LVDS_ERR;//LVDSʧ��
extern unsigned short *CHS_WAR_UNKNOWN_NOZZLE_COUNT;//��ǰ��ͷ��������δ֪��
extern unsigned short *CHS_UPDATE_SUCCESS;//�����ɹ�.
extern unsigned short *CHS_UPDATEERR_DSP_BEGIN_TIMEOUT;//DSP��ʼ�������ʱ.
extern unsigned short *CHS_UPDATEERR_DSP_DATA_TIMEOUT;//DSP���ݳ�ʱ.
extern unsigned short *CHS_UPDATEERR_DSP_END_TIMEOUT;//DSP������ʱ.
extern unsigned short *CHS_UPDATEERR_ILIGALFILE;//����������ļ���ʽ.
extern unsigned short *CHS_UPDATEERR_INTERNAL_DATA;//���Ϸ��������ļ�.
extern unsigned short *CHS_UPDATEERR_CHECKSUM;//����У�������.
extern unsigned short *CHS_UPDATEERR_EREASE;//ARM �������.
extern unsigned short *CHS_UPDATEERR_FLASHOP;//Flash����.
extern unsigned short *CHS_UPDATEERR_GZ_ILIGALFILE;//��Ҫ�ر�̼���
extern unsigned short *CHS_UPDATEERR_INKP_ILIGALFILE;//��Ҫ����īˮ����̼���
extern unsigned short *CHS_UPDATEERR_16H_ILIGALFILE;//8ͷӲ���޷�����16ͷ�Ĺ̼���
extern unsigned short *CHS_UNKNOWN_ERR;//δ֪�Ĵ���

extern unsigned short *CHS_STATUS_SVC;//����
extern unsigned short *CHS_STATUS_FTA;//����
extern unsigned short *CHS_STATUS_ERR;//����
extern unsigned short *CHS_STATUS_ERR_AUTO;//����
extern unsigned short *CHS_STATUS_WAR;//����
extern unsigned short *CHS_STATUS_INI;//��ʼ��
extern unsigned short *CHS_STATUS_RDY;//����
#ifdef FUNC_MAINTAIN
extern unsigned short *CHS_STATUS_MAINTAIN;//ά��
#endif
extern unsigned short *CHS_STATUS_MOVING;//�ƶ�
extern unsigned short *CHS_STATUS_PRINT;//��ӡ
extern unsigned short *CHS_STATUS_PAUSE;//��ͣ 
extern unsigned short *CHS_STATUS_PAUSE_1;//��ͣ 
extern unsigned short *CHS_STATUS_PAUSE_2;//��ͣ 
extern unsigned short *CHS_STATUS_PAUSE_3;//��ͣ 
extern unsigned short *CHS_STATUS_CLEANING;//��ϴ
extern unsigned short *CHS_STATUS_CANCELING;//ȡ��
extern unsigned short *CHS_STATUS_UPDATING;//����
#else
extern unsigned short ErrorCodeCHS[];
extern unsigned short MenuStr_2_ID3FF_Percent[];

extern unsigned short CHS_SVC_SX2[];//��USB chip�з������.
extern unsigned short CHS_SVC_FPGA0[];//Service Call: chip1.
extern unsigned short CHS_SVC_FPGA1[];//Service Call: chip2.
extern unsigned short CHS_SVC_FPGA2[];//Service Call: chip3.
extern unsigned short CHS_SVC_FPGA3[];//Service Call: chip4
extern unsigned short CHS_SVC_UPDATE_FAIL[];//Service Call: chip5.
extern unsigned short CHS_SVC_BYHX_DATA[];//Service Call: 6.
extern unsigned short CHS_SVC_EEPROM_CHK[];//BYHX_TOOL check EEPROM û��ͨ����
extern unsigned short CHS_SVC_SDRAM_CHECK[];//SDRAM ��Checkû��ͨ��
extern unsigned short CHS_SVC_FLASH[];//�޷���Falsh��ȡFPGA. 
extern unsigned short CHS_SVC_SDRAM_NOMATCH[];//SDRAM ̫С������֧�ֵ�ǰ�����á�
extern unsigned short CHS_SVC_READBOARDID_FAIL[];//���������
extern unsigned short CHS_FTA_SX2RESET[];//USB chip�쳣����
extern unsigned short CHS_FTA_INTERNAL_WRONGHEADER[];//�ڲ����� 1.
extern unsigned short CHS_FTA_INTERNAL_WRONGHEADERSIZE[];//�ڲ����� 2.
extern unsigned short CHS_FTA_INTERNAL_JOBSTARTHEADER[];//�ڲ����� 3.
extern unsigned short CHS_FTA_INTERNAL_BANDDATASIZE[];//�ڲ����� 4.
extern unsigned short CHS_FTA_INTERNAL_WRONGFORMAT[];//�ڲ����� 5.
extern unsigned short CHS_FTA_INTERNAL_DMA0WORKING[];//�ڲ����� 6.
extern unsigned short CHS_FTA_INTERNAL_PRINTPOINT[];//�ڲ����� 7.
extern unsigned short CHS_FTA_INTERNAL_OLIMIT[];//�ڲ����� 8.
extern unsigned short CHS_FTA_INTERNAL_OPPLIMIT[];//�ڲ����� 9.
extern unsigned short CHS_FTA_DSPINITS1[];//�˶�step 1.
extern unsigned short CHS_FTA_DSPINITS2[];//�˶�step 2.
extern unsigned short CHS_FTA_HEADINITS1[];//ͷ��step1.
extern unsigned short CHS_FTA_HEADINITS2[];//ͷ��step2.
extern unsigned short CHS_FTA_HEADTOMAINROAD[];//LVDS����.
extern unsigned short CHS_FTA_INTERNAL_BANDDIRECTION[];//Band�����еķ���ֵ��������
extern unsigned short CHS_FTA_DSPUPDATE_FAIL[];//DSP����ʧ��.
extern unsigned short CHS_FTA_EEPROM_READ[];//EEPROM��ȡʧ��	
extern unsigned short CHS_FTA_EEPROM_WRITE[];//EEPROMд��ʧ��
extern unsigned short CHS_FTA_FACTORY_DATA[];//���ӳ���û�г�ʼ��.
extern unsigned short CHS_FTA_HEADBOARD_RESET[];//ͷ�帴λ.
extern unsigned short CHS_FTA_SPECTRAHVBINITS1[];//Spectra��ѹ���޷��ڵ�1����ʼ��.
extern unsigned short CHS_FTA_PRINTHEAD_NOTMATCH[];//ͷ����������ݲ�ƥ��,�����ó������ݻ��߸���ͷ��.
extern unsigned short CHS_FTA_MANUFACTURERID_NOTMATCH[];//���ӵĳ���ID��ƥ��,�������̼�. 
extern unsigned short CHS_FTA_LIMITEDTIME_RUNOUT[];//���ش���: ������ʱʱ�䣬�������µ�����.
extern unsigned short CHS_FTA_INTERNAL_SW1[];//�ڲ�����,�հ�Band��Y�����Ϊ��.
extern unsigned short CHS_FTA_USB1_USB1CONNECT[];//USB1.1����.
extern unsigned short CHS_FTA_UILANGUAGE_NOT_MATCH[];//UIʹ�õ�������Ȩ�޲����� �������������Ի���������������
extern unsigned short CHS_FTA_INTERNAL_WRONGPINCONF[];//PINCONFд��FPGA����
extern unsigned short CHS_FTA_FACTORY_COLORNUM_WRONG[];//����������д�����ɫ������.
extern unsigned short CHS_FTA_HB_EEPROM_WRT_ERR[];//ͷ���EEPROMд��ʧ��
extern unsigned short CHS_FTA_HB_OVERHEAT[];//��ͷ���ȣ����м��ȱ�ǿ�йرա�
extern unsigned short CHS_FTA_SHAKEHAND_ERR[];//���������߰汾����û��ͨ������Э�顣
extern unsigned short CHS_FTA_SWVERSION_ERR[];//�̼�Ҫ�����������汾���汾����
extern unsigned short CHS_FTA_NOT_SUPPORT_2C_SHARE_1H[];//��ǰϵͳ���ò�֧��һͷ��ɫ��
extern unsigned short CHS_FTA_LIMITEDINK_RUNOUT[];//����īˮ�������ƣ��������������
extern unsigned short CHS_FTA_SWVERSION_ERR_INK_PWD[];//�̼�Ҫ������汾֧��īˮ���룬�汾����
extern unsigned short CHS_FTA_EPSON_HEAD_BAD[];//������ID����
extern unsigned short CHS_FTA_EPSON_HEAD_FPGA_ERR[];//ͷ��FPGA����.
extern unsigned short CHS_FTA_SECURITY_CHIP_ERR[];//д�������.
extern unsigned short CHS_FTA_CALIBRATION_DATA[];//������ʼ�����ó���
extern unsigned short CHS_ERR_EP0OVERUN_SETUPDATA[];//EP0������
extern unsigned short CHS_ERR_UART1_TXTIMEOUT[];//ͷ��COM��ʱ.
extern unsigned short CHS_ERR_UART2_TXTIMEOUT[];//�˶�COM��ʱ.
extern unsigned short CHS_ERR_INTERNAL_PRINTDATA[];//��ӡ���ݺ͵��Ƶ�ʲ�ƥ��.
extern unsigned short CHS_ERR_FPGA_LESSDATA[];//��ӡ����С�ڵ��Ƶ��
extern unsigned short CHS_ERR_FPGA_ULTRADATA[];//��ӡ���ݳ������Ƶ��.
extern unsigned short CHS_ERR_FPGA_WRONGCHS[];//��ӡ�����ݺͿ�������ƥ��.
extern unsigned short CHS_ERR_UV_CTR_WRONGCHS[];//�ڲ�״̬.
extern unsigned short CHS_ERR_FPGA_WRONGCOMMAND[];//FPGA �յ����������
extern unsigned short CHS_ERR_MOTION_SPEED_BAD[];//�˶��ٶ�̫��򲻾��ȣ����ݻ��ڳ��飬ȴ�е������
extern unsigned short CHS_ERR_INTERNAL_MOVING_TIMEOUT[];//�˶������30���û���յ��˶��������
extern unsigned short CHS_ERR_INTERNAL_WRONGAUTOCLEAN[];//�����AUTOCLEAN����.
extern unsigned short CHS_ERR_INTERNAL_WRONGBANDINFO[];//�����AUTOCLEAN����.
extern unsigned short CHS_ERR_INTERNAL_DEBUG1[];//����״̬1
extern unsigned short CHS_ERR_INTERNAL_DEBUG2[];//����״̬2
extern unsigned short CHS_INI_ARM[];//���ڳ�ʼ��ARM.
extern unsigned short CHS_INI_SX2[];//���ڳ�ʼ��USB
extern unsigned short CHS_INI_FPGA[];//���ڳ�ʼ��FPGA
extern unsigned short CHS_INI_DSP[];//���ڳ�ʼ��DSP.
extern unsigned short CHS_INI_HEADBOARD[];//���ڳ�ʼ��ͷ��
extern unsigned short CHS_INI_HVB[];//��װ Spectra ��ѹ��.
extern unsigned short CHS_WAR_UNKNOWNHEADERTYPE[];//��֪���ľ���
extern unsigned short CHS_WAR_EP0OVERUN_REQUEST_IGNORE[];//EP0���.
extern unsigned short CHS_WAR_PUMP_CYAN[];//��ɫ���ڱ�ī.
extern unsigned short CHS_WAR_PUMP_MAGENTA[];//Ʒɫ���ڱ�ī.
extern unsigned short CHS_WAR_PUMP_YELLOW[];//��ɫ���ڱ�ī.
extern unsigned short CHS_WAR_PUMP_BLACK[];//��ɫ���ڱ�ī.
extern unsigned short CHS_WAR_PUMP_LIGHTCYAN[];//ǳ��ɫ���ڱ�ī.
extern unsigned short CHS_WAR_PUMP_LIGHTMAGENTA[];//ǳƷɫ���ڱ�ī.
extern unsigned short CHS_WAR_TIME_PASSWORD_WRONGINPUT[];//������ʱ������󣬺��к��зǷ��ַ�; 
extern unsigned short CHS_WAR_TIME_PASSWORD_WRONG[];//����һ���Ϸ���ʱ����; 
extern unsigned short CHS_WAR_TIME_PASSWORD_MANUFACTURERIDNOTMATCH[];//��ʱ����ͳ��̲�ƥ��
extern unsigned short CHS_WAR_TIME_PASSWORD_BOARDIDNOTMATCH[];//��ʱ����Ͱ��Ӳ�ƥ��
extern unsigned short CHS_WAR_LIMITEDTIME_FIRST[];//��һ�ξ���:����100��Сʱ�ͳ�����ʱ��, ���򳧼���ȡ����.
extern unsigned short CHS_WAR_LIMITEDTIME_SECOND[];//�ڶ��ξ���: ����50��Сʱ�ͳ�����ʱ��,���򳧼���ȡ����.
extern unsigned short CHS_WAR_LIMITEDTIME_LAST[];//���һ�ξ���: ����1��Сʱ�ͳ�����ʱ��ֹͣ��ӡ, �������򳧼���ȡ����.
extern unsigned short CHS_WAR_OPTION_PASSWORD_WRONGINPUT[];//����ѡ��������󣬺��з�0~F��ֵ
extern unsigned short CHS_WAR_OPTION_PASSWORD_WRONG[];//����һ���Ϸ�ѡ������
extern unsigned short CHS_WAR_OPTION_PASSWORD_MANUFACTURERIDNOTMATCH[];//ѡ������ͳ��̲�ƥ��
extern unsigned short CHS_WAR_OPTION_PASSWORD_BOARDIDNOTMATCH[];//ѡ������Ͱ��Ӳ�ƥ��
extern unsigned short CHS_WAR_PUMP_PROHIBIT_SENSOR[];//��ī��ȫƿ����, ����ī��ֹͣ��ī.
extern unsigned short CHS_WAR_OVER_SPEED_NOT_SUPPORT[];//��ͼ�ڲ�֧�ֳ�Ƶ��ͷ��汾��ʹ�ó�Ƶ, ϵͳǿ��ʹ�ø��ٴ�ӡ.
extern unsigned short CHS_WAR_INK_PASSWORD_WRONGINPUT[];//����īˮ������󣬺��з�0~F��ֵ
extern unsigned short CHS_WAR_INK_PASSWORD_WRONG[];//����һ���Ϸ�īˮ����
extern unsigned short CHS_WAR_INK_PASSWORD_MANUFACTURERIDNOTMATCH[];//īˮ����ͳ��̲�ƥ��
extern unsigned short CHS_WAR_INK_PASSWORD_BOARDIDNOTMATCH[];//īˮ����Ͱ��Ӳ�ƥ��
extern unsigned short CHS_WAR_LIMITEDINK_FIRST[];//����10���ͳ���īˮ�����ˣ���һ�ξ���
extern unsigned short CHS_WAR_LIMITEDINK_SECOND[];//����5���ͳ���īˮ�����ˣ��ڶ��ξ���
extern unsigned short CHS_WAR_LIMITEDINK_LAST[];//����1���ͳ���īˮ�����ˣ����һ�ξ���
extern unsigned short CHS_WAR_INK_PASSWORD_UNKNOWN_DOT_VOLUME[];//��ǰ��ͷ��֧��īˮ���빦��.
extern unsigned short CHS_WAR_PUMP_SPOTCOLOR1[];//רɫ1���ڱ�ī.
extern unsigned short CHS_WAR_PUMP_SPOTCOLOR2[];//רɫ2���ڱ�ī.
extern unsigned short CHS_WAR_FPGA_LESSDATA[];//��ӡ����С�ڵ����.
extern unsigned short CHS_WAR_FPGA_ULTRADATA[];//��ӡ���ݶ��ڵ����.
extern unsigned short CHS_WAR_EPSONHEAD_TEMP_TOO_LOW[];//��ͷ�¶�̫��.
extern unsigned short CHS_WAR_EPSONHEAD_TEMP_TOO_HIGH[];//��ͷ�¶�̫��.
extern unsigned short CHS_WAR_EPSONHEAD_NOT_CONNECT[];//��ͷδ����.
extern unsigned short CHS_WAR_EPSON_FPGA_ULTRADATA[];//����FPGA���������̫��.
extern unsigned short CHS_WAR_EPSON_FPGA_LESSDATA[];//����FPGA���������̫��.
extern unsigned short CHS_WAR_UNKNOWN_NOZZLE_COUNT[];//��ǰ��ͷ��������δ֪��
extern unsigned short CHS_UPDATE_SUCCESS[];//�����ɹ�.
extern unsigned short CHS_UPDATEERR_DSP_BEGIN_TIMEOUT[];//DSP��ʼ�������ʱ.
extern unsigned short CHS_UPDATEERR_DSP_DATA_TIMEOUT[];//DSP���ݳ�ʱ.
extern unsigned short CHS_UPDATEERR_DSP_END_TIMEOUT[];//DSP������ʱ.
extern unsigned short CHS_UPDATEERR_ILIGALFILE[];//����������ļ���ʽ.
extern unsigned short CHS_UPDATEERR_INTERNAL_DATA[];//���Ϸ��������ļ�.
extern unsigned short CHS_UPDATEERR_CHECKSUM[];//����У�������.
extern unsigned short CHS_UPDATEERR_EREASE[];//ARM �������.
extern unsigned short CHS_UPDATEERR_FLASHOP[];//Flash����.
extern unsigned short CHS_UPDATEERR_GZ_ILIGALFILE[];//��Ҫ�ر�̼���
extern unsigned short CHS_UPDATEERR_INKP_ILIGALFILE[];//��Ҫ����īˮ����̼���
extern unsigned short CHS_UPDATEERR_16H_ILIGALFILE[];//8ͷӲ���޷�����16ͷ�Ĺ̼���
extern unsigned short CHS_UNKNOWN_ERR[];//δ֪�Ĵ���

extern unsigned short CHS_STATUS_SVC[];//����
extern unsigned short CHS_STATUS_FTA[];//����
extern unsigned short CHS_STATUS_ERR[];//����
extern unsigned short CHS_STATUS_ERR_AUTO[];//����
extern unsigned short CHS_STATUS_WAR[];//����
extern unsigned short CHS_STATUS_INI[];//��ʼ��
extern unsigned short CHS_STATUS_RDY[];//����
extern unsigned short CHS_STATUS_MOVING[];//�ƶ�
extern unsigned short CHS_STATUS_PRINT[];//��ӡ
extern unsigned short CHS_STATUS_PAUSE[];//��ͣ 
extern unsigned short CHS_STATUS_CLEANING[];//��ϴ
extern unsigned short CHS_STATUS_CANCELING[];//ȡ��
extern unsigned short CHS_STATUS_UPDATING[];//����
#endif
//MainInfo field
extern CHAR MainInfo_MediaWidth[8];      //value is float *. unit is inch.
extern CHAR MainInfo_PrintOrigin[8];     //value is float *. unit is inch.
#ifdef RIPSTAR_FLAT_EX
extern CHAR MainInfo_MediaLength[8];      //value is float *. unit is inch.
extern CHAR MainInfo_YOrigin[8];     //value is float *. unit is inch.
extern CHAR MainInfo_MediaHigh[8];      //value is float *. unit is inch.
extern CHAR MainInfo_ZOrigin[8];     //value is float *. unit is inch.
#endif
extern CHAR MainInfo_PassNum[8];         //value is INT8U *. 
extern CHAR MainInfo_Resolution[8];      //value is INT16U *. 
extern CHAR MainInfo_PrinterName[16];     //value is C string. 
extern CHAR MainInfo_ManufactureName[16]; //value is C string. 
extern CHAR MainInfo_HeadHeightLevel[8]; //value is INT8U *. the valid value is 1,2,3(high, middle, low).
extern CHAR MainInfo_QualitySetting[8];  //value is INT8U *. the valid value is 0,1,2(OFF/type1/type2).
extern CHAR MainInfo_CleaningStrong[8];  //value is INT8U *. the valid value is 1,2,3(weak, normal, strong).
extern CHAR MainInfo_DataReceiving[8];   //value is INT8U *. the valid value is 0,1(FALSE/TRUE).
extern CHAR MainInfo_Busy[8];            //value is INT8U *. the valid value is 0,1(FALSE/TRUE).
extern CHAR MainInfo_strinfo[16];
extern CHAR MainInfo_percent[8];
extern CHAR MainInfo_errorcode[8];

//
extern INT8U imgTop[8];
extern INT8U imgBot[8];
extern INT8U imgLeft[8];
extern INT8U imgRight[8];
extern INT8U imgZero[16];
#endif