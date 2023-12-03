# useful script when i have too many leftover branches on my local machine

# i consider it safe to delete local branch that has no diff with remote
# because i can always restore it from remote

$branchRegexPrefixes = 'feat/*', 'chore/*', 'docs/*'
foreach ($branchRegexPrefix in $branchRegexPrefixes) {
  Write-Host "Branches with prefix ($branchRegexPrefix):"

  $untrimmedBranches = git branch --list $branchRegexPrefix
  # list branches status of local branches
  # whether they exists or have diff on local and remote
  foreach ($untrimmedBranch in $untrimmedBranches) {
    $branch = $untrimmedBranch.Trim()

    $diff = git --no-pager diff $branch origin/$branch;

    # git diff exits with exit code if one of the branches doesn't exist
    if ($LASTEXITCODE -eq 0) {
      if ($diff) {
        write-host "(unsafe, has remote, has diff): $branch"
      } else {
        write-host "(safe, has remote, has no diff): $branch";
        # keep commented because deletion is dangerous and destructive behavior
        # carefully revise branches before uncommenting the line below
        # git branch -d $branch
      }
    } else {
      # Possibly we want to use the content of this branch
      write-host "(unsafe, no remote): $branch"
    }
  }
}
