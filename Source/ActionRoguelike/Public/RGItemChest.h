#pragma once

#include "CoreMinimal.h"
#include "RGGameplayInterface.h"
#include "RGItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARGItemChest : public AActor, public IRGGameplayInterface
{
	GENERATED_BODY()

protected:

	/** Static mesh of the chest base. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent*	BaseMesh;

	/** Static mesh of the chest lid. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* LidMesh;

	/** The rotation pitch of the lid when it is open. */
	UPROPERTY(EditAnywhere)
	float TargetPitch = 110.0f;

public:

	ARGItemChest();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};