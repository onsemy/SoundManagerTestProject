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
	void OnClickPlayEffectType2();
	UFUNCTION()
	void OnClickPlayEffect100();
	UFUNCTION()
	void OnClickPlayBGMType1();
	UFUNCTION()
	void OnClickPlayBGMType2();
	UFUNCTION()
	void OnClickStopBGMType1();
	UFUNCTION()
	void OnClickStopBGMType2();
	UFUNCTION()
	void OnClickStopBGMType1FadeOut();
	UFUNCTION()
	void OnClickStopBGMType2FadeOut();
	UFUNCTION()
	void OnClickPlayBGMType1FadeIn();
	UFUNCTION()
	void OnClickPlayBGMType2FadeIn();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnPlayEffect1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnPlayEffectType2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnPlayEffect100 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnPlayBGMType1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnPlayBGMType2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnStopBGMType1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnStopBGMType2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnStopBGMType1FadeOut = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnStopBGMType2FadeOut = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnPlayBGMType1FadeIn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnPlayBGMType2FadeIn = nullptr;

};
