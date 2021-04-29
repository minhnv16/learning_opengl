# OBJS specifies which files to compile as part of the project
OBJS = Main.cpp Learn0.cpp Source0_sample_draw_aray_triangle.cpp Source1_sample_draw_element_triangle.cpp Source2_sample_drawing_triangle_index.cpp

# CC specifies which compiler we're using
CC = g++ -std=c++11

# COMPILER_FLAGS specifies the additional compilation options we're using
# -Wall will turn on all standard warnings
COMPILER_FLAGS = -Wall

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lGL -lGLU -lglut -lGLEW -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = sample

#This is the target that compiles our executable
all: $(OBJS)
        $(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
