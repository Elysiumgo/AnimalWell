// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuHUD.h"
#include "SMenuWidget.h"
#include "Engine/Engine.h"
#include "Widgets/SWeakWidget.h"
#include "GameFramework/PlayerController.h"

#include "Engine/PostProcessVolume.h"
#include "EngineUtils.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	ShowMenu();
}

void AMenuHUD::ShowMenu()
{
	if (GEngine && GEngine->GameViewport) {
		MenuWidget = SNew(SMenuWidget).OwningHUD(this);	// 传入自身指针
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));

		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	}
}

void AMenuHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && MenuWidgetContainer.IsValid()) {
		GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());			//从视口移除菜单 Slate
		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor = false;		//隐藏鼠标
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}

void AMenuHUD::SetScreenBrightness(float NewBrightness)
{
	CurrentScreenBrightness = NewBrightness;

	UWorld* World = GetWorld();
	if (!World) {
		return;
	}

	//遍历场景中的所有后处理卷并修改 AutoExposureBias（运行时生效）
	for (TActorIterator<APostProcessVolume> It(World); It; ++It)
	{
		APostProcessVolume* PPV = *It;
		if (PPV)
		{
			PPV->Settings.AutoExposureBias = CurrentScreenBrightness;
		}
	}
}