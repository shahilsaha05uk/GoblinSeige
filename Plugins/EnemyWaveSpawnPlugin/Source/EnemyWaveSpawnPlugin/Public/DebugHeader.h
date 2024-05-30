#pragma once

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