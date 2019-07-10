#include <iostream>
#include "olcConsoleGameEngine.h"

class HillsANDValleys : public olcConsoleGameEngine {

	public:
		HillsANDValleys(){
			m_sAppName = L"Hills and Valleys";
		}

	private:
		bool bIntro = 0;
		bool bMenu = 0;
		bool bPlaying = 0;
		int nCursor = 0;
		int nMapWidth = 5;
		int nMapHeight = 5;

		int nMap[15][15];

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

			return;
		}

		void menuFrame() {
			for (int y = 10; y < 12; y++)
				for (int x = 10; x < 50; x++) {
					Draw(x, y);
				}
			for (int x = 10; x < 12; x++)
				for (int y = 10; y < 60; y++) {
					Draw(x, y);
				}
			for (int y = 58; y < 60; y++)
				for (int x = 10; x < 50; x++) {
					Draw(x, y);
				}
			for (int x = 48; x < 50; x++)
				for (int y = 10; y < 60; y++) {
					Draw(x, y);
				}
		}

		int menu() {

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
					return 1;
					break;
				case 1:
					return 2;
					break;
				case 2:
					return 3;
					break;
				}
			}

			return 0;
		}

		bool genMap() {

			//Printing the Menu Frame 
			menuFrame();

			DrawString(20, 15, L"Select the map size");

			//Highlighting the selected option and printing the map overview
			switch (nCursor) {
				case 0: //5x5 map
					//Highlighting cursor position
					DrawString(15, 20, L"5x5 tiles map", BG_WHITE);
					DrawString(15, 25, L"10x10 tiles map");
					DrawString(15, 30, L"15x15 tiles map");
					DrawString(15, 55, L"Back");

					//--Map preview
					//-Outline
					DrawLine(51, 9, 78, 9);
					DrawLine(51, 9, 51, 36);
					DrawLine(51, 36, 78, 36);
					DrawLine(78, 36, 78, 9);

					//Drawing and filling tiles lines
					for (int y = 0; y < 5; y++)
						for (int x = 0; x < 5; x++) {
							DrawLine(52 + (5 * x), 10 + (5 * y), 57 + (5 * x), 10 + (5 * y), PIXEL_SOLID, FG_BLACK);
							DrawLine(52 + (5 * x), 10 + (5 * y), 52 + (5 * x), 15 + (5 * y), PIXEL_SOLID, FG_BLACK);
							DrawLine(52 + (5 * x), 15 + (5 * y), 57 + (5 * x), 15 + (5 * y), PIXEL_SOLID, FG_BLACK);
							DrawLine(57 + (5 * x), 15 + (5 * y), 57 + (5 * x), 10 + (5 * y), PIXEL_SOLID, FG_BLACK);

							Fill(53 + (5 * x), 11 + (5 * y), 57 + (5 * x), 15 + (5 * y), PIXEL_SOLID, FG_GREEN);
						}

					break;

				case 1: //10x10 map

					//Highlighting cursor position
					DrawString(15, 20, L"5x5 tiles map");
					DrawString(15, 25, L"10x10 tiles map", BG_WHITE);
					DrawString(15, 30, L"15x15 tiles map");
					DrawString(15, 55, L"Back");

					//--Map preview
					//-Outline
					DrawLine(51, 9, 103, 9);
					DrawLine(51, 9, 51, 61);
					DrawLine(51, 61, 103, 61);
					DrawLine(103, 61, 103, 9);

					//Drawing and filling tiles lines
					for (int y = 0; y < 10; y++)
						for (int x = 0; x < 10; x++) {
							DrawLine(52 + (5 * x), 10 + (5 * y), 57 + (5 * x), 10 + (5 * y), PIXEL_SOLID, FG_BLACK);
							DrawLine(52 + (5 * x), 10 + (5 * y), 52 + (5 * x), 15 + (5 * y), PIXEL_SOLID, FG_BLACK);
							DrawLine(52 + (5 * x), 15 + (5 * y), 57 + (5 * x), 15 + (5 * y), PIXEL_SOLID, FG_BLACK);
							DrawLine(57 + (5 * x), 15 + (5 * y), 57 + (5 * x), 10 + (5 * y), PIXEL_SOLID, FG_BLACK);

							Fill(53 + (5 * x), 11 + (5 * y), 57 + (5 * x), 15 + (5 * y), PIXEL_SOLID, FG_GREEN);
						}
					break;

				case 2: //15x15 map
					//Highlighting cursor position
					DrawString(15, 20, L"5x5 tiles map");
					DrawString(15, 25, L"10x10 tiles map");
					DrawString(15, 30, L"15x15 tiles map", BG_WHITE);
					DrawString(15, 55, L"Back");

					//--Map preview
					//-Outline
					DrawLine(51, 9, 98, 9);
					DrawLine(51, 9, 51, 56);
					DrawLine(51, 56, 98, 56);
					DrawLine(98, 56, 98, 9);

					//Drawing and filling tiles lines
					for (int y = 0; y < 15; y++)
						for (int x = 0; x < 15; x++) {
							DrawLine(52 + (3 * x), 10 + (3 * y), 55 + (3 * x), 10 + (3 * y), PIXEL_SOLID, FG_BLACK);
							DrawLine(52 + (3 * x), 10 + (3 * y), 52 + (3 * x), 13 + (3 * y), PIXEL_SOLID, FG_BLACK);
							DrawLine(52 + (3 * x), 13 + (3 * y), 55 + (3 * x), 13 + (3 * y), PIXEL_SOLID, FG_BLACK);
							DrawLine(55 + (3 * x), 13 + (3 * y), 55 + (3 * x), 10 + (3 * y), PIXEL_SOLID, FG_BLACK);

							Fill(53 + (3 * x), 11 + (3 * y), 55 + (3 * x), 13 + (3 * y), PIXEL_SOLID, FG_GREEN);
						}
					break;

				case 3: //Back 
					//Highlighting cursor position
					DrawString(15, 20, L"5x5 tiles map");
					DrawString(15, 25, L"10x10 tiles map");
					DrawString(15, 30, L"15x15 tiles map");
					DrawString(15, 55, L"Back", BG_WHITE);
					break;
			}

			//Updating nCursor
			if (GetKey(VK_DOWN).bPressed)
				nCursor += 1;
			if (GetKey(VK_UP).bPressed)
				nCursor -= 1;

			//Correcting nCursor Overflow
			if (nCursor > 3)
				nCursor = 3;
			if (nCursor < 0)
				nCursor = 0;

			//Interpreting input
			//Cases 0 to 2 - Generating random map of the specified size
			//Sase 3 - Back
			if (GetKey(VK_RETURN).bPressed) {
				bPlaying = 1;
				switch (nCursor) {
				case 0:
					nMapWidth = 5;
					nMapHeight = 5;

					for (int y = 0; y < nMapHeight; y++)
						for (int x = 0; x < nMapWidth; x++)
							nMap[x][y] = rand() % 4;
					play();
					return 1;
					break;
				case 1:
					nMapWidth = 10;
					nMapHeight = 10;

					for (int y = 0; y < nMapHeight; y++)
						for (int x = 0; x < nMapWidth; x++)
							nMap[x][y] = rand() % 4;
					play();
					return 1;
					break;
				case 2:
					nMapWidth = 15;
					nMapHeight = 15;

					for (int y = 0; y < nMapHeight; y++)
						for (int x = 0; x < nMapWidth; x++)
							nMap[x][y] = rand() % 4;
					play();
					return 1;
					break;
				case 3:
					nCursor = 0;
					bMenu = 0;
					break;
				}
			}
			
			return 0;
		}

		void loadMap() {

			//Clearing the screen
			Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', 0);

			//Printing the map 
			for(int y = 0; y < nMapHeight; y++)
				for (int x = 0; x < nMapWidth; x++) {
					switch (nMap[x][y]) {
						case 0:
							DrawLine(5 + (5 * x) , 5 + (5 * y), 10 + (5 * x), 5 + (5 * y));
							DrawLine(5 + (5 * x), 5 + (5 * y), 5 + (5 * x), 10 + (5 * y));
							DrawLine(5 + (5 * x), 10 + (5 * y), 10 + (5 * x), 10 + (5 * y));
							DrawLine(10 + (5 * x), 10 + (5 * y), 10 + (5 * x), 5 + (5 * y));

							Fill(6 + (5 * x), 6 + (5 * y), 10 + (5 * x), 5 + (5 * y), PIXEL_SOLID, FG_GREEN);
						case 1:
							DrawLine(5 + (5 * x), 5 + (5 * y), 10 + (5 * x), 5 + (5 * y));
							DrawLine(5 + (5 * x), 5 + (5 * y), 5 + (5 * x), 10 + (5 * y));
							DrawLine(5 + (5 * x), 10 + (5 * y), 10 + (5 * x), 10 + (5 * y));
							DrawLine(10 + (5 * x), 10 + (5 * y), 10 + (5 * x), 5 + (5 * y));

							Fill(6 + (5 * x), 6 + (5 * y), 10 + (5 * x), 5 + (5 * y), PIXEL_SOLID, FG_DARK_RED);
						case 2:
							DrawLine(5 + (5 * x), 5 + (5 * y), 10 + (5 * x), 5 + (5 * y));
							DrawLine(5 + (5 * x), 5 + (5 * y), 5 + (5 * x), 10 + (5 * y));
							DrawLine(5 + (5 * x), 10 + (5 * y), 10 + (5 * x), 10 + (5 * y));
							DrawLine(10 + (5 * x), 10 + (5 * y), 10 + (5 * x), 5 + (5 * y));

							Fill(6 + (5 * x), 6 + (5 * y), 10 + (5 * x), 5 + (5 * y), PIXEL_SOLID, FG_GREY);
						case 3:
							DrawLine(5 + (5 * x), 5 + (5 * y), 10 + (5 * x), 5 + (5 * y));
							DrawLine(5 + (5 * x), 5 + (5 * y), 5 + (5 * x), 10 + (5 * y));
							DrawLine(5 + (5 * x), 10 + (5 * y), 10 + (5 * x), 10 + (5 * y));
							DrawLine(10 + (5 * x), 10 + (5 * y), 10 + (5 * x), 5 + (5 * y));

							Fill(6 + (5 * x), 6 + (5 * y), 10 + (5 * x), 5 + (5 * y), PIXEL_SOLID, FG_CYAN);
						case 4:
							DrawLine(5 + (5 * x), 5 + (5 * y), 10 + (5 * x), 5 + (5 * y));
							DrawLine(5 + (5 * x), 5 + (5 * y), 5 + (5 * x), 10 + (5 * y));
							DrawLine(5 + (5 * x), 10 + (5 * y), 10 + (5 * x), 10 + (5 * y));
							DrawLine(10 + (5 * x), 10 + (5 * y), 10 + (5 * x), 5 + (5 * y));

							Fill(6 + (5 * x), 6 + (5 * y), 10 + (5 * x), 5 + (5 * y), PIXEL_SOLID, FG_BLUE);
					}
				}

			return;

		}

		void play(){
			
			loadMap();

		}

	protected: 
		virtual bool OnUserCreate() {

			intro();

			return true;
		}

		virtual bool OnUserUpdate(float fElapsedTime) {

			if (IsFocused()) {

				if (!bPlaying) {

					if (!bIntro)
						if (GetKey(VK_SPACE).bPressed)
							bIntro = 1;
						else
							return true;
					else {

						Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', 0);

						if (!bMenu) {
							switch (menu()) {
							case 1:
								bMenu = 1;
								nCursor = 0;
								genMap();
								break;
							case 3:
								exit(0);
								break;
							default:
								break;
							}
						}
						else genMap();
					}
				}
				else {
					Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', 0);
					play();
				}
			}

			return true;

		}

};

int main() {

	HillsANDValleys game;
	game.ConstructConsole(110, 70, 12, 12);
	game.Start();

	return 0;
}