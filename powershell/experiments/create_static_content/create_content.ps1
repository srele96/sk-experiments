$__dirname = $PSScriptRoot

$staticContent = "dist"
$staticContentPath = Join-Path $__dirname $staticContent

function createFileObject($fileName, $fileContent) {
  $filePath = Join-Path $staticContentPath $fileName

  $fileObject = New-Object -TypeName PSObject -Property @{
    fileName = $fileName
    filePath = $filePath
    fileContent = $fileContent
  }

  return $fileObject
}

function createFileObjects {
  $indexHtmlFileName = "index.html"
  $indexHtmlFileContent = @"
    <!DOCTYPE html>
    <html>
      <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>Test</title>

        <link rel="stylesheet" type="text/css" href="index.css" />
      </head>
      <body>
        <h1>Test</h1>
        <p>Test</p>
        <h2 class="red">Test</h2>
        <script>
          console.log("Hello World!");
        </script>
        <script src="index.js"></script>

        <script src="react.development.js"></script>
        <script src="react-dom.development.js"></script>
        <script>
          console.log({ React, ReactDOM }) // Verify that they are loaded
        </script>

        <div id="root"></div>
        <script src="react-app.js"></script>
      </body>
    </html>
"@
  $indexHtml = createFileObject $indexHtmlFileName $indexHtmlFileContent

  $indexCssFileName = "index.css"
  $indexCssFileContent = @"
  .red { color: red; }
"@
  $indexCss = createFileObject $indexCssFileName $indexCssFileContent

  $indexJsFileName = "index.js"
  $indexJsFileContent = @"
    function createHeader(type) {
      const root = document.querySelector('body');
      const h2 = document.createElement(type);
      h2.textContent = 'Hello World!';
      root.appendChild(h2);
    }

    const headerType = 'h2';
    createHeader(headerType);
"@
  $indexJs = createFileObject $indexJsFileName $indexJsFileContent

  $reactAppJsFileName = "react-app.js"
  $reactAppJsFileContent = @"
    const domRootId = 'root';
    const domRoot = document.getElementById(domRootId);

    const { createElement: e } = React;

    function App() {
      return e(
        'h1',
        { className: 'red' },
        'Hello React Root!'
      );
    }

    const reactRoot = ReactDOM.createRoot(domRoot)
    reactRoot.render(e(App));
"@
  $reactAppJs = createFileObject $reactAppJsFileName $reactAppJsFileContent

  $fileObjects = @($indexHtml, $indexCss, $indexJs, $reactAppJs)

  return $fileObjects
}

function createStaticContentDirectorySilentlyIfNotExist {
  if (!(Test-Path $staticContentPath)) {
    Write-Host "Directory already exist: $staticContentPath"
    Write-Host "Creating directory: $staticContentPath"
    $createDirectorySilently = New-Item -ItemType Directory -Path $staticContentPath | Out-Null

    $createDirectorySilently
  }
}

function createStaticContent {
  $files = createFileObjects

  foreach ($file in $files) {
    Write-Host "Creating the file: " $file.filePath
    Set-Content $file.filePath $file.fileContent
    Write-Host "File created: " $file.filePath
  }
}

function downloadFromUrl($url, $outPath) {
  Write-Host "Downloading: " $url
  Invoke-WebRequest -Uri $url -OutFile $outPath
  Write-Host "Downloaded: " $outPath
}

function downloadReactIfNotExist {
  $urlReact = "https://cdn.jsdelivr.net/npm/react@18.2.0/umd/react.development.js"
  $fileNameReact = "react.development.js"
  $outPathReact = Join-Path $staticContentPath $fileNameReact

  $reactAlreadyDownloaded = Test-Path $outPathReact
  if ($reactAlreadyDownloaded) {
    Write-Host "React already downloaded: " $outPathReact
  } else {
    downloadFromUrl $urlReact $outPathReact
  }

  $urlReactDOM = "https://cdn.jsdelivr.net/npm/react-dom@18.2.0/umd/react-dom.development.js"
  $fileNameReactDOM = "react-dom.development.js"
  $outPathReactDOM = Join-Path $staticContentPath $fileNameReactDOM

  $reactDOMAlreadyDownloaded = Test-Path $outPathReactDOM
  if ($reactDOMAlreadyDownloaded) {
    Write-Host "ReactDOM already downloaded: " $outPathReactDOM
  } else {
    downloadFromUrl $urlReactDOM $outPathReactDOM
  }
}

createStaticContentDirectorySilentlyIfNotExist
createStaticContent
downloadReactIfNotExist
