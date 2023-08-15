// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RedSceneViewExtension.h"
#include "SceneViewHolder.generated.h"


UCLASS()
class BRADLEARNSUNREAL_API ASceneViewHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneViewHolder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TSharedPtr<class FRedSceneViewExtension, ESPMode::ThreadSafe> RedSceneViewExtension;
};
