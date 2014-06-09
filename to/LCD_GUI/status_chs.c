
#include "resources.h"

#ifdef IIC_Key_Board_LCD
#ifdef LCD_MODULE_ZX19264M1A
unsigned short ErrorCodeCHS[]={'0','X','0','0','0','0','0','0','0','0',0 };

//��USB chip�з������.
unsigned short *CHS_SVC_SX2 = (unsigned short*)"��USB chip�з������.";


//Service Call: chip1.
unsigned short *CHS_SVC_FPGA0= (unsigned short*)"Service Call: chip1.";


//Service Call: chip2.
unsigned short *CHS_SVC_FPGA1= (unsigned short*)"Service Call: chip2.";


//Service Call: chip3.
unsigned short *CHS_SVC_FPGA2= (unsigned short*)"Service Call: chip3.";


//Service Call: chip4
unsigned short *CHS_SVC_FPGA3= (unsigned short*)"Service Call: chip4.";


//Service Call: chip5.
unsigned short *CHS_SVC_UPDATE_FAIL= (unsigned short*)"Service Call: chip5.";


//Service Call: 6.
unsigned short *CHS_SVC_BYHX_DATA= (unsigned short*)"Service Call: chip6.";


//BYHX_TOOL check EEPROM û��ͨ����
unsigned short *CHS_SVC_EEPROM_CHK= (unsigned short*)"BYHX_TOOL check EEPROM û��ͨ��";


//SDRAM ��Checkû��ͨ��
unsigned short *CHS_SVC_SDRAM_CHECK= (unsigned short*)"SDRAM ��Checkû��ͨ��";


//�޷���Falsh��ȡFPGA.
unsigned short *CHS_SVC_FLASH= (unsigned short*)"�޷���Falsh��ȡFPGA";

//SDRAM ̫С������֧�ֵ�ǰ�����á�
unsigned short *CHS_SVC_SDRAM_NOMATCH= (unsigned short*)"SDRAM ̫С������֧�ֵ�ǰ�����á�";

//���������
unsigned short *CHS_SVC_READBOARDID_FAIL= (unsigned short*)"���������";

//MOTION��ʼ��ʧ��
unsigned short *CHS_SVC_MOTION_FAIL= (unsigned short*)"MOTION��ʼ��ʧ��";

//��ʼ��ͷ�����оƬ
unsigned short *CHS_SVC_HEADBOARD_FAIL= (unsigned short*)"��ʼ��ͷ�����оƬʧ��";

//�ػ�ģʽ����رմ�ӡ��
unsigned short *CHS_SVC_POWEROFF_MODE= (unsigned short*)"�ػ�ģʽ����رմ�ӡ��";

//USB chip�쳣����
unsigned short *CHS_FTA_SX2RESET= (unsigned short*)"USB chip�쳣����";


//�ڲ����� 1.
unsigned short *CHS_FTA_INTERNAL_WRONGHEADER= (unsigned short*)"�ڲ����� 1";

//�ڲ����� 2.
unsigned short *CHS_FTA_INTERNAL_WRONGHEADERSIZE= (unsigned short*)"�ڲ����� 2";

//�ڲ����� 3.
unsigned short *CHS_FTA_INTERNAL_JOBSTARTHEADER= (unsigned short*)"�ڲ����� 3";

//�ڲ����� 4.
unsigned short *CHS_FTA_INTERNAL_BANDDATASIZE = (unsigned short*)"�ڲ����� 4";

//�ڲ����� 5.
unsigned short *CHS_FTA_INTERNAL_WRONGFORMAT= (unsigned short*)"�ڲ����� 5";

//�ڲ����� 6.
unsigned short *CHS_FTA_INTERNAL_DMA0WORKING= (unsigned short*)"�ڲ����� 6";
//�ڲ����� 7.
unsigned short *CHS_FTA_INTERNAL_PRINTPOINT= (unsigned short*)"�ڲ����� 7";

//�ڲ����� 8.
unsigned short *CHS_FTA_INTERNAL_OLIMIT= (unsigned short*)"�ڲ����� 8";

//�ڲ����� 9.
unsigned short *CHS_FTA_INTERNAL_OPPLIMIT= (unsigned short*)"�ڲ����� 9";

//�˶�step 1.
unsigned short *CHS_FTA_DSPINITS1= (unsigned short*)"�˶�step 1";

//�˶�step 2.
unsigned short *CHS_FTA_DSPINITS2 = (unsigned short*)"�˶�step 2";


//ͷ��step1.
unsigned short *CHS_FTA_HEADINITS1 = (unsigned short*)"ͷ��step1";

//ͷ��step2.
unsigned short *CHS_FTA_HEADINITS2 = (unsigned short*)"ͷ��step2";

//LVDS����.
unsigned short *CHS_FTA_HEADTOMAINROAD = (unsigned short*)"LVDS����";

//Band�����еķ���ֵ��������
unsigned short *CHS_FTA_INTERNAL_BANDDIRECTION = (unsigned short*)"Band�����еķ���ֵ��������";

//DSP����ʧ��.
unsigned short *CHS_FTA_DSPUPDATE_FAIL=(unsigned short*)"DSP����ʧ��";

//EEPROM��ȡʧ��	
unsigned short *CHS_FTA_EEPROM_READ=(unsigned short*)"EEPROM��ȡʧ��	";

//EEPROMд��ʧ��
unsigned short *CHS_FTA_EEPROM_WRITE=(unsigned short*)"EEPROMд��ʧ��";


//���ӳ���û�г�ʼ��.
unsigned short *CHS_FTA_FACTORY_DATA=(unsigned short*)"���ӳ���û�г�ʼ��";

//ͷ�帴λ.
unsigned short *CHS_FTA_HEADBOARD_RESET=(unsigned short*)"ͷ�帴λ";

//Spectra��ѹ���޷��ڵ�1����ʼ��.
unsigned short *CHS_FTA_SPECTRAHVBINITS1=(unsigned short*)"Spectra��ѹ���޷��ڵ�1����ʼ��";

//ͷ����������ݲ�ƥ��,�����ó������ݻ��߸���ͷ��.
unsigned short *CHS_FTA_PRINTHEAD_NOTMATCH=(unsigned short*)"ͷ����������ݲ�ƥ��,�����ó������ݻ��߸���ͷ��";

//���ӵĳ���ID��ƥ��,�������̼�.
unsigned short *CHS_FTA_MANUFACTURERID_NOTMATCH=(unsigned short*)"���ӵĳ���ID��ƥ��,�������̼�";

//���ش���: ������ʱʱ�䣬�������µ�����.
unsigned short *CHS_FTA_LIMITEDTIME_RUNOUT=(unsigned short*)"���ش���: ������ʱʱ�䣬�������µ�����";


//�ڲ�����,�հ�Band��Y�����Ϊ��.
unsigned short *CHS_FTA_INTERNAL_SW1=(unsigned short*)"�ڲ�����,�հ�Band��Y�����Ϊ��";


//USB1.1����.
unsigned short *CHS_FTA_USB1_USB1CONNECT=(unsigned short*)"USB1.1����\n USB�������½�����...";

//UIʹ�õ�������Ȩ�޲����� �������������Ի���������������
unsigned short *CHS_FTA_UILANGUAGE_NOT_MATCH=(unsigned short*)"UIʹ�õ�������Ȩ�޲����� �������������Ի���������������";

//PINCONFд��FPGA����
unsigned short *CHS_FTA_INTERNAL_WRONGPINCONF=(unsigned short*)"PINCONFд��FPGA����";


//����������д�����ɫ������.
unsigned short *CHS_FTA_FACTORY_COLORNUM_WRONG=(unsigned short*)"����������д�����ɫ������";


//ͷ���EEPROMд��ʧ��
unsigned short *CHS_FTA_HB_EEPROM_WRT_ERR=(unsigned short*)"ͷ���EEPROMд��ʧ��";


//��ͷ���ȣ����м��ȱ�ǿ�йرա�
unsigned short *CHS_FTA_HB_OVERHEAT=(unsigned short*)"��ͷ���ȣ����м��ȱ�ǿ�йرա�";

//���������߰汾����û��ͨ������Э�顣
unsigned short *CHS_FTA_SHAKEHAND_ERR=(unsigned short*)"���������߰汾����û��ͨ������Э��";

//�̼�Ҫ�����������汾���汾����
unsigned short *CHS_FTA_SWVERSION_ERR=(unsigned short*)"�̼�Ҫ�����������汾���汾����";


//��ǰϵͳ���ò�֧��һͷ��ɫ��
unsigned short *CHS_FTA_NOT_SUPPORT_2C_SHARE_1H=(unsigned short*)"��ǰϵͳ���ò�֧��һͷ��ɫ";

//����īˮ�������ƣ��������������
unsigned short *CHS_FTA_LIMITEDINK_RUNOUT=(unsigned short*)"����īˮ�������ƣ��������������";

//�̼�Ҫ������汾֧��īˮ���룬�汾����
unsigned short *CHS_FTA_SWVERSION_ERR_INK_PWD=(unsigned short*)"�̼�Ҫ������汾֧��īˮ���룬�汾����";

//������ID����
unsigned short *CHS_FTA_EPSON_HEAD_BAD=(unsigned short*)"������ID����";


//ͷ��FPGA����.
unsigned short *CHS_FTA_EPSON_HEAD_FPGA_ERR=(unsigned short*)"ͷ��FPGA����";


//д�������.
unsigned short *CHS_FTA_SECURITY_CHIP_ERR=(unsigned short*)"д�������";

//������ʼ�����ó���
unsigned short *CHS_FTA_CALIBRATION_DATA=(unsigned short*)"������ʼ�����ó���";

//��ӡ���ݴ�������ʧ
unsigned short *CHS_FTA_PRINT_DATA_ERROR=(unsigned short*)"USB��ӡ���ݴ�������ʧ�������USB�߻�USB�˿�";
//FACTORY_DATA���ݴ�����Ҫ����д��
unsigned short *CHS_FTA_FACTORY_DATA_ERROR=(unsigned short*)"FACTORY_DATA���ݴ�����Ҫ����д��";
//��ī���
unsigned short *CHS_FTA_WASTE_INK_FULL = (unsigned short *)"��ī���";
//EP0������
unsigned short *CHS_ERR_EP0OVERUN_SETUPDATA=(unsigned short*)"EP0������";

//ͷ��COM��ʱ.
unsigned short *CHS_ERR_UART1_TXTIMEOUT=(unsigned short*)"ͷ��COM��ʱ";

//�˶�COM��ʱ.
unsigned short *CHS_ERR_UART2_TXTIMEOUT=(unsigned short*)"�˶�COM��ʱ";

//��ӡ���ݺ͵��Ƶ�ʲ�ƥ��.
unsigned short *CHS_ERR_INTERNAL_PRINTDATA=(unsigned short*)"��ӡ���ݺ͵��Ƶ�ʲ�ƥ��";

//��ӡ����С�ڵ��Ƶ��
unsigned short *CHS_ERR_FPGA_LESSDATA=(unsigned short*)"��ӡ����С�ڵ��Ƶ��";

//��ӡ���ݳ������Ƶ��.
unsigned short *CHS_ERR_FPGA_ULTRADATA=(unsigned short*)"��ӡ���ݳ������Ƶ��";

//��ӡ�����ݺͿ�������ƥ��.
unsigned short *CHS_ERR_FPGA_WRONGCHS=(unsigned short*)"��ӡ�����ݺͿ�������ƥ��";

//�ڲ�״̬.
unsigned short *CHS_ERR_UV_CTR_WRONGCHS=(unsigned short*)"�ڲ�״̬";

//FPGA �յ����������
unsigned short *CHS_ERR_FPGA_WRONGCOMMAND =(unsigned short*)"FPGA �յ����������";


//�˶��ٶ�̫��򲻾��ȣ����ݻ��ڳ��飬ȴ�е������
unsigned short *CHS_ERR_MOTION_SPEED_BAD =(unsigned short*)"�˶��ٶ�̫��򲻾��ȣ����ݻ��ڳ��飬ȴ�е������";

//�˶������30���û���յ��˶��������
unsigned short *CHS_ERR_INTERNAL_MOVING_TIMEOUT =(unsigned short*)"�˶������30���û���յ��˶��������";



//�����AUTOCLEAN����.
unsigned short *CHS_ERR_INTERNAL_WRONGAUTOCLEAN=(unsigned short*)"�����AUTOCLEAN����";

//�����AUTOCLEAN����.
unsigned short *CHS_ERR_INTERNAL_WRONGBANDINFO=(unsigned short*)"�����AUTOCLEAN����";


//����״̬1
unsigned short *CHS_ERR_INTERNAL_DEBUG1=(unsigned short*)"����״̬1";

//����״̬2
unsigned short *CHS_ERR_INTERNAL_DEBUG2=(unsigned short*)"����״̬2";


//���ڳ�ʼ��ARM.
unsigned short *CHS_INI_ARM=(unsigned short*)"���ڳ�ʼ��ARM";


//���ڳ�ʼ��USB
unsigned short *CHS_INI_SX2=(unsigned short*)"���ڳ�ʼ��USB";


//���ڳ�ʼ��FPGA
unsigned short *CHS_INI_FPGA=(unsigned short*)"���ڳ�ʼ��FPGA";



//���ڳ�ʼ��DSP.
unsigned short *CHS_INI_DSP=(unsigned short*)"���ڳ�ʼ��DSP";

//���ڳ�ʼ��ͷ��
unsigned short *CHS_INI_HEADBOARD=(unsigned short*)"���ڳ�ʼ��ͷ��";


//��װ Spectra ��ѹ��.
unsigned short *CHS_INI_HVB=(unsigned short*)"��װ Spectra ��ѹ��";

//��֪���ľ���
unsigned short *CHS_WAR_UNKNOWNHEADERTYPE=(unsigned short*)"��֪���ľ���";


//EP0���.
unsigned short *CHS_WAR_EP0OVERUN_REQUEST_IGNORE=(unsigned short*)"EP0���";


//��ɫ���ڱ�ī.
unsigned short *CHS_WAR_PUMP_CYAN=(unsigned short*)"��ɫ���ڱ�ī";

//Ʒɫ���ڱ�ī.
unsigned short *CHS_WAR_PUMP_MAGENTA=(unsigned short*)"Ʒɫ���ڱ�ī";


//��ɫ���ڱ�ī.
unsigned short *CHS_WAR_PUMP_YELLOW=(unsigned short*)"��ɫ���ڱ�ī";



//��ɫ���ڱ�ī.
unsigned short *CHS_WAR_PUMP_BLACK=(unsigned short*)"��ɫ���ڱ�ī";

//ǳ��ɫ���ڱ�ī.
unsigned short *CHS_WAR_PUMP_LIGHTCYAN=(unsigned short*)"ǳ��ɫ���ڱ�ī";
//ǳƷɫ���ڱ�ī.
unsigned short *CHS_WAR_PUMP_LIGHTMAGENTA=(unsigned short*)"ǳƷɫ���ڱ�ī";

//������ʱ������󣬺��к��зǷ��ַ�;
unsigned short *CHS_WAR_TIME_PASSWORD_WRONGINPUT=(unsigned short*)"������ʱ������󣬺��к��зǷ��ַ�";


//����һ���Ϸ���ʱ����;
unsigned short *CHS_WAR_TIME_PASSWORD_WRONG=(unsigned short*)"����һ���Ϸ���ʱ����";


//��ʱ����ͳ��̲�ƥ��
unsigned short *CHS_WAR_TIME_PASSWORD_MANUFACTURERIDNOTMATCH=(unsigned short*)"��ʱ����Ͱ��Ӳ�ƥ��";

//��ʱ����Ͱ��Ӳ�ƥ��
unsigned short *CHS_WAR_TIME_PASSWORD_BOARDIDNOTMATCH=(unsigned short*)"��ʱ����Ͱ��Ӳ�ƥ��";

//��һ�ξ���:����100��Сʱ�ͳ�����ʱ��, ���򳧼���ȡ����.
unsigned short *CHS_WAR_LIMITEDTIME_FIRST=(unsigned short*)"��һ�ξ���:����100��Сʱ�ͳ�����ʱ��, ���򳧼���ȡ����";


//�ڶ��ξ���: ����50��Сʱ�ͳ�����ʱ��,���򳧼���ȡ����.
unsigned short *CHS_WAR_LIMITEDTIME_SECOND=(unsigned short*)"�ڶ��ξ���: ����50��Сʱ�ͳ�����ʱ��,���򳧼���ȡ����.";

//���һ�ξ���: ����1��Сʱ�ͳ�����ʱ��ֹͣ��ӡ, �������򳧼���ȡ����.
unsigned short *CHS_WAR_LIMITEDTIME_LAST=(unsigned short*)"���һ�ξ���: ����1��Сʱ�ͳ�����ʱ��ֹͣ��ӡ, �������򳧼���ȡ����";

//����ѡ��������󣬺��з�0~F��ֵ
unsigned short *CHS_WAR_OPTION_PASSWORD_WRONGINPUT=(unsigned short*)"����ѡ��������󣬺��з�0~F��ֵ";

//����һ���Ϸ�ѡ������
unsigned short *CHS_WAR_OPTION_PASSWORD_WRONG=(unsigned short*)"����һ���Ϸ�ѡ������";

//ѡ������ͳ��̲�ƥ��
unsigned short *CHS_WAR_OPTION_PASSWORD_MANUFACTURERIDNOTMATCH=(unsigned short*)"ѡ������ͳ��̲�ƥ��";

//ѡ������Ͱ��Ӳ�ƥ��
unsigned short *CHS_WAR_OPTION_PASSWORD_BOARDIDNOTMATCH=(unsigned short*)"ѡ������Ͱ��Ӳ�ƥ��";

//��ī��ȫƿ����, ����ī��ֹͣ��ī.
unsigned short *CHS_WAR_PUMP_PROHIBIT_SENSOR=(unsigned short*)"��ī��ȫƿ����, ����ī��ֹͣ��ī";


//��ͼ�ڲ�֧�ֳ�Ƶ��ͷ��汾��ʹ�ó�Ƶ, ϵͳǿ��ʹ�ø��ٴ�ӡ.
unsigned short *CHS_WAR_OVER_SPEED_NOT_SUPPORT=(unsigned short*)"��ͼ�ڲ�֧�ֳ�Ƶ��ͷ��汾��ʹ�ó�Ƶ, ϵͳǿ��ʹ�ø��ٴ�ӡ";

//����īˮ������󣬺��з�0~F��ֵ
unsigned short *CHS_WAR_INK_PASSWORD_WRONGINPUT=(unsigned short*)"����īˮ������󣬺��з�0~F��ֵ";


//����һ���Ϸ�īˮ����
unsigned short *CHS_WAR_INK_PASSWORD_WRONG=(unsigned short*)"����һ���Ϸ�īˮ����";

//īˮ����ͳ��̲�ƥ��
unsigned short *CHS_WAR_INK_PASSWORD_MANUFACTURERIDNOTMATCH=(unsigned short*)"īˮ����ͳ��̲�ƥ��";

//īˮ����Ͱ��Ӳ�ƥ��
unsigned short *CHS_WAR_INK_PASSWORD_BOARDIDNOTMATCH=(unsigned short*)"īˮ����Ͱ��Ӳ�ƥ��";

//����10���ͳ���īˮ�����ˣ���һ�ξ���
unsigned short *CHS_WAR_LIMITEDINK_FIRST=(unsigned short*)"����10���ͳ���īˮ�����ˣ���һ�ξ���";

//����5���ͳ���īˮ�����ˣ��ڶ��ξ���
unsigned short *CHS_WAR_LIMITEDINK_SECOND=(unsigned short*)"����5���ͳ���īˮ�����ˣ��ڶ��ξ���";

//����1���ͳ���īˮ�����ˣ����һ�ξ���
unsigned short *CHS_WAR_LIMITEDINK_LAST=(unsigned short*)"����1���ͳ���īˮ�����ˣ����һ�ξ���";


//��ǰ��ͷ��֧��īˮ���빦��.
unsigned short *CHS_WAR_INK_PASSWORD_UNKNOWN_DOT_VOLUME=(unsigned short*)"��ǰ��ͷ��֧��īˮ���빦��";


//רɫ1���ڱ�ī.
unsigned short *CHS_WAR_PUMP_SPOTCOLOR1=(unsigned short*)"רɫ1���ڱ�ī";


//רɫ2���ڱ�ī.
unsigned short *CHS_WAR_PUMP_SPOTCOLOR2 =(unsigned short*)"רɫ2���ڱ�ī";


//��ӡ����С�ڵ����.
unsigned short *CHS_WAR_FPGA_LESSDATA=(unsigned short*)"��ӡ����С�ڵ����";

//��ӡ���ݶ��ڵ����.
unsigned short *CHS_WAR_FPGA_ULTRADATA=(unsigned short*)"��ӡ���ݶ��ڵ����";

//��ͷ�¶�̫��.
unsigned short *CHS_WAR_EPSONHEAD_TEMP_TOO_LOW=(unsigned short*)"��ͷ�¶�̫��";


//��ͷ�¶�̫��.
unsigned short *CHS_WAR_EPSONHEAD_TEMP_TOO_HIGH=(unsigned short*)"��ͷ�¶�̫��";


//��ͷδ����.
unsigned short *CHS_WAR_EPSONHEAD_NOT_CONNECT=(unsigned short*)"��ͷδ����";


//����FPGA���������̫��.
unsigned short *CHS_WAR_EPSON_FPGA_ULTRADATA=(unsigned short*)"����FPGA���������̫��";

//����FPGA���������̫��.
unsigned short *CHS_WAR_EPSON_FPGA_LESSDATA=(unsigned short*)"����FPGA���������̫��";

//ͷ��FPGA����.
unsigned short *CHS_WAR_EPSON_FPGA_ERR=(unsigned short*)"ͷ��FPGA����";

//����LVDSʧ��
unsigned short *CHS_WAR_EPSON_LVDS_ERR=(unsigned short*)"����LVDSʧ��";

//ͷ��LVDSʧ��
unsigned short *CHS_WAR_EPSON_REPORT_LVDS_ERR=(unsigned short*)"ͷ��LVDSʧ��";
//��ǰ��ͷ��������δ֪��
unsigned short *CHS_WAR_UNKNOWN_NOZZLE_COUNT=(unsigned short*)"��ǰ��ͷ��������δ֪";

//�����ɹ�.
unsigned short *CHS_UPDATE_SUCCESS=(unsigned short*)"�����ɹ�";


//DSP��ʼ�������ʱ.
unsigned short *CHS_UPDATEERR_DSP_BEGIN_TIMEOUT=(unsigned short*)"DSP��ʼ�������ʱ";


//DSP���ݳ�ʱ.
unsigned short *CHS_UPDATEERR_DSP_DATA_TIMEOUT=(unsigned short*)"DSP���ݳ�ʱ";

//DSP������ʱ.
unsigned short *CHS_UPDATEERR_DSP_END_TIMEOUT=(unsigned short*)"DSP������ʱ";


//����������ļ���ʽ.
unsigned short *CHS_UPDATEERR_ILIGALFILE=(unsigned short*)"����������ļ���ʽ";

//���Ϸ��������ļ�.
unsigned short *CHS_UPDATEERR_INTERNAL_DATA=(unsigned short*)"���Ϸ��������ļ�";


//����У�������.
unsigned short *CHS_UPDATEERR_CHECKSUM=(unsigned short*)"����У�������";


//ARM �������.
unsigned short *CHS_UPDATEERR_EREASE=(unsigned short*)"ARM �������";


//Flash����.
unsigned short *CHS_UPDATEERR_FLASHOP=(unsigned short*)"Flash����";


//��Ҫ�ر�̼���
unsigned short *CHS_UPDATEERR_GZ_ILIGALFILE=(unsigned short*)"��Ҫ�ر�̼�";


//��Ҫ����īˮ����̼���
unsigned short *CHS_UPDATEERR_INKP_ILIGALFILE=(unsigned short*)"��Ҫ����īˮ����̼�";


//8ͷӲ���޷�����16ͷ�Ĺ̼���
unsigned short *CHS_UPDATEERR_16H_ILIGALFILE=(unsigned short*)"8ͷӲ���޷�����16ͷ�Ĺ̼�";

//δ֪�Ĵ���
unsigned short *CHS_UNKNOWN_ERR=(unsigned short*)"δ֪�Ĵ���";

unsigned short *CHS_STATUS_SVC = (unsigned short*)"SVC����:";
unsigned short *CHS_STATUS_FTA = (unsigned short*)"FTA����:";
unsigned short *CHS_STATUS_ERR = (unsigned short*)"ERR����:";
unsigned short *CHS_STATUS_ERR_AUTO= (unsigned short*)"ERR_AUTO����:";
unsigned short *CHS_STATUS_WAR = (unsigned short*)"����:";
unsigned short *CHS_STATUS_INI = (unsigned short*)"��ʼ��:";
unsigned short *CHS_STATUS_RDY =  (unsigned short*)"����";
#ifdef FUNC_MAINTAIN
unsigned short *CHS_STATUS_MAINTAIN = (unsigned short *)"ά��";
#endif
unsigned short *CHS_STATUS_MOVING = (unsigned short*)"�ƶ�";
unsigned short *CHS_STATUS_PRINT = (unsigned short*)"��ӡ";
unsigned short *CHS_STATUS_PAUSE = (unsigned short*)"��ͣ";
unsigned short *CHS_STATUS_PAUSE_1 = (unsigned short*)"��ͣ(ѹֽ��̧��)";
unsigned short *CHS_STATUS_PAUSE_2 = (unsigned short*)"��ͣ(ǰ���̧��)";
unsigned short *CHS_STATUS_PAUSE_3 = (unsigned short*)"��ͣ(ȱֽ)";
unsigned short *CHS_STATUS_CLEANING =  (unsigned short*)"��ϴ";
unsigned short *CHS_STATUS_CANCELING = (unsigned short*)"�˳�";
unsigned short *CHS_STATUS_UPDATING = (unsigned short*)"����";
#else
unsigned short ErrorCodeCHS[]={'0','X','0','0','0','0','0','0','0','0',0 };

//��USB chip�з������.
unsigned short CHS_SVC_SX2[] = {
	CHAR_TABLE_OFFSET + 143,85,83,66,32,
	99,104,105,112,CHAR_TABLE_OFFSET + 93,
	CHAR_TABLE_OFFSET + 144,CHAR_TABLE_OFFSET + 145,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,46, 0 };


//Service Call: chip1.
unsigned short CHS_SVC_FPGA0[] = {
	83,101,114,118,105,
	99,101,32,67,97,
	108,108,58,32,99,
	104,105,112,49,46, 0 };


//Service Call: chip2.
unsigned short CHS_SVC_FPGA1[] = {
	83,101,114,118,105,
	99,101,32,67,97,
	108,108,58,32,99,
	104,105,112,50,46, 0 };


//Service Call: chip3.
unsigned short CHS_SVC_FPGA2[] = {
	83,101,114,118,105,
	99,101,32,67,97,
	108,108,58,32,99,
	104,105,112,51,46, 0 };


//Service Call: chip4
unsigned short CHS_SVC_FPGA3[] = {
	83,101,114,118,105,
	99,101,32,67,97,
	108,108,58,32,99,
	104,105,112,52, 0 };


//Service Call: chip5.
unsigned short CHS_SVC_UPDATE_FAIL[] = {
	83,101,114,118,105,
	99,101,32,67,97,
	108,108,58,32,99,
	104,105,112,53,46, 0 };


//Service Call: 6.
unsigned short CHS_SVC_BYHX_DATA[] = {
	83,101,114,118,105,
	99,101,32,67,97,
	108,108,58,32,54,
	46, 0 };


//BYHX_TOOL check EEPROM û��ͨ����
unsigned short CHS_SVC_EEPROM_CHK[] = {
	66,89,72,88,95,
	84,79,79,76,32,
	99,104,101,99,107,
	32,69,69,80,82,
	79,77,32,CHAR_TABLE_OFFSET + 146,CHAR_TABLE_OFFSET + 147,
	CHAR_TABLE_OFFSET + 148,CHAR_TABLE_OFFSET + 149,CHAR_TABLE_OFFSET + 150, 0 };


//SDRAM ��Checkû��ͨ��
unsigned short CHS_SVC_SDRAM_CHECK[] = {
	83,68,82,65,77,
	32,CHAR_TABLE_OFFSET + 151,67,104,101,
	99,107,CHAR_TABLE_OFFSET + 146,CHAR_TABLE_OFFSET + 147,CHAR_TABLE_OFFSET + 148,
	CHAR_TABLE_OFFSET + 149, 0 };


//�޷���Falsh��ȡFPGA.
unsigned short CHS_SVC_FLASH[] = {
	CHAR_TABLE_OFFSET + 119,CHAR_TABLE_OFFSET + 152,CHAR_TABLE_OFFSET + 153,70,97,
	108,115,104,CHAR_TABLE_OFFSET + 154,CHAR_TABLE_OFFSET + 155,
	70,80,71,65,46,
	32, 0 };


//SDRAM ̫С������֧�ֵ�ǰ�����á�
unsigned short CHS_SVC_SDRAM_NOMATCH[] = {
	83,68,82,65,77,
	32,CHAR_TABLE_OFFSET + 156,CHAR_TABLE_OFFSET + 157,CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 6,
	CHAR_TABLE_OFFSET + 31,CHAR_TABLE_OFFSET + 159,CHAR_TABLE_OFFSET + 160,CHAR_TABLE_OFFSET + 161,CHAR_TABLE_OFFSET + 34,
	CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 19,CHAR_TABLE_OFFSET + 20,CHAR_TABLE_OFFSET + 150, 0 };


//���������
unsigned short CHS_SVC_READBOARDID_FAIL[] = {
	CHAR_TABLE_OFFSET + 154,CHAR_TABLE_OFFSET + 162,CHAR_TABLE_OFFSET + 36,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,
	CHAR_TABLE_OFFSET + 150, 0 };


//USB chip�쳣����
unsigned short CHS_FTA_SX2RESET[] = {
	85,83,66,32,99,
	104,105,112,CHAR_TABLE_OFFSET + 163,CHAR_TABLE_OFFSET + 164,
	CHAR_TABLE_OFFSET + 165,CHAR_TABLE_OFFSET + 166, 0 };


//�ڲ����� 1.
unsigned short CHS_FTA_INTERNAL_WRONGHEADER[] = {
	CHAR_TABLE_OFFSET + 114,CHAR_TABLE_OFFSET + 167,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,32,
	49,46, 0 };


//�ڲ����� 2.
unsigned short CHS_FTA_INTERNAL_WRONGHEADERSIZE[] = {
	CHAR_TABLE_OFFSET + 114,CHAR_TABLE_OFFSET + 167,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,32,
	50,46, 0 };


//�ڲ����� 3.
unsigned short CHS_FTA_INTERNAL_JOBSTARTHEADER[] = {
	CHAR_TABLE_OFFSET + 114,CHAR_TABLE_OFFSET + 167,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,32,
	51,46, 0 };


//�ڲ����� 4.
unsigned short CHS_FTA_INTERNAL_BANDDATASIZE[] = {
	CHAR_TABLE_OFFSET + 114,CHAR_TABLE_OFFSET + 167,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,32,
	52,46, 0 };


//�ڲ����� 5.
unsigned short CHS_FTA_INTERNAL_WRONGFORMAT[] = {
	CHAR_TABLE_OFFSET + 114,CHAR_TABLE_OFFSET + 167,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,32,
	53,46, 0 };


//�ڲ����� 6.
unsigned short CHS_FTA_INTERNAL_DMA0WORKING[] = {
	CHAR_TABLE_OFFSET + 114,CHAR_TABLE_OFFSET + 167,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,32,
	54,46, 0 };


//�ڲ����� 7.
unsigned short CHS_FTA_INTERNAL_PRINTPOINT[] = {
	CHAR_TABLE_OFFSET + 114,CHAR_TABLE_OFFSET + 167,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,32,
	55,46, 0 };


//�ڲ����� 8.
unsigned short CHS_FTA_INTERNAL_OLIMIT[] = {
	CHAR_TABLE_OFFSET + 114,CHAR_TABLE_OFFSET + 167,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,32,
	56,46, 0 };


//�ڲ����� 9.
unsigned short CHS_FTA_INTERNAL_OPPLIMIT[] = {
	CHAR_TABLE_OFFSET + 114,CHAR_TABLE_OFFSET + 167,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,32,
	57,46, 0 };


//�˶�step 1.
unsigned short CHS_FTA_DSPINITS1[] = {
	CHAR_TABLE_OFFSET + 168,CHAR_TABLE_OFFSET + 18,115,116,101,
	112,32,49,46, 0 };


//�˶�step 2.
unsigned short CHS_FTA_DSPINITS2[] = {
	CHAR_TABLE_OFFSET + 168,CHAR_TABLE_OFFSET + 18,115,116,101,
	112,32,50,46, 0 };


//ͷ��step1.
unsigned short CHS_FTA_HEADINITS1[] = {
	CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 36,115,116,101,
	112,49,46, 0 };


//ͷ��step2.
unsigned short CHS_FTA_HEADINITS2[] = {
	CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 36,115,116,101,
	112,50,46, 0 };


//LVDS����.
unsigned short CHS_FTA_HEADTOMAINROAD[] = {
	76,86,68,83,CHAR_TABLE_OFFSET + 69,
	CHAR_TABLE_OFFSET + 138,46, 0 };


//Band�����еķ���ֵ��������
unsigned short CHS_FTA_INTERNAL_BANDDIRECTION[] = {
	66,97,110,100,CHAR_TABLE_OFFSET + 90,
	CHAR_TABLE_OFFSET + 91,CHAR_TABLE_OFFSET + 93,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 99,CHAR_TABLE_OFFSET + 67,
	CHAR_TABLE_OFFSET + 64,CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 90,CHAR_TABLE_OFFSET + 91, 0 };


//DSP����ʧ��.
unsigned short CHS_FTA_DSPUPDATE_FAIL[] = {
	68,83,80,CHAR_TABLE_OFFSET + 171,CHAR_TABLE_OFFSET + 132,
	CHAR_TABLE_OFFSET + 172,CHAR_TABLE_OFFSET + 173,46, 0 };


//EEPROM��ȡʧ��	
unsigned short CHS_FTA_EEPROM_READ[] = {
	69,69,80,82,79,
	77,CHAR_TABLE_OFFSET + 154,CHAR_TABLE_OFFSET + 155,CHAR_TABLE_OFFSET + 172,CHAR_TABLE_OFFSET + 173,
	9, 0 };


//EEPROMд��ʧ��
unsigned short CHS_FTA_EEPROM_WRITE[] = {
	69,69,80,82,79,
	77,CHAR_TABLE_OFFSET + 174,CHAR_TABLE_OFFSET + 23,CHAR_TABLE_OFFSET + 172,CHAR_TABLE_OFFSET + 173, 0 };


//���ӳ���û�г�ʼ��.
unsigned short CHS_FTA_FACTORY_DATA[] = {
	CHAR_TABLE_OFFSET + 36,CHAR_TABLE_OFFSET + 175,CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 176,CHAR_TABLE_OFFSET + 146,
	CHAR_TABLE_OFFSET + 147,CHAR_TABLE_OFFSET + 177,CHAR_TABLE_OFFSET + 178,CHAR_TABLE_OFFSET + 55,46, 0 };


//ͷ�帴λ.
unsigned short CHS_FTA_HEADBOARD_RESET[] = {
	CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 36,CHAR_TABLE_OFFSET + 179,CHAR_TABLE_OFFSET + 180,46, 0 };


//Spectra��ѹ���޷��ڵ�1����ʼ��.
unsigned short CHS_FTA_SPECTRAHVBINITS1[] = {
	83,112,101,99,116,
	114,97,CHAR_TABLE_OFFSET + 7,CHAR_TABLE_OFFSET + 181,CHAR_TABLE_OFFSET + 36,
	CHAR_TABLE_OFFSET + 119,CHAR_TABLE_OFFSET + 152,CHAR_TABLE_OFFSET + 143,CHAR_TABLE_OFFSET + 182,49,
	CHAR_TABLE_OFFSET + 61,CHAR_TABLE_OFFSET + 177,CHAR_TABLE_OFFSET + 178,CHAR_TABLE_OFFSET + 55,46, 0 };


//ͷ����������ݲ�ƥ��,�����ó������ݻ��߸���ͷ��.
unsigned short CHS_FTA_PRINTHEAD_NOTMATCH[] = {
	CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 36,CHAR_TABLE_OFFSET + 183,CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 176,
	CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 184,CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 185,CHAR_TABLE_OFFSET + 186,
	44,CHAR_TABLE_OFFSET + 187,CHAR_TABLE_OFFSET + 165,CHAR_TABLE_OFFSET + 20,CHAR_TABLE_OFFSET + 170,
	CHAR_TABLE_OFFSET + 176,CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 184,CHAR_TABLE_OFFSET + 188,CHAR_TABLE_OFFSET + 189,
	CHAR_TABLE_OFFSET + 190,CHAR_TABLE_OFFSET + 191,CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 36,46, 0 };


//���ӵĳ���ID��ƥ��,�������̼�.
unsigned short CHS_FTA_MANUFACTURERID_NOTMATCH[] = {
	CHAR_TABLE_OFFSET + 36,CHAR_TABLE_OFFSET + 175,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 176,CHAR_TABLE_OFFSET + 192,
	73,68,CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 185,CHAR_TABLE_OFFSET + 186,
	44,CHAR_TABLE_OFFSET + 187,CHAR_TABLE_OFFSET + 171,CHAR_TABLE_OFFSET + 132,CHAR_TABLE_OFFSET + 193,
	CHAR_TABLE_OFFSET + 194,46,32, 0 };


//���ش���: ������ʱʱ�䣬�������µ�����.
unsigned short CHS_FTA_LIMITEDTIME_RUNOUT[] = {
	CHAR_TABLE_OFFSET + 195,CHAR_TABLE_OFFSET + 165,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,58,
	32,CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 149,CHAR_TABLE_OFFSET + 196,CHAR_TABLE_OFFSET + 103,
	CHAR_TABLE_OFFSET + 103,CHAR_TABLE_OFFSET + 74,CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 187,CHAR_TABLE_OFFSET + 22,
	CHAR_TABLE_OFFSET + 23,CHAR_TABLE_OFFSET + 197,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199,
	46, 0 };


//�ڲ�����,�հ�Band��Y�����Ϊ��.
unsigned short CHS_FTA_INTERNAL_SW1[] = {
	CHAR_TABLE_OFFSET + 114,CHAR_TABLE_OFFSET + 167,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,44,
	CHAR_TABLE_OFFSET + 115,CHAR_TABLE_OFFSET + 29,66,97,110,
	100,CHAR_TABLE_OFFSET + 188,89,CHAR_TABLE_OFFSET + 67,CHAR_TABLE_OFFSET + 75,
	CHAR_TABLE_OFFSET + 200,CHAR_TABLE_OFFSET + 201,CHAR_TABLE_OFFSET + 202,46, 0 };


//USB1.1����.
unsigned short CHS_FTA_USB1_USB1CONNECT[] = {
	85,83,66,49,46,
	49,CHAR_TABLE_OFFSET + 203,CHAR_TABLE_OFFSET + 204,46, 0 };


//UIʹ�õ�������Ȩ�޲����� �������������Ի���������������
unsigned short CHS_FTA_UILANGUAGE_NOT_MATCH[] = {
	85,73,CHAR_TABLE_OFFSET + 205,CHAR_TABLE_OFFSET + 206,CHAR_TABLE_OFFSET + 151,
	CHAR_TABLE_OFFSET + 126,CHAR_TABLE_OFFSET + 127,CHAR_TABLE_OFFSET + 183,CHAR_TABLE_OFFSET + 207,CHAR_TABLE_OFFSET + 196,
	CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 208,CHAR_TABLE_OFFSET + 158,32,CHAR_TABLE_OFFSET + 187,
	CHAR_TABLE_OFFSET + 165,CHAR_TABLE_OFFSET + 197,CHAR_TABLE_OFFSET + 19,CHAR_TABLE_OFFSET + 20,CHAR_TABLE_OFFSET + 126,
	CHAR_TABLE_OFFSET + 127,CHAR_TABLE_OFFSET + 188,CHAR_TABLE_OFFSET + 189,CHAR_TABLE_OFFSET + 165,CHAR_TABLE_OFFSET + 197,
	CHAR_TABLE_OFFSET + 22,CHAR_TABLE_OFFSET + 23,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199, 0 };


//PINCONFд��FPGA����
unsigned short CHS_FTA_INTERNAL_WRONGPINCONF[] = {
	80,73,78,67,79,
	78,70,CHAR_TABLE_OFFSET + 174,CHAR_TABLE_OFFSET + 23,70,
	80,71,65,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138, 0 };


//����������д�����ɫ������.
unsigned short CHS_FTA_FACTORY_COLORNUM_WRONG[] = {
	CHAR_TABLE_OFFSET + 209,CHAR_TABLE_OFFSET + 176,CHAR_TABLE_OFFSET + 19,CHAR_TABLE_OFFSET + 20,CHAR_TABLE_OFFSET + 93,
	CHAR_TABLE_OFFSET + 174,CHAR_TABLE_OFFSET + 23,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 210,CHAR_TABLE_OFFSET + 211,
	CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,46, 0 };


//ͷ���EEPROMд��ʧ��
unsigned short CHS_FTA_HB_EEPROM_WRT_ERR[] = {
	CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 36,CHAR_TABLE_OFFSET + 151,69,69,
	80,82,79,77,CHAR_TABLE_OFFSET + 174,
	CHAR_TABLE_OFFSET + 23,CHAR_TABLE_OFFSET + 172,CHAR_TABLE_OFFSET + 173, 0 };


//��ͷ���ȣ����м��ȱ�ǿ�йرա�
unsigned short CHS_FTA_HB_OVERHEAT[] = {
	CHAR_TABLE_OFFSET + 58,CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 149,CHAR_TABLE_OFFSET + 46,CHAR_TABLE_OFFSET + 158,
	CHAR_TABLE_OFFSET + 212,CHAR_TABLE_OFFSET + 147,CHAR_TABLE_OFFSET + 45,CHAR_TABLE_OFFSET + 46,CHAR_TABLE_OFFSET + 213,
	CHAR_TABLE_OFFSET + 92,CHAR_TABLE_OFFSET + 214,CHAR_TABLE_OFFSET + 48,CHAR_TABLE_OFFSET + 215,CHAR_TABLE_OFFSET + 150, 0 };


//���������߰汾����û��ͨ������Э�顣
unsigned short CHS_FTA_SHAKEHAND_ERR[] = {
	CHAR_TABLE_OFFSET + 216,CHAR_TABLE_OFFSET + 194,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,CHAR_TABLE_OFFSET + 188,
	CHAR_TABLE_OFFSET + 189,CHAR_TABLE_OFFSET + 217,CHAR_TABLE_OFFSET + 218,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,
	CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 146,CHAR_TABLE_OFFSET + 147,CHAR_TABLE_OFFSET + 148,CHAR_TABLE_OFFSET + 149,
	CHAR_TABLE_OFFSET + 219,CHAR_TABLE_OFFSET + 21,CHAR_TABLE_OFFSET + 220,CHAR_TABLE_OFFSET + 221,CHAR_TABLE_OFFSET + 150, 0 };


//�̼�Ҫ�����������汾���汾����
unsigned short CHS_FTA_SWVERSION_ERR[] = {
	CHAR_TABLE_OFFSET + 193,CHAR_TABLE_OFFSET + 194,CHAR_TABLE_OFFSET + 222,CHAR_TABLE_OFFSET + 223,CHAR_TABLE_OFFSET + 224,
	CHAR_TABLE_OFFSET + 225,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 216,CHAR_TABLE_OFFSET + 194,CHAR_TABLE_OFFSET + 217,
	CHAR_TABLE_OFFSET + 218,CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 217,CHAR_TABLE_OFFSET + 218,CHAR_TABLE_OFFSET + 69,
	CHAR_TABLE_OFFSET + 138,CHAR_TABLE_OFFSET + 150, 0 };


//��ǰϵͳ���ò�֧��һͷ��ɫ��
unsigned short CHS_FTA_NOT_SUPPORT_2C_SHARE_1H[] = {
	CHAR_TABLE_OFFSET + 161,CHAR_TABLE_OFFSET + 34,CHAR_TABLE_OFFSET + 130,CHAR_TABLE_OFFSET + 131,CHAR_TABLE_OFFSET + 19,
	CHAR_TABLE_OFFSET + 20,CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 159,CHAR_TABLE_OFFSET + 160,CHAR_TABLE_OFFSET + 118,
	CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 226,CHAR_TABLE_OFFSET + 211,CHAR_TABLE_OFFSET + 150, 0 };


//����īˮ�������ƣ��������������
unsigned short CHS_FTA_LIMITEDINK_RUNOUT[] = {
	CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 149,CHAR_TABLE_OFFSET + 102,CHAR_TABLE_OFFSET + 76,CHAR_TABLE_OFFSET + 206,
	CHAR_TABLE_OFFSET + 26,CHAR_TABLE_OFFSET + 196,CHAR_TABLE_OFFSET + 227,CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 187,
	CHAR_TABLE_OFFSET + 165,CHAR_TABLE_OFFSET + 197,CHAR_TABLE_OFFSET + 22,CHAR_TABLE_OFFSET + 23,CHAR_TABLE_OFFSET + 228,
	CHAR_TABLE_OFFSET + 229, 0 };


//�̼�Ҫ������汾֧��īˮ���룬�汾����
unsigned short CHS_FTA_SWVERSION_ERR_INK_PWD[] = {
	CHAR_TABLE_OFFSET + 193,CHAR_TABLE_OFFSET + 194,CHAR_TABLE_OFFSET + 222,CHAR_TABLE_OFFSET + 223,CHAR_TABLE_OFFSET + 216,
	CHAR_TABLE_OFFSET + 194,CHAR_TABLE_OFFSET + 217,CHAR_TABLE_OFFSET + 218,CHAR_TABLE_OFFSET + 159,CHAR_TABLE_OFFSET + 160,
	CHAR_TABLE_OFFSET + 102,CHAR_TABLE_OFFSET + 76,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199,CHAR_TABLE_OFFSET + 158,
	CHAR_TABLE_OFFSET + 217,CHAR_TABLE_OFFSET + 218,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,CHAR_TABLE_OFFSET + 158, 0 };


//������ID����
unsigned short CHS_FTA_EPSON_HEAD_BAD[] = {
	CHAR_TABLE_OFFSET + 154,CHAR_TABLE_OFFSET + 36,CHAR_TABLE_OFFSET + 175,73,68,
	CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,CHAR_TABLE_OFFSET + 150, 0 };


//ͷ��FPGA����.
unsigned short CHS_FTA_EPSON_HEAD_FPGA_ERR[] = {
	CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 217,70,80,71,
	65,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,46, 0 };


//д�������.
unsigned short CHS_FTA_SECURITY_CHIP_ERR[] = {
	CHAR_TABLE_OFFSET + 174,CHAR_TABLE_OFFSET + 162,CHAR_TABLE_OFFSET + 36,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,
	46, 0 };


//������ʼ�����ó���
unsigned short CHS_FTA_CALIBRATION_DATA[] = {
	CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 176,CHAR_TABLE_OFFSET + 177,CHAR_TABLE_OFFSET + 178,CHAR_TABLE_OFFSET + 55,
	CHAR_TABLE_OFFSET + 19,CHAR_TABLE_OFFSET + 20,CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 150, 0 };


//EP0������
unsigned short CHS_ERR_EP0OVERUN_SETUPDATA[] = {
	69,80,48,CHAR_TABLE_OFFSET + 230,CHAR_TABLE_OFFSET + 229,
	CHAR_TABLE_OFFSET + 213,CHAR_TABLE_OFFSET + 51,CHAR_TABLE_OFFSET + 231, 0 };


//ͷ��COM��ʱ.
unsigned short CHS_ERR_UART1_TXTIMEOUT[] = {
	CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 36,67,79,77,
	CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 103,46, 0 };


//�˶�COM��ʱ.
unsigned short CHS_ERR_UART2_TXTIMEOUT[] = {
	CHAR_TABLE_OFFSET + 168,CHAR_TABLE_OFFSET + 18,67,79,77,
	CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 103,46, 0 };


//��ӡ���ݺ͵��Ƶ�ʲ�ƥ��.
unsigned short CHS_ERR_INTERNAL_PRINTDATA[] = {
	CHAR_TABLE_OFFSET + 51,CHAR_TABLE_OFFSET + 52,CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 184,CHAR_TABLE_OFFSET + 89,
	CHAR_TABLE_OFFSET + 15,CHAR_TABLE_OFFSET + 232,CHAR_TABLE_OFFSET + 110,CHAR_TABLE_OFFSET + 111,CHAR_TABLE_OFFSET + 6,
	CHAR_TABLE_OFFSET + 185,CHAR_TABLE_OFFSET + 186,46, 0 };


//��ӡ����С�ڵ��Ƶ��
unsigned short CHS_ERR_FPGA_LESSDATA[] = {
	CHAR_TABLE_OFFSET + 51,CHAR_TABLE_OFFSET + 52,CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 184,CHAR_TABLE_OFFSET + 157,
	CHAR_TABLE_OFFSET + 233,CHAR_TABLE_OFFSET + 15,CHAR_TABLE_OFFSET + 232,CHAR_TABLE_OFFSET + 110,CHAR_TABLE_OFFSET + 111, 0 };


//��ӡ���ݳ������Ƶ��.
unsigned short CHS_ERR_FPGA_ULTRADATA[] = {
	CHAR_TABLE_OFFSET + 51,CHAR_TABLE_OFFSET + 52,CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 184,CHAR_TABLE_OFFSET + 169,
	CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 15,CHAR_TABLE_OFFSET + 232,CHAR_TABLE_OFFSET + 110,CHAR_TABLE_OFFSET + 111,
	46, 0 };


//��ӡ�����ݺͿ�������ƥ��.
unsigned short CHS_ERR_FPGA_WRONGCHS[] = {
	CHAR_TABLE_OFFSET + 51,CHAR_TABLE_OFFSET + 52,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 184,
	CHAR_TABLE_OFFSET + 89,CHAR_TABLE_OFFSET + 47,CHAR_TABLE_OFFSET + 232,CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 6,
	CHAR_TABLE_OFFSET + 185,CHAR_TABLE_OFFSET + 186,46, 0 };


//�ڲ�״̬.
unsigned short CHS_ERR_UV_CTR_WRONGCHS[] = {
	CHAR_TABLE_OFFSET + 114,CHAR_TABLE_OFFSET + 167,CHAR_TABLE_OFFSET + 133,CHAR_TABLE_OFFSET + 134,46, 0 };


//FPGA �յ����������
unsigned short CHS_ERR_FPGA_WRONGCOMMAND[] = {
	70,80,71,65,32,
	CHAR_TABLE_OFFSET + 234,CHAR_TABLE_OFFSET + 235,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,CHAR_TABLE_OFFSET + 151,
	CHAR_TABLE_OFFSET + 230,CHAR_TABLE_OFFSET + 229, 0 };


//�˶��ٶ�̫��򲻾��ȣ����ݻ��ڳ��飬ȴ�е������
unsigned short CHS_ERR_MOTION_SPEED_BAD[] = {
	CHAR_TABLE_OFFSET + 168,CHAR_TABLE_OFFSET + 18,CHAR_TABLE_OFFSET + 108,CHAR_TABLE_OFFSET + 50,CHAR_TABLE_OFFSET + 156,
	CHAR_TABLE_OFFSET + 97,CHAR_TABLE_OFFSET + 188,CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 236,CHAR_TABLE_OFFSET + 237,
	CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 184,CHAR_TABLE_OFFSET + 238,CHAR_TABLE_OFFSET + 143,
	CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 239,CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 240,CHAR_TABLE_OFFSET + 147,
	CHAR_TABLE_OFFSET + 15,CHAR_TABLE_OFFSET + 232,CHAR_TABLE_OFFSET + 230,CHAR_TABLE_OFFSET + 229, 0 };


//�˶������30���û���յ��˶��������
unsigned short CHS_ERR_INTERNAL_MOVING_TIMEOUT[] = {
	CHAR_TABLE_OFFSET + 168,CHAR_TABLE_OFFSET + 18,CHAR_TABLE_OFFSET + 230,CHAR_TABLE_OFFSET + 229,CHAR_TABLE_OFFSET + 241,
	CHAR_TABLE_OFFSET + 170,51,48,CHAR_TABLE_OFFSET + 242,CHAR_TABLE_OFFSET + 243,
	CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 146,CHAR_TABLE_OFFSET + 147,CHAR_TABLE_OFFSET + 234,CHAR_TABLE_OFFSET + 235,
	CHAR_TABLE_OFFSET + 168,CHAR_TABLE_OFFSET + 18,CHAR_TABLE_OFFSET + 244,CHAR_TABLE_OFFSET + 245,CHAR_TABLE_OFFSET + 230,
	CHAR_TABLE_OFFSET + 229, 0 };


//�����AUTOCLEAN����.
unsigned short CHS_ERR_INTERNAL_WRONGAUTOCLEAN[] = {
	CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,CHAR_TABLE_OFFSET + 151,65,85,
	84,79,67,76,69,
	65,78,CHAR_TABLE_OFFSET + 230,CHAR_TABLE_OFFSET + 229,46, 0 };


//�����AUTOCLEAN����.
unsigned short CHS_ERR_INTERNAL_WRONGBANDINFO[] = {
	CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,CHAR_TABLE_OFFSET + 151,65,85,
	84,79,67,76,69,
	65,78,CHAR_TABLE_OFFSET + 230,CHAR_TABLE_OFFSET + 229,46, 0 };


//����״̬1
unsigned short CHS_ERR_INTERNAL_DEBUG1[] = {
	CHAR_TABLE_OFFSET + 246,CHAR_TABLE_OFFSET + 68,CHAR_TABLE_OFFSET + 133,CHAR_TABLE_OFFSET + 134,49, 0 };


//����״̬2
unsigned short CHS_ERR_INTERNAL_DEBUG2[] = {
	CHAR_TABLE_OFFSET + 246,CHAR_TABLE_OFFSET + 68,CHAR_TABLE_OFFSET + 133,CHAR_TABLE_OFFSET + 134,50, 0 };


//���ڳ�ʼ��ARM.
unsigned short CHS_INI_ARM[] = {
	CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,CHAR_TABLE_OFFSET + 177,CHAR_TABLE_OFFSET + 178,CHAR_TABLE_OFFSET + 55,
	65,82,77,46, 0 };


//���ڳ�ʼ��USB
unsigned short CHS_INI_SX2[] = {
	CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,CHAR_TABLE_OFFSET + 177,CHAR_TABLE_OFFSET + 178,CHAR_TABLE_OFFSET + 55,
	85,83,66, 0 };


//���ڳ�ʼ��FPGA
unsigned short CHS_INI_FPGA[] = {
	CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,CHAR_TABLE_OFFSET + 177,CHAR_TABLE_OFFSET + 178,CHAR_TABLE_OFFSET + 55,
	70,80,71,65, 0 };


//���ڳ�ʼ��DSP.
unsigned short CHS_INI_DSP[] = {
	CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,CHAR_TABLE_OFFSET + 177,CHAR_TABLE_OFFSET + 178,CHAR_TABLE_OFFSET + 55,
	68,83,80,46, 0 };


//���ڳ�ʼ��ͷ��
unsigned short CHS_INI_HEADBOARD[] = {
	CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,CHAR_TABLE_OFFSET + 177,CHAR_TABLE_OFFSET + 178,CHAR_TABLE_OFFSET + 55,
	CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 36, 0 };


//��װ Spectra ��ѹ��.
unsigned short CHS_INI_HVB[] = {
	CHAR_TABLE_OFFSET + 37,CHAR_TABLE_OFFSET + 247,32,83,112,
	101,99,116,114,97,
	32,CHAR_TABLE_OFFSET + 7,CHAR_TABLE_OFFSET + 181,CHAR_TABLE_OFFSET + 36,46, 0 };


//��֪���ľ���
unsigned short CHS_WAR_UNKNOWNHEADERTYPE[] = {
	CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 248,CHAR_TABLE_OFFSET + 249,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 250,
	CHAR_TABLE_OFFSET + 251, 0 };


//EP0���.
unsigned short CHS_WAR_EP0OVERUN_REQUEST_IGNORE[] = {
	69,80,48,CHAR_TABLE_OFFSET + 252,CHAR_TABLE_OFFSET + 170,
	46, 0 };


//��ɫ���ڱ�ī.
unsigned short CHS_WAR_PUMP_CYAN[] = {
	CHAR_TABLE_OFFSET + 253,CHAR_TABLE_OFFSET + 211,CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,CHAR_TABLE_OFFSET + 254,
	CHAR_TABLE_OFFSET + 102,46, 0 };


//Ʒɫ���ڱ�ī.
unsigned short CHS_WAR_PUMP_MAGENTA[] = {
	CHAR_TABLE_OFFSET + 255,CHAR_TABLE_OFFSET + 211,CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,CHAR_TABLE_OFFSET + 254,
	CHAR_TABLE_OFFSET + 102,46, 0 };


//��ɫ���ڱ�ī.
unsigned short CHS_WAR_PUMP_YELLOW[] = {
	CHAR_TABLE_OFFSET + 256,CHAR_TABLE_OFFSET + 211,CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,CHAR_TABLE_OFFSET + 254,
	CHAR_TABLE_OFFSET + 102,46, 0 };


//��ɫ���ڱ�ī.
unsigned short CHS_WAR_PUMP_BLACK[] = {
	CHAR_TABLE_OFFSET + 257,CHAR_TABLE_OFFSET + 211,CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,CHAR_TABLE_OFFSET + 254,
	CHAR_TABLE_OFFSET + 102,46, 0 };


//ǳ��ɫ���ڱ�ī.
unsigned short CHS_WAR_PUMP_LIGHTCYAN[] = {
	CHAR_TABLE_OFFSET + 258,CHAR_TABLE_OFFSET + 253,CHAR_TABLE_OFFSET + 211,CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,
	CHAR_TABLE_OFFSET + 254,CHAR_TABLE_OFFSET + 102,46, 0 };


//ǳƷɫ���ڱ�ī.
unsigned short CHS_WAR_PUMP_LIGHTMAGENTA[] = {
	CHAR_TABLE_OFFSET + 258,CHAR_TABLE_OFFSET + 255,CHAR_TABLE_OFFSET + 211,CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,
	CHAR_TABLE_OFFSET + 254,CHAR_TABLE_OFFSET + 102,46, 0 };


//������ʱ������󣬺��к��зǷ��ַ�;
unsigned short CHS_WAR_TIME_PASSWORD_WRONGINPUT[] = {
	CHAR_TABLE_OFFSET + 22,CHAR_TABLE_OFFSET + 23,CHAR_TABLE_OFFSET + 196,CHAR_TABLE_OFFSET + 103,CHAR_TABLE_OFFSET + 198,
	CHAR_TABLE_OFFSET + 199,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 259,
	CHAR_TABLE_OFFSET + 147,CHAR_TABLE_OFFSET + 259,CHAR_TABLE_OFFSET + 147,CHAR_TABLE_OFFSET + 260,CHAR_TABLE_OFFSET + 152,
	CHAR_TABLE_OFFSET + 261,CHAR_TABLE_OFFSET + 208,59,32, 0 };


//����һ���Ϸ���ʱ����;
unsigned short CHS_WAR_TIME_PASSWORD_WRONG[] = {
	CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 262,CHAR_TABLE_OFFSET + 118,CHAR_TABLE_OFFSET + 263,CHAR_TABLE_OFFSET + 264,
	CHAR_TABLE_OFFSET + 152,CHAR_TABLE_OFFSET + 196,CHAR_TABLE_OFFSET + 103,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199,
	59,32, 0 };


//��ʱ����ͳ��̲�ƥ��
unsigned short CHS_WAR_TIME_PASSWORD_MANUFACTURERIDNOTMATCH[] = {
	CHAR_TABLE_OFFSET + 196,CHAR_TABLE_OFFSET + 103,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199,CHAR_TABLE_OFFSET + 89,
	CHAR_TABLE_OFFSET + 176,CHAR_TABLE_OFFSET + 192,CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 185,CHAR_TABLE_OFFSET + 186, 0 };


//��ʱ����Ͱ��Ӳ�ƥ��
unsigned short CHS_WAR_TIME_PASSWORD_BOARDIDNOTMATCH[] = {
	CHAR_TABLE_OFFSET + 196,CHAR_TABLE_OFFSET + 103,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199,CHAR_TABLE_OFFSET + 89,
	CHAR_TABLE_OFFSET + 36,CHAR_TABLE_OFFSET + 175,CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 185,CHAR_TABLE_OFFSET + 186, 0 };


//��һ�ξ���:����100��Сʱ�ͳ�����ʱ��, ���򳧼���ȡ����.
unsigned short CHS_WAR_LIMITEDTIME_FIRST[] = {
	CHAR_TABLE_OFFSET + 182,CHAR_TABLE_OFFSET + 118,CHAR_TABLE_OFFSET + 101,CHAR_TABLE_OFFSET + 250,CHAR_TABLE_OFFSET + 251,
	58,CHAR_TABLE_OFFSET + 265,CHAR_TABLE_OFFSET + 147,49,48,
	48,CHAR_TABLE_OFFSET + 263,CHAR_TABLE_OFFSET + 157,CHAR_TABLE_OFFSET + 103,CHAR_TABLE_OFFSET + 266,
	CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 196,CHAR_TABLE_OFFSET + 103,CHAR_TABLE_OFFSET + 267,
	44,32,CHAR_TABLE_OFFSET + 187,CHAR_TABLE_OFFSET + 67,CHAR_TABLE_OFFSET + 176,
	CHAR_TABLE_OFFSET + 268,CHAR_TABLE_OFFSET + 269,CHAR_TABLE_OFFSET + 155,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199,
	46, 0 };


//�ڶ��ξ���: ����50��Сʱ�ͳ�����ʱ��,���򳧼���ȡ����.
unsigned short CHS_WAR_LIMITEDTIME_SECOND[] = {
	CHAR_TABLE_OFFSET + 182,CHAR_TABLE_OFFSET + 123,CHAR_TABLE_OFFSET + 101,CHAR_TABLE_OFFSET + 250,CHAR_TABLE_OFFSET + 251,
	58,32,CHAR_TABLE_OFFSET + 265,CHAR_TABLE_OFFSET + 147,53,
	48,CHAR_TABLE_OFFSET + 263,CHAR_TABLE_OFFSET + 157,CHAR_TABLE_OFFSET + 103,CHAR_TABLE_OFFSET + 266,
	CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 196,CHAR_TABLE_OFFSET + 103,CHAR_TABLE_OFFSET + 267,
	44,CHAR_TABLE_OFFSET + 187,CHAR_TABLE_OFFSET + 67,CHAR_TABLE_OFFSET + 176,CHAR_TABLE_OFFSET + 268,
	CHAR_TABLE_OFFSET + 269,CHAR_TABLE_OFFSET + 155,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199,46, 0 };


//���һ�ξ���: ����1��Сʱ�ͳ�����ʱ��ֹͣ��ӡ, �������򳧼���ȡ����.
unsigned short CHS_WAR_LIMITEDTIME_LAST[] = {
	CHAR_TABLE_OFFSET + 270,CHAR_TABLE_OFFSET + 243,CHAR_TABLE_OFFSET + 118,CHAR_TABLE_OFFSET + 101,CHAR_TABLE_OFFSET + 250,
	CHAR_TABLE_OFFSET + 251,58,32,CHAR_TABLE_OFFSET + 265,CHAR_TABLE_OFFSET + 147,
	49,CHAR_TABLE_OFFSET + 263,CHAR_TABLE_OFFSET + 157,CHAR_TABLE_OFFSET + 103,CHAR_TABLE_OFFSET + 266,
	CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 196,CHAR_TABLE_OFFSET + 103,CHAR_TABLE_OFFSET + 271,
	CHAR_TABLE_OFFSET + 272,CHAR_TABLE_OFFSET + 273,CHAR_TABLE_OFFSET + 51,CHAR_TABLE_OFFSET + 52,44,
	32,CHAR_TABLE_OFFSET + 187,CHAR_TABLE_OFFSET + 274,CHAR_TABLE_OFFSET + 275,CHAR_TABLE_OFFSET + 67,
	CHAR_TABLE_OFFSET + 176,CHAR_TABLE_OFFSET + 268,CHAR_TABLE_OFFSET + 269,CHAR_TABLE_OFFSET + 155,CHAR_TABLE_OFFSET + 198,
	CHAR_TABLE_OFFSET + 199,46, 0 };


//����ѡ��������󣬺��з�0~F��ֵ
unsigned short CHS_WAR_OPTION_PASSWORD_WRONGINPUT[] = {
	CHAR_TABLE_OFFSET + 22,CHAR_TABLE_OFFSET + 23,CHAR_TABLE_OFFSET + 276,CHAR_TABLE_OFFSET + 186,CHAR_TABLE_OFFSET + 198,
	CHAR_TABLE_OFFSET + 199,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 259,
	CHAR_TABLE_OFFSET + 147,CHAR_TABLE_OFFSET + 260,48,126,70,
	CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 64, 0 };


//����һ���Ϸ�ѡ������
unsigned short CHS_WAR_OPTION_PASSWORD_WRONG[] = {
	CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 262,CHAR_TABLE_OFFSET + 118,CHAR_TABLE_OFFSET + 263,CHAR_TABLE_OFFSET + 264,
	CHAR_TABLE_OFFSET + 152,CHAR_TABLE_OFFSET + 276,CHAR_TABLE_OFFSET + 186,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199, 0 };


//ѡ������ͳ��̲�ƥ��
unsigned short CHS_WAR_OPTION_PASSWORD_MANUFACTURERIDNOTMATCH[] = {
	CHAR_TABLE_OFFSET + 276,CHAR_TABLE_OFFSET + 186,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199,CHAR_TABLE_OFFSET + 89,
	CHAR_TABLE_OFFSET + 176,CHAR_TABLE_OFFSET + 192,CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 185,CHAR_TABLE_OFFSET + 186, 0 };


//ѡ������Ͱ��Ӳ�ƥ��
unsigned short CHS_WAR_OPTION_PASSWORD_BOARDIDNOTMATCH[] = {
	CHAR_TABLE_OFFSET + 276,CHAR_TABLE_OFFSET + 186,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199,CHAR_TABLE_OFFSET + 89,
	CHAR_TABLE_OFFSET + 36,CHAR_TABLE_OFFSET + 175,CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 185,CHAR_TABLE_OFFSET + 186, 0 };


//��ī��ȫƿ����, ����ī��ֹͣ��ī.
unsigned short CHS_WAR_PUMP_PROHIBIT_SENSOR[] = {
	CHAR_TABLE_OFFSET + 254,CHAR_TABLE_OFFSET + 102,CHAR_TABLE_OFFSET + 37,CHAR_TABLE_OFFSET + 38,CHAR_TABLE_OFFSET + 277,
	CHAR_TABLE_OFFSET + 278,CHAR_TABLE_OFFSET + 267,44,32,CHAR_TABLE_OFFSET + 212,
	CHAR_TABLE_OFFSET + 147,CHAR_TABLE_OFFSET + 102,CHAR_TABLE_OFFSET + 254,CHAR_TABLE_OFFSET + 272,CHAR_TABLE_OFFSET + 273,
	CHAR_TABLE_OFFSET + 279,CHAR_TABLE_OFFSET + 102,46, 0 };


//��ͼ�ڲ�֧�ֳ�Ƶ��ͷ��汾��ʹ�ó�Ƶ, ϵͳǿ��ʹ�ø��ٴ�ӡ.
unsigned short CHS_WAR_OVER_SPEED_NOT_SUPPORT[] = {
	CHAR_TABLE_OFFSET + 68,CHAR_TABLE_OFFSET + 280,CHAR_TABLE_OFFSET + 143,CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 159,
	CHAR_TABLE_OFFSET + 160,CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 110,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 73,
	CHAR_TABLE_OFFSET + 36,CHAR_TABLE_OFFSET + 217,CHAR_TABLE_OFFSET + 218,CHAR_TABLE_OFFSET + 24,CHAR_TABLE_OFFSET + 205,
	CHAR_TABLE_OFFSET + 206,CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 110,44,32,
	CHAR_TABLE_OFFSET + 130,CHAR_TABLE_OFFSET + 131,CHAR_TABLE_OFFSET + 92,CHAR_TABLE_OFFSET + 227,CHAR_TABLE_OFFSET + 205,
	CHAR_TABLE_OFFSET + 206,CHAR_TABLE_OFFSET + 7,CHAR_TABLE_OFFSET + 108,CHAR_TABLE_OFFSET + 51,CHAR_TABLE_OFFSET + 52,
	46, 0 };


//����īˮ������󣬺��з�0~F��ֵ
unsigned short CHS_WAR_INK_PASSWORD_WRONGINPUT[] = {
	CHAR_TABLE_OFFSET + 22,CHAR_TABLE_OFFSET + 23,CHAR_TABLE_OFFSET + 102,CHAR_TABLE_OFFSET + 76,CHAR_TABLE_OFFSET + 198,
	CHAR_TABLE_OFFSET + 199,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 259,
	CHAR_TABLE_OFFSET + 147,CHAR_TABLE_OFFSET + 260,48,126,70,
	CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 64, 0 };


//����һ���Ϸ�īˮ����
unsigned short CHS_WAR_INK_PASSWORD_WRONG[] = {
	CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 262,CHAR_TABLE_OFFSET + 118,CHAR_TABLE_OFFSET + 263,CHAR_TABLE_OFFSET + 264,
	CHAR_TABLE_OFFSET + 152,CHAR_TABLE_OFFSET + 102,CHAR_TABLE_OFFSET + 76,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199, 0 };


//īˮ����ͳ��̲�ƥ��
unsigned short CHS_WAR_INK_PASSWORD_MANUFACTURERIDNOTMATCH[] = {
	CHAR_TABLE_OFFSET + 102,CHAR_TABLE_OFFSET + 76,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199,CHAR_TABLE_OFFSET + 89,
	CHAR_TABLE_OFFSET + 176,CHAR_TABLE_OFFSET + 192,CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 185,CHAR_TABLE_OFFSET + 186, 0 };


//īˮ����Ͱ��Ӳ�ƥ��
unsigned short CHS_WAR_INK_PASSWORD_BOARDIDNOTMATCH[] = {
	CHAR_TABLE_OFFSET + 102,CHAR_TABLE_OFFSET + 76,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199,CHAR_TABLE_OFFSET + 89,
	CHAR_TABLE_OFFSET + 36,CHAR_TABLE_OFFSET + 175,CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 185,CHAR_TABLE_OFFSET + 186, 0 };


//����10���ͳ���īˮ�����ˣ���һ�ξ���
unsigned short CHS_WAR_LIMITEDINK_FIRST[] = {
	CHAR_TABLE_OFFSET + 265,CHAR_TABLE_OFFSET + 206,49,48,CHAR_TABLE_OFFSET + 171,
	CHAR_TABLE_OFFSET + 266,CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 102,CHAR_TABLE_OFFSET + 76,
	CHAR_TABLE_OFFSET + 196,CHAR_TABLE_OFFSET + 227,CHAR_TABLE_OFFSET + 267,CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 182,
	CHAR_TABLE_OFFSET + 118,CHAR_TABLE_OFFSET + 101,CHAR_TABLE_OFFSET + 250,CHAR_TABLE_OFFSET + 251, 0 };


//����5���ͳ���īˮ�����ˣ��ڶ��ξ���
unsigned short CHS_WAR_LIMITEDINK_SECOND[] = {
	CHAR_TABLE_OFFSET + 265,CHAR_TABLE_OFFSET + 206,53,CHAR_TABLE_OFFSET + 171,CHAR_TABLE_OFFSET + 266,
	CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 102,CHAR_TABLE_OFFSET + 76,CHAR_TABLE_OFFSET + 196,
	CHAR_TABLE_OFFSET + 227,CHAR_TABLE_OFFSET + 267,CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 182,CHAR_TABLE_OFFSET + 123,
	CHAR_TABLE_OFFSET + 101,CHAR_TABLE_OFFSET + 250,CHAR_TABLE_OFFSET + 251, 0 };


//����1���ͳ���īˮ�����ˣ����һ�ξ���
unsigned short CHS_WAR_LIMITEDINK_LAST[] = {
	CHAR_TABLE_OFFSET + 265,CHAR_TABLE_OFFSET + 206,49,CHAR_TABLE_OFFSET + 171,CHAR_TABLE_OFFSET + 266,
	CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 170,CHAR_TABLE_OFFSET + 102,CHAR_TABLE_OFFSET + 76,CHAR_TABLE_OFFSET + 196,
	CHAR_TABLE_OFFSET + 227,CHAR_TABLE_OFFSET + 267,CHAR_TABLE_OFFSET + 158,CHAR_TABLE_OFFSET + 270,CHAR_TABLE_OFFSET + 243,
	CHAR_TABLE_OFFSET + 118,CHAR_TABLE_OFFSET + 101,CHAR_TABLE_OFFSET + 250,CHAR_TABLE_OFFSET + 251, 0 };


//��ǰ��ͷ��֧��īˮ���빦��.
unsigned short CHS_WAR_INK_PASSWORD_UNKNOWN_DOT_VOLUME[] = {
	CHAR_TABLE_OFFSET + 161,CHAR_TABLE_OFFSET + 34,CHAR_TABLE_OFFSET + 58,CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 6,
	CHAR_TABLE_OFFSET + 159,CHAR_TABLE_OFFSET + 160,CHAR_TABLE_OFFSET + 102,CHAR_TABLE_OFFSET + 76,CHAR_TABLE_OFFSET + 198,
	CHAR_TABLE_OFFSET + 199,CHAR_TABLE_OFFSET + 30,CHAR_TABLE_OFFSET + 31,46, 0 };


//רɫ1���ڱ�ī.
unsigned short CHS_WAR_PUMP_SPOTCOLOR1[] = {
	CHAR_TABLE_OFFSET + 281,CHAR_TABLE_OFFSET + 211,49,CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,
	CHAR_TABLE_OFFSET + 254,CHAR_TABLE_OFFSET + 102,46, 0 };


//רɫ2���ڱ�ī.
unsigned short CHS_WAR_PUMP_SPOTCOLOR2[] = {
	CHAR_TABLE_OFFSET + 281,CHAR_TABLE_OFFSET + 211,50,CHAR_TABLE_OFFSET + 63,CHAR_TABLE_OFFSET + 143,
	CHAR_TABLE_OFFSET + 254,CHAR_TABLE_OFFSET + 102,46, 0 };


//��ӡ����С�ڵ����.
unsigned short CHS_WAR_FPGA_LESSDATA[] = {
	CHAR_TABLE_OFFSET + 51,CHAR_TABLE_OFFSET + 52,CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 184,CHAR_TABLE_OFFSET + 157,
	CHAR_TABLE_OFFSET + 233,CHAR_TABLE_OFFSET + 15,CHAR_TABLE_OFFSET + 232,CHAR_TABLE_OFFSET + 84,46, 0 };


//��ӡ���ݶ��ڵ����.
unsigned short CHS_WAR_FPGA_ULTRADATA[] = {
	CHAR_TABLE_OFFSET + 51,CHAR_TABLE_OFFSET + 52,CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 184,CHAR_TABLE_OFFSET + 282,
	CHAR_TABLE_OFFSET + 233,CHAR_TABLE_OFFSET + 15,CHAR_TABLE_OFFSET + 232,CHAR_TABLE_OFFSET + 84,46, 0 };


//��ͷ�¶�̫��.
unsigned short CHS_WAR_EPSONHEAD_TEMP_TOO_LOW[] = {
	CHAR_TABLE_OFFSET + 58,CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 49,CHAR_TABLE_OFFSET + 50,CHAR_TABLE_OFFSET + 156,
	CHAR_TABLE_OFFSET + 283,46, 0 };


//��ͷ�¶�̫��.
unsigned short CHS_WAR_EPSONHEAD_TEMP_TOO_HIGH[] = {
	CHAR_TABLE_OFFSET + 58,CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 49,CHAR_TABLE_OFFSET + 50,CHAR_TABLE_OFFSET + 156,
	CHAR_TABLE_OFFSET + 7,46, 0 };


//��ͷδ����.
unsigned short CHS_WAR_EPSONHEAD_NOT_CONNECT[] = {
	CHAR_TABLE_OFFSET + 58,CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 284,CHAR_TABLE_OFFSET + 203,CHAR_TABLE_OFFSET + 204,
	46, 0 };


//����FPGA���������̫��.
unsigned short CHS_WAR_EPSON_FPGA_ULTRADATA[] = {
	CHAR_TABLE_OFFSET + 162,CHAR_TABLE_OFFSET + 36,70,80,71,
	65,CHAR_TABLE_OFFSET + 285,CHAR_TABLE_OFFSET + 251,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 84,
	CHAR_TABLE_OFFSET + 184,CHAR_TABLE_OFFSET + 156,CHAR_TABLE_OFFSET + 282,46, 0 };


//����FPGA���������̫��.
unsigned short CHS_WAR_EPSON_FPGA_LESSDATA[] = {
	CHAR_TABLE_OFFSET + 162,CHAR_TABLE_OFFSET + 36,70,80,71,
	65,CHAR_TABLE_OFFSET + 285,CHAR_TABLE_OFFSET + 251,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 84,
	CHAR_TABLE_OFFSET + 184,CHAR_TABLE_OFFSET + 156,CHAR_TABLE_OFFSET + 286,46, 0 };


//��ǰ��ͷ��������δ֪��
unsigned short CHS_WAR_UNKNOWN_NOZZLE_COUNT[] = {
	CHAR_TABLE_OFFSET + 161,CHAR_TABLE_OFFSET + 34,CHAR_TABLE_OFFSET + 58,CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 151,
	CHAR_TABLE_OFFSET + 58,CHAR_TABLE_OFFSET + 59,CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 284,CHAR_TABLE_OFFSET + 248,
	CHAR_TABLE_OFFSET + 150, 0 };


//�����ɹ�.
unsigned short CHS_UPDATE_SUCCESS[] = {
	CHAR_TABLE_OFFSET + 171,CHAR_TABLE_OFFSET + 132,CHAR_TABLE_OFFSET + 245,CHAR_TABLE_OFFSET + 30,46, 0 };


//DSP��ʼ�������ʱ.
unsigned short CHS_UPDATEERR_DSP_BEGIN_TIMEOUT[] = {
	68,83,80,CHAR_TABLE_OFFSET + 47,CHAR_TABLE_OFFSET + 178,
	CHAR_TABLE_OFFSET + 171,CHAR_TABLE_OFFSET + 132,CHAR_TABLE_OFFSET + 230,CHAR_TABLE_OFFSET + 229,CHAR_TABLE_OFFSET + 169,
	CHAR_TABLE_OFFSET + 103,46, 0 };


//DSP���ݳ�ʱ.
unsigned short CHS_UPDATEERR_DSP_DATA_TIMEOUT[] = {
	68,83,80,CHAR_TABLE_OFFSET + 84,CHAR_TABLE_OFFSET + 184,
	CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 103,46, 0 };


//DSP������ʱ.
unsigned short CHS_UPDATEERR_DSP_END_TIMEOUT[] = {
	68,83,80,CHAR_TABLE_OFFSET + 287,CHAR_TABLE_OFFSET + 288,
	CHAR_TABLE_OFFSET + 169,CHAR_TABLE_OFFSET + 103,46, 0 };


//����������ļ���ʽ.
unsigned short CHS_UPDATEERR_ILIGALFILE[] = {
	CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 171,CHAR_TABLE_OFFSET + 132,
	CHAR_TABLE_OFFSET + 129,CHAR_TABLE_OFFSET + 194,CHAR_TABLE_OFFSET + 289,CHAR_TABLE_OFFSET + 88,46, 0 };


//���Ϸ��������ļ�.
unsigned short CHS_UPDATEERR_INTERNAL_DATA[] = {
	CHAR_TABLE_OFFSET + 6,CHAR_TABLE_OFFSET + 264,CHAR_TABLE_OFFSET + 152,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 171,
	CHAR_TABLE_OFFSET + 132,CHAR_TABLE_OFFSET + 129,CHAR_TABLE_OFFSET + 194,46, 0 };


//����У�������.
unsigned short CHS_UPDATEERR_CHECKSUM[] = {
	CHAR_TABLE_OFFSET + 171,CHAR_TABLE_OFFSET + 132,CHAR_TABLE_OFFSET + 56,CHAR_TABLE_OFFSET + 290,CHAR_TABLE_OFFSET + 199,
	CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,46, 0 };


//ARM �������.
unsigned short CHS_UPDATEERR_EREASE[] = {
	65,82,77,32,CHAR_TABLE_OFFSET + 109,
	CHAR_TABLE_OFFSET + 291,CHAR_TABLE_OFFSET + 292,CHAR_TABLE_OFFSET + 293,46, 0 };


//Flash����.
unsigned short CHS_UPDATEERR_FLASHOP[] = {
	70,108,97,115,104,
	CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138,46, 0 };


//��Ҫ�ر�̼���
unsigned short CHS_UPDATEERR_GZ_ILIGALFILE[] = {
	CHAR_TABLE_OFFSET + 294,CHAR_TABLE_OFFSET + 222,CHAR_TABLE_OFFSET + 224,CHAR_TABLE_OFFSET + 295,CHAR_TABLE_OFFSET + 193,
	CHAR_TABLE_OFFSET + 194,CHAR_TABLE_OFFSET + 150, 0 };


//��Ҫ����īˮ����̼���
unsigned short CHS_UPDATEERR_INKP_ILIGALFILE[] = {
	CHAR_TABLE_OFFSET + 294,CHAR_TABLE_OFFSET + 222,CHAR_TABLE_OFFSET + 224,CHAR_TABLE_OFFSET + 225,CHAR_TABLE_OFFSET + 102,
	CHAR_TABLE_OFFSET + 76,CHAR_TABLE_OFFSET + 198,CHAR_TABLE_OFFSET + 199,CHAR_TABLE_OFFSET + 193,CHAR_TABLE_OFFSET + 194,
	CHAR_TABLE_OFFSET + 150, 0 };


//8ͷӲ���޷�����16ͷ�Ĺ̼���
unsigned short CHS_UPDATEERR_16H_ILIGALFILE[] = {
	56,CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 296,CHAR_TABLE_OFFSET + 194,CHAR_TABLE_OFFSET + 119,
	CHAR_TABLE_OFFSET + 152,CHAR_TABLE_OFFSET + 171,CHAR_TABLE_OFFSET + 132,49,54,
	CHAR_TABLE_OFFSET + 73,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 193,CHAR_TABLE_OFFSET + 194,CHAR_TABLE_OFFSET + 150, 0 };

//δ֪�Ĵ���
unsigned short CHS_UNKNOWN_ERR[] = {
	CHAR_TABLE_OFFSET + 284,CHAR_TABLE_OFFSET + 248,CHAR_TABLE_OFFSET + 151,CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138, 0 };

unsigned short CHS_STATUS_SVC[] = {CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138, 0 };
unsigned short CHS_STATUS_FTA[] = {CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138, 0 };
unsigned short CHS_STATUS_ERR[] = {CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138, 0 };
unsigned short CHS_STATUS_ERR_AUTO[] = {CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138, 0 };
unsigned short CHS_STATUS_WAR[] = {CHAR_TABLE_OFFSET + 69,CHAR_TABLE_OFFSET + 138, 0 };
unsigned short CHS_STATUS_INI[] = {CHAR_TABLE_OFFSET + 177,CHAR_TABLE_OFFSET + 178,CHAR_TABLE_OFFSET + 55, 0 };
unsigned short CHS_STATUS_RDY[] = {CHAR_TABLE_OFFSET + 266,CHAR_TABLE_OFFSET + 297, 0 };
unsigned short CHS_STATUS_MOVING[] = {CHAR_TABLE_OFFSET + 298,CHAR_TABLE_OFFSET + 18, 0 };
unsigned short CHS_STATUS_PRINT[] = {CHAR_TABLE_OFFSET + 51,CHAR_TABLE_OFFSET + 52, 0 };
unsigned short CHS_STATUS_PAUSE[] = {CHAR_TABLE_OFFSET + 299,CHAR_TABLE_OFFSET + 272,32, 0 };
unsigned short CHS_STATUS_CLEANING[] = {CHAR_TABLE_OFFSET + 85,CHAR_TABLE_OFFSET + 86, 0 };
unsigned short CHS_STATUS_CANCELING[] = {CHAR_TABLE_OFFSET + 155,CHAR_TABLE_OFFSET + 300, 0 };
unsigned short CHS_STATUS_UPDATING[] = {CHAR_TABLE_OFFSET + 171,CHAR_TABLE_OFFSET + 132, 0 };
#endif
#endif
