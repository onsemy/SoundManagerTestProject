// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/SoundTestWidget.h"
#include "SoundManagerTestProjGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDMANAGERTESTPROJ_API ASoundManagerTestProjGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	TWeakObjectPtr<USoundTestWidget> m_pSoundWidget;
	
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	
};
