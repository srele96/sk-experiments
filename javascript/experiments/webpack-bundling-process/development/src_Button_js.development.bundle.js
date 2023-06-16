'use strict';
(self['webpackChunkwebpack_bundling_process'] =
  self['webpackChunkwebpack_bundling_process'] || []).push([
  ['src_Button_js'],
  {
    /***/ './src/Button.js':
      /*!***********************!*\
  !*** ./src/Button.js ***!
  \***********************/
      /***/ function (
        __unused_webpack_module,
        __webpack_exports__,
        __webpack_require__
      ) {
        __webpack_require__.r(__webpack_exports__);
        /* harmony export */ __webpack_require__.d(__webpack_exports__, {
          /* harmony export */ Button: function () {
            return /* binding */ Button;
          },
          /* harmony export */ UnusedButton: function () {
            return /* binding */ UnusedButton;
          },
          /* harmony export */
        });
        /* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0__ =
          __webpack_require__(/*! react */ '../../node_modules/react/index.js');
        /* harmony import */ var react__WEBPACK_IMPORTED_MODULE_0___default =
          /*#__PURE__*/ __webpack_require__.n(
            react__WEBPACK_IMPORTED_MODULE_0__
          );

        var Button = function Button(_ref) {
          var text = _ref.text,
            onClick = _ref.onClick;
          return /*#__PURE__*/ react__WEBPACK_IMPORTED_MODULE_0___default().createElement(
            'button',
            {
              onClick: onClick,
            },
            text
          );
        }; // check if harmony-unused-export is present for this component

        var UnusedButton = function UnusedButton(_ref2) {
          var text = _ref2.text,
            onClick = _ref2.onClick;
          return /*#__PURE__*/ react__WEBPACK_IMPORTED_MODULE_0___default().createElement(
            'button',
            {
              onClick: onClick,
            },
            text
          );
        };

        /***/
      },
  },
]);
