// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* LaunchPadMesh;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* ArrowMesh;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, Category = Components)
	float PlayerLaunchFactor;
	UPROPERTY(EditAnywhere, Category = Components)
	float BoxLaunchFactor;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UParticleSystem* LaunchParticles;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
private:

};


