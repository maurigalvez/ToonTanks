// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
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
	// get original turret yaw
	this->StartYawAngle = this->TurretMesh->GetComponentRotation().Yaw;
	// add a random delay to make surveleance more random
	this->RandomDelay = FMath::FRandRange(0, 1);
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

void APawnTurret::LookForPlayer(float DeltaTime)
{
	this->RunningTime += DeltaTime;
	FRotator turretRotation = this->TurretMesh->GetComponentRotation();
	// use sin wave to rotate turret yaw
	turretRotation.Yaw = this->StartYawAngle + FMath::Sin(this->RunningTime) * this->SurveillanceAngle;
	// smooth rotation
	FRotator newRotation = FMath::Lerp(this->TurretMesh->GetComponentRotation(), turretRotation, DeltaTime * this->SurveillanceRotationSpeed);
	// apply rotation
	this->TurretMesh->SetWorldRotation(newRotation);
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// if no player was found or out of range then return
	if (this->PlayerPawn != NULL && this->PlayerPawn->CheckIsPlayerAlive() &&  this->ReturnDistanceToPlayer() <= this->FireRange)
	{
		// look at player
		this->RotateTurret(this->PlayerPawn->GetActorLocation());
	}
	else if(this->RandomDelay < 0)
	{		
		// look at player
		this->LookForPlayer(DeltaTime);
	}
	else
	{
		this->RandomDelay -= DeltaTime;
	}
	
}