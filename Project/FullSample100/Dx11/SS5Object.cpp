#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\�z
	SS5Object::SS5Object(const shared_ptr<Stage> stageptr,const wstring& BaseDir,const wstring FileName,const wstring FirstAnim):
	SS5ssae(stageptr,BaseDir,FileName,FirstAnim){

	}
	//�j��
	SS5Object::~SS5Object() {

	}
	//����
	void SS5Object::OnCreate() {

	}
}