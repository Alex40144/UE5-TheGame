// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDController.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "RTSController.h"

AHUDController::AHUDController()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/UI_Textures/crosshair.crosshair"));
	CrosshairTex = CrosshairTexObj.Object;

}

void AHUDController::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition((Center.X - 15),
										  (Center.Y - 15));

	// draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	TileItem.Size = FVector2D(30, 30);

	ARTSController* playerController = Cast<ARTSController>(GetWorld()->GetFirstPlayerController());
	if (!playerController->bCameraRTSMode)
	{
		Canvas->DrawItem(TileItem);
	}
};

void AHUDController::BeginPlay()
{
	Super::BeginPlay();

}