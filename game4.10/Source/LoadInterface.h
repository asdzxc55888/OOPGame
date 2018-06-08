#pragma once
namespace game_framework {
#define LoadInterface_bg_x 50
#define LoadInterface_bg_y 50
	class LoadInterface
	{
	public:
		LoadInterface();
		~LoadInterface();
		void Initial();
		void OnShow();
		void ShowSave();
		void LoadSaveData();
	private:
		CMovingBitmap bg;   //­I´º¹Ï
		string save_str[5];

	};

}