// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "TextBlock.h"
#include "SoundTestWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDMANAGERTESTPROJ_API USoundTestWidget : public UUserWidget
{
	GENERATED_BODY()

	bool m_bIsMute;

public:
	virtual bool Initialize() override;

	UFUNCTION()
	void OnClickMute();
	UFUNCTION()
	void OnClickStopAll();
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
	UFUNCTION()
	void OnClickEnvPlayBGMType1();
	UFUNCTION()
	void OnClickEnvPlayBGMType2();
	UFUNCTION()
	void OnClickEnvStopBGMType1();
	UFUNCTION()
	void OnClickEnvStopBGMType2();
	UFUNCTION()
	void OnClickEnvStopBGMType1FadeOut();
	UFUNCTION()
	void OnClickEnvStopBGMType2FadeOut();
	UFUNCTION()
	void OnClickEnvPlayBGMType1FadeIn();
	UFUNCTION()
	void OnClickEnvPlayBGMType2FadeIn();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnEnvPlayBGMType1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnEnvPlayBGMType2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnEnvStopBGMType1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnEnvStopBGMType2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnEnvStopBGMType1FadeOut = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnEnvStopBGMType2FadeOut = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnEnvPlayBGMType1FadeIn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnEnvPlayBGMType2FadeIn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnMute = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UTextBlock* txtMute = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	UButton* btnStopAll = nullptr;

};
