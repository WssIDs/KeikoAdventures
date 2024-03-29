# Makefile generated by CMakefileGenerator.cs (v1.2)
# *DO NOT EDIT*

cmake_minimum_required (VERSION 2.6)
project (UE4)

# CMake Flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 1 CACHE BOOL "" FORCE)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 1 CACHE BOOL "" FORCE)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)

# Standard Includes
include("/home/wssids/GDrive/KeikoAdventures/Intermediate/ProjectFiles/cmake-includes.cmake")
include("/home/wssids/GDrive/KeikoAdventures/Intermediate/ProjectFiles/cmake-definitions.cmake")
include("/home/wssids/GDrive/KeikoAdventures/Intermediate/ProjectFiles/cmake-headers-ue4.cmake")
include("/home/wssids/GDrive/KeikoAdventures/Intermediate/ProjectFiles/cmake-headers-project.cmake")
include("/home/wssids/GDrive/KeikoAdventures/Intermediate/ProjectFiles/cmake-sources-engine.cmake")
include("/home/wssids/GDrive/KeikoAdventures/Intermediate/ProjectFiles/cmake-sources-project.cmake")
include("/home/wssids/GDrive/KeikoAdventures/Intermediate/ProjectFiles/cmake-csharp-engine.cmake")
include("/home/wssids/GDrive/KeikoAdventures/Intermediate/ProjectFiles/cmake-csharp-project.cmake")

# Optional Shader Include
include("/home/wssids/GDrive/KeikoAdventures/Intermediate/ProjectFiles/cmake-shaders-engine.cmake")
set_source_files_properties(${ENGINE_SHADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
include("/home/wssids/GDrive/KeikoAdventures/Intermediate/ProjectFiles/cmake-shaders-project.cmake")
set_source_files_properties(${PROJECT_SHADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
source_group("Shader Files" REGULAR_EXPRESSION .*.usf)

# Optional Config Include
include("/home/wssids/GDrive/KeikoAdventures/Intermediate/ProjectFiles/cmake-config-engine.cmake")
set_source_files_properties(${ENGINE_CONFIG_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
include("/home/wssids/GDrive/KeikoAdventures/Intermediate/ProjectFiles/cmake-config-project.cmake")
set_source_files_properties(${PROJECT_CONFIG_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
source_group("Config Files" REGULAR_EXPRESSION .*.ini)

add_custom_target(UE4Client-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Client Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Client-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Client Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Client-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Client Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Client-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Client Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Client cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Client Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UE4Editor-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Editor Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Editor-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Editor Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Editor-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Editor Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Editor-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Editor Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Editor cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Editor Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UE4Game-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Game Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Game-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Game Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Game-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Game Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Game-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Game Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Game cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Game Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UE4Server-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Server Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Server-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Server Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Server-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Server Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Server-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Server Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UE4Server cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4Server Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(BlankProgram-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BlankProgram Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(BlankProgram-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BlankProgram Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(BlankProgram-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BlankProgram Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(BlankProgram-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BlankProgram Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(BlankProgram cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BlankProgram Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(BuildPatchTool-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BuildPatchTool Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(BuildPatchTool-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BuildPatchTool Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(BuildPatchTool-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BuildPatchTool Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(BuildPatchTool-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BuildPatchTool Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(BuildPatchTool cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BuildPatchTool Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(CrashReportClient-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" CrashReportClient Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(CrashReportClient-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" CrashReportClient Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(CrashReportClient-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" CrashReportClient Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(CrashReportClient-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" CrashReportClient Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(CrashReportClient cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" CrashReportClient Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UnrealLaunchDaemon-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealLaunchDaemon Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealLaunchDaemon-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealLaunchDaemon Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealLaunchDaemon-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealLaunchDaemon Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealLaunchDaemon-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealLaunchDaemon Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealLaunchDaemon cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealLaunchDaemon Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(DsymExporter-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" DsymExporter Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(DsymExporter-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" DsymExporter Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(DsymExporter-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" DsymExporter Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(DsymExporter-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" DsymExporter Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(DsymExporter cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" DsymExporter Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UE4EditorServices-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4EditorServices Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UE4EditorServices-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4EditorServices Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UE4EditorServices-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4EditorServices Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UE4EditorServices-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4EditorServices Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UE4EditorServices cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UE4EditorServices Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UnrealAtoS-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealAtoS Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealAtoS-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealAtoS Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealAtoS-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealAtoS Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealAtoS-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealAtoS Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealAtoS cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealAtoS Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(MayaLiveLinkPlugin2016-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2016 Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(MayaLiveLinkPlugin2016-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2016 Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(MayaLiveLinkPlugin2016-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2016 Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(MayaLiveLinkPlugin2016-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2016 Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(MayaLiveLinkPlugin2016 cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2016 Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(MayaLiveLinkPlugin2017-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2017 Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(MayaLiveLinkPlugin2017-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2017 Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(MayaLiveLinkPlugin2017-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2017 Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(MayaLiveLinkPlugin2017-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2017 Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(MayaLiveLinkPlugin2017 cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2017 Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(MayaLiveLinkPlugin2018-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2018 Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(MayaLiveLinkPlugin2018-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2018 Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(MayaLiveLinkPlugin2018-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2018 Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(MayaLiveLinkPlugin2018-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2018 Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(MayaLiveLinkPlugin2018 cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MayaLiveLinkPlugin2018 Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(MinidumpDiagnostics-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MinidumpDiagnostics Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(MinidumpDiagnostics-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MinidumpDiagnostics Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(MinidumpDiagnostics-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MinidumpDiagnostics Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(MinidumpDiagnostics-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MinidumpDiagnostics Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(MinidumpDiagnostics cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" MinidumpDiagnostics Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(ShaderCompileWorker-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" ShaderCompileWorker Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(ShaderCompileWorker-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" ShaderCompileWorker Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(ShaderCompileWorker-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" ShaderCompileWorker Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(ShaderCompileWorker-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" ShaderCompileWorker Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(ShaderCompileWorker cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" ShaderCompileWorker Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(SlateViewer-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" SlateViewer Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(SlateViewer-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" SlateViewer Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(SlateViewer-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" SlateViewer Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(SlateViewer-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" SlateViewer Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(SlateViewer cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" SlateViewer Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(SymbolDebugger-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" SymbolDebugger Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(SymbolDebugger-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" SymbolDebugger Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(SymbolDebugger-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" SymbolDebugger Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(SymbolDebugger-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" SymbolDebugger Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(SymbolDebugger cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" SymbolDebugger Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(TestPAL-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" TestPAL Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(TestPAL-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" TestPAL Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(TestPAL-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" TestPAL Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(TestPAL-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" TestPAL Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(TestPAL cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" TestPAL Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UnrealCEFSubProcess-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealCEFSubProcess Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealCEFSubProcess-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealCEFSubProcess Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealCEFSubProcess-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealCEFSubProcess Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealCEFSubProcess-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealCEFSubProcess Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealCEFSubProcess cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealCEFSubProcess Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UnrealFileServer-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealFileServer Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealFileServer-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealFileServer Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealFileServer-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealFileServer Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealFileServer-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealFileServer Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealFileServer cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealFileServer Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UnrealFrontend-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealFrontend Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealFrontend-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealFrontend Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealFrontend-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealFrontend Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealFrontend-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealFrontend Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealFrontend cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealFrontend Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UnrealHeaderTool-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealHeaderTool Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealHeaderTool-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealHeaderTool Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealHeaderTool-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealHeaderTool Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealHeaderTool-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealHeaderTool Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealHeaderTool cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealHeaderTool Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UnrealLightmass-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealLightmass Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealLightmass-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealLightmass Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealLightmass-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealLightmass Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealLightmass-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealLightmass Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealLightmass cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealLightmass Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UnrealPak-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealPak Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealPak-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealPak Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealPak-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealPak Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealPak-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealPak Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealPak cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealPak Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UnrealVersionSelector-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealVersionSelector Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealVersionSelector-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealVersionSelector Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealVersionSelector-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealVersionSelector Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealVersionSelector-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealVersionSelector Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealVersionSelector cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealVersionSelector Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(UnrealWatchdog-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealWatchdog Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealWatchdog-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealWatchdog Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealWatchdog-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealWatchdog Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealWatchdog-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealWatchdog Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealWatchdog cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" UnrealWatchdog Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(BootstrapPackagedGame-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BootstrapPackagedGame Linux Debug  -game -progress -buildscw VERBATIM)
add_custom_target(BootstrapPackagedGame-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BootstrapPackagedGame Linux DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(BootstrapPackagedGame-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BootstrapPackagedGame Linux Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(BootstrapPackagedGame-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BootstrapPackagedGame Linux Test  -game -progress -buildscw VERBATIM)
add_custom_target(BootstrapPackagedGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" BootstrapPackagedGame Linux Development  -game -progress -buildscw VERBATIM)

add_custom_target(KeikoAdventures-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" KeikoAdventures Linux Debug "-project=/home/wssids/GDrive/KeikoAdventures/KeikoAdventures.uproject" -game -progress -buildscw VERBATIM)
add_custom_target(KeikoAdventures-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" KeikoAdventures Linux DebugGame "-project=/home/wssids/GDrive/KeikoAdventures/KeikoAdventures.uproject" -game -progress -buildscw VERBATIM)
add_custom_target(KeikoAdventures-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" KeikoAdventures Linux Shipping "-project=/home/wssids/GDrive/KeikoAdventures/KeikoAdventures.uproject" -game -progress -buildscw VERBATIM)
add_custom_target(KeikoAdventures-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" KeikoAdventures Linux Test "-project=/home/wssids/GDrive/KeikoAdventures/KeikoAdventures.uproject" -game -progress -buildscw VERBATIM)
add_custom_target(KeikoAdventures cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" KeikoAdventures Linux Development "-project=/home/wssids/GDrive/KeikoAdventures/KeikoAdventures.uproject" -game -progress -buildscw VERBATIM)

add_custom_target(KeikoAdventuresEditor-Linux-Debug cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" KeikoAdventuresEditor Linux Debug "-project=/home/wssids/GDrive/KeikoAdventures/KeikoAdventures.uproject" -game -progress -buildscw VERBATIM)
add_custom_target(KeikoAdventuresEditor-Linux-DebugGame cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" KeikoAdventuresEditor Linux DebugGame "-project=/home/wssids/GDrive/KeikoAdventures/KeikoAdventures.uproject" -game -progress -buildscw VERBATIM)
add_custom_target(KeikoAdventuresEditor-Linux-Shipping cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" KeikoAdventuresEditor Linux Shipping "-project=/home/wssids/GDrive/KeikoAdventures/KeikoAdventures.uproject" -game -progress -buildscw VERBATIM)
add_custom_target(KeikoAdventuresEditor-Linux-Test cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" KeikoAdventuresEditor Linux Test "-project=/home/wssids/GDrive/KeikoAdventures/KeikoAdventures.uproject" -game -progress -buildscw VERBATIM)
add_custom_target(KeikoAdventuresEditor cd "/UnrealEngine" && bash "/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh" KeikoAdventuresEditor Linux Development "-project=/home/wssids/GDrive/KeikoAdventures/KeikoAdventures.uproject" -game -progress -buildscw VERBATIM)

add_executable(FakeTarget ${ENGINE_HEADER_FILES} ${ENGINE_SOURCE_FILES} ${ENGINE_CSHARP_FILES} ${ENGINE_SHADER_FILES} ${ENGINE_CONFIG_FILES} ${PROJECT_HEADER_FILES} ${PROJECT_SOURCE_FILES} ${PROJECT_CSHARP_FILES} ${PROJECT_SHADER_FILES} ${PROJECT_CONFIG_FILES})
