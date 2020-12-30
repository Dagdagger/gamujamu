// Fill out your copyright notice in the Description page of Project Settings.


#include "PikminActor.h"

// Sets default values
APikminActor::APikminActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APikminActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APikminActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

