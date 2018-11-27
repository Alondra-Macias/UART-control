/**
	\file
	\brief
		This is the source file for the FlexTimer device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the FlexTimer peripheral.
	\authors  Margarita Jauregui, Alondra Macias
	\date	22/10/2018
 */



#include "FlexTimer.h"
#include "MK64F12.h"
#include <stdio.h>
#include "stdint.h"



void interrupt_flag_en_dis(BooleanType N){
	if(N){
	FTM2->CONTROLS[0].CnSC|=FLEX_TIMER_CHIE;}
	else{
	FTM2->CONTROLS[0].CnSC&=~FLEX_TIMER_CHIE;
	}

}

void FTM_clk(FTM_channel_t channel){
	switch(channel)
					{
						case (FTM_0):
						/** Clock gating for the FlexTimer 0*/
							SIM->SCGC6 |= FLEX_TIMER_0_CLOCK_GATING;
							break;

						case (FTM_1):
						/** Clock gating for the FlexTimer 1*/
							SIM->SCGC6 |= FLEX_TIMER_1_CLOCK_GATING;
							break;

						case (FTM_2):
						/** Clock gating for the FlexTimer 2*/
							SIM->SCGC6 |= FLEX_TIMER_2_CLOCK_GATING;
							break;
						case (FTM_3):
						/** Clock gating for the FlexTimer 2*/
							SIM->SCGC3 |= FLEX_TIMER_1_CLOCK_GATING;
							break;

						default:
							break;
					}
}


void FTM_write_protection_disable(FTM_channel_t channel, FTM_WP_DIS_t writeprot){
	switch(channel)
			{
				case (FTM_0):
						if (writeprot)
						{
							/* When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
									FTM0->MODE |= FLEX_TIMER_WPDIS;
									/**Enables the writing over all registers*/
									FTM0->MODE &= ~FLEX_TIMER_FTMEN;
						}
						else
									FTM0->MODE |= ~FLEX_TIMER_WPDIS;
									/**Enables the writing over all registers*/
									FTM0->MODE &= FLEX_TIMER_FTMEN;;
						break;

				case (FTM_1):
								if (writeprot)
								{
									/* When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
											FTM1->MODE |= FLEX_TIMER_WPDIS;
											/**Enables the writing over all registers*/
											FTM1->MODE &= ~FLEX_TIMER_FTMEN;
								}
								else
											FTM1->MODE |= ~FLEX_TIMER_WPDIS;
											/**Enables the writing over all registers*/
											FTM1->MODE &= FLEX_TIMER_FTMEN;;
								break;
					break;

				case (FTM_2):
								if (writeprot)
								{
									/* When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
											FTM2->MODE |= FLEX_TIMER_WPDIS;
											/**Enables the writing over all registers*/
											FTM2->MODE &= ~FLEX_TIMER_FTMEN;
								}
								else
											FTM2->MODE |= ~FLEX_TIMER_WPDIS;
											/**Enables the writing over all registers*/
											FTM2->MODE &= FLEX_TIMER_FTMEN;;
								break;
					break;
				case (FTM_3):
												if (writeprot)
												{
													/* When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
															FTM3->MODE |= FLEX_TIMER_WPDIS;
															/**Enables the writing over all registers*/
															FTM3->MODE &= ~FLEX_TIMER_FTMEN;
												}
												else
															FTM3->MODE |= ~FLEX_TIMER_WPDIS;
															/**Enables the writing over all registers*/
															FTM3->MODE &= FLEX_TIMER_FTMEN;;
												break;
									break;

				default:
					break;
			}
}
void FTM_counter(FTM_channel_t channel, uint16_t count){
	switch(channel)
				{
					case (FTM_0):
						FTM0->MOD = count;
						break;

					case (FTM_1):
						FTM1->MOD = count;
						break;

					case (FTM_2):
						FTM2->MOD = count;
						break;
					case (FTM_3):
						FTM3->MOD = count;
						break;

					default:
						break;
				}

	}
void FTM_duty_cycle_value(FTM_channel_t channel, FTM_canal_t canal, uint16_t channelValue)
{	switch(channel) {
	case (FTM_0):
			FTM0->CONTROLS[canal].CnV = channelValue;
		break;

	case (FTM_1):
			FTM1->CONTROLS[canal].CnV = channelValue;
		break;

	case (FTM_2):
			FTM2->CONTROLS[canal].CnV = channelValue;
		break;
	case (FTM_3):
				FTM3->CONTROLS[canal].CnV = channelValue;
			break;

	default:
		break;
}
}

void FMT_mode_edge_level_selection(FTM_channel_t channel,FTM_canal_t canal, uint8_t mels){
	switch(channel)
				{
					case (FTM_0):
				FTM0->CONTROLS[canal].CnSC = mels;
						break;

					case (FTM_1):
				FTM1->CONTROLS[canal].CnSC = mels;
						break;

					case (FTM_2):
				FTM2->CONTROLS[canal].CnSC = mels;
						break;
					case (FTM_3):
									FTM3->CONTROLS[canal].CnSC = mels;
											break;

					default:
						break;
				}

}
void FTM_timer(FTM_channel_t channel, uint8_t PS, uint8_t clock)
					{
	switch(channel)
{
	case (FTM_0):
		/**Configure the times*/
		FTM0->SC = clock | PS | FLEX_TIMER_CPWMS;
		break;

	case (FTM_1):
		FTM1->SC = clock | PS | FLEX_TIMER_CPWMS;
		break;

	case (FTM_2):
		FTM2->SC = clock | PS | FLEX_TIMER_CPWMS;
		break;
	case (FTM_3):
			FTM3->SC = clock | PS | FLEX_TIMER_CPWMS;
			break;

	default:
		break;
}
					}
	void FTM_clean(FTM_channel_t channel){
		switch(channel)
	{
		case (FTM_0):
		FTM0->COMBINE=clear;
		FTM0->CNTIN=clear;
			break;

		case (FTM_1):
		FTM1->COMBINE=clear;
		FTM1->CNTIN=clear;
			break;

		case (FTM_2):
		FTM2->COMBINE=clear;
		FTM2->CNTIN=clear;
			break;
		case (FTM_3):
				FTM3->COMBINE=clear;
				FTM3->CNTIN=clear;
					break;

		default:
			break;
	}


								}

void FlexTimer_Init(const FTM_config_t* FTM_Config)
{
		FTM_clk(FTM_Config->FTM_channel);
		FTM_write_protection_disable(FTM_Config->FTM_channel, FTM_Config->FTM_WP_DIS);
		FTM_counter(FTM_Config->FTM_channel, FTM_Config->count);
		FMT_mode_edge_level_selection(FTM_Config->FTM_channel,FTM_Config->FTM_canal, FTM_Config->mels);
		FTM_duty_cycle_value(FTM_Config->FTM_channel,FTM_Config->FTM_canal, FTM_Config->channelValue);
		FTM_clean(FTM_Config->FTM_channel);
		FTM_timer(FTM_Config->FTM_channel, FTM_Config->PS, FTM_Config->clock);
}


