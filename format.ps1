<#
.SYNOPSIS
    Script to automatically format all C/C++ files in the project using clang-format.
.DESCRIPTION
    Checks for the availability of clang-format from the system PATH or the VS Code C/C++ extension.
    If found, it formats all .c, .cpp, .h, and .hpp files in the current directory and subdirectories.
#>

# 1. Search for clang-format.exe path within VS Code extensions
$extensionClangPath = Get-ChildItem -Path "$env:USERPROFILE\.vscode\extensions" -Filter "clang-format.exe" -Recurse -ErrorAction SilentlyContinue | 
                      Where-Object { $_.FullName -like "*ms-vscode.cpptools*" } | 
                      Select-Object -First 1 -ExpandProperty FullName

# 2. Check clang-format availability
# 2. Check clang-format availability
$clangExecutable = $null

if (Get-Command "clang-format" -ErrorAction SilentlyContinue) {
    # Case 1: clang-format is available in system PATH
    $clangExecutable = "clang-format"
} elseif ($extensionClangPath -and (Test-Path $extensionClangPath)) {
    # Case 2: Found clang-format.exe in VS Code C/C++ Extension
    $clangExecutable = $extensionClangPath
    Set-Alias -Name clang-format -Value $extensionClangPath -Scope Local -ErrorAction SilentlyContinue
}

# 3. Handle formatting logic or display warnings
if ($clangExecutable) {
    Write-Host "[INFO] Found clang-format at: $clangExecutable" -ForegroundColor Green
    Write-Host "[INFO] Formatting C/C++ files..." -ForegroundColor Cyan

    $files = Get-ChildItem -Recurse -Include *.c, *.cpp, *.h, *.hpp

    if ($files.Count -eq 0) {
        Write-Host "[INFO] No .c, .cpp, .h, or .hpp files found in this directory." -ForegroundColor Yellow
    } else {
        $count = 0
        foreach ($file in $files) {
            & $clangExecutable -i $file.FullName
            $count++
            Write-Host "  -> Formatted: $($file.Name)" -ForegroundColor Gray
        }
        Write-Host "[SUCCESS] Successfully formatted $count C/C++ file(s)!" -ForegroundColor Green
    }
} else {
    Write-Host "==========================================================================" -ForegroundColor Yellow
    Write-Host "[WARNING] 'clang-format' tool was not found on your system!" -ForegroundColor Yellow
    Write-Host "Required configuration:" -ForegroundColor Yellow
    Write-Host "  1. VS Code C/C++ extension (ms-vscode.cpptools) is not installed," -ForegroundColor Yellow
    Write-Host "  2. Or LLVM/clang-format is not added to your system PATH." -ForegroundColor Yellow
    Write-Host "How to fix:" -ForegroundColor Yellow
    Write-Host "  - Option 1: Run in PowerShell: winget install LLVM.LLVM" -ForegroundColor Yellow
    Write-Host "  - Option 2: Install Microsoft's 'C/C++' extension in VS Code." -ForegroundColor Yellow
    Write-Host "==========================================================================" -ForegroundColor Yellow
}