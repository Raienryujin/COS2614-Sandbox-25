#include "lifewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <cstdlib>
#include <ctime>

LifeWidget::LifeWidget(QWidget *parent)
    : QWidget(parent), rows(50), cols(50), cellSize(10)
{
    // Init grid
    grid.resize(rows, std::vector<bool>(cols, false));

    setFixedSize(cols * cellSize, rows * cellSize);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LifeWidget::updateSimulation);
    timer->start(100); // update every 100 ms

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void LifeWidget::clear()
{
    for (auto &row : grid) {
        std::fill(row.begin(), row.end(), false);
    }
    update();
}

void LifeWidget::randomize() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c] = (std::rand() % 2 == 0);
        }
    }
    update();
}


void LifeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::black);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            QRect rect(c * cellSize, r * cellSize, cellSize, cellSize);
            if (grid[r][c]) {
                painter.fillRect(rect, Qt::blue);
            } else {
                painter.fillRect(rect, Qt::white);
            }
            painter.drawRect(rect);
        }
    }
}

void LifeWidget::mousePressEvent(QMouseEvent *event)
{
    int c = static_cast<int>(event->position().x()) / cellSize;
    int r = static_cast<int>(event->position().y()) / cellSize;
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        grid[r][c] = !grid[r][c]; // toggle cell state
        update();
    }
}


int LifeWidget::countNeighbors(int r, int c)
{
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0)
                continue;
            int nr = r + i;
            int nc = c + j;
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc])
                ++count;
        }
    }
    return count;
}

void LifeWidget::step()
{
    std::vector<std::vector<bool>> newGrid = grid;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int neighbors = countNeighbors(r, c);
            if (grid[r][c]) {
                // Live cell: dies if fewer than 2 or more than 3 neighbors.
                if (neighbors < 2 || neighbors > 3)
                    newGrid[r][c] = false;
            } else {
                // Dead cell: becomes alive if exactly 3 neighbors.
                if (neighbors == 3)
                    newGrid[r][c] = true;
            }
        }
    }
    grid = newGrid;
}

void LifeWidget::updateSimulation()
{
    step();
    update();
}
