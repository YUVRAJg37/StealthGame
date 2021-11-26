// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

UCLASS()
class FPSGAME_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Attract();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TArray<UPrimitiveComponent*> OverlappingComponents;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	float Radius;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	float Strength;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* DestroyFX;

};

