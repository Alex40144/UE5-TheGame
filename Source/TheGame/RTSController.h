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
protected:
	virtual void BeginPlay() override;
public:
	virtual void SetupInputComponent() override;

	void MoveForward(float dist);
	void MoveRight(float dist);

	void ZoomIn();
	void ZoomOut();

	void RotateCamera(float dist);

	void RotateCameraLR(float dist);
	void RotateCameraUD(float dist);

	void SwitchCameraMode();
	void Jump();


	int cameraMoveSpeed = 1200;
	int cameraRotationSpeed = 150;

	int cameraZoomDist = 100;

	int maxZoom = 3000;
	int minZoom = 700;

	int maxPitch = -15;
	int minPitch = -60;
	

	bool bCameraRTSMode = true;
	
	UPROPERTY()
	class AFPSCamera* FPSCamera;

	UPROPERTY()
	class ARTSCamera* RTSCamera;
};
