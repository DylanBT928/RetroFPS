// Copyright 2023 Dylan Tran All Rights Reserved.


#include "RetroFPSAttributeSet.h"

URetroFPSAttributeSet::URetroFPSAttributeSet()
{

}

void URetroFPSAttributeSet::PreAttributeChange(const FGameplayAttribute &Attribute, float &NewValue)
{
    NewValue = FMath::Clamp<float>(NewValue, 0, 100);
}

bool URetroFPSAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData &Data)
{
    float AbsoluteMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude);

    if (Data.EvaluatedData.Magnitude > 0)
    {
        if (Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor() + AbsoluteMagnitude >= 100)
        {
            SetArmor(100);
            return false;
        }

        if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() + AbsoluteMagnitude >= 100)
        {
            SetHealth(100);
            return false;
        }
    }
    else
    {
        if (Data.EvaluatedData.Attribute == GetArmorAttribute() && AbsoluteMagnitude > GetArmor())
                Health.SetCurrentValue(Health.GetCurrentValue() - (AbsoluteMagnitude - GetArmor()));
    }

    return true;
}
