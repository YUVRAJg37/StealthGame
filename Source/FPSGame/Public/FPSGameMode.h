// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFPSGameMode();

	void CompleteMission(APawn* InstigatorPawn,bool bMissionComplete);
	UFUNCTION(BlueprintImplementableEvent, Category = Functions)
	void OnMissionCompletion(APawn* InstigatorPawn, bool bMissionComplete);

protected:

	UPROPERTY(EditDefaultsOnly, Category = SubClass)
	TSubclassOf<AActor> SpectatingActorClass;
};



