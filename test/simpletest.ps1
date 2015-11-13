$testFolder = 'C:\TestFiles\Sample'
Set-Alias fileid (Resolve-Path ..\x64\debug\fileid.exe)

gci $testFolder | ?{!$_.PSIsContainer} | % {
    $r = fileid $_.FullName text
    $rExt = $r.Split()[2].Trim()
    if ($rExt -ne $_.Extension.Trim('.')) {        
        New-Object PSObject -Property @{
            File = $_.FullName
            Result = $r
        }
    } 
}