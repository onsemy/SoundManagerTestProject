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

	SoundManager::GetInstance()->Initialize(GetWorld());
	//for (TActorIterator<AAmbientSound> ActorIter(GetWorld()); ActorIter; ++ActorIter)
	//{
	//	AAmbientSound* Sound = *ActorIter;
	//	//if (Sound->GetAudioComponent()->GetName().Contains(TEXT("bgm_title_01")))
	//	{
	//		for (int i = 0; i < 100; ++i)
	//		{
	//			Sound->Play();
	//			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::White, TEXT("Sound Play!"));
	//		}
	//	}
	//}
	UClass* BPClass = LoadObject<UClass>(GetWorld(), TEXT("WidgetBlueprint'/Game/UI/SoundTestWidget.SoundTestWidget_C'"));
	m_pSoundWidget = CreateWidget<USoundTestWidget>(GetWorld(), BPClass);
	m_pSoundWidget->AddToViewport();
	//m_pSoundWidget->RegisterInputComponent();
}

void ASoundManagerTestProjGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//m_pSoundWidget->UnregisterInputComponent();
	m_pSoundWidget->RemoveFromViewport();
	m_pSoundWidget = nullptr;

	SoundManager::ReleaseInstance();

	Super::EndPlay(EndPlayReason);
}
