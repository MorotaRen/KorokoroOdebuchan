#pragma once

#include "stdafx.h"

namespace basecross{
	class SS5Object : public SS5ssae {
	public:
		//\’z
		SS5Object(const shared_ptr<Stage> stageptr, const wstring& BaseDir, const wstring FileName, const wstring FirstAnim);
		//”jŠü
		~SS5Object();
		//‰Šú‰»
		virtual void OnCreate() override;

	};
}