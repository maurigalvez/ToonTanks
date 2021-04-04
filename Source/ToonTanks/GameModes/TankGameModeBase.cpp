// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

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
		// disable controller
		if (this->PlayerController != nullptr)
		{
			this->PlayerController->SetPlayerEnabledState(false);
		}
	}
	// if destroyed actor is a turret
	else if(APawnTurret* destroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		destroyedTurret->HandleDestruction();
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
	// get player controller reference
	this->PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	// call blueprint version of gamestart
	this->GameStart();
	// enable controller
	if (this->PlayerController != nullptr)
	{
		// disable player controller
		this->PlayerController->SetPlayerEnabledState(false);
		// make sure that you enable after timer
		FTimerHandle playerEnabledHandle;
		FTimerDelegate playerEnableDelegate = FTimerDelegate::CreateUObject(this->PlayerController, &APlayerControllerBase::SetPlayerEnabledState, true);
		// create timer for player start
		this->GetWorld()->GetTimerManager().SetTimer(playerEnabledHandle, playerEnableDelegate, this->StartDelay, false);
	}
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// See if the player has destroyed all the turrets, show win result
	// otherwse turret destroyed player, show lose result

	// Call blueprint version of GameOver
	this->GameOver(PlayerWon);
	if (this->PlayerController != nullptr)
	{
		// disable player controller
		this->PlayerController->SetPlayerEnabledState(false);
	}
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> turretActors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), APawnTurret::StaticClass(), turretActors);
	return turretActors.Num();
}
