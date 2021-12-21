// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBearingGoal.h"
#include "Components/SphereComponent.h"
#include "Components/BillboardComponent.h"



//Constructor for a goal for ball bearings.
ABallBearingGoal::ABallBearingGoal()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorHiddenInGame(false);
}

//Get a ratio of a value between a minimumand maximum amount, optionally clamped.
static float GetRatio(float value, float minimum, float maximum, bool clamp = true)
{
	if (value > maximum && clamp == true)
	{
		return 1.0f;
	}
	else if (value > minimum)
	{
		return (value - minimum) / (maximum - minimum);
	}
	else
	{
		return 0.0f;
	}
}

//Hide the collision and sprite components in-game.
void ABallBearingGoal::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetCollisionComponent()->SetHiddenInGame(true);

#if WITH_EDITORONLY_DATA
	GetSpriteComponent()->SetHiddenInGame(true);
#endif
}

//Add magnetism to the proximate ball bearings, drawing them towards our center.
void ABallBearingGoal::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	FVector ourLocation = GetActorLocation();
	float sphereRadius = Cast<USphereComponent>(GetCollisionComponent())->GetScaledSphereRadius();
	float magnetism = Magnetism;

	// Now iterate around the proximate ball bearings and draw them towards our center
	// using physics forces scaled by magnetism and distance from the center.
	for (ABallBearing* ballBearing : BallBearings)
	{
		FVector difference = ourLocation - ballBearing->GetActorLocation();
		float distance = difference.Size();
		FVector direction = difference;

		direction.Normalize();

		float ratio = GetRatio(distance, 0.0f, sphereRadius);
		FVector force = (1.0f - ratio) * magnetism * direction;

		ballBearing->BallMesh->AddForce(force);
	}
}

//Add a ball bearing to the list of proximate bearings we're maintaining.
void ABallBearingGoal::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	ABallBearing* ballBearing = Cast<ABallBearing>(otherActor);

	if (ballBearing != nullptr &&
		ballBearing->Magnetized == true)
	{
		BallBearings.AddUnique(ballBearing);
	}
}

//Remove a ball bearing from the list of proximate bearings we're maintaining.
void ABallBearingGoal::NotifyActorEndOverlap(AActor* otherActor)
{
	Super::NotifyActorEndOverlap(otherActor);

	ABallBearing* ballBearing = Cast<ABallBearing>(otherActor);

	if (ballBearing != nullptr &&
		ballBearing->Magnetized == true)
	{
		BallBearings.Remove(ballBearing);
	}
}


//Does this goal have a ball bearing resting in its center ?
bool ABallBearingGoal::HasBallBearing() const
{
	FVector ourLocation = GetActorLocation();

	for (const ABallBearing* ballBearing : BallBearings)
	{
		FVector difference = ourLocation - ballBearing->GetActorLocation();
		float distance = difference.Size();

		if (distance < 75.0f)
		{
			return true;
		}
	}

	return false;
}
