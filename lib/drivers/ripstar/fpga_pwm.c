#include <fpga_pwm.h>
#include <fpga_pwm.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <delay.h>
#include <asm/regs.h>
#include <asm/io.h>
#include <platform.h>

static void __pwm_clear_buffer(uint32_t ch, dbuf_id_t bufId);
/*-----------buffer half full interrupt register---------------*/
static void __pwm_irq_almost_enable(uint32_t ch, dbuf_id_t bufId, uint8_t isena);
static void __pwm_irq_almost_clr(uint32_t ch, dbuf_id_t bufId);
static void __pwm_irq_almost_mask(uint32_t ch, dbuf_id_t bufId, uint8_t ismast);
/*------------buffer empty interrupt register----------*/
static void __pwm_irq_empty_enable(uint32_t ch, dbuf_id_t bufId, uint8_t isena);
static void __pwm_irq_empty_clr(uint32_t ch, dbuf_id_t bufId);
static void __pwm_irq_empty_mask(uint32_t ch, dbuf_id_t bufId, uint8_t ismask);
static void __pwm_switch_buf(uint32_t ch, uint32_t bufids);
static inline void __pwm_handler_empty(void * chId);
static inline void __pwm_handler_almost(void * chId);
static void __pwm_irq_handler(void *arg);

pwm_t *__pwm = (pwm_t *)PWM_BASE_ADDR;
channel_t *__channels = (channel_t *)PWM_CHANNEL_ADDR;

//pwm func
static pwm_handler_t pwm_handler;		//pwm �жϴ�����
pwm_handler_t pwm_handler_e;
pwm_handler_t pwm_handler_ae;
pwm_handler_t pwm_handler_tmp;

pwm_t *pwm_get_pwm()
{
	return __pwm;
}

channel_t *pwm_get_channels()
{
	return __channels;
}

inline void pwm_mode_pwm(uint32_t ch, uint8_t ispwm)
{
	pwm_t *pwm = __pwm;

	if(ispwm == 0)
		clrbits32(&pwm->pwm_mr, ch);
	else
		setbits32(&pwm->pwm_mr, ch);
}

inline void pwm_control_source_hps(uint32_t ch, uint8_t isHps)
{
	pwm_t *pwm = __pwm;

	if(isHps)
		setbits32(&pwm->pwm_csr, ch);
	else
		clrbits32(&pwm->pwm_csr, ch);
}

inline void pwm_polar_pos(uint32_t ch, uint8_t ispos)
{
	pwm_t *pwm = __pwm;

	if(ispos == 0)
		setbits32(&pwm->pwm_pr, ch);
	else
		clrbits32(&pwm->pwm_pr, ch);
}

inline uint8_t pwm_ch_polar_isneg(uint32_t chId)
{
	return (__pwm->pwm_pr & (0x01 << chId)) ? PWM_PR_NEG : !PWM_PR_NEG;
}

inline void pwm_override(uint32_t ch, uint8_t isover)
{
	pwm_t *pwm = __pwm;

	if(isover == 0)
		clrbits32(&pwm->pwm_ovr, ch);
	else
		setbits32(&pwm->pwm_ovr, ch);
}

inline void pwm_enable(uint32_t ch, uint8_t isena)
{
	pwm_t *pwm = __pwm;

	if(isena == 0)
		clrbits32(&pwm->pwm_enr, ch);
	else
		setbits32(&pwm->pwm_enr, ch);
}

inline void pwm_switch_fill_b0(uint32_t ch, uint8_t isbuf0)		//**
{
	pwm_t *pwm = __pwm;

	if(isbuf0)
		clrbits32(&pwm->pwm_sfbr, ch);
	else
		setbits32(&pwm->pwm_sfbr, ch);
}

inline void pwm_switch_exe_b0(uint32_t ch, uint8_t isbuf0)		//**
{
	pwm_t *pwm = __pwm;

	if(isbuf0)
		clrbits32(&pwm->pwm_sebr, ch);
	else
		setbits32(&pwm->pwm_sebr, ch);
}

static inline void __pwm_clear_buffer(uint32_t ch, dbuf_id_t bufId)
{
	pwm_t *pwm = __pwm;

	setbits32(&pwm->pwm_cbr[bufId], ch);
}

static inline uint8_t __pwm_buffer_isfull(uint32_t ch, dbuf_id_t bufId, uint8_t isfull)
{
	pwm_t *pwm = __pwm;

	return ((pwm->pwm_sfr[bufId] & ch) ? 1 : 0);
}

//static inline uint8_t __pwm_buffer_isempty(uint32_t ch, dbuf_id_t bufId, uint8_t isfull){}

/*-----------buffer almost empty interrupt register---------------*/
static inline void __pwm_irq_almost_enable(uint32_t ch, dbuf_id_t bufId, uint8_t isena)
{
	pwm_t *pwm = __pwm;

	if(isena == 0)
		clrbits32(&pwm->pwm_iaeer[bufId], ch);
	else
		setbits32(&pwm->pwm_iaeer[bufId], ch);
}

static inline void __pwm_irq_almost_clr(uint32_t ch, dbuf_id_t bufId)
{
	pwm_t *pwm = __pwm;

	setbits32(&pwm->pwm_iaecr[bufId], ch);
}

static inline void __pwm_irq_almost_mask(uint32_t ch, dbuf_id_t bufId, uint8_t ismask)
{
	pwm_t *pwm = __pwm;

	if(ismask == 0)	//������
		clrbits32(&pwm->pwm_iaemr[bufId], ch);
	else
		setbits32(&pwm->pwm_iaemr[bufId], ch);

}

/*------------buffer empty interrupt register----------*/
static inline void __pwm_irq_empty_enable(uint32_t ch, dbuf_id_t bufId, uint8_t isena)
{
	pwm_t *pwm = __pwm;

	if(isena == 0)
		clrbits32(&pwm->pwm_ieer[bufId], ch);
	else
		setbits32(&pwm->pwm_ieer[bufId], ch);
}

static inline void __pwm_irq_empty_clr(uint32_t ch, dbuf_id_t bufId)
{
	pwm_t *pwm = __pwm;

	setbits32(&pwm->pwm_iecr[bufId], ch);
}

static inline void __pwm_irq_empty_mask(uint32_t ch, dbuf_id_t bufId, uint8_t ismask)
{
	pwm_t *pwm = __pwm;

	if(ismask == 0)	//������
		clrbits32(&pwm->pwm_iemr[bufId], ch);
	else
		setbits32(&pwm->pwm_iemr[bufId], ch);

}

/*����FPGA��˵�����ں�������趨����˳��Ҫ��ģ��������ڡ���������
 * �Է��ⲿ��������ʱ˳��ߵ������ٶ����ṩ�����������ڻ�����ĺ���
 */
inline uint32_t pwm_ch_set_pwm(uint32_t chId, uint32_t period, uint32_t duty)
{
	channel_t *channels = __channels;

#if 0
	uint32_t tmp;

	if(period < duty)
	{
		tmp = period;
		period = duty;
		duty = tmp;
	}
#endif
	writel(period, &channels[chId].pwmc_cprdr);
	writel(duty, &channels[chId].pwmc_cdtyr);
	return 0;
}

/*
 * ch		:Ҫswitch buffer��channel,32λ��ÿһλ��Ӧһ��channel,����ӦλΪ1����˵����Ҫswitch
 * bufids	:��Ӧÿһ��channel��bufid,32λ��ÿһλ��Ӧһ��channel������ӦλΪ1����˵����channelʹ�õ�bufidΪDBUF_1
 */
static void __pwm_switch_buf(uint32_t ch, uint32_t bufids)
{
	pwm_t *pwm = __pwm;

	//����ת�� execute buffer��fill in buffer
	setbits32(&pwm->pwm_sebr, ch & bufids);
	clrbits32(&pwm->pwm_sebr, (~bufids) & ch);
	setbits32(&pwm->pwm_sfbr, ch & bufids);
	clrbits32(&pwm->pwm_sfbr, (~bufids) & ch);

	//Ĭ�ϲ������Ч�����buffer

	//�л���Ӧ���ж����μĴ���
	clrbits32(&pwm->pwm_iaemr[DBUF_1], bufids & ch);			//����
	setbits32(&pwm->pwm_iaemr[DBUF_1], (~bufids) & ch);
	setbits32(&pwm->pwm_iaemr[DBUF_0], bufids & ch);			//����
	clrbits32(&pwm->pwm_iaemr[DBUF_0], (~bufids) & ch);
	clrbits32(&pwm->pwm_iemr[DBUF_1], bufids & ch);			//��
	setbits32(&pwm->pwm_iemr[DBUF_1], (~bufids) & ch);
	setbits32(&pwm->pwm_iemr[DBUF_0], bufids & ch);			//��
	clrbits32(&pwm->pwm_iemr[DBUF_0], (~bufids) & ch);

#if 1	//��ʵֻҪ��֤����buffer��ʹ�ܶ��Ǵ򿪵ģ����л�Ҳû��ϵ����Ϊ�ж��������л�
	//�л���Ӧ���ж�ʹ�ܼĴ���
	setbits32(&pwm->pwm_iaeer[DBUF_1], bufids & ch);			//����
	clrbits32(&pwm->pwm_iaeer[DBUF_1], (~bufids) & ch);
	clrbits32(&pwm->pwm_iaeer[DBUF_0], bufids & ch);			//����
	setbits32(&pwm->pwm_iaeer[DBUF_0], (~bufids) & ch);

	setbits32(&pwm->pwm_ieer[DBUF_1], bufids & ch);			//��
	clrbits32(&pwm->pwm_ieer[DBUF_1], (~bufids) & ch);
	clrbits32(&pwm->pwm_ieer[DBUF_0], bufids & ch);			//��
	setbits32(&pwm->pwm_ieer[DBUF_0], (~bufids) & ch);
#endif
}

/*NOTE���ú�����ѻ�����δִ�е�PWM������գ�ֱ��ִ����������PWM����
 * �����ǽ���ִ�е�pwm���ݣ������������ݾ�����Ҫ̫�ࣨ������10���ڣ���
 * ������FPGA��buffer��С���ƣ�����������ݲ�Ҫ̫�࣬һ��ҪС��buffer��С��FPAG buffer:256��
 * ��ʵ����Ҫִ�е�pwm����С����10���������5-10����ʣ�����ݿ���ִ�����ٴ���䣬
 * ����Ҫע�⣺���Ǽ���������ֱ�ӵ��ú���pwm_ch_set_pwm��䣬�����ٴ���pwm_ch_urgency_pwm
 * (�����ԣ���д�������ִ��������ʱʱ��ģ����ÿ��д20�����ҵ�PWM���ݾͻ���ʱ10um
 * ��ˣ��ú�����д���PWM���ݽ��鱣����5-10�����������ݿ����Ժ�д��)
 */
uint32_t pwm_ch_urgency_pwm(uint32_t chId, uint32_t period[], uint32_t duty[], uint32_t num)
{
	pwm_t *pwm = __pwm;
	uint32_t i = 0;
	dbuf_id_t old_buf = DBUF_0;
	dbuf_id_t new_buf = DBUF_0;

#if 1
	old_buf = (pwm->pwm_sebr & (0x01 << chId)) ? DBUF_1 : DBUF_0;
	new_buf = (old_buf == DBUF_1) ? DBUF_0: DBUF_1;
	pwm_switch_fill_b0(0x01 << chId, new_buf == DBUF_0);		//�����pwm����ʹ������һ��buf

	for(i = 0; i < num; i ++)
	{
		//����û���жϻ����Ƿ��������������ʱҪע������С
		pwm_ch_set_pwm(chId, period[i], duty[i]);
	}

	__pwm_switch_buf(0x01 << chId, new_buf << chId);			//ת��ִ���»����PWM
	__pwm_clear_buffer(0x01 << chId, old_buf);					//�����ǰ�Ļ����е�PWM
#endif
	if(num == 0)		//���numΪ0���������ⲿ���൱��ֻ���建��
		return 0;

	return i;			//����ѹ�뻺���PWM����
}

/*��ĳһ��pwm channel��д��Ҫ����ִ�е�pwm���ݣ�Ҫ��ʹ���channel��Ľ�������ִ�У���Ҫ��ε��øú�����
* ��ÿ��ֻ��дһ��channel����д�����Ҫ���̵��ú���pwm_start_urgency_pwm�ſ�ʹ��д���pwm����ִ��
* ��������С���Ʋ�������pwm_ch_urgency_pwm��ע��
*/
uint32_t pwm_ch_set_urgency_pwm(uint32_t chId, uint32_t period[], uint32_t duty[], uint32_t num)
{
	pwm_t *pwm = __pwm;
	uint32_t i = 0;
	dbuf_id_t old_buf = DBUF_0;
	dbuf_id_t new_buf = DBUF_0;

	old_buf = (pwm->pwm_sebr & (0x01 << chId)) ? DBUF_1 : DBUF_0;
	new_buf = (old_buf == DBUF_1) ? DBUF_0: DBUF_1;

	pwm_switch_fill_b0(0x01 << chId, new_buf == DBUF_0);		//�����pwm����ʹ������һ��buffer
	for(i = 0; i < num; i ++)
	{
		pwm_ch_set_pwm(chId, period[i], duty[i]);
	}
	pwm_switch_fill_b0(0x01 << chId, old_buf == DBUF_0);		//�������л���ԭ����fill buffer

	return i;
}

void pwm_start_urgency_pwm(uint32_t ch)
{
	uint32_t newBufId = 0;
	uint32_t oldBufId = 0;
	int i = 0;
	pwm_t *pwm = __pwm;

	for(i = 0; i < PWM_MAX_CH_CNT; i++)
	{
		if(!((pwm->pwm_sebr & ch) & (0x01 << i)))
			newBufId |= 0x01 << i;
	}
	__pwm_switch_buf(ch, newBufId);			//ִ���µ�buffer�Ľ���pwm����

	//��վɵ�buffer���pwm����
	for(i = 0; i < PWM_MAX_CH_CNT; i++)
	{
		if(!(ch & (0x01 << i)))
			continue;
		oldBufId = (newBufId & (0x01 << i)) ? DBUF_0 : DBUF_1;
		__pwm_clear_buffer(ch & (0x01 << i), oldBufId);				//�����ǰ�Ļ����е�PWM
	}
}

#if 1
/*����ӿڣ�һ�㲻��Ҫʹ����Щ��������������²����룬(δ�����ԣ���һ���ԣ�����,(-_-))
 * ����ѡ���ԵĿ����˼����õ��Ŀ����ԱȽϴ�ĺ����������������Ҳ�����
 * pwm_clear_buffer:��յ�ǰִ�л��������
 * pwm_buffer_isfull���жϵ�ǰд��Ļ����Ƿ�����
 */
inline void pwm_clear_buffer(uint32_t ch)		//��ǰִ�л���
{
	pwm_t *pwm = __pwm;
	int i = 0;

	for(i = 0; i < PWM_MAX_CH_CNT; i ++)
	{
		dbuf_id_t bufId = ((pwm->pwm_sebr & ch) & (0x01 << i)) ? DBUF_1 : DBUF_0;

		setbits32(&pwm->pwm_cbr[bufId], ch);
	}
}

inline uint8_t pwm_buffer_isfull(uint32_t ch)	//��ǰ��仺�壬ͬʱֻ���ж�һ��ͨ��
{
	pwm_t *pwm = __pwm;
	dbuf_id_t bufId = (pwm->pwm_sfbr & ch) ? DBUF_1 : DBUF_0;

	return ((pwm->pwm_sfr[bufId] & ch) ? 1 : 0);
}

inline uint8_t pwm_buffer_isempty(uint32_t ch)	//��ǰִ�л��壬ͬʱֻ���ж�һ��ͨ��
{
	pwm_t *pwm = __pwm;
	dbuf_id_t bufId = (pwm->pwm_sebr & ch) ? DBUF_1 : DBUF_0;

	return ((pwm->pwm_ser[bufId] & ch) ? 1 : 0);
}

inline void pwm_irq_almost_clr(uint32_t ch)		//��ǰִ��
{
	pwm_t *pwm = __pwm;
	int i = 0;

	for(i = 0; i < PWM_MAX_CH_CNT; i ++)
	{
		dbuf_id_t bufId = ((pwm->pwm_sebr & ch) & (0x01 << i)) ? DBUF_1 : DBUF_0;

		setbits32(&pwm->pwm_iaecr[bufId], ch);
	}
}

inline void pwm_irq_almost_enable(uint32_t ch, uint8_t isena)	//��ǰִ��
{
	pwm_t *pwm = __pwm;
	int i = 0;

	for(i = 0; i < PWM_MAX_CH_CNT; i ++)
	{
		dbuf_id_t bufId = ((pwm->pwm_sebr & ch) & (0x01 << i)) ? DBUF_1 : DBUF_0;

		if(isena == 0)
			clrbits32(&pwm->pwm_iaeer[bufId], ch);
		else
			setbits32(&pwm->pwm_iaeer[bufId], ch);
	}
}

inline void pwm_irq_almost_mask(uint32_t ch, uint8_t ismask)	//��ǰִ��
{
	pwm_t *pwm = __pwm;
	int i = 0;

	for(i = 0; i < PWM_MAX_CH_CNT; i ++)
	{
		dbuf_id_t bufId = ((pwm->pwm_sebr & ch) & (0x01 << i)) ? DBUF_1 : DBUF_0;

		if(ismask == 0)	//������
			clrbits32(&pwm->pwm_iaemr[bufId], ch);
		else
			setbits32(&pwm->pwm_iaemr[bufId], ch);
	}

}

inline uint32_t pwm_irq_almost_status(uint32_t ch)				//��ǰִ��
{
	pwm_t *pwm = __pwm;
	int i = 0;
	uint32_t irq_status = 0;

	for(i = 0; i < PWM_MAX_CH_CNT; i ++)
	{
		dbuf_id_t bufId = ((pwm->pwm_sebr & ch) & (0x01 << i)) ? DBUF_1 : DBUF_0;
		irq_status |= pwm->pwm_iaesr[bufId] & (0x01 << i);
	}

	return irq_status;
}
/*------------buffer empty interrupt register----------*/
inline void pwm_irq_empty_enable(uint32_t ch, uint8_t isena)		//��ǰִ��
{
	pwm_t *pwm = __pwm;
	int i = 0;

	for(i = 0; i < PWM_MAX_CH_CNT; i ++)
	{
		dbuf_id_t bufId = ((pwm->pwm_sebr & ch) & (0x01 << i)) ? DBUF_1 : DBUF_0;

		if(isena == 0)
			clrbits32(&pwm->pwm_ieer[bufId], ch);
		else
			setbits32(&pwm->pwm_ieer[bufId], ch);
	}
}

inline void pwm_irq_empty_clr(uint32_t ch)			//��ǰִ��
{
	pwm_t *pwm = __pwm;
	int i = 0;

	for(i = 0; i < PWM_MAX_CH_CNT; i ++)
	{
		dbuf_id_t bufId = ((pwm->pwm_sebr & ch) & (0x01 << i)) ? DBUF_1 : DBUF_0;

		setbits32(&pwm->pwm_iecr[bufId], ch);
	}
}

inline void pwm_irq_empty_mask(uint32_t ch, uint8_t ismask)			//��ǰִ��
{
	pwm_t *pwm = __pwm;
	int i = 0;

	for(i = 0; i < PWM_MAX_CH_CNT; i ++)
	{
		dbuf_id_t bufId = ((pwm->pwm_sebr & ch) & (0x01 << i)) ? DBUF_1 : DBUF_0;

		if(ismask == 0)	//������
			clrbits32(&pwm->pwm_iemr[bufId], ch);
		else
			setbits32(&pwm->pwm_iemr[bufId], ch);
	}
}

inline uint32_t pwm_irq_empty_status(uint32_t ch)				//��ǰִ��
{
	pwm_t *pwm = __pwm;
	int i = 0;
	uint32_t irq_status = 0;

	for(i = 0; i < PWM_MAX_CH_CNT; i ++)
	{
		dbuf_id_t bufId = ((pwm->pwm_sebr & ch) & (0x01 << i)) ? DBUF_1 : DBUF_0;
		irq_status |= pwm->pwm_iesr[bufId] & (0x01 << i);
	}

	return irq_status;
}

/*�ú�������
 * 1:һ��������ⲿ����Ҫ�ֶ��л�buffer
 * 2:�л�bufferһ�������Ҫ�����һ��buffer��δִ�����pwm���ݣ��ú�����û�����
 * ����ڵ��ú������Ҫ���*/
dbuf_id_t pwm_switch_buf(uint32_t ch)
{
	pwm_t *pwm = __pwm;

	uint32_t cur_bufid = pwm->pwm_sebr;
	uint32_t new_bufid = (~(ch & cur_bufid)) | ((~ch) & cur_bufid);
	//����ת�� execute buffer��fill in buffer
	setbits32(&pwm->pwm_sebr, ch & new_bufid);
	clrbits32(&pwm->pwm_sebr, (~new_bufid) & ch);
	setbits32(&pwm->pwm_sfbr, ch & new_bufid);
	clrbits32(&pwm->pwm_sfbr, (~new_bufid) & ch);

	//Ĭ�ϲ������Ч�����buffer

	//�л���Ӧ���ж����μĴ���
	clrbits32(&pwm->pwm_iaemr[DBUF_1], new_bufid & ch);			//����
	setbits32(&pwm->pwm_iaemr[DBUF_1], (~new_bufid) & ch);
	setbits32(&pwm->pwm_iaemr[DBUF_0], new_bufid & ch);			//����
	clrbits32(&pwm->pwm_iaemr[DBUF_0], (~new_bufid) & ch);
	clrbits32(&pwm->pwm_iemr[DBUF_1], new_bufid & ch);			//��
	setbits32(&pwm->pwm_iemr[DBUF_1], (~new_bufid) & ch);
	setbits32(&pwm->pwm_iemr[DBUF_0], new_bufid & ch);			//��
	clrbits32(&pwm->pwm_iemr[DBUF_0], (~new_bufid) & ch);

#if 1	//��ʵֻҪ��֤����buffer��ȫ�ܶ��Ǵ򿪵ģ����л�Ҳû��ϵ����Ϊ�ж��������л�
	//�л���Ӧ���ж�ʹ�ܼĴ���
	setbits32(&pwm->pwm_iaeer[DBUF_1], new_bufid & ch);			//����
	clrbits32(&pwm->pwm_iaeer[DBUF_1], (~new_bufid) & ch);
	clrbits32(&pwm->pwm_iaeer[DBUF_0], new_bufid & ch);			//����
	setbits32(&pwm->pwm_iaeer[DBUF_0], (~new_bufid) & ch);

	setbits32(&pwm->pwm_ieer[DBUF_1], new_bufid & ch);			//��
	clrbits32(&pwm->pwm_ieer[DBUF_1], (~new_bufid) & ch);
	clrbits32(&pwm->pwm_ieer[DBUF_0], new_bufid & ch);			//��
	setbits32(&pwm->pwm_ieer[DBUF_0], (~new_bufid) & ch);
#endif

	return new_bufid;
}
#endif


static inline void __pwm_handler_empty(void * arg)
{

}

static inline void __pwm_handler_almost(void * arg)
{

	int i = 0;
	uint32_t chId = (uint32_t)arg;
	static uint32_t cnt = 0;
	int chIndex = 0;

	if(!(chId & PWM_CH(0)))
		return;

#if 0
	if(cnt == 100)
	{
		static uint8_t pwm_num = 18;
#if 0
		//��ʽһ
		pwm_ch_urgency_pwm(PWM_CHID0, period, duty, pwm_num);
		pwm_ch_urgency_pwm(PWM_CHID1, period, duty, pwm_num);
#else
		//��ʽ��
		pwm_ch_set_urgency_pwm(PWM_CHID0, period, duty, pwm_num);
		pwm_ch_set_urgency_pwm(PWM_CHID1, period, duty, pwm_num);
		pwm_start_urgency_pwm(PWM_CH(0)|PWM_CH(1));
#endif
	}
	else
#endif

#if 1
	static uint8_t level = 0;
	static uint32_t periodNum = 100;
	static uint32_t period1 = 5000;
	static uint32_t period2 = 3000;
	static uint32_t period3 = 3000;
	static uint32_t duty1 = 1500;
	static uint32_t duty2 = 0;
	static uint32_t duty3 = 1500;
	static uint32_t period_s = 5000;
	static uint32_t period_e = 1000;
	static uint32_t duty_acc = 500;
	static uint8_t acc_time = 1;	//��
	static uint32_t per_tatal_num = 0;

	static uint32_t cur_per = 3000;
	uint32_t per = acc_time * 1000 * 10 / ((period_s * 10 / 1000) * (period_s * 10 / 1000 - 1) / 2
			- (period_e * 10 / 1000) * (period_e * 10 / 1000 - 1) / 2);


	if(per_tatal_num++ < 10 * 1000 * 60)	//��
	{

		if(cur_per >= period_e)
		{
			if(cnt++ < per)
			{
				pwm_ch_set_pwm(chIndex, cur_per, duty_acc);
			}
			else if(cnt >= per)
			{
				pwm_ch_set_pwm(chIndex, cur_per, duty_acc);
				cur_per--;
				cnt = 0;
			}
		}
		else
		{
			pwm_ch_set_pwm(chIndex, cur_per, duty_acc);
		}
	}
	else if(per_tatal_num++ < 10 * 1000 * 110)	// ��
	{
		pwm_ch_set_pwm(chIndex, cur_per, duty_acc);
	}
	else if(per_tatal_num++ < 10 * 1000 * 180)	//��
	{
		if(cur_per < period_s)
		{
			if(cnt++ < per)
			{
				pwm_ch_set_pwm(chIndex, cur_per, duty_acc);
			}
			else if(cnt >= per)
			{
				pwm_ch_set_pwm(chIndex, cur_per, duty_acc);
				cur_per++;
				cnt = 0;
			}
		}
		else
		{
			pwm_ch_set_pwm(chIndex, cur_per, 0);
		}
	}
	else
	{
		per_tatal_num = 0;
	}
#endif
}
static spinlock_t irq_lock;
static void __pwm_irq_handler(void *arg)
{
	int i = 0;
	volatile uint32_t chId = 0;
	unsigned long flags = 0;


	// check the empty irq
	spin_lock_irqsave(&irq_lock, flags);
	for(i = 0; i < PWM_MAX_CH_CNT; i++)
	{
		dbuf_id_t valid_buf = (__pwm->pwm_sebr & (0x01 << i)) ? DBUF_1 : DBUF_0;
		chId |= __pwm->pwm_iesr[valid_buf] & (0x01 << i);
	}
	if(chId != 0 && pwm_handler_e != NULL)
		pwm_handler_e((void *)chId);		//call the interrupt handler
	spin_unlock_irqrestore(&irq_lock, flags);

	if(chId != 0)
	{
		__pwm_irq_empty_clr(PWM_CHID_ALL,DBUF_0);		//���ж�
		__pwm_irq_empty_clr(PWM_CHID_ALL,DBUF_1);		//���ж�
	}

	//check the almost empty irq
	chId = 0;
	volatile dbuf_id_t valid_buf = 0;
	spin_lock_irqsave(&irq_lock, flags);
	for(i = 0; i < PWM_MAX_CH_CNT; i ++)
	{
		valid_buf = (__pwm->pwm_sebr & (0x01 << i)) ? DBUF_1 : DBUF_0;
		chId |= (__pwm->pwm_iaesr[valid_buf] & (0x01 << i));
	}
	if(chId != 0 && pwm_handler_ae != NULL)
		pwm_handler_ae((void *)chId);		//call the interrupt handler

	spin_unlock_irqrestore(&irq_lock, flags);

	if(chId != 0)
	{
		__pwm_irq_almost_clr(PWM_CHID_ALL,DBUF_0);		//���ж�
		__pwm_irq_almost_clr(PWM_CHID_ALL,DBUF_1);		//���ж�
	}

}

int pwm_reset(uint32_t ch)
{
	//disable pwm function first
	pwm_enable(ch, 0);

	pwm_mode_pwm(ch, 1);							// pwm mode
	pwm_control_source_hps(ch, 0);					//control by fpga
	pwm_polar_pos(ch, 1);							//positive logic
	pwm_override(ch, 0);							//��HPSԽȨֱ�ӿ���
	__pwm_clear_buffer(ch, DBUF_0);					//clear buffer
	__pwm_clear_buffer(ch, DBUF_1);					//clear buffer
	pwm_switch_fill_b0(ch, 1);						//Ĭ����� bufferΪbuf0
	pwm_switch_exe_b0(ch, 1);						//Ĭ��ִ��bufferΪbuf0

	// disable all almost empty interrutp
	__pwm_irq_almost_enable(ch, DBUF_0, 0);
	__pwm_irq_almost_mask(ch, DBUF_0, 1);
	__pwm_irq_almost_enable(ch, DBUF_1, 0);
	__pwm_irq_almost_mask(ch, DBUF_1, 1);

	//disable all empty interrutp
	__pwm_irq_empty_enable(ch, DBUF_0, 0);
	__pwm_irq_empty_mask(ch, DBUF_0, 1);
	__pwm_irq_empty_enable(ch, DBUF_1, 0);
	__pwm_irq_empty_mask(ch, DBUF_1, 1);

	pwm_switch_fill_b0(ch, 1);							//�������bufferΪbuffer0

	/*�����жϴ�������������жϺ������Զ��壬��һ�������ֻ��Ҫ��������
	 *�����жϴ������ͽ����жϴ������������жϴ������ͽ����жϴ�������
	 *��Ϊ�жϴ��������ж��ж�״̬������ص��жϴ��������ջ��߽��գ�
	 */
	pwm_handler = __pwm_irq_handler;
	pwm_handler_e = __pwm_handler_empty;
	pwm_handler_ae = __pwm_handler_almost;

	return 0;
}

int pwm_init(void)
{
	pwm_reset(PWM_CHID_ALL);

	pwm_irq_almost_enable(PWM_CHID_ALL, 0);					//���ж�
	pwm_irq_almost_mask(PWM_CHID_ALL, 1);					//���ж�����
	request_irq(CONFIG_PWM_IRQ, pwm_handler, __pwm);		//set interrupt handle function

	return 0;
}

#if 1// old function

#endif

