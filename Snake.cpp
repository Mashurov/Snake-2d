#include <time.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include  <GL/glut.h>

using namespace std;

bool son = 1; bool gameover; char answer[1]; // son äëÿ òîãî ÷òîáû óñïåòü ïåðåéòè ñ êîíñîëè â .åõå , answer äëÿ new game , gameover - êîíåö èãðû

string name; // äëÿ highscores
int speed = 100;
int N = 30, M = 20; //N - øèðèíà , M - äëèíà â âåðõ
int Scale = 25;// ñêîëüêî ïèêñåëåé çàíèìàåò 1 êâàäðàò

int score = 0;//points 

int w = Scale*N; // øèðèíà îêîøêà
int h = Scale*M; // äîëãîòà îêîøêà

int dir, num = 2; // dir - íàïðàâëåíèå . 

struct s
{
	int x;
	int y;
}	s[100]; // òåëî çìåéêè ,õ-ó êîîðäèíàòû. s- ìàêñ êîëè÷åñòâî êâàäðàòèêîâ â çìåéêå.


class Fructs
{
public:
	int x, y;

	void New(); // ðåãåíåðàöèÿ íîâîé ïîçèöèè ÿáëîêà


	void DrawApple(); // ðèñîâêà ÿáëîêà


}	m[1]; // ãåíåðàöèÿ ÿáëîêà+îòðèñîâêà

void Fructs::New()
{
	x = rand() % N;
	y = rand() % M;
}
void Fructs::DrawApple()
{
	glColor3f(1.0, 1.0, 0.0);
	glRectf(x*Scale, y*Scale, (x + 1)*Scale, (y + 1)*Scale);

}

void DrawSnake()
{
	glColor3f(0.0, 1.0, 0.0);
	for (int i = 0; i<num; i++)
	{
		glRectf(s[i].x*Scale, s[i].y*Scale, (s[i].x + 0.9)*Scale, (s[i].y + 0.9)*Scale);
	} // ðèñóåì êâàäðàòèêè
} // îòðèñîâêà çìåéêè


void Tick() // øàãè çìåéêè
{

	for (int i = num; i>0; --i) //÷òîáû òåëî çìåéêè äâèãàëîñü
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	if (dir == 0) s[0].y += 1;      // dir == 0 ââåðõ
	if (dir == 1) s[0].x -= 1;        // íàëåâî
	if (dir == 2) s[0].x += 1;         // íàïðàâî
	if (dir == 3) s[0].y -= 1;         // âíèç

	int	i = 0;
	if ((s[0].x == m[i].x) && (s[0].y == m[i].y))
	{                       // ïðîâåðêà,êîãäà çìåéêà åñò ÿáëîêî òî îíà ðàñòåò + î÷êè äîáàâëÿþòñÿ
		{
			num++;
			m[i].New();
		}
		score++;
	}

	if (s[0].x>N) gameover = 1;  if (s[0].x<0) gameover = 1; // âûõîä çà ãðàíèöû,
	if (s[0].y>M) gameover = 1;  if (s[0].y<0) gameover = 1;

	for (int i = 1; i<num; i++) // ñüåäàåì ñàìè ñåáÿ 
		if (s[0].x == s[i].x && s[0].y == s[i].y)
		{
			num = i;
			score = num - 2;
		}

} // ãåéìïëåé çìåéêè


void TextOut(int x, int y, char *string) {
	char *c; glRasterPos2f(x, y); // ïîçèöèè
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c); // bitmap øðèôòû
	}
	if (!gameover)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
} // âûâîä òåêñòà íà ýêðàí opengl

void display() {

	if (son == 1)
	{
		Sleep(1000);
		son = 0;
	}; // äëÿ òîãî,÷òîáû óñïåòü ïåðåêëþ÷èòü êîíñîëüíîå îêíî íà èãðó 

	glClear(GL_COLOR_BUFFER_BIT);// î÷èñòêà ýêðàíà

	DrawSnake(); // âûçîâ ôóíêöèè ðèñîâàíèÿ çìåéêè
	char scors[12] = { 's','c','o','r','e',' ',':',' ' };
	char str[10]; // äëÿ ïîäñ÷åòà î÷êîâ
	itoa(score, str, 10);        // ïåðåâîä èç int â ñòðîêó è çàïèñü â ïåðåìåííóþ str
	TextOut(720, 10, str);   // òàê âûâîäèòñÿ òåêñò (ñòðîêîâàÿ ïåðåìåííàÿ)
	TextOut(650, 10, scors); //
	if (gameover == 1)
	{
		char gameovertext[16] = { 'G','a','m','e',' ','O','v','e','r','!' };
		TextOut(290, 250, gameovertext);
	}

	m[0].DrawApple(); // âûçîâ ôóíêöèè ðèñîâàíèÿ ôðóêòà

	glFlush();// âûâîä íà ýêðàí
	glutSwapBuffers(); //ìåíÿåò áóôåðû , ÷òîáû êàðòèíêà íå òîðìîçèëà
}

void KeyboardEvent(int key, int a, int b) // äëÿ óïðàâëåíèÿ çìåéêîé
{
	switch (key)
	{
	case GLUT_KEY_UP: if (dir != 3)	dir = 0; break; // 101 code 
	case GLUT_KEY_RIGHT:  if (dir != 1) dir = 2; break; // 102 code
	case GLUT_KEY_LEFT: if (dir != 2)  dir = 1; break; // 100 code
	case GLUT_KEY_DOWN: if (dir != 0)  dir = 3; break; // 103 code
	}
}
void KeyboardEventesc(unsigned char key, int a, int b) // c÷èòóåì ÷èñëîâûå çíà÷åíèÿ êëàâèø íà êëàâèàòóðå ( ñêàí-êîä)
{
	if (key == 27)
	{
		exit(0);
	}
} // äëÿ âûõîäà èç ïðîãðàììû


string toString(int numInt)
{
	string numStr;
	int i = 10, j = 1;

	if (numInt < 0)
	{
		numStr.push_back('-');
		numInt = -numInt;
	}

	while (numInt%i != numInt)
	{
		i *= 10;
	}

	while (i>1)
	{
		i /= 10;
		numStr.push_back(48 + (numInt / i));
		numInt -= (numInt / i)*i;
	}

	return numStr;
}//ïðåîáðàçîâàíèÿ äëÿ çàïèñè ðåçóëüòàòà
int toInt(string numStr)
{
	int numInt = 0, n = 1;

	for (int i = 0; i<numStr.size(); i++, n *= 10);

	for (int i = 0; i<numStr.size(); i++)
	{
		n /= 10;
		numInt += (numStr[i] - 48)*n;
	}

	return numInt;
}//ïðåîáðàçîâàíèÿ äëÿ çàïèñè ðåçóëüòàòà

void saveHighscore() // ñîõðàíåíèå+âûâîä ðåçóëüòàòîâ
{
	ifstream file;
	ofstream out;
	string line;
	bool flag = false;
	struct
	{
		string name;
		string points;
	} fiile[128], aux;

	file.open("highscores.txt");
	for (int i = 0; i<100; i++)
	{
		getline(file, fiile[i].name, ',');
		getline(file, fiile[i].points);

		if (fiile[i].name.compare(name) == 0)
		{
			flag = true;
			if (toInt(fiile[i].points) < score)
				fiile[i].points = toString(score);
		}
	}
	file.close();

	if (!flag)
	{
		fiile[100].name = name;
		fiile[100].points = toString(score);
	}
	else
	{
		fiile[100].name = "0";
		fiile[100].points = "0";
	}

	for (int i = 0; i <= 100; i++)
		for (int j = 0; j<100; j++)
			if (toInt(fiile[j].points) < toInt(fiile[j + 1].points))
			{
				aux = fiile[j];
				fiile[j] = fiile[j + 1];
				fiile[j + 1] = aux;
			}

	cout << "\t\t\t\tTop 10 Highscores:\n";

	for (int i = 0; i<10; i++)
		cout << fiile[i].name << " \t\t\t\t\t" << fiile[i].points << endl;

	out.open("highscores.txt");

	for (int i = 0; i<100; i++)
		out << fiile[i].name << "," << fiile[i].points << endl;

	out.close();
}

void timer(int = 0) //îñíîâíîé öèêë 
{
	if (num <= 11)speed = 100; // DOIT
	if (num == 12)speed = 75;
	if (num == 22)speed = 50;
	if (num == 32)speed = 35;

	display(); // îòîáðàæàåò òî , ÷òî íà ýêðàíå

	if (!gameover)
	{
		Tick();
	}
	else
	{
		Sleep(1000); // ïðîâåðêà,íå âòàðàíèëàñü ëè çìåéêà â ãðàíèöó

		cout << "Your name: "; cout << name << endl;
		cout << "Your score: "; cout << score << endl;
		saveHighscore();
		exit(0);
	}

	glutTimerFunc(speed, timer, 0);
}

int main(int argc, char **argv)
{
	cout << "What's your name? -  ";
	getline(cin, name); cout << endl;

	srand(time(0));

	m[0].New();//ñîçäàåì íîâîå ÿáëîêî
	s[0].x = 1; // íà÷àëüíûå êîîðäèíàòû
	s[0].y = 1; // íà÷àëüíûå êîîðäèíàòû
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);// w , h äëÿ òîãî,÷òîáû ñîõðàíÿëèñü ïðîïîðöèè.
	glutCreateWindow("Snake");
	glColor3f(0.0, 0.0, 0.0);  //öâåò ôîíà
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);// w , h äëÿ òîãî,÷òîáû ñîõðàíÿëèñü ïðîïîðöèè.
	glutDisplayFunc(display);
	glutSpecialFunc(KeyboardEvent);
	glutKeyboardFunc(KeyboardEventesc);
	glutTimerFunc(100, timer, 0);
	glutMainLoop();
}
