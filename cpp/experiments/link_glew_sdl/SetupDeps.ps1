function PromptUser {
  param(
    [string]$title,
    [string]$question,
    [System.Management.Automation.Host.ChoiceDescription[]]$choices
  )
  # https://stackoverflow.com/questions/69098394/powershell-promptforchoice-how-to-edit-descriptions
  $decision = $Host.UI.PromptForChoice($title, $question, $choices, 0)
  if ($decision -eq 0) {
    return $true
  }
  else {
    return $false
  }
}

function SetupRemoteDependenciesRobustly {
  $projectRoot = (Get-Location).Path
  $dependencies = "dependencies"
  $destination = Join-Path $projectRoot $dependencies

  if (Test-Path -Path $destination) {
    $title = 'Directory already exists: ' + $destination
    $question = 'Do you want to delete it?'
    $choices = @(
      [System.Management.Automation.Host.ChoiceDescription]::new("&Yes", "Delete the directory")
      [System.Management.Automation.Host.ChoiceDescription]::new("&No", "Don't delete the directory.")
    )
    if (PromptUser $title $question $choices) {
      Remove-Item -Path $destination -Recurse -Force
      Write-Host "Deleted directory $destination."
    }
    else {
      Write-Host "Aborting setup..."
      return
    }
  }

  $repository = 'https://github.com/srele96/link-glew-sdl-dependencies.git'
  git clone $repository $destination

  # https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.management/copy-item?view=powershell-7.3
  $librariesSubdirectory = "libraries\*"
  $libraries = Join-Path $destination $librariesSubdirectory

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

  if ($itemsToOverwrite.Count -gt 0) {
    $itemsToOverwriteList = $itemsToOverwrite | ForEach-Object { "`n  - $_" }

    $title = 'The following items already exist in the project root: ' + $projectRoot + $itemsToOverwriteList
    $question = "The following operation will overwrite them. Do you want to continue?"
    $choices = @(
      [System.Management.Automation.Host.ChoiceDescription]::new("&Yes", "Continue.")
      [System.Management.Automation.Host.ChoiceDescription]::new("&No", "Abort.")
    )
    if (PromptUser $title $question $choices) {
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

  if (Test-Path -Path $destination) {
    $title = 'Clean up cloned repository.'
    $question = 'Do you want to delete the cloned repository?'
    $choices = @(
      [System.Management.Automation.Host.ChoiceDescription]::new("&Yes", "Delete the cloned repository.")
      [System.Management.Automation.Host.ChoiceDescription]::new("&No", "Don't delete the cloned repository.")
    )
    if (PromptUser $title $question $choices) {
      Remove-Item -Path $destination -Recurse -Force
      Write-Host "Deleted directory $destination."
    }
    else {
      Write-Host "Aborting cleanup..."
      return
    }
  }
}

SetupRemoteDependenciesRobustly
