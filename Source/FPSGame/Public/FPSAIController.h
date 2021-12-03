// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSAICharacter.h"
#include "FPSCharacter.h"
#include "Engine/TargetPoint.h"
#include "FPSAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSAIController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	AFPSAICharacter* FPSAiCharacter;

	bool bCondition;

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AFPSAICharacter> FPSAICharacterClass;

	void TargetOne();
	void WaitOne();
	void TargetTwo();
	void WaitTwo();
	void Sus();
};
