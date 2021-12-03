// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"

#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>("Overlap Component");
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->bHiddenInGame = false;
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	DecalComponent = CreateDefaultSubobject<UDecalComponent>("Decal Component");
	DecalComponent->SetupAttachment(GetRootComponent());
	DecalComponent->DecalSize = FVector(200.0f);
}

// Called when the game starts or when spawned
void AFPSExtractionZone::BeginPlay()
{
	Super::BeginPlay();

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::OnComponentBeginOverlap);
	
}

// Called every frame
void AFPSExtractionZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSExtractionZone::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(OtherActor);

	if(PlayerCharacter && PlayerCharacter->bIScarryingObjective)
	{
		AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->CompleteMission(PlayerCharacter, true);
		}
	}
	else
	{
		if(MissionFailureSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), MissionFailureSound);
		}
	}

}

