// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"

// constructor
APawnTank::APawnTank()
{	
	//create spring arm component
	this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	this->SpringArm->SetupAttachment(this->RootComponent);

	// create camera component
	this->Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	this->Camera->SetupAttachment(this->SpringArm);
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();
}

void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// you rotate before you move
	this->Rotate();
	this->Move();
}

void APawnTank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// bind player movemnt
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
}

void APawnTank::CalculateMoveInput(float Value)
{
	// only move on X value
	this->MoveDirection = FVector(Value * this->MoveSpeed * this->GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(float Value)
{
	float rotateAmount = Value * this->RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator rotation = FRotator(0, rotateAmount, 0);
	this->RotationDirection = FQuat(rotation);
}

void APawnTank::Move()
{
	this->AddActorLocalOffset(this->MoveDirection, true);
}

void APawnTank::Rotate()
{
	// we set sweet to tru to prevent any weird rotation issues
	this->AddActorLocalRotation(this->RotationDirection, true);
}