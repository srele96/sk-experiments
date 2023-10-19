/*
 * ATTENTION: The "eval" devtool has been used (maybe by default in mode: "development").
 * This devtool is neither made for production nor for readable output files.
 * It uses "eval()" calls to create a separate source file in the browser devtools.
 * If you are trying to read the output file, select a different devtool (https://webpack.js.org/configuration/devtool/)
 * or disable the default devtool with "devtool: false".
 * If you are looking for production-ready output files, see mode: "production" (https://webpack.js.org/configuration/mode/).
 */
/******/ (() => { // webpackBootstrap
/******/ 	"use strict";
/******/ 	var __webpack_modules__ = ({

/***/ "./App.js":
/*!****************!*\
  !*** ./App.js ***!
  \****************/
/***/ ((__unused_webpack_module, __webpack_exports__, __webpack_require__) => {

eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export */ __webpack_require__.d(__webpack_exports__, {\n/* harmony export */   App: () => (/* binding */ App)\n/* harmony export */ });\n/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ \"react\");\n/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);\n\n\nfunction App() {\n  // The problem is fairly complex.\n  // The data has to fetch on the server and the client.\n  // The data has to be fetched on the server for the initial render.\n  // The data does not need to be fetched on initial client side render.\n  // The data should be fetched on subsequent client side renders.\n  // (Later): The user should be able to refetch the data on demand.\n  //\n  // The engineers need to learn more about the problem domain.\n  // They need to define the problem clearly.\n  // Then they need to start thinking about the constraints, the trade-offs.\n  // Then they need to think about possible solutions, public APIs, etc.\n  //\n  // Then there is probably an experimental phase where they try out the\n  // solution and gather feedback from their users.\n  //\n  // Efficient algorithms and data structures are only a part of the software\n  // engineering process. I start to understand why the ReactJS team uses RFCs.\n  //\n  // Some problems:\n  // - fetching data on the client and the server\n  // - how do we expose the user the data to fetch\n  // - and more...\n  // const { state, loading, error } = useData({\n  //   before: () => {\n  //     //\n  //   },\n  //   after: () => {\n  //     //\n  //   },\n  //   select: (state) => {\n  //     // select the data i want to use in my component\n  //   },\n  // });\n\n  (0,react__WEBPACK_IMPORTED_MODULE_0__.useEffect)(() => {\n    console.log('Hello World!');\n  }, []);\n\n  return (0,react__WEBPACK_IMPORTED_MODULE_0__.createElement)('h1', null, 'Hello World');\n}\n\n\n\n\n//# sourceURL=webpack://ssr/./App.js?");

/***/ }),

/***/ "./Page.js":
/*!*****************!*\
  !*** ./Page.js ***!
  \*****************/
/***/ ((__unused_webpack_module, __webpack_exports__, __webpack_require__) => {

eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export */ __webpack_require__.d(__webpack_exports__, {\n/* harmony export */   Page: () => (/* binding */ Page)\n/* harmony export */ });\n/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! react */ \"react\");\n/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_0__);\n\n\nfunction Page(props) {\n  return (0,react__WEBPACK_IMPORTED_MODULE_0__.createElement)(\n    'html',\n    null,\n    (0,react__WEBPACK_IMPORTED_MODULE_0__.createElement)(\n      'head',\n      null,\n      (0,react__WEBPACK_IMPORTED_MODULE_0__.createElement)('meta', { charSet: 'utf-8' }),\n      (0,react__WEBPACK_IMPORTED_MODULE_0__.createElement)('meta', {\n        name: 'viewport',\n        content: 'width=device-width, initial-scale=1',\n      }),\n      (0,react__WEBPACK_IMPORTED_MODULE_0__.createElement)('title', null, props.title)\n    ),\n    (0,react__WEBPACK_IMPORTED_MODULE_0__.createElement)(\n      'body',\n      null,\n      (0,react__WEBPACK_IMPORTED_MODULE_0__.createElement)('div', { id: 'root' }, props.children),\n      (0,react__WEBPACK_IMPORTED_MODULE_0__.createElement)('script', { src: '/client.js' }),\n      (0,react__WEBPACK_IMPORTED_MODULE_0__.createElement)(\n        'script',\n        {\n          dangerouslySetInnerHTML: {\n            __html: `window.__INITIAL_STATE__ = ${JSON.stringify(\n              props.initialState\n              // Sanitize initial state to prevent XSS attacks.\n            ).replace(/</g, '\\\\u003c')}`,\n          },\n        },\n        null\n      )\n    )\n  );\n}\n\n\n\n\n//# sourceURL=webpack://ssr/./Page.js?");

/***/ }),

/***/ "./server.js":
/*!*******************!*\
  !*** ./server.js ***!
  \*******************/
/***/ ((__unused_webpack_module, __webpack_exports__, __webpack_require__) => {

eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var path__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! path */ \"path\");\n/* harmony import */ var path__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(path__WEBPACK_IMPORTED_MODULE_0__);\n/* harmony import */ var express__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! express */ \"express\");\n/* harmony import */ var express__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(express__WEBPACK_IMPORTED_MODULE_1__);\n/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! react */ \"react\");\n/* harmony import */ var react__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(react__WEBPACK_IMPORTED_MODULE_2__);\n/* harmony import */ var react_dom_server__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! react-dom/server */ \"react-dom/server\");\n/* harmony import */ var react_dom_server__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(react_dom_server__WEBPACK_IMPORTED_MODULE_3__);\n/* harmony import */ var _App__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! ./App */ \"./App.js\");\n/* harmony import */ var _Page__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! ./Page */ \"./Page.js\");\n\n\n\n\n\n\n\nconst app = express__WEBPACK_IMPORTED_MODULE_1___default()();\n\napp.use(express__WEBPACK_IMPORTED_MODULE_1___default()[\"static\"](path__WEBPACK_IMPORTED_MODULE_0___default().join(__dirname, 'public')));\n\napp.get('/', (req, res) => {\n  const initialState = { name: 'World' };\n\n  const { pipe } = react_dom_server__WEBPACK_IMPORTED_MODULE_3___default().renderToPipeableStream(\n    (0,react__WEBPACK_IMPORTED_MODULE_2__.createElement)(_Page__WEBPACK_IMPORTED_MODULE_5__.Page, { title: 'Hello', initialState }, (0,react__WEBPACK_IMPORTED_MODULE_2__.createElement)(_App__WEBPACK_IMPORTED_MODULE_4__.App)),\n    {\n      onShellReady() {\n        pipe(res);\n      },\n    }\n  );\n});\n\napp.listen(3000, () => {\n  console.log('Server is listening on port: 3000');\n});\n\n\n//# sourceURL=webpack://ssr/./server.js?");

/***/ }),

/***/ "express":
/*!**************************!*\
  !*** external "express" ***!
  \**************************/
/***/ ((module) => {

module.exports = require("express");

/***/ }),

/***/ "react":
/*!************************!*\
  !*** external "react" ***!
  \************************/
/***/ ((module) => {

module.exports = require("react");

/***/ }),

/***/ "react-dom/server":
/*!***********************************!*\
  !*** external "react-dom/server" ***!
  \***********************************/
/***/ ((module) => {

module.exports = require("react-dom/server");

/***/ }),

/***/ "path":
/*!***********************!*\
  !*** external "path" ***!
  \***********************/
/***/ ((module) => {

module.exports = require("path");

/***/ })

/******/ 	});
/************************************************************************/
/******/ 	// The module cache
/******/ 	var __webpack_module_cache__ = {};
/******/ 	
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/ 		// Check if module is in cache
/******/ 		var cachedModule = __webpack_module_cache__[moduleId];
/******/ 		if (cachedModule !== undefined) {
/******/ 			return cachedModule.exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = __webpack_module_cache__[moduleId] = {
/******/ 			// no module.id needed
/******/ 			// no module.loaded needed
/******/ 			exports: {}
/******/ 		};
/******/ 	
/******/ 		// Execute the module function
/******/ 		__webpack_modules__[moduleId](module, module.exports, __webpack_require__);
/******/ 	
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/ 	
/************************************************************************/
/******/ 	/* webpack/runtime/compat get default export */
/******/ 	(() => {
/******/ 		// getDefaultExport function for compatibility with non-harmony modules
/******/ 		__webpack_require__.n = (module) => {
/******/ 			var getter = module && module.__esModule ?
/******/ 				() => (module['default']) :
/******/ 				() => (module);
/******/ 			__webpack_require__.d(getter, { a: getter });
/******/ 			return getter;
/******/ 		};
/******/ 	})();
/******/ 	
/******/ 	/* webpack/runtime/define property getters */
/******/ 	(() => {
/******/ 		// define getter functions for harmony exports
/******/ 		__webpack_require__.d = (exports, definition) => {
/******/ 			for(var key in definition) {
/******/ 				if(__webpack_require__.o(definition, key) && !__webpack_require__.o(exports, key)) {
/******/ 					Object.defineProperty(exports, key, { enumerable: true, get: definition[key] });
/******/ 				}
/******/ 			}
/******/ 		};
/******/ 	})();
/******/ 	
/******/ 	/* webpack/runtime/hasOwnProperty shorthand */
/******/ 	(() => {
/******/ 		__webpack_require__.o = (obj, prop) => (Object.prototype.hasOwnProperty.call(obj, prop))
/******/ 	})();
/******/ 	
/******/ 	/* webpack/runtime/make namespace object */
/******/ 	(() => {
/******/ 		// define __esModule on exports
/******/ 		__webpack_require__.r = (exports) => {
/******/ 			if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 				Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 			}
/******/ 			Object.defineProperty(exports, '__esModule', { value: true });
/******/ 		};
/******/ 	})();
/******/ 	
/************************************************************************/
/******/ 	
/******/ 	// startup
/******/ 	// Load entry module and return exports
/******/ 	// This entry module can't be inlined because the eval devtool is used.
/******/ 	var __webpack_exports__ = __webpack_require__("./server.js");
/******/ 	
/******/ })()
;