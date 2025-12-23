// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LadderInteraction.generated.h"

UCLASS()
class ANIMALWELL_API ALadderInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALadderInteraction();

private:

	UPROPERTY(VisibleAnywhere, Category = "MyCharacter|Interaction")
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, Category = "MyCharacter")
	class AMyCharacter* PlayerCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MyCharacter")
	void BoxBeginOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "MyCharacter")
	void BoxEndOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
