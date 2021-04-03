// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// check what type of actor died. If turret, tally. If player -> go to lose condition.
}

void ATankGameModeBase::HandleGameStart()
{
	// Initialize the start countdown, turret activation, pawn check et.
	// call blueprint version of gamestart
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// See if the player has destroyed all the turrets, show win result
	// otherwse turret destroyed player, show lose result
	// Call blueprint version of GameOver
}
