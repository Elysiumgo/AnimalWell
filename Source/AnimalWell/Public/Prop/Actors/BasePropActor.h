// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BasePropActor.generated.h"


UCLASS()
class ANIMALWELL_API ABasePropActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePropActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//添加碰撞盒组件，在蓝图里可见
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Prop")
	UBoxComponent* CollisionBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	virtual void ActionEvent(FVector BeginLoaction = FVector::ForwardVector*-1);
};
