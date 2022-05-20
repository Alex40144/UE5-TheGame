// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSController.h"
#include "Components/InputComponent.h"
#include "RTSCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/Rotator.h"
#include "FPSCamera.h"

void ARTSController::SetupInputComponent()
{
    // Always call this.
    Super::SetupInputComponent();
    check(InputComponent);
    // This is initialized on startup, you can go straight to binding
    InputComponent->BindAxis("MoveForward", this, &ARTSController::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &ARTSController::MoveRight);

    InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ARTSController::ZoomIn);
    InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ARTSController::ZoomOut);

    InputComponent->BindAxis("RotateCamera", this, &ARTSController::RotateCamera);

    InputComponent->BindAxis("RotateCameraLR", this, &ARTSController::RotateCameraLR);
    InputComponent->BindAxis("RotateCameraUD", this, &ARTSController::RotateCameraUD);

    InputComponent->BindAction("SwitchCameraMode", IE_Pressed, this, &ARTSController::SwitchCameraMode);
    InputComponent->BindAction("Jump", IE_Pressed, this, &ARTSController::Jump);



}

void ARTSController::BeginPlay()
{
    Super::BeginPlay();
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    RTSCamera = Cast<ARTSCamera>(GetPawn());

    FPSCamera = Cast<AFPSCamera>(GetWorld()->SpawnActor(AFPSCamera::StaticClass())); //create FPScamera
}

void ARTSController::MoveForward(float dist)
{
    if (bCameraRTSMode)
    {
        FRotator rotation = GetPawn()->GetActorRotation() + FRotator{ -GetPawn()->GetActorRotation().Pitch, 0, 0 };
        GetPawn()->SetActorLocation(GetPawn()->GetActorLocation() + rotation.RotateVector(FVector{ GetWorld()->GetDeltaSeconds() * cameraMoveSpeed * dist, 0, 0 }));
    }
    else
    {
        GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), GetWorld()->GetDeltaSeconds() * cameraMoveSpeed * dist);
    }
}


void ARTSController::MoveRight(float dist)
{
    if (bCameraRTSMode)
    {
        FRotator rotation = GetPawn()->GetActorRotation() + FRotator{ -GetPawn()->GetActorRotation().Pitch, 0, 0 };

        GetPawn()->SetActorLocation(GetPawn()->GetActorLocation() + rotation.RotateVector(FVector{ 0, GetWorld()->GetDeltaSeconds() * cameraMoveSpeed * dist, 0 }));
    }
    else
    {
        GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), GetWorld()->GetDeltaSeconds() * cameraMoveSpeed * dist);
    }
}

void ARTSController::ZoomIn()
{
    if (bCameraRTSMode)
    {
        int targetLength = RTSCamera->SpringArmComp->TargetArmLength - cameraZoomDist;
        if (targetLength < minZoom)
        {
            targetLength = minZoom;
        }
        RTSCamera->SpringArmComp->TargetArmLength = targetLength;
    }
}

void ARTSController::ZoomOut()
{
    if (bCameraRTSMode)
    {
        int targetLength = RTSCamera->SpringArmComp->TargetArmLength + cameraZoomDist;
        if (targetLength > maxZoom)
        {
            targetLength = maxZoom;
        }
        RTSCamera->SpringArmComp->TargetArmLength = targetLength;
    }
}

void ARTSController::RotateCamera(float dist)
{
    if (bCameraRTSMode)
    {
        GetPawn()->AddActorWorldRotation({ 0, GetWorld()->GetDeltaSeconds() * cameraRotationSpeed * dist, 0 });
    }
}

void ARTSController::RotateCameraLR(float dist)
{
    if (IsInputKeyDown(EKeys::RightMouseButton) && bCameraRTSMode)
    {
        GetPawn()->AddActorWorldRotation({ 0, GetWorld()->GetDeltaSeconds() * cameraRotationSpeed * dist, 0 });
    }
    if (!bCameraRTSMode)
    {
        FPSCamera->AddControllerYawInput(GetWorld()->GetDeltaSeconds() * cameraRotationSpeed * dist);

    }
}

void ARTSController::RotateCameraUD(float dist)
{
    if (IsInputKeyDown(EKeys::RightMouseButton) && bCameraRTSMode)
    {
        double desiredPitch = GetWorld()->GetDeltaSeconds() * cameraRotationSpeed * dist;
        double currentPitch = RTSCamera->SpringArmComp->GetRelativeRotation().Pitch;
        double targetPitch = desiredPitch + currentPitch;
        if (targetPitch > maxPitch)
        {
            targetPitch = maxPitch;
        }
        else if (targetPitch < minPitch)
        {
            targetPitch = minPitch;
        }
        RTSCamera->SpringArmComp->AddLocalRotation({ targetPitch - currentPitch, 0, 0 });
    }
    if (!bCameraRTSMode)
    {
        FPSCamera->AddControllerPitchInput(GetWorld()->GetDeltaSeconds() * cameraRotationSpeed * -dist);
    }
}


void ARTSController::SwitchCameraMode()
{
    UE_LOG(LogTemp, Warning, TEXT("Switch camera"));
    if (bCameraRTSMode)
    {
        UE_LOG(LogTemp, Warning, TEXT("Posess FPS"));
        FPSCamera->SetActorLocation(RTSCamera->GetActorLocation());
        Possess(FPSCamera);
        this->bShowMouseCursor = false;
        FPSCamera->EnableInput(this);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Posess RTS"));
        RTSCamera->SetActorLocation(FPSCamera->GetActorLocation());
        Possess(RTSCamera);
        bShowMouseCursor = true;
    }
    bCameraRTSMode = !bCameraRTSMode;
}

void ARTSController::Jump()
{
    if (!bCameraRTSMode)
    {
        FPSCamera->Jump();
    }
}