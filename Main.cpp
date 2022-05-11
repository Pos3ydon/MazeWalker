#include <windows.h>
#include <iostream>


#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#pragma comment(lib, "glew32.lib")

#ifdef GLEW_STATIC
#  define GLEWAPI extern
#else
#  ifdef GLEW_BUILD
#    define GLEWAPI extern __declspec(dllexport)
#  else
#    define GLEWAPI extern __declspec(dllimport)
#  endif
#endif fdadfaf




int main() {
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(600, 400, "hello OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}



	const GLfloat vertices[] = {
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	const GLuint indices[] = {
		0, 1, 2
	};

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	char const* vertexShaderSrc =
		"#version 300 es\n"
		"precision mediump float;\n"
		"in vec2 position;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(position, 0.0, 1.0);}n"
		"}";
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	char const* fragmentShaderSrc =
		"#version 300 es\n"
		"precision mediump float;\n"
		"out vec4 outColor;\n"
		"void main()\n"
		"{\n"
		"	outColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"}";
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);


	GLint positionAttribute = glGetAttribLocation(shaderProgram, "position");
	glDisableVertexAttribArray(positionAttribute);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);

	glfwTerminate();
}




//#include <windows.h>
//
//
//
//HWND  windowHandle = nullptr;
//
//
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//	switch (uMsg) {
//		case WM_CLOSE:
//			PostQuitMessage(0);
//			break;
//		case WM_CHAR:
//			switch (wParam) {
//				case VK_ESCAPE:
//					SendMessage(hwnd, WM_CLOSE, 0, 0);
//					break;
//			}
//		default:
//			break;
//	}
//
//	return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}
//
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//	WNDCLASSEX windowClass;
//	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
//
//	windowClass.cbSize = sizeof(WNDCLASSEX);
//	windowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
//	windowClass.lpfnWndProc = WindowProc;
//	windowClass.hInstance = hInstance;
//	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
//	windowClass.lpszClassName = L"WindowClass";
//
//	RegisterClassEx(&windowClass);
//
//
//	windowHandle = CreateWindowEx(
//		NULL, 
//		L"WindowClass", 
//		L"Hallo World", 
//		WS_VISIBLE, 
//		0, 
//		0, 
//		400, 
//		200, 
//		NULL, 
//		NULL, 
//		hInstance, 
//		NULL
//	);
//
//	if (windowHandle == nullptr) {
//		DWORD errVal = GetLastError();
//	}
//
//
//
//	MSG msg;
//
//	while (true) {
//		PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
//		if (msg.message == WM_QUIT)
//			break;
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//}