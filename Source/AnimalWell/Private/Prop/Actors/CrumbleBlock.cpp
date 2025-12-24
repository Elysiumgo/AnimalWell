// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/CrumbleBlock.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"  
#include "Engine/World.h"

ACrumbleBlock::ACrumbleBlock() {
    BlockSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BlockSprite"));

    if (CollisionBox) {
        BlockSprite->SetupAttachment(CollisionBox);
        CollisionBox->SetCollisionProfileName(TEXT("BlockAll"));
        CollisionBox->SetNotifyRigidBodyCollision(true);

        //绑定重叠事件
        CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACrumbleBlock::OnOverlapBegin);
    }

}

void ACrumbleBlock::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

    // 只要撞到的是玩家（Pawn），就触发
    if (Other && Other->IsA(APawn::StaticClass()))
    {
        //if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Hit Success!"));
        StartCrumbling();
    }
}



void ACrumbleBlock::StartCrumbling()
{
    //定时器启动
    if (!GetWorldTimerManager().IsTimerActive(CrumbleTimerHandle))
    {
        //3秒后消失
        GetWorld()->GetTimerManager().SetTimer(CrumbleTimerHandle, this, &ACrumbleBlock::Vanish, 3.0f, false);

        //改变颜色，提示玩家快塌了
        if (BlockSprite) {
            BlockSprite->SetSpriteColor(FLinearColor::Red);
        }
    }
}


void ACrumbleBlock::Vanish()
{
    //隐藏渲染
    SetActorHiddenInGame(true);
    //禁用碰撞，这样玩家就掉下去了
    SetActorEnableCollision(false);

    //过一会再刷出来
    GetWorld()->GetTimerManager().SetTimer(CrumbleTimerHandle, this, &ACrumbleBlock::Respawn, 5.0f, false);
}


void ACrumbleBlock::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(APawn::StaticClass()))
    {
        StartCrumbling();
    }
}

void ACrumbleBlock::Respawn()
{
    //恢复渲染和碰撞
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);

    // 恢复正常颜色
    if (BlockSprite){
        BlockSprite->SetSpriteColor(FLinearColor::White);
    }

    //清除定时器
    GetWorld()->GetTimerManager().ClearTimer(CrumbleTimerHandle);
}