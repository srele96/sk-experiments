# $\frac{d}{dx}\arcsin{x}$ by the first principle

Start by using the limit definition:

$$
\frac{d}{dx}  \arcsin{x} =
\lim_{h \to  0}  \frac{\arcsin(x+h)  -  \arcsin{x}}{h}
$$

Derive the identity for $\arcsin{x}-\arcsin{y}$:

$$
\begin{align}
\sin(\alpha-\beta)=\sin{\alpha}\cos{\beta}-\cos{\alpha}\sin{\beta}
\\
\arcsin(\sin(\alpha-\beta))=\arcsin(\sin{\alpha}\cos{\beta}-\cos{\alpha}\sin{\beta})
\\
\alpha-\beta=\arcsin(\sin{\alpha}\cos{\beta}-\cos{\alpha}\sin{\beta})
\end{align}
$$

By substitution:

$$
\alpha=\arcsin{x} \implies \sin{\alpha}=x \quad
-\pi/2\leq\alpha\leq\pi/2 \quad
\text{and} \quad -1 \leq x \leq 1
\\
\beta=\arcsin{y} \implies \sin{\beta}=y \quad
-\pi/2\leq\beta\leq\pi/2 \quad
\text{and} \quad -1 \leq y \leq 1
\\
\text{Bounds on } \alpha \text{ result in choice of the positive square root.}
\\
\cos{\alpha} = \sqrt{1 - \sin^2{\alpha}} = \sqrt{1 - x^2}
\\
\text{Bounds on } \beta \text{ result in choice of the positive square root.}
\\
\cos{\beta} = \sqrt{1 - sin^2{\beta}} = \sqrt{1 - y^2}
$$

Therefore:

$$
\arcsin{x} - \arcsin{y} = \arcsin(x\sqrt{1 - y^2} - y\sqrt{1 - x^2})
$$

Back to the limit and apply the derived identity:

$$
\frac{d}{dx} \arcsin{x} =
\lim_{h \to 0} \frac{\arcsin(x+h) - \arcsin{x}}{h} =
\\
\lim_{h \to 0} \frac{\arcsin((x+h)\sqrt{1 - x^2} - x\sqrt{1 - (x+h)^2})}{h}
$$

Apply substitution to get rid of the function in the numerator.

$$
\arcsin((x+h)\sqrt{1 - x^2} - x\sqrt{1 - (x+h)^2}) = t
\\
\sin(\arcsin((x+h)\sqrt{1 - x^2} - x\sqrt{1 - (x+h)^2})) = \sin{t}
\\
(x+h)\sqrt{1 - x^2} - x\sqrt{1 - (x+h)^2} = \sin{t}
$$

Solve for h:

$$
(x+h)\sqrt{1 - x^2} - \sin{t} = x\sqrt{1 - (x+h)^2}
\\
[(x+h)\sqrt{1 - x^2} - \sin{t}]^2 = [x\sqrt{1 - (x+h)^2}]^2
\\
(x+h)^2\lvert1 - x^2\rvert - 2(x+h)\sqrt{1 - x^2}\sin{t} + \sin^2{t} = x^2\lvert1 - (x+h)^2\rvert
$$

_(I am possibly wrong here. This is another substitution and I might not be able to rely on restrictions of x and y.)_ Because of restrictions \(-1 \leq x \leq 1\) and \(-1 \leq y \leq 1\) in identity \(\arcsin{x} - \arcsin{y} = \arcsin(x\sqrt{1-y^2} - y\sqrt{1-x^2})\) we know that the two expressions \(1-x^2 > 0\) and \(1 - y^2 > 0\) are positive. Therefore we can use the positive definition of the absolute value.

Therefore:

$$
(x+h)^2(1 - x^2) - 2(x+h)\sqrt{1 - x^2}\sin{t} + \sin^2{t} = x^2(1 - (x+h)^2)
\\
(x+h)^2(1 - x^2) - 2(x+h)\sqrt{1 - x^2}\sin{t} + \sin^2{t} = x^2 - x^2(x+h)^2
\\
(x+h)^2(1 - x^2) + x^2(x+h)^2 - 2(x+h)\sqrt{1 - x^2}\sin{t} + \sin^2{t} - x^2 = 0
\\
(x+h)^2(1 - x^2 + x^2) - 2(x+h)\sqrt{1 - x^2}\sin{t} + \sin^2{t} - x^2 = 0
\\
(x+h)^2 - 2(x+h)\sqrt{1 - x^2}\sin{t} + \sin^2{t} - x^2 = 0
\\
[1](x+h)^2 - [2\sqrt{1 - x^2}\sin{t}](x+h) + [\sin^2{t} - x^2] = 0
$$

We notice that it is a quadratic equation, where:

$$
a = 1 \\
b = -2\sqrt{1 - x^2}\sin{t} \\
c = \sin^2{t} - x^2 \\
$$

Solve for \((x + h)\) using quadratic formula \(\frac{-b \pm \sqrt{b^2 - 4ac}}{2a}\):

$$
(x+h) = \frac{2\sqrt{1 - x^2}\sin{t} \pm \sqrt{[2\sqrt{1 - x^2}\sin{t}]^2 - 4[\sin^2{t} - x^2]}}{2}
\\
(x+h) = \frac{2\sqrt{1 - x^2}\sin{t} \pm \sqrt{4(1 - x^2)\sin^2{t} - 4\sin^2{t} + 4x^2}}{2}
\\
(x+h) = \frac{2\sqrt{1 - x^2}\sin{t} \pm \sqrt{4\sin^2{t} - 4x^2sin^2{t} - 4\sin^2{t} + 4x^2}}{2}
\\
(x+h) = \frac{2\sqrt{1 - x^2}\sin{t} \pm \sqrt{4x^2 - 4x^2sin^2{t}}}{2}
\\
(x+h) = \frac{2\sqrt{1 - x^2}\sin{t} \pm \sqrt{4x^2(1 - sin^2{t})}}{2}
\\
(x+h) = \frac{2\sqrt{1 - x^2}\sin{t} \pm 2\sqrt{x^2}\sqrt{1 - sin^2{t}}}{2}
\\
(x+h) = \sqrt{1 - x^2}\sin{t} \pm \sqrt{x^2}\sqrt{1 - sin^2{t}}
\\
(x+h) = \sqrt{1 - x^2}\sin{t} + \lvert{x}\rvert(\pm\sqrt{1 - sin^2{t}})
\\
h = \sqrt{1 - x^2}\sin{t} + \lvert{x}\rvert(\pm\sqrt{1 - sin^2{t}}) - x
$$

Here we notice that the square root is a \(\cos{t}\):

$$
\cos{t}=\pm\sqrt{1 - sin^2{t}}
$$

_(I might be wrong here. I don't know how to handle the absolute value of x.)._ And in the context of the limit and substitution:

$$\text{The variables we solve for are } \mathbf{t} \text{ and } \mathbf{h} \text{. Therefore the variable } \mathbf{x} \text{ is treated as a constant.}$$

Since the absolute value of a constant is always positive value, we proceed as follows:

$$
h = \sqrt{1 - x^2}\sin{t} + x\cos{t} - x
\\
h \to 0 \implies t \to 0
\\
\sqrt{1 - x^2}\sin{t} + x\cos{t} - x = 0
\\
0 + x - x = 0
\\
0 = 0
$$

Therefore, we can apply the following substitution to the limit:

$$
\arcsin((x+h)\sqrt{1 - x^2} - x\sqrt{1 - (x+h)^2}) = t
\\
h = \sqrt{1 - x^2}\sin{t} + x\cos{t} - x
\\
h \to 0 \implies t \to 0
$$

Back to the limit and apply the substitution:

$$
\frac{d}{dx} \arcsin{x} =
\lim_{h \to 0} \frac{\arcsin(x+h) - \arcsin{x}}{h} =
\\
\lim_{h \to 0} \frac{\arcsin((x+h)\sqrt{1 - x^2} - x\sqrt{1 - (x+h)^2})}{h} =
\\
\lim_{t \to 0} \frac{t}{\sqrt{1 - x^2}\sin{t} + x\cos{t} - x}
$$

Here we notice that:

$$[x\cos{t}] \rightarrow x \text{ as } t \to 0 $$

Therefore:

$$
\lim_{t \to 0} \frac{t}{\sqrt{1 - x^2}\sin{t} + x\cos{t} - x} =
\\
\lim_{t \to 0} \frac{t}{\sqrt{1 - x^2}\sin(t) + x - x}
\\
\lim_{t \to 0} \frac{t}{\sqrt{1 - x^2}\sin(t)}
$$

By the common limit and by the limit law:

$$
\lim_{t \to 0} \frac{\sin{t}}{t} = 1
\\
[\lim_{t \to 0} \frac{\sin{t}}{t}]^{-1} = [1]^{-1}
\\
\lim_{t \to 0} [\frac{\sin{t}}{t}]^{-1} = [1]^{-1}
\\
\lim_{t \to 0} \frac{t}{\sin{t}} = 1
$$

Hence, we conclude:

$$
\lim_{t \to 0} \frac{t}{\sqrt{1 - x^2}\sin(t)} = \frac{1}{\sqrt{1 - x^2}}
$$
