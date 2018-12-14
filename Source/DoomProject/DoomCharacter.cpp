// Fill out your copyright notice in the Description page of Project Settings.

#include "DoomCharacter.h"
#include "Components/InputComponent.h"
#include "Engine.h"
#include "Camera/CameraComponent.h"
#include "WeaponInventory.h"
#include "DoomWeapon.h"

// Sets default values
ADoomCharacter::ADoomCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	camera = CreateDefaultSubobject<UCameraComponent>("CAMERA");

	camera->SetupAttachment(GetRootComponent());

	inventory = CreateDefaultSubobject<UWeaponInventory>("WEAPONS");
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

void ADoomCharacter::UpdateShootingAction()
{
	if (!isShooting)
		return;

	if (inventory->FireCurrentWeapon())
		BPEVENT_OnCurrentWeaponShoot();
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

	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ADoomCharacter::ShootPressAction);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Released, this, &ADoomCharacter::ShootReleaseAction);

	PlayerInputComponent->BindAction("Cycle", EInputEvent::IE_Pressed, this, &ADoomCharacter::CycleWeaponAction);
}

void ADoomCharacter::MoveForward(float scale)
{
	if(scale > 0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Red, "MOVING FORWARDS");
	if(scale < -0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Blue, "MOVING BACKWARDS");

	// Move character in forward direction based on the scale
	AddMovementInput(GetActorForwardVector(), scale);
}

void ADoomCharacter::MoveRight(float scale)
{
	if (scale > 0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Green, "MOVING RIGHT");
	if (scale < -0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Yellow, "MOVING LEFT");

	// Move character in sideways direction based on the scale
	AddMovementInput(GetActorRightVector(), -scale);
}

void ADoomCharacter::Turn(float scale)
{
	if (scale > 0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Black, "TURN RIGHT");
	if (scale < -0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::White, "TURN LEFT");

	// Turn the character's facing direction horizontally based on the scale
	AddControllerYawInput(scale);
}

void ADoomCharacter::Pitch(float scale)
{
	if (scale > 0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Purple, "TURN UP");
	if (scale < -0.5f)
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Cyan, "TURN DOWN");

	// Turn the character's facing direction vertically based on the scale
	AddControllerPitchInput(-scale);
}

void ADoomCharacter::ShootPressAction()
{
	if (inventory->GetCurrentWeapon()->isSemiAuto && inventory->FireCurrentWeapon())
		BPEVENT_OnCurrentWeaponShoot();
	else isShooting = true;
}

void ADoomCharacter::ShootReleaseAction()
{
	isShooting = true;
}

void ADoomCharacter::CycleWeaponAction()
{
	if (inventory->CanSwitchWeapon() && inventory->SwitchWeapon())
		BPEVENT_OnCurrentWeaponSwitched();
}
