// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSActorObjective.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSActorObjective::AFPSActorObjective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Component");

	RootComponent = MeshComponent;
	SphereComponent->SetupAttachment(MeshComponent);
	
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
}

// Called when the game starts or when spawned
void AFPSActorObjective::BeginPlay()
{
	Super::BeginPlay();

	PlayEffects();
}

// Called every frame
void AFPSActorObjective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSActorObjective::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();
}

void AFPSActorObjective::PlayEffects()
{
	if(PickupFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupFX, GetActorLocation());
	}
}


