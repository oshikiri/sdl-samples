simple pendulum
=====

$\theta$ は反時計回りが正、$\theta=0$が真下。

$$
    m \ell \ddot \theta = -mg\sin\theta
$$

$$
    \ddot{\theta} = -{g \over \ell} \sin \theta
$$

$\Theta := (\theta, \dot\theta)^\top$ = `(x1, x2)`

$$
    \frac{d \Theta}{dt}
    = \begin{pmatrix}
        \dot\theta \\
        \ddot\theta
    \end{pmatrix}
    = \begin{pmatrix}
        \dot\theta \\
        -{g \over \ell} \sin \theta
    \end{pmatrix}
$$


## References

- https://github.com/PacktPublishing/Hands-On-Game-Development-with-WebAssembly/blob/5913ee456dcb32c6ee1a2d45d78e40458a4d11ea/Chapter04/hello_sdl.c
- https://github.com/PacktPublishing/Hands-On-Game-Development-with-WebAssembly/blob/5913ee456dcb32c6ee1a2d45d78e40458a4d11ea/Chapter04/hello_sdl.c
