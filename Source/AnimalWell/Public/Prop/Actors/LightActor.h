// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Actors/BasePropActor.h"
#include "LightActor.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API ALightActor : public ABasePropActor
{
	GENERATED_BODY()

	
public:
	
	// Sets default values for this actor's properties
	ALightActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UPaperSpriteComponent* LineSpriteComp;
	class UPaperSpriteComponent* LightSpriteComp;
	FRotator TargetRotator;
	FFloatCurve* MoveCurve;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ActionEvent(FVector BeginLoaction) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	UPROPERTY(EditAnywhere)
	FName MName;

	float CurrentAngle;   
	float CurrentSpeed;    
	float MaxSwingAngle = 30.f;    
    
	float SwingAngle;   
	float SwingSpeed;   
    
	

	
};
