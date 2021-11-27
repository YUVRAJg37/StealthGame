// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"

#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALaunchPad::ALaunchPad() :
PlayerLaunchFactor(500.0f),
BoxLaunchFactor(1000.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaunchPadMesh = CreateDefaultSubobject<UStaticMeshComponent>("Launch Pad Mesh");
	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>("Arrow Mesh");
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");

	RootComponent = LaunchPadMesh;
	ArrowMesh->SetupAttachment(LaunchPadMesh);
	BoxComponent->SetupAttachment(LaunchPadMesh);

	ArrowMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);

	
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::OnBeginOverlap);
}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALaunchPad::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(OtherActor);
	if(PlayerCharacter)
	{
		FVector ActorForwardVector = LaunchPadMesh->GetForwardVector();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorForwardVector.ToString());
		PlayerCharacter->LaunchCharacter(FVector(-ActorForwardVector.X*PlayerLaunchFactor, -ActorForwardVector.Y*PlayerLaunchFactor, PlayerLaunchFactor), false, false);
	}
	if(OtherComp->IsSimulatingPhysics() && OtherComp)
	{
		FVector ActorForwardVector = LaunchPadMesh->GetForwardVector();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherComp->GetName());
		// OtherComp->AddImpulseAtLocation(FVector(-ActorForwardVector.X*LaunchFactor, -ActorForwardVector.Y*LaunchFactor, LaunchFactor), OtherComp->GetComponentLocation());
		OtherComp->AddImpulse(FVector(-ActorForwardVector.X*BoxLaunchFactor, -ActorForwardVector.Y*BoxLaunchFactor, BoxLaunchFactor), NAME_None, true);
	}

	if(LaunchParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchParticles, GetActorLocation());
	}
}

