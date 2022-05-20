// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCamera.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFPSCamera::AFPSCamera()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(GetRootComponent());
	CameraComp->AddRelativeLocation({ 0,0,60 });
	CameraComp->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AFPSCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

