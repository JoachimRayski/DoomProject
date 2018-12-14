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
	// create an empty scene component
	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>("ROOT");
	// make this empty component the root object
	SetRootComponent(sceneComp);
	// create the weapon mesh
	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WEAPON_MESH");
	// attach the mesh to the root component of the actor
	weaponMesh->SetupAttachment(GetRootComponent());
	// create the weapon light
	weaponLight = CreateDefaultSubobject<UPointLightComponent>("WEAPON_LIGHT");
	// attach the light to the root component of the actor
	weaponLight->SetupAttachment(GetRootComponent());
	// hide the component first
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
	// has enough time passed
	if(GetWorld()->GetTimeSeconds() < nextFire)
		return false;
	// do we have ammo to shoot?
	if (currentAmmo <= 0)
		return false;
	// reduce ammo
	currentAmmo--;
	// updating the time interval thingy
	nextFire = GetWorld()->GetTimeSeconds() + rateOfFire;
	// call under the hood on shoot event
	OnWeaponShoot();
	// call the BP event
	BPEVENT_OnWeaponShoot();

	return true;
}

