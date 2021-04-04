// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
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

	UFUNCTION(BlueprintCallable)
	// return current target count
	int32 GetTargetTurretCount();

	UFUNCTION(BlueprintCallable)
	float GetPlayerHealthPercentage();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Settings")
	TSubclassOf<APawnTurret> EnemyToSpawn;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTurretCount(int turretCount);

private:

	// used to handle game start
	void HandleGameStart();

	// use to handle game over
	void HandleGameOver(bool PlayerWon);

	// Spawn enemies
	void SpawnEnemies();

	// ----------
	// PROPERTIES
	// -----------
	APawnTank* PlayerTank = nullptr;
	int32 TargetTurrets = 0;
	APlayerControllerBase* PlayerController = nullptr;
	
};
