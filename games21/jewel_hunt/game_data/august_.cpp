#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <Windows.h>
using namespace std;
using namespace sf;

const int block_size = 75;
const int ROWS = 9;
const int COLS = 9;
Vector2i offset(70, 80);                                                                      //position from borders

struct fragment
{
	int a, b, row, col; 
	int type, match, anim;
	fragment()
	{
		match = 0;
		anim = 255;
	}
} gemset[ROWS + 1][COLS + 1];


#pragma region Functions
void swap(fragment f1, fragment f2)                                                           //swapping function
{
	swap(f1.row, f2.row);                                                                     //allocating fragments
	swap(f1.col, f2.col);

	gemset[f1.row][f1.col] = f1;
	gemset[f2.row][f2.col] = f2;
}

void Menu(RenderWindow &jewel, int &highScore,bool &isMenu)                                                 //linking with main window
{
	Sound sound_menu, sound_click;
	SoundBuffer boat, tick;
	boat.loadFromFile("tracks/sea.wav");
	tick.loadFromFile("tracks/select.wav");

	sound_menu.setBuffer(boat);
	sound_click.setBuffer(tick);

	sound_menu.play();
	sound_menu.setVolume(30);
	sound_menu.setLoop(true);

	Texture opt1, opt2, opt3, opt4, menuBackground, name;
	opt1.loadFromFile("images/play.png");
	opt2.loadFromFile("images/rules.png");
	opt3.loadFromFile("images/exit.png");
	opt4.loadFromFile("images/records.png");
	menuBackground.loadFromFile("images/men1.jpg");
	name.loadFromFile("images/jwl.png");

	Sprite play(opt1), rules(opt2), exit(opt3), rec(opt4), menuBck(menuBackground), namme(name);
	
	Texture opt2_1;
	opt2_1.loadFromFile("images/men.jpg");

	Sprite info(opt2_1);

	Font style2;
	style2.loadFromFile("Fonts/pirate.ttf");

	Text top_points;
	ostringstream topScore;
	top_points.setCharacterSize(85);
	top_points.setPosition(500, 400);
	top_points.setFont(style2);
	top_points.setFillColor(Color(207,167,7));
	top_points.setOutlineColor(Color::Black);
	top_points.setOutlineThickness(4);
	top_points.setLetterSpacing(2);

	
	int menuNum = 0;

	play.setPosition(5, 150);
	rules.setPosition(5, 270);
	rec.setPosition(5, 390);
	exit.setPosition(5, 510);
	namme.setPosition(420, 5);

	while (isMenu)   //Menu Loop
	{
		play.setColor(Color::White);
		rules.setColor(Color::White);
		rec.setColor(Color::White);
		exit.setColor(Color::White);
		menuNum = 0;
		jewel.clear(Color::White);
		
		if (IntRect(10, 150, 330, 120).contains(Mouse::getPosition(jewel)))
		{
			play.setColor(Color::Magenta); 
			menuNum = 1;
		}
		if (IntRect(10, 270, 400, 120).contains(Mouse::getPosition(jewel)))
		{
			rules.setColor(Color::Magenta); 
			menuNum = 2;
		}
		if (IntRect(10, 390, 430, 120).contains(Mouse::getPosition(jewel)))
		{
			rec.setColor(Color::Magenta);
			menuNum = 3;
		}
		if (IntRect(10, 510, 330, 120).contains(Mouse::getPosition(jewel)))
		{
			exit.setColor(Color::Magenta);
			menuNum = 4;
		}

		Event click;
		while (jewel.pollEvent(click))                              //mouse loop
		{
			switch (click.type)
			{
			case Event::MouseButtonPressed:

				if (click.key.code == Mouse::Left)
				{
					sound_click.play();
					sound_click.setVolume(60);
					
					if (menuNum == 1) {Sleep(100); isMenu = false;}
					
					if (menuNum == 2)
					{
						jewel.draw(info);
						jewel.draw(namme);
						jewel.display();
						while (!Keyboard::isKeyPressed(Keyboard::Escape));
					}
					if (menuNum == 3)
					{
						top_points.setString(topScore.str());
						topScore.str(" ");
						topScore << " BEST SCORE : " << highScore;
					}
				    
					if (menuNum == 4) 
					{Sleep(100); isMenu = false; jewel.close();}
				}
				break;
			
			case Event::MouseButtonReleased:
				if (menuNum == 3)
				{
					    top_points.setString(topScore.str());
						topScore.str(" ");
						topScore << " ";
				}
				break;

			case Event::MouseMoved:
				if (menuNum == 3)
				{
					top_points.setString(topScore.str());
					topScore.str(" ");
					topScore << " ";
				}
				break;

			case Event::Closed:
				jewel.close();
				break;
			}
		}
		jewel.draw(menuBck);
		jewel.draw(play);
		jewel.draw(rules);
		jewel.draw(rec);
		jewel.draw(exit);
		jewel.draw(namme);
		jewel.draw(top_points);
		jewel.display();
	}
}

void incLevel(RenderWindow &jewel, int &numLevel, int &score, int &Target, int &limit, bool &isMenu)
{
	if (numLevel > 1)
	{
		Target += 25000;
		limit += 30;
	}
}
#pragma endregion

//############################################################################################################################################################//

bool startGame(RenderWindow &jewel,int &numLevel, int &Target, int &score, int &highScore, int &limit, bool &isMenu)
{
	srand(unsigned(time(NULL)));

	//------------------------------WINDOW SETTINGS----------------------------------------------------------------------------------------------------------//
	Menu(jewel,highScore,isMenu);
	jewel.setFramerateLimit(60); 

	incLevel(jewel,numLevel,score,Target,limit,isMenu);
	
	//------------------------------SOUND SETTINGS-----------------------------------------------------------------------------------------------------------//
	SoundBuffer glass, explore, gem_click;
	glass.loadFromFile("tracks/glassbr2.flac");
	explore.loadFromFile("tracks/novigrad.wav");
	gem_click.loadFromFile("tracks/gemstone.wav");

	Sound sound1, sound2, sound3;
	sound1.setBuffer(glass);
	sound2.setBuffer(explore);
	sound3.setBuffer(gem_click);

	sound2.play();
	sound2.setVolume(30);
	sound2.setLoop(true);

	//----------------------------TEXT SETTINGS--------------------------------------------------------------------------------------------------------------//	
	Font style1;
	style1.loadFromFile("Fonts/ngs.otf");
	Font style2;
	style2.loadFromFile("Fonts/pirate.ttf");

	Text points;
	ostringstream gameScore;
	points.setCharacterSize(60);
	points.setPosition(800, 600);
	points.setFont(style1);
	points.setFillColor(Color(231, 204, 14));
	points.setOutlineThickness(3);
	points.setOutlineColor(Color(56, 0, 113));
	points.setLetterSpacing(2);

	Text target;
	ostringstream levelTarget;
	target.setCharacterSize(50);
	target.setPosition(850, 220);
	target.setFont(style1);
	target.setFillColor(Color(231, 204, 14));;
	target.setOutlineThickness(3);
	target.setOutlineColor(Color(56, 0, 113));
	points.setLetterSpacing(1);

	Text timer;
	ostringstream gameTime;
	timer.setCharacterSize(70);
	timer.setPosition(900, 120);
	timer.setFont(style2);
	timer.setFillColor(Color(231, 204, 14));
	timer.setOutlineThickness(3);
	timer.setOutlineColor(Color(56, 0, 113));
	timer.setLetterSpacing(2);

	Text timeisup;
	ostringstream gameOver;
	timeisup.setCharacterSize(55);
	timeisup.setPosition (750, 350);
	timeisup.setFont(style2);
	timeisup.setFillColor(Color(56, 0, 113));
	timeisup.setOutlineThickness(5);
	timeisup.setOutlineColor(Color(231, 204, 14));
	timeisup.setLetterSpacing(1);

	//---------------------------IMAGE SETTINGS--------------------------------------------------------------------------------------------------------------//
	Texture img1, img2, img3;
	img1.loadFromFile("images/yuio.jpg");
	img2.loadFromFile("images/screen.png");
	img3.loadFromFile("images/jwl.png");
	
	
	Sprite Background(img1), gems(img2), name(img3);
	
	//----------------------------------------ALLOCATION-----------------------------------------------------------------------------------------------------//

	for (int i = 1; i < ROWS; i++)
	{
		for (int j = 1; j < COLS; j++)
		{
			gemset[i][j].type = rand() % 3;
			gemset[i][j].row = i;
			gemset[i][j].col = j;
			gemset[i][j].a = i * block_size;
			gemset[i][j].b = j * block_size;
		}
	}

	int x0, y0, x, y;
	int press = 0;                  //click of a mouse
	Vector2i position;

	bool SWAP = false;            //swapping
	bool MOVE = false;            //moving
	
	Clock clock;

//--------------------------------------------------------MAIN GAME LOOP---------------------------------------------------------------------------------//
	while (jewel.isOpen())
	{
		Time elapsed = clock.getElapsedTime();
		int time_sec = elapsed.asSeconds();
	    //int time_min = (limit - time_sec) / 60;

		timer.setString(gameTime.str());
		gameTime.str(" ");
		gameTime << " Timer : " << limit - time_sec;

			if (time_sec >= limit && score < Target)         //FAILURE
			{
				gameTime.str(" ");
				gameTime << " You Lost ";
				MOVE = true;
				timeisup.setString(gameOver.str());
				gameOver.str(" ");
				gameOver << " Try Again >>> 'TAB' " << endl;
				gameOver << " Main Menu >>> 'BackSpace' " << endl;
				gameOver << " Exit >>> 'ESC' " << endl;
				if (Keyboard::isKeyPressed(Keyboard::Tab)) { numLevel = false; score = 0; isMenu = false; return true; }          //restart
				if (Keyboard::isKeyPressed(Keyboard::BackSpace)) { numLevel = false; score = 0; isMenu = true; return true; }     //main menu
				if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }                                                   //exit
			}

			if (score >= Target)         //VICTORY
			{
				gameTime.str(" ");
				gameTime << " Well Done!!! ";
				MOVE = true;
				timeisup.setString(gameOver.str());
				gameOver.str(" ");
				gameOver << " Next Level >>> 'SPACE' " << endl;
				gameOver << " Main Menu >>> 'BackSpace' " << endl;
				gameOver << " Exit >>> 'ESC' " << endl;
				if (Keyboard::isKeyPressed(Keyboard::Space)) { numLevel++; score = 0; isMenu = false; return true; }                   //next level
				if (Keyboard::isKeyPressed(Keyboard::BackSpace)) { score = 0; isMenu = true; return true; }                            //main menu
				if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }                                                        //exit
			}
	
		points.setString(gameScore.str());
		gameScore.str(" ");
		gameScore << " Score : " << score;

		target.setString(levelTarget.str());
		levelTarget.str(" ");
		levelTarget << " Target : " << Target;

		//--------------------------------------------------------HIGSCORE SAVING IN FILE---------------------------------------------------------------------------------//
		ifstream readFile;
		readFile.open("Highscores.txt");

		if (readFile.is_open())
		{
			while (!readFile.eof()) {
				readFile >> highScore;
			}
		}
		readFile.close();

		ofstream writeFile("Highscores.txt");
		if (writeFile.is_open())
		{
			if (score > highScore)
				highScore = score;

			writeFile << highScore;
		}
		writeFile.close();

		Event progress;
		while (jewel.pollEvent(progress))                              //progress loop
		{
			switch (progress.type)
			{
			case Event::Closed:                                        //SFML Close window
				 jewel.close();
				 break;

			case Event::MouseButtonPressed:
				if (progress.key.code == Mouse::Left)
				{
					if (!SWAP && !MOVE)
					{
						press++;
						position = Mouse::getPosition(jewel) - offset;
					}
					sound3.play();
					sound3.setVolume(30);
				}
				break;

			case Event::Resized:
				FloatRect visibleArea(0, 0, progress.size.width, progress.size.height);
				jewel.setView(View(visibleArea));
				break;
			}
		}
			
		//--------------------MOUSE SETTINGS-----------------------------------------------------------------------------------------------------//
		if (press == 1)
		{
			x0 = position.x / block_size + 1;                          //first click
			y0 = position.y / block_size + 1;
		}

		if (press == 2)
		{
			x = position.x / block_size + 1;                           //second click
			y = position.y / block_size + 1;

			if (abs(x - x0) + abs(y - y0) == true)
			{
				swap(gemset[x0][y0], gemset[x][y]);
				SWAP = true;                                           //swapping happens
				press = 0;                                             //refresh
			}
			else
			{
				press = 1;
			}
		}
		
		//--------------------------------MOVEMENT OF GEMS-------------------------------------------------------------------------------//
		MOVE = false;

		for (int i = 1; i < ROWS; i++)
		{
			for (int j = 1; j < COLS; j++)
			{
				fragment &f = gemset[i][j];
				int D1, D2;                                    //delta

				for (int s = 0; s < 5; s++)                    //speed
				{
					D1 = f.a - f.row * block_size;             //a = row x block_size
					D2 = f.b - f.col * block_size;             //b = column x block_size

					if (D1)
						f.a -= D1 / abs(D1);

					if (D2)
						f.b -= D2 / abs(D2);
				}
				if (D1 || D2)
					MOVE = true;
			}
		}

		//--------------------------------MATCHING SAME GEMS----------------------------------------------------------------------------------//

		for (int i = 1; i < ROWS; i++)
		{
			for (int j = 1; j < COLS; j++)
			{
				if (gemset[i][j].type == gemset[i + 1][j].type && gemset[i][j].type == gemset[i - 1][j].type)
				{
					for (int n = -1; n < 2; n++)
					{
						gemset[i + n][j].match++;
						sound1.play();
						sound1.setVolume(30);
					}
				}

				if (gemset[i][j].type == gemset[i][j + 1].type && gemset[i][j].type == gemset[i][j - 1].type)
				{
					for (int n = -1; n < 2; n++)
					{
						gemset[i][j + n].match++;
						sound1.play();
						sound1.setVolume(30);
					}
				}
			}
		}

		//---------------------------SCORING SYSTEM-------------------------------------------------------------------------------------//

		for (int i = 1; i < ROWS; i++) {
			for (int j = 1; j < COLS; j++) {
				if (gemset[i][j].match)
					score += 5;
			}
		}

		//------------------------------TRANSPARENT ANIMATION--------------------------------------------------------------------------------//
		if (!MOVE)
			for (int i = 1; i < ROWS; i++)
			{
				for (int j = 1; j < COLS; j++)
				{
					if (gemset[i][j].match && gemset[i][j].anim > 10)
					{
						gemset[i][j].anim -= 10;
						MOVE = true;
					}
				}
			}

		//-------------------------SWAP UNTIL MATCHING HAPPENS----------------------------------------------------------------------------//
		for (int i = 1; i < ROWS; i++)
		{
			for (int j = 1; j < COLS; j++)
			{
				if (SWAP && !MOVE)
				{
					if (!gemset[i][j].match)
					{
						swap(gemset[x0][y0], gemset[x][y]);               //back to previous places
						SWAP = false;
					}
				}
			}
		}
	
		//---------------------------------ADDITION OF NEW GEMS--------------------------------------------------------------------------//
		if (!MOVE)
		{
			for (int i = 1; i < ROWS; i++)                             
			{
				for (int j = COLS - 1; j > 0; j--)                   //decrement j so new gems will be fulfilled from columns
				{
					if (gemset[i][j].match)
					{
						for (int n = j; n > 0; n--)
						{
							if (!gemset[i][n].match)
							{
								swap(gemset[i][n], gemset[i][j]);
								break;
							}
						}
					}
				}
			}

			for (int i = 1; i < ROWS; i++)
			{
				for (int j = COLS - 1, n = 0; j > 0; j--)
				{
					if (gemset[i][j].match)
					{
						gemset[i][j].type = rand() % 5;
						gemset[i][j].b = ++n * -block_size;
						gemset[i][j].match = 0;
						gemset[i][j].anim = 255;
					}
				}
			}
		}

		//--------------------------------------SFML DISPLAY SETTINGS--------------------------------------------------------------------//
		jewel.draw(Background);
		jewel.draw(points);
		jewel.draw(target);
		jewel.draw(timer);
		jewel.draw(timeisup);
		name.setPosition(850, 10);
		jewel.draw(name);


		for (int i = 1; i < ROWS; i++)
		{
			for (int j = 1; j < COLS; j++)
			{
				fragment f = gemset[i][j];

				gems.setTextureRect(IntRect(f.type * 75, 0, 75, 75));
				gems.setColor(Color(255, 255, 255, f.anim));
				gems.setPosition(f.a, f.b);
				gems.move(offset.x - block_size, offset.y - block_size);
				jewel.draw(gems);
			}
		}
		jewel.display();
	}
}

void playGame(RenderWindow &jewel, int &numLevel, int &Target, int &score, int &highScore, int &limit, bool &isMenu)   //restart function
{
	if (startGame(jewel, numLevel, Target, score, highScore, limit, isMenu))
	{
		numLevel++;
		playGame(jewel, numLevel, Target, score, highScore, limit, isMenu);               //recursion
	}
}

int main()
{
	RenderWindow jewel(VideoMode(1330, 750), "Jewel Hunt");
	
	int score = 0;
	int numLevel = 1;
	int Target = 50000;
	int limit = 60;
	int highScore;
	bool isMenu = true;

	//--------------------------------------------------------HIGSCORE SAVING IN FILE---------------------------------------------------------------------------------//
	ifstream readFile;
	readFile.open("Highscores.txt");

	if (readFile.is_open())
	{
		while (!readFile.eof()) {
			readFile >> highScore;
		}
	}
	readFile.close();
	ofstream writeFile("Highscores.txt");

	if (writeFile.is_open())
	{
		if (score > highScore)
			highScore = score;

		writeFile << highScore;
	}
	writeFile.close();

	playGame(jewel, numLevel, Target, score, highScore, limit,  isMenu);

	return 0;
}