#include "RGAttributesComponent.h"

URGAttributesComponent::URGAttributesComponent()
{
	Health = 100;
}

bool URGAttributesComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	return true;
}