// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAICharacter.h"

#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSAICharacter::AFPSAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("Pawn Sensing Component");
	PathFollowingComponent = CreateDefaultSubobject<UPathFollowingComponent>("Path Following Component");

}

// Called when the game starts or when spawned
void AFPSAICharacter::BeginPlay()
{
	Super::BeginPlay();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AFPSAICharacter::OnSeeing);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AFPSAICharacter::OnHeering);

	OriginalRotation = GetActorRotation();

	SetGuardAiState(EAiState::Idle);
	
}

// Called every frame
void AFPSAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AFPSAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AActor* AFPSAICharacter::GetTargetPointArray(int32 index)
{
	return TargetPointsArray[index];
}

void AFPSAICharacter::OnSeeing(APawn* Pawn)
{
	
	if(!Pawn) return;

	DrawDebugSphere(GetWorld(), Pawn->GetActorLocation(), 30.0f, 12, FColor::Emerald, false, 10.0f);
	UE_LOG(LogTemp, Warning, TEXT("Working"));

	AFPSGameMode* Gm = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if(Gm)
	{
		Gm->CompleteMission(Pawn, false);
	}

	SetGuardAiState(EAiState::Alerted);
}

void AFPSAICharacter::OnHeering(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if(AiState == EAiState::Alerted) return;
	
	DrawDebugSphere(GetWorld(), Location, 30.0f, 12, FColor::Red, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0;
	NewLookAt.Roll = 0;
	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(RotationTimerHandle);
	GetWorldTimerManager().SetTimer(RotationTimerHandle, this, &AFPSAICharacter::ResetOrientation, 3.0f);

	SetGuardAiState(EAiState::Suspecious);
}

void AFPSAICharacter::ResetOrientation()
{
	if(AiState == EAiState::Alerted) return;
	SetActorRotation(OriginalRotation);
}

void AFPSAICharacter::SetGuardAiState(EAiState NewState)
{
	if(NewState == AiState) return;

	AiState = NewState;

	GuardAiState(AiState);
}

void AFPSAICharacter::GuardPatrolling()
{
	
}



