// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickableComponent.h"
#include "Components/InputComponent.h"


// Sets default values for this component's properties
UClickableComponent::UClickableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClickableComponent::BeginPlay()
{
	Super::BeginPlay();

	mesh = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	mesh->OnClicked.AddDynamic(this, &UClickableComponent::OnClicked);

	mesh->OnBeginCursorOver.AddDynamic(this, &UClickableComponent::OnBeginCursorOver);

	mesh->OnEndCursorOver.AddDynamic(this, &UClickableComponent::OnEndCursorOver);
}


// Called every frame
void UClickableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UClickableComponent::OnClicked(UPrimitiveComponent* a, FKey b)
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked"));
	if (mesh->IsValidLowLevel())
	{
		bClicked = !bClicked;
	}

}

void UClickableComponent::OnBeginCursorOver(UPrimitiveComponent* a)
{
	UE_LOG(LogTemp, Warning, TEXT("hover"));
	if (mesh->IsValidLowLevel())
	{
		bHovered = true;
		mesh->SetRenderCustomDepth(true);
	}
}

void UClickableComponent::OnEndCursorOver(UPrimitiveComponent* a)
{
	if (mesh->IsValidLowLevel())
	{
		bHovered = false;
		mesh->SetRenderCustomDepth(false);

	}
}

