#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    GLuint ID;
} Shader;

static char* shader__read_file(const char* filepath) {
    FILE* file = fopen(filepath, "rb");
    if (!file) {
        fprintf(stderr, "ERROR: Cannot open file %s\n", filepath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        fprintf(stderr, "ERROR: Memory allocation failed for %s\n", filepath);
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

static void shader__check_errors(GLuint object, const char* type) {
    GLint success;
    char infoLog[1024];
    if (strcmp(type, "PROGRAM") == 0) {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR: Program Linking Failed\n%s\n", infoLog);
        }
    } else {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR: Shader Compilation Failed (%s)\n%s\n", type, infoLog);
        }
    }
}

static int shader_create(Shader* shader, const char* vertex_path, const char* fragment_path) {
    char* v_source = shader__read_file(vertex_path);
    char* f_source = shader__read_file(fragment_path);

    if (!v_source || !f_source) {
        free(v_source);
        free(f_source);
        return 0;
    }

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const char**)&v_source, NULL);
    glCompileShader(vertex);
    shader__check_errors(vertex, "VERTEX");

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const char**)&f_source, NULL);
    glCompileShader(fragment);
    shader__check_errors(fragment, "FRAGMENT");

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    shader__check_errors(program, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    free(v_source);
    free(f_source);

    shader->ID = program;
    return 1;
}

static void shader_use(const Shader* shader) {
    glUseProgram(shader->ID);
}

static void shader_delete(Shader* shader) {
    glDeleteProgram(shader->ID);
    shader->ID = 0;
}

static void shader_set_bool(const Shader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

static void shader_set_int(const Shader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

static void shader_set_float(const Shader* shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader->ID, name), value);
}

static void shader_set_vec3(const Shader* shader, const char* name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(shader->ID, name), x, y, z);
}

static void shader_set_mat4(const Shader* shader, const char* name, const float* mat4) {
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, name), 1, GL_FALSE, mat4);
}

#endif // SHADER_H

