// use 'real' code sample to check what will be minified
const { spawn } = require('child_process');

// shell is a different term for terminal, command prompt, powershell, etc...
function runCommandInSeparateShell() {
  const CHANGE_PATH_PRINT_PATH_PRINT_MESSAGE =
    'cd ../ && pwd && echo hello world';

  spawn(CHANGE_PATH_PRINT_PATH_PRINT_MESSAGE, {
    shell: true,
    stdio: 'inherit',
  });
}

runCommandInSeparateShell();
