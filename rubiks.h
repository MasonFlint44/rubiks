//Jump to line
#define HOME "\e[0;1H"
#define LONE "\e[1;1H"
#define LTWO "\e[8;1H"
#define LTHR "\e[15;1H"
#define LFOU "\e[23;1H"

#define BOLD(msg) "\e[1m"msg"\e[0m"

typedef enum {WHITE, GREEN, RED, BLUE, ORANGE, YELLOW} Color;
typedef enum {true, false} Bool;
typedef enum {UP, DOWN, LEFT, RIGHT} Direction;

typedef struct square_ {
	Color color;
} Square;

//rubiks.c prototypes
Square* buildCube(Square* cube);
void shuffleCube(Square* cube, int** rowNum, int** faceNum, Color* color, int cycles, Bool indexMode);
void movementHelper(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i, int face, Bool inverted);
void rotateHelper(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i, Direction direction);
void solveCube(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode);
void orientCube(Square* cube, int** faceNum, Color* color, Bool indexMode, int* j);
void solveWhiteCross(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* l);
Bool checkWhiteCross(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i);
void solveWhiteCorners(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i);
Bool checkWhiteCorners(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i);
void solveMiddleLayer(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i);
Bool checkMiddleLayer(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i);
int getYellowCrossState(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i);
void solveYellowCross(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i);
Bool checkYellowCross(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i);
int getYellowCornerState(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i);
void solveYellowCorners(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i);
Bool checkYellowCorners(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i);
int getYellowCornersPosition(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i);
void positionYellowCorners(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i);
Bool checkYellowCornersPosition(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i);
void positionYellowEdges(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i);
Bool checkYellowEdgesPosition(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i);

//print.c prototypes
void printRubiks(Square* cube, Bool indexMode);
void printMirrorFace(Square* square, int padding);
void printMirrorFaceIndex(Square* square, int padding, int sideId);
void removeNewLine(char* string);
void clearMenu();
void clearHome();
void clearLine();
char* printBool(Bool bool);
void printSquare(Square square);
void printCube(Square* cube);
void printFace(Square* cube, int padding);
void printCubeIndex(Square* cube);
void printFaceIndex(Square* cube, int padding, int sideId);
void printSquareIndex(Square square, int index);
void waitFor(int secs);

//movements.c prototypes
void movements(Square* cube, int* rowNum, int* faceNum, Color* color, int face, Bool inverted);
void rotateCube(Square* cube, int** faceNum, Color* color, Direction direction);
void reflectFaceOverY(Square* cube, int* faceNum);
void reflectFaceOverX(Square* cube, int* faceNum);
void swapColor(Square* cube, int swapOne, int swapTwo);
void swapFaces(Square* cube, int** faceNum, Color* color, int faceOne, int faceTwo);
void rotateFace(Square* cube, int* rowNum, Color* color, Direction direction);
void rotateSide(Square* cube, int* rowNum, Color* color, Direction direction);
Color* fillFaceColor(Square* cube, Color* color, int* rowNum);
Color* fillSideColor(Square* cube, Color* color, int* rowNum);

//file.c prototypes
int saveFile(Square* cube, char* name, Bool indexMode, int slotNum);
int loadFile(Square* cube, char* name, Bool* indexMode, int slotNum);

//array.c prototypes
int** fillFaceNum(int** faceNum);
int** fillRowNum(int** rowNum);
char** fillName(char** name);
void freeIntArr(int** arr, int index);
void freeCharArr(char** name, int index);

//menu.c prototypes
void saveMenu(Square* cube, int** rowNum, int** faceNum, Color* color, char** name);
int loadGameMenu(Square* cube, Bool* indexMode, char** name, int* slot, char* input, int menu);
int newGameMenu(Square* cube, Bool indexMode, char** name, int* slot, char* input, int menu);
void mainMenu(Square* cube, int** rowNum, int** faceNum, Color* color, char* name, Bool* indexMode, char* input, int menu, int slot);
void shuffleMenu(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, char* input);
void solveMenu(Square* cube, int** rowNum, int** faceNum, Color* color, char* input, int menu, Bool indexMode);
void manualSolveMenu(Square* cube, int** rowNum, int** faceNum, Color* color, char* input, int menu, Bool indexMode);
int rotateMenu(Square* cube, int** faceNum, Color* color, int menu, char* input, int* prevTurn);
int directionMenu(Square* cube, int** rowNum, int** faceNum, Color* color, char* input, int face, int* prevTurn, int menu, Bool indexMode, Bool* inverted);
void optionsMenu(Square* cube, int menu, char* input, char* name, Bool* indexMode, int slot);
void changeNameMenu(char* name);
