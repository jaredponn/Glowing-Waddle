# set the compiler to clang first
# export CC=/usr/bin/clang

project('Glowing Waddle', 'c',
 default_options : ['c_std=c11'] )

srcs = [ 'src/main.c'
       , 'src/program.c'
       , 'src/scene.c'
       , 'src/vertex_types.c'
       , 'src/geometry.c'
       , 'src/shader_tools.c'
       , 'src/renderer.c'
       , 'extern/glad/src/glad.c'
       ]

executable('Glowing Waddle'
        , srcs
        , c_args : ['-Wall', '-Wextra', '-O2']
        , link_args : ['-lm', '-lglfw', '-lGL', '-ldl', '-lSOIL'] )
