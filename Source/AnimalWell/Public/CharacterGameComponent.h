// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "CharacterGameComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANIMALWELL_API UCharacterGameComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterGameComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveLeftRight(const FInputActionValue& Value);

	void MoveUpAndDown(const FInputActionValue& Value);

	void Jump();

private:
	UPROPERTY(VisibleAnywhere, Category = "MyCharacter|Player")
	class AMyCharacter* CurrentCharacter;
	
	UPROPERTY(VisibleAnywhere, Category = "MyCharacter|Player")
	AActor* Owner;

	bool bJumping;

	bool bOnLadder;

public:
	bool IsJumping() const { return bJumping; }

	void SetJumping(bool bNewJumping) { this->bJumping = bNewJumping; }

	bool IsOnLadder() const { return bOnLadder; }

	void SetOnLadder(bool bNewOnLadder) { this->bOnLadder = bNewOnLadder; }
};
