#include "tetris.h"
#include <pluslib/util/pointInt.h>
#include <pluslib/util/random.h>

struct Block {
    int rotate;
    int blocks[3][2];
};

struct Block blocks[] = {
    {},
    {2, {{0, 1}, {0, 2}, {0, -1}}},    // tetris
    {1, {{-1, 0}, {-1, 1}, {0, 1}}},   // square
    {4, {{0, -1}, {0, 1}, {1, 1}}},    // L
    {4, {{0, -1}, {0, 1}, {-1, 1}}},   // ~L
    {2, {{0, -1}, {1, 0}, {1, 1}}},    // S
    {2, {{0, -1}, {-1, 0}, {-1, 1}}},  // ~S
    {4, {{-1, 0}, {1, 0}, {0, 1}}},    // T
};

Tetris::Tetris() {
    for (int y = 0; y < Tetris::BOARD_SIZE_HEIGHT + Tetris::BOARD_CEILING_BUFFER; y++) {
        for (int x = 0; x < Tetris::BOARD_SIZE_WIDTH; x++) {
            board[x][y] = 0;
        }
    }
    newBlock();
}

void Tetris::rotate() {
    tryMove(&this->currentRotate, (this->currentRotate + 1) % blocks[this->currentBlock].rotate);
}

void Tetris::progress(bool toEnd) {
    do {
        if(!tryMove(&this->currentBlockY, this->currentBlockY - 1)) {
            finalizeBlock();
            break;
        }
    } while (toEnd);
}

void Tetris::finalizeBlock() {
    List<PointInt>* list = getCurrent();
    for (int i = 0; i < 4; i++) {
        PointInt* p = list->get(i);
        this->board[p->x][p->y] = this->currentBlock;
    }
    delete(list);
    for (int y = 0; y < BOARD_SIZE_HEIGHT; y++) {
        bool isFilled = true;
        for (int x = BOARD_SIZE_WIDTH - 1; x >= 0; x--) {
            if (!this->board[x][y]) {
                isFilled = false;
                break;
            }
        }
        if (isFilled) {
            for (int yy = y; yy < BOARD_SIZE_HEIGHT; yy++) {
                for (int x = BOARD_SIZE_WIDTH - 1; x >= 0; x--) {
                    this->board[x][yy] = this->board[x][yy + 1];
                }
            }
            y++;
        }
    }
    newBlock();
}

void Tetris::move(int dx) {
    tryMove(&this->currentBlockX, this->currentBlockX + dx);
}

bool Tetris::tryMove(int* target, int after) {
    int before = *target;
    *target = after;
    if (!isLegalState()) {
        *target = before;
        return false;
    }
    return true;
}

int Tetris::getBlock(int x, int y) {
    return this->board[x][y];
}

int Tetris::getCurrentType() {
    return this->currentBlock;
}

void Tetris::newBlock() {
    this->currentBlock = Random::getInteger(BLOCK_TYPE_COUNT) + 1;
    this->currentBlockX = Tetris::BOARD_SIZE_WIDTH / 2;
    this->currentBlockY = Tetris::BOARD_SIZE_HEIGHT;
}

List<PointInt>* Tetris::getCurrent() {
    List<PointInt>* list = new List<PointInt>();
    list->add(new PointInt(this->currentBlockX, this->currentBlockY));
    for (int i = 0; i < 3; i++) {
        int x = blocks[this->currentBlock].blocks[i][0];
        int y = blocks[this->currentBlock].blocks[i][1];
        for (int j = 0; j < this->currentRotate; j++) {
            int tempX = x;
            x = -y;
            y = tempX;
        }
        list->add(new PointInt(currentBlockX + x, currentBlockY + y));
    }
    return list;
}

bool Tetris::isLegalState() {
    List<PointInt>* list = getCurrent();
    for (int i = 0; i < 4; i++) {
        PointInt* p = list->get(i);
        if (p->x < 0 || p->x >= Tetris::BOARD_SIZE_WIDTH || p->y < 0 || p->y >= Tetris::BOARD_SIZE_HEIGHT + Tetris::BOARD_CEILING_BUFFER || this->board[p->x][p->y] != 0) {
            delete(list);
            return false;
        }
    }
    delete(list);
    return true;
}