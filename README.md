# OpenGL
Final Project

# Description
## main.cpp:
- framebuffer_resize_callback(): Resize windows without effecting objects
- updateInput(): Update Keyboard input
- main(): Create window; Init OpenGL, Shader, Model, Texture, Matrices, Lights; Rendering
## libs.h: Libraries
## Vertex.h: Vertex structure
## vertex_core.glsl:
- main(): Output object's movement
## fragment_core.glsl :
- main(): Output object's color/lighting
## Texture.h: Class
- Texture(): Texture's Constructor loading image with SOIL2
- ~Texture(): Texture's Destructor
## Shader.h: Class
- Shader()&~Shader(): Constructor & Destructor
- setVec2,3,4f(), setMat3,4fv(): Set uniform function
- linkProgram(): link shader to program
- loadShader(): compile shader
## Mesh.h: Class
- initVAO(): Generate, bind, send data of VAO, VBO, EBO
- Mesh() & ~Mesh(): Constructor & Destructor
- setPosition()/setRotation()/setScale(): Modifiers
- move()/rotate()/scaleUp()/render(): Functions
## Primitives: Classes
- class Primitive: set and get Vertices, Indices
- class Cube: inherits Primitive, set vertices & indices coordinates of a Cube. 

# References
- Setup OpenGL's libraries: http://in2gpu.com/2014/10/15/setting-up-opengl-with-visual-studio/
- OpenGL C Tutorial: https://github.com/Headturna/OpenGL-C---Tutorials 
- 3D Model Tutorial: https://www.youtube.com/watch?v=pKJ52fDq6Cw&list=PL6xSOsbVA1eYSZTKBxnoXYboy7wc4yg-Z
