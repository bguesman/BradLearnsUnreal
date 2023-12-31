// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleFog.generated.h"


UCLASS()
class BRADLEARNSUNREAL_API ASimpleFog : public AActor
{
	GENERATED_BODY()
	
public:
  UPROPERTY(EditAnywhere, Category = "Brad Learns Unreal")
  FLinearColor Scattering;
  UPROPERTY(EditAnywhere, Category = "Brad Learns Unreal")
  FLinearColor Extinction;
  UPROPERTY(EditAnywhere, Category = "Brad Learns Unreal")
  float Density;
	UPROPERTY(EditAnywhere, Category = "Brad Learns Unreal")
  float MaxDistance;

public:	
	// Sets default values for this actor's properties
	ASimpleFog();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
