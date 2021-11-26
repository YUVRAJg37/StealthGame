// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ABlackHole::ABlackHole() :
Radius(1.0f),
Strength(1.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("BlackHole Mesh");
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Component");

	RootComponent = MeshComponent;
	SphereComponent->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OnBeginOverlap);
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Attract();
}

void ABlackHole::Attract()
{
	SphereComponent->GetOverlappingComponents(OverlappingComponents);

	for(int32 i=0; i<OverlappingComponents.Num(); i++)
	{
		if(OverlappingComponents[i]->IsSimulatingPhysics())
		{
			OverlappingComponents[i]->AddRadialForce(GetActorLocation(), Radius, -Strength, ERadialImpulseFalloff::RIF_Linear, true);
		}
	}
}

void ABlackHole::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		if(DestroyFX)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyFX, OtherActor->GetActorLocation());
		}
		OtherActor->Destroy();
	}
}


