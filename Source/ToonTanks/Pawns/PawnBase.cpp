// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create capsule component
	this->CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	this->RootComponent = this->CapsuleComp;

	//create base mesh
	this->BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	this->BaseMesh->SetupAttachment(this->RootComponent);

	// create turret mesh
	this->TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	this->TurretMesh->SetupAttachment(this->BaseMesh);

	// create projectile spawn point
	this->ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	this->ProjectileSpawnPoint->SetupAttachment(this->TurretMesh);

	// create health component
	this->HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	// clean to handle rotation
	FVector LookAtTargerClean = FVector(LookAtTarget.X, LookAtTarget.Y, this->TurretMesh->GetComponentLocation().Z);
	// start location
	FVector StartLocation = this->TurretMesh->GetComponentLocation();

	// Update turret mesh rotation to face towards look at target from child classes
	// we use the direction towards look at target
	FRotator turretRotation = FVector(LookAtTargerClean - StartLocation).Rotation();

	this->TurretMesh->SetWorldRotation(turretRotation);
}

void APawnBase::Fire()
{
	// Get Projectile spawn points location && rotation - > spawn projectile class at location firing towards rotation
	if (this->ProjectileToSpawn != NULL)
	{
		FVector spawnLocation = this->ProjectileSpawnPoint->GetComponentLocation();
		FRotator spawnRotation = this->ProjectileSpawnPoint->GetComponentRotation();
		// spawn projectile at spawn location and rotation
		AProjectileBase* tempProjectile = GetWorld()->SpawnActor<AProjectileBase>(this->ProjectileToSpawn, spawnLocation, spawnRotation);
		// set parent author to this to prevent collision with owner
		tempProjectile->SetOwner(this);
	}
}

void APawnBase::PawnDestroyed()
{
}

void APawnBase::HandleDestruction()
{
	// Play death effects particle, sound and camera shake
	UGameplayStatics::SpawnEmitterAtLocation(this, this->DeathParticle, this->GetActorLocation());
}
