// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "GameFramework/Pawn.h"

void APlayerControllerBase::SetPlayerEnabledState(bool SetPlayerEnabled)
{
	if (SetPlayerEnabled)
	{
		this->GetPawn()->EnableInput(this);
	}
	else
	{
		this->GetPawn()->DisableInput(this);
	}
	this->bShowMouseCursor = SetPlayerEnabled;
}