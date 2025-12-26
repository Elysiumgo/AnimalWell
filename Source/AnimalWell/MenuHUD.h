// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BloodHUD.h" //继承自血量 HUD
#include "MenuHUD.generated.h"

/**
 * 菜单 HUD，现在继承自 ABloodHUD，这样同一 HUD 实例可以同时负责血量绘制和菜单 Slate
 */
UCLASS()
class ANIMALWELL_API AMenuHUD : public ABloodHUD
{
	GENERATED_BODY()
	
protected:
	//使用 SWeakWidget 容器承载菜单 Slate
	TSharedPtr<class SWeakWidget> MenuWidgetContainer;
	TSharedPtr<class SMenuWidget> MenuWidget;

	virtual void BeginPlay() override;

public:
	void ShowMenu();
	void RemoveMenu();

	//设置并应用画面亮度
	void SetScreenBrightness(float NewBrightness);

	//供 SMenuWidget 读取当前亮度
	float GetCurrentScreenBrightness() const { return CurrentScreenBrightness; }

private:
	//当前存储的亮度值，默认 1.0
	float CurrentScreenBrightness = 1.0f;
};
