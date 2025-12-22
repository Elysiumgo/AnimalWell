// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Actors/BasePropActor.h"
#include "ToggerActor.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API AToggerActor : public ABasePropActor
{
	GENERATED_BODY()
	bool OpenFlag;
	public:
	AToggerActor();
	bool GetOpenFlag(){ return OpenFlag; };
	void SetOpenFlag(bool InOpenFlag){ OpenFlag = InOpenFlag; };
	virtual void BeginPlay() override;
	class UPaperSpriteComponent *SpriteComp;

	void ActionEvent(FVector BeginLoaction = FVector::ForwardVector * -1) override;
};
