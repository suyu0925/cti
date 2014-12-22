
#include "StdAfx.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"
#include "DJAcsDevState.h"

#include  "AMD.h"

//for AMD testing

//input testing file type


AMD_DETECT_INSTANCE  AMD_instance[MAX_AMD_CH];


//to chanege alaw to linear



// func:void doInputBargeInDetect(DJ_U16 ch)

/*ע��:silenceTimeout>maxPersonSilenceTime>minSilenceTime

  voiceTimeout>maxMusicVocTime>minVoiceTime
  minVoiceTime and minSilenceTime must >(TICK_PARAM*BARGE_STATE_CHANGE_THRED), otherwise will err*/



//AMD function



//void  startAmd(int ch)
void  startAmd( TRUNK_STRUCT *pOneTrunk)
{

	int ch;

	ch=pOneTrunk->VocDevID.m_s16ChannelID;
	
	memset(&AMD_instance[ch],0,sizeof(AMD_DETECT_INSTANCE));

	AMD_instance[ch].enable = ITP_Enable;

}

//void  stopAmd(int ch)
void  startAmd( TRUNK_STRUCT *pOneTrunk)
{
	int ch;

	ch=pOneTrunk->VocDevID.m_s16ChannelID;

	memset(&AMD_instance[ch],0,sizeof(AMD_DETECT_INSTANCE));

	
}

DJ_S32  doAMDdetect(Acs_Voc_Bargein_Event *bargeInEvent, int ch)
{

	DJ_S32  result=-1;
	
	if(AMD_instance[ch].enable==ITP_Disable)
	{

		 memset(&AMD_instance[ch],0,sizeof(AMD_DETECT_INSTANCE));
		 		
		return(-1);
	}

#if 0	
	
	AMD_instance[ch].totalCheckTime++;

	if(AMD_instance[ch].totalCheckTime>=AMD_CHECK_TIME)
	{	
		//memset(&AMD_instance[ch],0,sizeof(AMD_DETECT_INSTANCE));

		
		 AMD_instance[ch].totalCheckTime = 0;
		
		AMD_instance[ch].enable=ITP_Disable;	

	//	gBarge_Config_instance[ch].enable = ITP_Disable; ---ZCQ disable bargeIn func

	}
#endif

		
	
	

	if((bargeInEvent->event!=SILENCE_NORMAL_EVENT)
		&&(bargeInEvent->event!=VOICE_NORMAL_EVENT)
		&&(bargeInEvent->event!=BARGE_DTMF_EVENT)
		&&(bargeInEvent->event!=BARGE_GTD_EVENT))
	{  // SILENCE_NORMAL_EVENT��VOICE_NORMAL_EVENT������Ϊ���������ж����ݣ�
	// ֻ����߸��ϲ���вο����¼������Բ����ڴ˴����С�
	
		// �Լ���¼��ڵ������¼�����ͳ��
		switch(bargeInEvent->event )
		{
			case SILENCE_MIN_EVENT:

				AMD_instance[ch].minSilenceCount++;
				

				break;


			case SILENCE_PROMPT_TONE_EVENT:

				AMD_instance[ch].maxToneSilenceTime++;

				if((AMD_instance[ch].minSilenceCount>0)
					&&(AMD_instance[ch].lastEvent==SILENCE_MIN_EVENT))
				{ //SILENCE_PROMPT_TONE_EVENT��SILENCE_MIN_EVENT�����¼������ص��ԣ�����
				// ��Ҫ�ų�SILENCE_MIN_EVENT�¼�
				
					AMD_instance[ch].minSilenceCount--;
				}


				break;

			case SILENCE_PERSON_EVENT:

				if((AMD_instance[ch].maxToneSilenceTime>0)
					&&(AMD_instance[ch].lastEvent==SILENCE_PROMPT_TONE_EVENT))
				{ // SILENCE_PERSON_EVENT��SILENCE_PROMPT_TONE_EVENT�����ص��ԣ�������Ҫ�ų�SILENCE_PROMPT_TONE_EVENT

					AMD_instance[ch].maxToneSilenceTime--;

					AMD_instance[ch].toneValidFlag=0;

					
				}

				if((AMD_instance[ch].minVocCount>0)
					||(AMD_instance[ch].maxMUSICCount>0))
				{ //ȷ�����˾����¼����������¼�֮���յ�����Ч
				
					AMD_instance[ch].maxPersonSilencCount++;

					if(AMD_instance[ch].maxPersonSilencCount==1)
					{
						AMD_instance[ch].personValidFlag = 0;

					}
				}
								
				break;

			case SILENCE_TIMEOUT_EVENT:

				if((AMD_instance[ch].maxPersonSilencCount>0)
					&&(AMD_instance[ch].lastEvent==SILENCE_PERSON_EVENT))
				{
					AMD_instance[ch].maxPersonSilencCount--;
				}
					
				AMD_instance[ch].silenceToutCount++;

				break;

			case VOICE_MIN_EVENT:

				AMD_instance[ch].minVocCount++;

				//����ժ�����ж�
				if((AMD_instance[ch].personValidFlag==0)
					&&(AMD_instance[ch].maxPersonSilencCount>0))
				{
					AMD_instance[ch].personValidFlag = 1;
				}

				//��ʾ���ж�
				if(AMD_instance[ch].maxToneSilenceTime>0)
				{
					AMD_instance[ch].toneValidFlag=1;
				}
				
				break;

			case  VOICE_MUSIC_EVENT:

				if((AMD_instance[ch].minVocCount>0)
					&&(AMD_instance[ch].lastEvent==VOICE_MIN_EVENT))
				{
					AMD_instance[ch].minVocCount--;
				}

				AMD_instance[ch].maxMUSICCount++;
				
				break;

			case VOICE_TIMEOUT_EVENT:

				if((AMD_instance[ch].maxMUSICCount>0)
					&&(AMD_instance[ch].lastEvent==VOICE_MUSIC_EVENT))
				{

					AMD_instance[ch].maxMUSICCount--;
				}

				AMD_instance[ch].vocToutCount++;

				break;
		}

		

		

		AMD_instance[ch].lastEvent = bargeInEvent->event ;
		
	}


	// ͨ��ͳ�����ݶ������ɷݽ��з���

	//����������ժ�����ж�
	if(AMD_instance[ch].maxMUSICCount>0)
	{
		//LOG_printf(&LOG1,"detect MUSIC!!!\n");


//		fprintf(g_fpLog, "&&&&&&&&&&__detect MUSIC,samples_cnt=%d\n",samples_cnt);

//		printf("&&&&&&&&&&detect MUSIC,samples_cnt=%d\n",samples_cnt);

		
		AMD_instance[ch].maxMUSICCount = 0;  // end check music

		AMD_instance[ch].minSilenceCount = 0;

		AMD_instance[ch].minVocCount = 0;

		AMD_instance[ch].toneValidFlag = 0;

		AMD_instance[ch].result = AMD_RESULT_MUSIC;

		result = AMD_RESULT_MUSIC;
	}
	else if((AMD_instance[ch].personValidFlag==1)
		&&(AMD_instance[ch].result !=AMD_RESULT_VIRTUAL_PERSON)
		&&(AMD_instance[ch].result !=AMD_RESULT_PROMPT_TONE ))
	{ // Ҫ��취�ų��������뾲��������·����������Ӱ��
		//�����ڼ�⵽��ʾ��֮��Ҳ���ټ���ˣ�����������ʾ��
		//֮��ľ������������������ժ��������������������

		AMD_instance[ch].result = AMD_RESULT_VIRTUAL_PERSON;

		AMD_instance[ch].enable=ITP_Disable;	  // then not detect 

//		fprintf(g_fpLog, "&&&&&&&&&&detect virtual person,samples_cnt=%d\n",samples_cnt);

//		printf("&&&&&&&&&&detect virtual person,samples_cnt=%d\n",samples_cnt);

		result = AMD_RESULT_VIRTUAL_PERSON;
	}

	//��ʾ������������������ж�
	if((AMD_instance[ch].result!=AMD_RESULT_VIRTUAL_PERSON)&&(AMD_instance[ch].result!=AMD_RESULT_PROMPT_TONE)
		&&(AMD_instance[ch].minVocCount>4)&&(AMD_instance[ch].minSilenceCount>1)
		&&(AMD_instance[ch].toneValidFlag==1))
	{
	
		//LOG_printf(&LOG1,"detect prompt Tone!!!\n");

		AMD_instance[ch].maxMUSICCount = 0;  // end check music

		AMD_instance[ch].minSilenceCount = 0;

		AMD_instance[ch].minVocCount = 0;

		AMD_instance[ch].toneValidFlag = 0;
		
		AMD_instance[ch].result = AMD_RESULT_PROMPT_TONE;


		result = AMD_RESULT_PROMPT_TONE;

	//	fprintf(g_fpLog, "&&&&&&&&&&detect prompt Tone,samples_cnt=%d\n",samples_cnt);

	//	printf("&&&&&&&&&&detect prompt Tone,samples_cnt=%d\n",samples_cnt);
	}

	return(result);

}



