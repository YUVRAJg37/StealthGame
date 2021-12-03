// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIController.h"

#include "FPSAICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void AFPSAIController::BeginPlay()
{
	Super::BeginPlay();

	FPSAiCharacter = Cast<AFPSAICharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), FPSAICharacterClass));

	if(FPSAiCharacter)
	{	
		TargetOne();
	}
	
}

void AFPSAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(FPSAiCharacter->AiState == EAiState::Alerted)
	{
		StopMovement();
	}
	else if ( FPSAiCharacter->AiState == EAiState::Suspecious)
	{
		FPSAiCharacter->GetCharacterMovement()->SetActive(false);
		FTimerHandle SusTimerHandle;
		GetWorldTimerManager().SetTimer(SusTimerHandle, this, &AFPSAIController::Sus, 3.0f);
	}
	else if(FVector::Dist(FPSAiCharacter->GetTargetPointArray(0)->GetActorLocation(), FPSAiCharacter->GetActorLocation()) < 150.0f)
	{
		FPSAiCharacter->GetCharacterMovement()->SetActive(true);
		WaitTwo();
	}
	else if(FVector::Dist(FPSAiCharacter->GetTargetPointArray(1)->GetActorLocation(), FPSAiCharacter->GetActorLocation()) < 150.0f)
	{
		FPSAiCharacter->GetCharacterMovement()->SetActive(true);
		WaitOne();
	}
	
}

void AFPSAIController::TargetOne()
{
	FPSAiCharacter->GetCharacterMovement()->SetActive(true);
	MoveToActor(FPSAiCharacter->GetTargetPointArray(0));
}

void AFPSAIController::TargetTwo()
{
	FPSAiCharacter->GetCharacterMovement()->SetActive(true);
	MoveToActor(FPSAiCharacter->GetTargetPointArray(1));
}

void AFPSAIController::WaitOne()
{
	FTimerHandle TargetOneHandle;

	GetWorldTimerManager().SetTimer(TargetOneHandle, this, &AFPSAIController::TargetOne, 5);
}

void AFPSAIController::WaitTwo()
{
	FTimerHandle TargetTwoHandle;

	GetWorldTimerManager().SetTimer(TargetTwoHandle, this, &AFPSAIController::TargetTwo, 5);
}

void AFPSAIController::Sus()
{
	TargetOne();
	// if(FVector::Dist(FPSAiCharacter->GetTargetPointArray(0)->GetActorLocation(), FPSAiCharacter->GetActorLocation()) < FVector::Dist(FPSAiCharacter->GetTargetPointArray(1)->GetActorLocation(), FPSAiCharacter->GetActorLocation()))
	// {
	// 	TargetOne();
	// }
	// else
	// {
	// 	TargetTwo();
	// }
}


