// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/BasePropActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"

// Sets default values
ABasePropActor::ABasePropActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	
	CollisionBox->SetCollisionProfileName(TEXT("Prop"));

	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABasePropActor::OnOverlapBegin);



}

// Called when the game starts or when spawned
void ABasePropActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePropActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABasePropActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor && (OtherActor != this))
	{
	
		APawn* PawnActor = Cast<APawn>(OtherActor);
		if (PawnActor)
		{
			ActionEvent(PawnActor->GetActorLocation());
		}
	}
}



void ABasePropActor::ActionEvent(FVector BeginLoaction)
{
}

