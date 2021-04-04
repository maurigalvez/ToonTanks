// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;
/**
 * Class to define Pawn turret controlled by AI
 */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

public:
	// constructor
	APawnTurret();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void HandleDestruction() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	// used to check whether this turret should fire at player
	void CheckFireCondition();

	// return distance between this pawn turret and player pawn
	float ReturnDistanceToPlayer();

	// simulate looking for player
	void LookForPlayer(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float SurveillanceRotationSpeed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float SurveillanceAngle = 25.f;
	
	// Yaw turret mesh starts at
	float StartYawAngle = 0;

	// Delay before turret can start doing surveillance
	float RandomDelay = 0;

	// How much time has passed since turret is doing surveillance
	float RunningTime = 0;

	FTimerHandle FireRateTimerHandle;

	APawnTank* PlayerPawn = nullptr;
};
