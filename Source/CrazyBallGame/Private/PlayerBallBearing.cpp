// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBallBearing.h"
#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"

APlayerBallBearing::APlayerBallBearing()
{
	Magnetized = false;
}
//Establish the default pawn input bindings for a PlayerBallBearing.
static void InitializeDefaultPawnInputBindings()
{
	static bool bindingsAdded = false;

	if (bindingsAdded == false)
	{
		bindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::S, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::Up, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::Down, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::Gamepad_LeftY, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::D, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::Left, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::Right, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::Gamepad_LeftX, 1.f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("BallBearing_Jump", EKeys::Enter));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("BallBearing_Dash", EKeys::SpaceBar));
	}
}

//Called to bind functionality to input.
void APlayerBallBearing::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	check(playerInputComponent != nullptr);

	Super::SetupPlayerInputComponent(playerInputComponent);

	InitializeDefaultPawnInputBindings();

	playerInputComponent->BindAxis("BallBearing_MoveLongitudinally", this, &APlayerBallBearing::MoveLongitudinally);
	playerInputComponent->BindAxis("BallBearing_MoveLaterally", this, &APlayerBallBearing::MoveLaterally);

	playerInputComponent->BindAction("BallBearing_Jump", EInputEvent::IE_Pressed, this, &APlayerBallBearing::Jump);
	playerInputComponent->BindAction("BallBearing_Dash", EInputEvent::IE_Pressed, this, &APlayerBallBearing::Dash);
}

//Have the ball bearing perform a jump.
void APlayerBallBearing::Jump()
{
}

//Have the ball bearing perform a dash.
void APlayerBallBearing::Dash()
{
}

void APlayerBallBearing::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	BallMesh->AddForce(FVector(InputLongitude, InputLatitude, 0.0f) * ControllerForce * BallMesh->GetMass());
}