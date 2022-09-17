const { spawn } = require("child_process");
const { mkdir } = require("fs");

function verifyThatCommandWorksOnVercelDeployment() {
  spawn("git ls-tree -r --name-only HEAD | tree --fromfile", {
    shell: true,
    stdio: "inherit",
  });
}

verifyThatCommandWorksOnVercelDeployment();

// make directory to stop build from failing
mkdir(__dirname, "build", (error, path) => {
  if (error) throw error;
  console.log(`Created directory: ${path}`);
});
