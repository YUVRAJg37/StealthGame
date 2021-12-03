// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "FPSAICharacter.generated.h"

UENUM(BlueprintType)
enum class EAiState : uint8
{
	Idle,
	Suspecious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAICharacter();

	UFUNCTION()
	void OnSeeing(APawn* Pawn);
	UFUNCTION()
	void OnHeering(APawn* PawnInstigator, const FVector& Location, float Volume);
	UFUNCTION()
	void ResetOrientation();
	UFUNCTION(BlueprintImplementableEvent, Category = Ai)
	void GuardAiState(EAiState GuardState);
	void SetGuardAiState(EAiState NewState);
	void GuardPatrolling();

	EAiState AiState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensingComponent;
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UPathFollowingComponent* PathFollowingComponent;

	FRotator OriginalRotation;
	FTimerHandle RotationTimerHandle;
	
	

	UPROPERTY(EditInstanceOnly, Category = "Targets")
	TArray<ATargetPoint*> TargetPointsArray;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE AActor* GetTargetPointArray(int32 index);

};



