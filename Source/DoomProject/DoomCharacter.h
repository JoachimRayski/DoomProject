// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DoomCharacter.generated.h"

class UCameraComponent;
class UWeaponInventory;

UCLASS()
class DOOMPROJECT_API ADoomCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADoomCharacter();

	UPROPERTY(Category = DoomCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* camera;

	UPROPERTY(Category = DoomCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UWeaponInventory* inventory;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// update shooting if auto fire
	void UpdateShootingAction();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Input functions for movement
	void MoveForward(float scale);
	void MoveRight(float scale);
	void Turn(float scale);
	void Pitch(float scale);

	void ShootPressAction();
	void ShootReleaseAction();
	void CycleWeaponAction();

	// BP EVENTS ////////////////////////

	// Called when the current weapon is fired
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Current Weapon Shoot"))
		void BPEVENT_OnCurrentWeaponShoot();

	// Called when the current weapon is switched
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Current Weapon Switch"))
		void BPEVENT_OnCurrentWeaponSwitched();

private:

	bool isShooting = false;
};
