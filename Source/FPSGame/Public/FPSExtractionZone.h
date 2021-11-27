// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "FPSExtractionZone.generated.h"

UCLASS()
class FPSGAME_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSExtractionZone();

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Components)
	UBoxComponent* OverlapComp;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UDecalComponent* DecalComponent;
	UPROPERTY(EditDefaultsOnly, Category = Sounds)
	USoundCue* MissionFailureSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
