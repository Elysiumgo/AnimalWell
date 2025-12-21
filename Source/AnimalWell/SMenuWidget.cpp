// Fill out your copyright notice in the Description page of Project Settings.

//UI界面实现
#include "SMenuWidget.h"
#include "MenuHUD.h"
#include "GameFramework/PlayerController.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SMenuWidget::Construct(const FArguments& InArgs)
{
	bCanChildrenBeAccessible = true;	//允许子控件被辅助功能访问

	OwningHUD = InArgs._OwningHUD;	//存储传进来的AMenuHUD指针

	const FMargin ContentPadding = FMargin(500.0f, 300.0f);	//按钮内容边距
	const FMargin ButtonPadding = FMargin(10.0f);		//按钮间距

	const FText TitleText = LOCTEXT("GameTitle", "Animal Well");	//标题文本，LOCTEXT便于本地化
	const FText PlayText = LOCTEXT("PlayGame", "Play");				//开始
	const FText SettingsText = LOCTEXT("Settings", "Settings");		//设置
	const FText QuitText = LOCTEXT("QuitGame", "Quit Game");		//退出

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");	//文本字体
	ButtonTextStyle.Size = 40.0f;	//文本字体大小
	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.0f;	//标题字体大小

	ChildSlot
		[
			SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
						.ColorAndOpacity(FColor::Black)		//纯黑背景
				]
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(ContentPadding)
				[
					SNew(SVerticalBox)
						//标题
						+ SVerticalBox::Slot()
						[
							SNew(STextBlock)
								.Font(TitleTextStyle)
								.Text(TitleText)
								.Justification(ETextJustify::Center)	//中心对齐
						]

						//开始游戏按钮
						+ SVerticalBox::Slot()
						.Padding(ButtonPadding)
						[
							SNew(SButton)
								.OnClicked(this, &SMenuWidget::OnPlayClicked)	//绑定点击事件
							[
								SNew(STextBlock)
									.Font(ButtonTextStyle)
									.Text(PlayText)
									.Justification(ETextJustify::Center)
							]
						]
						//设置按钮
						+ SVerticalBox::Slot()
						.Padding(ButtonPadding)
						[
							SNew(SButton)
							[
								SNew(STextBlock)
									.Font(ButtonTextStyle)
									.Text(SettingsText)
									.Justification(ETextJustify::Center)
							]
						]
						//退出游戏按钮
						+ SVerticalBox::Slot()
						.Padding(ButtonPadding)
						[
							SNew(SButton)
								.OnClicked(this, &SMenuWidget::OnQuitClicked)	//绑定点击事件
							[
								SNew(STextBlock)
									.Font(ButtonTextStyle)
									.Text(QuitText)
									.Justification(ETextJustify::Center)
							]
						]
				]
		];
}

FReply SMenuWidget::OnPlayClicked()	const
{
	if (OwningHUD.IsValid()) {
		OwningHUD->RemoveMenu();	//调用HUD里的移除菜单函数
	}

	return FReply::Handled();	//返回已处理
}

FReply SMenuWidget::OnQuitClicked() const
{
	if (OwningHUD.IsValid()) {
		if (APlayerController* PC = OwningHUD->PlayerOwner) {
			PC->ConsoleCommand("quit");	//执行退出命令
		}
	}
	return FReply::Handled();	//返回已处理
}

#undef LOCTEXT_NAMESPACE