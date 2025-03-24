# Computer Graphics Fractals - Fract-ol 🌀
![frattale](https://github.com/user-attachments/assets/7517bd1e-7847-4c83-a1d3-085f87b9a986)

## Introduction
Fract-ol is a project from the 42 school that aims to explore and visualize fractals using the MiniLibX graphics library. This project will help you understand the basics of graphical programming and introduce you to the beautiful world of fractals.

## Objectives
- Implement and visualize different types of fractals (Mandelbrot, Julia, etc.).
- Use the MiniLibX library for graphical management.
- Allow user interaction (zoom, movement, parameter changes).
- Optimize code for better performance.

## Requirements
- UNIX/macOS system
- MiniLibX installed
- C compiler (GCC or Clang)

(aggiungere comandi su come utilizzare e comandi)

## Index
1) [What are Fractals?](#what-are-fractals)

## What are Fractals?
Imagine you have a drawing of a tree. At the end of those big branches there are smaller branches that look just like the big branches. On the smaller branches, there are even tinier branches that also look like the big branches. No matter which branch you look at, big or small, they all look similar.

A fractal is like that tree: the same pattern keeps showing up, no matter how close or far away you look.

Or, said it better, fractals are infinitely complex patterns that are self-similar across different scales. They are created by repeating a simple process over and over in an ongoing feedback loop. Fractals are found in nature, mathematics, and computer graphics.
![fractals_tree_shutterstock](https://github.com/user-attachments/assets/0a2f20b7-c244-4c7a-83b2-b230e04db566)


## The math of fractals

To understand fractals, having an advanced technical background isn't strictly necessary, but some mathematical knowledge can help you better grasp the concepts. 

The strictly necessary concepts to understand fractals are:

1. **Complex Numbers**  
   Fractals like the Mandelbrot set rely on complex numbers \( c = a + bi \), where \( i \) is the imaginary unit. For this reason, you need to understand the definition of a complex number and its representation (on the Argand-Gauss Plane).

2. **Iteration**  
   A repeated process that calculates a sequence, such as the formula \( z_{n+1} = z_n^2 + c \), to determine if a point is part of the fractal.

4. **Limits and Convergence**  
   Points belonging to fractals should not diverge to infinity but stay "contained" to be part of the fractal. For this reason, you need to understand what a limit is and what convergence and divergence mean in the context of a limit.

 It is also useful to know:
  - **Self-similarity:** The property that fractals look similar at different scales.
  - **Fractal Dimension:** A measure of geometric complexity that can be non-integer.
  - **Chaos Theory:** How small changes in initial conditions can lead to vastly different outcomes.

## The Mandelbrot set

The **Mandelbrot set** is one of the most famous fractals in mathematics and is defined using complex numbers. It is named after **Benoît B. Mandelbrot**, who studied and popularized fractal geometry.

## **Definition**
The Mandelbrot set consists of all complex numbers \( c \) for which the sequence defined by the iterative formula:

\[
z_{n+1} = z_n^2 + c
\]

with \( z_0 = 0 \), **remains bounded** (does not go to infinity).

## **Key Properties**
- If the sequence grows without bound (tends to infinity), the point \( c \) is **not** in the Mandelbrot set.
- If the sequence remains bounded, \( c \) **is** in the Mandelbrot set.
- The boundary of the Mandelbrot set exhibits **infinite complexity** and **self-similarity**, meaning zooming in reveals intricate, repeating patterns.

## **Visual Representation**
When plotted, the Mandelbrot set creates a **beautiful, complex shape** in the complex plane. The set itself is usually black, while the surrounding area is colored based on how quickly the sequence diverges.

## **Connection to Chaos & Fractals**
- The Mandelbrot set is an example of a **fractal**, meaning it shows self-similarity at different scales.
- It exhibits **chaotic behavior**—small changes in \( c \) can result in vastly different behaviors in the iteration.
- Zooming in reveals **infinite detail**, with tiny versions of the Mandelbrot set appearing within itself.

To generate fractals like Mandelbrot, Julia, or Burning Ship, we'll be using the MiniLibX library. This library allows you to create windows, display images, and manage pixels to visualize fractals efficiently.

## Key Steps

### 1. Setup MiniLibX Library
Follow the resources available to set up the MiniLibX library on your project.

### 2. Create Window and Image
Utilize the MiniLibX functions to set up a window and an image to display your fractals.

### 3. Iterate Through Pixels
Loop through each pixel of the window and calculate the corresponding complex number that each pixel represents.

## Fractal Drawing

### Main Function: `draw_fractal`

To generate fractals like Mandelbrot, Julia, or Burning Ship, we'll be using the MiniLibX library. This library allows you to create windows, display images, and manage pixels to visualize fractals efficiently.

## Key Steps

### 1. Setup MiniLibX Library
libX is a collection of libraries that are part of the X Window System, which provides the graphical environment for Unix-based operating systems. These libraries allow applications to create and manage windows, handle events, and render graphics on the screen. However, libX is complex and requires a deep understanding of the X11 system to use effectively.

To simplify graphical programming for students, 42 created MiniLibX. MiniLibX is a lightweight, minimalistic graphics library that abstracts many complexities of libX, making it easier to create windows, draw shapes, and handle basic events. It is specifically designed for educational purposes, allowing students to focus on learning fundamental programming concepts without getting lost in low-level graphical system details.

You can find the MiniLibX repository on GitHub.


### 2. Create Window and Image
Utilize the MiniLibX functions to set up a window and an image to display your fractals.

### 3. Iterate Through Pixels
Loop through each pixel of the window and calculate the corresponding complex number that each pixel represents.

## Fractal Drawing

### Main Function: `draw_fractal`

```c
int draw_fractal(t_fractal *fractal, char *query, double cx, double cy)
```
# Fractal Calculation

## `draw_fractal` Function

The `draw_fractal` function iterates over the pixels on the window and applies the corresponding fractal function (Mandelbrot, Julia, or Burning Ship). It calculates which color to apply based on whether the fractal's mathematical sequence converges or diverges.

## Mandelbrot Set Calculation: `calculate_mandelbrot`

```c
void calculate_mandelbrot(t_fractal *fractal)
```
Set initial variables for the Mandelbrot set. `z` starts at 0 (the beginning of the sequence), and `c` represents the pixel coordinates.  
For performance, use the faster `x * x` instead of `pow(x, 2)`.  
Iterate through the sequence until:
- The absolute value of `z` exceeds a threshold, meaning the sequence diverges.
- The number of iterations exceeds a limit, indicating the sequence may be trapped in a loop.

If the sequence diverges, color the pixel white. If it converges, color the pixel black.

## Julia Set Calculation: `calculate_julia`

This is similar to the Mandelbrot set, but instead of using pixel-based constants, it uses predefined values for `c`. A common example is:

- Real part: `-0.745429`
- Imaginary part: `0.05`

## Burning Ship Set Calculation: `calculate_burning_ship`

```c
void calculate_burning_ship(t_fractal *fractal)
```
This is another variation of the Mandelbrot set but uses the absolute value of the complex number at each step:

```c
z_n+1 = abs(z_n)^2 + c
```
## Color Visualization

If the sequence diverges, we assign a color to the pixel, adjusting its intensity based on the number of iterations. This technique helps highlight the depth of the fractal and makes it visually more engaging.

For psychedelic effects, multiplying the color by the number of iterations can create unique results, especially using vibrant hues like #FCBE11.

Fun Fact:
For a more visually striking output, consider using the British Standard subtitle color #FCBE11, which creates an impressive psychedelic effect when multiplied by the iteration count.




## Sources e approfondimenti

- Video di Oceano sul progetto: 
- Questa repo su github: https://github.com/leogaudin/fract-ol
- Provenienza delle immagini: sito Universita dell'Oregon e theconversation.com

### How to access an element of a struct:

- If you have a **variable** of type `struct`, you use the **dot** operator (`.`) to access its members.
- If you have a **pointer** to a `struct`, you use the **arrow** operator (`->`) to access its members.

### What does the arrow operator (`->`) do?

The **arrow** operator (`->`) is used when you have a pointer to a `struct`. It dereferences the pointer and accesses the member of the `struct` directly. It combines the dereference (`*`) and the dot (`.`) operator in one step.
