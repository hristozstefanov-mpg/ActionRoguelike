#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RGTargetDummy.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARGTargetDummy : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	class URGAttributesComponent* AttributesComponent;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComponent;

public:	

	ARGTargetDummy();

protected:
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, class URGAttributesComponent* OwningComponent, float NewHeath, float Delta);

	virtual void PostInitializeComponents() override;
};
