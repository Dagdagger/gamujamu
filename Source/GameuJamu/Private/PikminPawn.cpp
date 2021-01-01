// Fill out your copyright notice in the Description page of Project Settings.

#include "PikminPawn.h"
#include "DrawDebugHelpers.h"
#include "PikminMovementComponent.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "../GameuJamuCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
APikminPawn::APikminPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bShooting = false;
	// Create a dummy root component we can attach things to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	RootComponent = CollisionMesh;
	CollisionMesh->SetBoxExtent(FVector(2.0f, 2.0f, 2.0f));
	CollisionMesh->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);
	CollisionMesh->BodyInstance.SetResponseToAllChannels(ECR_Block);
	CollisionMesh->bHiddenInGame = false;

	// Create a Visible Component

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PikminVisibleComponent"));
	// CollisionMesh->SetupAttachment(RootComponent);
	OurVisibleComponent->SetupAttachment(RootComponent);

	



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
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		if ((FVector::Dist(MainPlayerLocation, this->GetActorLocation()) > 300.f) && !bShooting) {
			FVector MovementVector = MainPlayerLocation - this->GetActorLocation();
			MovementVector.Normalize();
			MovementVector = MovementVector * 200;

			OurMovementComponent->AddInputVector(MovementVector);
		}
		else if (bShooting) {

			OurMovementComponent->AddInputVector(ShotVector);
			if (FVector::Dist(this->GetActorLocation(), AimedLocation) < 100.f) {
				bShooting = false;
			}
		}
	}
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
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Shooting!"));
	}


	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Executing movement!"));
		}
		//OurMovementComponent->AddInputVector(GetActorForwardVector() * 1000.0f);
		if (AGameuJamuCharacter* PlayerPawn = Cast<AGameuJamuCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
		{
			if (PlayerPawn->GetCursorToWorld())
			{
				bShooting = true;
				AimedLocation = PlayerPawn->GetCursorToWorld()->GetComponentLocation();

				ShotVector = AimedLocation - this->GetActorLocation();
				ShotVector.Normalize();
				ShotVector = ShotVector * 500.f;

				OurMovementComponent->AddInputVector(ShotVector);
	
			}
		}
	}
}

void APikminPawn::Shoot_YAxis()

{
	// Move at 100 units per second right or left
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Shooting!"));
	}
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * 50.0f);
	}

}

void APikminPawn::StartGrowing()
{
	bGrowing = true;
}




