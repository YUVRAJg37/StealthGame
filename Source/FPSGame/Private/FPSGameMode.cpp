// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if(InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);
		OnMissionCompletion(InstigatorPawn);

		TArray<AActor*> SpectatingViewTargetArray;
		
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpectatingActorClass, SpectatingViewTargetArray);

		if(SpectatingViewTargetArray.Num()>0)
		{
			AActor* ViewTarget = SpectatingViewTargetArray[0];

			if(ViewTarget)
			{
				APlayerController* PlayerController = Cast<APlayerController>(InstigatorPawn->GetController());
				if(PlayerController)
				{
					PlayerController->SetViewTargetWithBlend(ViewTarget, 0.5, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
	}
}
