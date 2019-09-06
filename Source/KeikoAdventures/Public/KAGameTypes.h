#pragma once

#include "ObjectAndNameAsStringProxyArchive.h"

struct FKASaveGameArchive : public FObjectAndNameAsStringProxyArchive
{
	FKASaveGameArchive(FArchive& InInnerArchive, bool bInLoadIfFindFails)
		: FObjectAndNameAsStringProxyArchive(InInnerArchive, bInLoadIfFindFails)
	{
		//SetIsSaving(true),
		ArIsSaveGame = true;
	}
};


UENUM(BlueprintType)
enum class ETileType : uint8
{
	TT_Active,
	TT_Inactive,
	TT_Notused
};
