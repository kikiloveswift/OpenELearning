//
//  main.cpp
//  OpenGLLearning
//
//  Created by konglee on 2019/10/5.
//  Copyright © 2019 konglee. All rights reserved.
//
#include <iostream>
#include "GLShaderManager.h"
#include "GLTools.h"
#include <GLUT/GLUT.h>
//#include<glut/glut.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

/// 着色管理器
GLShaderManager shaderManager;

/// 批次处理工具
GLBatch batch;

/// 三角形批次处理工具
GLTriangleBatch triangleBath;

// 窗口尺寸变化
void changeSize(int w, int h);

// 渲染屏幕
void renderScene();

// 键盘回调
void keyboardPress(unsigned char key, int x, int y);

//extern void APIENTRY glutKeyboardFunc(void (*func)(unsigned char key, int x, int y)) OPENGL_DEPRECATED(10_0, 10_9);


// 创建
void setupRC();

int main(int argc, char *argv[]) {
    // 初始化 GLUT
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle");
    
    // 注册回调函数
    // 窗口改变函数
    glutReshapeFunc(changeSize);
    
    // 注册键盘点击函数
    glutKeyboardFunc(keyboardPress);
    
    // 窗口开始绘图
    glutDisplayFunc(renderScene);
    
    GLenum err = glewInit();
    
    if (err != GLEW_OK) {
        printf("驱动程序初始化异常");
        return 1;
    }
    
    setupRC();
    
    glutMainLoop();
    return 0;
}

void setupRC() {
    
    // 设置背景颜色
    glClearColor(0.f, 0.f, 0.f, 1.f);
    
    // 初始化着色管理器
    shaderManager.InitializeStockShaders();
    
    // 设置顶点数组
    GLfloat vArrs[] = {
        0.f, 0.5f, 0.f,
        -0.5f, 0.f, 0.f,
        0.5f, 0.f, 0.f
    };
    
    // 三角形批次处理
    
    batch.Begin(GL_TRIANGLES, 3);
    batch.CopyVertexData3f(vArrs);
    batch.End();
    
    /// 三角形批次处理工具 最多使用 200 个顶点数
    triangleBath.BeginMesh(200);
    
    /// 添加 3 个顶点 3个法线 3个纹理坐标的数组
//    triangleBath.AddTriangle(<#M3DVector3f *verts#>, <#M3DVector3f *vNorms#>, <#M3DVector2f *vTexCoords#>)
    
    triangleBath.End();
    
    /// 在 renderScene 的时候调用 triangles.Draw()
}


void changeSize(int w, int h) {
    glViewport(0, 0, w, h);
}

void renderScene() {
 
    /// 清除一个或者特定的缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    GLfloat vRed[] = {1.f, 0.f, 0.f, 1.f};
    
    /// 传递到存储着色器，也就是 GLT_SHADER_IDENTITY 着色器, 这个着色器是以笛卡尔坐标系上渲染几何图形
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    
    /// 提交着色器
    batch.Draw();
    
    /// 后台缓冲区进行渲染，然后结束的时候交换到前台
    glutSwapBuffers();
    
}

// 点击键盘
void keyboardPress(unsigned char key, int x, int y) {
    std::cout << "key = " << key << " x = " << x << " y = " << y << std::endl;
}





#pragma clang diagnostic pop
