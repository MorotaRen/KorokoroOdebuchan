#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//ç\íz
	SS5Object::SS5Object(const shared_ptr<Stage> stageptr,const wstring& BaseDir,const wstring FileName,const wstring FirstAnim):
	SS5ssae(stageptr,BaseDir,FileName,FirstAnim){

	}
	//îjä¸
	SS5Object::~SS5Object() {

	}
	//ê∂ê¨
	void SS5Object::OnCreate() {

	}
}