# First write shaders

Shaders are apparently like functions! Or at last that makes it easier for me to see them... First define a shader's behavior, then provide the data it needs!

## Story

I was thinking whether shaders are committed with game engine code or where else. I first looked up on [Hazel Engine](https://github.com/TheCherno/Hazel/tree/master/Hazel/src/Hazel/Core) GitHub and didn't have luck finding any.

Then I did a quick Google search `threejs shaders` and I found [threejs-shader-materials](https://github.com/MasatoMakino/threejs-shader-materials). I saw that some classes provide names for uniforms and attributes _(i think?)_. That made me think... do we first define a shader and provide the data to it after? I mean... shader requires uniforms and attributes and what not... since it **requires** them, then it makes sense to provide them?

We also can change shaders as we need to, we recompile the shader program when we do that... In a way I could imagine shaders as functions that require parameters to do some things.

After that I saw the example of `threejs-shader-materials` where it imports something and provides it to the `threejs` library. It provides shader to a mesh... Now that was quite a new way to see shaders!

I had to document findings for later referral.

I went on to ask ChatGPT about these things, looks like it confirmed some of my thoughts.

[My conversation with ChatGPT](./first-write-shaders.conversation.md)
