// Fill out your copyright notice in the Description page of Project Settings.

#include "DoomCharacter.h"
#include "Components/InputComponent.h"
#include "Engine.h"

// Sets default values
ADoomCharacter::ADoomCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoomCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADoomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind action to Input
	PlayerInputComponent->BindAxis("MoveForward", this, &ADoomCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADoomCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ADoomCharacter::Turn);
	PlayerInputComponent->BindAxis("Pitch", this, &ADoomCharacter::Pitch);
}

void ADoomCharacter::MoveForward(float scale)
{
	if(scale > 0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Red, "MOVING FORWARDS");
	if(scale < -0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Blue, "MOVING BACKWARDS");

	AddMovementInput(GetActorForwardVector(), scale);
}

void ADoomCharacter::MoveRight(float scale)
{
	if (scale > 0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Green, "MOVING RIGHT");
	if (scale < -0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Yellow, "MOVING LEFT");

	AddMovementInput(GetActorRightVector(), -scale);
}

void ADoomCharacter::Turn(float scale)
{
	if (scale > 0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Black, "TURN RIGHT");
	if (scale < -0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::White, "TURN LEFT");

	AddControllerYawInput(scale);
}

void ADoomCharacter::Pitch(float scale)
{
	if (scale > 0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Purple, "TURN UP");
	if (scale < -0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Cyan, "TURN DOWN");

	AddControllerPitchInput(-scale);
}
