param(
    [switch]$Clean
)

$buildDir = "build"

if ($Clean) {
    Write-Host "Cleaning build directory..." -ForegroundColor Cyan
    if (Test-Path $buildDir) {
        Remove-Item -Recurse -Force $buildDir
    }
}

function Find-CMake {
    $cmake = Get-Command cmake -ErrorAction SilentlyContinue | Select-Object -First 1 -ExpandProperty Source
    if (-not $cmake) {
        $candidates = @(
            "C:\Program Files\CMake\bin\cmake.exe",
            "C:\Program Files (x86)\CMake\bin\cmake.exe"
        )
        foreach ($path in $candidates) {
            if (Test-Path $path) {
                return $path
            }
        }
    }
    return $cmake
}

function Select-CMakeGenerator {
    if (Get-Command ninja -ErrorAction SilentlyContinue) {
        return 'Ninja'
    }
    if (Get-Command mingw32-make -ErrorAction SilentlyContinue) {
        return 'MinGW Makefiles'
    }
    if (Get-Command make -ErrorAction SilentlyContinue) {
        return 'Unix Makefiles'
    }
    return $null
}

$cmakeExe = Find-CMake
if (-not $cmakeExe) {
    Write-Error "CMake executable not found. Install CMake and add it to the PATH, or install it in the default Program Files location."
    exit 1
}

$generator = Select-CMakeGenerator
if (-not $generator) {
    Write-Error "No supported CMake generator found. Install Ninja, mingw32-make, or make and try again."
    exit 1
}

Write-Host "Using CMake: $cmakeExe"
Write-Host "Using generator: $generator"

& "$cmakeExe" -S . -B $buildDir -G $generator -DCMAKE_CXX_COMPILER=g++
if ($LASTEXITCODE -ne 0) {
    Write-Error "CMake configuration failed."
    exit $LASTEXITCODE
}

& "$cmakeExe" --build $buildDir
if ($LASTEXITCODE -ne 0) {
    Write-Error "Build failed."
    exit $LASTEXITCODE
}

Write-Host "Build completed successfully!" -ForegroundColor Green