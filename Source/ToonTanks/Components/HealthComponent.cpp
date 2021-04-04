// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	this->Health = this->DefaultHealth;
	// get gamemode
	this->GameMode = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(this->GetWorld()));
	// create damage binding
	this->GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	// validate damage
	if (Damage == 0)
	{
		return;
	}
	// you could also use damage to add health pick ups

	// apply damage value to health
	this->Health = FMath::Clamp(this->Health - Damage, 0.0f, this->DefaultHealth);

	// send actor died damage if health lower than zero
	if (this->Health <= 0)
	{
		if (this->GameMode != NULL)
		{
			// let game mode this actor died
			this->GameMode->ActorDied(this->GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health Component has no reference to GameMode in %s"), *this->GetOwner()->GetName());
		}
	}
}


