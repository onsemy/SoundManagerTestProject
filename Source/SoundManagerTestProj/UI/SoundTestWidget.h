// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "SoundTestWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDMANAGERTESTPROJ_API USoundTestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	UFUNCTION()
	void OnClickPlayEffect1();
	UFUNCTION()
	void OnClickPlayEffect100();
	UFUNCTION()
	void OnClickPlayBGMType1();
	UFUNCTION()
	void OnClickPlayBGMType2();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnPlayEffect1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnPlayEffect100 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnPlayBGMType1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnPlayBGMType2 = nullptr;

};
