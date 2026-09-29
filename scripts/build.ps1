param([ValidateSet('x64', 'Win32')][string]$Platform = 'x64')
$ErrorActionPreference = 'Stop'
Set-Location (Split-Path $PSScriptRoot -Parent)
$root = (Get-Location).Path
$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$vs = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (!$vs) { throw 'Instala Visual Studio con Desarrollo para el escritorio con C++.' }
Import-Module "$vs\Common7\Tools\Microsoft.VisualStudio.DevShell.dll"
$arch = if ($Platform -eq 'Win32') { 'x86' } else { 'x64' }
Enter-VsDevShell -VsInstallPath $vs -SkipAutomaticLocation -DevCmdArguments "-arch=$arch -host_arch=x64"
$out = "$root\bin\$Platform\Release\"
& msbuild Motor_CID/Motor_CID.vcxproj /m /p:Configuration=Release /p:Platform=$Platform /p:PlatformToolset=v143 "/p:OutDir=$out" "/p:IntDir=$root\obj\$Platform\Release\"
if ($LASTEXITCODE -ne 0) { throw 'Fallo de compilación del motor.' }
New-Item -ItemType Directory -Force "$root\obj\tests-$Platform" | Out-Null
Push-Location "$root\obj\tests-$Platform"
try {
    $sources = @(Get-ChildItem "$root\Motor_CID\*.cpp" | Where-Object Name -ne 'main.cpp' | ForEach-Object FullName)
    & cl /nologo /std:c++20 /EHsc /utf-8 /MT /DUNICODE /D_UNICODE "/I$root\Motor_CID" "$root\tests\regression.cpp" @sources "/Fe:regression.exe" /link user32.lib gdi32.lib ole32.lib oleaut32.lib uiautomationcore.lib shell32.lib
    if ($LASTEXITCODE -ne 0) { throw 'Fallo de compilación de las pruebas.' }
    & .\regression.exe "$root\Motor_CID\cid0.cid"
    if ($LASTEXITCODE -ne 0) { throw 'Han fallado las pruebas de regresión.' }
} finally { Pop-Location }
Copy-Item LICENSE, README.md, CHANGELOG.md, GUIA-RAPIDA.md, MECACID.md $out
$smoke = Start-Process -FilePath "$out\Motor_CID.exe" -ArgumentList '--mecacid-smoke' -PassThru
if (!$smoke.WaitForExit(60000)) { $smoke.Kill(); throw 'MECACID no terminó la prueba de interfaz.' }
if ($smoke.ExitCode -ne 0) { throw "MECACID falló la prueba de interfaz: $($smoke.ExitCode)" }
New-Item -ItemType Directory -Force dist | Out-Null
Add-Type -AssemblyName System.Drawing
foreach ($bmp in Get-ChildItem "$out\mecacid-*.bmp") {
    $img = [System.Drawing.Image]::FromFile($bmp.FullName)
    try { $img.Save("$root\dist\$($bmp.BaseName)-$arch.png", [System.Drawing.Imaging.ImageFormat]::Png) }
    finally { $img.Dispose() }
}
foreach ($resource in @('Motor_CID.exe', 'keyboard-layout.json', 'Diccionarios\cid0.cid')) {
    if (!(Test-Path "$out$resource")) { throw "Falta recurso: $resource" }
}
New-Item -ItemType Directory -Force dist | Out-Null
$zip = "$root\dist\CID-MECACID-Beta-0.3-Win-$arch.zip"
# Solo archivos de distribución, sin símbolos ni intermedios de compilación.
Compress-Archive -Path "$out\Motor_CID.exe", "$out\keyboard-layout.json", "$out\Diccionarios", "$out\LICENSE", "$out\README.md", "$out\CHANGELOG.md", "$out\GUIA-RAPIDA.md", "$out\MECACID.md" -DestinationPath $zip -Force
(Get-FileHash $zip -Algorithm SHA256).Hash + '  ' + (Split-Path $zip -Leaf) | Set-Content "$zip.sha256" -Encoding ascii
