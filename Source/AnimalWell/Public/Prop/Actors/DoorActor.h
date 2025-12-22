// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Actors/BasePropActor.h"
#include "DoorActor.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API ADoorActor : public ABasePropActor
{
	GENERATED_BODY()

	public:
	ADoorActor();


	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
	FVector Ta1Vector;
	UPROPERTY()
	class AToggerActor * TA1;
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
	FVector Ta2Vector;
	UPROPERTY()
	class AToggerActor * TA2;
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
	FVector Ta3Vector;
	UPROPERTY()
	class AToggerActor * TA3;

	class UPaperSpriteComponent * DoorSpriteComp;

	virtual void BeginPlay() override;

	virtual void ActionEvent(FVector BeginLoaction = FVector::ForwardVector * -1) override;
};
