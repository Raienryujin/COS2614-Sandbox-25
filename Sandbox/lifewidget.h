#ifndef LIFEWIDGET_H
#define LIFEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <vector>

class LifeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LifeWidget(QWidget *parent = nullptr);

    void clear();
    void randomize();
    void pause() { timer->stop(); }
    void resume() { timer->start(100); } // 100 ms per simulation step

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void updateSimulation();

private:
    int rows;
    int cols;
    int cellSize;
    std::vector<std::vector<bool>> grid;
    QTimer *timer;

    int countNeighbors(int r, int c);
    void step();
};

#endif // LIFEWIDGET_H
