[CmdletBinding()] 
param(
	[ValidateSet("x64", "x86")][String[]]$Platforms = @("x64", "x86"),
	[ValidateSet("Debug", "Release")][String[]]$Flavors = @("Debug", "Release"),
	[Switch]$KeepPDB
)

$msbuildPath = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -requires Microsoft.Component.MSBuild -find MSBuild\Current\Bin\amd64\MSBuild.exe | Select-Object -First 1
Set-Alias -name msbuild -Value $msbuildPath


$Platforms | ForEach-Object {
	$platform = $_
	$Flavors | ForEach-Object {
		$config = $_
		
		Write-Progress -Activity "Building" -Status ($platform + "," + $config)
		msbuild -noLogo -m -verbosity:detailed -restore -target:Rebuild -property:Configuration=$config -property:Platform=$platform -clp:"ErrorsOnly;NoSummary" fileid.sln
		Write-Progress -Activity "Building" -Status ($platform + "," + $config) -Completed
		if ($LASTEXITCODE) { exit $LASTEXITCODE }
	}
}

if ($KeepPDB) {
	Get-ChildItem -Path .\Bin -Recurse -Exclude @("*.exe", "*.pdb") -File | Remove-Item
} else {
	#Clean up other artifacts
	Get-ChildItem -Path .\Bin -Recurse -Exclude @("*.exe") -File | Remove-Item
}