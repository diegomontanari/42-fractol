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


## Sources e approfondimenti

- Video di Oceano sul progetto: 
- Questa repo su github: https://github.com/leogaudin/fract-ol
- Provenienza delle immagini: sito Universita dell'Oregon e theconversation.com
