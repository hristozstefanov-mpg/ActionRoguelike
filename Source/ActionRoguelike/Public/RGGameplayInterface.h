#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RGGameplayInterface.generated.h"

UINTERFACE(MinimalAPI)
class URGGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

class ACTIONROGUELIKE_API IRGGameplayInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);
};
