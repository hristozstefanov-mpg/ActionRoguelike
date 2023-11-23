#pragma once

#include "CoreMinimal.h"
#include "RGBaseProjectile.h"
#include "RGMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARGMagicProjectile : public ARGBaseProjectile
{
	GENERATED_BODY()

public:

	/** Damage amount dealth to whatever gets hit */
	UPROPERTY(EditAnywhere)
	float DamageAmount = 20.0f;

protected:

	virtual void Explode_Implementation(AActor* HitActor) override;

};