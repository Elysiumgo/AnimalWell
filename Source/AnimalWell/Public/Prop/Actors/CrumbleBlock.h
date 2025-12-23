// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Actors/BasePropActor.h"
#include "PaperSpriteComponent.h"
#include "CrumbleBlock.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API ACrumbleBlock : public ABasePropActor
{
	GENERATED_BODY()
	
public:
	ACrumbleBlock();

protected:

    //äÖÈ¾×é¼þ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UPaperSpriteComponent* BlockSprite;

    //ÏûÊ§Âß¼­
    void StartCrumbling();

    UFUNCTION()
    void Vanish();

    UFUNCTION()
    void Respawn();


    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

    FTimerHandle CrumbleTimerHandle;



};
