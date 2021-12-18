// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "BallBearing.generated.h"

UCLASS()
class ABallBearing : public APawn
{
	GENERATED_BODY()

public:

	// Create a static mesh for this ball bearing on object construction.
	ABallBearing();

	// The static mesh that represents the ball bearing.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BallBearing)
		UStaticMeshComponent* BallMesh = nullptr;

	// Is the ball bearing attractive to magnets?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
		bool Magnetized = true;

};
