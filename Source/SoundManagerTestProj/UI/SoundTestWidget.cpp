// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundTestWidget.h"
#include "SoundManager.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, text)

bool USoundTestWidget::Initialize()
{
	if (Super::Initialize())
	{
		if (btnPlayEffect1) btnPlayEffect1->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickPlayEffect1);
		if (btnPlayEffect100) btnPlayEffect100->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickPlayEffect100);
		if (btnPlayBGMType1) btnPlayBGMType1->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickPlayBGMType1);
		if (btnPlayBGMType2) btnPlayBGMType2->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickPlayBGMType2);

		return true;
	}

	return false;
}

void USoundTestWidget::OnClickPlayEffect1()
{
	print(TEXT("OnClickPlayEffect1"));
	SoundManager::GetInstance()->PlayEffect();
}

void USoundTestWidget::OnClickPlayEffect100()
{
	print(TEXT("OnClickPlayEffect100"));
	for (int i = 0; i < 100; ++i)
	{
		SoundManager::GetInstance()->PlayEffect();
	}
}

void USoundTestWidget::OnClickPlayBGMType1()
{
	print(TEXT("OnClickPlayBGMType1"));
	SoundManager::GetInstance()->PlayBGM(TEXT("SoundWave'/Game/Sound/bgm_title_01.bgm_title_01'"));
}

void USoundTestWidget::OnClickPlayBGMType2()
{
	print(TEXT("OnClickPlayBGMType2"));
	SoundManager::GetInstance()->PlayBGM(TEXT("SoundWave'/Engine/EngineSounds/WhiteNoise.WhiteNoise'"));
}

#undef print