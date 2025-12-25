// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/GhostActor.h"

#include "paperflipbookcomponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGhostActor::AGhostActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RenderGhost = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("RenderGhostComp"));
	RenderGhost->SetupAttachment(RootComponent);
	RenderGhost->SetRelativeScale3D(FVector(0.2f));

	
	GhostCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("GhostCollisionComponent");
	GhostCollisionComponent->SetupAttachment(RenderGhost);
	GhostCollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));

	GhostCollisionComponent->SetCapsuleRadius(72.f);
	GhostCollisionComponent->SetCapsuleHalfHeight(144.f);
	GhostCollisionComponent->bHiddenInGame = true;


	MyMovementComponent  = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MyMovementComponent->InitialSpeed = 60.f;
	MyMovementComponent->MaxSpeed = 60.f;

	MyMovementComponent->ProjectileGravityScale = 0.f;
	MyMovementComponent->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void AGhostActor::BeginPlay()
{
	Super::BeginPlay();
	ActionEvent(UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation());
}

// Called every frame
void AGhostActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateGhostState();
}

void AGhostActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	
	if (!GhostFlipbook_Idle)
	{
		GhostFlipbook_Idle = LoadObject<UPaperFlipbook>(this,TEXT("/Script/Paper2D.PaperFlipbook'/Game/Prop/PaperFlipbook/PF_Ghost_Idle.PF_Ghost_Idle'"));
	}
	if (!GhostFlipbook_Walk)
	{
		GhostFlipbook_Walk = LoadObject<UPaperFlipbook>(this,TEXT("/Script/Paper2D.PaperFlipbook'/Game/Prop/PaperFlipbook/PF_Ghost_Walk.PF_Ghost_Walk'"));
	}
	if (!GhostFlipbook_Jump)
	{
		GhostFlipbook_Jump = LoadObject<UPaperFlipbook>(this,TEXT("/Script/Paper2D.PaperFlipbook'/Game/Prop/PaperFlipbook/PF_Ghost_Jump.PF_Ghost_Jump'"));
	}
	if (!GhostFlipbook_Dash)
	{
		GhostFlipbook_Dash = LoadObject<UPaperFlipbook>(this,TEXT("/Script/Paper2D.PaperFlipbook'/Game/Prop/PaperFlipbook/BlueWizardDash.BlueWizardDash'"));
	}


	RenderGhost->SetFlipbook(GhostFlipbook_Idle);
}


void AGhostActor::ChangeGhostState(EGhostState NewGhostState)
{
	CurrentGhostState = NewGhostState;
	RenderGhost->SetFlipbook(GetGhostFlipbook(CurrentGhostState));
}


UPaperFlipbook* AGhostActor::GetGhostFlipbook(EGhostState GhostState)
{
	UPaperFlipbook* TempFlipbook = nullptr;

	switch (GhostState)
	{
		case EGhostState::Idle:
			TempFlipbook = GhostFlipbook_Idle;
			break;
		case EGhostState::Walk:
			TempFlipbook = GhostFlipbook_Walk;
			break;
		case EGhostState::Jump:
			TempFlipbook = GhostFlipbook_Jump;
			break;
		case EGhostState::Dash:
			TempFlipbook = GhostFlipbook_Dash;
			break;
	}
	return TempFlipbook;
}

void AGhostActor::ActionEvent(FVector BeginLoaction)
{
	Super::ActionEvent(BeginLoaction);
	GhostMove(BeginLoaction);
}

void AGhostActor::UpdateTargetLocation()
{
	GhostMove(UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation());
}

void AGhostActor::GhostMove(FVector Destination)
{
	ChangeGhostState(EGhostState::Walk);

	TargetLocation = Destination;

	
	MoveDirection = (Destination.X - GetActorLocation().X) > 0 ? 1 : -1;
	SetActorRotation(FRotator(0.f, (Destination.X - GetActorLocation().X) > 0 ? 0 : 180, 0.f));

	if (MyMovementComponent)
	{
		MyMovementComponent->Activate();
		MyMovementComponent->Velocity = FVector(MoveDirection * 60,0.f,0.f);
	}
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AGhostActor::UpdateTargetLocation,FMath::RandRange(5,10),true);
}

void AGhostActor::UpdateGhostState()
{
	if (CurrentGhostState == EGhostState::Idle)
	{
		return;
	}else if (CurrentGhostState == EGhostState::Walk)
	{
		
		if (FMath::Abs(GetActorLocation().X - TargetLocation.X) < 60.f && FMath::Abs(GetActorLocation().Z - TargetLocation.Z) > 1.f)
		{
			ChangeGhostState(EGhostState::Dash);
		}
	}else if (CurrentGhostState == EGhostState::Dash)
	{
		FVector NewDirection = (TargetLocation - GetActorLocation()).GetSafeNormal();
		
		if ((TargetLocation - GetActorLocation()).Length() < 10.f)
		{
			ChangeGhostState(EGhostState::Walk);
			MyMovementComponent->Velocity = FVector(MoveDirection * 60,0.f,0.f);
			return;
		}
		MyMovementComponent->Velocity = NewDirection * 60.f;
	}
}
