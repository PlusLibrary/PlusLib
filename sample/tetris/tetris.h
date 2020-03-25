#include <pluslib/util/list.h>
#include <pluslib/util/pointInt.h>

class Tetris {
    public:
        static const int BOARD_SIZE_WIDTH = 10;
        static const int BOARD_SIZE_HEIGHT = 20;
        static const int BOARD_CEILING_BUFFER = 4;
        static const int BLOCK_TYPE_COUNT = 7;
        Tetris();
        int getBlock(int x, int y);
        int getCurrentType();
        List<PointInt>* getCurrent();
        void rotate();
        void progress(bool toEnd);
        void move(int dx);
    private:
        int currentBlock;
        int currentRotate;
        int currentBlockX;
        int currentBlockY;
        int board[BOARD_SIZE_WIDTH][BOARD_SIZE_HEIGHT + BOARD_CEILING_BUFFER];
        bool isLegalState();
        bool tryMove(int* target, int after);
        void finalizeBlock();
        void newBlock();
};