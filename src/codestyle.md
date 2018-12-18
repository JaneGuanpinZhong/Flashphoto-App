Coding style  {#codestyle}
===========

This page is a discussion of the most important rules of coding style
that I enforce within the project. It includes conventions for naming
variables, documenting code, use of namespaces.

## Conventions for naming variables
The names of variables and data members are all lowercase, with
underscores between words. Data members of classes additionally have
trailing underscores.

For example, in the class image_tools::ConvolutionFilterBlur, I use
**radius_** to represent the radius of the kernel. It has an
underscore, and is exactly the word that has the meaning. So it follows
the conventions for naming variables.

Here are some examples depicting the rules better.
![](../../docs/images/e1.png)
![](../../docs/images/e2.png)

## Documenting code
Comments are very important, as they indicate your purposes, and some
relationships between some codes and others. For example, I write "main
purpose" for each class, at the beginning of the head files. Those
sentences imply the basic usage of those classes, which make readers
more comfortable.

However, according to Google C++ Style Guide, "while comments are very
important, the best code is self-documenting. Giving sensible names to
types and variables is much better than using obscure names that you
must then explain through comments." In this project, I tried my best
to make codes self-documenting, so it should be easy to understand them.
[See the codes in details](classes.html).

## Use of namespaces
According to Google C++ Style Guide, namespaces subdivide the global
scope into distinct, named scopes, and so are useful for preventing name
collisions in the global scope. Namespaces should have unique names
based on the project name, and possibly its path.

One small tip: do not add an extra level of indentation.
![](../../docs/images/e3.png)

In this project, I used **image_tools** namespace. I put almost all
classes inside it, except main functions.

It can be very useful when we develop multiple projects where there are
classes with the same name. Namespaces can prevent name conflicts in
large programs while allowing most code to use reasonably short names.

**Citation:** <br/>
- More details can be found at [Google C++ Style
Guide](https://google.github.io/styleguide/cppguide.html) <br/>
- [Materials](https://umn.instructure.com/courses/73375/files?preview=4174164)
from CSci 3081W in Fall 2018 at University of Minnesota, instructed
by Professor Daniel Keefe.

[Go back to Developer Tutorial](@ref devtutorial)
