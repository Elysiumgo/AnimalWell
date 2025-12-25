// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePropActor.h"
#include "PaperFlipbook.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GhostActor.generated.h"

UENUM()
enum class EGhostState : uint8
{
	Idle,
	Walk,
	Jump,
	Dash
};

UCLASS()
class ANIMALWELL_API AGhostActor : public ABasePropActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGhostActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* RenderGhost;

	UPROPERTY(EditAnywhere,Category = "Ghost|Animation")
	UPaperFlipbook* GhostFlipbook_Idle;
	UPROPERTY(EditAnywhere,Category = "Ghost|Animation")
	UPaperFlipbook* GhostFlipbook_Walk;
	UPROPERTY(EditAnywhere,Category = "Ghost|Animation")
	UPaperFlipbook* GhostFlipbook_Jump;
	UPROPERTY(EditAnywhere,Category = "Ghost|Animation")
	UPaperFlipbook* GhostFlipbook_Dash;


	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* GhostCollisionComponent;


	UPROPERTY(EditAnywhere)
	TObjectPtr<UProjectileMovementComponent> MyMovementComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;


	UPROPERTY()
	EGhostState CurrentGhostState;

	void ChangeGhostState(EGhostState NewGhostState);
	UPaperFlipbook* GetGhostFlipbook(EGhostState GhostState);



	virtual void ActionEvent(FVector BeginLoaction = FVector::ForwardVector * -1) override;

	UFUNCTION()
	void UpdateTargetLocation();

	void GhostMove(FVector Destination);
	UPROPERTY()
	int32 MoveDirection;

	UPROPERTY()
	FVector TargetLocation;
	void UpdateGhostState();
};
