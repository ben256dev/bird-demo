# Bird Demo

![two-legged bird-like character walking with procedural foot placement](https://shthub.org/u/benjamin/bird-demo1.gif?raw)

## Explanation

This is a demo of planar two-form inverse kinematics and a simple foot placement algorithm. The inverse kinematics formula is derived from the law of cosines. Page 4 of [this paper](https://www.andreasaristidou.com/publications/papers/IK_survey.pdf) was used for reference in addition to my [YouTube video](https://www.youtube.com/watch?v=wgpgNLEEpeY). This method is planar because it runs in the 2D x-y plane. I call it “two-form” because, unless you specify which way the arm should bend for a given state, there are two valid solutions. This IK is often described as “closed-form” because you can compute it directly with a formula, rather than using an iterative numerical method.

The step target is derived from the character velocity, and each foot alternates between stance and swing phases to produce a basic walking motion. Movement is controlled with `A` / `D` or the left/right arrow keys.

### Solve for elbow angle (relative to end affector angle):

$$
\theta=\cos^{-1}\left(\frac{l_{1}^{2}+x^{2}+y^{2}-l_{2}^{2}}{2l_{1}\sqrt{x^{2}+y^{2}}}\right)
$$

### Derive speed to integrate gait phase from velocity and stride_length:

$$
\Delta p=\frac{\lVert\ v\rVert \cdot \Delta t}{L}
$$

## Building

```bash
make all && make run;
```

This project uses `pkg-config` to resolve `raylib`. The `Makefile` also checks `/tmp/raylib-install/lib/pkgconfig`.

If `raylib` is not being detected, verify with:

```bash
PKG_CONFIG_PATH=/tmp/raylib-install/lib/pkgconfig:$PKG_CONFIG_PATH pkg-config --modversion raylib
```

## Future Improvements

Only the character's legs are implemented. The legs should step in a more natural arc, with a more fixed algorithm based on gait parameters. The legs should derive step start and end times from the duty factor. The neck could be implemented with a bezier curve. The elbow switching could be made smoother with interpolation.
