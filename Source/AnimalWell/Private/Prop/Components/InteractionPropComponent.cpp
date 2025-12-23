// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Components/InteractionPropComponent.h"

#include "GameFramework/Character.h"
#include "Prop/Actors/BasePropActor.h"
#include "Prop/Actors/LightActor.h"

// Sets default values for this component's properties
UInteractionPropComponent::UInteractionPropComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionPropComponent::BeginPlay()
{
	Super::BeginPlay();
	CharacterInstance = Cast<ACharacter>(GetOwner());
}


// Called every frame
void UInteractionPropComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TracePropOjb();
	
}

void UInteractionPropComponent::TracePropOjb()
{
	TArray<FHitResult> OutHits;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(CharacterInstance);
	FVector StartLocation = 
		CharacterInstance->GetActorLocation()+CharacterInstance->GetActorUpVector()*35;
	FVector EndLocation = 
		CharacterInstance->GetActorLocation()*20+StartLocation +CharacterInstance->GetActorUpVector()*35;
	GetWorld()->LineTraceMultiByChannel(OutHits,StartLocation,EndLocation,ECollisionChannel::ECC_GameTraceChannel1,Params);
	
	for (FHitResult &HitResult : OutHits)
	{
		if (!HitResult.bBlockingHit) 
			return;
		ALightActor* Light = Cast<ALightActor>(HitResult.GetActor());
		if (Light)
		{
			FVector Location = Light->GetActorLocation()-CharacterInstance->GetActorLocation().Normalize();
			Light->ActionEvent(Location);
		}
	}
}

