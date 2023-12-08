// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Mini_Jame_GamGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MINI_JAME_GAM_API AMini_Jame_GamGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
	
};
