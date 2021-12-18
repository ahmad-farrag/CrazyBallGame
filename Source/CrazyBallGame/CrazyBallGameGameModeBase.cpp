// Copyright Epic Games, Inc. All Rights Reserved.


#include "CrazyBallGameGameModeBase.h"
#include "BallBearingHUD.h"

//Construct the game mode, assigning a debugging HUD class.
ACrazyBallGameGameModeBase::ACrazyBallGameGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HUDClass = ABallBearingHUD::StaticClass();
}