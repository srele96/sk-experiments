const { spawn } = require("child_process");

function verifyThatCommandWorksOnVercelDeployment() {
  spawn("git ls-tree -r --name-only HEAD | tree --fromfile", {
    shell: true,
    stdio: "inherit",
  });
}

verifyThatCommandWorksOnVercelDeployment();
