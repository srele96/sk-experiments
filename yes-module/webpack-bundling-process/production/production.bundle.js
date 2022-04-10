/*! For license information please see production.bundle.js.LICENSE.txt */
!(function () {
  'use strict';
  var e,
    t,
    r = {
      426: function (e, t) {
        var r = Symbol.for('react.element'),
          n = Symbol.for('react.portal'),
          o = Symbol.for('react.fragment'),
          u = Symbol.for('react.strict_mode'),
          c = Symbol.for('react.profiler'),
          i = Symbol.for('react.provider'),
          a = Symbol.for('react.context'),
          l = Symbol.for('react.forward_ref'),
          f = Symbol.for('react.suspense'),
          s = Symbol.for('react.memo'),
          p = Symbol.for('react.lazy'),
          d = Symbol.iterator,
          y = {
            isMounted: function () {
              return !1;
            },
            enqueueForceUpdate: function () {},
            enqueueReplaceState: function () {},
            enqueueSetState: function () {},
          },
          b = Object.assign,
          h = {};
        function m(e, t, r) {
          (this.props = e),
            (this.context = t),
            (this.refs = h),
            (this.updater = r || y);
        }
        function v() {}
        function _(e, t, r) {
          (this.props = e),
            (this.context = t),
            (this.refs = h),
            (this.updater = r || y);
        }
        (m.prototype.isReactComponent = {}),
          (m.prototype.setState = function (e, t) {
            if ('object' != typeof e && 'function' != typeof e && null != e)
              throw Error(
                'setState(...): takes an object of state variables to update or a function which returns an object of state variables.'
              );
            this.updater.enqueueSetState(this, e, t, 'setState');
          }),
          (m.prototype.forceUpdate = function (e) {
            this.updater.enqueueForceUpdate(this, e, 'forceUpdate');
          }),
          (v.prototype = m.prototype);
        var g = (_.prototype = new v());
        (g.constructor = _), b(g, m.prototype), (g.isPureReactComponent = !0);
        var S = Array.isArray,
          w = Object.prototype.hasOwnProperty,
          k = { current: null },
          E = { key: !0, ref: !0, __self: !0, __source: !0 };
        function C(e, t, n) {
          var o,
            u = {},
            c = null,
            i = null;
          if (null != t)
            for (o in (void 0 !== t.ref && (i = t.ref),
            void 0 !== t.key && (c = '' + t.key),
            t))
              w.call(t, o) && !E.hasOwnProperty(o) && (u[o] = t[o]);
          var a = arguments.length - 2;
          if (1 === a) u.children = n;
          else if (1 < a) {
            for (var l = Array(a), f = 0; f < a; f++) l[f] = arguments[f + 2];
            u.children = l;
          }
          if (e && e.defaultProps)
            for (o in (a = e.defaultProps)) void 0 === u[o] && (u[o] = a[o]);
          return {
            $$typeof: r,
            type: e,
            key: c,
            ref: i,
            props: u,
            _owner: k.current,
          };
        }
        function $(e) {
          return 'object' == typeof e && null !== e && e.$$typeof === r;
        }
        var j = /\/+/g;
        function R(e, t) {
          return 'object' == typeof e && null !== e && null != e.key
            ? (function (e) {
                var t = { '=': '=0', ':': '=2' };
                return (
                  '$' +
                  e.replace(/[=:]/g, function (e) {
                    return t[e];
                  })
                );
              })('' + e.key)
            : t.toString(36);
        }
        function O(e, t, o, u, c) {
          var i = typeof e;
          ('undefined' !== i && 'boolean' !== i) || (e = null);
          var a = !1;
          if (null === e) a = !0;
          else
            switch (i) {
              case 'string':
              case 'number':
                a = !0;
                break;
              case 'object':
                switch (e.$$typeof) {
                  case r:
                  case n:
                    a = !0;
                }
            }
          if (a)
            return (
              (c = c((a = e))),
              (e = '' === u ? '.' + R(a, 0) : u),
              S(c)
                ? ((o = ''),
                  null != e && (o = e.replace(j, '$&/') + '/'),
                  O(c, t, o, '', function (e) {
                    return e;
                  }))
                : null != c &&
                  ($(c) &&
                    (c = (function (e, t) {
                      return {
                        $$typeof: r,
                        type: e.type,
                        key: t,
                        ref: e.ref,
                        props: e.props,
                        _owner: e._owner,
                      };
                    })(
                      c,
                      o +
                        (!c.key || (a && a.key === c.key)
                          ? ''
                          : ('' + c.key).replace(j, '$&/') + '/') +
                        e
                    )),
                  t.push(c)),
              1
            );
          if (((a = 0), (u = '' === u ? '.' : u + ':'), S(e)))
            for (var l = 0; l < e.length; l++) {
              var f = u + R((i = e[l]), l);
              a += O(i, t, o, f, c);
            }
          else if (
            ((f = (function (e) {
              return null === e || 'object' != typeof e
                ? null
                : 'function' == typeof (e = (d && e[d]) || e['@@iterator'])
                ? e
                : null;
            })(e)),
            'function' == typeof f)
          )
            for (e = f.call(e), l = 0; !(i = e.next()).done; )
              a += O((i = i.value), t, o, (f = u + R(i, l++)), c);
          else if ('object' === i)
            throw (
              ((t = String(e)),
              Error(
                'Objects are not valid as a React child (found: ' +
                  ('[object Object]' === t
                    ? 'object with keys {' + Object.keys(e).join(', ') + '}'
                    : t) +
                  '). If you meant to render a collection of children, use an array instead.'
              ))
            );
          return a;
        }
        function P(e, t, r) {
          if (null == e) return e;
          var n = [],
            o = 0;
          return (
            O(e, n, '', '', function (e) {
              return t.call(r, e, o++);
            }),
            n
          );
        }
        function x(e) {
          if (-1 === e._status) {
            var t = e._result;
            (t = t()).then(
              function (t) {
                (0 !== e._status && -1 !== e._status) ||
                  ((e._status = 1), (e._result = t));
              },
              function (t) {
                (0 !== e._status && -1 !== e._status) ||
                  ((e._status = 2), (e._result = t));
              }
            ),
              -1 === e._status && ((e._status = 0), (e._result = t));
          }
          if (1 === e._status) return e._result.default;
          throw e._result;
        }
        var T = { current: null },
          A = { transition: null },
          I = {
            ReactCurrentDispatcher: T,
            ReactCurrentBatchConfig: A,
            ReactCurrentOwner: k,
          };
        (t.Children = {
          map: P,
          forEach: function (e, t, r) {
            P(
              e,
              function () {
                t.apply(this, arguments);
              },
              r
            );
          },
          count: function (e) {
            var t = 0;
            return (
              P(e, function () {
                t++;
              }),
              t
            );
          },
          toArray: function (e) {
            return (
              P(e, function (e) {
                return e;
              }) || []
            );
          },
          only: function (e) {
            if (!$(e))
              throw Error(
                'React.Children.only expected to receive a single React element child.'
              );
            return e;
          },
        }),
          (t.Component = m),
          (t.Fragment = o),
          (t.Profiler = c),
          (t.PureComponent = _),
          (t.StrictMode = u),
          (t.Suspense = f),
          (t.__SECRET_INTERNALS_DO_NOT_USE_OR_YOU_WILL_BE_FIRED = I),
          (t.cloneElement = function (e, t, n) {
            if (null == e)
              throw Error(
                'React.cloneElement(...): The argument must be a React element, but you passed ' +
                  e +
                  '.'
              );
            var o = b({}, e.props),
              u = e.key,
              c = e.ref,
              i = e._owner;
            if (null != t) {
              if (
                (void 0 !== t.ref && ((c = t.ref), (i = k.current)),
                void 0 !== t.key && (u = '' + t.key),
                e.type && e.type.defaultProps)
              )
                var a = e.type.defaultProps;
              for (l in t)
                w.call(t, l) &&
                  !E.hasOwnProperty(l) &&
                  (o[l] = void 0 === t[l] && void 0 !== a ? a[l] : t[l]);
            }
            var l = arguments.length - 2;
            if (1 === l) o.children = n;
            else if (1 < l) {
              a = Array(l);
              for (var f = 0; f < l; f++) a[f] = arguments[f + 2];
              o.children = a;
            }
            return {
              $$typeof: r,
              type: e.type,
              key: u,
              ref: c,
              props: o,
              _owner: i,
            };
          }),
          (t.createContext = function (e) {
            return (
              ((e = {
                $$typeof: a,
                _currentValue: e,
                _currentValue2: e,
                _threadCount: 0,
                Provider: null,
                Consumer: null,
                _defaultValue: null,
                _globalName: null,
              }).Provider = { $$typeof: i, _context: e }),
              (e.Consumer = e)
            );
          }),
          (t.createElement = C),
          (t.createFactory = function (e) {
            var t = C.bind(null, e);
            return (t.type = e), t;
          }),
          (t.createRef = function () {
            return { current: null };
          }),
          (t.forwardRef = function (e) {
            return { $$typeof: l, render: e };
          }),
          (t.isValidElement = $),
          (t.lazy = function (e) {
            return {
              $$typeof: p,
              _payload: { _status: -1, _result: e },
              _init: x,
            };
          }),
          (t.memo = function (e, t) {
            return { $$typeof: s, type: e, compare: void 0 === t ? null : t };
          }),
          (t.startTransition = function (e) {
            var t = A.transition;
            A.transition = {};
            try {
              e();
            } finally {
              A.transition = t;
            }
          }),
          (t.unstable_act = function () {
            throw Error(
              'act(...) is not supported in production builds of React.'
            );
          }),
          (t.useCallback = function (e, t) {
            return T.current.useCallback(e, t);
          }),
          (t.useContext = function (e) {
            return T.current.useContext(e);
          }),
          (t.useDebugValue = function () {}),
          (t.useDeferredValue = function (e) {
            return T.current.useDeferredValue(e);
          }),
          (t.useEffect = function (e, t) {
            return T.current.useEffect(e, t);
          }),
          (t.useId = function () {
            return T.current.useId();
          }),
          (t.useImperativeHandle = function (e, t, r) {
            return T.current.useImperativeHandle(e, t, r);
          }),
          (t.useInsertionEffect = function (e, t) {
            return T.current.useInsertionEffect(e, t);
          }),
          (t.useLayoutEffect = function (e, t) {
            return T.current.useLayoutEffect(e, t);
          }),
          (t.useMemo = function (e, t) {
            return T.current.useMemo(e, t);
          }),
          (t.useReducer = function (e, t, r) {
            return T.current.useReducer(e, t, r);
          }),
          (t.useRef = function (e) {
            return T.current.useRef(e);
          }),
          (t.useState = function (e) {
            return T.current.useState(e);
          }),
          (t.useSyncExternalStore = function (e, t, r) {
            return T.current.useSyncExternalStore(e, t, r);
          }),
          (t.useTransition = function () {
            return T.current.useTransition();
          }),
          (t.version = '18.0.0-fc46dba67-20220329');
      },
      784: function (e, t, r) {
        e.exports = r(426);
      },
    },
    n = {};
  function o(e) {
    var t = n[e];
    if (void 0 !== t) return t.exports;
    var u = (n[e] = { exports: {} });
    return r[e](u, u.exports, o), u.exports;
  }
  (o.m = r),
    (o.d = function (e, t) {
      for (var r in t)
        o.o(t, r) &&
          !o.o(e, r) &&
          Object.defineProperty(e, r, { enumerable: !0, get: t[r] });
    }),
    (o.f = {}),
    (o.e = function (e) {
      return Promise.all(
        Object.keys(o.f).reduce(function (t, r) {
          return o.f[r](e, t), t;
        }, [])
      );
    }),
    (o.u = function (e) {
      return e + '.production.bundle.js';
    }),
    (o.g = (function () {
      if ('object' == typeof globalThis) return globalThis;
      try {
        return this || new Function('return this')();
      } catch (e) {
        if ('object' == typeof window) return window;
      }
    })()),
    (o.o = function (e, t) {
      return Object.prototype.hasOwnProperty.call(e, t);
    }),
    (e = {}),
    (t = 'webpack-bundling-process:'),
    (o.l = function (r, n, u, c) {
      if (e[r]) e[r].push(n);
      else {
        var i, a;
        if (void 0 !== u)
          for (
            var l = document.getElementsByTagName('script'), f = 0;
            f < l.length;
            f++
          ) {
            var s = l[f];
            if (
              s.getAttribute('src') == r ||
              s.getAttribute('data-webpack') == t + u
            ) {
              i = s;
              break;
            }
          }
        i ||
          ((a = !0),
          ((i = document.createElement('script')).charset = 'utf-8'),
          (i.timeout = 120),
          o.nc && i.setAttribute('nonce', o.nc),
          i.setAttribute('data-webpack', t + u),
          (i.src = r)),
          (e[r] = [n]);
        var p = function (t, n) {
            (i.onerror = i.onload = null), clearTimeout(d);
            var o = e[r];
            if (
              (delete e[r],
              i.parentNode && i.parentNode.removeChild(i),
              o &&
                o.forEach(function (e) {
                  return e(n);
                }),
              t)
            )
              return t(n);
          },
          d = setTimeout(
            p.bind(null, void 0, { type: 'timeout', target: i }),
            12e4
          );
        (i.onerror = p.bind(null, i.onerror)),
          (i.onload = p.bind(null, i.onload)),
          a && document.head.appendChild(i);
      }
    }),
    (o.r = function (e) {
      'undefined' != typeof Symbol &&
        Symbol.toStringTag &&
        Object.defineProperty(e, Symbol.toStringTag, { value: 'Module' }),
        Object.defineProperty(e, '__esModule', { value: !0 });
    }),
    (function () {
      var e;
      o.g.importScripts && (e = o.g.location + '');
      var t = o.g.document;
      if (!e && t && (t.currentScript && (e = t.currentScript.src), !e)) {
        var r = t.getElementsByTagName('script');
        r.length && (e = r[r.length - 1].src);
      }
      if (!e)
        throw new Error(
          'Automatic publicPath is not supported in this browser'
        );
      (e = e
        .replace(/#.*$/, '')
        .replace(/\?.*$/, '')
        .replace(/\/[^\/]+$/, '/')),
        (o.p = e);
    })(),
    (function () {
      var e = { 143: 0 };
      o.f.j = function (t, r) {
        var n = o.o(e, t) ? e[t] : void 0;
        if (0 !== n)
          if (n) r.push(n[2]);
          else {
            var u = new Promise(function (r, o) {
              n = e[t] = [r, o];
            });
            r.push((n[2] = u));
            var c = o.p + o.u(t),
              i = new Error();
            o.l(
              c,
              function (r) {
                if (o.o(e, t) && (0 !== (n = e[t]) && (e[t] = void 0), n)) {
                  var u = r && ('load' === r.type ? 'missing' : r.type),
                    c = r && r.target && r.target.src;
                  (i.message =
                    'Loading chunk ' + t + ' failed.\n(' + u + ': ' + c + ')'),
                    (i.name = 'ChunkLoadError'),
                    (i.type = u),
                    (i.request = c),
                    n[1](i);
                }
              },
              'chunk-' + t,
              t
            );
          }
      };
      var t = function (t, r) {
          var n,
            u,
            c = r[0],
            i = r[1],
            a = r[2],
            l = 0;
          if (
            c.some(function (t) {
              return 0 !== e[t];
            })
          ) {
            for (n in i) o.o(i, n) && (o.m[n] = i[n]);
            a && a(o);
          }
          for (t && t(r); l < c.length; l++)
            (u = c[l]), o.o(e, u) && e[u] && e[u][0](), (e[u] = 0);
        },
        r = (self.webpackChunkwebpack_bundling_process =
          self.webpackChunkwebpack_bundling_process || []);
      r.forEach(t.bind(null, 0)), (r.push = t.bind(null, r.push.bind(r)));
    })(),
    (function () {
      var e = o(784);
      function t(t) {
        var r = t.text,
          n = t.onClick;
        return e.createElement('button', { onClick: n }, r);
      }
      o
        .e(454)
        .then(o.bind(o, 454))
        .then(function (e) {
          var t = e.Button;
          console.log(React.createElement(t, null));
        }),
        console.log(React.createElement(t, null)),
        document.body.appendChild(
          document.createTextNode(''.concat(2 * 2 * 2))
        );
    })();
})();
