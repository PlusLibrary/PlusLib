#include <pluslib/opengl/graphics2d.h>

#define COLOR_MAX 256.0
#define CIRCLE_DETAIL_RATIO 1
#define CHARACTER_WIDTH 27
#define LETTER_SPACING 3
#define DEFAULT_FONT_SIZE 48
#define FONT_WIDTH_RATIO .55

Graphics2D* Graphics2D::instance;

Graphics2D* Graphics2D::getInstance() {
    if (Graphics2D::instance == nullptr) {
        Graphics2D::instance = new Graphics2D();
    }
    return Graphics2D::instance;
}

Graphics2D::Graphics2D() {
    this->color = new Color(0, 0, 0);
    this->textRenderer = TextRenderer::getInstance();
    this->fontSize = DEFAULT_FONT_SIZE;
}

void Graphics2D::setColor(int r, int g, int b) {
    this->color->setColor(r, g, b);
}

void Graphics2D::setColor(Color* c) {
    this->color->setColor(c->getR(), c->getG(), c->getB());
}

void Graphics2D::setFontSize(int size) {
    this->fontSize = size;
}

int Graphics2D::textWidth(char16_t* text) {
    int totalWidth = 0;
    for (; text[totalWidth] != '\0'; totalWidth++) {}
    return totalWidth * this->fontSize * FONT_WIDTH_RATIO;
}

void Graphics2D::drawText(char16_t* text, double y, int parentWidth) {
    int totalWidth = 0;
    for (; text[totalWidth] != '\0'; totalWidth++) {}
    drawText(text, (parentWidth - totalWidth * this->fontSize * FONT_WIDTH_RATIO) / 2, y);
}

void Graphics2D::drawText(char16_t* text, double x, double y) {
    loadColor();
    pushMatrix();
    translate(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        Character* character = this->textRenderer->render(text[i], this->fontSize);
        initCharacterTexture(character->getTexture());
        int offset = (this->fontSize * FONT_WIDTH_RATIO - character->getWidth()) / 2;
        translate(offset, 0);
        pushMatrix();
        translate(0, character->getOffset());
        glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2d(0.0, 0.0);
        glTexCoord2d(0.0, 1.0);
        glVertex2d(0.0, character->getHeight());
        glTexCoord2d(1.0, 1.0);
        glVertex2d(character->getWidth(), character->getHeight());
        glTexCoord2d(1.0, 0.0);
        glVertex2d(character->getWidth(), 0.0);
        glEnd();
        popMatrix();
        glDisable(GL_TEXTURE_2D);
        translate(character->getWidth() + offset, 0);
    }
    popMatrix();
}

void Graphics2D::drawLine(double x0, double y0, double x1, double y1) {
    List<PointDouble>* points = new List<PointDouble>();
    glBegin(GL_LINES);
    points->add(new PointDouble(x0, y0));
    points->add(new PointDouble(x1, y1));
    processVertices(GL_LINES, points);
    delete(points);
}

void Graphics2D::fillRect(double x, double y, double width, double height) {
    List<PointDouble>* points = new List<PointDouble>();
    points->add(new PointDouble(x, y));
    points->add(new PointDouble(x, y + height));
    points->add(new PointDouble(x + width, y + height));
    points->add(new PointDouble(x + width, y));
    processVertices(GL_QUADS, points);
    delete(points);
}

void Graphics2D::fillCircle(double centerX, double centerY, double radius) {
    List<PointDouble>* points = new List<PointDouble>();
    int detail = radius * CIRCLE_DETAIL_RATIO;
    for (int i = 0; i < detail; i++) {
        double x = cos(M_PI * 2 * i / detail) * radius + centerX;
        double y = sin(M_PI * 2 * i / detail) * radius + centerY;
        points->add(new PointDouble(x, y));
    }
    processVertices(GL_POLYGON, points);
    delete(points);
}

void Graphics2D::loadColor() {
    glColor3d(color->getR(), color->getG(), color->getB());
}

void Graphics2D::processVertices(GLenum type, List<PointDouble>* vertices) {
    loadColor();
    glBegin(type);
    vertices->forEach([](PointDouble* p) { 
        glVertex2d(p->x, p->y);
    });
    glEnd();
}

void Graphics2D::pushMatrix() {
    glPushMatrix();
}

void Graphics2D::popMatrix() {
    glPopMatrix();
}

void Graphics2D::translate(double x, double y) {
    glTranslated(x, y, 0);
}

void Graphics2D::initCharacterTexture(GLuint texture) {
    glBindTexture(GL_TEXTURE_2D , texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}