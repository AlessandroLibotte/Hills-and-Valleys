#include <iostream>
#include <string>
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

		float fZoomOffset = 1;

		bool bSubCursor = 0;
		bool bCursor = 0;
		bool bZoom = 0;
		bool bBuildMenu = 0;

		struct genOptions {

			bool bGrass = 1;
			bool bForest = 1;
			bool bMountain = 1;
			bool bWather = 1;
			bool bDeepWather = 1;

			int nActiveTiles = 5;

		}genOp;

		int nMap[20][20];
		int nBuildings[20][20];
		int nResources[4][20][20];

		olcSprite *farm = nullptr;

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
					break;

				case 2:
					//Highlighting cursor
					DrawString(15, 15, L"New Game");
					DrawString(15, 20, L"Load Game");
					DrawString(15, 55, L"Quit Game", BG_WHITE);
					break;
			}

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
					nCursor = 0;
					break;
				case 2:
					exit(0);
					break;
				}
			}
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
											nResources[0][x][y] = rand() % 300 + 100;
											bGen = 1;
										}
										break;
									case 2:
										if (!genOp.bMountain)
											nMap[x][y] = rand() % 3 + 2;
										else {
											nResources[2][x][y] = rand() % 100 + 200;
											if (rand() % 3 == 1)
												nResources[3][x][y] = rand() % 100 + 10;
											bGen = 1;
										}
										break;
									case 3:
										if (!genOp.bWather)
											nMap[x][y] = rand() % 4 + 1;
										else {
											if (rand() % 3 <= 2)
												nResources[1][x][y] = rand() % 100 + 10;
											bGen = 1;
										}
										break;
									case 4:
										if (!genOp.bDeepWather)
											nMap[x][y] = rand() % 4;
										else {
											if (rand() % 3 <= 2)
												nResources[1][x][y] = rand() % 100 + 10;
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
					case 0:
						if(!nBuildings[x][y])
							Fill(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), 10 * fZoomOffset + (nZoom * (x - plX)), 10 * fZoomOffset + (nZoom * (y - plY)), PIXEL_SOLID, FG_GREEN);
						else {
							if (bZoom) {
								switch (nBuildings[x][y]) {
								case 1:
									DrawSprite(0, 0, farm);
									break;
								}
							}
						}
						break;
					case 1:
						Fill(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), 10 * fZoomOffset + (nZoom * (x - plX)), 10 * fZoomOffset + (nZoom * (y - plY)), PIXEL_THREEQUARTERS, FG_DARK_GREEN);
						break;
					case 2:
						Fill(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), 10 * fZoomOffset + (nZoom * (x - plX)), 10 * fZoomOffset + (nZoom * (y - plY)), PIXEL_SOLID, FG_DARK_GREY);
						break;
					case 3:
						Fill(6 + (nZoom * (x - plX)), 6 + (nZoom * (y - plY)), 10 * fZoomOffset + (nZoom * (x - plX)), 10 * fZoomOffset + (nZoom * (y - plY)), PIXEL_SOLID, FG_CYAN);
						break;
					case 4:
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

			Fill(57, 0, m_nScreenWidth, m_nScreenHeight, L' ', 0);
			Fill(0, 57, m_nScreenWidth, m_nScreenHeight, L' ', 0);

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
				DrawString(86, 15, std::to_wstring(nResources[0][nPlayerCursorX][nPlayerCursorY]));
				break;
			case 2:
				DrawString(81, 10, L"Mountain");
				DrawString(70, 15, L"Resources: ");
				DrawString(81, 15, L"Stone");
				DrawString(87, 15, std::to_wstring(nResources[2][nPlayerCursorX][nPlayerCursorY]));
				DrawString(81, 17, L"Iron");
				DrawString(86, 17, std::to_wstring(nResources[3][nPlayerCursorX][nPlayerCursorY]));
				break;
			case 3:
				DrawString(81, 10, L"Wather");
				DrawString(70, 15, L"Resources: ");
				DrawString(81, 15, L"Fish ");
				DrawString(86, 15, std::to_wstring(nResources[1][nPlayerCursorX][nPlayerCursorY]));
				break;
			case 4:
				DrawString(81, 10, L"Deep Wather");
				DrawString(70, 15, L"Resources: ");
				DrawString(81, 15, L"Fish ");
				DrawString(86, 15, std::to_wstring(nResources[1][nPlayerCursorX][nPlayerCursorY]));
				break;
			}

			//Tile Menu
			if (!bBuildMenu) {

				//Shows if a building is in the current tile 
				DrawString(70, 13, L"Building: ");
				switch (nBuildings[nPlayerCursorX][nPlayerCursorY]) {
				default:
					DrawString(80, 13, L"None");
				}

				//Highlights the selected tile menu option 
				switch (nCursor) {
				case 0:
					DrawString(65, 20, L"Build", BG_WHITE);
					DrawString(65, 50, L"Back");
					break;
				case 1:
					DrawString(65, 20, L"Build");
					DrawString(65, 50, L"Back", BG_WHITE);
					break;
				default:
					DrawString(65, 20, L"Build");
					DrawString(65, 50, L"Back");
					break;
				}
			}
			//Build Menu
			else {
				//Printing the builidngs according to the tile type
				switch (nMap[nPlayerCursorX][nPlayerCursorY]) {
				case 0:
					nMaxCursorPos = 6;
					switch (nCursor) {
					case 0:
						DrawString(65, 20, L"Farm", BG_WHITE);
						DrawString(65, 25, L"Field");
						DrawString(65, 30, L"House");
						DrawString(65, 35, L"Road");
						DrawString(65, 40, L"Windmill");
						DrawString(65, 50, L"Back");
						break;
					case 1:
						DrawString(65, 20, L"Farm");
						DrawString(65, 25, L"Field", BG_WHITE);
						DrawString(65, 30, L"House");
						DrawString(65, 35, L"Road");
						DrawString(65, 40, L"Windmill");
						DrawString(65, 50, L"Back");
						break;
					case 2:
						DrawString(65, 20, L"Farm");
						DrawString(65, 25, L"Field");
						DrawString(65, 30, L"House", BG_WHITE);
						DrawString(65, 35, L"Road");
						DrawString(65, 40, L"Windmill");
						DrawString(65, 50, L"Back");
						break;
					case 3:
						DrawString(65, 20, L"Farm");
						DrawString(65, 25, L"Field");
						DrawString(65, 30, L"House");
						DrawString(65, 35, L"Road", BG_WHITE);
						DrawString(65, 40, L"Windmill");
						DrawString(65, 50, L"Back");
						break;
					case 4:
						DrawString(65, 20, L"Farm");
						DrawString(65, 25, L"Field");
						DrawString(65, 30, L"House");
						DrawString(65, 35, L"Road");
						DrawString(65, 40, L"Windmill", BG_WHITE);
						DrawString(65, 50, L"Back");
						break;
					case 5:
						DrawString(65, 20, L"Farm");
						DrawString(65, 25, L"Field");
						DrawString(65, 30, L"House");
						DrawString(65, 35, L"Road");
						DrawString(65, 40, L"Windmill");
						DrawString(65, 50, L"Back", BG_WHITE);
						break;
					}
					break;
				case 1:
					nMaxCursorPos = 3;
					switch (nCursor) {
					case 0:
						DrawString(65, 20, L"Carpenter Workshop", BG_WHITE);
						DrawString(65, 25, L"Road");
						DrawString(65, 50, L"Back");
						break;
					case 1:
						DrawString(65, 20, L"Carpenter Workshop");
						DrawString(65, 25, L"Road", BG_WHITE);
						DrawString(65, 50, L"Back");
						break;
					case 2:
						DrawString(65, 20, L"Carpenter Workshop");
						DrawString(65, 25, L"Road");
						DrawString(65, 50, L"Back", BG_WHITE);
						break;
					}
					break;
				case 2:
					nMaxCursorPos = 2;
					switch (nCursor) {
					case 0:
						DrawString(65, 20, L"Mine", BG_WHITE);
						DrawString(65, 50, L"Back");
						break;
					case 1:
						DrawString(65, 20, L"Mine");
						DrawString(65, 50, L"Back", BG_WHITE);
						break;
					}
					break;
				case 3:
					switch (nCursor) {

					}
					break;
				case 4:
					switch (nCursor) {

					}
					break;
				}

			}

			//Map movement and zoom
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
			//Tile Menu
			else {

				//Cursor movement
				if (GetKey(VK_UP).bPressed)
					nCursor--;
				if (GetKey(VK_DOWN).bPressed)
					nCursor++;

				if (!bBuildMenu) {

					//Correcting cursor overflow
					if (nCursor > 1)
						nCursor = 1;
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
							bCursor = 0;
							nCursor = 10;
							break;
						}
				}
				//Build Menu
				else {

					//Correcting cursor overflow
					if (nCursor > nMaxCursorPos)
						nCursor = nMaxCursorPos;
					if (nCursor < 0)
						nCursor = 0;

					//Interpreting input
					if (GetKey(VK_RETURN).bPressed) {

						if (nCursor == nMaxCursorPos - 1) {
							bBuildMenu = 0;
							nCursor = 0;
						}

						switch (nMap[nPlayerCursorX][nPlayerCursorY]) {
						case 0:
							switch (nCursor) {
							case 0:
								nBuildings[nPlayerCursorX][nPlayerCursorY] = 1;
								break;
							}
							break;
						}
					}

				}
			}

			//Quit
			if (GetKey(VK_ESCAPE).bPressed) {
				bCursor = 0;
				nCursor = 0;
				bZoom = 0;
				nZoom = 5;
				fZoomOffset = 1;
				state = 1;
				memset(nMap, 0, sizeof(nMap));
				memset(nResources, 0, sizeof(nResources));
				genOp.bGrass = 1;
				genOp.bForest = 1;
				genOp.bMountain = 1;
				genOp.bWather = 1;
				genOp.bDeepWather = 1;
				genOp.nActiveTiles = 5;
			}

			return;
		}

	protected: 
		virtual bool OnUserCreate() {

			farm = new olcSprite(L"C:/Sprites/test.spr");

			return true;
		}

		virtual bool OnUserUpdate(float fElapsedTime) {

			Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', 0);

			if(IsFocused())
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