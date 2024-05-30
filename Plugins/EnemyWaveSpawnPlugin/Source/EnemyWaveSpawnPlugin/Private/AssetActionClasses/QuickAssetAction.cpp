// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActionClasses/QuickAssetAction.h"
#include "DebugHeader.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"

void UQuickAssetAction::DuplicateAssets(int32 NumOfDuplicates)
{
	if(NumOfDuplicates <= 0)
	{
		Print(TEXT("Please enter a valid duplicate Number"), FColor::Red);
		return;
	}

	TArray<FAssetData> SelectedAssetsData = UEditorUtilityLibrary::GetSelectedAssetData();
	int32 count = 0;
	for (const auto&d : SelectedAssetsData)
	{
		for (int32 i= 0; i < NumOfDuplicates; i++)
		{
			const FString SourceAssetPath = d.GetSoftObjectPath().ToString();
			const FString NewDuplicatedAssetName = d.AssetName.ToString() + TEXT("_") + FString::FromInt(i + 1);
			const FString NewPathName = FPaths::Combine(d.PackagePath.ToString(), NewDuplicatedAssetName);

			if(UEditorAssetLibrary::DuplicateAsset(SourceAssetPath, NewPathName))
			{
				UEditorAssetLibrary::SaveAsset(NewPathName, false);
				++count;
			}
		}
	}
}
