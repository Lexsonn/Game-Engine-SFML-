#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

#define CREATE_MAP false;	// true to create map, false to test created map.

#define _object tuple<int, int, int, int>			//	1
#define _entity tuple<int, string, float, float>	//	2
#define __entity tuple<int, string, float, float	// *********************** GENERIC ***********************
#define _bound tuple<float, float, float, float>	// 3rd bit 0x00000004 (AI bounded objects)
#define _rel  unsigned short int					// 4th bit 0x00000008 (stuff like buttons, levers, etc.)
#define _name string								// 5th bit 0x00000010 (named entities)

using namespace std;

int main() {
	bool create = CREATE_MAP;
	string op = "";

	vector<vector<int>> levels;			// list of level size/tile data to include in mapfile
	vector<int> tilesets;
	vector<vector<_entity>> entities;	// list of entities to include in each level
	vector<vector<_object>> objects;	// list of objects to include in each level
	vector<long> mapsize;				// metadata to keep track of # of levels and filesize

	/******************************************** SPECIAL LIST TYPE BIT OPERATIONS ********************************************\
	*																														  *
	*	First int in the generic tuple __entity specifies what information is written:										  *
	*																														  *
	*	Bit 1 & 2:	Reserved for collidable and generic Entity																  *
	*	Bit 3:		(0x00000004) Bounded AI entities. consists of 4 floats.													  *
	*	Bit 4:		(0x00000008) Relational entities tied to another entity by ID.											  *
	*	Bit 5:		(0x00000010) Specially Named entities.																	  *
	*																														  *
	\**************************************************************************************************************************/

	vector<vector<__entity, _bound, _rel, _name>>> specialList;	// All the non-default specific cases go here. 

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////// LEVELS //////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (create) {

		levels.push_back({ 5, 5,
			4,  4,  4,  4,  4,
			5,  5,  5,  5,  5,
			5,  5,  5,  5,  5,
			5,  5,  5,  5,  5,
			19, 19, 19, 19, 19
		});
		levels.push_back({ 25, 25,
			0,  4,  8,  4,  4,  4,  8,  12, 0,  4,  4,  4,  8,  0,  4,  8,  0,  1,  2,  3,  4,  5,  6,  7,  1,
			1,  5,  9,  5,  5,  5,  9,  12, 1,  5,  5,  5,  9,  1,  5,  9,  8,  9,  10, 11, 12, 13, 14, 15, 1,
			2,  6,  10, 5,  5,  5,  9,  12, 1,  5,  5,  5,  9,  1,  5,  9,  16, 17, 18, 19, 20, 21, 22, 23, 1,
			1,  5,  5,  5,  5,  5,  9,  12, 1,  5,  5,  5,  9,  1,  5,  9,  23, 23, 23, 23, 23, 23, 23, 23, 1,
			1,  5,  5,  5,  17, 6,  10, 12, 2,  6,  6,  6,  10, 2,  16, 9,  23, 23, 23, 23, 23, 23, 23, 23, 1,
			1,  5,  5,  5,  9,  12, 12, 12, 13, 13, 13, 13, 13, 14, 2,  10, 23, 23, 23, 23, 23, 23, 23, 23, 1,
			2,  6,  6,  6,  10, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 14, 23, 23, 23, 23, 23, 23, 23, 23, 1,
			12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 14, 23, 23, 23, 23, 23, 23, 23, 23, 1,
			12, 12, 12, 12, 12, 12, 12, 0,  4,  4,  4,  8,  14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,
			12, 12, 12, 12, 12, 12, 12, 1,  5,  5,  5,  9,  14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,
			12, 12, 12, 12, 12, 12, 12, 1,  5,  5,  5,  18, 8,  13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,
			12, 12, 12, 12, 12, 12, 12, 1,  5,  5,  5,  5,  9,  13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,
			12, 12, 12, 12, 12, 12, 12, 1,  5,  5,  5,  5,  9,  13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 1,
			12, 12, 12, 12, 12, 12, 12, 2,  6,  6,  6,  6,  10, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 1,
			12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 1,
			12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 1,
			4,  4,  4,  4,  4,  4,  8,  13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 0,  8,
			5,  5,  5,  5,  5,  5,  18, 4,  4,  8,  13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,  9,
			5,  5,  5,  5,  5,  5,  5,  5,  5,  18, 4,  4,  4,  4,  4,  4,  4,  4,  4,  8,  14, 14, 14, 1,  9,
			5,  5,  17, 6, 16,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  18, 4,  4,  4,  1,  9,
			5,  5,  9,  3,  1,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  1,  9,
			5,  5,  18, 4,  15, 5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  1,  9,
			5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  1,  9,
			5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  1,  9,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 2,  10
		});
		levels.push_back({ 10, 8,
			0,  4,  4,  4,  4,  4,  4,  4,  4,  8,
			1,  5,  5,  5,  5,  17, 6,  6,  16, 9,
			1,  5,  5,  5,  5,  9,  3,  3,  1,  9,
			1,  5,  5,  5,  5,  9,  3,  3,  1,  9,
			1,  5,  5,  5,  5,  9,  3,  3,  1,  9,
			1,  5,  5,  5,  5,  18, 4,  4,  15, 9,
			2,  6,  6,  6,  6,  6,  6,  6,  6,  10,
			12, 12, 12, 12, 12, 12, 12, 13, 13, 13
		});

		tilesets.push_back(0);
		tilesets.push_back(0);
		tilesets.push_back(0);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////// ENTITIES AND OBJECTS ///////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		vector<_entity> eList;
		vector<_object> oList;

		eList.push_back(_entity(2, "Player", 20.f, 20.f));

		eList.push_back(_entity(2, "Slime", 100.f, 100.f));
		eList.push_back(_entity(2, "BabySlime", 100.f, 160.f));
		eList.push_back(_entity(2, "BabySlime", 160.f, 100.f));
		eList.push_back(_entity(2, "Slime", 160.f, 160.f));

		oList.push_back(_object(0, 0, 200, 20));
		oList.push_back(_object(0, 0, 20, 200));
		oList.push_back(_object(0, 180, 200, 20));
		oList.push_back(_object(180, 0, 20, 200));

		entities.push_back(eList); objects.push_back(oList); //////////////////////////////////////////////////////////////////////
		eList.clear(); oList.clear(); /////////////////////////////////////////////////////////////////////////////////////////////

		eList.push_back(_entity(2, "Player", 200.f, 200.f));

		eList.push_back(_entity(2, "Slime", 100.f, 100.f));
		eList.push_back(_entity(2, "Slime", 50.f, 100.f));
		eList.push_back(_entity(2, "Slime", 150.f, 100.f));
		eList.push_back(_entity(2, "Slime", 200.f, 100.f));
		eList.push_back(_entity(2, "Slime", 250.f, 100.f));
		eList.push_back(_entity(2, "Slime", 300.f, 100.f));
		eList.push_back(_entity(2, "Slime", 140.f, 140.f));
		eList.push_back(_entity(2, "Slime", 140.f, 40.f));
		eList.push_back(_entity(2, "Slime", 250.f, 140.f));
		eList.push_back(_entity(2, "Slime", 300.f, 140.f));
		eList.push_back(_entity(2, "Slime", 190.f, 250.f));
		eList.push_back(_entity(2, "Slime", 340.f, 340.f));

		eList.push_back(_entity(2, "BabySlime", 300.f, 200.f));
		eList.push_back(_entity(2, "BabySlime", 300.f, 220.f));
		eList.push_back(_entity(2, "BabySlime", 300.f, 240.f));
		eList.push_back(_entity(2, "BabySlime", 300.f, 260.f));
		eList.push_back(_entity(2, "BabySlime", 320.f, 200.f));
		eList.push_back(_entity(2, "BabySlime", 320.f, 220.f));
		eList.push_back(_entity(2, "BabySlime", 320.f, 240.f));
		eList.push_back(_entity(2, "BabySlime", 320.f, 260.f));
		eList.push_back(_entity(2, "BabySlime", 340.f, 200.f));
		eList.push_back(_entity(2, "BabySlime", 340.f, 220.f));
		eList.push_back(_entity(2, "BabySlime", 340.f, 240.f));
		eList.push_back(_entity(2, "BabySlime", 340.f, 260.f));

		oList.push_back(_object(370, 140, 40, 240));
		oList.push_back(_object(80, 290, 210, 20));
		oList.push_back(_object(140, 270, 60, 60));

		entities.push_back(eList); objects.push_back(oList); //////////////////////////////////////////////////////////////////////
		eList.clear(); oList.clear(); /////////////////////////////////////////////////////////////////////////////////////////////

		eList.push_back(_entity(2, "Player", 100.f, 100.f));

		oList.push_back(_object(0, 0, 380, 20));
		oList.push_back(_object(380, 0, 20, 240));

		entities.push_back(eList); objects.push_back(oList); //////////////////////////////////////////////////////////////////////
		eList.clear(); oList.clear(); /////////////////////////////////////////////////////////////////////////////////////////////

		// Create mapsize for finding positions of map data.
		long fsize = 0;
		for (int i = 0; i < levels.size(); i++) {
			fsize += sizeof(int);
			fsize += (levels.at(i).at(0) * levels.at(i).at(1) + 2) * sizeof(int);
			fsize += sizeof(int);
			for (auto entity : entities.at(i)) {
				fsize += sizeof(std::get<0>(entity));
				string name = std::get<1>(entity);
				size_t slen = strlen(name.c_str());
				fsize += sizeof(slen);
				fsize += slen;
				fsize += sizeof(std::get<2>(entity));
				fsize += sizeof(std::get<3>(entity));
			}
			for (auto object : objects.at(i)) {
				fsize += sizeof(int);
				fsize += sizeof(std::get<0>(object));
				fsize += sizeof(std::get<1>(object));
				fsize += sizeof(std::get<2>(object));
				fsize += sizeof(std::get<3>(object));
			}

			mapsize.push_back(fsize);
			std::cout << "mapsize after level " << i << ": " << mapsize.at(mapsize.size() - 1) << "\n";
		}

		for (int i = 0; i < mapsize.size(); i++) 
			mapsize.at(i) += mapsize.size()*sizeof(long) + sizeof(int);

		for (long i : mapsize)
			std::cout << i << ' ';

		std::cout << "Done testing levels\n";
	}

	//////////////////////////////////////////////// NO NEED TO TOUCH PAST HERE ////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////// WRITE ///////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (create) {
		ofstream mapfile("mapfile/map.vhmap", ios::binary | ios::trunc);
		std::cout << "writing to file...\n";

		int s = mapsize.size();
		mapfile.write((char*)&s, sizeof(int)); std::cout << s << " ";
		mapfile.write((char*)mapsize.data(), s*sizeof(long));

		for (int i = 0; i < mapsize.size(); i++) std::cout << mapsize.at(i) << " ";
		std::cout << "\n";		

		for (int i = 0; i < levels.size(); i++) {
			const int size = levels.at(i).at(0) * levels.at(i).at(1) + 2;
			vector<int> level(levels.at(i));
			std::cout << "\n**** LEVEL " << i << " ****\n\n";
			mapfile.write((char*)&size, sizeof(int)); std::cout << size << " ";
			mapfile.write((char*)&level[0], size*sizeof(int));
			mapfile.write((char*)&tilesets.at(i), sizeof(int));

			for (int j = 0; j < size; j++) std::cout << levels.at(i).at(j) << " ";
			std::cout << "tileset=" << tilesets.at(i) << '\n';

			for (auto entity : entities.at(i)) {
				int toDo = std::get<0>(entity);
				mapfile.write((char*)&toDo, sizeof(int));	std::cout << toDo << ' ';
				string name = std::get<1>(entity);
				size_t slen = strlen(name.c_str());
				float x = std::get<2>(entity);
				float y = std::get<3>(entity);
				mapfile.write((char*)&slen, sizeof(slen));	std::cout << "size=" << slen << ' ';
				mapfile.write(&name[0], slen);				std::cout << name << ' ';
				mapfile.write((char*)&x, sizeof(float));	std::cout << x << ' ';
				mapfile.write((char*)&y, sizeof(float));	std::cout << y << '\n';
			}
			int obj = 1;
			for (auto object : objects.at(i)) {
				mapfile.write((char*)&obj, sizeof(int));
				mapfile.write((char*)&std::get<0>(object), sizeof(int)); std::cout << std::get<0>(object) << ' ';
				mapfile.write((char*)&std::get<1>(object), sizeof(int)); std::cout << std::get<1>(object) << ' ';
				mapfile.write((char*)&std::get<2>(object), sizeof(int)); std::cout << std::get<2>(object) << ' ';
				mapfile.write((char*)&std::get<3>(object), sizeof(int)); std::cout << std::get<3>(object) << '\n';
			}
		}
		op = "writing";
		mapfile.close();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////// READ ///////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	else {
		fstream mapfile("mapfile/map.vhmap", ios::binary | ios::in );
		if (mapfile.is_open()) {
			int s;
			vector<long> msize;
			mapfile.read((char*)&s, sizeof(int));
			msize.resize(s);
			mapfile.read((char*)msize.data(), s * sizeof(long));
			std::cout << s << " ";
			for (int i = 0; i < s; i++) std::cout << msize.at(i) << " ";
			for (int i = 0; i < s; i++) {
				std::cout << "\n\n" << mapfile.tellg() << ": LEVEL " << i << "\n\n";
				vector<int> level;
				int size;
				int tileset;
				mapfile.read((char*)&size, sizeof(size)); std::cout << size << '\n';
				level.resize(size);
				mapfile.read((char*)level.data(), size * sizeof(int));
				mapfile.read((char*)&tileset, sizeof(int));

				for (int i = 0; i < size; i++) std::cout << level[i] << " ";
				std::cout << "tileset=" << tileset << '\n';
				//*
				int toDo;
				while ((mapfile.tellg() < msize.at(i)) && !mapfile.eof()) {
					std::cout << "tellg: " << mapfile.tellg() << " ";
					int l, t, w, h;
					float x, y, boundx, boundy, bsizex, bsizey;
					string name;
					size_t slen;
					std::cout << "slen size: " << sizeof(slen) << " ";
					mapfile.read((char*)&toDo, sizeof(int));
					switch (toDo) {
					case 3:
					case 2: mapfile.read((char*)&slen, sizeof(slen)); name.resize(slen);
						mapfile.read((char*)&name[0], slen); mapfile.read((char*)&x, sizeof(float)); mapfile.read((char*)&y, sizeof(float));
						std::cout << "Entity: name=(" << name << ", size: " << slen << ") pos=(" << x << ", " << y << ")\n"; break;
					case 1: mapfile.read((char*)&l, sizeof(int)); mapfile.read((char*)&t, sizeof(int)); mapfile.read((char*)&w, sizeof(int)); mapfile.read((char*)&h, sizeof(int));
						std::cout << "Collidable: pos=(" << l << ", " << t << ") size=(" << w << ", " << h << ")\n"; break;
					default: std::cout << "didnt do a thing.\n";
					}
					
					level.clear();
				}
				//*/
			}
			op = "reading";
			mapfile.close();
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////// END OF PROGRAM //////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	char data = 'a';
	std::cout << "\nFnished " << op << ".\n";
	std::cin >> data;
	return 0;
}
