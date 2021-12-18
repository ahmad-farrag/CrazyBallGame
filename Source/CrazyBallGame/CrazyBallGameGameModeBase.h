// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CrazyBallGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYBALLGAME_API ACrazyBallGameGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:

	// Construct the game mode, assigning a debugging HUD class.
	ACrazyBallGameGameModeBase();
	
};
