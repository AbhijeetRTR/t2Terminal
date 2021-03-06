/*
* @author: Praveen Suryawanshi
* @mailto: suryawanshi.praveen007@gmail.com
* please dont remove @author or modify it.
* any changes or bug fixes are done please annotate the locations where bug fixed.
*/

#ifndef _ISCENE_H
#define _ISCENE_H



#include <Windows.h>
#include<stdio.h>
#include <gl/glew.h>
#include<gl/GL.h>
#include<Math.h>
#include "vmath.h"
#include<iostream>
#include "KeyBoard.h"
#include "../OBJLoderUtility/ModelParser.h"

#pragma comment(lib,"glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "OBJLoderUtility.lib")

using namespace vmath;
/*	
	RULE TO IMPLEMENT THE ISCENE

	1. Namespace must be your name with first initial capital in your respective folder
	   eg namspace Praveen

	2. private Variable names must be prefixe with underscore.
	   eg ISCENE *_ptr;

	3. The function need not to be exposed must be in private block.

	4. The function name initial must be capital
	   eg Move();

	5. MUST: In Class Constructor the private variables must be initialise to defaul values
		eg _ptr =NULL

	6. MUST: In Intialize() the respective class variables must be intialize with values.

	7. MUST: In Class Destructor all the variables assigned on heap must be deleted. 
*/



/*REFERENCE FOR HEASER GUARDS
https://en.wikipedia.org/wiki/Include_guard
*/


#define CHECK_NULL(obj){if(obj==NULL){ goto CLEAN_LOCAL_ALLOCATION_BELOW;}} 
//#define SAFE_DELETE(obj){if(obj){delete obj;obj=NULL;}}

#define SAFE_LOG(FMT,TEXT){FILE *fp = NULL;fopen_s(&fp, "GL_LOG.txt", "a+");if(fp){fprintf(fp,FMT,TEXT);fclose(fp);fp=NULL;}}

#define SAFE_SCENE_DELETE(scene) {if (scene!=NULL){scene->UnInitialize(); /*delete scene*/;scene = NULL;}}

#define SCENE_AIRPORT				0
#define SCENE_TERRAIN_MAP			1
#define SCENE_SINGLE_AEROPLANE		2
#define SCENE_TOP_VIEW				3
#define SCENE_AIRPORT_MODEL			4
#define SCENE_CYLINDER_TRANS		5
#define SCENE_CYLINDER_TEXCOORD		6
#define SCENE_COUNT					SCENE_CYLINDER_TEXCOORD + 1

#define TRANSFORMATION_SINGLE_AEROPLANE_1	1
#define TRANSFORMATION_SINGLE_AEROPLANE_2	2
#define TRANSFORMATION_SINGLE_AEROPLANE_3	3
#define TRANSFORMATION_TOP_VIEW_1			4
#define TRANSFORMATION_TOP_VIEW_2			5
#define TRANSFORMATION_TOP_VIEW_3			6

namespace T2Terminal
{
	enum SCENE_NUMBER
	{
		MAIN,
		SCENE_1,
		SCENE_2,
		SCENE_3,
	};

	class IScene
	{

	public:
		struct Attributes
		{
			float translateCoords[SCENE_COUNT][3];
			float rotateCoords[SCENE_COUNT][3];
			int currentScene;
			int numSpotLight;
			int currentTransformation;
		};

		struct ResizeAttributes
		{
			float farValue;
			float nearValue;
		};

		static IScene* GetInstance(SCENE_NUMBER scene);

		virtual BOOL SceneHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) = 0;

		virtual void Initialize()= 0;

		virtual void Update() = 0;

		virtual void ReSize(int width, int height, struct ResizeAttributes attributes) = 0;

		virtual void Render(HDC hdc, struct Attributes attributes) = 0;

		virtual void SceneTransition() = 0;

		virtual void UnInitialize() = 0;
		
	};

}

#endif
