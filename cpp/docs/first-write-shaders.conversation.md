# First write shaders

My conversation with ChatGPT.

## Conversation

```txt
do the game engines commit shaders along other code? or are shaders stored in database? or what?

It depends on the game engine and how it's designed. Some game engines may embed the shader code directly in the game executable or package it as a resource file along with other game assets, while others may load the shader code dynamically at runtime from external files.

In general, it's good practice to keep the shader code separate from the rest of the game code, so that it can be modified and iterated on more easily. Some game engines may use a version control system like Git to manage the shader code, while others may use a database or other repository for storage.

Game engines that use a plugin architecture may also allow developers to create and share custom shaders as plugins, which can be loaded dynamically at runtime. In this case, the plugin may contain the shader code and any associated assets, and the game engine would load the plugin and its shaders as needed.

Srećko Kostić

so assets such as meshes are provided as plugins to game engine? as an expert, accoding to you knowledge, what is the most common way for game engine to use shaders

The most common way for game engines to use shaders is to have them as source code files in the project directory, along with other game code. Typically, the shader source code is compiled at runtime or during the build process into a binary format that is optimized for the target graphics hardware. This compiled binary is then loaded into the graphics card's memory and used for rendering.

Game engines may also provide tools for editing and previewing shaders within the engine, allowing developers to see the effects of changes to the shader code in real-time. Additionally, some engines may provide built-in shader libraries or shader assets that can be imported into a project, allowing developers to use pre-made shaders for common rendering tasks.

Srećko Kostić

do you have access to shaders used by unreal engine? show me

As an AI language model, I don't have direct access to the code or shaders used by Unreal Engine. However, you can find the shader code used by Unreal Engine on their official GitHub repository, which is publicly accessible. Keep in mind that the shader code for Unreal Engine is complex and may require a good understanding of graphics programming to understand and modify.

on github i saw a library of shaders, why are such libraries usefull? there are vertex and fragment shaders

Shader libraries can be very useful for game developers and other graphics programmers who want to quickly prototype or develop new graphical effects. By using existing shader code from a library, developers can save time and effort in creating custom shaders from scratch.

Shader libraries may also contain optimized code that has been tested and verified to work well on a range of hardware and software configurations, which can help ensure that the graphics code will run smoothly and efficiently.

The fact that the library contains both vertex and fragment shaders is also useful, as these are the two most common types of shaders used in modern graphics pipelines. The vertex shader is responsible for processing individual vertices in a mesh, while the fragment shader processes each pixel of the final image. Having access to a wide range of pre-written vertex and fragment shaders can be very helpful in speeding up the development process and making it easier to experiment with different visual effects.

Srećko Kostić

that looks cool as hell

Glad you think so! Shaders are a powerful tool for creating visual effects in graphics applications. There are many libraries of shaders available online that can be used as starting points or inspiration for your own projects. They can help you learn how to create certain effects, and can also save you time and effort in developing your own shaders from scratch.

Srećko Kostić

so a materials can be described through shaders and we can attach material through shaders on to the plain mesh?

Yes, that's correct! Shaders define how a material should look and behave, and they can be applied to a mesh to create a unique visual appearance. By combining different shaders with different settings, you can create a wide variety of materials, from simple diffuse materials to complex ones with reflections, refractions, and other advanced effects.

Srećko Kostić

so, whoever writes a shader, he needs to specify what uniforms and attributes he needs, so the user of the shader can provide those to the shader?

Yes, that's correct. When a shader is written, the programmer needs to specify what inputs (attributes) and outputs (varyings) the shader needs, as well as any constants (uniforms) that the shader requires. These inputs, outputs, and constants need to be defined and provided to the shader by the user of the shader, such as the game engine or application that is using the shader. This ensures that the shader has the necessary data to execute properly.

Srećko Kostić

so we first define a shader and after that we provide data to the shader?

Yes, that's correct. First, you define the shader program with its attributes, uniforms, and fragment and vertex shaders. Then, you provide the data to the shader program, such as the vertex and index data, and the values for the uniforms. Finally, you bind the shader program and issue draw calls to render the scene.

Srećko Kostić

what if we do not provide the data, we get an error i assume?

Yes, if the required data is not provided to the shader, the program will encounter an error. This could happen in various scenarios, such as:

    If you fail to bind the required buffer object before calling glDrawArrays or glDrawElements, you will get an error.
    If you try to access a uniform variable that has not been initialized with a value, you will get an error.
    If you try to access an attribute variable that has not been enabled or has not been bound to the correct buffer object, you will get an error.

In general, it is important to carefully follow the requirements of the shader program and provide all the required data before using it in your OpenGL application to avoid these errors.
```
