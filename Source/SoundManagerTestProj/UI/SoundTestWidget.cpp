// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundTestWidget.h"
#include "SoundManager.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, text)

bool USoundTestWidget::Initialize()
{
	if (Super::Initialize())
	{
		if (btnPlayEffect1) btnPlayEffect1->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickPlayEffect1);
		if (btnPlayEffectType2) btnPlayEffectType2->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickPlayEffectType2);
		if (btnPlayEffect100) btnPlayEffect100->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickPlayEffect100);
		if (btnPlayBGMType1) btnPlayBGMType1->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickPlayBGMType1);
		if (btnPlayBGMType2) btnPlayBGMType2->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickPlayBGMType2);
		if (btnStopBGMType1) btnStopBGMType1->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickStopBGMType1);
		if (btnStopBGMType2) btnStopBGMType2->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickStopBGMType2);
		if (btnStopBGMType1FadeOut) btnStopBGMType1FadeOut->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickStopBGMType1FadeOut);
		if (btnStopBGMType2FadeOut) btnStopBGMType2FadeOut->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickStopBGMType2FadeOut);
		if (btnPlayBGMType1FadeIn) btnPlayBGMType1FadeIn->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickPlayBGMType1FadeIn);
		if (btnPlayBGMType2FadeIn) btnPlayBGMType2FadeIn->OnClicked.AddDynamic(this, &USoundTestWidget::OnClickPlayBGMType2FadeIn);

		return true;
	}

	return false;
}

void USoundTestWidget::OnClickPlayEffect1()
{
	print(TEXT("OnClickPlayEffect1"));
	SoundManager::GetInstance()->PlayEffect(TEXT("SoundWave'/Engine/EngineSounds/WhiteNoise.WhiteNoise'"));
}

void USoundTestWidget::OnClickPlayEffectType2()
{
	print(TEXT("OnClickPlayEffectType2"));
	SoundManager::GetInstance()->PlayEffect(TEXT("SoundWave'/Game/Sound/VR_object_grabbed_loop1.VR_object_grabbed_loop1'"));
}

void USoundTestWidget::OnClickPlayEffect100()
{
	print(TEXT("OnClickPlayEffect100"));
	for (int i = 0; i < 100; ++i)
	{
		SoundManager::GetInstance()->PlayEffect(TEXT("SoundWave'/Engine/EngineSounds/WhiteNoise.WhiteNoise'"));
	}
}

void USoundTestWidget::OnClickPlayBGMType1()
{
	print(TEXT("OnClickPlayBGMType1"));
	SoundManager::GetInstance()->PlayBGM(0, TEXT("SoundWave'/Game/Sound/VR_object_grabbed_loop1.VR_object_grabbed_loop1'"));
}

void USoundTestWidget::OnClickPlayBGMType2()
{
	print(TEXT("OnClickPlayBGMType2"));
	SoundManager::GetInstance()->PlayBGM(1, TEXT("SoundWave'/Game/Sound/VR_WorldMoveLoop_03.VR_WorldMoveLoop_03'"));
}

void USoundTestWidget::OnClickStopBGMType1()
{
	SoundManager::GetInstance()->StopBGM(0);
}

void USoundTestWidget::OnClickStopBGMType2()
{
	SoundManager::GetInstance()->StopBGM(1);
}

void USoundTestWidget::OnClickStopBGMType1FadeOut()
{
	SoundManager::GetInstance()->StopBGM(0, true);
}

void USoundTestWidget::OnClickStopBGMType2FadeOut()
{
	SoundManager::GetInstance()->StopBGM(1, true);
}

void USoundTestWidget::OnClickPlayBGMType1FadeIn()
{
	print(TEXT("OnClickPlayBGMType1FadeIn"));
	//SoundManager::GetInstance()->StopBGM(1, true);
	SoundManager::GetInstance()->PlayBGM(0, TEXT("SoundWave'/Game/Sound/VR_object_grabbed_loop1.VR_object_grabbed_loop1'"), true);
}

void USoundTestWidget::OnClickPlayBGMType2FadeIn()
{
	print(TEXT("OnClickPlayBGMType2FadeIn"));
	//SoundManager::GetInstance()->StopBGM(2, true);
	SoundManager::GetInstance()->PlayBGM(1, TEXT("SoundWave'/Game/Sound/VR_WorldMoveLoop_03.VR_WorldMoveLoop_03'"), true);
}

#undef print