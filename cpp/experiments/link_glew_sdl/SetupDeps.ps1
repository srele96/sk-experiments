function AskForConfirmation {
  param(
    [string]$title,
    [string]$question,
    [System.Management.Automation.Host.ChoiceDescription[]]$choices
  )
  # https://stackoverflow.com/questions/69098394/powershell-promptforchoice-how-to-edit-descriptions
  $decision = $Host.UI.PromptForChoice($title, $question, $choices, 0)

  # Always treat the first choice as yes. This solution is flaky and bug-prone,
  # but it works for now.
  $yes = 0
  if ($decision -eq $yes) {
    return $true
  }
  else {
    return $false
  }
}

function SetupRemoteDependenciesRobustly {
  # Always use the path to the powershell script because the script can be
  # executed from any directory on user's machine. We always want to setup
  # dependencies in the project root, and not in the execution location.
  $projectRoot = $PSScriptRoot
  $dependencies = "dependencies"
  $downloadLibrariesDestination = Join-Path $projectRoot $dependencies

  if (Test-Path -Path $downloadLibrariesDestination) {
    $title = 'Directory already exists: ' + $downloadLibrariesDestination
    $question = 'Do you want to delete it?'
    $choices = @(
      [System.Management.Automation.Host.ChoiceDescription]::new("&Yes", "Delete the directory")
      [System.Management.Automation.Host.ChoiceDescription]::new("&No", "Don't delete the directory.")
    )
    if (AskForConfirmation $title $question $choices) {
      Remove-Item -Path $downloadLibrariesDestination -Recurse -Force
      Write-Host "Deleted directory $downloadLibrariesDestination."
    }
    else {
      Write-Host "Aborting setup..."
      return
    }
  }

  $repository = 'https://github.com/srele96/link-glew-sdl-dependencies.git'
  git clone $repository $downloadLibrariesDestination

  # https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.management/copy-item?view=powershell-7.3
  $librariesSubdirectory = "libraries\*"
  $libraries = Join-Path $downloadLibrariesDestination $librariesSubdirectory

  # Find out which items from the $libraries directory already exist in the
  # project root. We don't want to forcefully overwrite anything without the
  # user's consent.
  $itemsToOverwrite = @()
  foreach ($item in Get-ChildItem -Path $libraries) {
    $itemPath = Join-Path $projectRoot $item.Name
    if (Test-Path -Path $itemPath) {
      $itemsToOverwrite += $item.Name
    }
  }

  $hasItemsToOverwrite = $itemsToOverwrite.Count -gt 0
  if ($hasItemsToOverwrite) {
    $itemsToOverwriteList = $itemsToOverwrite | ForEach-Object { "`n  - $_" }

    $title = 'The following items already exist in the project root: ' + $projectRoot + $itemsToOverwriteList
    $question = "The following operation will overwrite them. Do you want to continue?"
    $choices = @(
      [System.Management.Automation.Host.ChoiceDescription]::new("&Yes", "Continue.")
      [System.Management.Automation.Host.ChoiceDescription]::new("&No", "Abort.")
    )
    if (AskForConfirmation $title $question $choices) {
      Write-Host "Continuing..."
    }
    else {
      Write-Host "Aborting setup..."
      return
    }
  }

  Write-Host "Copying libraries to $projectRoot..."
  Copy-Item -Path $libraries -Destination $projectRoot -Recurse -Force
  Write-Host "Setup complete."

  if (Test-Path -Path $downloadLibrariesDestination) {
    $title = 'Clean up cloned repository.'
    $question = 'Do you want to delete the cloned repository?'
    $choices = @(
      [System.Management.Automation.Host.ChoiceDescription]::new("&Yes", "Delete the cloned repository.")
      [System.Management.Automation.Host.ChoiceDescription]::new("&No", "Don't delete the cloned repository.")
    )
    if (AskForConfirmation $title $question $choices) {
      Remove-Item -Path $downloadLibrariesDestination -Recurse -Force
      Write-Host "Deleted directory $downloadLibrariesDestination."
    }
    else {
      Write-Host "Aborting cleanup..."
      return
    }
  }
}

SetupRemoteDependenciesRobustly
