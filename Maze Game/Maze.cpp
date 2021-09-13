#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>



#define MAZE_SIZE 41 // 미로 크기   반드시 홀수
#define MIX_COUNT 3  // 랜덤 횟수   적을수록 미로가 비슷해짐
#define CROSS_PERCENT 35 // 갈림길 확률(분모)   적을수록 갈림길이 많아짐

using namespace std;

// 생명력 변수, 점수 변수 info()에서 쓰임
int health = 100, score = 500 + MAZE_SIZE * 35;

enum {
	OUTER_WALL = -1,
	WALL = 0,
	ROAD = 1,
	FLAG = 2,
	EXIT = 5,
	PLAYER = 10,
	ENEMY = 15
};
enum {
	EAST = 0,
	WEST,
	SOUTH,
	NORTH
};

int maze[MAZE_SIZE][MAZE_SIZE] = { WALL, };


void CreateMaze();
void dfs(int,int);
void ShowMaze();
void PlayMaze();

int main()
{
	srand((unsigned int)time(NULL));

	CreateMaze();
	PlayMaze();
}


void CreateMaze()
{
	maze[MAZE_SIZE - 2][MAZE_SIZE - 1] = EXIT;
	for (int i = 1; i < MAZE_SIZE; i += 2) // 거쳐야 하는 포인트 생성  길생성시 포인트 전부를 지나야됨
	{
		for (int j = 1; j < MAZE_SIZE; j += 2)
		{
			maze[i][j] = FLAG;
		}
	}

	dfs(1, 1);
}


void dfs(int y, int x) // 길뚫는 함수
{
	int d1[4][2] = { {0,1},{0,-1},{1,0},{-1,0} }; //오른쪽, 왼쪽, 아래, 위
	int d2[4][2] = { {0,2},{0,-2},{2,0},{-2,0} };


	int dir[4] = { EAST, WEST, SOUTH, NORTH };  // 가야할 방향 순서
	int i = MIX_COUNT;
	while (i--)  // 길 뚫는 방향을 랜덤으로 하기 위해 무작위로 섞음
	{
		swap(dir[rand() % 4], dir[rand() % 4]);
	}


	for (int j = 0; j < 4; j++)
	{
		int dy1 = d1[dir[j]][1], dx1 = d1[dir[j]][0]; // 움직여야 되는 거리
		int dy2 = d2[dir[j]][1], dx2 = d2[dir[j]][0];



		if (x + dx2 >= MAZE_SIZE || x + dx2 < 0 || y + dy2 >= MAZE_SIZE || y + dy2 < 0)   // 배열 범위 초과시 스킵
			continue;

		if (maze[y + dy2][x + dx2] == FLAG) // 만약 해당 방향에 지나지 않은 포인트가 있을경우
		{

			maze[y + dy1][x + dx1] = ROAD; // 사이에 있는 벽을 뚫음
			maze[y + dy2][x + dx2] = ROAD;	// 포인트를 길로 바꿈 
			dfs(y + dy2, x + dx2);
		}
		else if(maze[y + dy2][x + dx2] == ROAD)
		{
			if (rand() % CROSS_PERCENT == 0) // 확률적으로 원래 있던 길과 연결됨 (갈림길 생성)
			{
				maze[y + dy1][x + dx1] = ROAD;
			}
		}


	}
	return;
}


void ShowMaze()
{
	for (int i = 0; i < MAZE_SIZE; i++)
	{
		for (int j = 0; j < MAZE_SIZE; j++)
		{
			switch (maze[i][j])
			{
			case WALL: cout << "■";
				break;
			case ROAD: cout << "  ";
				break;
			case FLAG: cout << "＠";
				break;
			case PLAYER: cout << "☆";
				break;
			case ENEMY: cout << "△";
				break;
			default: cout << "  ";
			}
		}
		cout << endl;
	}
}


// 인게임 도움말 출력
void info1() {
	printf("\n");
	printf("┌---------------┐\n");
	printf("│ 생명력 : %4d │\n", health);
	printf("│ 점  수 : %4d │\n", score);
	printf("└---------------┘\n");
	printf("┌---------------┐\n");
	printf("│ 상 : ↑ or w  │\n");
	printf("│ 하 : ↓ or s  │\n");
	printf("│ 좌 : ← or a  │\n");
	printf("│ 우 : → or d  │\n");
	printf("└---------------┘\n");
}

void info2() { // 게임 클리어시 호출 (점수 = 점수 + (생명력 *5)로 계산 )
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t┌----------------------------------------------┐\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t│   G  A  M  E                 C  L  E  A  R   │\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t│                                              │\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t│  점  수 : %4d [%4d + 생명력 보너스 %3d * 5]│\n", score + (health * 5),score, health);
	printf("\t\t\t\t\t\t\t\t\t\t\t└----------------------------------------------┘\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void info3() { // 게임 오버시 호출 (여기는 그냥 점수만 출력)
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t┌----------------------------------------------┐\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t│   G  A  M  E                    O  V  E  R   │\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t│                                              │\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t│   점     수 :                     %4d       │\n", score);
	printf("\t\t\t\t\t\t\t\t\t\t\t└----------------------------------------------┘\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}



void PlayMaze()
{
	int player_x = 1;
	int player_y = 1;
	maze[player_y][player_x] = PLAYER;

	// 적 초기 생성
	int enemy1_x;
	int	enemy1_y;
	while (1) {
		enemy1_x = rand() % MAZE_SIZE - 2;
		enemy1_y = rand() % MAZE_SIZE - 2;
		if (maze[enemy1_y][enemy1_x] == ROAD) {
			maze[enemy1_y][enemy1_x] = ENEMY;
			break;
		}
	}

	//적의 이동방향을 담는 변수
	int enemy_move;

	ShowMaze();
	info1();

	while (1)
	{
		score -= 5;
		int key = _getch();
		maze[player_y][player_x] = ROAD;
		switch (key)
		{
		case 'a':
		case VK_LEFT:
			if (maze[player_y][player_x - 1] != WALL) player_x--;
			break;
		case 'd':
		case VK_RIGHT:
			if (maze[player_y][player_x + 1] != WALL) player_x++;
			break;
		case 'w':
		case VK_UP:
			if (maze[player_y - 1][player_x] != WALL) player_y--;
			break;
		case 's':
		case VK_DOWN:
			if (maze[player_y + 1][player_x] != WALL) player_y++;
			break;
		default:
			break;
		}


		// 적이 이동하는 방향 랜덤으로 정함
		enemy_move = rand() % 4;

		maze[enemy1_y][enemy1_x] = ROAD;
		// 랜덤으로 뽑힌 적의 방향을 표현
		switch (enemy_move)
		{
		case 0: // 왼쪽
			if (maze[enemy1_y][enemy1_x - 1] != WALL) enemy1_x--;
			break;
		case 1: // 오른쪽
			if (maze[enemy1_y][enemy1_x + 1] != WALL && maze[enemy1_y][enemy1_x + 1] != EXIT) enemy1_x++;
			break;
		case 2:// 위
			if (maze[enemy1_y - 1][enemy1_x] != WALL) enemy1_y--;
			break;
		case 3:// 아래
			if (maze[enemy1_y + 1][enemy1_x] != WALL) enemy1_y++;
			break;
		default:
			break;
		}



		maze[player_y][player_x] = PLAYER;
		maze[enemy1_y][enemy1_x] = ENEMY;
		system("cls");
		ShowMaze();
		info1();

		// 적과 플레이어가 겹쳐졌을 때
		if (enemy1_y == player_y && enemy1_x == player_x)
		{
			health -= 10;
			score -= 50;
			// 생명력이 0이하가 돼서 죽었을 때
			if (health <= 0) {
				system("cls");
				info3();
				// 게임 종료하려고 리턴넣음
				return (void)0;
			}
		}



		// 골인지점 도착시
		if (player_y == MAZE_SIZE - 2 && player_x == MAZE_SIZE - 1)
		{
			system("cls");
			info2();
			// 게임 종료하려고 리턴넣음
			return (void)0;
		}
	}
}