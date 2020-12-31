// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PikminMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PikminPawn.generated.h"

UCLASS()
class GAMEUJAMU_API APikminPawn : public APawn
{
	GENERATED_BODY()

		
		
		void Shoot_XAxis();
		void Shoot_YAxis();
		void StartGrowing();
		void StopGrowing();

		//Input Variables
		FVector CurrentVelocity;
		bool bGrowing;
	

public:
	// Sets default values for this pawn's properties
	APikminPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere)
	class UPikminMovementComponent* OurMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;



};

