/*2048_console by Michael Liu
 *Time: 13th, July 2016
 *Description: My first project ever uploaded to Github.
 */
 
#include <iostream>
#include <iomanip>
#include <math.h>
#include <conio.h>
#include <vector>
using namespace std;
int Pane[4][4];

void showPane() {
	cout << setw(47) << "2048 by Fengyuan" << endl;
	cout << setw(50) << "|-------------------|" << endl;
	for (int i = 0; i <= 3; i++) {
		cout << setw(30) << "|";
		for (int j = 0; j <= 3; j++) {
			cout << setw(4) << Pane[i][j] << "|";
		}
		cout << endl;
	}
}

void startGame() {
	for (int i = 0; i <4; i++) {
		for (int j = 0; j< 4; j++) {
			Pane[i][j] = 0;
		}
	}
	srand((unsigned)time(NULL));
	int m = rand() % 4;
	int n = rand() % 4;
	int p = rand() % 4;
	int q = rand() % 4;
	while (m == p && n == q) {
		int m = rand() % 4;
		int n = rand() % 4;
		int p = rand() % 4;
		int q = rand() % 4;
	}
	Pane[m][n] = Pane[p][q] = 2;
	showPane();
}

int getDir() {
	int dir = 0;
	int ch = _getch();
	if (ch == 224) {
		ch = _getch();
		switch (ch) {
		case 72:
			dir = 1;
			break;
		case 75:
			dir = 3;
			break;
		case 77:
			dir = 4;
			break;
		case 80:
			dir = 2;
			break;
		default:
			break;
		}
	}
	return dir;
}

bool testUp() {
	bool up = false;
	for (int i = 1; i<4; i++) {
		for (int j = 0; j<4; j++) {
			if (Pane[i - 1][j] == 0 || Pane[i - 1][j] == Pane[i][j])
				up = true;
		}
	}
	return up;
}

bool testDown() {
	bool down = false;
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<4; j++) {
			if (Pane[i + 1][j] == 0 || Pane[i + 1][j] == Pane[i][j])
				down = true;
		}
	}
	return down;
}

bool testLeft() {
	bool left = false;
	for (int i = 0; i<4; i++) {
		for (int j = 1; j<4; j++) {
			if (Pane[i][j - 1] == 0 || Pane[i][j - 1] == Pane[i][j])
				left = true;
		}
	}
	return left;
}

bool testRight() {
	bool right = false;
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<3; j++) {
			if (Pane[i][j + 1] == 0 || Pane[i][j + 1] == Pane[i][j])
				right = true;
		}
	}
	return right;
}

void random() {
	class Grid {
	public:
		int a;
		int b;
	};

	vector <Grid> zero;
	Grid temp;

	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			if (Pane[i][j] == 0) {
				temp.a = i;
				temp.b = j;
			}
			zero.push_back(temp);
		}
	}
	int len = zero.size();
	int m = rand() % len;
	temp = zero[m];
	Pane[temp.a][temp.b] = 2;
}

void upMove() {
	for (int i = 3; i>0; i--) {
		for (int j = 0; j < 4; j++) {
			if (Pane[i - 1][j] == 0) {
				Pane[i - 1][j] = Pane[i][j];
				Pane[i][j] = 0;
			}
			else {
				if (i > 1) {
					if (Pane[i - 2][j] == 0) {
						Pane[i - 2][j] = Pane[i - 1][j];
						Pane[i - 1][j] = Pane[i][j];
						Pane[i][j] = 0;
					}
					else {
						if (i > 2) {
							if (Pane[i - 3][j] == 0) {
								Pane[i - 3][j] = Pane[i - 2][j];
								Pane[i - 2][j] = Pane[i - 1][j];
								Pane[i - 1][j] = Pane[i][j];
								Pane[i][j] = 0;
							}
						}
					}
				}
			}
		}
	}

	int count = 0;
	for (int j = 0; j < 4; j++) {
		for (int i = 3; i > 0; i--) {
			if (count == 0) {
				switch (i) {
				case 3:
					if (Pane[i - 1][j] == Pane[i][j] && Pane[i-1][j] != 0) {
						if (Pane[i - 2][j] == Pane[i - 1][j]) {
							if (Pane[i - 3][j] == Pane[i - 2][j]) {
								Pane[i - 3][j] = Pane[i - 3][j] + Pane[i - 2][j];
								Pane[i - 2][j] = Pane[i - 1][j] + Pane[i][j];
								Pane[i - 1][j] = Pane[i][j] = 0;
								count++;
							}
							else {
								Pane[i - 2][j] = Pane[i - 2][j] + Pane[i - 1][j];
								Pane[i - 1][j] = Pane[i][j];
								Pane[i][j] = 0;
								count++;
							}
						}
						else {
							Pane[i - 1][j] = Pane[i - 1][j] + Pane[i][j];
							Pane[i][j] = 0;
							count++;
						}
					}
					break;
				case 2:
					if (Pane[i - 1][j] == Pane[i][j] && Pane[i-1][j] != 0) {
						if (Pane[i - 2][j] == Pane[i - 1][j]) {
							Pane[i - 2][j] = Pane[i - 2][j] + Pane[i - 1][j];
							Pane[i - 1][j] = Pane[i][j];
							Pane[i][j] = Pane[i + 1][j];
							Pane[i + 1][j] = 0;
							count++;
						}
						else {
							Pane[i - 1][j] = Pane[i - 1][j] + Pane[i][j];
							Pane[i][j] = Pane[i + 1][j];
							Pane[i + 1][j] = 0;
							count++;
						}
					}
					break;
				case 1:
					if (Pane[i][j] == Pane[i - 1][j] && Pane[i-1][j] != 0) {
						Pane[i - 1][j] = Pane[i - 1][j] + Pane[i][j];
						Pane[i][j] = Pane[i + 1][j];
						Pane[i + 1][j] = Pane[i + 2][j];
						Pane[i + 2][j] = 0;
					}
					break;
				}
			}
		}
		count = 0;
	}
}

void downMove() {
	for (int j = 0; j<4; j++) {
		for (int i = 0; i<3; i++) {
			if (Pane[i + 1][j] == 0) {
				Pane[i + 1][j] = Pane[i][j];
				Pane[i][j] = 0;
			}
			else {
				if (i < 2) {
					if (Pane[i + 2][j] == 0) {
						Pane[i + 2][j] = Pane[i + 1][j];
						Pane[i + 1][j] = Pane[i][j];
						Pane[i][j] = 0;
					}
					else {
						if (i < 1) {
							if (Pane[i + 3][j] == 0) {
								Pane[i + 3][j] = Pane[i + 2][j];
								Pane[i + 2][j] = Pane[i + 1][j];
								Pane[i + 1][j] = Pane[i][j];
								Pane[i][j] = 0;
							}
						}
					}
				}
			}
		}
	}

	int count = 0;
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 3; i++) {
			if (count == 0) {
				switch (i) {
				case 0:
					if (Pane[i + 1][j] == Pane[i][j] && Pane[i+1][j] != 0) {
						if (Pane[i + 2][j] == Pane[i + 1][j]) {
							if (Pane[i + 3][j] == Pane[i + 2][j]) {
								Pane[i + 3][j] = Pane[i + 3][j] + Pane[i + 2][j];
								Pane[i + 2][j] = Pane[i + 1][j] + Pane[i][j];
								Pane[i + 1][j] = Pane[i][j] = 0;
								count++;
							}
							else {
								Pane[i + 2][j] = Pane[i + 2][j] + Pane[i + 1][j];
								Pane[i + 1][j] = Pane[i][j];
								Pane[i][j] = 0;
								count++;
							}
						}
						else {
							Pane[i + 1][j] = Pane[i][j] + Pane[i + 1][j];
							Pane[i][j] = 0;
						}
					}
					break;
				case 1:
					if (Pane[i + 1][j] == Pane[i][j] && Pane[i + 1][j] != 0) {
						if (Pane[i + 1][j] == Pane[i + 2][j]) {
							Pane[i + 2][j] = Pane[i + 2][j] + Pane[i + 1][j];
							Pane[i + 1][j] = Pane[i][j];
							Pane[i][j] = Pane[i - 1][j];
							Pane[i - 1][j] = 0;
							count++;
						}
						else {
							Pane[i + 1][j] = Pane[i + 1][j] + Pane[i][j];
							Pane[i][j] = Pane[i - 1][j];
							Pane[i - 1][j] = 0;
							count++;
						}
					}
					break;
				case 2:
					if (Pane[i + 1][j] == Pane[i][j] && Pane[i + 1][j] != 0) {
						Pane[i + 1][j] = Pane[i + 1][j] + Pane[i][j];
						Pane[i][j] = Pane[i - 1][j];
						Pane[i - 1][j] = Pane[i - 2][j];
						Pane[i - 2][j] = 0;
					}
					break;
				}
			}
		}
		count = 0;
	}
}


void leftMove() {
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j > 0; j--) {
			if (Pane[i][j - 1] == 0) {
				Pane[i][j - 1] = Pane[i][j];
				Pane[i][j] = 0;
			}
			else {
				if (j > 1) {
					if (Pane[i][j - 2] == 0) {
						Pane[i][j - 2] = Pane[i][j - 1];
						Pane[i][j - 1] = Pane[i][j];
						Pane[i][j] = 0;
					}
					else {
						if (j > 2) {
							if (Pane[i][j - 3] == 0) {
								Pane[i][j - 3] = Pane[i][j - 2];
								Pane[i][j - 2] = Pane[i][j - 1];
								Pane[i][j - 1] = Pane[i][j];
								Pane[i][j] = 0;
							}
						}
					}
				}
			}
		}
	}

	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j > 0; j--) {
			if (count == 0) {
				switch (j) {
				case 3:
					if (Pane[i][j - 1] == Pane[i][j] && Pane[i][j-1] != 0) {
						if (Pane[i][j - 2] == Pane[i][j - 1]) {
							if (Pane[i][j - 2] == Pane[i][j - 3]) {
								Pane[i][j - 3] = Pane[i][j - 3] + Pane[i][j - 2];
								Pane[i][j - 2] = Pane[i][j - 1] + Pane[i][j];
								Pane[i][j] = Pane[i][j - 1] = 0;
								count++;
							}
							else {
								Pane[i][j - 2] = Pane[i][j - 2] + Pane[i][j - 1];
								Pane[i][j - 1] = Pane[i][j];
								Pane[i][j] = 0;
								count++;
							}
						}
						else {
							Pane[i][j - 1] = Pane[i][j - 1] + Pane[i][j];
							Pane[i][j] = 0;
							count++;
						}
					}
					break;
				case 2:
					if (Pane[i][j - 1] == Pane[i][j] && Pane[i][j - 1] != 0) {
						if (Pane[i][j - 2] == Pane[i][j - 1]) {
							Pane[i][j - 2] = Pane[i][j - 2] + Pane[i][j - 1];
							Pane[i][j - 1] = Pane[i][j];
							Pane[i][j] = Pane[i][j + 1];
							Pane[i][j + 1] = 0;
							count++;
						}
						else {
							Pane[i][j - 1] = Pane[i][j] + Pane[i][j - 1];
							Pane[i][j] = Pane[i][j + 1];
							Pane[i][j + 1] = 0;
							count++;
						}
					}
					break;
				case 1:
					if (Pane[i][j - 1] == Pane[i][j] && Pane[i][j - 1] != 0) {
						Pane[i][j - 1] = Pane[i][j] + Pane[i][j - 1];
						Pane[i][j] = Pane[i][j + 1];
						Pane[i][j + 1] = Pane[i][j + 2];
						Pane[i][j + 2] = 0;
						count++;
					}
					break;
				}
			}
		}
		count = 0;
	}
}


void rightMove() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (Pane[i][j + 1] == 0) {
				Pane[i][j + 1] = Pane[i][j];
				Pane[i][j] = 0;
			}
			else {
				if (j < 2) {
					if (Pane[i][j + 2] == 0) {
						Pane[i][j + 2] = Pane[i][j + 1];
						Pane[i][j + 1] = Pane[i][j];
						Pane[i][j] = 0;
					}
					else {
						if (j < 1) {
							if (Pane[i][j + 3] == 0) {
								Pane[i][j + 3] = Pane[i][j + 2];
								Pane[i][j + 2] = Pane[i][j + 1];
								Pane[i][j + 1] = Pane[i][j];
								Pane[i][j] = 0;
							}
						}
					}
				}
			}
		}
	}

	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (count == 0) {
				switch (j) {
				case 0:
					if (Pane[i][j + 1] == Pane[i][j] && Pane[i][j] != 0) {
						if (Pane[i][j + 2] == Pane[i][j + 1]) {
							if (Pane[i][j + 3] == Pane[i][j + 2]) {
								Pane[i][j + 3] = Pane[i][j + 3] + Pane[i][j + 2];
								Pane[i][j + 2] = Pane[i][j] + Pane[i][j + 1];
								Pane[i][j] = Pane[i][j + 1] = 0;
								count++;
							}
							else {
								Pane[i][j + 2] = Pane[i][j + 2] + Pane[i][j + 1];
								Pane[i][j + 1] = Pane[i][j];
								Pane[i][j] = 0;
								count++;
							}
						}
						else {
							Pane[i][j + 1] = Pane[i][j + 1] + Pane[i][j];
							Pane[i][j] = 0;
							count++;
						}
					}
					break;
				case 1:
					if (Pane[i][j + 1] == Pane[i][j] && Pane[i][j + 1] != 0) {
						if (Pane[i][j + 2] == Pane[i][j + 1]) {
							Pane[i][j + 2] = Pane[i][j + 2] + Pane[i][j + 1];
							Pane[i][j + 1] = Pane[i][j + 1];
							Pane[i][j] = Pane[i][j - 1];
							Pane[i][j - 1] = 0;
							count++;
						}
						else {
							Pane[i][j + 1] = Pane[i][j + 1] + Pane[i][j];
							Pane[i][j] = Pane[i][j - 1];
							Pane[i][j - 1] = 0;
							count++;
						}
					}
					break;
				case 2:
					if (Pane[i][j + 1] == Pane[i][j] && Pane[i][j + 1] != 0) {
						Pane[i][j + 1] = Pane[i][j + 1] + Pane[i][j];
						Pane[i][j] = Pane[i][j - 1];
						Pane[i][j - 1] = Pane[i][j - 2];
						Pane[i][j - 2] = 0;
						count++;
					}
					break;
				}
			}
		}
		count = 0;
	}
}



bool endGame() {
	return false;
}

int main() {
	int getdir;
	bool testup;
	bool testdown;
	bool testleft;
	bool testright;
	startGame();
	while (!endGame()) {
		getdir = getDir();
		testup = testUp();
		testdown = testDown();
		testleft = testLeft();
		testright = testRight();
		if (getdir == 1) {
			if (testup = true) {
				upMove();
				random();
			}
		}
		else if (getdir == 2) {
			if (testdown = true) {
				downMove();
				random();
			}
		}
		else if (getdir == 3) {
			if (testleft = true) {
				leftMove();
				random();
			}
		}
		else if (getdir == 4) {
			if (testright = true) {
				rightMove();
				random();
			}
		}

		if (testright || testleft || testdown || testup) {
			system("cls");
			showPane();
		}
		else {
			system("cls");
			cout << "Game over!" << endl;
		}
	}
	system("pause");
	return 0;
}
