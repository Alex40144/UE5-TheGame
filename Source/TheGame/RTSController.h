// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSController.generated.h"

/**
 * 
 */
UCLASS()
class THEGAME_API ARTSController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	void MoveForward(float dist);
	void MoveRight(float dist);

	void ZoomIn();
	void ZoomOut();

	void RotateCamera(float dist);

	UPROPERTY(EditAnywhere)
	int cameraMoveSpeed = 1200;
	int cameraZoomSpeed = 100;
	int cameraRotationSpeed = 100;
	
};
