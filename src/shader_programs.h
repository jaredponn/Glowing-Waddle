#pragma once
#include <stddef.h>

#define SHADER_CODE(val) #val

// clang-format off
static const char *const defaultVertexShader = 
        "#version 410 \n"
        SHADER_CODE(
                // location indices for these attributes correspond to those specified in the
                // InitializeGeometry() function of the main program
                layout(location = 0) in vec3 VertexPosition;
                layout(location = 1) in vec3 VertexColour;
                
                // output to be interpolated between vertices and passed to the fragment stage
                out vec3 Colour;
                
                void main()
                {
                    // assign vertex position without modification
                    gl_Position = vec4(VertexPosition.xy, 0.0, 1.0);
                
                    // assign output colour to be interpolated
                    Colour = VertexColour;
                }
        );

static const char *const defaultGeometryShader = NULL;

static const char *const defaultFragmentShader = 
        "#version 410\n" 
        SHADER_CODE(
                // interpolated colour received from vertex stage
                in vec3 Colour;
                
                // first output is mapped to the framebuffer's colour index by default
                out vec4 FragmentColour;
                
                void main(void)
                {
                    // write colour output without modification
                    FragmentColour = vec4(Colour, 0);
                }
        );

// clang-format on
#undef SHADER_CODE
