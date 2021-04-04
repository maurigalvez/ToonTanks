// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APawnTurret;
class APlayerControllerBase;
/**
 * Handle Tank Game rules
 */
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

private:

	// used to handle game start
	void HandleGameStart();

	// use to handle game over
	void HandleGameOver(bool PlayerWon);

	// return current target count
	int32 GetTargetTurretCount();

	// ----------
	// PROPERTIES
	// -----------
	APawnTank* PlayerTank = nullptr;
	int32 TargetTurrets = 0;
	APlayerControllerBase* PlayerController = nullptr;
	
};
