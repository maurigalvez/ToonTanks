// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{

}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	// set timer
	this->GetWorld()->GetTimerManager().SetTimer(this->FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, this->FireRate, true);
	// get player pawn
	this->PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (this->PlayerPawn == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("No player pawn was found in %s"), *this->GetName());
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("Initialized"), *this->GetName());
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void APawnTurret::CheckFireCondition()
{
	// If player == NULL or Is Dead then bail'
	if (this->PlayerPawn == NULL || !this->PlayerPawn->CheckIsPlayerAlive())
	{		
		return;
	}
	// Check if player is within range
	if (this->ReturnDistanceToPlayer() <= this->FireRange)
	{
		// fire
		this->Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (this->PlayerPawn == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("No player pawn was found in %s"), *this->GetName());
		return 0.0f;
	}
	return FVector::Dist(this->PlayerPawn->GetActorLocation(), this->GetActorLocation());
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// if no player was found or out of range then return
	if (this->PlayerPawn == NULL || !this->PlayerPawn->CheckIsPlayerAlive() || this->ReturnDistanceToPlayer() > this->FireRange)
	{
		return;
	}
	// look at player
	this->RotateTurret(this->PlayerPawn->GetActorLocation());
}