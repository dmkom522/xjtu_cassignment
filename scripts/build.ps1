param([switch]$Test, [switch]$Run)
$ErrorActionPreference = 'Stop'
if ($PSVersionTable.PSVersion.Major -le 5) {
    # Avoid importing incompatible PowerShell 7 modules inherited by a child shell.
    $env:PSModulePath = Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\Modules'
}
$taskRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$taskBuild = Join-Path $taskRoot 'build'
$taskOriginalPath = $env:Path

function Find-TaskTool([string]$toolName, [string]$relativePath) {
    $taskCommand = Get-Command $toolName -ErrorAction SilentlyContinue
    if ($taskCommand) { return $taskCommand.Source }
    $taskJetBrains = Join-Path $env:ProgramFiles 'JetBrains'
    if (Test-Path -LiteralPath $taskJetBrains) {
        foreach ($taskClion in (Get-ChildItem -LiteralPath $taskJetBrains -Directory -Filter 'CLion*' | Sort-Object Name -Descending)) {
            $taskCandidate = Join-Path $taskClion.FullName $relativePath
            if (Test-Path -LiteralPath $taskCandidate) { return $taskCandidate }
        }
    }
    throw "Cannot find $toolName. Use CLion's CMake project, or install CMake/Ninja/MinGW and add them to PATH."
}

try {
    $taskCmake = Find-TaskTool 'cmake.exe' 'bin\cmake\win\x64\bin\cmake.exe'
    $taskNinja = Find-TaskTool 'ninja.exe' 'bin\ninja\win\x64\ninja.exe'
    $taskCompiler = Find-TaskTool 'g++.exe' 'bin\mingw\bin\g++.exe'
    $taskCtest = Join-Path (Split-Path -Parent $taskCmake) 'ctest.exe'
    $env:Path = (Split-Path -Parent $taskCompiler) + ';' + $env:Path

    & $taskCmake -S $taskRoot -B $taskBuild -G Ninja "-DCMAKE_MAKE_PROGRAM=$taskNinja" "-DCMAKE_CXX_COMPILER=$taskCompiler" -DCMAKE_BUILD_TYPE=Debug
    if ($LASTEXITCODE -ne 0) { throw 'CMake configuration failed.' }
    & $taskCmake --build $taskBuild
    if ($LASTEXITCODE -ne 0) { throw 'Compilation failed.' }
    if ($Test) {
        & $taskCtest --test-dir $taskBuild --output-on-failure
        if ($LASTEXITCODE -ne 0) { throw 'Skeleton tests failed.' }
    }
    if ($Run) {
        & (Join-Path $taskBuild 'finals_survival.exe')
        if ($LASTEXITCODE -ne 0) { throw 'Program returned an error.' }
    }
} finally {
    $env:Path = $taskOriginalPath
}
