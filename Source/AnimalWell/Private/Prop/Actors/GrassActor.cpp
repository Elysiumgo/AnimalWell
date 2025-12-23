// Fill out your copyright notice in the Description page of Project Settings.

#include "Prop/Actors/GrassActor.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/BoxComponent.h"

AGrassActor::AGrassActor()
{
	GrassFlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("GrassFlipbookComp"));

	//挂到父类的碰撞盒上
	if (CollisionBox) {
		GrassFlipbookComp->SetupAttachment(CollisionBox);
	}

	//静止帧设置
	GrassFlipbookComp->SetComponentTickEnabled(true); // 确保它能更新动画
	GrassFlipbookComp->bAutoActivate = false;         // 关键：不自动激活
	GrassFlipbookComp->Stop();                        // 初始状态停止

}

void AGrassActor::BeginPlay()
{
	Super::BeginPlay();

	if (GrassFlipbookComp)
	{
		GrassFlipbookComp->Stop(); // 确保开局不播放
		GrassFlipbookComp->SetPlaybackPositionInFrames(0, false); // 停在第一帧（静止帧）
	}
}


void AGrassActor::ActionEvent(FVector BeginLoaction)
{
	//触发动画
	if (SwayAnimation && GrassFlipbookComp) {
		GrassFlipbookComp->Activate(true);
		GrassFlipbookComp->SetFlipbook(SwayAnimation);
		GrassFlipbookComp->SetLooping(true); 
		GrassFlipbookComp->PlayFromStart();

		//0.5秒后停止
		FTimerHandle GrassHandle;
		GetWorld()->GetTimerManager().SetTimer(GrassHandle, this, &AGrassActor::StopFlut, 0.5f, false);
	}
	//else {
		//调试
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Animation Missing"));
	//}
}



void AGrassActor::StopFlut()
{
	if (GrassFlipbookComp) {
		GrassFlipbookComp->Stop();
		//停止后设置回静止状态
		GrassFlipbookComp->SetPlaybackPositionInFrames(0, false);
	}
}
