$__DIRNAME = $PSScriptRoot

$staticContent = "dist"
$staticContentPath = Join-Path $__DIRNAME $staticContent
$port = 3000

function serveStaticContent($port, $path) {
  python -m http.server $port --directory $path
}

serveStaticContent $port $staticContentPath
