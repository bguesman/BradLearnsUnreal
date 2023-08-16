// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneViewHolder.h"

// Sets default values
ASceneViewHolder::ASceneViewHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASceneViewHolder::BeginPlay()
{
	Super::BeginPlay();	
	
}

// Called every frame
void ASceneViewHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_bRegistered)
	{
		this->RedSceneViewExtension = FSceneViewExtensions::NewExtension<FRedSceneViewExtension>();
		m_bRegistered = true;
	}

}

