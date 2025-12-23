// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentActorInteraction.h"
#include "Kismet/GameplayStatics.h"
#include "PaperSpriteComponent.h"
#include "MyCharacter.h"

// Sets default values
AParentActorInteraction::AParentActorInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("sprite"));	//创建纸精灵组件
	RootComponent = PaperSprite;	//设置为根组件

}

// Called when the game starts or when spawned
void AParentActorInteraction::BeginPlay()
{
	Super::BeginPlay();
	//获取玩家角色
	AController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//确保控制器有效
	if (PlayerController) {
		APawn* CurrentCharacter = PlayerController->GetPawn();
		PlayerCharacter = Cast<AMyCharacter>(CurrentCharacter);
	}
}

// Called every frame
void AParentActorInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

