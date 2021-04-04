// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ToonTanks/ProjectileBase.h"
#include "PawnBase.generated.h"

class UHealthComponent;
class UCapsuleComponent;	// this also works as an include, the main difference is that include also allow access to functions/ properties
							// where this won't

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();

	// handle turret destruction (spawn vfx/sfx) 
	virtual void  HandleDestruction();

protected:
	// rotate turret mesh towards target
	virtual void RotateTurret(FVector LookAtTarget);

	// will spawn projectile and fire it in look direction
	virtual void Fire();

private:
    
	// ---------
	// COMPONENTS
	// ---------
	// collision component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent = nullptr;

	// ---------
	// VARIABLES
	// ---------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileToSpawn;

	UPROPERTY(EditAnywhere, Category ="Effects")
	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* DeathSound;	

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShake> ExplosionShake;
};
