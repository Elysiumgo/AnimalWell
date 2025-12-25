// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/LightActor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"


ALightActor::ALightActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp0"));
	LineSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LineSpriteComp0"));
	LineSpriteComp->SetupAttachment(RootComponent);
	LightSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LightSpriteComp0"));
	LightSpriteComp->SetupAttachment(LineSpriteComp);
	LineSpriteComp->SetCollisionProfileName(TEXT("Prop"));
	LightSpriteComp->SetCollisionProfileName(TEXT("Prop"));
}

// Called when the game starts or when spawned
void ALightActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SwingSpeed += -SwingAngle * 0.02f;  
	SwingSpeed *= 0.98f;               
	SwingAngle += SwingSpeed * DeltaTime * 60.f;          
    
	
	if (SwingAngle > 30) SwingAngle = 30, SwingSpeed *= -0.7f;
	if (SwingAngle < -30) SwingAngle = -30, SwingSpeed *= -0.7f;
    
	
	SetActorRotation(FRotator(SwingAngle, 0, 0));
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this,AStaticMeshActor::StaticClass(),OutActors);
	for ( auto Mask :OutActors)
	{
		if (AStaticMeshActor* MaskActor = Cast<AStaticMeshActor>(Mask))
		{
			for (auto Tag :MaskActor->Tags)
			{
				if (Tag == "Mask")
				{
					UStaticMeshComponent* MeshComponent = MaskActor->GetStaticMeshComponent();
					FVector LightPosion = LightSpriteComp->GetComponentLocation();
					MeshComponent->SetVectorParameterValueOnMaterials(MName,LightPosion);
				}
			}
		}
	}
}

void ALightActor::ActionEvent(FVector BeginLoaction)
{
	
	if (BeginLoaction.X > GetActorLocation().X)
		SwingSpeed -= 10.0f;  
	else
		SwingSpeed += 10.0f; 
}

void ALightActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UPaperSprite* LineSprite = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_Line.PS_Line'"));
	UPaperSprite* LigthSprite = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_Light.PS_Light'"));
	if (LineSprite && LigthSprite)
	{
		LineSpriteComp->SetSprite(LineSprite);
		LightSpriteComp->SetSprite(LigthSprite);
		LineSpriteComp->SetRelativeLocation(FVector(0, 0, LineSprite->GetSourceSize().Y/-2)) ;
		LightSpriteComp->SetRelativeLocation(FVector(0, 0.1, LineSprite->GetSourceSize().Y/-2)) ;
	}	
}


