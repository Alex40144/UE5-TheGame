// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSController.h"
#include "Components/InputComponent.h"
#include "RTSCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/Rotator.h"

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

}

void ARTSController::MoveForward(float dist)
{
    FRotator rotation = GetPawn()->GetActorRotation() + FRotator{ -GetPawn()->GetActorRotation().Pitch, 0, 0 };
    GetPawn()->SetActorLocation(GetPawn()->GetActorLocation() + rotation.RotateVector(FVector{ GetWorld()->GetDeltaSeconds() * cameraMoveSpeed * dist, 0, 0 }));
}

void ARTSController::MoveRight(float dist)
{
    FRotator rotation = GetPawn()->GetActorRotation() + FRotator{ -GetPawn()->GetActorRotation().Pitch, 0, 0 };

    GetPawn()->SetActorLocation(GetPawn()->GetActorLocation() + rotation.RotateVector(FVector{ 0, GetWorld()->GetDeltaSeconds() * cameraMoveSpeed * dist, 0 }));

}

void ARTSController::ZoomIn()
{
    ARTSCamera* pawn = Cast<ARTSCamera>(GetPawn());
    pawn->SpringArmComp->TargetArmLength = pawn->SpringArmComp->TargetArmLength - cameraZoomSpeed;
}

void ARTSController::ZoomOut()
{
    ARTSCamera* pawn = Cast<ARTSCamera>(GetPawn());
    pawn->SpringArmComp->TargetArmLength = pawn->SpringArmComp->TargetArmLength + cameraZoomSpeed;
}

void ARTSController::RotateCamera(float dist)
{
    GetPawn()->AddActorWorldRotation({ 0, GetWorld()->GetDeltaSeconds() * cameraRotationSpeed * dist, 0 });
}
