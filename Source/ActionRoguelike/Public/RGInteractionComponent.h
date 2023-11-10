#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RGInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API URGInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URGInteractionComponent();	
	
	virtual void PrimaryInteract();

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
};
