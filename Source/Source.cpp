#include <iostream>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include "olcConsoleGameEngine.h"

class HillsANDValleys : public olcConsoleGameEngine {

	public:
		HillsANDValleys(){
			m_sAppName = L"Hills and Valleys";
		}

	private:

		int state = 0;

		int nZoom = 5;
		int nCursor = 0;
		int nSubCursor = 6 ;
		int nMaxCursorPos = 0;
		int nMapWidth = 0;
		int nMapHeight = 0;
		int maxMapY = 0;
		int maxMapX = 0;
		int nPlayerCursorX = 0;
		int nPlayerCursorY = 0;
		int nUnenplyedCitizens = 0;
		int nTotCitizens = 0;
		int nSaveNum = 1;

		float fZoomOffset = 1;
		float fUptime = 0;

		bool bSubCursor = 0;
		bool bCursor = 0;
		bool bZoom = 0;
		bool bBuildMenu = 0;
		bool bCastle = 0;

		std::string path = "Saves/";
		std::wstring wsSavesName[9];
		int nSaveNumber = 0;

		struct genOptions {

			bool bGrass = 1;
			bool bForest = 1;
			bool bMountain = 1;
			bool bWather = 1;
			bool bDeepWather = 1;

			int nActiveTiles = 5;

		}genOp;

		int nMap[20][20] = { 0 };
		/*
			Grass		- 0
			Forest		- 1
			Mountain	- 2
			Water		- 3
			Deep water	- 4
		*/
		int nBuildings[20][20];
		/*
			If the tile si Grass	- 0
				Fram		- 1
				Field		- 2
				House		- 3
				Road		- 4
				Windmill	- 5
				Bakery		- 6

				Castle		- 10,11,12,13

			If the tile is Forest	- 1
				Carpenter	- 1
				Road		- 2

				Castle		- 10,11,12,13
			
			If the tile is Mountain	- 2
				Mine		- 1

			If the tile is Water	- 3
				Harbor		- 1
		*/
		bool bActive[20][20];

		float nTyleResources[4][20][20];
		/*
			Wood	-	0
			Fish	-	1
			Stone	-	2
			Iron	-	3
		*/
		int nBuildingsCount[7] = { 0 };
		/*
			Farm		-	0
			Windmill	-	1
			Bakery		-	2
			Carpenter	-	3
			Mine		-	4
			Harbor		-	5
			Field		-	6
		*/
		float fResources[6] = { 
			15,		//Wood	-	0
			0,		//Wheat	-	1
			0,		//Flour	-	2
			50,		//Food	-	3
			0,		//Stone	-	4
			0		//Iron	-	5
		};

		olcSprite* farm = nullptr;
		olcSprite* farmSM = nullptr;
		olcSprite* field = nullptr;
		olcSprite* fieldSM = nullptr;
		olcSprite* house = nullptr;
		olcSprite* houseSM = nullptr;
		olcSprite* windmill = nullptr;
		olcSprite* windmillSM = nullptr;
		olcSprite* carpenter = nullptr;
		olcSprite* carpenterSM = nullptr;
		olcSprite* mountain = nullptr;
		olcSprite* mountainSM = nullptr;
		olcSprite* bakery = nullptr;
		olcSprite* bakerySM = nullptr;
		olcSprite* mine = nullptr;
		olcSprite* mineSM = nullptr;
		olcSprite* harbor = nullptr;
		olcSprite* harborSM = nullptr;
		olcSprite* roadO = nullptr;
		olcSprite* roadOSM = nullptr;
		olcSprite* roadV = nullptr;
		olcSprite* roadVSM = nullptr;
		olcSprite* roadTN = nullptr;
		olcSprite* roadTS = nullptr;
		olcSprite* roadTE = nullptr;
		olcSprite* roadTW = nullptr;
		olcSprite* roadNE = nullptr;
		olcSprite* roadNW = nullptr;
		olcSprite* roadSE = nullptr;
		olcSprite* roadSW = nullptr;
		olcSprite* roadX = nullptr;
		olcSprite* roadXSM = nullptr;
		olcSprite* roadNESM = nullptr;
		olcSprite* roadNWSM = nullptr;
		olcSprite* roadSESM = nullptr;
		olcSprite* roadSWSM = nullptr;
		olcSprite* roadTNSM = nullptr;
		olcSprite* roadTSSM = nullptr;
		olcSprite* roadTESM = nullptr;
		olcSprite* roadTWSM = nullptr;
		olcSprite* forestRoadO = nullptr;
		olcSprite* forestRoadOSM = nullptr;
		olcSprite* forestRoadV = nullptr;
		olcSprite* forestRoadVSM = nullptr;
		olcSprite* forestRoadTN = nullptr;
		olcSprite* forestRoadTS = nullptr;
		olcSprite* forestRoadTE = nullptr;
		olcSprite* forestRoadTW = nullptr;
		olcSprite* forestRoadNE = nullptr;
		olcSprite* forestRoadNW = nullptr;
		olcSprite* forestRoadSE = nullptr;
		olcSprite* forestRoadSW = nullptr;
		olcSprite* forestRoadX = nullptr;
		olcSprite* forestRoadXSM = nullptr;
		olcSprite* forestRoadNESM = nullptr;
		olcSprite* forestRoadNWSM = nullptr;
		olcSprite* forestRoadSESM = nullptr;
		olcSprite* forestRoadSWSM = nullptr;
		olcSprite* forestRoadTNSM = nullptr;
		olcSprite* forestRoadTSSM = nullptr;
		olcSprite* forestRoadTESM = nullptr;
		olcSprite* forestRoadTWSM = nullptr;
		
		olcSprite* castleTL = nullptr;
		olcSprite* castleTR = nullptr;
		olcSprite* castleBL = nullptr;
		olcSprite* castleBR = nullptr;
		olcSprite* castleTLSM = nullptr;
		olcSprite* castleTRSM = nullptr;
		olcSprite* castleBLSM = nullptr;
		olcSprite* castleBRSM = nullptr;

		void intro() {

			//H
			DrawLine(10, 10, 12, 10);
			DrawLine(10, 10, 10, 16);
			DrawLine(12, 10, 12, 12);
			DrawLine(10, 16, 12, 16);
			DrawLine(12, 16, 12, 14);

			DrawLine(12, 12, 14, 12);
			DrawLine(12, 14, 14, 14);

			DrawLine(14, 12, 14, 10);
			DrawLine(14, 14, 14, 16);
			DrawLine(14, 10, 16, 10);
			DrawLine(14, 16, 16, 16);
			DrawLine(16, 16, 16, 10);

			//I
			DrawLine(18, 10, 20, 10);
			DrawLine(18, 10, 18, 16);
			DrawLine(20, 10, 20, 16);
			DrawLine(18, 16, 20, 16);

			//L
			DrawLine(22, 10, 24, 10);
			DrawLine(22, 10, 22, 16);
			DrawLine(22, 16, 26, 16);
			DrawLine(26, 16, 26, 14);
			DrawLine(26, 14, 24, 14);
			DrawLine(24, 14, 24, 10);

			//L
			DrawLine(28, 10, 30, 10);
			DrawLine(28, 10, 28, 16);
			DrawLine(28, 16, 32, 16);
			DrawLine(32, 16, 32, 14);
			DrawLine(32, 14, 30, 14);
			DrawLine(30, 14, 30, 10);

			//S
			DrawLine(34, 10, 34, 16);
			DrawLine(34, 10, 38, 10);
			DrawLine(38, 10, 38, 16);
			DrawLine(38, 12, 36, 12);
			DrawLine(34, 14, 36, 14);
			DrawLine(38, 16, 34, 16);

			//and
			DrawString(40, 16, L"AND");
			//V
			DrawLine(44, 10, 44, 13);
			DrawLine(44, 10, 46, 10);
			DrawLine(46, 10, 46, 12);
			DrawLine(45, 13, 45, 15);
			DrawLine(47, 12, 47, 14);
			DrawLine(48, 12, 48, 10);
			DrawLine(48, 10, 50, 10);
			DrawLine(50, 10, 50, 13);
			DrawLine(49, 13, 49, 15);
			DrawLine(48, 15, 48, 16);
			DrawLine(46, 15, 46, 16);
			Draw(47, 16);

			//A
			DrawLine(52, 10, 57, 10);
			DrawLine(52, 10, 52, 16);
			DrawLine(52, 16, 54, 16);
			DrawLine(54, 16, 54, 14);
			Draw(55, 14);
			DrawLine(56, 14, 56, 16);
			DrawLine(56, 16, 58, 16);
			DrawLine(58, 16, 58, 10);
			DrawLine(54, 12, 56, 12);

			//L
			DrawLine(60, 10, 62, 10);
			DrawLine(60, 10, 60, 16);
			DrawLine(60, 16, 64, 16);
			DrawLine(64, 16, 64, 14);
			DrawLine(64, 14, 62, 14);
			DrawLine(62, 14, 62, 10);

			//L
			DrawLine(66, 10, 68, 10);
			DrawLine(66, 10, 66, 16);
			DrawLine(66, 16, 70, 16);
			DrawLine(70, 16, 70, 14);
			DrawLine(70, 14, 68, 14);
			DrawLine(68, 14, 68, 10);

			//E
			DrawLine(72, 10, 72, 16);
			DrawLine(72, 10, 77, 10);
			DrawLine(77, 10, 77, 16);
			DrawLine(77, 12, 74, 12);
			DrawLine(77, 14, 74, 14);
			DrawLine(77, 16, 72, 16);

			//Y
			Draw(79, 10);
			DrawLine(79, 11, 81, 13);
			DrawLine(80, 10, 82, 12);
			DrawLine(82, 12, 84, 10);
			Draw(85, 10);
			DrawLine(85, 11, 83, 13);
			DrawLine(83, 13, 83, 16);
			DrawLine(81, 13, 81, 16);
			Draw(82, 16);

			//S
			DrawLine(87, 10, 87, 16);
			DrawLine(87, 10, 91, 10);
			DrawLine(91, 10, 91, 16);
			DrawLine(91, 12, 89, 12);
			DrawLine(87, 14, 89, 14);
			DrawLine(91, 16, 87, 16);

			DrawString(35, 30, L"[Press ENTER to start]");

			DrawString(0, m_nScreenHeight - 1, L"onelonecoder.com - Made with olcConsoleGameEngine");

			if (GetKey(VK_RETURN).bPressed) 
				state = 1;

			return;
		}

		void menuFrame(int xOffset = 0, int yOffset = 0, int nWidth = 50, int nHeight = 60) {
			for (int y = 10; y < 12; y++)
				for (int x = 10; x < nWidth; x++) {
					Draw(x + xOffset, y + yOffset);
				}
			for (int x = 10; x < 12; x++)
				for (int y = 10; y < nHeight; y++) {
					Draw(x + xOffset, y + yOffset);;
				}
			for (int y = 58; y < nHeight; y++)
				for (int x = 10; x < nWidth; x++) {
					Draw(x + xOffset, y + yOffset);
				}
			for (int x = 48; x < nWidth; x++)
				for (int y = 10; y < nHeight; y++) {
					Draw(x + xOffset, y + yOffset);
				}
		}
		
		void Save() {

			if (nSaveNum == 10) {
				if (MessageBox(NULL, L"You rached the max number of saves!\nGo delete some saves in the Saves/ folder then click OK\n or click CANCEL to abort the saveing", L"WARNING", MB_OKCANCEL || MB_ICONERROR) == 1) {
					nSaveNum = 1;
				}
				else {
					return;
				}
			}

			std::ofstream save;

			char cSaveName[13] = "Saves/save_";

			switch (nSaveNum) {
			case 1:
				strcat_s(cSaveName, "1");
				break;
			case 2:
				strcat_s(cSaveName, "2");
				break;
			case 3:
				strcat_s(cSaveName, "3");
				break;
			case 4:
				strcat_s(cSaveName, "4");
				break;
			case 5:
				strcat_s(cSaveName, "5");
				break;
			case 6:
				strcat_s(cSaveName, "6");
				break;
			case 7:
				strcat_s(cSaveName, "7");
				break;
			case 8:
				strcat_s(cSaveName, "8");
				break;
			case 9:
				strcat_s(cSaveName, "9");
				break;
			}

			save.open(cSaveName, std::ios::out);

			save << nMapHeight << " " << nMapWidth << "\n\n\n";

			for (int y = 0; y < nMapHeight; y++) {
				for (int x = 0; x < nMapWidth; x++) {
					save << nMap[x][y] << " ";
				}
				save << "\n";
			}

			save << "\n\n\n";

			for (int y = 0; y < nMapHeight; y++) {
				for (int x = 0; x < nMapWidth; x++) {
					save << nBuildings[x][y] << " ";
				}
				save << "\n";
			}

			save << "\n\n\n";

			for (int y = 0; y < nMapHeight; y++) {
				for (int x = 0; x < nMapWidth; x++) {
					save << bActive[x][y] << " ";
				}
				save << "\n";
			}

			save << "\n\n\n";

			for (int z = 0; z < 4; z++) {
				for (int y = 0; y < nMapHeight; y++) {
					for (int x = 0; x < nMapWidth; x++) {
						save << nTyleResources[z][x][y] << " ";
					}
					save << "\n";
				}
				save << "\n\n";
			}

			save << "\n\n\n";

			for (int a = 0; a < 7; a++) {
				save << nBuildingsCount[a] << " ";
			}
			
			save << "\n\n\n";

			for (int a = 0; a < 6; a++) {
				save << fResources[a] << " ";
			}

			save << "\n\n\n";

			save << bCastle << " " << nTotCitizens << " " << nUnenplyedCitizens;

			save.close();

			nSaveNum++;

			return;

		}

		void Load(std::wstring wsFileName) {

			std::ifstream load;
			load.open(wsFileName, std::ios::in);

			load >> nMapHeight >> nMapWidth;

			for (int y = 0; y < nMapHeight; y++) {
				for (int x = 0; x < nMapWidth; x++) {
					load >> nMap[x][y];
					
				}
				
			}

			for (int y = 0; y < nMapHeight; y++) {
				for (int x = 0; x < nMapWidth; x++) {
					load >> nBuildings[x][y];
				}
				
			}

			for (int y = 0; y < nMapHeight; y++) {
				for (int x = 0; x < nMapWidth; x++) {
					load >> bActive[x][y];
				}
				
			}

			for (int z = 0; z < 4; z++) {
				for (int y = 0; y < nMapHeight; y++) {
					for (int x = 0; x < nMapWidth; x++) {
						load >> nTyleResources[z][x][y];
					}
					
				}
				
			}

			for (int a = 0; a < 7; a++) {
				load >> nBuildingsCount[a] ;
			}

			for (int a = 0; a < 6; a++) {
				load >> fResources[a] ;
			}
			
			load >> bCastle >> nTotCitizens >> nUnenplyedCitizens;
			
			load.close();

			return;
		}

		void menu() {
			DrawString(22, 5, L"HILLS and VALLEYS");

			//Printing the Menu Frame
			menuFrame();

			//Highlighting the selected option
			switch (nCursor) {
				case 0:
					//Highlighting cursor
					DrawString(15, 15, L"New Game", BG_WHITE);
					DrawString(15, 20, L"Load Game");
					DrawString(15, 55, L"Quit Game");
					break;

				case 1:
					//Highlighting cursor
					DrawString(15, 15, L"New Game");
					DrawString(15, 20, L"Load Game", BG_WHITE);
					DrawString(15, 55, L"Quit Game");

					menuFrame(45);

					switch (nSubCursor) {
					case 0:
						DrawString(60, 15, wsSavesName[0],  BG_WHITE);
						DrawString(60, 20, wsSavesName[1]);
						DrawString(60, 25, wsSavesName[2]);
						DrawString(60, 30, wsSavesName[3]);
						DrawString(60, 35, wsSavesName[4]);
						DrawString(60, 40, wsSavesName[5]);
						DrawString(60, 45, wsSavesName[6]);
						DrawString(60, 50, wsSavesName[7]);
						DrawString(60, 55, wsSavesName[8]);
						break;
					case 1:
						DrawString(60, 15, wsSavesName[0]);
						DrawString(60, 20, wsSavesName[1],  BG_WHITE);
						DrawString(60, 25, wsSavesName[2]);
						DrawString(60, 30, wsSavesName[3]);
						DrawString(60, 35, wsSavesName[4]);
						DrawString(60, 40, wsSavesName[5]);
						DrawString(60, 45, wsSavesName[6]);
						DrawString(60, 50, wsSavesName[7]);
						DrawString(60, 55, wsSavesName[8]);
						break;
					case 2:
						DrawString(60, 15, wsSavesName[0]);
						DrawString(60, 20, wsSavesName[1]);
						DrawString(60, 25, wsSavesName[2],  BG_WHITE);
						DrawString(60, 30, wsSavesName[3]);
						DrawString(60, 35, wsSavesName[4]);
						DrawString(60, 40, wsSavesName[5]);
						DrawString(60, 45, wsSavesName[6]);
						DrawString(60, 50, wsSavesName[7]);
						DrawString(60, 55, wsSavesName[8]);
						break;
					case 3:
						DrawString(60, 15, wsSavesName[0]);
						DrawString(60, 20, wsSavesName[1]);
						DrawString(60, 25, wsSavesName[2]);
						DrawString(60, 30, wsSavesName[3],  BG_WHITE);
						DrawString(60, 35, wsSavesName[4]);
						DrawString(60, 40, wsSavesName[5]);
						DrawString(60, 45, wsSavesName[6]);
						DrawString(60, 50, wsSavesName[7]);
						DrawString(60, 55, wsSavesName[8]);
						break;
					case 4:
						DrawString(60, 15, wsSavesName[0]);
						DrawString(60, 20, wsSavesName[1]);
						DrawString(60, 25, wsSavesName[2]);
						DrawString(60, 30, wsSavesName[3]);
						DrawString(60, 35, wsSavesName[4],  BG_WHITE);
						DrawString(60, 40, wsSavesName[5]);
						DrawString(60, 45, wsSavesName[6]);
						DrawString(60, 50, wsSavesName[7]);
						DrawString(60, 55, wsSavesName[8]);
						break;
					case 5:
						DrawString(60, 15, wsSavesName[0]);
						DrawString(60, 20, wsSavesName[1]);
						DrawString(60, 25, wsSavesName[2]);
						DrawString(60, 30, wsSavesName[3]);
						DrawString(60, 35, wsSavesName[4]);
						DrawString(60, 40, wsSavesName[5],  BG_WHITE);
						DrawString(60, 45, wsSavesName[6]);
						DrawString(60, 50, wsSavesName[7]);
						DrawString(60, 55, wsSavesName[8]);
						break;
					case 6:
						DrawString(60, 15, wsSavesName[0]);
						DrawString(60, 20, wsSavesName[1]);
						DrawString(60, 25, wsSavesName[2]);
						DrawString(60, 30, wsSavesName[3]);
						DrawString(60, 35, wsSavesName[4]);
						DrawString(60, 40, wsSavesName[5]);
						DrawString(60, 45, wsSavesName[6],  BG_WHITE);
						DrawString(60, 50, wsSavesName[7]);
						DrawString(60, 55, wsSavesName[8]);
						break;
					case 7:
						DrawString(60, 15, wsSavesName[0]);
						DrawString(60, 20, wsSavesName[1]);
						DrawString(60, 25, wsSavesName[2]);
						DrawString(60, 30, wsSavesName[3]);
						DrawString(60, 35, wsSavesName[4]);
						DrawString(60, 40, wsSavesName[5]);
						DrawString(60, 45, wsSavesName[6]);
						DrawString(60, 50, wsSavesName[7],  BG_WHITE);
						DrawString(60, 55, wsSavesName[8]);
						break;
					case 8:
						DrawString(60, 15, wsSavesName[0]);
						DrawString(60, 20, wsSavesName[1]);
						DrawString(60, 25, wsSavesName[2]);
						DrawString(60, 30, wsSavesName[3]);
						DrawString(60, 35, wsSavesName[4]);
						DrawString(60, 40, wsSavesName[5]);
						DrawString(60, 45, wsSavesName[6]);
						DrawString(60, 50, wsSavesName[7]);
						DrawString(60, 55, wsSavesName[8],  BG_WHITE);
						break;
					default:
						DrawString(60, 15, wsSavesName[0]);
						DrawString(60, 20, wsSavesName[1]);
						DrawString(60, 25, wsSavesName[2]);
						DrawString(60, 30, wsSavesName[3]);
						DrawString(60, 35, wsSavesName[4]);
						DrawString(60, 40, wsSavesName[5]);
						DrawString(60, 45, wsSavesName[6]);
						DrawString(60, 50, wsSavesName[7]);
						DrawString(60, 55, wsSavesName[8]);
						break;
					}
							
					break;

				case 2:
					//Highlighting cursor
					DrawString(15, 15, L"New Game");
					DrawString(15, 20, L"Load Game");
					DrawString(15, 55, L"Quit Game", BG_WHITE);
					break;

				default:
					DrawString(15, 15, L"New Game");
					DrawString(15, 20, L"Load Game");
					DrawString(15, 55, L"Quit Game");
					break;
			}

			if (!bSubCursor) {
				//Updating nCursor
				if (GetKey(VK_DOWN).bPressed)
					nCursor += 1;
				if (GetKey(VK_UP).bPressed)
					nCursor -= 1;

				//Correcting nCursor Overflow
				if (nCursor > 2)
					nCursor = 2;
				if (nCursor < 0)
					nCursor = 0;

				//Interpreting input
				if (GetKey(VK_RETURN).bPressed) {
					switch (nCursor) {
					case 0:
						state = 2;
						nZoom = 5;
						fZoomOffset = 1;
						nCursor = 0;
						break;
					case 1:
						bSubCursor = 1;
						nSubCursor = 0;
						break;
					case 2:
						exit(0);
						break;
					}
				}
			}
			else {

				if (GetKey(VK_DOWN).bPressed)
					nSubCursor += 1;
				if (GetKey(VK_UP).bPressed)
					nSubCursor -= 1;

				if (nSubCursor > nSaveNumber - 1)
					nSubCursor = nSaveNumber - 1;
				if (nSubCursor < 0)
					nSubCursor = 0;

				if (GetKey(VK_RETURN).bPressed) {
					switch (nSubCursor) {
					case 0:
						Load(wsSavesName[0]);
						break;
					case 1:
						Load(wsSavesName[1]);
						break;
					case 2:
						Load(wsSavesName[2]);
						break;
					case 3:
						Load(wsSavesName[3]);
						break;
					case 4:
						Load(wsSavesName[4]);
						break;
					case 5:
						Load(wsSavesName[5]);
						break;
					case 6:
						Load(wsSavesName[6]);
						break;
					case 7:
						Load(wsSavesName[7]);
						break;
					case 8:
						Load(wsSavesName[8]);
						break;
					}
					bSubCursor = 0;
					state = 3;
				}

			}

			return;
		}

		void DrawCursor(int x, int y, int plX = 0, int plY = 0) {

			if (!bCursor) {

				//Up left corner
				Draw(5 + ((x - plX) * nZoom), 5 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);
				Draw(5 + ((x - plX) * nZoom), 6 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);
				Draw(6 + ((x - plX) * nZoom), 5 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);

				//Up right corner
				Draw(10 * fZoomOffset + ((x - plX) * nZoom), 5 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);
				Draw(10 * fZoomOffset + ((x - plX) * nZoom), 6 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);

				//Down left corner
				Draw(5 + ((x - plX) * nZoom), 10 * fZoomOffset + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);
				Draw(6 + ((x - plX) * nZoom), 10 * fZoomOffset + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);

				//Down right corner
				Draw(10 * fZoomOffset + ((x - plX) * nZoom), 10 * fZoomOffset + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);

				if (bZoom) {
					//Down right corner
					Draw(10 * fZoomOffset + ((x - plX) * nZoom), 9 * fZoomOffset + ((y - plY) * nZoom) + 1, PIXEL_SOLID, FG_DARK_YELLOW);
					Draw(9 * fZoomOffset + ((x - plX) * nZoom) + 1, 10 * fZoomOffset + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);
					//Up right corner
					Draw(9 * fZoomOffset + ((x - plX) * nZoom) + 1, 5 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);
					//Down left corner
					Draw(5 + ((x - plX) * nZoom), 9 * fZoomOffset + ((y - plY) * nZoom) + 1, PIXEL_SOLID, FG_DARK_YELLOW);
				}
				else {
					//Down right corner
					Draw(10 + ((x - plX) * nZoom), 9 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);
					Draw(9 + ((x - plX) * nZoom), 10 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);
					//Up right corner
					Draw(9 + ((x - plX) * nZoom), 5 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);
					//Down left corner
					Draw(5 + ((x - plX) * nZoom), 9 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_YELLOW);
				}
			}
			else {

				//Up left corner
				Draw(5 + ((x - plX) * nZoom), 5 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);
				Draw(5 + ((x - plX) * nZoom), 6 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);
				Draw(6 + ((x - plX) * nZoom), 5 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);

				//Up right corner
				Draw(10 * fZoomOffset + ((x - plX) * nZoom), 5 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);
				Draw(10 * fZoomOffset + ((x - plX) * nZoom), 6 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);

				//Down left corner
				Draw(5 + ((x - plX) * nZoom), 10 * fZoomOffset + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);
				Draw(6 + ((x - plX) * nZoom), 10 * fZoomOffset + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);

				//Down right corner
				Draw(10 * fZoomOffset + ((x - plX) * nZoom), 10 * fZoomOffset + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);

				if (bZoom) {
					//Down right corner
					Draw(10 * fZoomOffset + ((x - plX) * nZoom), 9 * fZoomOffset + ((y - plY) * nZoom) + 1, PIXEL_SOLID, FG_DARK_RED);
					Draw(9 * fZoomOffset + ((x - plX) * nZoom) + 1, 10 * fZoomOffset + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);
					//Up right corner
					Draw(9 * fZoomOffset + ((x - plX) * nZoom) + 1, 5 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);
					//Down left corner
					Draw(5 + ((x - plX) * nZoom), 9 * fZoomOffset + ((y - plY) * nZoom) + 1, PIXEL_SOLID, FG_DARK_RED);
				}
				else {
					//Down right corner
					Draw(10 + ((x - plX) * nZoom), 9 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);
					Draw(9 + ((x - plX) * nZoom), 10 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);
					//Up right corner
					Draw(9 + ((x - plX) * nZoom), 5 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);
					//Down left corner
					Draw(5 + ((x - plX) * nZoom), 9 + ((y - plY) * nZoom), PIXEL_SOLID, FG_DARK_RED);
				}

			}
		}

		void genMap() {

			//Printing the Menu Frame 
			menuFrame();

			DrawString(20, 15, L"Select the map size");

			//Highlighting the selected option and printing the map preview
			switch (nCursor) {
				case 0: //10x10 map
					//Highlighting cursor position
					DrawString(15, 20, L"10x10 tiles map", BG_WHITE);
					DrawString(15, 25, L"15x15 tiles map");
					DrawString(15, 30, L"20x20 tiles map");
					DrawString(15, 50, L"Generation Options");
					DrawString(15, 55, L"Back");

					//--Map preview
					//-Outline
					DrawLine(51, 9, 103, 9);
					DrawLine(51, 9, 51, 61);
					DrawLine(51, 61, 103, 61);
					DrawLine(103, 61, 103, 9);

					//Drawing and filling tiles lines
					for (int y = 0; y < 10; y++)
						for (int x = 0; x < 10; x++)
							Fill(53 + (5 * x), 11 + (5 * y), 57 + (5 * x), 15 + (5 * y), PIXEL_SOLID, FG_GREEN);
					break;

				case 1: //15x15 map

					//Highlighting cursor position
					DrawString(15, 20, L"10x10 tiles map");
					DrawString(15, 25, L"15x15 tiles map", BG_WHITE);
					DrawString(15, 30, L"20x20 tiles map");
					DrawString(15, 50, L"Generation Options");
					DrawString(15, 55, L"Back");

					//--Map preview
					//-Outline
					DrawLine(51, 9, 98, 9);
					DrawLine(51, 9, 51, 56);
					DrawLine(51, 56, 98, 56);
					DrawLine(98, 56, 98, 9);

					//Drawing and filling tiles lines
					for (int y = 0; y < 15; y++)
						for (int x = 0; x < 15; x++)
							Fill(53 + (3 * x), 11 + (3 * y), 55 + (3 * x), 13 + (3 * y), PIXEL_SOLID, FG_GREEN);
					break;

				case 2: //20x20 map
					//Highlighting cursor position
					DrawString(15, 20, L"10x10 tiles map");
					DrawString(15, 25, L"15x15 tiles map");
					DrawString(15, 30, L"20x20 tiles map", BG_WHITE);
					DrawString(15, 50, L"Generation Options");
					DrawString(15, 55, L"Back");

					//--Map preview
					//-Outline
					DrawLine(51, 9, 93, 9);
					DrawLine(51, 9, 51, 51);
					DrawLine(51, 51, 93, 51);
					DrawLine(93, 51, 93, 9);

					//Drawing and filling tiles lines
					for (int y = 0; y < 40; y += 2)
						for (int x = 0; x < 40; x += 2)
							Draw(x + 53, y + 11, PIXEL_SOLID, FG_GREEN);
					break;

				case 3: //Map Generation Options
					//Highlighting cursor position
					DrawString(15, 20, L"10x10 tiles map");
					DrawString(15, 25, L"15x15 tiles map");
					DrawString(15, 30, L"20x20 tiles map");
					DrawString(15, 50, L"Generation Options", BG_WHITE);
					DrawString(15, 55, L"Back");

					//Printing sub-menu frame
					menuFrame(45);

					//Printing sub-menu contetnt
					DrawString(65, 15, L"Map generation options");
					switch (nSubCursor) {
					case 0:
						//Highlighting cursor position
						DrawString(60, 20, L"Grass: ", BG_WHITE);
						if (genOp.bGrass)
							DrawString(67, 20, L"ON", BG_WHITE);
						else
							DrawString(67, 20, L"OFF", BG_WHITE);

						DrawString(60, 25, L"Forests: ");
						if (genOp.bForest)
							DrawString(69, 25, L"ON");
						else
							DrawString(69, 25, L"OFF");

						DrawString(60, 30, L"Mountine: ");
						if (genOp.bMountain)
							DrawString(70, 30, L"ON");
						else
							DrawString(70, 30, L"OFF");

						DrawString(60, 35, L"Wather: ");
						if (genOp.bWather)
							DrawString(68, 35, L"ON");
						else
							DrawString(68, 35, L"OFF");

						DrawString(60, 40, L"Deep Wather: ");
						if (genOp.bDeepWather)
							DrawString(73, 40, L"ON");
						else
							DrawString(73, 40, L"OFF");

						DrawString(60, 55, L"Back");
						break;

					case 1:
						//Highlighting cursor position
						DrawString(60, 20, L"Grass: ");
						if (genOp.bGrass)
							DrawString(67, 20, L"ON");
						else
							DrawString(67, 20, L"OFF");

						DrawString(60, 25, L"Forests: ", BG_WHITE);
						if (genOp.bForest)
							DrawString(69, 25, L"ON", BG_WHITE);
						else
							DrawString(69, 25, L"OFF", BG_WHITE);

						DrawString(60, 30, L"Mountine: ");
						if (genOp.bMountain)
							DrawString(70, 30, L"ON");
						else
							DrawString(70, 30, L"OFF");

						DrawString(60, 35, L"Wather: ");
						if (genOp.bWather)
							DrawString(68, 35, L"ON");
						else
							DrawString(68, 35, L"OFF");

						DrawString(60, 40, L"Deep Wather: ");
						if (genOp.bDeepWather)
							DrawString(73, 40, L"ON");
						else
							DrawString(73, 40, L"OFF");

						DrawString(60, 55, L"Back");
						break;

					case 2:
						//Highlighting cursor position
						DrawString(60, 20, L"Grass: ");
						if (genOp.bGrass)
							DrawString(67, 20, L"ON");
						else
							DrawString(67, 20, L"OFF");

						DrawString(60, 25, L"Forests: ");
						if (genOp.bForest)
							DrawString(69, 25, L"ON");
						else
							DrawString(69, 25, L"OFF");

						DrawString(60, 30, L"Mountine: ", BG_WHITE);
						if (genOp.bMountain)
							DrawString(70, 30, L"ON", BG_WHITE);
						else
							DrawString(70, 30, L"OFF", BG_WHITE);

						DrawString(60, 35, L"Wather: ");
						if (genOp.bWather)
							DrawString(68, 35, L"ON");
						else
							DrawString(68, 35, L"OFF");

						DrawString(60, 40, L"Deep Wather: ");
						if (genOp.bDeepWather)
							DrawString(73, 40, L"ON");
						else
							DrawString(73, 40, L"OFF");

						DrawString(60, 55, L"Back");
						break;

					case 3:
						//Highlighting cursor position
						DrawString(60, 20, L"Grass: ");
						if (genOp.bGrass)
							DrawString(67, 20, L"ON");
						else
							DrawString(67, 20, L"OFF");

						DrawString(60, 25, L"Forests: ");
						if (genOp.bForest)
							DrawString(69, 25, L"ON");
						else
							DrawString(69, 25, L"OFF");

						DrawString(60, 30, L"Mountine: ");
						if (genOp.bMountain)
							DrawString(70, 30, L"ON");
						else
							DrawString(70, 30, L"OFF");

						DrawString(60, 35, L"Wather: ", BG_WHITE);
						if (genOp.bWather)
							DrawString(68, 35, L"ON", BG_WHITE);
						else
							DrawString(68, 35, L"OFF", BG_WHITE);

						DrawString(60, 40, L"Deep Wather: ");
						if (genOp.bDeepWather)
							DrawString(73, 40, L"ON");
						else
							DrawString(73, 40, L"OFF");

						DrawString(60, 55, L"Back");
						break;

					case 4:
						//Highlighting cursor position
						DrawString(60, 20, L"Grass: ");
						if (genOp.bGrass)
							DrawString(67, 20, L"ON");
						else
							DrawString(67, 20, L"OFF");

						DrawString(60, 25, L"Forests: ");
						if (genOp.bForest)
							DrawString(69, 25, L"ON");
						else
							DrawString(69, 25, L"OFF");

						DrawString(60, 30, L"Mountine: ");
						if (genOp.bMountain)
							DrawString(70, 30, L"ON");
						else
							DrawString(70, 30, L"OFF");

						DrawString(60, 35, L"Wather: ");
						if (genOp.bWather)
							DrawString(68, 35, L"ON");
						else
							DrawString(68, 35, L"OFF");

						DrawString(60, 40, L"Deep Wather: ", BG_WHITE);
						if (genOp.bDeepWather)
							DrawString(73, 40, L"ON", BG_WHITE);
						else
							DrawString(73, 40, L"OFF", BG_WHITE);

						DrawString(60, 55, L"Back");
						break;

					case 5:
						//Highlighting cursor position
						DrawString(60, 20, L"Grass: ");
						if (genOp.bGrass)
							DrawString(67, 20, L"ON");
						else
							DrawString(67, 20, L"OFF");

						DrawString(60, 25, L"Forests: ");
						if (genOp.bForest)
							DrawString(69, 25, L"ON");
						else
							DrawString(69, 25, L"OFF");

						DrawString(60, 30, L"Mountine: ");
						if (genOp.bMountain)
							DrawString(70, 30, L"ON");
						else
							DrawString(70, 30, L"OFF");

						DrawString(60, 35, L"Wather: ");
						if (genOp.bWather)
							DrawString(68, 35, L"ON");
						else
							DrawString(68, 35, L"OFF");

						DrawString(60, 40, L"Deep Wather: ");
						if (genOp.bDeepWather)
							DrawString(73, 40, L"ON");
						else
							DrawString(73, 40, L"OFF");

						DrawString(60, 55, L"Back", BG_WHITE);
						break;

					default:
						DrawString(60, 20, L"Grass: ");
						if (genOp.bGrass)
							DrawString(67, 20, L"ON");
						else
							DrawString(67, 20, L"OFF");

						DrawString(60, 25, L"Forests: ");
						if (genOp.bForest)
							DrawString(69, 25, L"ON");
						else
							DrawString(69, 25, L"OFF");

						DrawString(60, 30, L"Mountine: ");
						if (genOp.bMountain)
							DrawString(70, 30, L"ON");
						else
							DrawString(70, 30, L"OFF");

						DrawString(60, 35, L"Wather: ");
						if (genOp.bWather)
							DrawString(68, 35, L"ON");
						else
							DrawString(68, 35, L"OFF");

						DrawString(60, 40, L"Deep Wather: ");
						if (genOp.bDeepWather)
							DrawString(73, 40, L"ON");
						else
							DrawString(73, 40, L"OFF");

						DrawString(60, 55, L"Back");
						break;
					}

					break;

				case 4: //Back 
					//Highlighting cursor position
					DrawString(15, 20, L"10x10 tiles map");
					DrawString(15, 25, L"15x15 tiles map");
					DrawString(15, 30, L"20x20 tiles map");
					DrawString(15, 50, L"Generation Options");
					DrawString(15, 55, L"Back", BG_WHITE);
					break;
				
			}

			//Menu
			if (!bSubCursor) {		

				//Updating nCursor
				if (GetKey(VK_DOWN).bPressed)
					nCursor += 1;
				if (GetKey(VK_UP).bPressed)
					nCursor -= 1;

				//Correcting nCursor Overflow
				if (nCursor > 4)
					nCursor = 4;
				if (nCursor < 0)
					nCursor = 0;
			
				//Interpreting input
				//Cases 0 to 2 - Generates random map of the specified size according to the active tiles type 
				//case 3 - Enters generation option menu (see SubMenu)
				//Case 4 - Back
				if (GetKey(VK_RETURN).bPressed) {

					//If there are more than 2 tiles types active it generates the map according to the active tiles type 
					if (genOp.nActiveTiles >= 2) {
						switch (nCursor) {
						case 0:		//10x10
							nPlayerCursorX = 0;
							nPlayerCursorY = 0;

							nMapWidth = 10;
							nMapHeight = 10;

							
							nCursor = 10;
							state = 3;
							break;
						case 1:		//15x15
							nPlayerCursorX = 0;
							nPlayerCursorY = 0;

							nMapWidth = 15;
							nMapHeight = 15;

							nCursor = 10;
							state = 3;
							break;
						case 2:		//20x20
							nPlayerCursorX = 0;
							nPlayerCursorY = 0;

							nMapWidth = 20;
							nMapHeight = 20;
							
							nCursor = 10;
							state = 3;
							break;
						case 3:
							nSubCursor = 0;
							bSubCursor = 1;
							break;
						case 4:
							nCursor = 0;
							state = 1;
							genOp.bGrass = 1;
							genOp.bForest = 1;
							genOp.bMountain = 1;
							genOp.bWather = 1;
							genOp.bDeepWather = 1;
							genOp.nActiveTiles = 5;
							break;
						}

						for (int y = 0; y < nMapHeight; y++)
							for (int x = 0; x < nMapWidth; x++) {
								nMap[x][y] = rand() % 5;

								if (nMap[x][y] == 3)
									if (rand() % 5 != 1)
										nMap[x][y] = rand() % 3;
								if (nMap[x][y] == 4)
									if (rand() % 5 != 1)
										nMap[x][y] = rand() % 3;
								if (nMap[x][y] == 1)
									if (rand() % 5 < 2)
										if (rand() % 1)
											nMap[x][y] = rand() % 3 + 2;
										else
											nMap[x][y] = 0;
								if (nMap[x][y] == 2)
									if (rand() % 1)
										if (rand() % 1)
											nMap[x][y] = rand() % 1 + 3;
										else
											nMap[x][y] = 0;

								bool bGen = 0;

								while (!bGen) {
									switch (nMap[x][y]) {
									case 0:
										if (!genOp.bGrass)
											nMap[x][y] = rand() % 1 + 4;
										else
											bGen = 1;
										break;
									case 1:
										if (!genOp.bForest)
											nMap[x][y] = rand() % 2 + 3;
										else {
											nTyleResources[0][x][y] = rand() % 300 + 100;
											bGen = 1;
										}
										break;
									case 2:
										if (!genOp.bMountain)
											nMap[x][y] = rand() % 3 + 2;
										else {
											nTyleResources[2][x][y] = rand() % 100 + 200;
											if (rand() % 3 == 1)
												nTyleResources[3][x][y] = rand() % 100 + 10;
											bGen = 1;
										}
										break;
									case 3:
										if (!genOp.bWather)
											nMap[x][y] = rand() % 4 + 1;
										else {
											if (rand() % 3 <= 2)
												nTyleResources[1][x][y] = rand() % 100 + 10;
											bGen = 1;
										}
										break;
									case 4:
										if (!genOp.bDeepWather)
											nMap[x][y] = rand() % 4;
										else {
											if (rand() % 3 <= 2)
												nTyleResources[1][x][y] = rand() % 100 + 10;
											bGen = 1;
										}
										break;
									}
								}

							}

					}
					//If there are less than 2 tiles type active but a generation option is not selected 
					else if(nCursor > 2){
						switch (nCursor) {
						case 3:
							nSubCursor = 0;
							bSubCursor = 1;
							break;
						case 4:
							nCursor = 0;
							state = 1;
							break;
						}
					}
					//If there are less than 2 tiles type active and a generation option is selected it returns an error 
					else 
						MessageBox(NULL, L"You must activate at least two types of tiels to generate a map", L"ERROR", MB_OK | MB_ICONERROR);
				}
			}
			//SubMenu
			else {		

				//Updating nSubCursor
				if (GetKey(VK_DOWN).bPressed)
					nSubCursor += 1;
				if (GetKey(VK_UP).bPressed)
					nSubCursor -= 1;

				//Correcting nSubCursor Overflow
				if (nSubCursor > 5)
					nSubCursor = 5;
				if (nSubCursor < 0)
					nSubCursor = 0;

				//Interpreting input
				//Cases 0 to 4 - Generation Options
				//Sase 5 - Back
				if (GetKey(VK_RETURN).bPressed) {
					switch (nSubCursor) {
					case 0:
						if (genOp.bGrass) {
							genOp.bGrass = 0;
							genOp.nActiveTiles--;
						}
						else {
							genOp.bGrass = 1;
							genOp.nActiveTiles++;
						}
						break;
					case 1:
						if (genOp.bForest) {
							genOp.bForest = 0;
							genOp.nActiveTiles--;
						}
						else {
							genOp.bForest = 1;
							genOp.nActiveTiles++;
						}
						break;
					case 2:
						if (genOp.bMountain) {
							genOp.bMountain = 0;
							genOp.nActiveTiles--;
						}
						else {
							genOp.bMountain = 1;
							genOp.nActiveTiles++;
						}
						break;
					case 3:
						if (genOp.bWather) {
							genOp.bWather = 0;
							genOp.nActiveTiles--;
						}
						else {
							genOp.bWather = 1;
							genOp.nActiveTiles++;
						}
						break;
					case 4:
						if (genOp.bDeepWather) {
							genOp.bDeepWather = 0;
							genOp.nActiveTiles--;
						}
						else {
							genOp.bDeepWather = 1;
							genOp.nActiveTiles++;
						}
						break;

					case 5:
						bSubCursor = 0;
						nSubCursor = 6;
						break;
					}
				}

			}
		}

		void loadMap(int plX = 0, int plY = 0) {

			//Clearing the screen
			Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', 0);

			if (bZoom) {
				maxMapY = plY + 10;
				maxMapX = plX + 10;
			}
			else {
				maxMapY = nMapHeight;
				maxMapX = nMapWidth;
			}

			//Printing the map 
			for (int y = plY; y < maxMapY; y++)
				for (int x = plX; x < maxMapX; x++) {
					switch (nMap[x][y]) {
					case 0:		//Grass
						if(!nBuildings[x][y])
							Fill(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), 10 * fZoomOffset + (nZoom * (x - plX)), 10 * fZoomOffset + (nZoom * (y - plY)), PIXEL_SOLID, FG_GREEN);
						else {
							if (bZoom) {
								switch (nBuildings[x][y]) {
								case 1:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), farm);
									break;
								case 2:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), field);
									break;
								case 3:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), house);
									break;
								case 4:
									if (nBuildings[x + 1][y] != 0 && nBuildings[x - 1][y] != 0) {
										if(nBuildings[x][y + 1] != 0 && nBuildings[x][y - 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadX);
										else if (nBuildings[x][y + 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadTN);
										else if (nBuildings[x][y - 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadTS);
										
										else
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadO);
									}
									else if (nBuildings[x][y + 1] != 0 && nBuildings[x][y - 1] != 0) {
										if (nBuildings[x + 1][y] != 0 && nBuildings[x - 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadX);
										else if (nBuildings[x + 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadTW);
										else if (nBuildings[x - 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadTE);
										else
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadV);
									}
									else if (nBuildings[x + 1][y] != 0 && nBuildings[x][y + 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadSE);
									else if (nBuildings[x + 1][y] != 0 && nBuildings[x][y - 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadNE);
									else if (nBuildings[x - 1][y] != 0 && nBuildings[x][y + 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadSW);
									else if (nBuildings[x - 1][y] != 0 && nBuildings[x][y - 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadNW);
									else
										if(nBuildings[x - 1][y] != 0 || nBuildings[x + 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadO);
										else if (nBuildings[x][y - 1] != 0 || nBuildings[x][y + 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadV);
										else
											if (rand() % 1)
												DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadO);
											else
												DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadV);
									
									break;
								case 5:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), windmill);
									break;
								case 6:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), bakery);
									break;
								case 10:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleTL);
									break;
								case 11:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleTR);
									break;
								case 12:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleBL);
									break;
								case 13:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleBR);
									break;
								}
							}
							else {
								switch (nBuildings[x][y]) {
								case 1:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), farmSM);
									break;
								case 2:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), fieldSM);
									break;
								case 3:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), houseSM);
									break;
								case 4:
									if (nBuildings[x + 1][y] != 0 && nBuildings[x - 1][y] != 0) {
										if (nBuildings[x][y + 1] != 0 && nBuildings[x][y - 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadXSM);
										else if (nBuildings[x][y + 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadTNSM);
										else if (nBuildings[x][y - 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadTSSM);
										else
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadOSM);
									}
									else if (nBuildings[x][y + 1] != 0 && nBuildings[x][y - 1] != 0) {
										if (nBuildings[x + 1][y] != 0 && nBuildings[x - 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadXSM);
										else if (nBuildings[x + 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadTWSM);
										else if (nBuildings[x - 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadTESM);
										else
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadVSM);
									}
									else if (nBuildings[x + 1][y] != 0 && nBuildings[x][y + 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadSESM);
									else if (nBuildings[x + 1][y] != 0 && nBuildings[x][y - 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadNESM);
									else if (nBuildings[x - 1][y] != 0 && nBuildings[x][y + 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadSWSM);
									else if (nBuildings[x - 1][y] != 0 && nBuildings[x][y - 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadNWSM);
									else 
										if (nBuildings[x - 1][y] != 0 || nBuildings[x + 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadOSM);
										else if (nBuildings[x][y - 1] != 0 || nBuildings[x][y + 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadVSM);
										else 
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), roadOSM);

									break;
								case 5:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), windmillSM);
									break;
								case 6:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), bakerySM);
									break;
								case 10:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleTLSM);
									break;
								case 11:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleTRSM);
									break;
								case 12:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleBLSM);
									break;
								case 13:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleBRSM);
									break;
								}
							}
						}
						break;
					case 1:		//Forest
						if (!nBuildings[x][y])
							Fill(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), 10 * fZoomOffset + (nZoom * (x - plX)), 10 * fZoomOffset + (nZoom * (y - plY)), PIXEL_THREEQUARTERS, FG_DARK_GREEN);
						else {
							if (bZoom) {
								switch (nBuildings[x][y]) {
								case 1:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), carpenter);
									break;
								case 2:
									if (nBuildings[x + 1][y] != 0 && nBuildings[x - 1][y] != 0) {
										if (nBuildings[x][y + 1] != 0 && nBuildings[x][y - 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadX);
										else if (nBuildings[x][y + 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadTN);
										else if (nBuildings[x][y - 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadTS);
										else
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadO);
									}
									else if (nBuildings[x][y + 1] != 0 && nBuildings[x][y - 1] != 0) {
										if (nBuildings[x + 1][y] != 0 && nBuildings[x - 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadX);
										else if (nBuildings[x + 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadTW);
										else if (nBuildings[x - 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadTE);
										else
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadV);
									}
									else if (nBuildings[x + 1][y] != 0 && nBuildings[x][y + 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadSE);
									else if (nBuildings[x + 1][y] != 0 && nBuildings[x][y - 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadNE);
									else if (nBuildings[x - 1][y] != 0 && nBuildings[x][y + 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadSW);
									else if (nBuildings[x - 1][y] != 0 && nBuildings[x][y - 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadNW);
									else
										if (nBuildings[x - 1][y] != 0 || nBuildings[x + 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadO);
										else if (nBuildings[x][y - 1] != 0 || nBuildings[x][y + 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadV);
										else
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadO);

									break;
								case 10:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleTL);
									break;
								case 11:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleTR);
									break;
								case 12:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleBL);
									break;
								case 13:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleBR);
									break;
								}
							}
							else {
								switch (nBuildings[x][y]) {
								case 1:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), carpenterSM);
									break;
								case 2:
									if (nBuildings[x + 1][y] != 0 && nBuildings[x - 1][y] != 0) {
										if (nBuildings[x][y + 1] != 0 && nBuildings[x][y - 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadXSM);
										else if (nBuildings[x][y + 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadTNSM);
										else if (nBuildings[x][y - 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadTSSM);
										else
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadOSM);
									}
									else if (nBuildings[x][y + 1] != 0 && nBuildings[x][y - 1] != 0) {
										if (nBuildings[x + 1][y] != 0 && nBuildings[x - 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadX);
										else if (nBuildings[x + 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadTWSM);
										else if (nBuildings[x - 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadTESM);
										else
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadVSM);
									}
									else if (nBuildings[x + 1][y] != 0 && nBuildings[x][y + 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadSESM);
									else if (nBuildings[x + 1][y] != 0 && nBuildings[x][y - 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadNESM);
									else if (nBuildings[x - 1][y] != 0 && nBuildings[x][y + 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadSWSM);
									else if (nBuildings[x - 1][y] != 0 && nBuildings[x][y - 1] != 0)
										DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadNWSM);
									else
										if (nBuildings[x - 1][y] != 0 || nBuildings[x + 1][y] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadOSM);
										else if (nBuildings[x][y - 1] != 0 || nBuildings[x][y + 1] != 0)
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadVSM);
										else
											DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), forestRoadOSM);

									break;
								case 10:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleTLSM);
									break;
								case 11:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleTRSM);
									break;
								case 12:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleBLSM);
									break;
								case 13:
									DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), castleBRSM);
									break;
								}
							}
						}
						break;
					case 2:		//Mountain
						if (bZoom) {
							if (!nBuildings[x][y])
								DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), mountain);
							else {
								DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), mine);
							}
						}
						else {
							if (!nBuildings[x][y])
								DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), mountainSM);
							else 
								DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), mineSM);
						}
						break;
					case 3: //Water
						if (bZoom) {
							if (!nBuildings[x][y])
								Fill(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), 10 * fZoomOffset + (nZoom * (x - plX)), 10 * fZoomOffset + (nZoom * (y - plY)), PIXEL_SOLID, FG_CYAN);
							else
								DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), harbor);
						}
						else
						{
							if (!nBuildings[x][y])
								Fill(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), 10 * fZoomOffset + (nZoom * (x - plX)), 10 * fZoomOffset + (nZoom * (y - plY)), PIXEL_SOLID, FG_CYAN);
							else
								DrawSprite(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), harborSM);
						}
						break;
					case 4:	//Deep Wather
						Fill(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), 10 * fZoomOffset + (nZoom * (x - plX)), 10 * fZoomOffset + (nZoom * (y - plY)), PIXEL_SOLID, FG_BLUE);
						break;
					}

					if (x == nPlayerCursorX)
						if (y == nPlayerCursorY)
							DrawCursor(x, y, plX, plY);
				}

			//Drawing the map outline
		
			DrawLine(4, 4, 56, 4);
			DrawLine(56, 4, 56, 56);
			DrawLine(56, 56, 4, 56);
			DrawLine(4, 56, 4, 4);

			Fill(57, 0, m_nScreenWidth, m_nScreenHeight, FG_BLACK);
			Fill(0, 57, m_nScreenWidth, m_nScreenHeight, FG_BLACK);

			return;
		}

		void play(){
			
			//--Camera Handling
			//-If the map is zoomed
			if (bZoom) {
				if (nPlayerCursorX < 5 && nPlayerCursorY < 5) 
					loadMap();
				
				if (nPlayerCursorX >= 5 && nPlayerCursorY < 5) 
					loadMap(5, 0);
				
				if (nPlayerCursorX <= 5 && nPlayerCursorY >= 5) 
					loadMap(0, 5);
				
				if (nPlayerCursorX >= 5 && nPlayerCursorY >= 5) 
					loadMap(5, 5);
				

				if (nPlayerCursorX >= 10 && nPlayerCursorY < 10) 
					loadMap(10, 0);
				
				if (nPlayerCursorX <= 10 && nPlayerCursorY >= 10) 
					loadMap(0, 10);
				

				if (nPlayerCursorX >= 5 && nPlayerCursorY >= 10) 
					loadMap(5, 10);
				

				if (nPlayerCursorX >= 10 && nPlayerCursorY >= 5) 
					loadMap(10, 5);
				

				if (nPlayerCursorX >= 10 && nPlayerCursorY >= 10) 
					loadMap(10, 10);
				

				if (nPlayerCursorX >= 15 && nPlayerCursorY < 15) 
					loadMap(15, 0);
				
				if (nPlayerCursorX <= 15 && nPlayerCursorY >= 15) 
					loadMap(0, 15);
				
				
				if (nPlayerCursorX >= 5 && nPlayerCursorY >= 15) 
					loadMap(5, 15);
				

				if (nPlayerCursorX >= 15 && nPlayerCursorY >= 5) 
					loadMap(15, 5);
				

				if (nPlayerCursorX >= 10 && nPlayerCursorY >= 15) 
					loadMap(10, 15);
				
				

				if (nPlayerCursorX >= 15 && nPlayerCursorY >= 10) 
					loadMap(15, 10);
				

				if (nPlayerCursorX >= 15 && nPlayerCursorY >= 15) 
					loadMap(15, 15);
				

			}
			//-If the map is not zoomed
			else {
				if (nPlayerCursorX < 10 && nPlayerCursorY < 10) 
					loadMap();
				
				if (nPlayerCursorX >= 10 && nPlayerCursorY < 10) 
					loadMap(10, 0);
				
				if (nPlayerCursorX <= 10 && nPlayerCursorY >= 10) 
					loadMap(0, 10);
				
				if (nPlayerCursorX >= 10 && nPlayerCursorY >= 10) 
					loadMap(10, 10);
				
			}

			//Printing the cursor coordinates
			DrawString(0, 0, std::to_wstring(nPlayerCursorX));
			if (nPlayerCursorX > 9) {
				Draw(2, 0, L',');
				DrawString(3, 0, std::to_wstring(nPlayerCursorY));
			}
			else {
				Draw(1, 0, L',');
				DrawString(2, 0, std::to_wstring(nPlayerCursorY));
			}

			//Printing tile menu frame
			menuFrame(50, -5);

			//Printing resources
			DrawString(4, 3, L"Wheat= ");
			DrawString(11, 3, std::to_wstring((int)fResources[1]));
			DrawString(15, 3, L"Flour= ");
			DrawString(21, 3, std::to_wstring((int)fResources[2]));
			DrawString(25, 3, L"Wood= ");
			DrawString(31, 3, std::to_wstring((int)fResources[0]));
			DrawString(35, 3, L"Stone= ");
			DrawString(42, 3, std::to_wstring((int)fResources[4]));
			DrawString(46, 3, L"Iron= ");
			DrawString(52, 3, std::to_wstring((int)fResources[5]));
			DrawString(56, 3, L"Food= ");
			DrawString(62, 3, std::to_wstring((int)fResources[3]));
			DrawString(66, 3, L"Citizens= ");
			DrawString(76, 3, std::to_wstring(nUnenplyedCitizens));
			DrawString(78, 3, L"/");
			DrawString(79, 3, std::to_wstring(nTotCitizens));

			//Shows the current tile info
			DrawString(70, 10, L"Tile Type: ");
			switch (nMap[nPlayerCursorX][nPlayerCursorY]) {
			case 0:
				DrawString(81, 10, L"Grass");
				break;
			case 1:
				DrawString(81, 10, L"Forest");
				DrawString(70, 15, L"Resources: ");
				DrawString(81, 15, L"Wood ");
				DrawString(86, 15, std::to_wstring((int)nTyleResources[0][nPlayerCursorX][nPlayerCursorY]));
				break;
			case 2:
				DrawString(81, 10, L"Mountain");
				DrawString(70, 15, L"Resources: ");
				DrawString(81, 15, L"Stone");
				DrawString(87, 15, std::to_wstring((int)nTyleResources[2][nPlayerCursorX][nPlayerCursorY]));
				DrawString(91, 15, L"Iron");
				DrawString(96, 15, std::to_wstring((int)nTyleResources[3][nPlayerCursorX][nPlayerCursorY]));
				break;
			case 3:
				DrawString(81, 10, L"Wather");
				DrawString(70, 15, L"Resources: ");
				DrawString(81, 15, L"Fish ");
				DrawString(86, 15, std::to_wstring((int)nTyleResources[1][nPlayerCursorX][nPlayerCursorY]));
				break;
			case 4:
				DrawString(81, 10, L"Deep Wather");
				DrawString(70, 15, L"Resources: ");
				DrawString(81, 15, L"Fish ");
				DrawString(86, 15, std::to_wstring((int)nTyleResources[1][nPlayerCursorX][nPlayerCursorY]));
				break;
			}

			//Tile/Build menu printing
			if (bCastle) {
				//Tile Menu printing
				if (!bBuildMenu) {

					//Shows if a building is in the current tile 
					DrawString(70, 13, L"Building: ");
					switch (nMap[nPlayerCursorX][nPlayerCursorY]) {
					case 0:
						switch (nBuildings[nPlayerCursorX][nPlayerCursorY]) {
						case 1:
							DrawString(80, 13, L"Farm");
							break;
						case 2:
							DrawString(80, 13, L"Field");
							break;
						case 3:
							DrawString(80, 13, L"House");
							break;
						case 4:
							DrawString(80, 13, L"Road");
							break;
						case 5:
							DrawString(80, 13, L"Windmill");
							break;
						case 10:
							DrawString(80, 13, L"Castle");
							break;
						case 11:
							DrawString(80, 13, L"Castle");
							break;
						case 12:
							DrawString(80, 13, L"Castle");
							break;
						case 13:
							DrawString(80, 13, L"Castle");
							break;
						default:
							DrawString(80, 13, L"None");
							break;
						}
						break;
					case 1:
						switch (nBuildings[nPlayerCursorX][nPlayerCursorY]) {
						case 1:
							DrawString(80, 13, L"Carpenter");
							break;
						case 2:
							DrawString(80, 13, L"Road");
							break;
						case 10:
							DrawString(80, 13, L"Castle");
							break;
						case 11:
							DrawString(80, 13, L"Castle");
							break;
						case 12:
							DrawString(80, 13, L"Castle");
							break;
						case 13:
							DrawString(80, 13, L"Castle");
							break;
						default:
							DrawString(80, 13, L"None");
							break;
						}
						break;
					case 2:
						if (nBuildings[nPlayerCursorX][nPlayerCursorY])
							DrawString(80, 13, L"Mine");
						else
							DrawString(80, 13, L"None");
						break;
					case 3:
						if (nBuildings[nPlayerCursorX][nPlayerCursorY])
							DrawString(80, 13, L"Harbor");
						else 
							DrawString(80, 13, L"None");
						break;
					}

					//Show if the building is active
					if (nBuildings[nPlayerCursorX][nPlayerCursorY] != 0) {
						if (nBuildings[nPlayerCursorX][nPlayerCursorY] != 10 &&
							nBuildings[nPlayerCursorX][nPlayerCursorY] != 11 &&
							nBuildings[nPlayerCursorX][nPlayerCursorY] != 12 &&
							nBuildings[nPlayerCursorX][nPlayerCursorY] != 13) {

							DrawString(70, 17, L"Active: ");
							if (bActive[nPlayerCursorX][nPlayerCursorY])
								DrawString(78, 17, L"Yes");
							else
								DrawString(78, 17, L"No");
						}
					}

					//Highlights the selected tile menu option 
					switch (nCursor) {
					case 0:
						DrawString(65, 20, L"Build", BG_WHITE);
						if (nBuildings[nPlayerCursorX][nPlayerCursorY] != 0 && nBuildings[nPlayerCursorX][nPlayerCursorY] < 10)
							DrawString(65, 25, L"Remove building");
						DrawString(65, 50, L"Back");
						break;
					case 1:
						if (nBuildings[nPlayerCursorX][nPlayerCursorY] != 0 && nBuildings[nPlayerCursorX][nPlayerCursorY] < 10) {
							DrawString(65, 20, L"Build");
							DrawString(65, 25, L"Remove building", BG_WHITE);
							DrawString(65, 50, L"Back");
						}
						else {
							DrawString(65, 20, L"Build");
							DrawString(65, 50, L"Back", BG_WHITE);
						}
						break;
					case 2:
						if (nBuildings[nPlayerCursorX][nPlayerCursorY] != 0 && nBuildings[nPlayerCursorX][nPlayerCursorY] < 10) {
							DrawString(65, 20, L"Build");
							DrawString(65, 25, L"Remove building");
							DrawString(65, 50, L"Back", BG_WHITE);
						}
						break;
					default:
						DrawString(65, 20, L"Build");
						if (nBuildings[nPlayerCursorX][nPlayerCursorY] != 0 && nBuildings[nPlayerCursorX][nPlayerCursorY] < 10)
							DrawString(65, 25, L"Remove building");
						DrawString(65, 50, L"Back");
						break;
					}
				}
				//Build Menu printing
				else {
					//Printing the builidngs according to the tile type
					switch (nMap[nPlayerCursorX][nPlayerCursorY]) {
					case 0:
						nMaxCursorPos = 7;
						switch (nCursor) {
						case 0:	//Grass
							DrawString(65, 20, L"Farm", BG_WHITE);
							DrawString(65, 25, L"Field");
							DrawString(65, 30, L"House");
							DrawString(65, 35, L"Road");
							DrawString(65, 40, L"Windmill");
							DrawString(65, 45, L"Bakery");
							DrawString(65, 50, L"Back");

							DrawString(75, 20, L"Requirements: ");
							DrawString(75, 23, L"Wood: 20");
							DrawString(75, 25, L"Workers: 2");
							break;
						case 1:
							DrawString(65, 20, L"Farm");
							DrawString(65, 25, L"Field", BG_WHITE);
							DrawString(65, 30, L"House");
							DrawString(65, 35, L"Road");
							DrawString(65, 40, L"Windmill");
							DrawString(65, 45, L"Bakery");
							DrawString(65, 50, L"Back");

							DrawString(75, 20, L"Requirements: ");
							DrawString(75, 23, L"Wheat: 25");
							DrawString(75, 25, L"Workers: 2");
							break;
						case 2:
							DrawString(65, 20, L"Farm");
							DrawString(65, 25, L"Field");
							DrawString(65, 30, L"House", BG_WHITE);
							DrawString(65, 35, L"Road");
							DrawString(65, 40, L"Windmill");
							DrawString(65, 45, L"Bakery");
							DrawString(65, 50, L"Back");

							DrawString(75, 20, L"Requirements: ");
							DrawString(75, 23, L"Wood: 30");
							DrawString(75, 25, L"Workers: +10");
							break;
						case 3:
							DrawString(65, 20, L"Farm");
							DrawString(65, 25, L"Field");
							DrawString(65, 30, L"House");
							DrawString(65, 35, L"Road", BG_WHITE);
							DrawString(65, 40, L"Windmill");
							DrawString(65, 45, L"Bakery");
							DrawString(65, 50, L"Back");

							DrawString(75, 20, L"Requirements: ");
							DrawString(75, 23, L"None");
							break;
						case 4:
							DrawString(65, 20, L"Farm");
							DrawString(65, 25, L"Field");
							DrawString(65, 30, L"House");
							DrawString(65, 35, L"Road");
							DrawString(65, 40, L"Windmill", BG_WHITE);
							DrawString(65, 45, L"Bakery");
							DrawString(65, 50, L"Back");

							DrawString(75, 20, L"Requirements: ");
							DrawString(75, 23, L"Wood: 30");
							DrawString(75, 25, L"Stone: 20");
							DrawString(75, 27, L"Workers: 2");
							break;
						case 5:
							DrawString(65, 20, L"Farm");
							DrawString(65, 25, L"Field");
							DrawString(65, 30, L"House");
							DrawString(65, 35, L"Road");
							DrawString(65, 40, L"Windmill");
							DrawString(65, 45, L"Bakery", BG_WHITE);
							DrawString(65, 50, L"Back");

							DrawString(75, 20, L"Requirements: ");
							DrawString(75, 23, L"Wood: 10");
							DrawString(75, 25, L"Workers: 2");
							break;
						case 6:
							DrawString(65, 20, L"Farm");
							DrawString(65, 25, L"Field");
							DrawString(65, 30, L"House");
							DrawString(65, 35, L"Road");
							DrawString(65, 40, L"Windmill");
							DrawString(65, 45, L"Bakery");
							DrawString(65, 50, L"Back", BG_WHITE);
							break;
						}
						break;
					case 1:	//Forest
						nMaxCursorPos = 3;
						switch (nCursor) {
						case 0:
							DrawString(65, 20, L"Carpenter Workshop", BG_WHITE);
							DrawString(65, 25, L"Road");
							DrawString(65, 50, L"Back");

							DrawString(75, 20, L"Requirements: ");
							DrawString(75, 23, L"Wood: 15");
							DrawString(75, 25, L"Workers: 2");
							break;
						case 1:
							DrawString(65, 20, L"Carpenter Workshop");
							DrawString(65, 25, L"Road", BG_WHITE);
							DrawString(65, 50, L"Back");

							DrawString(75, 20, L"Requirements: ");
							DrawString(75, 23, L"None");
							break;
						case 2:
							DrawString(65, 20, L"Carpenter Workshop");
							DrawString(65, 25, L"Road");
							DrawString(65, 50, L"Back", BG_WHITE);
							break;
						}
						break;
					case 2:	//mountain
						nMaxCursorPos = 2;
						switch (nCursor) {
						case 0:
							DrawString(65, 20, L"Mine", BG_WHITE);
							DrawString(65, 50, L"Back");

							DrawString(75, 20, L"Requirements: ");
							DrawString(75, 23, L"Wood: 35");
							DrawString(75, 25, L"Workers: 5");
							break;
						case 1:
							DrawString(65, 20, L"Mine");
							DrawString(65, 50, L"Back", BG_WHITE);
							break;
						}
						break;
					case 3: //Water
						nMaxCursorPos = 2;
						switch (nCursor) {
						case 0:
							DrawString(65, 20, L"Harbor", BG_WHITE);
							DrawString(65, 50, L"Back");

							DrawString(75, 20, L"Requirements: ");
							DrawString(75, 23, L"Wood: 40");
							DrawString(75, 25, L"Workers: 5");
							break;
						case 1:
							DrawString(65, 20, L"Harbor");
							DrawString(65, 50, L"Back", BG_WHITE);
							break;
						}
						break;
					case 4: //Deep water
						switch (nCursor) {

						}
						break;
					}

				}
			}
			//Castle positioning menu printing
			else {
				switch (nCursor) {
				case 0:
					DrawString(65, 20, L"Place castle", BG_WHITE);
					DrawString(65, 50, L"Back");
					break;
				case 1:
					DrawString(65, 20, L"Place castle");
					DrawString(65, 50, L"Back",BG_WHITE);
					break;
				default:
					DrawString(65, 20, L"Place castle");
					DrawString(65, 50, L"Back");
					break;
				}
			}

			//Map movement and zoom handling
			if (!bCursor) {

				//Enabales the tile Menu
				if (GetKey(VK_RETURN).bPressed) {
					bCursor = 1;
					nCursor = 0;
				}

				//Cursor movement
				if (GetKey(VK_UP).bPressed)
					nPlayerCursorY--;
				if (GetKey(VK_DOWN).bPressed)
					nPlayerCursorY++;
				if (GetKey(VK_LEFT).bPressed)
					nPlayerCursorX--;
				if (GetKey(VK_RIGHT).bPressed)
					nPlayerCursorX++;
				//Correcting cursor overflow
				if (nPlayerCursorX > nMapWidth - 1)
					nPlayerCursorX = nMapWidth - 1;
				if (nPlayerCursorY > nMapHeight - 1)
					nPlayerCursorY = nMapHeight - 1;
				if (nPlayerCursorX < 0)
					nPlayerCursorX = 0;
				if (nPlayerCursorY < 0)
					nPlayerCursorY = 0;

				//Correcting zoom overflow
				if (nZoom > 10) {
					nZoom = 10;
					fZoomOffset = 1.5;
				}
				if (nZoom < 5) {
					nZoom = 5;
					fZoomOffset = 1;
				}
				else {
					//Zoom increment/decrement
					if (GetKey(VK_PRIOR).bPressed) {
						nZoom *= 2;
						fZoomOffset += 0.5f;
						bZoom = 1;
					}
					else if (GetKey(VK_NEXT).bPressed) {
						nZoom /= 2;
						fZoomOffset -= 0.5f;
						bZoom = 0;
					}
				}

			}
			//Tile / Build / Castle positioning Menu handling
			else {

				//Cursor movement
				if (GetKey(VK_UP).bPressed)
					nCursor--;
				if (GetKey(VK_DOWN).bPressed)
					nCursor++;

				//Tile/Build Menu handling
				if (bCastle) {
					//Tile Menu handling
					if (!bBuildMenu) {

						//Correcting cursor overflow
						if (nBuildings[nPlayerCursorX][nPlayerCursorY] != 0 && nBuildings[nPlayerCursorX][nPlayerCursorY] < 10) {
							if (nCursor > 2)
								nCursor = 2;
						}
						else {
							if (nCursor > 1)
								nCursor = 1;
						}
						if (nCursor < 0)
							nCursor = 0;

						//Interpreting input
						if (GetKey(VK_RETURN).bPressed)
							switch (nCursor) {
							case 0:
								bBuildMenu = 1;
								nCursor = 0;
								break;
							case 1:
								if (nBuildings[nPlayerCursorX][nPlayerCursorY] != 0 && nBuildings[nPlayerCursorX][nPlayerCursorY] < 10) {
									switch(nMap[nPlayerCursorX][nPlayerCursorY]){
									case 0:
										switch (nBuildings[nPlayerCursorX][nPlayerCursorY]) {
										case 1:
											if(bActive[nPlayerCursorX][nPlayerCursorY] == 1)
												nUnenplyedCitizens += 2;
											bActive[nPlayerCursorX][nPlayerCursorY] = 0;
											nBuildingsCount[0] --;
											break;
										case 2:
											if (bActive[nPlayerCursorX][nPlayerCursorY] == 1)
												nUnenplyedCitizens += 2;
											bActive[nPlayerCursorX][nPlayerCursorY] = 0;
											nBuildingsCount[6] --;
											break;
										case 3:
											nUnenplyedCitizens -= 10;
											nTotCitizens -= 10;
											break;
										case 5:
											if (bActive[nPlayerCursorX][nPlayerCursorY] == 1)
												nUnenplyedCitizens += 2;
											bActive[nPlayerCursorX][nPlayerCursorY] = 0;
											nBuildingsCount[1] --;
											break;
										case 6:
											if (bActive[nPlayerCursorX][nPlayerCursorY] == 1)
												nUnenplyedCitizens += 2;
											bActive[nPlayerCursorX][nPlayerCursorY] = 0;
											nBuildingsCount[2] --;
											break;
										}
										break;
									case 1:
										switch (nBuildings[nPlayerCursorX][nPlayerCursorY]) {
										case 1:
											if (bActive[nPlayerCursorX][nPlayerCursorY] == 1)
												nUnenplyedCitizens += 2;
											bActive[nPlayerCursorX][nPlayerCursorY] = 0;
											nBuildingsCount[3] --;
										}
										break;
									case 2:
										switch (nBuildings[nPlayerCursorX][nPlayerCursorY]) {
										case 1:
											if (bActive[nPlayerCursorX][nPlayerCursorY] == 1)
												nUnenplyedCitizens += 5;
											bActive[nPlayerCursorX][nPlayerCursorY] = 0;
											nBuildingsCount[4] --;
										}
										break;
									case 3:
										switch (nBuildings[nPlayerCursorX][nPlayerCursorY]) {
										case 1:
											if (bActive[nPlayerCursorX][nPlayerCursorY] == 1)
												nUnenplyedCitizens += 5;
											bActive[nPlayerCursorX][nPlayerCursorY] = 0;
											nBuildingsCount[5] --;
										}
										break;
									}
									
									nBuildings[nPlayerCursorX][nPlayerCursorY] = 0;
									nCursor = 0;
								}
								else {
									bCursor = 0;
									nCursor = 10;
								}
								break;
							case 2:
								if (nBuildings[nPlayerCursorX][nPlayerCursorY] != 0 && nBuildings[nPlayerCursorX][nPlayerCursorY] < 10) {
									bCursor = 0;
									nCursor = 10;
								}
								break;
							}
					}
					//Build Menu handling
					else {

						//Correcting cursor overflow
						if (nCursor > nMaxCursorPos - 1)
							nCursor = nMaxCursorPos - 1;
						if (nCursor < 0)
							nCursor = 0;

						//Interpreting input
						if (GetKey(VK_RETURN).bPressed) {

							if (nCursor == nMaxCursorPos - 1) {
								bBuildMenu = 0;
								nCursor = 0;
							}
							else {

								switch (nMap[nPlayerCursorX][nPlayerCursorY]) {
								case 0:		//Grass
									switch (nCursor) {
									case 0:	//Farm
										if (fResources[0] >= 20) {
											fResources[0] -= 20;
											if (nUnenplyedCitizens >= 2) {
												nUnenplyedCitizens -= 2;
												bActive[nPlayerCursorX][nPlayerCursorY] = 1;
											}
											nBuildings[nPlayerCursorX][nPlayerCursorY] = 1;
											nBuildingsCount[0] ++;
											bBuildMenu = 0;
											bCursor = 0;
											nCursor = 10;
										}
										break;
									case 1:	//Field
										if (fResources[1] >= 25) {
											fResources[1] -= 25;
											if (nUnenplyedCitizens >= 2) {
												nUnenplyedCitizens -= 2;
												bActive[nPlayerCursorX][nPlayerCursorY] = 1;
											}
											nBuildings[nPlayerCursorX][nPlayerCursorY] = 2;
											nBuildingsCount[6] ++;
											bBuildMenu = 0;
											bCursor = 0;
											nCursor = 10;
										}
										break;
									case 2: //House
										if (fResources[0] >= 30) {
											fResources[0] -= 30;
											nTotCitizens += 10;
											nUnenplyedCitizens += 10;
											nBuildings[nPlayerCursorX][nPlayerCursorY] = 3;
											bBuildMenu = 0;
											bCursor = 0;
											nCursor = 10;
										}
										break;
									case 3: //Road
										nBuildings[nPlayerCursorX][nPlayerCursorY] = 4;
										bBuildMenu = 0;
										bCursor = 0;
										nCursor = 10;
										break;
									case 4: //Windmill
										if (fResources[0] >= 30 && fResources[4] >= 20) {
											fResources[0] -= 30;
											fResources[4] -= 20;
											if (nUnenplyedCitizens >= 2) {
												nUnenplyedCitizens -= 2;
												bActive[nPlayerCursorX][nPlayerCursorY] = 1;
											}
											nBuildings[nPlayerCursorX][nPlayerCursorY] = 5;
											nBuildingsCount[1] ++;
											bBuildMenu = 0;
											bCursor = 0;
											nCursor = 10;
										}
										break;
									case 5: //Bakery
										if (fResources[0] >= 10) {
											fResources[0] -= 10;
											if (nUnenplyedCitizens >= 2) {
												nUnenplyedCitizens -= 2;
												bActive[nPlayerCursorX][nPlayerCursorY] = 1;
											}
											nBuildings[nPlayerCursorX][nPlayerCursorY] = 6;
											nBuildingsCount[2] ++;
											bBuildMenu = 0;
											bCursor = 0;
											nCursor = 10;
										}
										break;
									}
									break;
								case 1:		//Forest
									switch (nCursor) {
									case 0:	//Carpenter
										if (fResources[0] >= 15) {
											fResources[0] -= 15;
											if (nUnenplyedCitizens >= 2) {
												nUnenplyedCitizens -= 2;
												bActive[nPlayerCursorX][nPlayerCursorY] = 1;
											}
											nBuildings[nPlayerCursorX][nPlayerCursorY] = 1;
											nBuildingsCount[3] ++;
											bBuildMenu = 0;
											bCursor = 0;
											nCursor = 10;
										}
										break;
									case 1:	//Road
										nTyleResources[0][nPlayerCursorX][nPlayerCursorY] /= 2;
										nBuildings[nPlayerCursorX][nPlayerCursorY] = 2;
										bBuildMenu = 0;
										bCursor = 0;
										nCursor = 10;
										break;
									}
									break;
								case 2:
									switch (nCursor) {
									case 0: //Mine
										if (fResources[0] >= 35) {
											fResources[0] -= 35;
											if (nUnenplyedCitizens >= 5) {
												nUnenplyedCitizens -= 5;
												bActive[nPlayerCursorX][nPlayerCursorY] = 1;
											}
											nBuildings[nPlayerCursorX][nPlayerCursorY] = 1;
											nBuildingsCount[4] ++;
											bBuildMenu = 0;
											bCursor = 0;
											nCursor = 10;
										}
										break;
									}
									break;
								case 3:
									switch (nCursor) {
									case 0:	//Harbor
										if (fResources[0] >= 40) {
											fResources[0] -= 40;
											if (nUnenplyedCitizens >= 5) {
												nUnenplyedCitizens -= 5;
												bActive[nPlayerCursorX][nPlayerCursorY] = 1;
											}
											nBuildings[nPlayerCursorX][nPlayerCursorY] = 1;
											nBuildingsCount[5] ++;
											bBuildMenu = 0;
											bCursor = 0;
											nCursor = 10;
										}
										break;
									}
									break;
								}
							}
						}

					}
				}
				//Castle positioning menu handling
				else {
					//Correcting cursor overflow
					if (nCursor > 1)
						nCursor = 1;
					if (nCursor < 0)
						nCursor = 0;
					
					//interpreting input
					if (GetKey(VK_RETURN).bPressed) {
						switch (nCursor) {
						case 0:
							if (nMap[nPlayerCursorX][nPlayerCursorY] < 2 && nMap[nPlayerCursorX + 1][nPlayerCursorY] < 2 && nMap[nPlayerCursorX][nPlayerCursorY + 1] < 2 && nMap[nPlayerCursorX + 1][nPlayerCursorY + 1] < 2) {
								nBuildings[nPlayerCursorX][nPlayerCursorY] = 10;
								nBuildings[nPlayerCursorX + 1][nPlayerCursorY] = 11;
								nBuildings[nPlayerCursorX][nPlayerCursorY + 1] = 12;
								nBuildings[nPlayerCursorX + 1][nPlayerCursorY + 1] = 13;

								nTyleResources[0][nPlayerCursorX][nPlayerCursorY] = 0;
								nTyleResources[0][nPlayerCursorX + 1][nPlayerCursorY] = 0;
								nTyleResources[0][nPlayerCursorX][nPlayerCursorY + 1] = 0;
								nTyleResources[0][nPlayerCursorX + 1][nPlayerCursorY + 1] = 0;

								nUnenplyedCitizens = 10;
								nTotCitizens = 10;
								
								bCastle = 1;
								bCursor = 0;
								nCursor = 10;
							}
							break;
						case 1:
							bCursor = 0;
							nCursor = 10;
							break;
						}
					}

				}
			}

			//Save game
			if (GetKey(VK_F10).bPressed)
				Save();

			//Quit
			if (GetKey(VK_ESCAPE).bPressed) {
				bCursor = 0;
				nCursor = 0;
				bZoom = 0;
				nZoom = 5;
				fZoomOffset = 1;
				state = 1;
				memset(nMap, 0, sizeof(nMap));
				memset(nTyleResources, 0, sizeof(nTyleResources));
				memset(nBuildings, 0, sizeof(nBuildings));
				memset(fResources, 0, sizeof(fResources));
				fResources[0] = 15.0f;
				fResources[3] = 50.0f;
				memset(nBuildingsCount, 0, sizeof(nBuildingsCount));
				genOp.bGrass = 1;
				genOp.bForest = 1;
				genOp.bMountain = 1;
				genOp.bWather = 1;
				genOp.bDeepWather = 1;
				genOp.nActiveTiles = 5;
			}

			return;
		}

		void updateBuildings(float fElapsedTime) {

			if (fUptime >= 1.0f) {

				for (int y = 0; y < nMapHeight; y++) {
					for (int x = 0; x < nMapWidth; x++) {

						if (nBuildingsCount[0] > 0) {	//Farm
							if (nMap[x][y] == 0) {
								if (nBuildings[x][y] == 1) {
									if (bActive[x][y] == 1) {
										fResources[1] += 0.2f;
									}
									else if (nUnenplyedCitizens >= 2) {
										nUnenplyedCitizens -= 2;
										bActive[x][y] = 1;
									}
								}
							}
						}


						if (nBuildingsCount[6] > 0) {	//Field
							if (nMap[x][y] == 0) {
								if (nBuildings[x][y] == 2) {
									if (bActive[x][y] == 1) {
										fResources[1] += 0.3f * nBuildingsCount[6];
									}
									else if (nUnenplyedCitizens >= 2) {
										nUnenplyedCitizens -= 2;
										bActive[x][y] = 1;
									}
								}
							}
						}

						if (nBuildingsCount[1] > 0) {		//Windmill
							if (nMap[x][y] == 0) {
								if (nBuildings[x][y] == 5) {
									if (bActive[x][y] == 1) {
										if (fResources[1] >= 0.2) {
											fResources[2] += 0.1f * nBuildingsCount[1];
											fResources[1] -= 0.2f * nBuildingsCount[1];
										}
									}
									else if (nUnenplyedCitizens >= 2) {
										nUnenplyedCitizens -= 2;
										bActive[x][y] = 1;
									}
								}
							}
						}

						if (nBuildingsCount[3] > 0) {	//Carpenter
							if (nMap[x][y] == 1){
								if (nBuildings[x][y] == 1) {
									if (bActive[x][y] == 1) {
										if (nTyleResources[0][x][y] > 0) {
											fResources[0] += 0.5;
											nTyleResources[0][x][y] -= 0.3f;
										}
									}
									else if (nUnenplyedCitizens >= 2) {
										nUnenplyedCitizens -= 2;
										bActive[x][y] = 1;
									}
								}
							}
						}

						if (nBuildingsCount[4] > 0) {	//Mine
							if (nMap[x][y] == 2) {
								if (nBuildings[x][y] == 1) {
									if (bActive[x][y] == 1) {
										if (nTyleResources[2][x][y] > 0) {
											fResources[4] += 0.2;
											nTyleResources[2][x][y] -= 0.2f;
										}
										if (nTyleResources[3][x][y] > 0) {
											fResources[5] += 0.2;
											nTyleResources[3][x][y] -= 0.2f;
										}
									}
									else if (nUnenplyedCitizens >= 5) {
										nUnenplyedCitizens -= 5;
										bActive[x][y] = 1;
									}
								}
							}
						}

						if (nBuildingsCount[2] > 0) {	//Bakery
							if (nMap[x][y] == 0) {
								if (nBuildings[x][y] == 6) {
									if (bActive[x][y] == 1) {
										if (fResources[2] >= 0.1) {
											fResources[3] += 0.2 * nBuildingsCount[2];
											fResources[2] -= 0.1 * nBuildingsCount[2];
										}
									}
									else if (nUnenplyedCitizens >= 2) {
										nUnenplyedCitizens -= 2;
										bActive[x][y] = 1;
									}
								}
							}
						}

						if (nBuildingsCount[5] > 0) {	//Harbor
							if (nMap[x][y] == 3) {
								if (nBuildings[x][y] == 1) {
									if (bActive[x][y] == 1) {
										if (nTyleResources[1][x][y] > 0) {
											fResources[3] += 0.2f;
											nTyleResources[1][x][y] -= 0.2f;
										}
									}
									else if (nUnenplyedCitizens >= 5) {
										nUnenplyedCitizens -= 5;
										bActive[x][y] = 1;
									}
								}
							}
						}
					}
				}

				if (nTotCitizens > 0) {
					if (fResources[3] <= 0)
						if (nTotCitizens == 0)
							state = 4;
						else
							nTotCitizens -= 0.001;
					else 
						fResources[3] -= 0.005 * nTotCitizens;
				}

				fUptime = 0;
			}
			else {
				fUptime += fElapsedTime;
			}

			return;

		}

		void GameOver() {

			//G
			DrawLine(30, 20, 33, 20);
			DrawLine(30, 20, 30, 25);
			DrawLine(30, 25, 33, 25);
			DrawLine(33, 25, 33, 23);
			Draw(32, 23);

			//A
			DrawLine(35, 20, 35, 25);
			DrawLine(35, 20, 38, 20);
			DrawLine(38, 20, 38, 25);
			DrawLine(35, 23, 38, 23);

			//M
			DrawLine(40, 20, 40, 25);
			DrawLine(40, 20, 42, 22);
			DrawLine(42, 22, 44, 20);
			DrawLine(44, 20, 44, 25);

			//E
			DrawLine(46, 20, 46, 25);
			DrawLine(46, 20, 49, 20);
			DrawLine(46, 23, 49, 23);
			DrawLine(46, 25, 49, 25);



			//O
			DrawLine(54, 20, 57, 20);
			DrawLine(54, 20, 54, 25);
			DrawLine(54, 25, 57, 25);
			DrawLine(57, 25, 57, 20);

			//V
			DrawLine(59, 20, 61, 25);
			DrawLine(61, 25, 63, 20);

			//E
			DrawLine(65, 20, 65, 25);
			DrawLine(65, 20, 68, 20);
			DrawLine(65, 23, 68, 23);
			DrawLine(65, 25, 68, 25);

			//R
			DrawLine(70, 20, 73, 20);
			DrawLine(70, 20, 70, 25);
			DrawLine(70, 22, 73, 22);
			DrawLine(73, 22, 73, 20);
			DrawLine(70, 22, 73, 25);

			//All your citizen died

			DrawString(40, 30, L"All yor citizens died");

			if (GetKey(VK_RETURN).bPressed)
				state = 1;

		}

	protected: 
		virtual bool OnUserCreate() {

			for (const auto& entry : std::experimental::filesystem::directory_iterator(path)) {
				if (nSaveNumber == 9) break;
				wsSavesName[nSaveNumber] = entry.path();
				nSaveNumber++;
				
			}

			farm = new olcSprite(L"Sprites/farm.spr");
			farmSM = new olcSprite(L"Sprites/farmSM.spr");
			field = new olcSprite(L"Sprites/field.spr");
			fieldSM = new olcSprite(L"Sprites/fieldSM.spr");
			house = new olcSprite(L"Sprites/house.spr");
			houseSM = new olcSprite(L"Sprites/houseSM.spr");
			windmill = new olcSprite(L"Sprites/windmill.spr");
			windmillSM = new olcSprite(L"Sprites/windmillSM.spr");
			carpenter = new olcSprite(L"Sprites/carpenter.spr");
			carpenterSM = new olcSprite(L"Sprites/carpenterSM.spr");
			mountain = new olcSprite(L"Sprites/mountain.spr");
			mountainSM = new olcSprite(L"Sprites/mountainSM.spr");
			bakery = new olcSprite(L"Sprites/bakery.spr");
			bakerySM = new olcSprite(L"Sprites/bakerySM.spr");
			mine = new olcSprite(L"Sprites/mine.spr");
			mineSM = new olcSprite(L"Sprites/mineSM.spr");
			harbor = new olcSprite(L"Sprites/harbor.spr");
			harborSM = new olcSprite(L"Sprites/harborSM.spr");
			roadO = new olcSprite(L"Sprites/roadO.spr");
			roadOSM = new olcSprite(L"Sprites/roadOSM.spr");
			roadV = new olcSprite(L"Sprites/roadV.spr");
			roadVSM = new olcSprite(L"Sprites/roadVSM.spr");
			roadTN = new olcSprite(L"Sprites/roadTN.spr");
			roadTS = new olcSprite(L"Sprites/roadTS.spr");
			roadTE = new olcSprite(L"Sprites/roadTE.spr");
			roadTW = new olcSprite(L"Sprites/roadTW.spr");
			roadNE = new olcSprite(L"Sprites/roadNE.spr");
			roadNW = new olcSprite(L"Sprites/roadNW.spr");
			roadSE = new olcSprite(L"Sprites/roadSE.spr");
			roadSW = new olcSprite(L"Sprites/roadSW.spr");
			roadX = new olcSprite(L"Sprites/roadX.spr");
			roadXSM = new olcSprite(L"Sprites/roadXSM.spr");
			roadNESM = new olcSprite(L"Sprites/roadNESM.spr");
			roadNWSM = new olcSprite(L"Sprites/roadNWSM.spr");
			roadSESM = new olcSprite(L"Sprites/roadSESM.spr");
			roadSWSM = new olcSprite(L"Sprites/roadSWSM.spr");
			roadTNSM = new olcSprite(L"Sprites/roadTNSM.spr");
			roadTSSM = new olcSprite(L"Sprites/roadTSSM.spr");
			roadTESM = new olcSprite(L"Sprites/roadTESM.spr");
			roadTWSM = new olcSprite(L"Sprites/roadTWSM.spr");
			forestRoadO = new olcSprite(L"Sprites/forestRoadO.spr");
			forestRoadOSM = new olcSprite(L"Sprites/forestRoadOSM.spr");
			forestRoadV = new olcSprite(L"Sprites/forestRoadV.spr");
			forestRoadVSM = new olcSprite(L"Sprites/forestRoadVSM.spr");
			forestRoadTN = new olcSprite(L"Sprites/forestRoadTN.spr");
			forestRoadTS = new olcSprite(L"Sprites/forestRoadTS.spr");
			forestRoadTE = new olcSprite(L"Sprites/forestRoadTE.spr");
			forestRoadTW = new olcSprite(L"Sprites/forestRoadTW.spr");
			forestRoadNE = new olcSprite(L"Sprites/forestRoadNE.spr");
			forestRoadNW = new olcSprite(L"Sprites/forestRoadNW.spr");
			forestRoadSE = new olcSprite(L"Sprites/forestRoadSE.spr");
			forestRoadSW = new olcSprite(L"Sprites/forestRoadSW.spr");
			forestRoadX = new olcSprite(L"Sprites/forestRoadX.spr");
			forestRoadXSM = new olcSprite(L"Sprites/forestRoadXSM.spr");
			forestRoadNESM = new olcSprite(L"Sprites/forestRoadNESM.spr");
			forestRoadNWSM = new olcSprite(L"Sprites/forestRoadNWSM.spr");
			forestRoadSESM = new olcSprite(L"Sprites/forestRoadSESM.spr");
			forestRoadSWSM = new olcSprite(L"Sprites/forestRoadSWSM.spr");
			forestRoadTNSM = new olcSprite(L"Sprites/forestRoadTNSM.spr");
			forestRoadTSSM = new olcSprite(L"Sprites/forestRoadTSSM.spr");
			forestRoadTESM = new olcSprite(L"Sprites/forestRoadTESM.spr");
			forestRoadTWSM = new olcSprite(L"Sprites/forestRoadTWSM.spr");
			
			castleTL = new olcSprite(L"Sprites/castleTL.spr");
			castleTR = new olcSprite(L"Sprites/castleTR.spr");
			castleBL = new olcSprite(L"Sprites/castleBL.spr");
			castleBR = new olcSprite(L"Sprites/castleBR.spr");
			castleTLSM = new olcSprite(L"Sprites/castleTLSM.spr");
			castleTRSM = new olcSprite(L"Sprites/castleTRSM.spr");
			castleBLSM = new olcSprite(L"Sprites/castleBLSM.spr");
			castleBRSM = new olcSprite(L"Sprites/castleBRSM.spr");
			
			return true;
		}

		virtual bool OnUserUpdate(float fElapsedTime) {

			Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', 0);

			DrawString(0, 0, std::to_wstring(nSaveNumber));
			
			if (IsFocused()) {
				switch (state) {
				case 0:
					intro();
					break;
				case 1:
					menu();
					break;
				case 2:
					genMap();
					break;
				case 3:
					play();
					break;
				case 4:
					GameOver();
					break;
				}

				

				updateBuildings(fElapsedTime);

			}
			
			return true;

		}

};

int main() {

	HillsANDValleys game;
	game.ConstructConsole(110, 70, 13, 13);
	game.Start();

	return 0;
}