// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_CountdownTimer.h"


bool UDA_CountdownTimer::GetCountDownDetails(int Wave, FWaveCountDownTimerDetails& Details)
{
	if(CountDownMap.Contains(Wave))
	{
		Details = CountDownMap[Wave];
		return true;
	}

	return false;
}
