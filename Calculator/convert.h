#ifndef CONVERT_H
#define CONVERT_H

#include <QMainWindow>

namespace Ui {
class convert;
}

class convert : public QMainWindow
{
    Q_OBJECT

public:
    explicit convert(QWidget *parent = nullptr);
    ~convert();
    void doConvert();
signals:
    void back();
private slots:


    void on_pushButton_clicked();

private:
    Ui::convert *ui;
    QString frc;
    QString decimal;
};

#endif // CONVERT_H
