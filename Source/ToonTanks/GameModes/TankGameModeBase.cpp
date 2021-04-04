// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// start game
	this->HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// check what type of actor died. If turret, tally. If player -> go to lose condition.
	if(DeadActor == this->PlayerTank)
	{
		this->PlayerTank->HandleDestruction();
		this->HandleGameOver(false);
	}
	// if destroyed actor is a turret
	else if(APawnTurret* destroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		if (--this->TargetTurrets <= 0)
		{
			this->HandleGameOver(true);
		}
	}
}

void ATankGameModeBase::HandleGameStart()
{
	// Initialize the start countdown, turret activation, pawn check et.
	this->TargetTurrets = this->GetTargetTurretCount();
	// get player tank ref
	this->PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// call blueprint version of gamestart
	this->GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// See if the player has destroyed all the turrets, show win result
	// otherwse turret destroyed player, show lose result

	// Call blueprint version of GameOver
	this->GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> turretActors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), APawnTurret::StaticClass(), turretActors);
	return turretActors.Num();
}
