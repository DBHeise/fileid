[CmdletBinding()] 
param(
	[String][ValidateSet('Win32','x64')] $Platform = 'x64',
	[String][ValidateSet('Debug', 'Release')] $Config = 'Debug',
	[Switch] $ShowAll
)

$testFolder = Resolve-Path '.\files' -ErrorAction Stop
Set-Alias -Name fileid -Value (Resolve-Path -Path ("..\Bin\$platform\$config\fileid.exe") -ErrorAction Stop)

Write-Verbose -Message ("Using FileId executable: " + (Get-Alias fileid).Definition )

Get-ChildItem -Path $testFolder -Recurse | Where-Object {!$_.PSIsContainer} | ForEach-Object {
    $r = [String]::Join('',(fileid $_.FullName json)) | ConvertFrom-Json -ErrorAction Stop
    $actual = $r.extensions.extension
    $expected = $_.Extension.Trim('.')
    if ($actual -ne $expected -or $ShowAll) {
        New-Object PSObject -Property @{
            File = $_.FullName
            Expected = $expected
            Actual = $actual
        }
    }
}