// Fill out your copyright notice in the Description page of Project Settings.

#include "PikminPawn.h"
#include "PikminMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
APikminPawn::APikminPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a dummy root component we can attach things to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a Visible Component

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PikminVisibleComponent"));

	OurVisibleComponent->SetupAttachment(RootComponent);

	SetActorEnableCollision(true);
	


	// Create instance of 
	OurMovementComponent = CreateDefaultSubobject<UPikminMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;

}

// Called when the game starts or when spawned
void APikminPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APikminPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector MainPlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector MovementVector =  MainPlayerLocation - this->GetActorLocation();
	MovementVector.Normalize();
	MovementVector = MovementVector * 200;

	OurMovementComponent->AddInputVector(MovementVector);

}

// Called to bind functionality to input
void APikminPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UPawnMovementComponent* APikminPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void APikminPawn::Shoot_XAxis()
{
	// Move at 100 units per second forward or backward

	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * 50.0f);
	}

}

void APikminPawn::Shoot_YAxis()

{
	// Move at 100 units per second right or left

	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * 50.0f);
	}

}

void APikminPawn::StartGrowing()
{
	bGrowing = true;
}




