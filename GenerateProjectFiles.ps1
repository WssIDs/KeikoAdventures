$UnrealSelector = (New-Object -ComObject WScript.Shell).RegRead("HKLM\SOFTWARE\Classes\Unreal.ProjectFile\DefaultIcon\")
$UnrealSelector = "& "+$UnrealSelector
$project = (Get-ChildItem -Recurse *.uproject).fullname
$UnrealSelector+=" /projectfiles "+"$project" -2017
Invoke-Expression $UnrealSelector