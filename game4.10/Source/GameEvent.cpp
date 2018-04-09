#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameEvent.h"
namespace game_framework {
	void ChoseEvent(GameEvent_number event)
	{
		switch (event)
		{
		case game_framework::MonsterGohome_eventNumber:
			//MonsterGohome_event(Room *_room);
			break;
		default:
			break;
		}
	}
	void MonsterFindHouse(Monster **_monster, int TaskBoard_x, int TaskBoard_Width) //怪物找房
	{
		if (Moving(_monster,TaskBoard_x+60,0)) {
			(*_monster)->SetMovingType(Back);
			(*_monster)->SetMonsterState(findHouse);
		}
		
	}
	void MonsterlivingHouse_event(Room *_room,Monster **_monster) {
		_room->SetMonsterlivingRoom(_monster);
		MonsterGohome_event(_room);
	}
	void MonsterGohome_event(Room *_room)
	{
		_room->LetMonsterGohome();
	}
	void MonsterBeingClick(Monster **_monster,int room_size,Room **gameroom)
	{
		Monster_state nowState=(*_monster)->GetMonsterState();
		switch (nowState)
		{
		case game_framework::wolking:

			break;
		case game_framework::findHouse:                   //同意怪物住進防屋
			for (int i = 0; i < room_size; i++) {
				if (!(gameroom)[i]->GetIsMonsterLiving()) {  //沒怪物住的話就分配到那間房
					MonsterlivingHouse_event((gameroom)[i], _monster);
					
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	bool MonsterLeave(Monster ** _monster) //已經離開回傳true
	{
		if (Moving(_monster, -100, 0)) {
			DeleteMonster_event(_monster);
			return true;
		}
		return false;
	}
	bool Moving(Monster **_monster, int x, int floor)
	{
		if ((*_monster)->GetFloor() == floor) {
			if ((*_monster)->GetX() > x+40) {
				(*_monster)->SetMovingLeft(true);
			}
			else if ((*_monster)->GetX() <= x-40) {
				(*_monster)->SetMovingRight(true);
			}
			else {
				(*_monster)->SetMovingLeft(false);
				(*_monster)->SetMovingRight(false);
				return true;
			}
		}
		return false;
	}
	void AttackWarrior(Monster *_monster,Warrior * _warrior)
	{
		if (_warrior->GetX() > _monster->GetX()) {
			_monster->SetMovingType(Attack_Right);
		}
		else {
			_monster->SetMovingType(Attack_Left);
		}
		_warrior->BeingAttack(_monster->GetAttackPower(), _monster->GetAttackType());
	}
	bool HitWarrior(Monster *_monster,Warrior *_warrior)
	{
		return _monster->HitRectangle(_warrior->GetX(), _warrior->GetY(), _warrior->GetX() + _warrior->GetWidth(), _warrior->GetY() - _warrior->GetHeight());
	}
	void CreateMonster_event(Monster **_monster) {
			int result = 0;
			result = rand() % 1000;
			if (result < 20) {
				(*_monster) = new Monster();
				(*_monster)->LoadBitmap((*_monster)->GetMonsterType());
				(*_monster)->SetMonsterIsExist(true);
				(*_monster)->SetMonsterState(nothing);
				(*_monster)->SetPoint(-100, 530);
			}
		
	}
	void DeleteMonster_event(Monster ** _monster)
	{
		if ((*_monster) != NULL) {
			delete *_monster;
			(*_monster) = NULL;
		}
	}
	
	bool Moving(Warrior ** _warrior, int x, int floor)
	{
		if ((*_warrior)->GetFloor() == floor) {
			if ((*_warrior)->GetX() > x + 10) {
				(*_warrior)->SetMovingLeft(true);
				(*_warrior)->SetMovingRight(false);
			}
			else if ((*_warrior)->GetX() <= x - 10) {
				(*_warrior)->SetMovingRight(true);
				(*_warrior)->SetMovingLeft(false);
			}
			else {
				(*_warrior)->SetMovingLeft(false);
				(*_warrior)->SetMovingRight(false);
				return true;
			}
		}
		return false;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void CreateWarrior_event(Warrior ** _warrior,warrior_type type)
	{
		(*_warrior) = new Warrior(type);
		(*_warrior)->SetPoint(-100, 540);
	}
	void AttackMonster(Warrior * _warrior, Monster * _monster)
	{
		if (_monster->GetX() >_warrior->GetX()) {
			_warrior->SetMovingType(Attack_Right);
		}
		else {
			_warrior->SetMovingType(Attack_Left);
		}
		_monster->BeingAttack(_warrior->GetAttackPower(), _warrior->GetAttackType());
	}
	bool HitMonster(Warrior * _warrior, Monster *_monster)
	{
		return _warrior->HitRectangle(_monster->GetX(), _monster->GetY(), _monster->GetX() + _monster->GetWidth(), _monster->GetY() - _monster->GetHeight());
	}
	Monster * findMonsterTarget(Warrior * _warrior, Room **gameroom, int room_size)
	{
		Monster* result = NULL;
		int minX=9999;
		for (int i = 0; i < room_size; i++) {
			if (gameroom[i] ->GetIsMonsterLiving()&&abs(_warrior->GetX() - (gameroom[i]->GetLiveMonster())->GetX()) < minX) {
				minX = abs(_warrior->GetX() - (gameroom[i]->GetLiveMonster())->GetX());
				result = (gameroom[i]->GetLiveMonster());
			}
		}
		return result;
	}
	Warrior * findWarriorTarget(Monster *_monster, Warrior ** _warrior)
	{
		Warrior* result = NULL;
		int minX = 9999;
		for (int i = 0; i<10; i++) {
			if (_warrior[i]!=NULL&&abs(_monster->GetX()- _warrior[i]->GetX()) < minX) {
				minX = abs(_monster->GetX() - _warrior[i]->GetX());
				result = _warrior[i];
			}
		}
		return result;
	}
	void WarriorAdAttack(Warrior * _warrior, Monster _monster)
	{
		
	}
	
	void BattleTest1(Warrior ** _warrior,bool &isIntoBattle, Room **gameRoom)
	{
		isIntoBattle = true;
		CreateWarrior_event(&_warrior[0],villager);
	}
}