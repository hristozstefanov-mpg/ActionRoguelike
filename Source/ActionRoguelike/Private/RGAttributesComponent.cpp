#include "RGAttributesComponent.h"

URGAttributesComponent::URGAttributesComponent()
{
	Health = 100;
}

bool URGAttributesComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}