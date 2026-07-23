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

cmake -S . -B $buildDir -G Ninja -DCMAKE_CXX_COMPILER=g++
if ($LASTEXITCODE -ne 0) {
    Write-Error "CMake configuration failed."
    exit $LASTEXITCODE
}

cmake --build $buildDir
if ($LASTEXITCODE -ne 0) {
    Write-Error "Build failed."
    exit $LASTEXITCODE
}

Write-Host "Build completed successfully!" -ForegroundColor Green