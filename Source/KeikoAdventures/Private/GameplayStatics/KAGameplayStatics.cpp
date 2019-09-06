// Fill out your copyright notice in the Description page of Project Settings.

#include "KAGameplayStatics.h"
#include "KAGameTypes.h"
#include "Runtime/Core/Public/Serialization/MemoryReader.h"
#include "Runtime/Core/Public/Serialization/MemoryWriter.h"
#include "Runtime/Core/Public/Serialization/LargeMemoryWriter.h"
#include "Runtime/Core/Public/Serialization/LargeMemoryReader.h"
#include "Runtime/Core/Public/Serialization/Archive.h"


DEFINE_LOG_CATEGORY(KAGameplayStaticsLog)

TArray<uint8> UKAGameplayStatics::ObjectSaver(UObject * SaveObject)
{
	TArray<uint8> ObjectData;
	if (SaveObject == nullptr) return ObjectData;


	FMemoryWriter MemoryWriter(ObjectData, true);
	// use a wrapper archive that converts FNames and UObject*'s to strings that can be read back in
	FKASaveGameArchive SaveGameArchive(MemoryWriter, false);
	// serialize the object
	SaveObject->SerializeScriptProperties(SaveGameArchive);
	SaveObject->Serialize(SaveGameArchive);

	return ObjectData;
}

void UKAGameplayStatics::ObjectLoader(UObject * LoadObject, TArray<uint8> ObjectData)
{
	if (ObjectData.Num() <= 0) return;
	//TODO how to check if valid binary?

	FMemoryReader MemoryReader(ObjectData, true);
	FKASaveGameArchive LoadGameArchive(MemoryReader, true);
	LoadObject->Serialize(LoadGameArchive);
	LoadObject->SerializeScriptProperties(LoadGameArchive);
}

TArray<uint8> UKAGameplayStatics::ActortSaver(AActor * SaveActor)
{
	TArray<uint8> ActorData;
	if (SaveActor == nullptr) return ActorData;


	FMemoryWriter MemoryWriter(ActorData, true);
	// use a wrapper archive that converts FNames and UObject*'s to strings that can be read back in
	FArchive SaveGameArchive(MemoryWriter);
	// serialize the object

	//for (TFieldIterator<UProperty> PropIt(SaveActor->GetClass()); PropIt; ++PropIt)
	//{
		  //UProperty* Property = *PropIt;
	//	  auto PropNew = SaveActor->GetClass()->FindPropertyByName(*PropIt->GetName());
	//	  UE_LOG(KAGameplayStaticsLog,Log,TEXT("Property Name - %s"),*PropNew->GetNameCPP());
	//	  SaveGameArchive << PropNew;
		  // Do something with the property
	//}
	 
	SaveActor->Serialize(SaveGameArchive);

	return ActorData;
}

void UKAGameplayStatics::ActorLoader(AActor * LoadActor, TArray<uint8> ActorData)
{
	if (ActorData.Num() <= 0) return;
	//TODO how to check if valid binary?

	FMemoryReader MemoryReader(ActorData, true);
	FArchive LoadGameArchive(MemoryReader);
	
	//for (TFieldIterator<UProperty> PropIt(LoadActor->GetClass()); PropIt; ++PropIt)
	//{
		  //UProperty* Property = *PropIt;
	//	  auto PropNew = LoadActor->GetClass()->FindPropertyByName(*PropIt->GetName());
	//	  UE_LOG(KAGameplayStaticsLog,Log,TEXT("Property Name - %s"),*PropNew->GetNameCPP());
	//	  LoadGameArchive << PropNew;
		  // Do something with the property
	//	  	LoadGameArchive.GetSerializedProperty();
	//}
	
	LoadActor->Serialize(LoadGameArchive);
}

void UKAGameplayStatics::ChangeLocalization(FString target)
{
	FInternationalization::Get().SetCurrentCulture(target);
}
