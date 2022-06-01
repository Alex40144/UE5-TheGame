// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDController.generated.h"

/**
 * 
 */
UCLASS()
class THEGAME_API AHUDController : public AHUD
{
	GENERATED_BODY()
public:		
	AHUDController();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};
