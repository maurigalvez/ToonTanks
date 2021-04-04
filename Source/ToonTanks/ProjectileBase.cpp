// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	this->RootComponent = this->ProjectileMesh;

	this->ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	this->ProjectileMovement->InitialSpeed = this->MoveSpeed;
	this->ProjectileMovement->MaxSpeed = this->MoveSpeed;

	// this will make this destroy after 3f
	this->InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	// register event when this component is hit
	this->ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// make sure you cannot collide against yourself
	AActor* projectileOwner = this->GetOwner();
	if (projectileOwner == nullptr)
	{
		return;
	}
	// check whether you should apply damage 
	if (OtherActor && OtherActor != this && OtherActor != projectileOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, this->Damage, this->GetOwner()->GetInstigatorController(), this, this->DamageType);
		// play visual effects here!
		if (this->HitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, this->HitParticle, this->GetActorLocation());
		}
		Destroy();
	}		
}


