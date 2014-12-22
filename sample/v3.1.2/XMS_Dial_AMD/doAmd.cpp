
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

/*注意:silenceTimeout>maxPersonSilenceTime>minSilenceTime

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
	{  // SILENCE_NORMAL_EVENT和VOICE_NORMAL_EVENT并不作为语音类型判断依据，
	// 只是提高给上层进行参考的事件，所以并不在此处理中。
	
		// 对检测事件内的语音事件进行统计
		switch(bargeInEvent->event )
		{
			case SILENCE_MIN_EVENT:

				AMD_instance[ch].minSilenceCount++;
				

				break;


			case SILENCE_PROMPT_TONE_EVENT:

				AMD_instance[ch].maxToneSilenceTime++;

				if((AMD_instance[ch].minSilenceCount>0)
					&&(AMD_instance[ch].lastEvent==SILENCE_MIN_EVENT))
				{ //SILENCE_PROMPT_TONE_EVENT与SILENCE_MIN_EVENT两个事件会有重叠性，所以
				// 需要排除SILENCE_MIN_EVENT事件
				
					AMD_instance[ch].minSilenceCount--;
				}


				break;

			case SILENCE_PERSON_EVENT:

				if((AMD_instance[ch].maxToneSilenceTime>0)
					&&(AMD_instance[ch].lastEvent==SILENCE_PROMPT_TONE_EVENT))
				{ // SILENCE_PERSON_EVENT与SILENCE_PROMPT_TONE_EVENT会有重叠性，所以需要排除SILENCE_PROMPT_TONE_EVENT

					AMD_instance[ch].maxToneSilenceTime--;

					AMD_instance[ch].toneValidFlag=0;

					
				}

				if((AMD_instance[ch].minVocCount>0)
					||(AMD_instance[ch].maxMUSICCount>0))
				{ //确保真人静音事件是在语音事件之后收到才有效
				
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

				//真人摘机的判断
				if((AMD_instance[ch].personValidFlag==0)
					&&(AMD_instance[ch].maxPersonSilencCount>0))
				{
					AMD_instance[ch].personValidFlag = 1;
				}

				//提示音判断
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


	// 通过统计数据对语音成份进行分析

	//彩铃与真人摘机的判断
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
	{ // 要想办法排除不是输入静音而是线路静音的误判影响
		//所以在检测到提示音之后，也不再检测了，由于两段提示音
		//之间的静音间隔可能满足真人摘机的条件，而出现误判

		AMD_instance[ch].result = AMD_RESULT_VIRTUAL_PERSON;

		AMD_instance[ch].enable=ITP_Disable;	  // then not detect 

//		fprintf(g_fpLog, "&&&&&&&&&&detect virtual person,samples_cnt=%d\n",samples_cnt);

//		printf("&&&&&&&&&&detect virtual person,samples_cnt=%d\n",samples_cnt);

		result = AMD_RESULT_VIRTUAL_PERSON;
	}

	//提示音与其它语音情况的判断
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



