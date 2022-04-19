#include "convert.h"
#include "ui_convert.h"
#include"qvalidator.h"
#include"qmath.h"
#include"fraction.h"
#include<QDebug>
//#include"global.h"
convert::convert(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::convert)
{
    ui->setupUi(this);
    ui->decimal->setReadOnly(true);
    ui->frc_3->setReadOnly(true);
    connect(ui->pushButton_back,&QPushButton::clicked,[=](){
    emit this->back();
    });
    auto text=ui->frc->text();
    auto text1=ui->decimal2->text();
    connect(ui->btn_convert,&QPushButton::clicked,[=](){
        doConvert();
    });
    connect(ui->frc,&QLineEdit::textChanged,[=](const QString & text){
        this->frc=text;
    });
    connect(ui->decimal2,&QLineEdit::textChanged,[=](const QString & text){
        this->decimal=text;
    });
    QRegExp regExp("(?:[-1-9][0-9]*|0)(?:\/[-1-9][0-9]*)?");
    QRegExp regExp2("^[+-]?[0-9]+(\.[0-9]{1,4})?");
    //^[+-]?[0-9]+(\.[0-9]{1,4})?
    ui->frc->setValidator(new QRegExpValidator(regExp,this));
    ui->decimal2->setValidator(new QRegExpValidator(regExp2,this));
}

convert::~convert()
{
    delete ui;
}
void convert::doConvert(){
    if(!frc.contains("/")){
    QMessageBox::warning(this,"你在干什么","输入格式有误，请重新输入");
    return;
    }
    auto a=frc.split("/");
    auto up=a[0].toDouble();
    auto down=a[1].toDouble();
    double r=up/down;
    QString result=QString::number(r);
    ui->decimal->setText(result);
}


void convert::on_pushButton_clicked()
{
    if(!decimal.contains(".")){
    QMessageBox::warning(this,"你在干什么","输入格式有误，请重新输入");
    return;
    }
    QString flag="-";
    if(decimal.contains("-")){
        auto tmp1=decimal.split("-");
        auto a=tmp1[1].split(".");
        QString up=a[1];
            int length=a[1].length();
            QString down=QString::number(qPow(10,length));
            fraction tmp,result;
            tmp.up=a[1].toInt();
            tmp.down=down.toInt();
            if(a[0]=="0")
                result=tmp.reduction(tmp);
            else{
                qDebug()<<a[0];
                fraction tmps;
                tmps.up=a[0].toInt()*10;
                tmps.down=10;
                 result=tmp+tmps;
                result=result.reduction(result);
            }
            QString tmpl=QString::number(result.up)+"/"+QString::number(result.down);
            QString c=flag+tmpl;
            ui->frc_3->setText(c);
    }
    else {
            auto a=decimal.split(".");
            QString up=a[1];
            int length=a[1].length();
            QString down=QString::number(qPow(10,length));
            fraction tmp,result;
            tmp.up=a[1].toInt();
            tmp.down=down.toInt();
            if(a[0]=="0")
                result=tmp.reduction(tmp);
            else{
                qDebug()<<a[0];
                fraction tmps;
                tmps.up=a[0].toInt()*10;
                tmps.down=10;
               result=tmp+tmps;
                result=result.reduction(result);

            }
            QString c=QString::number(result.up)+"/"+QString::number(result.down);
            ui->frc_3->setText(c);


//            QString c=QString::number(result.up)+"/"+QString::number(result.down);
//            ui->frc_3->setText(c);


    }
}
