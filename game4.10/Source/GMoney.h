#pragma once
namespace game_framework {
#define Money_x 280
#define Money_y 630
	class GMoney
	{
	public:
		GMoney();
		~GMoney();
		void Initial();
		void OnShow();
		void OnMove();
		void SetValue(int _value);
		int  GetValue();

	private:
		int x, y;
		int value;
		int GetDigit(int x);
		CInteger *money;
	};
}
