// Fill out your copyright notice in the Description page of Project Settings.

#include "DoomWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Engine/World.h"


// Sets default values
ADoomWeapon::ADoomWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>("ROOT");

	SetRootComponent(sceneComp);

	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WEAPON_MESH");

	weaponMesh->SetupAttachment(GetRootComponent());

	weaponLight = CreateDefaultSubobject<UPointLightComponent>("WEAPON_LIGHT");

	weaponLight->SetupAttachment(GetRootComponent());
	weaponLight->SetHiddenInGame(true);


}

// Called when the game starts or when spawned
void ADoomWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoomWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoomWeapon::OnWeaponShoot()
{

}

bool ADoomWeapon::Shoot()
{
	if(GetWorld()->GetTimeSeconds() < nextFire)
		return false;
	if (currentAmmo <= 0)
		return false;

	currentAmmo--;
	nextFire = GetWorld()->GetTimeSeconds() + rateOfFire;

	OnWeaponShoot();
	BPEVENT_OnWeaponShoot();

	return true;
}

