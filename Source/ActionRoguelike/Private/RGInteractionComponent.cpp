#include "RGInteractionComponent.h"
#include "RGGameplayInterface.h"


URGInteractionComponent::URGInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URGInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URGInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void URGInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	APawn* MyOwner = GetOwner<APawn>();
	if (!ensureMsgf(MyOwner, TEXT("URGInteractionComponent must only be attached to a Pawn")))
	{
		return;
	}

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	float Radius = 30.0f;

	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	TArray<FHitResult> Hits;
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);	

	for (FHitResult Hit : Hits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor->Implements<URGGameplayInterface>())
			{
				IRGGameplayInterface::Execute_Interact(HitActor, MyOwner);
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 16, FColor::Green, false, 2.0f);
				break;
			}
		}

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 16, FColor::Yellow, false, 2.0f);
	}
	
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}