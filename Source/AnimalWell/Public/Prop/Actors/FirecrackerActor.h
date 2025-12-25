// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePropActor.h"
#include "PaperFlipbook.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "FirecrackerActor.generated.h"

UCLASS()
class ANIMALWELL_API AFirecrackerActor : public ABasePropActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFirecrackerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* FirecrackerSpriteComp;
	UPROPERTY(EditAnywhere)
	class UPaperSprite* FirecrackerSprite;
	
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* FirecrackerCollisionComponent;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UProjectileMovementComponent> MyProjectileMovementComp;
	UPROPERTY(EditAnywhere)
	TObjectPtr<URotatingMovementComponent> MyRotatingMovementComp;

	UPROPERTY()
	FTimerHandle CrackerHandle;

	void DestroyFirecracker();

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	
	virtual void ActionEvent(FVector BeginLoaction = FVector::ForwardVector * -1) override;
	
};
