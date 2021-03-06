// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Data/NWeaponItem.h"
#include "NAssetManager.h"

UNWeaponItem::UNWeaponItem()
{
    ItemType = UNAssetManager::WeaponItemType;
}


void UNWeaponItem::PostLoad()
{
    Super::PostLoad();

    const FString EnumAsString = EquipmentSocketEnum->GetNameStringByIndex(static_cast<int32>(HolsteredSocket));;
    HolsteredSocketName =  FName(EnumAsString);
}


void UNWeaponItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    
    const FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
    if (PropertyName == GET_MEMBER_NAME_CHECKED(UNWeaponItem, HolsteredSocket) && EquipmentSocketEnum)
    {
        const FString EnumAsString = EquipmentSocketEnum->GetNameStringByIndex(static_cast<int32>(HolsteredSocket));;
        HolsteredSocketName = FName(EnumAsString);
    }
}


void UNWeaponItem::PreSave(const ITargetPlatform* TargetPlatform)
{
    Super::PreSave(TargetPlatform);

    if (!EquippedGameplayTag.IsValid())
    {
        ShowWarning("EquippedGameplayTag not set!");
    }

    if (HolsteredSocket == ENEquipmentSocket::None)
    {
        ShowWarning("HolsteredSocket not set!");
    }
}


FTransform UNWeaponItem::GetHolsteredTransform() const
{
    return FTransform(HolsteredAttachmentOffset.RelativeRotationOffset, HolsteredAttachmentOffset.RelativeLocationOffset);
}
