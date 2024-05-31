#pragma once

#include "Framework/Notifications/NotificationManager.h"
#include "Misc/MessageDialog.h"
#include "Widgets/Notifications/SNotificationList.h"

void Print(const FString& message, const FColor& color)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, color, message);
	}
}
void PrintLog(const FString& Message)
{
    UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
}

EAppReturnType::Type ShowMessageDialog(EAppMsgType::Type MsgTyp, const FString& Message, bool bShowMessageAsWarning = true)
{
	if(bShowMessageAsWarning)
	{
		FText MsgTitle = FText::FromString(TEXT("Warning"));
		return FMessageDialog::Open(MsgTyp, FText::FromString(Message), &MsgTitle);
	}
	else
	{
		return FMessageDialog::Open(MsgTyp, FText::FromString(Message));
	}
}

void ShowNotifyInfo(const FString &Message)
{
	FNotificationInfo NotifyInfo(FText::FromString(Message));
	NotifyInfo.bUseLargeFont = true;
	NotifyInfo.FadeOutDuration = 7.0f;

	FSlateNotificationManager::Get().AddNotification(NotifyInfo);
}