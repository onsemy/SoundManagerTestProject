// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundManagerTestProjGameModeBase.h"
#include "EngineUtils.h"
#include "Sound/AmbientSound.h"
#include "Components/AudioComponent.h"
#include "SoundManager.h"
#include "UI/SoundTestWidget.h"

void ASoundManagerTestProjGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SoundManager::GetInstance()->Initialize(
		GetWorld(),
		TEXT("SoundClass'/Engine/EngineSounds/Music.Music'"),
		TEXT("SoundClass'/Engine/EngineSounds/SFX.SFX'"),
		TEXT("SoundConcurrency'/Game/Sound/BGMConcurrency.BGMConcurrency'"),
		TEXT("SoundConcurrency'/Game/Sound/NewSoundConcurrency.NewSoundConcurrency'"),
		2);

	// NOTE(JJO): For test
	UClass* BPClass = LoadObject<UClass>(GetWorld(), TEXT("WidgetBlueprint'/Game/UI/SoundTestWidget.SoundTestWidget_C'"));
	m_pSoundWidget = CreateWidget<USoundTestWidget>(GetWorld(), BPClass);
	m_pSoundWidget->AddToViewport();
}

void ASoundManagerTestProjGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	m_pSoundWidget->RemoveFromViewport();
	m_pSoundWidget = nullptr;

	SoundManager::ReleaseInstance();

	GEngine->ForceGarbageCollection(true);

	Super::EndPlay(EndPlayReason);
}
