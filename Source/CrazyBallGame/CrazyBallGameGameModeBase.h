// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Sound/SoundCue.h"
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

	// The sound cue to play for the background music.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
		USoundCue* BackgroundMusic = nullptr;

	// The sound cue to play when the game has been finished by the player.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
		USoundCue* FinishedSound = nullptr;

protected:

	// Play the background music at the beginning of the game.
	virtual void BeginPlay() override;

	// Manage the game mode, mostly detecting and implementing the end-game state.
	virtual void Tick(float deltaSeconds) override;

private:

	// The amount of time that the game has been finished.
	float FinishedTime = 0.0f;

	// Has the finished sound been played?
	bool FinishedSoundPlayed = false;
};
