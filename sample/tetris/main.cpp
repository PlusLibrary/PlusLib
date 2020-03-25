#include "main.h"
#include "tetris.h"
#include <stdio.h>
#include <pluslib/opengl/window.h>
#include <pluslib/opengl/graphics2d.h>
#include <pluslib/util/random.h>

#define BLOCK_SIZE 32
#define MAX_KEY 1024
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

struct Block;

Window* window;
Graphics2D graphics;
Color* blockColors[8];
Tetris* tetris = new Tetris();
int keyState[MAX_KEY];
int count = 0;
const int TRANSLATE_X = (WINDOW_WIDTH - Tetris::BOARD_SIZE_WIDTH * BLOCK_SIZE) / 2;
const int TRANSLATE_Y = (WINDOW_HEIGHT - Tetris::BOARD_SIZE_HEIGHT * BLOCK_SIZE) / 2;

int main() {
    init();
    window->show();
    return 0;
}

void drawBlock(int x, int y) {
    graphics.fillRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
}

void render() { 
    graphics.pushMatrix();
    graphics.translate(TRANSLATE_X, TRANSLATE_Y);
    for (int y = 0; y < Tetris::BOARD_SIZE_HEIGHT; y++) {
        for (int x = 0; x < Tetris::BOARD_SIZE_WIDTH; x++) {
            graphics.setColor(blockColors[tetris->getBlock(x, y)]);
            drawBlock(x, Tetris::BOARD_SIZE_HEIGHT - y - 1);
        }
    }
    graphics.setColor(blockColors[tetris->getCurrentType()]);
    List<PointInt>* currentBlocks = tetris->getCurrent();
    currentBlocks->forEach([] (PointInt* p) {
        if (p->y < Tetris::BOARD_SIZE_HEIGHT) {
            drawBlock(p->x, Tetris::BOARD_SIZE_HEIGHT - p->y - 1);
        }
    });
    delete(currentBlocks);
    if (++count % 30 == 0) {
        tetris->progress(false);
    }
    graphics.popMatrix();
}

void keyEvent(int keyCode, int action) {
    if (keyCode >= MAX_KEY) {
        return;
    }
    if (!keyState[keyCode] && action) {
        keyState[keyCode] = action;
        switch (keyCode) {
            case 32:
                tetris->progress(true);
                break;
            case 262: // right
            case 263: // left
                tetris->move(keyCode == 262 ? 1 : -1);
                break;
            case 264:
                tetris->progress(false);
                break;
            case 265:
                tetris->rotate();
                break;
        }
    } else if (!action) {
        keyState[keyCode] = 0;
    }
}

void init() {
    window = new Window();
    window->setRenderCallback(render);
    window->setKeyCallback(keyEvent);
    window->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    blockColors[0] = new Color(224, 224, 224);
    for (int i = 0; i < Tetris::BLOCK_TYPE_COUNT; i++) {
        blockColors[i + 1] = Color::fromHSB(i / (double) Tetris::BLOCK_TYPE_COUNT, 0.375, 0.9375);
    }
}